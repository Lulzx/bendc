// bendi: a small interpreter for Bend 2, written by hand, to bootstrap
// bendc from source (see boot/README in the main README's "Bootstrapping").
//
// Shared declarations. The interpreter is four files:
//   parse.c  the lexer, layout and parser (a port of bendc.bend's), and
//            module loading: Bend source to declarations (Decl, Expr, Pat)
//   eval.c   the resolver (names to slots, lambdas to closures) and the
//            evaluator (a tree walk with tail calls)
//   heap.c   values, the allocator and a conservative mark-sweep collector
//   prims.c  the natives bendc replaces (U32, Nat, F32, Map.bit, ...), the
//            IO effects bendc uses, and main
#ifndef BENDI_H
#define BENDI_H

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

typedef uint64_t V;

// Utilities
// ---------

void die(const char *fmt, ...);
void *xmalloc(size_t n);
void *xcalloc(size_t n, size_t k);
void *xrealloc(void *p, size_t n);
// Interned names: one pointer per spelling, so names compare with ==.
const char *intern(const char *s);
const char *intern_n(const char *s, size_t n);
const char *cat(const char *a, const char *b);  // interned a ++ b

// A growable array of pointers.
typedef struct { void **a; int n, cap; } Vec;
void vpush(Vec *v, void *x);

// Tokens
// ------

enum { K_ID, K_NAT, K_NATPLUS, K_NUM, K_FLT, K_CHR, K_STR, K_SYM, K_NL, K_IN, K_DE, K_EOF, K_ERR };

typedef struct {
  uint8_t k, sp;      // kind, whether a space comes before it
  uint32_t line;
  uint32_t n;         // K_NAT, K_NATPLUS, K_NUM, K_CHR
  const char *s;      // K_ID, K_FLT, K_SYM, K_ERR (interned)
  const uint32_t *cp; // K_STR: code points
  int len;
} Tok;

// Syntax (as core.bend's Pat and Expr, and bendc.bend's Decl)
// -----------------------------------------------------------

typedef struct Pat Pat;
typedef struct Expr Expr;

enum { P_VAR, P_CTOR, P_NAT, P_SUCC, P_NUM, P_FLT };
struct Pat {
  int k;
  const char *name;   // P_VAR, P_CTOR, P_FLT (its text)
  uint32_t n;         // P_NAT, P_SUCC (k), P_NUM
  int nargs;
  Pat **args;         // P_CTOR fields; P_SUCC: args[0]
};

enum { E_VAR, E_NUM, E_NAT, E_FLT, E_STR, E_CALL, E_CTOR, E_LAM, E_LET, E_MATCH, E_CASE,
       E_SUCC, E_OP, E_ANN, E_TY, E_ERR };
struct Expr {
  int k;
  const char *name;   // E_VAR, E_FLT, E_CTOR, E_OP (the operator), E_ANN (the type), E_TY, E_ERR
  uint32_t n;         // E_NUM, E_NAT, E_SUCC
  int nargs;
  Expr **args;        // E_CALL, E_CTOR, E_TY arguments; E_MATCH scrutinees
  int ncases;
  Expr **cases;       // E_MATCH: its E_CASEs
  Expr *f;            // E_CALL: the function
  Expr *a, *b;        // E_LAM body (a); E_LET value (a), body (b); E_CASE body (a);
                      // E_SUCC, E_ANN (a); E_OP (a, b)
  Pat *pat;           // E_LAM, E_LET
  int npats;
  Pat **pats;         // E_CASE
  const uint32_t *str;
  int slen;           // E_STR
};

// mode: 0 plain, 1 erased (-), 2 shared (+), 3 template (~), 4 bare
typedef struct { const char *name; int mode; const char *ty; } Param;
typedef struct { const char *name; int nfields; const char **fnames; Expr **ftys; } CtorD;

enum { D_DEF, D_EFF, D_LAW, D_TYPE, D_IMPORT };
typedef struct {
  int k;
  const char *name;
  int nps;
  Param *ps;          // D_DEF, D_EFF, D_LAW
  Expr *body, *ret;   // D_DEF (body, ret), D_LAW (ret)
  int nctors;
  CtorD *ctors;       // D_TYPE
  const char *path, *alias;  // D_IMPORT
} Decl;

// parse.c
Tok *lex_all(const uint32_t *src, int n, int *ntoks);
void show_toks(FILE *out, Tok *ts, int n);
Vec parse_file(const char *path, const uint32_t *src, int n);  // of Decl*
void show_decls(FILE *out, Vec ds);
uint32_t *read_source(const char *path, int *n);  // UTF-8 file to code points
Vec load_program(const char *base, const char *path);        // base ++ the program, qualified
const char *ty_head(Expr *e);

// Values
// ------
//
// A value is one word: a number (U32, Char, F32 bits, Nat), a nullary
// constructor (its tag), or a pointer into the heap to a constructor node
// {header, fields...} or a closure {header, Fn*, held...}. Only the
// heap's addresses are pointers, so v < heap_lo is an immediate.

extern uintptr_t heap_lo, heap_span;
static inline int is_ptr(V v) { return v - heap_lo < heap_span; }
#define HDR_TAG(h) ((uint32_t)(h))
#define MK_HDR(tag, n) ((V)(tag) | ((V)(n) << 56))
#define CLO_TAG 0xffffffu
static inline uint32_t tag_of(V v) { return is_ptr(v) ? HDR_TAG(*(V *)v) : (uint32_t)v; }
#define FLD(v, i) (((V *)(v))[(i) + 1])

// heap.c
void heap_init(void);
V *gc_alloc(int words);      // may collect
V *perm_alloc(int words);    // never collected (literals, static closures)
void gc_root(V *slot);       // a word the collector reads as a root
void set_stack_base(void *p);
void gc_stats(void);

// eval.c
typedef struct Fn Fn;
typedef V (*NativeFn)(V *args);
typedef struct CtorInfo { const char *name; uint32_t tag; int arity, kind; } CtorInfo;
enum { CK_NODE, CK_NULLARY, CK_NEWTYPE, CK_ZERO, CK_SUCC };
extern CtorInfo *ct_tuple, *ct_con, *ct_some, *ct_done, *ct_fail, *ct_emit, *ct_halt;
void compile_program(Vec ds);
Fn *find_fn(const char *name);
void define_native(const char *name, int arity, NativeFn f);
V apply(V f, int n, V *args);
V call_fn(Fn *f, V *args);
V mk_node(CtorInfo *c, V *fields);
V mk_closure(Fn *f, int n, V *held);

// prims.c
void install_natives(void);
V mk_string(const uint32_t *cp, size_t n, int perm);
V mk_cstring(const char *s, size_t n);  // from UTF-8
char *string_to_c(V s, size_t *len);
extern int prog_argc;
extern char **prog_argv;

#endif
