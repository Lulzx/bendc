// The evaluator: declarations to a tree of nodes whose variables are frame
// slots, then a strict tree walk over them.
//
// What the compiler does to a def before it runs, as bendc does it:
//   - LM (bendc.bend "Lambda-matches"): \{K: h; m} becomes a lambda that
//     matches its argument, a let whose variable the body never reads is
//     dropped (its value is pure, and may be a proof), and a def whose
//     type is a claim {a == b : T} has no body;
//   - R.ops: (a + b : T) calls T.add, and an operator with no annotation
//     around it belongs to Nat;
//   - the arguments of erased parameters (-A, or a type of Type, Data,
//     Kind, Quant; the modes a def's law gives when it has for lines) are
//     not evaluated at a call of the def by name;
//   - natives (U32, Nat, F32, Map.bit, ...) replace Base's definitions.
// Bool.pick, Bool.and and Bool.or evaluate only the argument they return;
// Bend is total and pure, so this changes no result.
//
// A function's frame holds its arguments, then its locals. A lambda is a
// function of its captured variables and its parameter; a closure holds a
// function and the arguments it has so far. Calls in tail position loop in
// call_fn instead of nesting.
#include "bendi.h"
#include <stdlib.h>
#include <string.h>

#define MAXARGS 32

// Nodes
// -----

enum { N_VAR, N_LIT, N_CAF, N_CALL, N_NATIVE, N_PART, N_APP, N_CTOR, N_LAM, N_LET, N_LETP, N_PAR,
       N_MATCH, N_SUCC, N_PICK, N_ERR };

enum { PK_VAR, PK_NODE, PK_IMM, PK_NEWTYPE, PK_SUCC, PK_ANY };

typedef struct PNode PNode;
struct PNode {
  int k;
  int slot;       // PK_VAR
  V val;          // PK_NODE, PK_IMM: the tag or the value; PK_SUCC: k
  int n;
  PNode **kids;   // PK_NODE fields; PK_NEWTYPE, PK_SUCC: kids[0]
};

typedef struct Node Node;
typedef struct { int npats; PNode **pats; Node *body; } Case;

struct Node {
  int op;
  int slot;          // N_VAR, N_LET
  int n;             // kids
  V lit;             // N_LIT; N_SUCC: k
  Fn *fn;            // N_CAF, N_CALL, N_NATIVE, N_PART, N_LAM
  CtorInfo *ct;      // N_CTOR
  Node **kids;       // arguments, fields, scrutinees, values
  int *caps;         // N_LAM: the slots it captures
  PNode *pat;        // N_LETP
  PNode **pats;      // N_PAR
  int *slots;        // N_MATCH, N_PAR: where the values go
  Node *a, *b, *c;   // N_LET value, body; N_APP function; N_PICK cond, then, else
  int ncases;
  Case *cases;       // N_MATCH
  const char *msg;   // N_ERR, N_MATCH (the def)
};

struct Fn {
  const char *name;
  int arity;         // the arguments it takes (a lambda: its captures and parameter)
  int nparams;       // as declared (an effect takes two more: the answer type and the continuation)
  int nslots;
  Node *body;
  NativeFn native;
  int is_caf, caf_state;
  V caf;
  V clo;             // its closure, when named without arguments
  uint8_t *erased;   // per parameter
  Decl *decl;
  int is_law;
};

// Global names
// ------------

typedef struct { const char *name; Fn *fn; CtorInfo *ct; Decl *law; } Glob;
static Glob *gtab;
static size_t gcap, gcount;

static Glob *glob(const char *name, int make) {
  if (gcount * 2 >= gcap) {
    size_t ncap = gcap ? gcap * 2 : 8192;
    Glob *nt = xcalloc(ncap, sizeof *nt);
    for (size_t i = 0; i < gcap; i++) {
      if (!gtab[i].name) continue;
      size_t j = ((uintptr_t)gtab[i].name >> 3) * 11400714819323198485ull >> 17 & (ncap - 1);
      while (nt[j].name) j = (j + 1) & (ncap - 1);
      nt[j] = gtab[i];
    }
    free(gtab);
    gtab = nt;
    gcap = ncap;
  }
  size_t j = ((uintptr_t)name >> 3) * 11400714819323198485ull >> 17 & (gcap - 1);
  while (gtab[j].name) {
    if (gtab[j].name == name) return &gtab[j];
    j = (j + 1) & (gcap - 1);
  }
  if (!make) return 0;
  gtab[j].name = name;
  gcount++;
  return &gtab[j];
}

Fn *find_fn(const char *name) {
  Glob *g = glob(intern(name), 0);
  return g ? g->fn : 0;
}

static CtorInfo *find_ct(const char *name) {
  Glob *g = glob(name, 0);
  return g ? g->ct : 0;
}

CtorInfo *ct_tuple, *ct_con, *ct_some, *ct_done, *ct_fail, *ct_emit, *ct_halt;

static Fn *new_fn(const char *name) {
  Fn *f = xcalloc(1, sizeof *f);
  f->name = name;
  return f;
}

void define_native(const char *name, int arity, NativeFn nf) {
  Glob *g = glob(intern(name), 1);
  if (!g->fn) g->fn = new_fn(g->name);
  g->fn->native = nf;
  g->fn->arity = arity;
  if (!g->fn->decl) g->fn->nparams = arity;
  g->fn->is_caf = 0;
}

// Values
// ------

V mk_node(CtorInfo *c, V *fields) {
  switch (c->kind) {
  case CK_NULLARY: return c->tag;
  case CK_NEWTYPE: return fields[0];
  case CK_ZERO: return 0;
  case CK_SUCC: return fields[0] + 1;
  }
  V *p = gc_alloc(c->arity + 1);
  p[0] = MK_HDR(c->tag, c->arity);
  memcpy(p + 1, fields, (size_t)c->arity * sizeof(V));
  return (V)p;
}

V mk_closure(Fn *f, int n, V *held) {
  V *p = gc_alloc(n + 2);
  p[0] = MK_HDR(CLO_TAG, n + 1);
  p[1] = (V)(uintptr_t)f;
  memcpy(p + 2, held, (size_t)n * sizeof(V));
  return (V)p;
}

static V fn_closure(Fn *f) {
  if (!f->clo) {
    V *p = perm_alloc(2);
    p[0] = MK_HDR(CLO_TAG, 1);
    p[1] = (V)(uintptr_t)f;
    f->clo = (V)p;
  }
  return f->clo;
}

// Syntax passes
// -------------

static Expr *ety(void) {
  Expr *e = xcalloc(1, sizeof *e);
  e->k = E_TY;
  e->name = intern("");
  return e;
}

// Whether x occurs free in e where a value is read (not inside a type).
static int occurs(const char *x, Expr *e);

static int pat_binds(Pat *p, const char *x) {
  if (p->k == P_VAR) return p->name == x;
  if (p->k == P_CTOR || p->k == P_SUCC)
    for (int i = 0; i < p->nargs; i++) if (pat_binds(p->args[i], x)) return 1;
  return 0;
}

static int occurs(const char *x, Expr *e) {
  switch (e->k) {
  case E_VAR: return e->name == x;
  case E_CALL:
    if (occurs(x, e->f)) return 1;
    for (int i = 0; i < e->nargs; i++) if (occurs(x, e->args[i])) return 1;
    return 0;
  case E_CTOR:
    for (int i = 0; i < e->nargs; i++) if (occurs(x, e->args[i])) return 1;
    return 0;
  case E_LAM: return !pat_binds(e->pat, x) && occurs(x, e->a);
  case E_LET: return occurs(x, e->a) || (!pat_binds(e->pat, x) && occurs(x, e->b));
  case E_MATCH:
    for (int i = 0; i < e->nargs; i++) if (occurs(x, e->args[i])) return 1;
    for (int i = 0; i < e->ncases; i++) if (occurs(x, e->cases[i])) return 1;
    return 0;
  case E_CASE:
    for (int i = 0; i < e->npats; i++) if (pat_binds(e->pats[i], x)) return 0;
    return occurs(x, e->a);
  case E_SUCC: case E_ANN: return occurs(x, e->a);
  case E_OP: return occurs(x, e->a) || occurs(x, e->b);
  default: return 0;
  }
}

static const char *s_lm, *s_mat, *s_efq, *s_par, *s_gpu;

static Expr *mk_evar(const char *n) { Expr *e = xcalloc(1, sizeof *e); e->k = E_VAR; e->name = n; return e; }
static Pat *mk_pvar(const char *n) { Pat *p = xcalloc(1, sizeof *p); p->k = P_VAR; p->name = n; return p; }

static Expr *lm_go(Expr *e);

// The arms of a %mat chain (LM.arms), appended to cs.
static void lm_arms(Expr *e, Vec *cs) {
  if (e->k == E_CTOR && e->name == s_mat && e->nargs == 3 && e->args[0]->k == E_CTOR) {
    const char *c = e->args[0]->name;
    CtorInfo *ci = find_ct(c);
    if (!ci) die("unknown constructor %s in a lambda-match", c);
    int n = ci->arity;
    Pat *p = xcalloc(1, sizeof *p);
    p->k = P_CTOR;
    p->name = c;
    p->nargs = n;
    p->args = xmalloc((size_t)(n + 1) * sizeof(Pat *));
    Expr *h = e->args[1];
    int i = 0;
    while (i < n && h->k == E_LAM && h->pat->k == P_VAR) { p->args[i++] = h->pat; h = h->a; }
    if (i < n) {
      Expr *call = xcalloc(1, sizeof *call);
      call->k = E_CALL;
      call->f = h;
      call->nargs = n - i;
      call->args = xmalloc((size_t)(n - i) * sizeof(Expr *));
      for (int j = i; j < n; j++) {
        char b[32];
        snprintf(b, sizeof b, "_lm%d", j);
        p->args[j] = mk_pvar(intern(b));
        call->args[j - i] = mk_evar(p->args[j]->name);
      }
      h = call;
    }
    Expr *k = xcalloc(1, sizeof *k);
    k->k = E_CASE;
    k->npats = 1;
    k->pats = xmalloc(sizeof(Pat *));
    k->pats[0] = p;
    k->a = h;
    vpush(cs, k);
    lm_arms(e->args[2], cs);
    return;
  }
  if (e->k == E_CTOR && e->name == s_efq && e->nargs == 0) return;
  Expr *k = xcalloc(1, sizeof *k);
  k->k = E_CASE;
  k->npats = 1;
  k->pats = xmalloc(sizeof(Pat *));
  if (e->k == E_LAM && e->pat->k == P_VAR) { k->pats[0] = e->pat; k->a = e->a; }
  else {
    k->pats[0] = mk_pvar(s_lm);
    Expr *call = xcalloc(1, sizeof *call);
    call->k = E_CALL;
    call->f = e;
    call->nargs = 1;
    call->args = xmalloc(sizeof(Expr *));
    call->args[0] = mk_evar(s_lm);
    k->a = call;
  }
  vpush(cs, k);
}

static Expr *lm_go(Expr *e) {
  switch (e->k) {
  case E_CALL:
    e->f = lm_go(e->f);
    for (int i = 0; i < e->nargs; i++) e->args[i] = lm_go(e->args[i]);
    return e;
  case E_CTOR:
    for (int i = 0; i < e->nargs; i++) e->args[i] = lm_go(e->args[i]);
    if (e->name == s_mat) {
      Vec cs = {0, 0, 0};
      lm_arms(e, &cs);
      Expr *m = xcalloc(1, sizeof *m);
      m->k = E_MATCH;
      m->nargs = 1;
      m->args = xmalloc(sizeof(Expr *));
      m->args[0] = mk_evar(s_lm);
      m->ncases = cs.n;
      m->cases = (Expr **)cs.a;
      Expr *l = xcalloc(1, sizeof *l);
      l->k = E_LAM;
      l->pat = mk_pvar(s_lm);
      l->a = m;
      return l;
    }
    return e;
  case E_LAM: e->a = lm_go(e->a); return e;
  case E_LET:
    e->b = lm_go(e->b);
    if (e->pat->k == P_VAR && !occurs(e->pat->name, e->b)) return e->b;
    e->a = lm_go(e->a);
    return e;
  case E_MATCH:
    for (int i = 0; i < e->nargs; i++) e->args[i] = lm_go(e->args[i]);
    for (int i = 0; i < e->ncases; i++) e->cases[i] = lm_go(e->cases[i]);
    return e;
  case E_CASE: case E_SUCC: case E_ANN: e->a = lm_go(e->a); return e;
  case E_OP: e->a = lm_go(e->a); e->b = lm_go(e->b); return e;
  default: return e;
  }
}

// Compiling
// ---------

typedef struct Builder Builder;
struct Builder {
  Fn *fn;
  const char **names;
  int *slots;
  int n, cap;
  int next, max;
};

static void bind(Builder *b, const char *name, int slot) {
  if (b->n == b->cap) {
    b->cap = b->cap ? b->cap * 2 : 32;
    b->names = xrealloc(b->names, (size_t)b->cap * sizeof *b->names);
    b->slots = xrealloc(b->slots, (size_t)b->cap * sizeof *b->slots);
  }
  b->names[b->n] = name;
  b->slots[b->n] = slot;
  b->n++;
}

static int new_slot(Builder *b) {
  int s = b->next++;
  if (b->next > b->max) b->max = b->next;
  return s;
}

static int lookup(Builder *b, const char *name) {
  for (int i = b->n - 1; i >= 0; i--) if (b->names[i] == name) return b->slots[i];
  return -1;
}

static Node *nd(int op) { Node *n = xcalloc(1, sizeof *n); n->op = op; return n; }

static Node *lit(V v) { Node *n = nd(N_LIT); n->lit = v; return n; }

static Node *err_node(const char *msg) { Node *n = nd(N_ERR); n->msg = msg; return n; }

static const char *cur_def;

static CtorInfo *need_ct(const char *name) {
  CtorInfo *c = find_ct(name);
  if (!c) die("in %s: unknown constructor %s", cur_def, name);
  return c;
}

static PNode *pn(int k) { PNode *p = xcalloc(1, sizeof *p); p->k = k; return p; }

static uint32_t f32_bits(const char *text) {
  union { float f; uint32_t u; } x;
  x.f = strtof(text, 0);
  return x.u;
}

// A pattern: its variables get fresh slots, bound in b.
static PNode *comp_pat(Builder *b, Pat *p) {
  PNode *r;
  switch (p->k) {
  case P_VAR:
    r = pn(PK_VAR);
    r->slot = new_slot(b);
    bind(b, p->name, r->slot);
    return r;
  case P_NAT: case P_NUM: r = pn(PK_IMM); r->val = p->n; return r;
  case P_FLT: r = pn(PK_IMM); r->val = f32_bits(p->name); return r;
  case P_SUCC:
    r = pn(PK_SUCC);
    r->val = p->n;
    r->n = 1;
    r->kids = xmalloc(sizeof(PNode *));
    r->kids[0] = comp_pat(b, p->args[0]);
    return r;
  }
  CtorInfo *c = need_ct(p->name);
  if (p->nargs != c->arity) die("in %s: %s takes %d fields, the pattern has %d", cur_def, p->name, c->arity, p->nargs);
  switch (c->kind) {
  case CK_NULLARY: r = pn(PK_IMM); r->val = c->tag; return r;
  case CK_ZERO: r = pn(PK_IMM); r->val = 0; return r;
  case CK_NEWTYPE: case CK_SUCC:
    r = pn(c->kind == CK_SUCC ? PK_SUCC : PK_NEWTYPE);
    r->val = 1;
    r->n = 1;
    r->kids = xmalloc(sizeof(PNode *));
    r->kids[0] = comp_pat(b, p->args[0]);
    return r;
  }
  r = pn(PK_NODE);
  r->val = c->tag;
  r->n = c->arity;
  r->kids = xmalloc((size_t)(c->arity + 1) * sizeof(PNode *));
  for (int i = 0; i < c->arity; i++) r->kids[i] = comp_pat(b, p->args[i]);
  return r;
}

static Node *comp(Builder *b, Expr *e, const char *ty);

static const char *opname(const char *op) {
  static const char *ops[] = {"+", "-", "*", "/", "%", "<", "<=", ">", ">=", ".&.", ".|.", ".^.", "<<", ">>", 0};
  static const char *names[] = {"add", "sub", "mul", "div", "mod", "is_lt", "is_le", "is_gt", "is_ge", "and", "or",
                                "xor", "shln", "shrn"};
  for (int i = 0; ops[i]; i++) if (!strcmp(op, ops[i])) return names[i];
  return "?";
}

// The free variables of e (outside types) that b has as locals, in order.
static void fv(Expr *e, Vec *bound, Builder *b, Vec *out);

static void fv_name(const char *x, Vec *bound, Builder *b, Vec *out) {
  for (int i = bound->n - 1; i >= 0; i--) if (bound->a[i] == x) return;
  for (int i = 0; i < out->n; i++) if (out->a[i] == x) return;
  if (lookup(b, x) >= 0) vpush(out, (void *)x);
}

static void pat_push(Pat *p, Vec *v) {
  if (p->k == P_VAR) vpush(v, (void *)p->name);
  else if (p->k == P_CTOR || p->k == P_SUCC) for (int i = 0; i < p->nargs; i++) pat_push(p->args[i], v);
}

static void fv(Expr *e, Vec *bound, Builder *b, Vec *out) {
  int n0 = bound->n;
  switch (e->k) {
  case E_VAR: fv_name(e->name, bound, b, out); break;
  case E_CALL: fv(e->f, bound, b, out); for (int i = 0; i < e->nargs; i++) fv(e->args[i], bound, b, out); break;
  case E_CTOR: for (int i = 0; i < e->nargs; i++) fv(e->args[i], bound, b, out); break;
  case E_LAM: pat_push(e->pat, bound); fv(e->a, bound, b, out); break;
  case E_LET: fv(e->a, bound, b, out); pat_push(e->pat, bound); fv(e->b, bound, b, out); break;
  case E_MATCH:
    for (int i = 0; i < e->nargs; i++) fv(e->args[i], bound, b, out);
    for (int i = 0; i < e->ncases; i++) fv(e->cases[i], bound, b, out);
    break;
  case E_CASE: for (int i = 0; i < e->npats; i++) pat_push(e->pats[i], bound); fv(e->a, bound, b, out); break;
  case E_SUCC: case E_ANN: fv(e->a, bound, b, out); break;
  case E_OP: fv(e->a, bound, b, out); fv(e->b, bound, b, out); break;
  }
  bound->n = n0;
}

static Node *comp_lam(Builder *b, Expr *e, const char *ty) {
  Vec caps = {0, 0, 0}, bound = {0, 0, 0};
  pat_push(e->pat, &bound);
  fv(e->a, &bound, b, &caps);
  Fn *f = new_fn(cat(cur_def, ".lam"));
  f->arity = caps.n + 1;
  if (f->arity > MAXARGS) die("in %s: a lambda captures %d variables (at most %d)", cur_def, caps.n, MAXARGS - 1);
  f->nparams = f->arity;
  Builder lb;
  memset(&lb, 0, sizeof lb);
  lb.fn = f;
  Node *n = nd(N_LAM);
  n->fn = f;
  n->n = caps.n;
  n->caps = xmalloc((size_t)(caps.n + 1) * sizeof(int));
  for (int i = 0; i < caps.n; i++) {
    n->caps[i] = lookup(b, caps.a[i]);
    bind(&lb, caps.a[i], new_slot(&lb));
  }
  int ps = new_slot(&lb);
  if (e->pat->k == P_VAR) {
    bind(&lb, e->pat->name, ps);
    f->body = comp(&lb, e->a, ty);
  } else {
    Node *l = nd(N_LETP);
    Node *v = nd(N_VAR);
    v->slot = ps;
    l->a = v;
    l->pat = comp_pat(&lb, e->pat);
    l->b = comp(&lb, e->a, ty);
    f->body = l;
  }
  f->nslots = lb.max;
  free(caps.a);
  free(bound.a);
  return n;
}

static Node **comp_args(Builder *b, Expr **as, int n, const char *ty, Fn *f) {
  Node **r = xmalloc((size_t)(n + 1) * sizeof *r);
  for (int i = 0; i < n; i++)
    r[i] = f && i < f->nparams && f->erased && f->erased[i] ? lit(0) : comp(b, as[i], ty);
  return r;
}

static const char *s_pick, *s_and, *s_or;

// A call of the function node fn with args (by value).
static Node *app_node(Node *fnode, Node **kids, int n) {
  Node *r = nd(N_APP);
  r->a = fnode;
  r->kids = kids;
  r->n = n;
  return r;
}

static Node *global_ref(Glob *g) {
  Fn *f = g ? g->fn : 0;
  if (f) {
    if (f->is_caf) { Node *n = nd(N_CAF); n->fn = f; return n; }
    if (f->nparams == 0 && f->arity > 0) {  // an effect of no parameters
      Node *n = nd(N_PART);
      n->fn = f;
      return n;
    }
    return lit(fn_closure(f));
  }
  if (g && g->ct && g->ct->arity == 0) return lit(mk_node(g->ct, 0));
  return lit(0);  // a type
}

static Node *comp_call(Builder *b, Expr *e, const char *ty) {
  Expr *fe = e->f;
  Expr **as = e->args;
  int na = e->nargs;
  if (fe->k == E_VAR && fe->name == s_gpu && na >= 1 && lookup(b, s_gpu) < 0) {
    Expr c = *e;
    c.f = as[0];
    c.args = as + 1;
    c.nargs = na - 1;
    return comp_call(b, &c, ty);
  }
  if (fe->k == E_VAR && lookup(b, fe->name) < 0) {
    Glob *g = glob(fe->name, 0);
    Fn *f = g ? g->fn : 0;
    if (!f) {
      if (g && g->ct) die("in %s: constructor %s called as a function", cur_def, fe->name);
      if (na == 0) return lit(0);
      die("in %s: unknown function %s", cur_def, fe->name);
    }
    if (fe->name == s_pick && na == 4) {
      Node *n = nd(N_PICK);
      n->a = comp(b, as[1], ty);
      n->b = comp(b, as[2], ty);
      n->c = comp(b, as[3], ty);
      return n;
    }
    if ((fe->name == s_and || fe->name == s_or) && na == 2) {
      Node *n = nd(N_PICK);
      n->a = comp(b, as[0], ty);
      n->b = fe->name == s_and ? comp(b, as[1], ty) : lit(1);
      n->c = fe->name == s_and ? lit(0) : comp(b, as[1], ty);
      return n;
    }
    if (f->is_caf) {
      Node *c = nd(N_CAF);
      c->fn = f;
      if (na == 0) return c;
      return app_node(c, comp_args(b, as, na, ty, 0), na);
    }
    Node **kids = comp_args(b, as, na, ty, f);
    if (na < f->arity) {
      if (na > MAXARGS) die("too many arguments");
      Node *n = nd(N_PART);
      n->fn = f;
      n->kids = kids;
      n->n = na;
      return n;
    }
    Node *n = nd(f->native ? N_NATIVE : N_CALL);
    n->fn = f;
    n->kids = kids;
    n->n = f->arity;
    if (na == f->arity) return n;
    return app_node(n, kids + f->arity, na - f->arity);
  }
  Node *fn = comp(b, fe, ty);
  if (na == 0) return fn;
  return app_node(fn, comp_args(b, as, na, ty, 0), na);
}

static Node *comp_match(Builder *b, Expr *e, const char *ty) {
  Node *n = nd(N_MATCH);
  n->msg = cur_def;
  n->n = e->nargs;
  n->kids = xmalloc((size_t)(e->nargs + 1) * sizeof(Node *));
  n->slots = xmalloc((size_t)(e->nargs + 1) * sizeof(int));
  for (int i = 0; i < e->nargs; i++) {
    n->kids[i] = comp(b, e->args[i], ty);
    n->slots[i] = new_slot(b);
  }
  n->ncases = e->ncases;
  n->cases = xmalloc((size_t)(e->ncases + 1) * sizeof(Case));
  for (int i = 0; i < e->ncases; i++) {
    Expr *c = e->cases[i];
    int n0 = b->n, s0 = b->next;
    if (c->npats != e->nargs) die("in %s: a case with %d patterns for %d values", cur_def, c->npats, e->nargs);
    n->cases[i].npats = c->npats;
    n->cases[i].pats = xmalloc((size_t)(c->npats + 1) * sizeof(PNode *));
    for (int j = 0; j < c->npats; j++) n->cases[i].pats[j] = comp_pat(b, c->pats[j]);
    n->cases[i].body = comp(b, c->a, ty);
    b->n = n0;
    b->next = s0;
  }
  return n;
}

static Node *comp(Builder *b, Expr *e, const char *ty) {
  Node *n;
  switch (e->k) {
  case E_VAR: {
    int s = lookup(b, e->name);
    if (s >= 0) { n = nd(N_VAR); n->slot = s; return n; }
    return global_ref(glob(e->name, 0));
  }
  case E_NUM: case E_NAT: return lit(e->n);
  case E_FLT: return lit(f32_bits(e->name));
  case E_STR: return lit(mk_string(e->str, (size_t)e->slen, 1));
  case E_CALL: return comp_call(b, e, ty);
  case E_CTOR: {
    if (e->name == s_efq) return err_node("an empty lambda-match was applied");
    CtorInfo *c = need_ct(e->name);
    if (e->nargs != c->arity) die("in %s: %s takes %d fields, given %d", cur_def, e->name, c->arity, e->nargs);
    if (c->arity == 0) return lit(mk_node(c, 0));
    n = nd(N_CTOR);
    n->ct = c;
    n->n = e->nargs;
    n->kids = comp_args(b, e->args, e->nargs, ty, 0);
    if (c->kind == CK_NEWTYPE) return n->kids[0];
    if (c->kind == CK_SUCC) { Node *s = nd(N_SUCC); s->lit = 1; s->a = n->kids[0]; return s; }
    return n;
  }
  case E_LAM: return comp_lam(b, e, ty);
  case E_LET: {
    int n0 = b->n, s0 = b->next;
    if (e->pat->k == P_CTOR && e->pat->name == s_par) {
      Expr *vs = e->a;
      n = nd(N_PAR);
      n->n = e->pat->nargs;
      if (vs->nargs != n->n) die("in %s: a parallel let of %d patterns and %d values", cur_def, n->n, vs->nargs);
      n->slots = xmalloc((size_t)(n->n + 1) * sizeof(int));
      for (int i = 0; i < n->n; i++) n->slots[i] = new_slot(b);  // before the values' own slots
      n->kids = comp_args(b, vs->args, vs->nargs, ty, 0);
      n->pats = xmalloc((size_t)(n->n + 1) * sizeof(PNode *));
      for (int i = 0; i < n->n; i++) n->pats[i] = comp_pat(b, e->pat->args[i]);
      n->b = comp(b, e->b, ty);
    } else if (e->pat->k == P_VAR) {
      n = nd(N_LET);
      n->a = comp(b, e->a, ty);
      n->slot = new_slot(b);
      bind(b, e->pat->name, n->slot);
      n->b = comp(b, e->b, ty);
    } else {
      n = nd(N_LETP);
      n->a = comp(b, e->a, ty);
      n->pat = comp_pat(b, e->pat);
      n->b = comp(b, e->b, ty);
    }
    b->n = n0;
    b->next = s0;
    return n;
  }
  case E_MATCH: return comp_match(b, e, ty);
  case E_SUCC:
    n = nd(N_SUCC);
    n->lit = e->n;
    n->a = comp(b, e->a, ty);
    return n;
  case E_OP: {
    Expr call, f, *args[2];
    memset(&call, 0, sizeof call);
    memset(&f, 0, sizeof f);
    f.k = E_VAR;
    f.name = cat(cat(ty, "."), opname(e->name));
    args[0] = e->a;
    args[1] = e->b;
    call.k = E_CALL;
    call.f = &f;
    call.nargs = 2;
    call.args = args;
    return comp_call(b, &call, ty);
  }
  case E_ANN: return comp(b, e->a, *e->name ? e->name : ty);
  case E_TY: return lit(0);
  case E_ERR: return err_node(e->name);
  }
  die("in %s: cannot compile expression kind %d", cur_def, e->k);
  return 0;
}

// Declarations
// ------------

static int erased_ty(const char *t) {
  return !strcmp(t, "Type") || !strcmp(t, "Data") || !strcmp(t, "Quant") || !strcmp(t, "Kind");
}

static void set_erased(Fn *f, Param *ps, int n, Decl *law) {
  int bare = 1;
  if (law && law->nps > 0) { ps = law->ps; n = law->nps; bare = 0; }
  f->erased = xcalloc((size_t)(f->nparams + 1), 1);
  for (int i = 0; i < n && i < f->nparams; i++) {
    int m = ps[i].mode;
    if (bare && m == 4) m = 0;
    f->erased[i] = m == 1 || m == 4 || erased_ty(ps[i].ty);
  }
}

static const char *s_eq;

static void compile_def(Fn *f) {
  Decl *d = f->decl;
  cur_def = f->name;
  Glob *g = glob(f->name, 0);
  Decl *law = g ? g->law : 0;
  int claim = !strcmp(ty_head(d->ret), "==") || (law && !strcmp(ty_head(law->ret), "=="));
  Expr *body = claim ? ety() : lm_go(d->body);
  Builder b;
  memset(&b, 0, sizeof b);
  b.fn = f;
  for (int i = 0; i < d->nps; i++) bind(&b, d->ps[i].name, new_slot(&b));
  f->body = comp(&b, body, intern("Nat"));
  f->nslots = b.max;
}

void compile_program(Vec ds) {
  s_lm = intern("_lm"); s_mat = intern("%mat"); s_efq = intern("%efq"); s_par = intern("%par");
  s_gpu = intern("%gpu"); s_pick = intern("Bool.pick"); s_and = intern("Bool.and"); s_or = intern("Bool.or");
  s_eq = intern("==");
  // Types and laws first: a later declaration of a name replaces an earlier.
  for (int i = 0; i < ds.n; i++) {
    Decl *d = ds.a[i];
    if (d->k == D_TYPE) {
      for (int j = 0; j < d->nctors; j++) {
        CtorD *c = &d->ctors[j];
        CtorInfo *ci = xcalloc(1, sizeof *ci);
        ci->name = c->name;
        ci->tag = (uint32_t)j;
        ci->arity = c->nfields;
        if (!strcmp(d->name, "Nat")) ci->kind = !strcmp(c->name, "Zero") ? CK_ZERO : CK_SUCC;
        else if (d->nctors == 1 && c->nfields == 1) ci->kind = CK_NEWTYPE;
        else if (c->nfields == 0) ci->kind = CK_NULLARY;
        else ci->kind = CK_NODE;
        glob(c->name, 1)->ct = ci;
      }
    } else if (d->k == D_LAW) glob(d->name, 1)->law = d;
  }
  for (int i = 0; i < ds.n; i++) {
    Decl *d = ds.a[i];
    if (d->k != D_DEF && d->k != D_EFF && d->k != D_LAW) continue;
    Glob *g = glob(d->name, 1);
    if (d->k == D_LAW) {
      if (!g->fn) { g->fn = new_fn(g->name); g->fn->is_law = 1; g->fn->nparams = g->fn->arity = d->nps; }
      continue;
    }
    if (!g->fn) g->fn = new_fn(g->name);
    Fn *f = g->fn;
    if (f->native) continue;
    f->is_law = 0;
    f->decl = d;
    f->nparams = d->nps;
    f->arity = d->k == D_EFF ? d->nps + 2 : d->nps;
    f->is_caf = d->k == D_DEF && d->nps == 0;
    if (f->arity > MAXARGS) die("%s takes %d arguments (at most %d)", f->name, f->arity, MAXARGS);
    set_erased(f, d->ps, d->nps, g->law);
  }
  // Natives keep the erasure of the declaration they replace.
  for (size_t i = 0; i < gcap; i++) {
    Glob *g = &gtab[i];
    if (!g->name || !g->fn || !g->fn->native || g->fn->erased) continue;
    Fn *f = g->fn;
    Decl *d = 0;
    for (int j = ds.n - 1; j >= 0 && !d; j--) {
      Decl *e = ds.a[j];
      if ((e->k == D_DEF || e->k == D_EFF) && e->name == g->name) d = e;
    }
    f->nparams = f->arity;
    if (d) {
      if (d->k == D_EFF) f->nparams = d->nps;
      set_erased(f, d->ps, d->nps < f->nparams ? d->nps : f->nparams, g->law);
    } else if (g->law) set_erased(f, g->law->ps, g->law->nps, 0);
  }
  ct_tuple = find_ct(intern("Tuple"));
  ct_con = find_ct(intern("Con"));
  ct_some = find_ct(intern("Some"));
  ct_done = find_ct(intern("Done"));
  ct_fail = find_ct(intern("Fail"));
  ct_emit = find_ct(intern("Emit"));
  ct_halt = find_ct(intern("Halt"));
  for (size_t i = 0; i < gcap; i++) {
    Glob *g = &gtab[i];
    if (g->name && g->fn && !g->fn->native && g->fn->decl && g->fn->decl->k == D_DEF) compile_def(g->fn);
  }
}

// Running
// -------

typedef struct { Fn *fn; V *args; } Tail;

static V eval(Node *e, V *fr, Tail *t);

static int pmatch(PNode *p, V v, V *fr) {
  for (;;) {
    switch (p->k) {
    case PK_VAR: fr[p->slot] = v; return 1;
    case PK_IMM: return v == p->val;
    case PK_NEWTYPE: p = p->kids[0]; continue;
    case PK_SUCC:
      if (v < p->val) return 0;
      v -= p->val;
      p = p->kids[0];
      continue;
    case PK_NODE: {
      if (!is_ptr(v) || HDR_TAG(*(V *)v) != (uint32_t)p->val) return 0;
      int n = p->n;
      for (int i = 0; i < n - 1; i++) if (!pmatch(p->kids[i], FLD(v, i), fr)) return 0;
      if (n == 0) return 1;
      v = FLD(v, n - 1);
      p = p->kids[n - 1];
      continue;
    }
    default: return 1;
    }
  }
}

static V fn_caf(Fn *f) {
  if (f->caf_state == 2) return f->caf;
  if (f->caf_state == 1) die("%s depends on itself", f->name);
  f->caf_state = 1;
  V v = call_fn(f, 0);
  f->caf = v;
  gc_root(&f->caf);
  f->caf_state = 2;
  return v;
}

static __attribute__((noinline)) void die_law(Fn *f) {
  if (f->is_law) die("%s has no definition (a law) but was called", f->name);
  die("%s has no body", f->name);
}

V call_fn(Fn *f, V *args) {
  V abuf[MAXARGS];
  for (;;) {
    if (f->native) return f->native(args);
    if (!f->body) die_law(f);
    V fr[f->nslots + 1];
    memcpy(fr, args, (size_t)f->arity * sizeof(V));
    Tail t;
    t.fn = 0;
    t.args = abuf;
    V r = eval(f->body, fr, &t);
    if (!t.fn) return r;
    f = t.fn;
    args = abuf;
  }
}

// Applies a closure to n arguments; returns 0 with the call in t when t is
// given and the application ends in a call of a function.
static V apply_t(V f, int n, V *args, Tail *t) {
  V buf[MAXARGS];
  while (n > 0) {
    if (!is_ptr(f) || HDR_TAG(*(V *)f) != CLO_TAG) die("applied a value that is not a function (%llx)", (unsigned long long)f);
    Fn *fn = (Fn *)(uintptr_t)FLD(f, 0);
    int m = (int)(*(V *)f >> 56) - 1;
    int need = fn->arity - m;
    if (n < need) {
      memcpy(buf, &FLD(f, 1), (size_t)m * sizeof(V));
      memcpy(buf + m, args, (size_t)n * sizeof(V));
      return mk_closure(fn, m + n, buf);
    }
    if (n == need && t && !fn->native) {
      memcpy(t->args, &FLD(f, 1), (size_t)m * sizeof(V));
      memcpy(t->args + m, args, (size_t)n * sizeof(V));
      t->fn = fn;
      return 0;
    }
    memcpy(buf, &FLD(f, 1), (size_t)m * sizeof(V));
    memcpy(buf + m, args, (size_t)need * sizeof(V));
    f = call_fn(fn, buf);
    args += need;
    n -= need;
  }
  return f;
}

V apply(V f, int n, V *args) { return apply_t(f, n, args, 0); }

static V eval(Node *e, V *fr, Tail *t) {
  for (;;) {
    switch (e->op) {
    case N_VAR: return fr[e->slot];
    case N_LIT: return e->lit;
    case N_CAF: return fn_caf(e->fn);
    case N_CALL: {
      int n = e->n;
      if (t) {
        V tmp[n + 1];
        for (int i = 0; i < n; i++) tmp[i] = eval(e->kids[i], fr, 0);
        memcpy(t->args, tmp, (size_t)n * sizeof(V));
        t->fn = e->fn;
        return 0;
      }
      V args[n + 1];
      for (int i = 0; i < n; i++) args[i] = eval(e->kids[i], fr, 0);
      return call_fn(e->fn, args);
    }
    case N_NATIVE: {
      V args[e->n + 1];
      for (int i = 0; i < e->n; i++) args[i] = eval(e->kids[i], fr, 0);
      return e->fn->native(args);
    }
    case N_PART: {
      V args[e->n + 1];
      for (int i = 0; i < e->n; i++) args[i] = eval(e->kids[i], fr, 0);
      return mk_closure(e->fn, e->n, args);
    }
    case N_APP: {
      V f = eval(e->a, fr, 0);
      V args[e->n + 1];
      for (int i = 0; i < e->n; i++) args[i] = eval(e->kids[i], fr, 0);
      return apply_t(f, e->n, args, t);
    }
    case N_CTOR: {
      V args[e->n + 1];
      for (int i = 0; i < e->n; i++) args[i] = eval(e->kids[i], fr, 0);
      return mk_node(e->ct, args);
    }
    case N_LAM: {
      V held[e->n + 1];
      for (int i = 0; i < e->n; i++) held[i] = fr[e->caps[i]];
      return mk_closure(e->fn, e->n, held);
    }
    case N_LET:
      fr[e->slot] = eval(e->a, fr, 0);
      e = e->b;
      continue;
    case N_LETP: {
      V v = eval(e->a, fr, 0);
      if (!pmatch(e->pat, v, fr)) die("a let's pattern did not match");
      e = e->b;
      continue;
    }
    case N_PAR:
      for (int i = 0; i < e->n; i++) fr[e->slots[i]] = eval(e->kids[i], fr, 0);
      for (int i = 0; i < e->n; i++)
        if (!pmatch(e->pats[i], fr[e->slots[i]], fr)) die("a let's pattern did not match");
      e = e->b;
      continue;
    case N_MATCH: {
      int n = e->n;
      for (int i = 0; i < n; i++) fr[e->slots[i]] = eval(e->kids[i], fr, 0);
      Case *c = e->cases, *end = c + e->ncases;
      for (; c < end; c++) {
        int j = 0;
        for (; j < n; j++) if (!pmatch(c->pats[j], fr[e->slots[j]], fr)) break;
        if (j == n) break;
      }
      if (c == end) die("in %s: no case matched", e->msg);
      e = c->body;
      continue;
    }
    case N_SUCC: return eval(e->a, fr, 0) + e->lit;
    case N_PICK:
      e = eval(e->a, fr, 0) ? e->b : e->c;
      continue;
    case N_ERR: die("%s", e->msg);
    }
    die("bad node %d", e->op);
  }
}

// A global's value: a def of no parameters evaluated, else its closure.
V global_value(const char *name) {
  Glob *g = glob(intern(name), 0);
  if (!g || !g->fn || (!g->fn->body && !g->fn->native)) die("no definition of %s", name);
  return g->fn->is_caf ? fn_caf(g->fn) : fn_closure(g->fn);
}
