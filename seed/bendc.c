#include "bendrt.h"

static V F_main(void);
static V L0(V *a);
static V W_main(V *a);
static V F_IO_dlist2(V a0);
static V W_IO_dlist2(V *a);
static V F_Main_drun(V a0);
static V L3(V *a);
static V L4(V *a);
static V L5(V *a);
static V L6(V *a);
static V S7(void);
static V W_Main_drun(V *a);
static V F_IO_ddie(V a1, V a2);
static V L8(V *a);
static V L9(V *a);
static V W_IO_ddie(V *a);
static V F_Main_dparse(V a0);
static V W_Main_dparse(V *a);
static V F_P_dfile(V a0);
static V W_P_dfile(V *a);
static V F_Lex_dall(V a0);
static V W_Lex_dall(V *a);
static V F_Lex_dlines(V a0);
static V W_Lex_dlines(V *a);
static V F_String_dlines(V a0);
static V W_String_dlines(V *a);
static V F_String_dsplit(V a0, V a1);
static V W_String_dsplit(V *a);
static V F_Char_dis__eq(V a0, V a1);
static V W_Char_dis__eq(V *a);
static V W_U32_dis__eq(V *a);
static V F_String_dsplit_dfin(V a0, V a1, V a2);
static V W_String_dsplit_dfin(V *a);
static V F_String_dsplit_dpush(V a0, V a1);
static V W_String_dsplit_dpush(V *a);
static V F_Lex_dlines_dgo(V a0, V a1);
static V W_Lex_dlines_dgo(V *a);
static V W_U32_dinc(V *a);
static V F_Lex_dline(V a0, V a1, V a2, V a3);
static V W_Lex_dline(V *a);
static V F_Lex_dclass(V a0);
static V W_Lex_dclass(V *a);
static V F_Bool_dpick(V a1, V a2, V a3);
static V W_Bool_dpick(V *a);
static V F_Char_dis__digit(V a0);
static V W_Char_dis__digit(V *a);
static V W_U32_dis__le(V *a);
static V W_U32_dis__ge(V *a);
static V F_Bool_dand(V a0, V a1);
static V W_Bool_dand(V *a);
static V F_Lex_dis__ids(V a0);
static V W_Lex_dis__ids(V *a);
static V F_Char_dto__u32(V a0);
static V W_Char_dto__u32(V *a);
static V F_Char_dis__alpha(V a0);
static V W_Char_dis__alpha(V *a);
static V F_Char_dis__lower(V a0);
static V W_Char_dis__lower(V *a);
static V F_Char_dis__upper(V a0);
static V W_Char_dis__upper(V *a);
static V F_Bool_dor(V a0, V a1);
static V W_Bool_dor(V *a);
static V F_Lex_dline_dgo(V a0, V a1, V a2, V a3, V a4, V a5);
static V W_Lex_dline_dgo(V *a);
static V F_Lex_dop__of(V a0);
static V W_Lex_dop__of(V *a);
static V F_Lex_dops3(void);
static V S26(void);
static V S27(void);
static V S28(void);
static V S29(void);
static V W_Lex_dops3(V *a);
static V F_Lex_dfind__op(V a0, V a1);
static V W_Lex_dfind__op(V *a);
static V F_String_dstarts__with(V a0, V a1);
static V W_String_dstarts__with(V *a);
static V F_String_dstarts__with_dif(V a0, V a1, V a2);
static V W_String_dstarts__with_dif(V *a);
static V F_Lex_dfind__op_dif(V a0, V a1, V a2, V a3);
static V W_Lex_dfind__op_dif(V *a);
static V F_Lex_dop__of_dgo(V a0, V a1);
static V W_Lex_dop__of_dgo(V *a);
static V F_Lex_dops2(void);
static V S36(void);
static V S37(void);
static V S38(void);
static V S39(void);
static V S40(void);
static V S41(void);
static V S42(void);
static V S43(void);
static V S44(void);
static V S45(void);
static V S46(void);
static V S47(void);
static V S48(void);
static V W_Lex_dops2(V *a);
static V F_Lex_dop__of_dtwo(V a0, V a1);
static V W_Lex_dop__of_dtwo(V *a);
static V F_String_dtake(V a0, V a1);
static V W_String_dtake(V *a);
static V F_Lex_dline_dop(V a0, V a1, V a2, V a3, V a4);
static V W_Lex_dline_dop(V *a);
static V F_String_dlength(V a0);
static V W_String_dlength(V *a);
static V F_String_ddrop(V a0, V a1);
static V W_String_ddrop(V *a);
static V F_Lex_dstr(V a0, V a1);
static V W_Lex_dstr(V *a);
static V F_Lex_dstr_dif(V a0, V a1, V a2, V a3);
static V W_Lex_dstr_dif(V *a);
static V F_Lex_dlit__char(V a0);
static V W_Lex_dlit__char(V *a);
static V F_Lex_dlit__char_dif(V a0, V a1, V a2);
static V W_Lex_dlit__char_dif(V *a);
static V F_Lex_dlit__char_desc(V a0);
static V W_Lex_dlit__char_desc(V *a);
static V F_Lex_desc(V a0);
static V W_Lex_desc(V *a);
static V F_Lex_dstr_dnext(V a0, V a1);
static V W_Lex_dstr_dnext(V *a);
static V F_Str_drev(V a0);
static V W_Str_drev(V *a);
static V F_String_dreverse(V a0);
static V W_String_dreverse(V *a);
static V F_String_dreverse_dgo(V a0, V a1);
static V W_String_dreverse_dgo(V *a);
static V F_Lex_dline_dstr(V a0, V a1, V a2, V a3);
static V W_Lex_dline_dstr(V *a);
static V F_Lex_dline_dchr(V a0, V a1, V a2, V a3);
static V W_Lex_dline_dchr(V *a);
static V F_Lex_ddrop1(V a0);
static V W_Lex_ddrop1(V *a);
static V F_Lex_ddigits(V a0, V a1);
static V W_Lex_ddigits(V *a);
static V F_Lex_ddigits_dif(V a0, V a1, V a2, V a3);
static V W_Lex_ddigits_dif(V *a);
static V W_U32_dsub(V *a);
static V W_U32_dmul(V *a);
static V W_U32_dadd(V *a);
static V F_Lex_dline_dnum(V a0, V a1, V a2, V a3);
static V W_Lex_dline_dnum(V *a);
static V F_Lex_dline_dnum_dgo(V a0, V a1, V a2, V a3, V a4);
static V W_Lex_dline_dnum_dgo(V *a);
static V F_Lex_dline_dnum_dif(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V W_Lex_dline_dnum_dif(V *a);
static V F_Lex_ddtext(V a0, V a1);
static V W_Lex_ddtext(V *a);
static V F_Lex_ddtext_dif(V a0, V a1, V a2, V a3);
static V W_Lex_ddtext_dif(V *a);
static V F_Lex_dline_dflt(V a0, V a1, V a2, V a3, V a4);
static V S74(void);
static V W_Lex_dline_dflt(V *a);
static V F_String_dappend(V a0, V a1);
static V W_String_dappend(V *a);
static V F_U32_dshow(V a0);
static V W_U32_dshow(V *a);
static V W_U32_dis__zero(V *a);
static V F_U32_dshow_dif(V a0, V a1);
static V W_U32_dshow_dif(V *a);
static V F_U32_dshow_dgo(V a0, V a1, V a2);
static V W_U32_dshow_dgo(V *a);
static V F_U32_dshow_dfin(V a0, V a1, V a2, V a3);
static V W_U32_dshow_dfin(V *a);
static V W_U32_dmod(V *a);
static V W_U32_ddiv(V *a);
static V F_Lex_dline_dnat(V a0, V a1, V a2, V a3, V a4);
static V W_Lex_dline_dnat(V *a);
static V F_Lex_dline_dnat_dif(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V W_Lex_dline_dnat_dif(V *a);
static V F_Lex_did(V a0, V a1);
static V W_Lex_did(V *a);
static V F_Lex_dis__idc(V a0);
static V W_Lex_dis__idc(V *a);
static V F_Lex_did_dif(V a0, V a1, V a2, V a3);
static V W_Lex_did_dif(V *a);
static V F_Lex_dline_did(V a0, V a1, V a2, V a3);
static V W_Lex_dline_did(V *a);
static V F_List_dreverse(V a2);
static V W_List_dreverse(V *a);
static V F_List_dreverse_dgo(V a2, V a3);
static V W_List_dreverse_dgo(V *a);
static V F_Lex_dindent(V a0);
static V W_Lex_dindent(V *a);
static V F_Lex_dindent_dif(V a0, V a1);
static V W_Lex_dindent_dif(V *a);
static V F_Lex_dlines_dput(V a0, V a1);
static V W_Lex_dlines_dput(V *a);
static V F_Lay_dlines(V a0, V a1);
static V W_Lay_dlines(V *a);
static V F_Lay_dline(V a0, V a1);
static V W_Lay_dline(V *a);
static V F_Lay_dline_dgo(V a0, V a1, V a2, V a3, V a4);
static V W_Lay_dline_dgo(V *a);
static V F_Lay_dtoks(V a0, V a1);
static V S97(void);
static V W_Lay_dtoks(V *a);
static V F_Lay_dis__op(V a0);
static V S99(void);
static V S100(void);
static V S101(void);
static V S102(void);
static V S103(void);
static V S104(void);
static V S105(void);
static V S106(void);
static V S107(void);
static V S108(void);
static V S109(void);
static V S110(void);
static V S111(void);
static V W_Lay_dis__op(V *a);
static V F_String_deq(V a0, V a1);
static V W_String_deq(V *a);
static V F_String_dcmp(V a0, V a1);
static V W_String_dcmp(V *a);
static V F_Char_dcmp(V a0, V a1);
static V W_Char_dcmp(V *a);
static V W_U32_dcmp(V *a);
static V F_String_dcmp_dfin(V a0, V a1, V a2);
static V W_String_dcmp_dfin(V *a);
static V F_String_dcmp_drec(V a0, V a1, V a2);
static V W_String_dcmp_drec(V *a);
static V F_String_deq_dfin(V a0);
static V W_String_deq_dfin(V *a);
static V F_Cmp_dis__eq(V a0);
static V W_Cmp_dis__eq(V *a);
static V F_List_dcontains(V a1, V a2, V a3);
static V W_List_dcontains(V *a);
static V F_Lay_dis__sym(V a0, V a1);
static V W_Lay_dis__sym(V *a);
static V F_Str_deq(V a0, V a1);
static V W_Str_deq(V *a);
static V F_Lay_ddelta(V a0);
static V S123(void);
static V S124(void);
static V S125(void);
static V S126(void);
static V S127(void);
static V S128(void);
static V W_Lay_ddelta(V *a);
static V F_Lay_dstart(V a0, V a1, V a2);
static V W_Lay_dstart(V *a);
static V F_Lay_dstart_dop(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7);
static V W_Lay_dstart_dop(V *a);
static V F_Lay_dstart_dgo(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V W_Lay_dstart_dgo(V *a);
static V F_Lay_dtok(V a0, V a1);
static V W_Lay_dtok(V *a);
static V F_Lay_dpop(V a0, V a1, V a2, V a3);
static V W_Lay_dpop(V *a);
static V W_U32_dis__gt(V *a);
static V F_Lay_dpop_dif(V a0, V a1, V a2, V a3, V a4, V a5);
static V W_Lay_dpop_dif(V *a);
static V F_Lay_ddedent(V a0, V a1, V a2, V a3);
static V W_Lay_ddedent(V *a);
static V F_Lay_dstart_dgt(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V W_Lay_dstart_dgt(V *a);
static V F_Lay_dtop(V a0);
static V W_Lay_dtop(V *a);
static V F_Lay_dfinish(V a0);
static V W_Lay_dfinish(V *a);
static V F_Lay_dfinish_dgo(V a0);
static V W_Lay_dfinish_dgo(V *a);
static V F_P_ddecls(void);
static V L140(V *a);
static V L141(V *a);
static V W_P_ddecls(V *a);
static V F_P_dtok__kind(V a0);
static V W_P_dtok__kind(V *a);
static V F_P_dstuck(V a0);
static V W_P_dstuck(V *a);
static V F_P_ddecls_dgo(V a0);
static V L145(V *a);
static V L146(V *a);
static V W_P_ddecls_dgo(V *a);
static V F_Parser_dpure(V a1);
static V L147(V *a);
static V W_Parser_dpure(V *a);
static V F_Parser_dbind(V a2, V a3);
static V L148(V *a);
static V W_Parser_dbind(V *a);
static V F_Parser_dgo(V a2, V a3);
static V W_Parser_dgo(V *a);
static V F_P_ddecl(void);
static V L150(V *a);
static V S151(void);
static V W_P_ddecl(V *a);
static V F_P_dtok__is(V a0, V a1);
static V W_P_dtok__is(V *a);
static V F_P_ddecl_dat(V a0, V a1);
static V L154(V *a);
static V L155(V *a);
static V L156(V *a);
static V S157(void);
static V S158(void);
static V S159(void);
static V S160(void);
static V W_P_ddecl_dat(V *a);
static V F_P_dtok__which__id(V a0, V a1);
static V W_P_dtok__which__id(V *a);
static V F_P_dwhich(V a0, V a1);
static V W_P_dwhich(V *a);
static V F_P_dwhich_dif(V a0, V a1, V a2);
static V W_P_dwhich_dif(V *a);
static V F_P_ddecl_dgo(V a0);
static V S165(void);
static V L166(V *a);
static V S167(void);
static V S168(void);
static V W_P_ddecl_dgo(V *a);
static V F_P_derr(V a0);
static V L169(V *a);
static V W_P_derr(V *a);
static V F_P_derr_dgo(V a0, V a1);
static V S171(void);
static V S172(void);
static V S173(void);
static V S174(void);
static V S175(void);
static V W_P_derr_dgo(V *a);
static V F_TK_dshow(V a0);
static V S177(void);
static V S178(void);
static V S179(void);
static V S180(void);
static V S181(void);
static V S182(void);
static V S183(void);
static V S184(void);
static V S185(void);
static V S186(void);
static V S187(void);
static V S188(void);
static V W_TK_dshow(V *a);
static V F_P_dimport(void);
static V L189(V *a);
static V L190(V *a);
static V L191(V *a);
static V S192(void);
static V L193(V *a);
static V L194(V *a);
static V W_P_dimport(V *a);
static V F_P_dskip__line(void);
static V L195(V *a);
static V W_P_dskip__line(V *a);
static V F_P_dskip__line_dgo(V a0);
static V W_P_dskip__line_dgo(V *a);
static V F_P_dskip__block_dgo(V a0, V a1);
static V W_P_dskip__block_dgo(V *a);
static V F_P_dskip__block_dde(V a0, V a1, V a2);
static V W_P_dskip__block_dde(V *a);
static V F_P_dtok__is__id(V a0, V a1);
static V W_P_dtok__is__id(V *a);
static V F_P_dimport_dalias(V a0);
static V L201(V *a);
static V S202(void);
static V W_P_dimport_dalias(V *a);
static V F_P_dident(void);
static V L203(V *a);
static V W_P_dident(V *a);
static V F_P_dident_dk(V a0);
static V L205(V *a);
static V S206(void);
static V L207(V *a);
static V S208(void);
static V W_P_dident_dk(V *a);
static V F_P_dskip(void);
static V L209(V *a);
static V W_P_dskip(V *a);
static V F_P_dskip_dgo(V a0);
static V W_P_dskip_dgo(V *a);
static V F_P_dskip_dif(V a0, V a1, V a2);
static V W_P_dskip_dif(V *a);
static V F_P_dpeek(void);
static V L212(V *a);
static V W_P_dpeek(V *a);
static V F_P_dpeek_dgo(V a0);
static V W_P_dpeek_dgo(V *a);
static V F_P_deof__tok(void);
static V W_P_deof__tok(V *a);
static V F_P_dimport_dpath(void);
static V L214(V *a);
static V W_P_dimport_dpath(V *a);
static V F_P_dimport_dpath_dgo(V a0);
static V S216(void);
static V S217(void);
static V W_P_dimport_dpath_dgo(V *a);
static V F_P_dimport_dpath_dcat(V a0, V a1);
static V W_P_dimport_dpath_dcat(V *a);
static V F_P_dimport_dpath_did(V a0, V a1, V a2, V a3, V a4);
static V S220(void);
static V W_P_dimport_dpath_did(V *a);
static V F_P_dlaw(void);
static V L221(V *a);
static V L222(V *a);
static V S223(void);
static V L224(V *a);
static V L225(V *a);
static V L226(V *a);
static V W_P_dlaw(V *a);
static V F_P_dlaw_dlines(void);
static V L227(V *a);
static V L228(V *a);
static V W_P_dlaw_dlines(V *a);
static V F_P_dis__de(V a0);
static V W_P_dis__de(V *a);
static V F_P_dlaw_dgo(V a0, V a1);
static V L231(V *a);
static V S232(void);
static V W_P_dlaw_dgo(V *a);
static V F_P_dlaw_dline(V a0);
static V L234(V *a);
static V L235(V *a);
static V L236(V *a);
static V L237(V *a);
static V L238(V *a);
static V W_P_dlaw_dline(V *a);
static V F_P_dparam(void);
static V L239(V *a);
static V L240(V *a);
static V L241(V *a);
static V L242(V *a);
static V L243(V *a);
static V S244(void);
static V W_P_dparam(V *a);
static V F_P_dparam_dty(V a0, V a1, V a2);
static V L246(V *a);
static V L247(V *a);
static V S248(void);
static V W_P_dparam_dty(V *a);
static V F_P_dhead(V a0);
static V S250(void);
static V W_P_dhead(V *a);
static V F_P_dexpr(void);
static V W_P_dexpr(V *a);
static V F_P_dbin(V a0);
static V L251(V *a);
static V W_P_dbin(V *a);
static V F_P_dbin_dloop(V a0, V a1);
static V L252(V *a);
static V W_P_dbin_dloop(V *a);
static V F_P_dtok__op(V a0);
static V S254(void);
static V W_P_dtok__op(V *a);
static V F_P_dops(void);
static V S255(void);
static V S256(void);
static V S257(void);
static V S258(void);
static V S259(void);
static V S260(void);
static V S261(void);
static V S262(void);
static V S263(void);
static V S264(void);
static V S265(void);
static V S266(void);
static V S267(void);
static V S268(void);
static V S269(void);
static V S270(void);
static V S271(void);
static V S272(void);
static V S273(void);
static V S274(void);
static V S275(void);
static V S276(void);
static V W_P_dops(V *a);
static V F_P_dop__find(V a0, V a1);
static V S278(void);
static V W_P_dop__find(V *a);
static V F_P_dop__find_dif(V a0, V a1, V a2, V a3);
static V W_P_dop__find_dif(V *a);
static V F_P_dbin_dloop_dop(V a0, V a1, V a2);
static V W_P_dbin_dloop_dop(V *a);
static V W_U32_dis__ne(V *a);
static V F_P_dbin_dloop_dgo(V a0, V a1, V a2, V a3, V a4, V a5);
static V L282(V *a);
static V L283(V *a);
static V W_P_dbin_dloop_dgo(V *a);
static V F_P_dmk__bin(V a0, V a1, V a2);
static V S284(void);
static V S285(void);
static V S286(void);
static V S287(void);
static V S288(void);
static V S289(void);
static V S290(void);
static V S291(void);
static V W_P_dmk__bin(V *a);
static V F_P_dmk__bin_dgo(V a0, V a1, V a2, V a3);
static V S293(void);
static V S294(void);
static V S295(void);
static V S296(void);
static V S297(void);
static V S298(void);
static V S299(void);
static V S300(void);
static V W_P_dmk__bin_dgo(V *a);
static V F_P_dterm(void);
static V L301(V *a);
static V W_P_dterm(V *a);
static V F_P_dpostfix(V a0);
static V L302(V *a);
static V W_P_dpostfix(V *a);
static V F_P_dpostfix_dt(V a0, V a1);
static V S303(void);
static V S304(void);
static V S305(void);
static V W_P_dpostfix_dt(V *a);
static V F_P_dtok__which(V a0, V a1);
static V W_P_dtok__which(V *a);
static V F_P_dtok__sp(V a0);
static V W_P_dtok__sp(V *a);
static V F_P_dpostfix_dk(V a0, V a1);
static V L309(V *a);
static V S310(void);
static V L311(V *a);
static V L312(V *a);
static V L313(V *a);
static V L314(V *a);
static V S315(void);
static V L316(V *a);
static V S317(void);
static V S318(void);
static V W_P_dpostfix_dk(V *a);
static V F_P_dexpect(V a0);
static V L319(V *a);
static V W_P_dexpect(V *a);
static V F_P_dexpect_dif(V a0, V a1);
static V S321(void);
static V S322(void);
static V W_P_dexpect_dif(V *a);
static V F_P_dlist(V a0);
static V L323(V *a);
static V W_P_dlist(V *a);
static V F_P_dlist_dstuck(V a0, V a1, V a2);
static V S325(void);
static V L326(V *a);
static V W_P_dlist_dstuck(V *a);
static V F_P_dlist_dgo(V a0, V a1);
static V L328(V *a);
static V W_P_dlist_dgo(V *a);
static V F_P_dlist_ditem(V a0);
static V L329(V *a);
static V S330(void);
static V L331(V *a);
static V L332(V *a);
static V W_P_dlist_ditem(V *a);
static V F_P_dlist_dmore(V a0, V a1);
static V L334(V *a);
static V W_P_dlist_dmore(V *a);
static V F_P_deat(V a0);
static V L335(V *a);
static V W_P_deat(V *a);
static V F_P_deat_dif(V a0);
static V L337(V *a);
static V W_P_deat_dif(V *a);
static V F_P_dprimary(void);
static V L338(V *a);
static V W_P_dprimary(V *a);
static V F_P_dprimary_dk(V a0);
static V L340(V *a);
static V L341(V *a);
static V L342(V *a);
static V L343(V *a);
static V L344(V *a);
static V L345(V *a);
static V L346(V *a);
static V L347(V *a);
static V L348(V *a);
static V S349(void);
static V S350(void);
static V S351(void);
static V S352(void);
static V S353(void);
static V S354(void);
static V S355(void);
static V S356(void);
static V S357(void);
static V S358(void);
static V L359(V *a);
static V S360(void);
static V W_P_dprimary_dk(V *a);
static V F_P_dprimary_dsym(V a0);
static V L362(V *a);
static V L363(V *a);
static V L364(V *a);
static V L365(V *a);
static V L366(V *a);
static V L367(V *a);
static V L368(V *a);
static V L369(V *a);
static V L370(V *a);
static V S371(void);
static V S372(void);
static V L373(V *a);
static V S374(void);
static V W_P_dprimary_dsym(V *a);
static V F_P_damp_dgo(V a0);
static V L376(V *a);
static V S377(void);
static V W_P_damp_dgo(V *a);
static V F_P_ddep(void);
static V S378(void);
static V L379(V *a);
static V S380(void);
static V L381(V *a);
static V L382(V *a);
static V S383(void);
static V L384(V *a);
static V L385(V *a);
static V S386(void);
static V W_P_ddep(V *a);
static V F_P_dneg(V a0);
static V S388(void);
static V W_P_dneg(V *a);
static V F_P_dbrace(void);
static V L389(V *a);
static V L390(V *a);
static V S391(void);
static V W_P_dbrace(V *a);
static V F_P_dbrace_dgo(V a0);
static V L393(V *a);
static V S394(void);
static V L395(V *a);
static V S396(void);
static V W_P_dbrace_dgo(V *a);
static V F_P_dbrace_dbody(void);
static V L397(V *a);
static V L398(V *a);
static V S399(void);
static V S400(void);
static V S401(void);
static V W_P_dbrace_dbody(V *a);
static V F_P_dbrace_dtail(V a0, V a1);
static V L403(V *a);
static V L404(V *a);
static V S405(void);
static V L406(V *a);
static V L407(V *a);
static V S408(void);
static V L409(V *a);
static V S410(void);
static V L411(V *a);
static V L412(V *a);
static V S413(void);
static V L414(V *a);
static V L415(V *a);
static V S416(void);
static V L417(V *a);
static V S418(void);
static V L419(V *a);
static V L420(V *a);
static V S421(void);
static V L422(V *a);
static V S423(void);
static V L424(V *a);
static V W_P_dbrace_dtail(V *a);
static V F_P_dbrack(void);
static V L425(V *a);
static V L426(V *a);
static V S427(void);
static V W_P_dbrack(V *a);
static V F_P_dbrack_dgo(V a0);
static V L429(V *a);
static V S430(void);
static V W_P_dbrack_dgo(V *a);
static V F_P_dbrack_dbody(void);
static V L431(V *a);
static V L432(V *a);
static V S433(void);
static V W_P_dbrack_dbody(V *a);
static V F_P_dbrack_dtail(V a0, V a1);
static V S435(void);
static V L436(V *a);
static V S437(void);
static V L438(V *a);
static V W_P_dbrack_dtail(V *a);
static V F_P_delist(V a0);
static V S440(void);
static V S441(void);
static V W_P_delist(V *a);
static V F_P_darr(V a0);
static V L442(V *a);
static V L443(V *a);
static V L444(V *a);
static V L445(V *a);
static V L446(V *a);
static V S447(void);
static V L448(V *a);
static V S449(void);
static V L450(V *a);
static V S451(void);
static V S452(void);
static V W_P_darr(V *a);
static V F_P_darr_dsize(V a0, V a1);
static V W_P_darr_dsize(V *a);
static V F_P_darr_dsize_dlit(V a0);
static V L455(V *a);
static V S456(void);
static V L457(V *a);
static V W_P_darr_dsize_dlit(V *a);
static V F_P_dlog2(V a0);
static V W_P_dlog2(V *a);
static V W_U32_dlog2(V *a);
static V W_U32_dfrom__nat(V *a);
static V F_P_dparen(void);
static V L458(V *a);
static V L459(V *a);
static V S460(void);
static V W_P_dparen(V *a);
static V F_P_dparen_dgo(V a0);
static V L462(V *a);
static V S463(void);
static V W_P_dparen_dgo(V *a);
static V F_P_dparen_dbody(void);
static V L464(V *a);
static V L465(V *a);
static V S466(void);
static V S467(void);
static V W_P_dparen_dbody(V *a);
static V F_P_dparen_dtail(V a0, V a1);
static V L469(V *a);
static V S470(void);
static V L471(V *a);
static V L472(V *a);
static V L473(V *a);
static V S474(void);
static V L475(V *a);
static V S476(void);
static V L477(V *a);
static V W_P_dparen_dtail(V *a);
static V F_P_dtuple(V a0);
static V S479(void);
static V S480(void);
static V W_P_dtuple(V *a);
static V F_P_dafter__id(V a0, V a1);
static V S481(void);
static V S482(void);
static V S483(void);
static V W_P_dafter__id(V *a);
static V F_P_dafter__id_dgo(V a0, V a1, V a2);
static V L485(V *a);
static V L486(V *a);
static V W_P_dafter__id_dgo(V *a);
static V F_P_dafter__id_dk(V a0, V a1);
static V L488(V *a);
static V S489(void);
static V L490(V *a);
static V L491(V *a);
static V L492(V *a);
static V W_P_dafter__id_dk(V *a);
static V F_P_dtyargs(void);
static V L493(V *a);
static V W_P_dtyargs(V *a);
static V F_P_dtyargs_dgo(V a0, V a1);
static V W_P_dtyargs_dgo(V *a);
static V F_P_dis__gt(V a0);
static V S495(void);
static V S496(void);
static V S497(void);
static V W_P_dis__gt(V *a);
static V F_P_dtyargs_dclose(V a0);
static V L499(V *a);
static V W_P_dtyargs_dclose(V *a);
static V F_P_dtyargs_ditem(void);
static V L500(V *a);
static V S501(void);
static V L502(V *a);
static V L503(V *a);
static V W_P_dtyargs_ditem(V *a);
static V F_P_dtyargs_dmore(V a0);
static V L505(V *a);
static V W_P_dtyargs_dmore(V *a);
static V F_P_dgt(void);
static V L506(V *a);
static V W_P_dgt(V *a);
static V F_P_dgt_dgo(V a0);
static V S508(void);
static V S509(void);
static V S510(void);
static V S511(void);
static V W_P_dgt_dgo(V *a);
static V F_P_dgt_dif(V a0, V a1, V a2, V a3, V a4);
static V S513(void);
static V S514(void);
static V S515(void);
static V W_P_dgt_dif(V *a);
static V F_P_dparam_dskip__mode(V a0);
static V W_P_dparam_dskip__mode(V *a);
static V F_P_dparam_dskip__mode_dgo(V a0);
static V W_P_dparam_dskip__mode_dgo(V *a);
static V F_P_dparam_dmode(V a0);
static V S517(void);
static V S518(void);
static V S519(void);
static V W_P_dparam_dmode(V *a);
static V F_P_dnls(void);
static V L520(V *a);
static V W_P_dnls(V *a);
static V F_P_dis__nl(V a0);
static V W_P_dis__nl(V *a);
static V F_P_dnls_dif(V a0);
static V L523(V *a);
static V W_P_dnls_dif(V *a);
static V F_P_dexpect__in(void);
static V L524(V *a);
static V W_P_dexpect__in(V *a);
static V F_P_dis__in(V a0);
static V W_P_dis__in(V *a);
static V F_P_dexpect__in_dgo(V a0);
static V S527(void);
static V W_P_dexpect__in_dgo(V *a);
static V F_P_dtype(void);
static V L528(V *a);
static V L529(V *a);
static V L530(V *a);
static V S531(void);
static V S532(void);
static V L533(V *a);
static V L534(V *a);
static V L535(V *a);
static V S536(void);
static V L537(V *a);
static V L538(V *a);
static V L539(V *a);
static V W_P_dtype(V *a);
static V F_P_dtype_dbody(V a0);
static V L541(V *a);
static V W_P_dtype_dbody(V *a);
static V F_P_dctors(void);
static V L542(V *a);
static V L543(V *a);
static V W_P_dctors(V *a);
static V F_P_dctors_dgo(V a0, V a1);
static V L545(V *a);
static V L546(V *a);
static V S547(void);
static V L548(V *a);
static V L549(V *a);
static V L550(V *a);
static V W_P_dctors_dgo(V *a);
static V F_P_dfields(void);
static V L551(V *a);
static V S552(void);
static V W_P_dfields(V *a);
static V F_P_dfields_dgo(V a0);
static V L554(V *a);
static V S555(void);
static V L556(V *a);
static V S557(void);
static V L558(V *a);
static V L559(V *a);
static V S560(void);
static V L561(V *a);
static V L562(V *a);
static V S563(void);
static V L564(V *a);
static V L565(V *a);
static V W_P_dfields_dgo(V *a);
static V F_P_duntil__is(void);
static V L566(V *a);
static V W_P_duntil__is(V *a);
static V F_P_duntil__is_dgo(V a0);
static V S568(void);
static V W_P_duntil__is_dgo(V *a);
static V F_P_duntil__is_dif(V a0, V a1, V a2);
static V W_P_duntil__is_dif(V *a);
static V F_P_dtparams_dopt(V a0);
static V L571(V *a);
static V L572(V *a);
static V W_P_dtparams_dopt(V *a);
static V F_P_dtparams(void);
static V S573(void);
static V L574(V *a);
static V L575(V *a);
static V L576(V *a);
static V S577(void);
static V L578(V *a);
static V L579(V *a);
static V W_P_dtparams(V *a);
static V F_P_dtparams_dmore(V a0);
static V L581(V *a);
static V W_P_dtparams_dmore(V *a);
static V F_P_dskip__ann(void);
static V L582(V *a);
static V S583(void);
static V W_P_dskip__ann(V *a);
static V F_P_dskip__ann_dgo(V a0);
static V L585(V *a);
static V L586(V *a);
static V W_P_dskip__ann_dgo(V *a);
static V F_P_ddef(void);
static V L587(V *a);
static V L588(V *a);
static V S589(void);
static V L590(V *a);
static V L591(V *a);
static V L592(V *a);
static V S593(void);
static V L594(V *a);
static V S595(void);
static V L596(V *a);
static V L597(V *a);
static V L598(V *a);
static V S599(void);
static V W_P_ddef(V *a);
static V F_P_ddef_dbody(V a0, V a1, V a2, V a3);
static V L601(V *a);
static V L602(V *a);
static V L603(V *a);
static V L604(V *a);
static V W_P_ddef_dbody(V *a);
static V F_Fold_dplain(V a0);
static V S606(void);
static V S607(void);
static V S608(void);
static V W_Fold_dplain(V *a);
static V F_P_dstmts(void);
static V L609(V *a);
static V L610(V *a);
static V W_P_dstmts(V *a);
static V F_P_dstmts_dgo(V a0, V a1);
static V L612(V *a);
static V L613(V *a);
static V L614(V *a);
static V W_P_dstmts_dgo(V *a);
static V F_List_dappend(V a2, V a3);
static V W_List_dappend(V *a);
static V F_P_dstmt(void);
static V L616(V *a);
static V S617(void);
static V W_P_dstmt(V *a);
static V F_P_dstmt_dgo(V a0, V a1);
static V L619(V *a);
static V S620(void);
static V S621(void);
static V S622(void);
static V W_P_dstmt_dgo(V *a);
static V F_P_dstmt_did(V a0);
static V L624(V *a);
static V L625(V *a);
static V L626(V *a);
static V L627(V *a);
static V L628(V *a);
static V W_P_dstmt_did(V *a);
static V F_P_dstmt_dscan(V a0);
static V W_P_dstmt_dscan(V *a);
static V W_U32_dto__nat(V *a);
static V F_P_dstmt_dscan_dgo(V a0);
static V L630(V *a);
static V W_P_dstmt_dscan_dgo(V *a);
static V F_P_dbind__stmt(void);
static V S631(void);
static V L632(V *a);
static V L633(V *a);
static V L634(V *a);
static V S635(void);
static V W_P_dbind__stmt(V *a);
static V F_Bool_dnot(V a0);
static V W_Bool_dnot(V *a);
static V F_P_dbind_darr(V a0, V a1);
static V L638(V *a);
static V L639(V *a);
static V S640(void);
static V L641(V *a);
static V S642(void);
static V L643(V *a);
static V L644(V *a);
static V S645(void);
static V S646(void);
static V L647(V *a);
static V S648(void);
static V L649(V *a);
static V L650(V *a);
static V W_P_dbind_darr(V *a);
static V F_P_dlet__stmt(void);
static V S651(void);
static V S652(void);
static V L653(V *a);
static V L654(V *a);
static V S655(void);
static V L656(V *a);
static V L657(V *a);
static V W_P_dlet__stmt(V *a);
static V F_P_dlets(V a0, V a1);
static V W_P_dlets(V *a);
static V F_List_dlength(V a2);
static V W_List_dlength(V *a);
static V F_P_dexprs__n(V a0);
static V L662(V *a);
static V L663(V *a);
static V W_P_dexprs__n(V *a);
static V F_P_dpat__seq(V a0);
static V L664(V *a);
static V W_P_dpat__seq(V *a);
static V F_P_dpat__seq_dstop(V a0, V a1);
static V W_P_dpat__seq_dstop(V *a);
static V W_Nat_dis__lt(V *a);
static V F_P_dpat__seq_dgo(V a0, V a1, V a2);
static V L666(V *a);
static V L667(V *a);
static V W_P_dpat__seq_dgo(V *a);
static V F_P_dpat(void);
static V L668(V *a);
static V L669(V *a);
static V S670(void);
static V W_P_dpat(V *a);
static V F_P_dpat_dcons(V a0, V a1);
static V L672(V *a);
static V L673(V *a);
static V S674(void);
static V W_P_dpat_dcons(V *a);
static V F_P_dpat1(void);
static V L675(V *a);
static V W_P_dpat1(V *a);
static V F_P_dpat1_dk(V a0);
static V L677(V *a);
static V L678(V *a);
static V S679(void);
static V L680(V *a);
static V L681(V *a);
static V L682(V *a);
static V L683(V *a);
static V L684(V *a);
static V L685(V *a);
static V S686(void);
static V S687(void);
static V S688(void);
static V S689(void);
static V S690(void);
static V L691(V *a);
static V S692(void);
static V W_P_dpat1_dk(V *a);
static V F_P_dpat_dsym(V a0);
static V L694(V *a);
static V L695(V *a);
static V L696(V *a);
static V S697(void);
static V L698(V *a);
static V L699(V *a);
static V S700(void);
static V L701(V *a);
static V S702(void);
static V L703(V *a);
static V S704(void);
static V W_P_dpat_dsym(V *a);
static V F_P_dplist(V a0);
static V S706(void);
static V S707(void);
static V W_P_dplist(V *a);
static V F_P_dpats(V a0);
static V L708(V *a);
static V W_P_dpats(V *a);
static V F_P_dpats_dgo(V a0, V a1, V a2);
static V W_P_dpats_dgo(V *a);
static V F_P_dpats_dclose(V a0, V a1);
static V L711(V *a);
static V W_P_dpats_dclose(V *a);
static V F_P_dpats_ditem(V a0);
static V L712(V *a);
static V S713(void);
static V L714(V *a);
static V L715(V *a);
static V W_P_dpats_ditem(V *a);
static V F_P_dpats_dmore(V a0, V a1);
static V L717(V *a);
static V W_P_dpats_dmore(V *a);
static V F_P_dptuple(V a0);
static V S719(void);
static V S720(void);
static V W_P_dptuple(V *a);
static V F_P_dpstr(V a0);
static V S722(void);
static V S723(void);
static V W_P_dpstr(V *a);
static V F_P_dpat_did(V a0, V a1);
static V L725(V *a);
static V S726(void);
static V L727(V *a);
static V W_P_dpat_did(V *a);
static V F_P_dscan(void);
static V L728(V *a);
static V W_P_dscan(V *a);
static V F_P_dscan_dret(V a0);
static V W_P_dscan_dret(V *a);
static V F_P_dscan_dgo(V a0, V a1);
static V S730(void);
static V S731(void);
static V S732(void);
static V S733(void);
static V S734(void);
static V S735(void);
static V S736(void);
static V S737(void);
static V W_P_dscan_dgo(V *a);
static V F_P_dscan_dend(V a0, V a1, V a2);
static V W_P_dscan_dend(V *a);
static V F_P_dscan_dsym(V a0, V a1, V a2);
static V W_P_dscan_dsym(V *a);
static V F_P_dscan_dtop(V a0, V a1, V a2, V a3);
static V W_P_dscan_dtop(V *a);
static V F_P_ddo(void);
static V L741(V *a);
static V L742(V *a);
static V S743(void);
static V L744(V *a);
static V L745(V *a);
static V S746(void);
static V L747(V *a);
static V L748(V *a);
static V L749(V *a);
static V W_P_ddo(V *a);
static V F_P_dlast(V a0);
static V S751(void);
static V W_P_dlast(V *a);
static V F_P_dinit(V a0);
static V W_P_dinit(V *a);
static V F_Fold_ddo(V a0, V a1, V a2, V a3);
static V S754(void);
static V S755(void);
static V S756(void);
static V S757(void);
static V S758(void);
static V S759(void);
static V S760(void);
static V S761(void);
static V S762(void);
static V W_Fold_ddo(V *a);
static V F_Fold_dapp(V a0, V a1, V a2, V a3);
static V S763(void);
static V W_Fold_dapp(V *a);
static V F_P_dmatch(void);
static V L764(V *a);
static V L765(V *a);
static V S766(void);
static V L767(V *a);
static V L768(V *a);
static V L769(V *a);
static V W_P_dmatch(V *a);
static V F_P_dmatch_dbody(V a0);
static V L771(V *a);
static V W_P_dmatch_dbody(V *a);
static V F_P_dcases(void);
static V L772(V *a);
static V L773(V *a);
static V W_P_dcases(V *a);
static V F_P_dcases_dde(V a0);
static V L775(V *a);
static V L776(V *a);
static V S777(void);
static V W_P_dcases_dde(V *a);
static V F_P_dcases_dgo(V a0);
static V L779(V *a);
static V S780(void);
static V L781(V *a);
static V S782(void);
static V L783(V *a);
static V L784(V *a);
static V L785(V *a);
static V W_P_dcases_dgo(V *a);
static V F_P_dbody(void);
static V L786(V *a);
static V L787(V *a);
static V W_P_dbody(V *a);
static V F_P_dscrs(void);
static V L788(V *a);
static V S789(void);
static V W_P_dscrs(V *a);
static V F_P_dscrs_dgo(V a0, V a1);
static V L791(V *a);
static V L792(V *a);
static V W_P_dscrs_dgo(V *a);
static V F_P_dskip__rest(void);
static V L793(V *a);
static V W_P_dskip__rest(V *a);
static V F_P_dret_dgo(V a0);
static V L795(V *a);
static V S796(void);
static V W_P_dret_dgo(V *a);
static V F_P_dparams(void);
static V L797(V *a);
static V S798(void);
static V W_P_dparams(V *a);
static V F_P_dparams_dgo(V a0);
static V L800(V *a);
static V L801(V *a);
static V S802(void);
static V L803(V *a);
static V L804(V *a);
static V W_P_dparams_dgo(V *a);
static V F_P_dparams_dmore(V a0);
static V S806(void);
static V L807(V *a);
static V W_P_dparams_dmore(V *a);
static V F_P_dfile_dfin(V a0);
static V W_P_dfile_dfin(V *a);
static V F_P_dfile_derr(V a0);
static V S810(void);
static V W_P_dfile_derr(V *a);
static V F_Main_dparse_dfin(V a0);
static V W_Main_dparse_dfin(V *a);
static V F_String_dis__empty(V a0);
static V W_String_dis__empty(V *a);
static V F_Main_dcompile(V a0, V a1);
static V S815(void);
static V S816(void);
static V W_Main_dcompile(V *a);
static V F_Gen_dprogram(V a0);
static V W_Gen_dprogram(V *a);
static V F_Gen_dprogram_dm(V a0);
static V S818(void);
static V L819(V *a);
static V S820(void);
static V W_Gen_dprogram_dm(V *a);
static V F_G_dbody(V a0, V a1);
static V S822(void);
static V S823(void);
static V W_G_dbody(V *a);
static V F_G_dget(V a1, V a2, V a3);
static V W_G_dget(V *a);
static V F_Map_dget(V a1, V a2, V a3);
static V W_Map_dget(V *a);
static V F_Map_dbit(V a0, V a1);
static V W_Map_dbit(V *a);
static V W_Nat_ddivmod(V *a);
static V F_Map_dbit_dat(V a0, V a1);
static V W_Map_dbit_dat(V *a);
static V F_Map_dbit_dgo(V a0, V a1, V a2);
static V W_Map_dbit_dgo(V *a);
static V F_Map_dbit_dgo_drec(V a0, V a1);
static V W_Map_dbit_dgo_drec(V *a);
static V F_Map_dbit_dchr(V a0, V a1);
static V W_Map_dbit_dchr(V *a);
static V W_Nat_dsub(V *a);
static V F_Map_dbit_du(V a0, V a1);
static V W_Map_dbit_du(V *a);
static V W_U32_dshrn(V *a);
static V W_U32_dand(V *a);
static V F_Map_dbit_dgo_dchr(V a0, V a1);
static V W_Map_dbit_dgo_dchr(V *a);
static V F_Map_dget_dbit(V a1, V a2, V a3, V a4, V a5);
static V W_Map_dget_dbit(V *a);
static V F_Map_dhi(V a3, V a4, V a5);
static V W_Map_dhi(V *a);
static V F_Map_dlo(V a3, V a4, V a5);
static V W_Map_dlo(V *a);
static V F_Map_dget_dleaf(V a1, V a2, V a3);
static V W_Map_dget_dleaf(V *a);
static V F_Pair_dsnd(V a2);
static V W_Pair_dsnd(V *a);
static V F_Gen_dentry(V a0, V a1);
static V S840(void);
static V S841(void);
static V L842(V *a);
static V S843(void);
static V W_Gen_dentry(V *a);
static V F_Gen_dpure(V a1);
static V L844(V *a);
static V W_Gen_dpure(V *a);
static V F_Gen_derror(V a0);
static V L845(V *a);
static V W_Gen_derror(V *a);
static V F_Gen_derror_dgo(V a0, V a1);
static V W_Gen_derror_dgo(V *a);
static V F_Gen_dbind(V a2, V a3);
static V L847(V *a);
static V W_Gen_dbind(V *a);
static V F_Gen_dgo(V a2, V a3);
static V W_Gen_dgo(V *a);
static V F_Ty_dhead(V a0);
static V S850(void);
static V W_Ty_dhead(V *a);
static V F_Gen_dentry_dty(V a0, V a1, V a2);
static V S852(void);
static V L853(V *a);
static V S854(void);
static V S855(void);
static V W_Gen_dentry_dty(V *a);
static V F_Gen_dprinter(V a0, V a1);
static V L857(V *a);
static V W_Gen_dprinter(V *a);
static V F_Gen_dprinter_dmemo(V a0, V a1, V a2, V a3);
static V L859(V *a);
static V S860(void);
static V L861(V *a);
static V L862(V *a);
static V S863(void);
static V S864(void);
static V L865(V *a);
static V L866(V *a);
static V S867(void);
static V S868(void);
static V S869(void);
static V L870(V *a);
static V W_Gen_dprinter_dmemo(V *a);
static V F_Doc_dlist(V a0);
static V W_Doc_dlist(V *a);
static V F_Gen_dcode(V a0);
static V L872(V *a);
static V W_Gen_dcode(V *a);
static V F_Gen_dcode_dgo(V a0, V a1);
static V W_Gen_dcode_dgo(V *a);
static V F_Gen_dprinter_dbody(V a0, V a1, V a2);
static V S874(void);
static V S875(void);
static V S876(void);
static V S877(void);
static V S878(void);
static V S879(void);
static V S880(void);
static V S881(void);
static V W_Gen_dprinter_dbody(V *a);
static V F_Gen_dprinter_dhead(V a0, V a1, V a2);
static V S883(void);
static V S884(void);
static V S885(void);
static V S886(void);
static V S887(void);
static V L888(V *a);
static V S889(void);
static V S890(void);
static V S891(void);
static V L892(V *a);
static V S893(void);
static V S894(void);
static V S895(void);
static V S896(void);
static V W_Gen_dprinter_dhead(V *a);
static V F_Gen_dprinter_dadt(V a0, V a1, V a2);
static V L898(V *a);
static V S899(void);
static V S900(void);
static V W_Gen_dprinter_dadt(V *a);
static V F_Ty_dargs(V a0);
static V W_Ty_dargs(V *a);
static V F_Ty_dbind(V a0, V a1);
static V W_Ty_dbind(V *a);
static V F_Ty_dbind_dgo(V a0, V a1);
static V W_Ty_dbind_dgo(V *a);
static V F_Gen_dprinter_dctors(V a0, V a1, V a2);
static V L905(V *a);
static V L906(V *a);
static V W_Gen_dprinter_dctors(V *a);
static V F_G_dctor(V a0, V a1);
static V W_G_dctor(V *a);
static V F_G_dopt__ctors(V a0);
static V W_G_dopt__ctors(V *a);
static V F_Gen_dprinter_dctor(V a0, V a1, V a2, V a3, V a4);
static V S910(void);
static V S911(void);
static V L912(V *a);
static V S913(void);
static V S914(void);
static V S915(void);
static V W_Gen_dprinter_dctor(V *a);
static V F_Gen_dprinter_dtest(V a0, V a1, V a2);
static V S916(void);
static V S917(void);
static V S918(void);
static V S919(void);
static V S920(void);
static V W_Gen_dprinter_dtest(V *a);
static V F_Gen_dprinter_dfields(V a0, V a1, V a2, V a3, V a4);
static V L922(V *a);
static V L923(V *a);
static V S924(void);
static V S925(void);
static V S926(void);
static V S927(void);
static V S928(void);
static V S929(void);
static V S930(void);
static V W_Gen_dprinter_dfields(V *a);
static V F_Ty_dsubst(V a0, V a1);
static V W_Ty_dsubst(V *a);
static V F_Ty_dsubsts(V a0, V a1);
static V W_Ty_dsubsts(V *a);
static V F_Ty_dfind(V a0, V a1);
static V W_Ty_dfind(V *a);
static V F_Ty_dfind_dif(V a0, V a1, V a2, V a3);
static V W_Ty_dfind_dif(V *a);
static V F_Maybe_ddefault(V a2, V a3);
static V W_Maybe_ddefault(V *a);
static V F_Ty_dtuple(V a0);
static V S937(void);
static V W_Ty_dtuple(V *a);
static V F_Ty_dtuple_dgo(V a0, V a1, V a2);
static V W_Ty_dtuple_dgo(V *a);
static V F_Ty_dtuple_dargs(V a0, V a1);
static V W_Ty_dtuple_dargs(V *a);
static V F_Gen_dprinter_dtuple(V a0, V a1, V a2);
static V L941(V *a);
static V S942(void);
static V S943(void);
static V L944(V *a);
static V S945(void);
static V S946(void);
static V L947(V *a);
static V S948(void);
static V S949(void);
static V W_Gen_dprinter_dtuple(V *a);
static V F_Gen_dproto(V a0);
static V L950(V *a);
static V W_Gen_dproto(V *a);
static V F_Gen_dproto_dgo(V a0, V a1);
static V W_Gen_dproto_dgo(V *a);
static V F_Gen_dmemo_dadd(V a0);
static V L952(V *a);
static V W_Gen_dmemo_dadd(V *a);
static V F_Gen_dmemo_dadd_dgo(V a0, V a1);
static V W_Gen_dmemo_dadd_dgo(V *a);
static V F_Gen_dfresh(void);
static V L954(V *a);
static V W_Gen_dfresh(V *a);
static V F_Gen_dfresh_dgo(V a0);
static V W_Gen_dfresh_dgo(V *a);
static V F_Gen_dmemo_dfind(V a0);
static V L956(V *a);
static V W_Gen_dmemo_dfind(V *a);
static V F_Gen_dmemo_dfind_dgo(V a0, V a1);
static V W_Gen_dmemo_dfind_dgo(V *a);
static V F_Env_dfind(V a0, V a1);
static V W_Env_dfind(V *a);
static V F_Env_dfind_dif(V a0, V a1, V a2, V a3);
static V W_Env_dfind_dif(V *a);
static V F_Expr_dshow(V a0);
static V S961(void);
static V S962(void);
static V S963(void);
static V S964(void);
static V S965(void);
static V S966(void);
static V S967(void);
static V S968(void);
static V S969(void);
static V S970(void);
static V S971(void);
static V S972(void);
static V S973(void);
static V S974(void);
static V S975(void);
static V S976(void);
static V S977(void);
static V S978(void);
static V S979(void);
static V S980(void);
static V S981(void);
static V S982(void);
static V S983(void);
static V S984(void);
static V S985(void);
static V S986(void);
static V S987(void);
static V S988(void);
static V S989(void);
static V S990(void);
static V S991(void);
static V S992(void);
static V S993(void);
static V S994(void);
static V W_Expr_dshow(V *a);
static V F_Pats_dshow(V a0);
static V S996(void);
static V S997(void);
static V W_Pats_dshow(V *a);
static V F_Pat_dshow(V a0);
static V S999(void);
static V S1000(void);
static V S1001(void);
static V S1002(void);
static V W_Pat_dshow(V *a);
static V F_Exprs_dshow(V a0);
static V S1004(void);
static V S1005(void);
static V W_Exprs_dshow(V *a);
static V F_Set_dnew(void);
static V W_Set_dnew(V *a);
static V F_Map_dnew(void);
static V W_Map_dnew(V *a);
static V F_Gen_dall(V a0, V a1, V a2);
static V W_Gen_dall(V *a);
static V F_Set_dhas(V a0, V a1);
static V W_Set_dhas(V *a);
static V F_Map_dhas(V a2, V a3);
static V W_Map_dhas(V *a);
static V F_Map_dhas_dbit(V a2, V a3, V a4, V a5);
static V W_Map_dhas_dbit(V *a);
static V F_Map_dhas_dleaf(V a2, V a3);
static V W_Map_dhas_dleaf(V *a);
static V F_Gen_dall_dseen(V a0, V a1, V a2, V a3);
static V W_Gen_dall_dseen(V *a);
static V F_Gen_dall_dgo(V a0, V a1, V a2, V a3, V a4);
static V L1013(V *a);
static V L1014(V *a);
static V W_Gen_dall_dgo(V *a);
static V F_Set_dadd(V a0, V a1);
static V W_Set_dadd(V *a);
static V F_Map_dset(V a2, V a3, V a4);
static V W_Map_dset(V *a);
static V F_Map_dseek(V a2, V a3);
static V W_Map_dseek(V *a);
static V F_Map_dseek_dbit(V a2, V a3, V a4, V a5);
static V W_Map_dseek_dbit(V *a);
static V F_Map_dset_dgo(V a2, V a3);
static V W_Map_dset_dgo(V *a);
static V F_Map_dset_dfin(V a2, V a3, V a4, V a5, V a6);
static V W_Map_dset_dfin(V *a);
static V F_Map_dset_dfin_dgo(V a2, V a3, V a4, V a5);
static V W_Map_dset_dfin_dgo(V *a);
static V F_Map_ddiff(V a0, V a1);
static V W_Map_ddiff(V *a);
static V F_Map_ddiff_dstep(V a0, V a1);
static V W_Map_ddiff_dstep(V *a);
static V W_U32_dxor(V *a);
static V F_Map_ddiff_dchr(V a0);
static V W_Map_ddiff_dchr(V *a);
static V F_Map_dmsb_du(V a0, V a1);
static V W_Map_dmsb_du(V *a);
static V F_Map_dmsb_du_dif(V a0, V a1, V a2);
static V W_Map_dmsb_du_dif(V *a);
static V W_U32_dshr(V *a);
static V W_Nat_dadd(V *a);
static V F_Map_ddiff_dfin(V a0, V a1, V a2);
static V W_Map_ddiff_dfin(V *a);
static V F_Map_dins(V a2, V a3, V a4, V a5);
static V W_Map_dins(V *a);
static V F_Map_dins_dif(V a2, V a3, V a4, V a5, V a6, V a7, V a8);
static V W_Map_dins_dif(V *a);
static V F_Map_dins_ddeep(V a2, V a3, V a4, V a5, V a6, V a7);
static V W_Map_dins_ddeep(V *a);
static V F_Map_dins_dsplice(V a2, V a3, V a4, V a5);
static V W_Map_dins_dsplice(V *a);
static V F_Map_dins_dsplice_dbit(V a2, V a3, V a4, V a5);
static V W_Map_dins_dsplice_dbit(V *a);
static V F_Map_dput(V a2, V a3, V a4);
static V W_Map_dput(V *a);
static V F_Map_dput_dbit(V a2, V a3, V a4, V a5, V a6);
static V W_Map_dput_dbit(V *a);
static V F_Gen_dtake__refs(void);
static V L1040(V *a);
static V W_Gen_dtake__refs(V *a);
static V F_Gen_dtake__refs_dgo(V a0);
static V W_Gen_dtake__refs_dgo(V *a);
static V F_Gen_ddef(V a0, V a1);
static V W_Gen_ddef(V *a);
static V F_G_ddef(V a0, V a1);
static V W_G_ddef(V *a);
static V F_Gen_ddef_ddecl(V a0, V a1, V a2, V a3);
static V W_Gen_ddef_ddecl(V *a);
static V F_Gen_ddef_dlaw(V a0, V a1, V a2);
static V W_Gen_ddef_dlaw(V *a);
static V F_Gen_ddummy__params(V a0);
static V S1047(void);
static V S1048(void);
static V W_Gen_ddummy__params(V *a);
static V F_Gen_dsig(V a0, V a1, V a2, V a3);
static V S1053(void);
static V S1054(void);
static V S1055(void);
static V S1057(void);
static V W_Gen_dsig(V *a);
static V F_Sig_dwargs(V a0);
static V W_Sig_dwargs(V *a);
static V F_Gen_dwrapper(V a0, V a1);
static V S1060(void);
static V S1061(void);
static V L1062(V *a);
static V S1063(void);
static V S1064(void);
static V S1065(void);
static V S1066(void);
static V S1067(void);
static V W_Gen_dwrapper(V *a);
static V F_String_djoin(V a0, V a1);
static V W_String_djoin(V *a);
static V F_String_djoin_dgo(V a0, V a1, V a2);
static V W_String_djoin_dgo(V *a);
static V F_Gen_df(V a0);
static V S1070(void);
static V W_Gen_df(V *a);
static V F_Gen_dmangle(V a0);
static V S1072(void);
static V W_Gen_dmangle(V *a);
static V F_Gen_dmangle_dchr(V a0);
static V S1073(void);
static V S1074(void);
static V S1075(void);
static V W_Gen_dmangle_dchr(V *a);
static V F_Str_dchr(V a0);
static V W_Str_dchr(V *a);
static V F_Gen_dw(V a0);
static V S1076(void);
static V W_Gen_dw(V *a);
static V F_Gen_ddef_deff(V a0, V a1);
static V S1080(void);
static V S1082(void);
static V S1083(void);
static V S1084(void);
static V S1085(void);
static V S1086(void);
static V L1087(V *a);
static V S1088(void);
static V S1089(void);
static V S1090(void);
static V S1091(void);
static V S1092(void);
static V S1093(void);
static V L1094(V *a);
static V S1095(void);
static V S1096(void);
static V S1097(void);
static V S1098(void);
static V S1099(void);
static V S1100(void);
static V S1101(void);
static V S1102(void);
static V S1103(void);
static V L1104(V *a);
static V W_Gen_ddef_deff(V *a);
static V F_Gen_deff_dargs(V a0, V a1);
static V S1106(void);
static V S1107(void);
static V W_Gen_deff_dargs(V *a);
static V F_String_dto__lower(V a0);
static V W_String_dto__lower(V *a);
static V F_Char_dto__lower(V a0);
static V W_Char_dto__lower(V *a);
static V F_Bool_dto__u32(V a0);
static V W_Bool_dto__u32(V *a);
static V F_Gen_dhost(V a0);
static V S1111(void);
static V W_Gen_dhost(V *a);
static V F_Gen_dhost_dchr(V a0);
static V S1112(void);
static V W_Gen_dhost_dchr(V *a);
static V F_Gen_dcparams(V a0);
static V S1114(void);
static V S1115(void);
static V W_Gen_dcparams(V *a);
static V F_Gen_dcparams_dgo(V a0);
static V S1117(void);
static V W_Gen_dcparams_dgo(V *a);
static V F_Gen_ddef_dnative(V a0, V a1, V a2, V a3, V a4, V a5);
static V W_Gen_ddef_dnative(V *a);
static V F_Gen_ddef_dbody(V a0, V a1, V a2, V a3, V a4);
static V S1121(void);
static V S1122(void);
static V S1123(void);
static V S1124(void);
static V L1125(V *a);
static V S1126(void);
static V L1127(V *a);
static V S1128(void);
static V S1129(void);
static V L1130(V *a);
static V W_Gen_ddef_dbody(V *a);
static V F_R_dops(V a0, V a1);
static V S1132(void);
static V W_R_dops(V *a);
static V F_R_dopss(V a0, V a1);
static V W_R_dopss(V *a);
static V F_R_dopname(V a0);
static V S1134(void);
static V S1135(void);
static V S1136(void);
static V S1137(void);
static V S1138(void);
static V S1139(void);
static V S1140(void);
static V S1141(void);
static V S1142(void);
static V S1143(void);
static V S1144(void);
static V S1145(void);
static V S1146(void);
static V S1147(void);
static V W_R_dopname(V *a);
static V F_R_dopname_dgo(V a0);
static V S1149(void);
static V S1150(void);
static V S1151(void);
static V S1152(void);
static V S1153(void);
static V S1154(void);
static V S1155(void);
static V S1156(void);
static V S1157(void);
static V S1158(void);
static V S1159(void);
static V S1160(void);
static V S1161(void);
static V S1162(void);
static V S1163(void);
static V W_R_dopname_dgo(V *a);
static V F_Gen_dstmt(V a0, V a1, V a2, V a3, V a4);
static V L1165(V *a);
static V W_Gen_dstmt(V *a);
static V F_Gen_dret(V a0, V a1);
static V S1167(void);
static V S1168(void);
static V S1169(void);
static V S1170(void);
static V W_Gen_dret(V *a);
static V F_Gen_dexpr(V a0, V a1, V a2);
static V S1172(void);
static V S1173(void);
static V S1174(void);
static V S1175(void);
static V L1176(V *a);
static V S1177(void);
static V S1178(void);
static V S1179(void);
static V S1180(void);
static V S1181(void);
static V L1182(V *a);
static V S1183(void);
static V S1184(void);
static V L1185(V *a);
static V S1186(void);
static V W_Gen_dexpr(V *a);
static V F_Gen_dblock(V a0, V a1, V a2);
static V L1187(V *a);
static V S1188(void);
static V L1189(V *a);
static V L1190(V *a);
static V S1191(void);
static V S1192(void);
static V S1193(void);
static V W_Gen_dblock(V *a);
static V F_Self_dnone(void);
static V S1194(void);
static V W_Self_dnone(V *a);
static V F_Gen_dlam(V a0, V a1, V a2, V a3);
static V L1197(V *a);
static V S1198(void);
static V L1199(V *a);
static V S1200(void);
static V S1201(void);
static V L1202(V *a);
static V S1203(void);
static V S1204(void);
static V L1205(V *a);
static V L1206(V *a);
static V S1207(void);
static V S1208(void);
static V S1209(void);
static V L1210(V *a);
static V S1211(void);
static V S1212(void);
static V S1213(void);
static V S1214(void);
static V S1215(void);
static V W_Gen_dlam(V *a);
static V F_Gen_dcaps_douter(V a0);
static V W_Gen_dcaps_douter(V *a);
static V F_Gen_darr(V a0);
static V S1218(void);
static V S1219(void);
static V S1220(void);
static V W_Gen_darr(V *a);
static V F_Gen_dcommas(V a0);
static V S1221(void);
static V W_Gen_dcommas(V *a);
static V F_Doc_dsep(V a0, V a1);
static V W_Doc_dsep(V *a);
static V F_Doc_dsep_dgo(V a0, V a1);
static V W_Doc_dsep_dgo(V *a);
static V F_Gen_dcaps_dinner(V a0, V a1);
static V S1225(void);
static V S1226(void);
static V W_Gen_dcaps_dinner(V *a);
static V F_Gen_dpat(V a0, V a1, V a2, V a3);
static V S1228(void);
static V S1229(void);
static V S1230(void);
static V S1231(void);
static V S1232(void);
static V S1233(void);
static V S1234(void);
static V S1235(void);
static V S1236(void);
static V W_Gen_dpat(V *a);
static V F_Gen_dpat_dcond(V a0, V a1);
static V W_Gen_dpat_dcond(V *a);
static V F_Gen_dpat_dctor(V a0, V a1, V a2, V a3, V a4, V a5);
static V S1239(void);
static V S1240(void);
static V W_Gen_dpat_dctor(V *a);
static V F_Gen_dpat_dkind(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V S1242(void);
static V S1243(void);
static V S1244(void);
static V S1245(void);
static V S1246(void);
static V S1247(void);
static V S1248(void);
static V S1249(void);
static V S1250(void);
static V S1251(void);
static V S1252(void);
static V W_Gen_dpat_dkind(V *a);
static V F_Gen_dpat_dfields(V a0, V a1, V a2, V a3, V a4);
static V S1254(void);
static V S1255(void);
static V S1256(void);
static V W_Gen_dpat_dfields(V *a);
static V F_Gen_dpat_dtag(V a0, V a1, V a2);
static V W_Gen_dpat_dtag(V *a);
static V F_Gen_dpat_dvar(V a0, V a1, V a2);
static V S1259(void);
static V W_Gen_dpat_dvar(V *a);
static V F_PatR_dbinds(V a0);
static V W_PatR_dbinds(V *a);
static V F_Pat_dvars(V a0, V a1);
static V W_Pat_dvars(V *a);
static V F_Pats_dvars(V a0, V a1);
static V W_Pats_dvars(V *a);
static V F_FV_dexpr(V a0, V a1, V a2);
static V W_FV_dexpr(V *a);
static V F_FV_dexprs(V a0, V a1, V a2);
static V W_FV_dexprs(V *a);
static V F_FV_dvar(V a0, V a1, V a2);
static V W_FV_dvar(V *a);
static V F_Str_dhas(V a0, V a1);
static V W_Str_dhas(V *a);
static V F_Gen_dcaps(V a0, V a1);
static V W_Gen_dcaps(V *a);
static V F_Gen_dcaps_dput(V a0, V a1, V a2);
static V W_Gen_dcaps_dput(V *a);
static V F_Gen_dctor(V a0, V a1, V a2, V a3);
static V W_Gen_dctor(V *a);
static V F_Gen_dctor_dinfo(V a0, V a1, V a2, V a3, V a4);
static V S1268(void);
static V L1269(V *a);
static V S1270(void);
static V L1271(V *a);
static V W_Gen_dctor_dinfo(V *a);
static V F_Gen_dctor_dkind(V a0, V a1, V a2);
static V S1273(void);
static V S1274(void);
static V S1275(void);
static V S1276(void);
static V S1277(void);
static V W_Gen_dctor_dkind(V *a);
static V F_Gen_dctor_dnode(V a0, V a1);
static V S1279(void);
static V S1280(void);
static V S1281(void);
static V S1282(void);
static V S1283(void);
static V S1284(void);
static V S1285(void);
static V S1286(void);
static V W_Gen_dctor_dnode(V *a);
static V F_Gen_dlen(V a0);
static V W_Gen_dlen(V *a);
static V F_Gen_dexprs(V a0, V a1, V a2);
static V L1288(V *a);
static V L1289(V *a);
static V W_Gen_dexprs(V *a);
static V F_Gen_dcall(V a0, V a1, V a2, V a3);
static V W_Gen_dcall(V *a);
static V F_Gen_dcall_dlocal(V a0, V a1, V a2, V a3);
static V L1291(V *a);
static V L1292(V *a);
static V W_Gen_dcall_dlocal(V *a);
static V F_Gen_dapply(V a0, V a1);
static V S1294(void);
static V S1295(void);
static V S1296(void);
static V W_Gen_dapply(V *a);
static V F_Env_dhas(V a0, V a1);
static V W_Env_dhas(V *a);
static V F_Maybe_dis__some(V a2);
static V W_Maybe_dis__some(V *a);
static V F_Gen_dcall_dvar(V a0, V a1, V a2, V a3, V a4);
static V W_Gen_dcall_dvar(V *a);
static V F_Gen_dcall_ddef(V a0, V a1, V a2, V a3, V a4);
static V W_Gen_dcall_ddef(V *a);
static V F_Gen_dsplit(V a0, V a1, V a2);
static V S1306(void);
static V W_Gen_dsplit(V *a);
static V F_Gen_dcall_dkind(V a0, V a1, V a2, V a3, V a4, V a5);
static V S1308(void);
static V S1309(void);
static V L1310(V *a);
static V S1311(void);
static V L1312(V *a);
static V W_Gen_dcall_dkind(V *a);
static V F_Gen_dcall_dsplit(V a0, V a1, V a2, V a3, V a4);
static V W_Gen_dcall_dsplit(V *a);
static V F_Gen_dcall_dfull(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7);
static V L1315(V *a);
static V L1316(V *a);
static V S1317(void);
static V S1318(void);
static V L1319(V *a);
static V S1320(void);
static V S1321(void);
static V S1322(void);
static V S1323(void);
static V S1324(void);
static V W_Gen_dcall_dfull(V *a);
static V F_Gen_dref(V a0);
static V L1325(V *a);
static V W_Gen_dref(V *a);
static V F_Gen_dref_dgo(V a0, V a1);
static V W_Gen_dref_dgo(V *a);
static V F_Gen_dstr(V a0);
static V L1327(V *a);
static V S1328(void);
static V L1329(V *a);
static V S1330(void);
static V S1331(void);
static V L1332(V *a);
static V S1333(void);
static V S1334(void);
static V S1335(void);
static V L1336(V *a);
static V S1337(void);
static V W_Gen_dstr(V *a);
static V F_Gen_dlit(V a0);
static V S1339(void);
static V W_Gen_dlit(V *a);
static V F_Gen_dlit__chr(V a0);
static V S1340(void);
static V S1341(void);
static V S1342(void);
static V W_Gen_dlit__chr(V *a);
static V F_Gen_dutf8(V a0);
static V W_Gen_dutf8(V *a);
static V W_U32_dor(V *a);
static V F_Gen_doct(V a0);
static V S1343(void);
static V W_Gen_doct(V *a);
static V W_U32_dis__lt(V *a);
static V F_Gen_dvar(V a0, V a1, V a2);
static V W_Gen_dvar(V *a);
static V F_Gen_dvar_dfound(V a0, V a1, V a2);
static V S1345(void);
static V W_Gen_dvar_dfound(V *a);
static V F_Gen_dvar_dglobal(V a0, V a1, V a2);
static V S1347(void);
static V W_Gen_dvar_dglobal(V *a);
static V F_Gen_dvar_ddef(V a0, V a1);
static V W_Gen_dvar_ddef(V *a);
static V F_Gen_dvar_dkind(V a0, V a1, V a2);
static V S1350(void);
static V S1351(void);
static V L1352(V *a);
static V S1353(void);
static V L1354(V *a);
static V S1355(void);
static V S1356(void);
static V S1357(void);
static V S1358(void);
static V W_Gen_dvar_dkind(V *a);
static V F_Gen_dis__tail(V a0, V a1, V a2, V a3, V a4);
static V W_Gen_dis__tail(V *a);
static V W_Nat_dis__eq(V *a);
static V F_Gen_dis__ret(V a0);
static V W_Gen_dis__ret(V *a);
static V F_Gen_dstmt_dcall(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V L1362(V *a);
static V W_Gen_dstmt_dcall(V *a);
static V F_Gen_dtail_dself(V a0, V a1, V a2, V a3);
static V W_Gen_dtail_dself(V *a);
static V F_Gen_dtail(V a0, V a1, V a2, V a3);
static V L1365(V *a);
static V S1366(void);
static V S1367(void);
static V W_Gen_dtail(V *a);
static V F_Gen_dtail_dassign(V a0, V a1);
static V S1369(void);
static V S1370(void);
static V W_Gen_dtail_dassign(V *a);
static V F_Gen_dtail_dtemps(V a0, V a1);
static V S1372(void);
static V S1373(void);
static V S1374(void);
static V W_Gen_dtail_dtemps(V *a);
static V F_Gen_dmatch(V a0, V a1, V a2, V a3, V a4, V a5);
static V L1375(V *a);
static V W_Gen_dmatch(V *a);
static V F_Gen_dmatch_dgo(V a0, V a1, V a2, V a3, V a4, V a5);
static V L1377(V *a);
static V W_Gen_dmatch_dgo(V *a);
static V F_Gen_dcases(V a0, V a1, V a2, V a3, V a4, V a5);
static V S1379(void);
static V L1383(V *a);
static V W_Gen_dcases(V *a);
static V F_Gen_dcases_dnext(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7);
static V S1385(void);
static V S1386(void);
static V L1387(V *a);
static V S1388(void);
static V S1389(void);
static V S1390(void);
static V W_Gen_dcases_dnext(V *a);
static V F_Gen_dand(V a0);
static V S1392(void);
static V S1393(void);
static V W_Gen_dand(V *a);
static V F_PatR_dconds(V a0);
static V W_PatR_dconds(V *a);
static V F_Gen_dpats(V a0, V a1, V a2, V a3);
static V W_Gen_dpats(V *a);
static V F_Gen_dscrs(V a0, V a1, V a2);
static V L1398(V *a);
static V S1399(void);
static V L1400(V *a);
static V L1401(V *a);
static V L1402(V *a);
static V W_Gen_dscrs(V *a);
static V F_Gen_dscrs_dput(V a0, V a1, V a2);
static V S1404(void);
static V S1405(void);
static V S1406(void);
static V W_Gen_dscrs_dput(V *a);
static V F_Gen_dlet(V a0, V a1, V a2, V a3, V a4, V a5, V a6);
static V S1408(void);
static V L1409(V *a);
static V S1410(void);
static V L1411(V *a);
static V L1412(V *a);
static V L1413(V *a);
static V L1414(V *a);
static V S1415(void);
static V S1416(void);
static V S1417(void);
static V W_Gen_dlet(V *a);
static V F_Gen_dlet_dvar(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7);
static V L1419(V *a);
static V L1420(V *a);
static V S1421(void);
static V S1422(void);
static V L1423(V *a);
static V S1424(void);
static V L1425(V *a);
static V L1426(V *a);
static V L1427(V *a);
static V S1428(void);
static V S1429(void);
static V S1430(void);
static V W_Gen_dlet_dvar(V *a);
static V F_Gen_dprogram_dfin(V a0);
static V S1433(void);
static V S1434(void);
static V S1435(void);
static V W_Gen_dprogram_dfin(V *a);
static V F_Doc_dflat(V a0);
static V W_Doc_dflat(V *a);
static V F_Doc_dgo(V a0, V a1);
static V W_Doc_dgo(V *a);
static V F_G_dnew(V a0);
static V W_G_dnew(V *a);
static V F_G_dlaws(V a0, V a1);
static V W_G_dlaws(V *a);
static V F_G_dbuild(V a0, V a1, V a2);
static V W_G_dbuild(V *a);
static V F_G_dadd(V a0, V a1, V a2);
static V W_G_dadd(V *a);
static V F_G_dadd_deff(V a0, V a1, V a2);
static V W_G_dadd_deff(V *a);
static V F_G_dmask(V a0);
static V W_G_dmask(V *a);
static V F_G_dkeep(V a0);
static V W_G_dkeep(V *a);
static V F_G_derased__ty(V a0);
static V S1443(void);
static V S1444(void);
static V S1445(void);
static V S1446(void);
static V W_G_derased__ty(V *a);
static V F_G_dadd_ddef(V a0, V a1, V a2, V a3, V a4, V a5);
static V W_G_dadd_ddef(V *a);
static V F_G_dparams(V a0, V a1, V a2);
static V W_G_dparams(V *a);
static V F_G_dparams_dgo(V a0, V a1);
static V W_G_dparams_dgo(V *a);
static V F_G_dis__native(V a0);
static V W_G_dis__native(V *a);
static V F_Natives(void);
static V S1449(void);
static V S1450(void);
static V S1451(void);
static V S1452(void);
static V S1453(void);
static V S1454(void);
static V S1455(void);
static V S1456(void);
static V S1457(void);
static V S1458(void);
static V S1459(void);
static V S1460(void);
static V S1461(void);
static V S1462(void);
static V S1463(void);
static V S1464(void);
static V S1465(void);
static V S1466(void);
static V S1467(void);
static V S1468(void);
static V S1469(void);
static V S1470(void);
static V S1471(void);
static V S1472(void);
static V S1473(void);
static V S1474(void);
static V S1475(void);
static V S1476(void);
static V S1477(void);
static V S1478(void);
static V S1479(void);
static V S1480(void);
static V S1481(void);
static V S1482(void);
static V S1483(void);
static V S1484(void);
static V S1485(void);
static V S1486(void);
static V S1487(void);
static V S1488(void);
static V S1489(void);
static V S1490(void);
static V S1491(void);
static V S1492(void);
static V S1493(void);
static V S1494(void);
static V S1495(void);
static V S1496(void);
static V S1497(void);
static V S1498(void);
static V S1499(void);
static V S1500(void);
static V S1501(void);
static V S1502(void);
static V S1503(void);
static V S1504(void);
static V S1505(void);
static V S1506(void);
static V S1507(void);
static V S1508(void);
static V S1509(void);
static V S1510(void);
static V S1511(void);
static V S1512(void);
static V S1513(void);
static V S1514(void);
static V S1515(void);
static V S1516(void);
static V S1517(void);
static V S1518(void);
static V S1519(void);
static V S1520(void);
static V S1521(void);
static V S1522(void);
static V S1523(void);
static V S1524(void);
static V S1525(void);
static V S1526(void);
static V S1527(void);
static V S1528(void);
static V S1529(void);
static V S1530(void);
static V S1531(void);
static V W_Natives(V *a);
static V F_G_dadd_dlaw(V a0, V a1, V a2);
static V W_G_dadd_dlaw(V *a);
static V F_G_dadd_dtype(V a0, V a1, V a2, V a3);
static V S1535(void);
static V W_G_dadd_dtype(V *a);
static V F_G_dctors(V a0, V a1, V a2, V a3, V a4);
static V W_G_dctors(V *a);
static V F_G_dctor__kind(V a0, V a1, V a2, V a3);
static V S1538(void);
static V S1539(void);
static V W_G_dctor__kind(V *a);
static V F_Main_demit(V a0);
static V S1542(void);
static V L1543(V *a);
static V S1544(void);
static V W_Main_demit(V *a);
static V F_IO_dprint__err(V a0);
static V E_IO_dprint__err(V *a);
static V W_IO_dprint__err(V *a);
static V F_IO_dbind(V a2, V a3);
static V L1545(V *a);
static V L1546(V *a);
static V L1547(V *a);
static V W_IO_dbind(V *a);
static V F_IO_dwrite(V a0);
static V E_IO_dwrite(V *a);
static V W_IO_dwrite(V *a);
static V F_Main_dload(V a0, V a1);
static V S1549(void);
static V L1550(V *a);
static V W_Main_dload(V *a);
static V F_Mod_ddir(V a0);
static V W_Mod_ddir(V *a);
static V F_Mod_ddir_dgo(V a0);
static V W_Mod_ddir_dgo(V *a);
static V F_Mod_ddir_dif(V a0, V a1, V a2);
static V W_Mod_ddir_dif(V *a);
static V F_Main_dload_dparsed(V a0, V a1, V a2, V a3);
static V S1554(void);
static V S1555(void);
static V L1556(V *a);
static V W_Main_dload_dparsed(V *a);
static V F_IO_dpure(V a1);
static V L1557(V *a);
static V L1558(V *a);
static V W_IO_dpure(V *a);
static V F_Main_dimports(V a0, V a1, V a2);
static V S1560(void);
static V W_Main_dimports(V *a);
static V F_Main_dimports_done(V a0, V a1, V a2, V a3, V a4, V a5);
static V L1562(V *a);
static V L1563(V *a);
static V W_Main_dimports_done(V *a);
static V F_Mod_dqualify(V a0, V a1);
static V W_Mod_dqualify(V *a);
static V F_Mod_dnames(V a0, V a1);
static V W_Mod_dnames(V *a);
static V F_Mod_dctor__names(V a0, V a1);
static V W_Mod_dctor__names(V *a);
static V F_Mod_ddecls(V a0, V a1);
static V W_Mod_ddecls(V *a);
static V F_Mod_ddecl(V a0, V a1);
static V W_Mod_ddecl(V *a);
static V F_Mod_dctors(V a0, V a1);
static V W_Mod_dctors(V *a);
static V F_Mod_dfields(V a0, V a1);
static V W_Mod_dfields(V *a);
static V F_Mod_dexpr(V a0, V a1, V a2);
static V W_Mod_dexpr(V *a);
static V F_Mod_dexprs(V a0, V a1, V a2);
static V W_Mod_dexprs(V *a);
static V F_Mod_dvar(V a0, V a1, V a2);
static V W_Mod_dvar(V *a);
static V F_Mod_dq(V a0, V a1);
static V S1573(void);
static V W_Mod_dq(V *a);
static V F_Mod_dpats(V a0, V a1);
static V W_Mod_dpats(V *a);
static V F_Mod_dpat(V a0, V a1);
static V W_Mod_dpat(V *a);
static V F_Mod_dparam__names(V a0);
static V W_Mod_dparam__names(V *a);
static V F_IO_dread__file(V a0);
static V S1577(void);
static V L1578(V *a);
static V L1579(V *a);
static V W_IO_dread__file(V *a);
static V F_IO_dread__fin(V a0);
static V L1581(V *a);
static V W_IO_dread__fin(V *a);
static V F_IO_dpass(V a1);
static V W_IO_dpass(V *a);
static V F_File_dclose(V a0);
static V E_File_dclose(V *a);
static V W_File_dclose(V *a);
static V F_File_dread(V a0, V a1);
static V E_File_dread(V *a);
static V W_File_dread(V *a);
static V F_File_dopen(V a0, V a1);
static V E_File_dopen(V *a);
static V W_File_dopen(V *a);
static V F_IO_dtry(V a1);
static V W_IO_dtry(V *a);
static V F_Main_dast(V a0);
static V S1584(void);
static V W_Main_dast(V *a);
static V F_Decls_dshow(V a0);
static V W_Decls_dshow(V *a);
static V F_Decls_dshow_dgo(V a0);
static V S1586(void);
static V S1587(void);
static V W_Decls_dshow_dgo(V *a);
static V F_Decl_dshow(V a0);
static V S1589(void);
static V S1590(void);
static V S1591(void);
static V S1592(void);
static V S1593(void);
static V S1594(void);
static V S1595(void);
static V S1596(void);
static V S1597(void);
static V S1598(void);
static V S1599(void);
static V S1600(void);
static V S1601(void);
static V W_Decl_dshow(V *a);
static V F_Ctors_dshow(V a0);
static V S1603(void);
static V S1604(void);
static V W_Ctors_dshow(V *a);
static V F_Ctor_dshow(V a0);
static V S1606(void);
static V S1607(void);
static V W_Ctor_dshow(V *a);
static V F_Fields_dshow(V a0);
static V S1609(void);
static V S1610(void);
static V S1611(void);
static V W_Fields_dshow(V *a);
static V F_Params_dshow(V a0);
static V S1613(void);
static V S1614(void);
static V W_Params_dshow(V *a);
static V F_Param_dshow(V a0);
static V S1616(void);
static V W_Param_dshow(V *a);
static V F_Toks_dshow(V a0);
static V S1618(void);
static V W_Toks_dshow(V *a);
static V F_Tok_dshow(V a0);
static V S1620(void);
static V S1621(void);
static V W_Tok_dshow(V *a);
static V F_IO_dprint(V a0);
static V E_IO_dprint(V *a);
static V W_IO_dprint(V *a);
static V F_IO_dargs(void);
static V E_IO_dargs(V *a);
static V W_IO_dargs(V *a);

static V L0(V *a) {
return F_Main_drun(F_IO_dlist2(a[0]));
}
static V F_main(void) {
top:;
return F_IO_dbind(F_IO_dargs(), mk_clo(L0, 1, 0, 0));
}
static V W_main(V *a) { (void)a; return F_main(); }
static V F_IO_dlist2(V a0) {
top:;
V s1 = a0;
if ((s1) == IMM(0)) {
return IMM(0);
} else if (TAG(s1) == 1) {
return C2(1, FLD(s1, 0), F_IO_dlist2(FLD(s1, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_IO_dlist2(V *a) { (void)a; return F_IO_dlist2(a[0]); }
static V L3(V *a) {
return F_IO_dprint(F_Toks_dshow(F_Lex_dall(a[0])));
}
static V L4(V *a) {
return F_Main_dast(F_Main_dparse(a[0]));
}
static V L6(V *a) {
return F_Main_dcompile(F_Main_dparse(a[0]), C1(1, a[1]));
}
static V L5(V *a) {
return F_IO_dbind(F_Main_dload(64u, a[0]), mk_clo(L6, 2, 1, (V[]){a[1]}));
}
static V S7(void) { static V c; if (!c) c = MKS("usage: bendc <base.bend> <input.bend> | --tokens <file> | --ast <file>"); return c; }
static V F_Main_drun(V a0) {
top:;
V s2 = a0;
if (TAG(s2) == 1 && TAG(FLD(s2, 0)) == 1 && (FLD(FLD(s2, 0), 0)) == 45 && TAG(FLD(FLD(s2, 0), 1)) == 1 && (FLD(FLD(FLD(s2, 0), 1), 0)) == 45 && TAG(FLD(FLD(FLD(s2, 0), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(s2, 0), 1), 1), 0)) == 116 && TAG(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 0)) == 111 && TAG(FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 1), 0)) == 107 && TAG(FLD(FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 1), 1), 0)) == 101 && TAG(FLD(FLD(FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 1), 1), 1), 0)) == 110 && TAG(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 1), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 1), 1), 1), 1), 0)) == 115 && (FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 1), 1), 1), 1), 1)) == IMM(0) && TAG(FLD(s2, 1)) == 1 && (FLD(FLD(s2, 1), 1)) == IMM(0)) {
return F_IO_dbind(F_IO_dread__file(FLD(FLD(s2, 1), 0)), mk_clo(L3, 1, 0, 0));
} else if (TAG(s2) == 1 && TAG(FLD(s2, 0)) == 1 && (FLD(FLD(s2, 0), 0)) == 45 && TAG(FLD(FLD(s2, 0), 1)) == 1 && (FLD(FLD(FLD(s2, 0), 1), 0)) == 45 && TAG(FLD(FLD(FLD(s2, 0), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(s2, 0), 1), 1), 0)) == 97 && TAG(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 0)) == 115 && TAG(FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 1)) == 1 && (FLD(FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 1), 0)) == 116 && (FLD(FLD(FLD(FLD(FLD(FLD(s2, 0), 1), 1), 1), 1), 1)) == IMM(0) && TAG(FLD(s2, 1)) == 1 && (FLD(FLD(s2, 1), 1)) == IMM(0)) {
return F_IO_dbind(F_IO_dread__file(FLD(FLD(s2, 1), 0)), mk_clo(L4, 1, 0, 0));
} else if (TAG(s2) == 1 && TAG(FLD(s2, 1)) == 1 && (FLD(FLD(s2, 1), 1)) == IMM(0)) {
return F_IO_dbind(F_IO_dread__file(FLD(s2, 0)), mk_clo(L5, 2, 1, (V[]){FLD(FLD(s2, 1), 0)}));
} else {
return F_IO_ddie(1u, S7());
}
}
static V W_Main_drun(V *a) { (void)a; return F_Main_drun(a[0]); }
static V L9(V *a) {
return C2(1, a[1], a[0]);
}
static V L8(V *a) {
return mk_clo(L9, 3, 2, (V[]){a[0], a[1]});
}
static V F_IO_ddie(V a1, V a2) {
top:;
return mk_clo(L8, 3, 2, (V[]){a2, a1});
}
static V W_IO_ddie(V *a) { (void)a; return F_IO_ddie(a[1], a[2]); }
static V F_Main_dparse(V a0) {
top:;
return F_Main_dparse_dfin(F_P_dfile(a0));
}
static V W_Main_dparse(V *a) { (void)a; return F_Main_dparse(a[0]); }
static V F_P_dfile(V a0) {
top:;
return F_P_dfile_dfin(apply(F_P_ddecls(), F_Lex_dall(a0)));
}
static V W_P_dfile(V *a) { (void)a; return F_P_dfile(a[0]); }
static V F_Lex_dall(V a0) {
top:;
return F_Lay_dfinish(F_Lay_dlines(F_Lex_dlines(a0), CN(0, 5, (V[]){IMM(0), 0u, IMM(0), C2(1, 0u, IMM(0)), IMM(0)})));
}
static V W_Lex_dall(V *a) { (void)a; return F_Lex_dall(a[0]); }
static V F_Lex_dlines(V a0) {
top:;
return F_Lex_dlines_dgo(F_String_dlines(a0), 1u);
}
static V W_Lex_dlines(V *a) { (void)a; return F_Lex_dlines(a[0]); }
static V F_String_dlines(V a0) {
top:;
return F_String_dsplit(a0, 10u);
}
static V W_String_dlines(V *a) { (void)a; return F_String_dlines(a[0]); }
static V F_String_dsplit(V a0, V a1) {
top:;
V s10 = a0;
if ((s10) == IMM(0)) {
return C2(1, IMM(0), IMM(0));
} else if (TAG(s10) == 1) {
return F_String_dsplit_dfin(FLD(s10, 0), F_String_dsplit(FLD(s10, 1), a1), F_Char_dis__eq(FLD(s10, 0), a1));
} else { bend_fail("incomplete match"); }
}
static V W_String_dsplit(V *a) { (void)a; return F_String_dsplit(a[0], a[1]); }
static V F_Char_dis__eq(V a0, V a1) {
top:;
V s11 = a0;
V s12 = a1;
{
return F_U32_dis__eq(s11, s12);
}
}
static V W_Char_dis__eq(V *a) { (void)a; return F_Char_dis__eq(a[0], a[1]); }
static V W_U32_dis__eq(V *a) { (void)a; return F_U32_dis__eq(a[0], a[1]); }
static V F_String_dsplit_dfin(V a0, V a1, V a2) {
top:;
V s13 = a2;
if ((s13) == IMM(0)) {
return F_String_dsplit_dpush(a0, a1);
} else if ((s13) == IMM(1)) {
return C2(1, IMM(0), a1);
} else { bend_fail("incomplete match"); }
}
static V W_String_dsplit_dfin(V *a) { (void)a; return F_String_dsplit_dfin(a[0], a[1], a[2]); }
static V F_String_dsplit_dpush(V a0, V a1) {
top:;
V s14 = a1;
if ((s14) == IMM(0)) {
return C2(1, C2(1, a0, IMM(0)), IMM(0));
} else if (TAG(s14) == 1) {
return C2(1, C2(1, a0, FLD(s14, 0)), FLD(s14, 1));
} else { bend_fail("incomplete match"); }
}
static V W_String_dsplit_dpush(V *a) { (void)a; return F_String_dsplit_dpush(a[0], a[1]); }
static V F_Lex_dlines_dgo(V a0, V a1) {
top:;
V s15 = a0;
if ((s15) == IMM(0)) {
return IMM(0);
} else if (TAG(s15) == 1) {
return F_Lex_dlines_dput(C3(0, F_Lex_dindent(FLD(s15, 0)), a1, F_List_dreverse(F_Lex_dline(FLD(s15, 0), IMM(1), a1, IMM(0)))), F_Lex_dlines_dgo(FLD(s15, 1), F_U32_dinc(a1)));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dlines_dgo(V *a) { (void)a; return F_Lex_dlines_dgo(a[0], a[1]); }
static V W_U32_dinc(V *a) { (void)a; return F_U32_dinc(a[0]); }
static V F_Lex_dline(V a0, V a1, V a2, V a3) {
top:;
V s16 = a0;
if ((s16) == IMM(0)) {
return a3;
} else if (TAG(s16) == 1) {
return F_Lex_dline_dgo(FLD(s16, 0), FLD(s16, 1), a1, a2, a3, F_Lex_dclass(FLD(s16, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dline(V *a) { (void)a; return F_Lex_dline(a[0], a[1], a[2], a[3]); }
static V F_Lex_dclass(V a0) {
top:;
return F_Bool_dpick(F_Bool_dor(F_U32_dis__eq(a0, 32u), F_U32_dis__eq(a0, 9u)), 0u, F_Bool_dpick(F_U32_dis__eq(a0, 35u), 1u, F_Bool_dpick(F_Lex_dis__ids(a0), 2u, F_Bool_dpick(F_Char_dis__digit(a0), 3u, F_Bool_dpick(F_U32_dis__eq(a0, 39u), 4u, F_Bool_dpick(F_U32_dis__eq(a0, 34u), 5u, F_Bool_dpick(F_U32_dis__eq(a0, 13u), 0u, 6u)))))));
}
static V W_Lex_dclass(V *a) { (void)a; return F_Lex_dclass(a[0]); }
static V F_Bool_dpick(V a1, V a2, V a3) {
top:;
V s17 = a1;
if ((s17) == IMM(0)) {
return a3;
} else if ((s17) == IMM(1)) {
return a2;
} else { bend_fail("incomplete match"); }
}
static V W_Bool_dpick(V *a) { (void)a; return F_Bool_dpick(a[1], a[2], a[3]); }
static V F_Char_dis__digit(V a0) {
top:;
V s18 = a0;
{
return F_Bool_dand(F_U32_dis__ge(s18, 48u), F_U32_dis__le(s18, 57u));
}
}
static V W_Char_dis__digit(V *a) { (void)a; return F_Char_dis__digit(a[0]); }
static V W_U32_dis__le(V *a) { (void)a; return F_U32_dis__le(a[0], a[1]); }
static V W_U32_dis__ge(V *a) { (void)a; return F_U32_dis__ge(a[0], a[1]); }
static V F_Bool_dand(V a0, V a1) {
top:;
V s19 = a0;
if ((s19) == IMM(0)) {
return IMM(0);
} else if ((s19) == IMM(1)) {
return a1;
} else { bend_fail("incomplete match"); }
}
static V W_Bool_dand(V *a) { (void)a; return F_Bool_dand(a[0], a[1]); }
static V F_Lex_dis__ids(V a0) {
top:;
return F_Bool_dor(F_Char_dis__alpha(a0), F_U32_dis__eq(F_Char_dto__u32(a0), 95u));
}
static V W_Lex_dis__ids(V *a) { (void)a; return F_Lex_dis__ids(a[0]); }
static V F_Char_dto__u32(V a0) {
top:;
V s20 = a0;
{
return s20;
}
}
static V W_Char_dto__u32(V *a) { (void)a; return F_Char_dto__u32(a[0]); }
static V F_Char_dis__alpha(V a0) {
top:;
return F_Bool_dor(F_Char_dis__upper(a0), F_Char_dis__lower(a0));
}
static V W_Char_dis__alpha(V *a) { (void)a; return F_Char_dis__alpha(a[0]); }
static V F_Char_dis__lower(V a0) {
top:;
V s21 = a0;
{
return F_Bool_dand(F_U32_dis__ge(s21, 97u), F_U32_dis__le(s21, 122u));
}
}
static V W_Char_dis__lower(V *a) { (void)a; return F_Char_dis__lower(a[0]); }
static V F_Char_dis__upper(V a0) {
top:;
V s22 = a0;
{
return F_Bool_dand(F_U32_dis__ge(s22, 65u), F_U32_dis__le(s22, 90u));
}
}
static V W_Char_dis__upper(V *a) { (void)a; return F_Char_dis__upper(a[0]); }
static V F_Bool_dor(V a0, V a1) {
top:;
V s23 = a0;
if ((s23) == IMM(0)) {
return a1;
} else if ((s23) == IMM(1)) {
return IMM(1);
} else { bend_fail("incomplete match"); }
}
static V W_Bool_dor(V *a) { (void)a; return F_Bool_dor(a[0], a[1]); }
static V F_Lex_dline_dgo(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V s24 = a5;
if ((s24) == 0) {
return F_Lex_dline(a1, IMM(1), a3, a4);
} else if ((s24) == 1) {
return a4;
} else if ((s24) == 2) {
return F_Lex_dline_did(a2, a3, a4, F_Lex_did(C2(1, a0, a1), IMM(0)));
} else if ((s24) == 3) {
return F_Lex_dline_dnum(a2, a3, a4, F_Lex_ddigits(C2(1, a0, a1), 0u));
} else if ((s24) == 4) {
return F_Lex_dline_dchr(a2, a3, a4, F_Lex_dlit__char(a1));
} else if ((s24) == 5) {
return F_Lex_dline_dstr(a2, a3, a4, F_Lex_dstr(a1, IMM(0)));
} else if ((s24) >= 6) {
V v25 = C2(1, a0, a1);
return F_Lex_dline_dop(v25, a2, a3, a4, F_Lex_dop__of(v25));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dline_dgo(V *a) { (void)a; return F_Lex_dline_dgo(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V F_Lex_dop__of(V a0) {
top:;
return F_Lex_dop__of_dgo(F_Lex_dfind__op(F_Lex_dops3(), a0), a0);
}
static V W_Lex_dop__of(V *a) { (void)a; return F_Lex_dop__of(a[0]); }
static V S26(void) { static V c; if (!c) c = MKS(".&."); return c; }
static V S27(void) { static V c; if (!c) c = MKS(".|."); return c; }
static V S28(void) { static V c; if (!c) c = MKS(".^."); return c; }
static V S29(void) { static V c; if (!c) c = MKS("<&>"); return c; }
static V F_Lex_dops3(void) {
top:;
return C2(1, S26(), C2(1, S27(), C2(1, S28(), C2(1, S29(), IMM(0)))));
}
static V W_Lex_dops3(V *a) { (void)a; return F_Lex_dops3(); }
static V F_Lex_dfind__op(V a0, V a1) {
top:;
V s30 = a0;
if ((s30) == IMM(0)) {
return IMM(0);
} else if (TAG(s30) == 1) {
return F_Lex_dfind__op_dif(FLD(s30, 0), FLD(s30, 1), a1, F_String_dstarts__with(a1, FLD(s30, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dfind__op(V *a) { (void)a; return F_Lex_dfind__op(a[0], a[1]); }
static V F_String_dstarts__with(V a0, V a1) {
top:;
V s31 = a0;
V s32 = a1;
if ((s31) == IMM(0) && (s32) == IMM(0)) {
return IMM(1);
} else if ((s31) == IMM(0) && TAG(s32) == 1) {
return IMM(0);
} else if (TAG(s31) == 1 && (s32) == IMM(0)) {
return IMM(1);
} else if (TAG(s31) == 1 && TAG(s32) == 1) {
return F_String_dstarts__with_dif(FLD(s31, 1), FLD(s32, 1), F_Char_dis__eq(FLD(s31, 0), FLD(s32, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_String_dstarts__with(V *a) { (void)a; return F_String_dstarts__with(a[0], a[1]); }
static V F_String_dstarts__with_dif(V a0, V a1, V a2) {
top:;
V s33 = a2;
if ((s33) == IMM(0)) {
return IMM(0);
} else if ((s33) == IMM(1)) {
return F_String_dstarts__with(a0, a1);
} else { bend_fail("incomplete match"); }
}
static V W_String_dstarts__with_dif(V *a) { (void)a; return F_String_dstarts__with_dif(a[0], a[1], a[2]); }
static V F_Lex_dfind__op_dif(V a0, V a1, V a2, V a3) {
top:;
V s34 = a3;
if ((s34) == IMM(1)) {
return C1(1, a0);
} else if ((s34) == IMM(0)) {
return F_Lex_dfind__op(a1, a2);
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dfind__op_dif(V *a) { (void)a; return F_Lex_dfind__op_dif(a[0], a[1], a[2], a[3]); }
static V F_Lex_dop__of_dgo(V a0, V a1) {
top:;
V s35 = a0;
if (TAG(s35) == 1) {
return FLD(s35, 0);
} else if ((s35) == IMM(0)) {
return F_Lex_dop__of_dtwo(F_Lex_dfind__op(F_Lex_dops2(), a1), a1);
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dop__of_dgo(V *a) { (void)a; return F_Lex_dop__of_dgo(a[0], a[1]); }
static V S36(void) { static V c; if (!c) c = MKS("=>"); return c; }
static V S37(void) { static V c; if (!c) c = MKS("->"); return c; }
static V S38(void) { static V c; if (!c) c = MKS("<-"); return c; }
static V S39(void) { static V c; if (!c) c = MKS("<>"); return c; }
static V S40(void) { static V c; if (!c) c = MKS("<="); return c; }
static V S41(void) { static V c; if (!c) c = MKS(">="); return c; }
static V S42(void) { static V c; if (!c) c = MKS("=="); return c; }
static V S43(void) { static V c; if (!c) c = MKS("!="); return c; }
static V S44(void) { static V c; if (!c) c = MKS("++"); return c; }
static V S45(void) { static V c; if (!c) c = MKS("&&"); return c; }
static V S46(void) { static V c; if (!c) c = MKS("||"); return c; }
static V S47(void) { static V c; if (!c) c = MKS(">>"); return c; }
static V S48(void) { static V c; if (!c) c = MKS("<<"); return c; }
static V F_Lex_dops2(void) {
top:;
return C2(1, S36(), C2(1, S37(), C2(1, S38(), C2(1, S39(), C2(1, S40(), C2(1, S41(), C2(1, S42(), C2(1, S43(), C2(1, S44(), C2(1, S45(), C2(1, S46(), C2(1, S47(), C2(1, S48(), IMM(0))))))))))))));
}
static V W_Lex_dops2(V *a) { (void)a; return F_Lex_dops2(); }
static V F_Lex_dop__of_dtwo(V a0, V a1) {
top:;
V s49 = a0;
if (TAG(s49) == 1) {
return FLD(s49, 0);
} else if ((s49) == IMM(0)) {
return F_String_dtake(a1, 1u);
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dop__of_dtwo(V *a) { (void)a; return F_Lex_dop__of_dtwo(a[0], a[1]); }
static V F_String_dtake(V a0, V a1) {
top:;
V s50 = a0;
V s51 = a1;
if ((s50) == IMM(0)) {
return IMM(0);
} else if (TAG(s50) == 1 && (s51) == 0) {
return IMM(0);
} else if (TAG(s50) == 1 && (s51) >= 1) {
return C2(1, FLD(s50, 0), F_String_dtake(FLD(s50, 1), (s51 - 1)));
} else { bend_fail("incomplete match"); }
}
static V W_String_dtake(V *a) { (void)a; return F_String_dtake(a[0], a[1]); }
static V F_Lex_dline_dop(V a0, V a1, V a2, V a3, V a4) {
top:;
return F_Lex_dline(F_String_ddrop(a0, F_String_dlength(a4)), IMM(0), a2, C2(1, C3(0, C1(7, a4), a1, a2), a3));
}
static V W_Lex_dline_dop(V *a) { (void)a; return F_Lex_dline_dop(a[0], a[1], a[2], a[3], a[4]); }
static V F_String_dlength(V a0) {
top:;
V s52 = a0;
if ((s52) == IMM(0)) {
return 0u;
} else if (TAG(s52) == 1) {
return (F_String_dlength(FLD(s52, 1)) + 1);
} else { bend_fail("incomplete match"); }
}
static V W_String_dlength(V *a) { (void)a; return F_String_dlength(a[0]); }
static V F_String_ddrop(V a0, V a1) {
top:;
V s53 = a0;
V s54 = a1;
if ((s53) == IMM(0)) {
return IMM(0);
} else if (TAG(s53) == 1 && (s54) == 0) {
return C2(1, FLD(s53, 0), FLD(s53, 1));
} else if (TAG(s53) == 1 && (s54) >= 1) {
{ V t0 = FLD(s53, 1); V t1 = (s54 - 1); a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_String_ddrop(V *a) { (void)a; return F_String_ddrop(a[0], a[1]); }
static V F_Lex_dstr(V a0, V a1) {
top:;
V s55 = a0;
if ((s55) == IMM(0)) {
return C2(0, F_Str_drev(a1), IMM(0));
} else if (TAG(s55) == 1) {
return F_Lex_dstr_dif(FLD(s55, 0), FLD(s55, 1), a1, F_U32_dis__eq(FLD(s55, 0), 34u));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dstr(V *a) { (void)a; return F_Lex_dstr(a[0], a[1]); }
static V F_Lex_dstr_dif(V a0, V a1, V a2, V a3) {
top:;
V s56 = a3;
if ((s56) == IMM(1)) {
return C2(0, F_Str_drev(a2), a1);
} else if ((s56) == IMM(0)) {
return F_Lex_dstr_dnext(a2, F_Lex_dlit__char(C2(1, a0, a1)));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dstr_dif(V *a) { (void)a; return F_Lex_dstr_dif(a[0], a[1], a[2], a[3]); }
static V F_Lex_dlit__char(V a0) {
top:;
V s57 = a0;
if ((s57) == IMM(0)) {
return C2(0, 0u, IMM(0));
} else if (TAG(s57) == 1) {
return F_Lex_dlit__char_dif(FLD(s57, 0), FLD(s57, 1), F_U32_dis__eq(FLD(s57, 0), 92u));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dlit__char(V *a) { (void)a; return F_Lex_dlit__char(a[0]); }
static V F_Lex_dlit__char_dif(V a0, V a1, V a2) {
top:;
V s58 = a2;
if ((s58) == IMM(0)) {
return C2(0, a0, a1);
} else if ((s58) == IMM(1)) {
return F_Lex_dlit__char_desc(a1);
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dlit__char_dif(V *a) { (void)a; return F_Lex_dlit__char_dif(a[0], a[1], a[2]); }
static V F_Lex_dlit__char_desc(V a0) {
top:;
V s59 = a0;
if ((s59) == IMM(0)) {
return C2(0, 92u, IMM(0));
} else if (TAG(s59) == 1) {
return C2(0, F_Lex_desc(FLD(s59, 0)), FLD(s59, 1));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dlit__char_desc(V *a) { (void)a; return F_Lex_dlit__char_desc(a[0]); }
static V F_Lex_desc(V a0) {
top:;
V v60 = a0;
return F_Bool_dpick(F_U32_dis__eq(v60, 110u), 10u, F_Bool_dpick(F_U32_dis__eq(v60, 116u), 9u, F_Bool_dpick(F_U32_dis__eq(v60, 114u), 13u, F_Bool_dpick(F_U32_dis__eq(v60, 48u), 0u, v60))));
}
static V W_Lex_desc(V *a) { (void)a; return F_Lex_desc(a[0]); }
static V F_Lex_dstr_dnext(V a0, V a1) {
top:;
V v61 = a1;
return F_Lex_dstr(FLD(v61, 1), C2(1, FLD(v61, 0), a0));
}
static V W_Lex_dstr_dnext(V *a) { (void)a; return F_Lex_dstr_dnext(a[0], a[1]); }
static V F_Str_drev(V a0) {
top:;
return F_String_dreverse(a0);
}
static V W_Str_drev(V *a) { (void)a; return F_Str_drev(a[0]); }
static V F_String_dreverse(V a0) {
top:;
return F_String_dreverse_dgo(a0, IMM(0));
}
static V W_String_dreverse(V *a) { (void)a; return F_String_dreverse(a[0]); }
static V F_String_dreverse_dgo(V a0, V a1) {
top:;
V s62 = a0;
if ((s62) == IMM(0)) {
return a1;
} else if (TAG(s62) == 1) {
{ V t0 = FLD(s62, 1); V t1 = C2(1, FLD(s62, 0), a1); a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_String_dreverse_dgo(V *a) { (void)a; return F_String_dreverse_dgo(a[0], a[1]); }
static V F_Lex_dline_dstr(V a0, V a1, V a2, V a3) {
top:;
V v63 = a3;
return F_Lex_dline(FLD(v63, 1), IMM(0), a1, C2(1, C3(0, C1(6, FLD(v63, 0)), a0, a1), a2));
}
static V W_Lex_dline_dstr(V *a) { (void)a; return F_Lex_dline_dstr(a[0], a[1], a[2], a[3]); }
static V F_Lex_dline_dchr(V a0, V a1, V a2, V a3) {
top:;
V v64 = a3;
return F_Lex_dline(F_Lex_ddrop1(FLD(v64, 1)), IMM(0), a1, C2(1, C3(0, C1(5, FLD(v64, 0)), a0, a1), a2));
}
static V W_Lex_dline_dchr(V *a) { (void)a; return F_Lex_dline_dchr(a[0], a[1], a[2], a[3]); }
static V F_Lex_ddrop1(V a0) {
top:;
V s65 = a0;
if ((s65) == IMM(0)) {
return IMM(0);
} else if (TAG(s65) == 1) {
return FLD(s65, 1);
} else { bend_fail("incomplete match"); }
}
static V W_Lex_ddrop1(V *a) { (void)a; return F_Lex_ddrop1(a[0]); }
static V F_Lex_ddigits(V a0, V a1) {
top:;
V s66 = a0;
if ((s66) == IMM(0)) {
return C2(0, a1, IMM(0));
} else if (TAG(s66) == 1) {
return F_Lex_ddigits_dif(FLD(s66, 0), FLD(s66, 1), a1, F_Char_dis__digit(FLD(s66, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_ddigits(V *a) { (void)a; return F_Lex_ddigits(a[0], a[1]); }
static V F_Lex_ddigits_dif(V a0, V a1, V a2, V a3) {
top:;
V s67 = a3;
if ((s67) == IMM(1)) {
return F_Lex_ddigits(a1, F_U32_dadd(F_U32_dmul(a2, 10u), F_U32_dsub(F_Char_dto__u32(a0), 48u)));
} else if ((s67) == IMM(0)) {
return C2(0, a2, C2(1, a0, a1));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_ddigits_dif(V *a) { (void)a; return F_Lex_ddigits_dif(a[0], a[1], a[2], a[3]); }
static V W_U32_dsub(V *a) { (void)a; return F_U32_dsub(a[0], a[1]); }
static V W_U32_dmul(V *a) { (void)a; return F_U32_dmul(a[0], a[1]); }
static V W_U32_dadd(V *a) { (void)a; return F_U32_dadd(a[0], a[1]); }
static V F_Lex_dline_dnum(V a0, V a1, V a2, V a3) {
top:;
V v68 = a3;
return F_Lex_dline_dnum_dgo(a0, a1, a2, FLD(v68, 0), FLD(v68, 1));
}
static V W_Lex_dline_dnum(V *a) { (void)a; return F_Lex_dline_dnum(a[0], a[1], a[2], a[3]); }
static V F_Lex_dline_dnum_dgo(V a0, V a1, V a2, V a3, V a4) {
top:;
V s69 = a4;
if ((s69) == IMM(0)) {
return F_Lex_dline(IMM(0), IMM(0), a1, C2(1, C3(0, C1(3, a3), a0, a1), a2));
} else if (TAG(s69) == 1) {
return F_Lex_dline_dnum_dif(a0, a1, a2, a3, FLD(s69, 0), FLD(s69, 1), F_Bool_dpick(F_U32_dis__eq(FLD(s69, 0), 110u), 1u, F_Bool_dpick(F_U32_dis__eq(FLD(s69, 0), 46u), 2u, 0u)));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dline_dnum_dgo(V *a) { (void)a; return F_Lex_dline_dnum_dgo(a[0], a[1], a[2], a[3], a[4]); }
static V F_Lex_dline_dnum_dif(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V s70 = a6;
if ((s70) == 0) {
return F_Lex_dline(C2(1, a4, a5), IMM(0), a1, C2(1, C3(0, C1(3, a3), a0, a1), a2));
} else if ((s70) == 1) {
return F_Lex_dline_dnat(a0, a1, a2, a3, a5);
} else if ((s70) >= 2) {
return F_Lex_dline_dflt(a0, a1, a2, a3, F_Lex_ddtext(a5, IMM(0)));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dline_dnum_dif(V *a) { (void)a; return F_Lex_dline_dnum_dif(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V F_Lex_ddtext(V a0, V a1) {
top:;
V s71 = a0;
if ((s71) == IMM(0)) {
return C2(0, F_Str_drev(a1), IMM(0));
} else if (TAG(s71) == 1) {
return F_Lex_ddtext_dif(FLD(s71, 0), FLD(s71, 1), a1, F_Char_dis__digit(FLD(s71, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_ddtext(V *a) { (void)a; return F_Lex_ddtext(a[0], a[1]); }
static V F_Lex_ddtext_dif(V a0, V a1, V a2, V a3) {
top:;
V s72 = a3;
if ((s72) == IMM(1)) {
return F_Lex_ddtext(a1, C2(1, a0, a2));
} else if ((s72) == IMM(0)) {
return C2(0, F_Str_drev(a2), C2(1, a0, a1));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_ddtext_dif(V *a) { (void)a; return F_Lex_ddtext_dif(a[0], a[1], a[2], a[3]); }
static V S74(void) { static V c; if (!c) c = MKS("."); return c; }
static V F_Lex_dline_dflt(V a0, V a1, V a2, V a3, V a4) {
top:;
V v73 = a4;
return F_Lex_dline(FLD(v73, 1), IMM(0), a1, C2(1, C3(0, C1(4, F_String_dappend(F_U32_dshow(a3), F_String_dappend(S74(), FLD(v73, 0)))), a0, a1), a2));
}
static V W_Lex_dline_dflt(V *a) { (void)a; return F_Lex_dline_dflt(a[0], a[1], a[2], a[3], a[4]); }
static V F_String_dappend(V a0, V a1) {
top:;
V s75 = a0;
if ((s75) == IMM(0)) {
return a1;
} else if (TAG(s75) == 1) {
return C2(1, FLD(s75, 0), F_String_dappend(FLD(s75, 1), a1));
} else { bend_fail("incomplete match"); }
}
static V W_String_dappend(V *a) { (void)a; return F_String_dappend(a[0], a[1]); }
static V F_U32_dshow(V a0) {
top:;
V v76 = a0;
return F_U32_dshow_dif(v76, F_U32_dis__zero(v76));
}
static V W_U32_dshow(V *a) { (void)a; return F_U32_dshow(a[0]); }
static V W_U32_dis__zero(V *a) { (void)a; return F_U32_dis__zero(a[0]); }
static V F_U32_dshow_dif(V a0, V a1) {
top:;
V s77 = a1;
if ((s77) == IMM(1)) {
return C2(1, 48u, IMM(0));
} else if ((s77) == IMM(0)) {
return F_U32_dshow_dgo(10u, a0, IMM(0));
} else { bend_fail("incomplete match"); }
}
static V W_U32_dshow_dif(V *a) { (void)a; return F_U32_dshow_dif(a[0], a[1]); }
static V F_U32_dshow_dgo(V a0, V a1, V a2) {
top:;
V s78 = a0;
if ((s78) == 0) {
return a2;
} else if ((s78) >= 1) {
return F_U32_dshow_dfin((s78 - 1), a2, a1, F_U32_dis__zero(a1));
} else { bend_fail("incomplete match"); }
}
static V W_U32_dshow_dgo(V *a) { (void)a; return F_U32_dshow_dgo(a[0], a[1], a[2]); }
static V F_U32_dshow_dfin(V a0, V a1, V a2, V a3) {
top:;
V s79 = a3;
if ((s79) == IMM(1)) {
return a1;
} else if ((s79) == IMM(0)) {
return F_U32_dshow_dgo(a0, F_U32_ddiv(a2, 10u), C2(1, F_U32_dadd(48u, F_U32_dmod(a2, 10u)), a1));
} else { bend_fail("incomplete match"); }
}
static V W_U32_dshow_dfin(V *a) { (void)a; return F_U32_dshow_dfin(a[0], a[1], a[2], a[3]); }
static V W_U32_dmod(V *a) { (void)a; return F_U32_dmod(a[0], a[1]); }
static V W_U32_ddiv(V *a) { (void)a; return F_U32_ddiv(a[0], a[1]); }
static V F_Lex_dline_dnat(V a0, V a1, V a2, V a3, V a4) {
top:;
V s80 = a4;
if ((s80) == IMM(0)) {
return F_Lex_dline(IMM(0), IMM(0), a1, C2(1, C3(0, C1(1, a3), a0, a1), a2));
} else if (TAG(s80) == 1) {
return F_Lex_dline_dnat_dif(a0, a1, a2, a3, FLD(s80, 0), FLD(s80, 1), F_U32_dis__eq(FLD(s80, 0), 43u));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dline_dnat(V *a) { (void)a; return F_Lex_dline_dnat(a[0], a[1], a[2], a[3], a[4]); }
static V F_Lex_dline_dnat_dif(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V s81 = a6;
if ((s81) == IMM(1)) {
return F_Lex_dline(a5, IMM(0), a1, C2(1, C3(0, C1(2, a3), a0, a1), a2));
} else if ((s81) == IMM(0)) {
return F_Lex_dline(C2(1, a4, a5), IMM(0), a1, C2(1, C3(0, C1(1, a3), a0, a1), a2));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dline_dnat_dif(V *a) { (void)a; return F_Lex_dline_dnat_dif(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V F_Lex_did(V a0, V a1) {
top:;
V s82 = a0;
if ((s82) == IMM(0)) {
return C2(0, F_Str_drev(a1), IMM(0));
} else if (TAG(s82) == 1) {
return F_Lex_did_dif(FLD(s82, 0), FLD(s82, 1), a1, F_Lex_dis__idc(FLD(s82, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_did(V *a) { (void)a; return F_Lex_did(a[0], a[1]); }
static V F_Lex_dis__idc(V a0) {
top:;
V v83 = F_Char_dto__u32(a0);
return F_Bool_dor(F_Char_dis__alpha(a0), F_Bool_dor(F_Char_dis__digit(a0), F_Bool_dor(F_U32_dis__eq(v83, 95u), F_U32_dis__eq(v83, 46u))));
}
static V W_Lex_dis__idc(V *a) { (void)a; return F_Lex_dis__idc(a[0]); }
static V F_Lex_did_dif(V a0, V a1, V a2, V a3) {
top:;
V s84 = a3;
if ((s84) == IMM(1)) {
return F_Lex_did(a1, C2(1, a0, a2));
} else if ((s84) == IMM(0)) {
return C2(0, F_Str_drev(a2), C2(1, a0, a1));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_did_dif(V *a) { (void)a; return F_Lex_did_dif(a[0], a[1], a[2], a[3]); }
static V F_Lex_dline_did(V a0, V a1, V a2, V a3) {
top:;
V v85 = a3;
return F_Lex_dline(FLD(v85, 1), IMM(0), a1, C2(1, C3(0, C1(0, FLD(v85, 0)), a0, a1), a2));
}
static V W_Lex_dline_did(V *a) { (void)a; return F_Lex_dline_did(a[0], a[1], a[2], a[3]); }
static V F_List_dreverse(V a2) {
top:;
return F_List_dreverse_dgo(a2, IMM(0));
}
static V W_List_dreverse(V *a) { (void)a; return F_List_dreverse(a[2]); }
static V F_List_dreverse_dgo(V a2, V a3) {
top:;
V s86 = a2;
if ((s86) == IMM(0)) {
return a3;
} else if (TAG(s86) == 1) {
{ V t0 = FLD(s86, 1); V t1 = C2(1, FLD(s86, 0), a3); a2 = t0; a3 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_List_dreverse_dgo(V *a) { (void)a; return F_List_dreverse_dgo(a[2], a[3]); }
static V F_Lex_dindent(V a0) {
top:;
V s87 = a0;
if ((s87) == IMM(0)) {
return 0u;
} else if (TAG(s87) == 1) {
return F_Lex_dindent_dif(FLD(s87, 1), F_U32_dis__eq(FLD(s87, 0), 32u));
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dindent(V *a) { (void)a; return F_Lex_dindent(a[0]); }
static V F_Lex_dindent_dif(V a0, V a1) {
top:;
V s88 = a1;
if ((s88) == IMM(1)) {
return F_U32_dinc(F_Lex_dindent(a0));
} else if ((s88) == IMM(0)) {
return 0u;
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dindent_dif(V *a) { (void)a; return F_Lex_dindent_dif(a[0], a[1]); }
static V F_Lex_dlines_dput(V a0, V a1) {
top:;
V s89 = a0;
if ((FLD(s89, 2)) == IMM(0)) {
return a1;
} else if (TAG(FLD(s89, 2)) == 1) {
return C2(1, C3(0, FLD(s89, 0), FLD(s89, 1), C2(1, FLD(FLD(s89, 2), 0), FLD(FLD(s89, 2), 1))), a1);
} else { bend_fail("incomplete match"); }
}
static V W_Lex_dlines_dput(V *a) { (void)a; return F_Lex_dlines_dput(a[0], a[1]); }
static V F_Lay_dlines(V a0, V a1) {
top:;
V s90 = a0;
if ((s90) == IMM(0)) {
return a1;
} else if (TAG(s90) == 1) {
{ V t0 = FLD(s90, 1); V t1 = F_Lay_dline(FLD(s90, 0), a1); a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Lay_dlines(V *a) { (void)a; return F_Lay_dlines(a[0], a[1]); }
static V F_Lay_dline(V a0, V a1) {
top:;
V v91 = a0;
V v92 = a1;
return F_Lay_dline_dgo(FLD(v91, 0), FLD(v91, 1), FLD(v91, 2), CN(0, 5, (V[]){FLD(v92, 0), FLD(v92, 1), FLD(v92, 2), FLD(v92, 3), FLD(v92, 4)}), F_U32_dis__zero(FLD(v92, 1)));
}
static V W_Lay_dline(V *a) { (void)a; return F_Lay_dline(a[0], a[1]); }
static V F_Lay_dline_dgo(V a0, V a1, V a2, V a3, V a4) {
top:;
V s93 = a4;
if ((s93) == IMM(1)) {
return F_Lay_dtoks(a2, F_Lay_dstart(a3, a0, a1));
} else if ((s93) == IMM(0)) {
return F_Lay_dtoks(a2, a3);
} else { bend_fail("incomplete match"); }
}
static V W_Lay_dline_dgo(V *a) { (void)a; return F_Lay_dline_dgo(a[0], a[1], a[2], a[3], a[4]); }
static V S97(void) { static V c; if (!c) c = MKS(":"); return c; }
static V F_Lay_dtoks(V a0, V a1) {
top:;
V s94 = a0;
if ((s94) == IMM(0)) {
return a1;
} else if (TAG(s94) == 1) {
V v95 = a1;
V v96 = F_U32_dadd(FLD(v95, 1), F_Lay_ddelta(FLD(FLD(s94, 0), 0)));
{ V t0 = FLD(s94, 1); V t1 = CN(0, 5, (V[]){C2(1, C3(0, FLD(FLD(s94, 0), 0), FLD(FLD(s94, 0), 1), FLD(FLD(s94, 0), 2)), FLD(v95, 0)), v96, F_Bool_dand(F_Lay_dis__sym(FLD(FLD(s94, 0), 0), S97()), F_U32_dis__zero(v96)), FLD(v95, 3), F_Lay_dis__op(FLD(FLD(s94, 0), 0))}); a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Lay_dtoks(V *a) { (void)a; return F_Lay_dtoks(a[0], a[1]); }
static V S99(void) { static V c; if (!c) c = MKS("->"); return c; }
static V S100(void) { static V c; if (!c) c = MKS("=>"); return c; }
static V S101(void) { static V c; if (!c) c = MKS("&"); return c; }
static V S102(void) { static V c; if (!c) c = MKS("|"); return c; }
static V S103(void) { static V c; if (!c) c = MKS("++"); return c; }
static V S104(void) { static V c; if (!c) c = MKS("<>"); return c; }
static V S105(void) { static V c; if (!c) c = MKS("&&"); return c; }
static V S106(void) { static V c; if (!c) c = MKS("||"); return c; }
static V S107(void) { static V c; if (!c) c = MKS("+"); return c; }
static V S108(void) { static V c; if (!c) c = MKS("*"); return c; }
static V S109(void) { static V c; if (!c) c = MKS(","); return c; }
static V S110(void) { static V c; if (!c) c = MKS("="); return c; }
static V S111(void) { static V c; if (!c) c = MKS("<-"); return c; }
static V F_Lay_dis__op(V a0) {
top:;
V s98 = a0;
if (TAG(s98) == 7) {
return F_List_dcontains(mk_clo(W_String_deq, 2, 0, 0), C2(1, S99(), C2(1, S100(), C2(1, S101(), C2(1, S102(), C2(1, S103(), C2(1, S104(), C2(1, S105(), C2(1, S106(), C2(1, S107(), C2(1, S108(), C2(1, S109(), C2(1, S110(), C2(1, S111(), IMM(0)))))))))))))), FLD(s98, 0));
} else {
return IMM(0);
}
}
static V W_Lay_dis__op(V *a) { (void)a; return F_Lay_dis__op(a[0]); }
static V F_String_deq(V a0, V a1) {
top:;
return F_String_deq_dfin(F_String_dcmp(a0, a1));
}
static V W_String_deq(V *a) { (void)a; return F_String_deq(a[0], a[1]); }
static V F_String_dcmp(V a0, V a1) {
top:;
V s112 = a0;
V s113 = a1;
if ((s112) == IMM(0) && (s113) == IMM(0)) {
return C2(0, C2(0, IMM(0), IMM(0)), IMM(1));
} else if ((s112) == IMM(0) && TAG(s113) == 1) {
return C2(0, C2(0, IMM(0), C2(1, FLD(s113, 0), FLD(s113, 1))), IMM(0));
} else if (TAG(s112) == 1 && (s113) == IMM(0)) {
return C2(0, C2(0, C2(1, FLD(s112, 0), FLD(s112, 1)), IMM(0)), IMM(2));
} else if (TAG(s112) == 1 && TAG(s113) == 1) {
return F_String_dcmp_dfin(FLD(s112, 1), FLD(s113, 1), F_Char_dcmp(FLD(s112, 0), FLD(s113, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_String_dcmp(V *a) { (void)a; return F_String_dcmp(a[0], a[1]); }
static V F_Char_dcmp(V a0, V a1) {
top:;
V s114 = a0;
V s115 = a1;
{
return C2(0, C2(0, s114, s115), F_U32_dcmp(s114, s115));
}
}
static V W_Char_dcmp(V *a) { (void)a; return F_Char_dcmp(a[0], a[1]); }
static V W_U32_dcmp(V *a) { (void)a; return F_U32_dcmp(a[0], a[1]); }
static V F_String_dcmp_dfin(V a0, V a1, V a2) {
top:;
V v116 = a2;
V s117 = FLD(v116, 1);
if ((s117) == IMM(0)) {
return C2(0, C2(0, C2(1, FLD(FLD(v116, 0), 0), a0), C2(1, FLD(FLD(v116, 0), 1), a1)), IMM(0));
} else if ((s117) == IMM(1)) {
return F_String_dcmp_drec(FLD(FLD(v116, 0), 0), FLD(FLD(v116, 0), 1), F_String_dcmp(a0, a1));
} else if ((s117) == IMM(2)) {
return C2(0, C2(0, C2(1, FLD(FLD(v116, 0), 0), a0), C2(1, FLD(FLD(v116, 0), 1), a1)), IMM(2));
} else { bend_fail("incomplete match"); }
}
static V W_String_dcmp_dfin(V *a) { (void)a; return F_String_dcmp_dfin(a[0], a[1], a[2]); }
static V F_String_dcmp_drec(V a0, V a1, V a2) {
top:;
V v118 = a2;
return C2(0, C2(0, C2(1, a0, FLD(FLD(v118, 0), 0)), C2(1, a1, FLD(FLD(v118, 0), 1))), FLD(v118, 1));
}
static V W_String_dcmp_drec(V *a) { (void)a; return F_String_dcmp_drec(a[0], a[1], a[2]); }
static V F_String_deq_dfin(V a0) {
top:;
V v119 = a0;
return F_Cmp_dis__eq(FLD(v119, 1));
}
static V W_String_deq_dfin(V *a) { (void)a; return F_String_deq_dfin(a[0]); }
static V F_Cmp_dis__eq(V a0) {
top:;
V s120 = a0;
if ((s120) == IMM(0)) {
return IMM(0);
} else if ((s120) == IMM(1)) {
return IMM(1);
} else if ((s120) == IMM(2)) {
return IMM(0);
} else { bend_fail("incomplete match"); }
}
static V W_Cmp_dis__eq(V *a) { (void)a; return F_Cmp_dis__eq(a[0]); }
static V F_List_dcontains(V a1, V a2, V a3) {
top:;
V s121 = a2;
if ((s121) == IMM(0)) {
return IMM(0);
} else if (TAG(s121) == 1) {
return F_Bool_dor(apply(apply(a1, FLD(s121, 0)), a3), F_List_dcontains(a1, FLD(s121, 1), a3));
} else { bend_fail("incomplete match"); }
}
static V W_List_dcontains(V *a) { (void)a; return F_List_dcontains(a[1], a[2], a[3]); }
static V F_Lay_dis__sym(V a0, V a1) {
top:;
V s122 = a0;
if (TAG(s122) == 7) {
return F_Str_deq(FLD(s122, 0), a1);
} else {
return IMM(0);
}
}
static V W_Lay_dis__sym(V *a) { (void)a; return F_Lay_dis__sym(a[0], a[1]); }
static V F_Str_deq(V a0, V a1) {
top:;
return F_String_deq(a0, a1);
}
static V W_Str_deq(V *a) { (void)a; return F_Str_deq(a[0], a[1]); }
static V S123(void) { static V c; if (!c) c = MKS("("); return c; }
static V S124(void) { static V c; if (!c) c = MKS("["); return c; }
static V S125(void) { static V c; if (!c) c = MKS("{"); return c; }
static V S126(void) { static V c; if (!c) c = MKS(")"); return c; }
static V S127(void) { static V c; if (!c) c = MKS("]"); return c; }
static V S128(void) { static V c; if (!c) c = MKS("}"); return c; }
static V F_Lay_ddelta(V a0) {
top:;
return F_Bool_dpick(F_Bool_dor(F_Lay_dis__sym(a0, S123()), F_Bool_dor(F_Lay_dis__sym(a0, S124()), F_Lay_dis__sym(a0, S125()))), 1u, F_Bool_dpick(F_Bool_dor(F_Lay_dis__sym(a0, S126()), F_Bool_dor(F_Lay_dis__sym(a0, S127()), F_Lay_dis__sym(a0, S128()))), 4294967295u, 0u));
}
static V W_Lay_ddelta(V *a) { (void)a; return F_Lay_ddelta(a[0]); }
static V F_Lay_dstart(V a0, V a1, V a2) {
top:;
V v129 = a0;
V v130 = F_Lay_dtop(FLD(v129, 3));
return F_Lay_dstart_dop(FLD(v129, 0), FLD(v129, 1), FLD(v129, 2), FLD(v129, 3), a1, a2, F_U32_dcmp(a1, v130), FLD(v129, 4));
}
static V W_Lay_dstart(V *a) { (void)a; return F_Lay_dstart(a[0], a[1], a[2]); }
static V F_Lay_dstart_dop(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7) {
top:;
V s131 = a7;
if ((s131) == IMM(1)) {
return CN(0, 5, (V[]){a0, a1, a2, a3, IMM(0)});
} else if ((s131) == IMM(0)) {
return F_Lay_dstart_dgo(a0, a1, a2, a3, a4, a5, a6);
} else { bend_fail("incomplete match"); }
}
static V W_Lay_dstart_dop(V *a) { (void)a; return F_Lay_dstart_dop(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]); }
static V F_Lay_dstart_dgo(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V s132 = a6;
if ((s132) == IMM(2)) {
return F_Lay_dstart_dgt(a0, a1, a2, a3, a4, a5, a2);
} else if ((s132) == IMM(1)) {
return CN(0, 5, (V[]){C2(1, F_Lay_dtok(IMM(8), a5), a0), a1, a2, a3, IMM(0)});
} else if ((s132) == IMM(0)) {
return F_Lay_ddedent(a1, a2, a5, F_Lay_dpop(a3, a4, C2(1, F_Lay_dtok(IMM(8), a5), a0), a5));
} else { bend_fail("incomplete match"); }
}
static V W_Lay_dstart_dgo(V *a) { (void)a; return F_Lay_dstart_dgo(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V F_Lay_dtok(V a0, V a1) {
top:;
return C3(0, a0, IMM(1), a1);
}
static V W_Lay_dtok(V *a) { (void)a; return F_Lay_dtok(a[0], a[1]); }
static V F_Lay_dpop(V a0, V a1, V a2, V a3) {
top:;
V s133 = a0;
if ((s133) == IMM(0)) {
return C2(0, IMM(0), a2);
} else if (TAG(s133) == 1) {
return F_Lay_dpop_dif(FLD(s133, 0), FLD(s133, 1), a1, a2, a3, F_U32_dis__gt(FLD(s133, 0), a1));
} else { bend_fail("incomplete match"); }
}
static V W_Lay_dpop(V *a) { (void)a; return F_Lay_dpop(a[0], a[1], a[2], a[3]); }
static V W_U32_dis__gt(V *a) { (void)a; return F_U32_dis__gt(a[0], a[1]); }
static V F_Lay_dpop_dif(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V s134 = a5;
if ((s134) == IMM(1)) {
return F_Lay_dpop(a1, a2, C2(1, F_Lay_dtok(IMM(10), a4), a3), a4);
} else if ((s134) == IMM(0)) {
return C2(0, C2(1, a0, a1), a3);
} else { bend_fail("incomplete match"); }
}
static V W_Lay_dpop_dif(V *a) { (void)a; return F_Lay_dpop_dif(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V F_Lay_ddedent(V a0, V a1, V a2, V a3) {
top:;
V v135 = a3;
return CN(0, 5, (V[]){FLD(v135, 1), a0, a1, FLD(v135, 0), IMM(0)});
}
static V W_Lay_ddedent(V *a) { (void)a; return F_Lay_ddedent(a[0], a[1], a[2], a[3]); }
static V F_Lay_dstart_dgt(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V s136 = a6;
if ((s136) == IMM(1)) {
return CN(0, 5, (V[]){C2(1, F_Lay_dtok(IMM(9), a5), a0), a1, a2, C2(1, a4, a3), IMM(0)});
} else if ((s136) == IMM(0)) {
return CN(0, 5, (V[]){a0, a1, a2, a3, IMM(0)});
} else { bend_fail("incomplete match"); }
}
static V W_Lay_dstart_dgt(V *a) { (void)a; return F_Lay_dstart_dgt(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V F_Lay_dtop(V a0) {
top:;
V s137 = a0;
if ((s137) == IMM(0)) {
return 0u;
} else if (TAG(s137) == 1) {
return FLD(s137, 0);
} else { bend_fail("incomplete match"); }
}
static V W_Lay_dtop(V *a) { (void)a; return F_Lay_dtop(a[0]); }
static V F_Lay_dfinish(V a0) {
top:;
V v138 = a0;
return F_Lay_dfinish_dgo(F_Lay_dpop(FLD(v138, 3), 0u, C2(1, F_Lay_dtok(IMM(8), 0u), FLD(v138, 0)), 0u));
}
static V W_Lay_dfinish(V *a) { (void)a; return F_Lay_dfinish(a[0]); }
static V F_Lay_dfinish_dgo(V a0) {
top:;
V v139 = a0;
return F_List_dreverse(C2(1, F_Lay_dtok(IMM(11), 0u), FLD(v139, 1)));
}
static V W_Lay_dfinish_dgo(V *a) { (void)a; return F_Lay_dfinish_dgo(a[0]); }
static V L141(V *a) {
return F_P_ddecls_dgo(F_P_dstuck(F_P_dtok__kind(a[0])));
}
static V L140(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L141, 1, 0, 0));
}
static V F_P_ddecls(void) {
top:;
return F_Parser_dbind(F_P_dnls(), mk_clo(L140, 1, 0, 0));
}
static V W_P_ddecls(V *a) { (void)a; return F_P_ddecls(); }
static V F_P_dtok__kind(V a0) {
top:;
V v142 = a0;
return FLD(v142, 0);
}
static V W_P_dtok__kind(V *a) { (void)a; return F_P_dtok__kind(a[0]); }
static V F_P_dstuck(V a0) {
top:;
V s143 = a0;
if (TAG(s143) == 12) {
return IMM(1);
} else if ((s143) == IMM(11)) {
return IMM(1);
} else {
return IMM(0);
}
}
static V W_P_dstuck(V *a) { (void)a; return F_P_dstuck(a[0]); }
static V L146(V *a) {
return F_Parser_dpure(C2(1, a[0], a[1]));
}
static V L145(V *a) {
return F_Parser_dbind(F_P_ddecls(), mk_clo(L146, 2, 1, (V[]){a[0]}));
}
static V F_P_ddecls_dgo(V a0) {
top:;
V s144 = a0;
if ((s144) == IMM(1)) {
return F_Parser_dpure(IMM(0));
} else if ((s144) == IMM(0)) {
return F_Parser_dbind(F_P_ddecl(), mk_clo(L145, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_ddecls_dgo(V *a) { (void)a; return F_P_ddecls_dgo(a[0]); }
static V L147(V *a) {
return C2(0, a[0], a[1]);
}
static V F_Parser_dpure(V a1) {
top:;
return mk_clo(L147, 2, 1, (V[]){a1});
}
static V W_Parser_dpure(V *a) { (void)a; return F_Parser_dpure(a[1]); }
static V L148(V *a) {
return F_Parser_dgo(apply(a[1], a[4]), a[0]);
}
static V F_Parser_dbind(V a2, V a3) {
top:;
return mk_clo(L148, 5, 4, (V[]){a3, a2, 0, 0});
}
static V W_Parser_dbind(V *a) { (void)a; return F_Parser_dbind(a[2], a[3]); }
static V F_Parser_dgo(V a2, V a3) {
top:;
V v149 = a2;
return apply(apply(a3, FLD(v149, 0)), FLD(v149, 1));
}
static V W_Parser_dgo(V *a) { (void)a; return F_Parser_dgo(a[2], a[3]); }
static V S151(void) { static V c; if (!c) c = MKS("@"); return c; }
static V L150(V *a) {
return F_P_ddecl_dat(F_P_dtok__is(a[0], S151()), a[0]);
}
static V F_P_ddecl(void) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L150, 1, 0, 0));
}
static V W_P_ddecl(V *a) { (void)a; return F_P_ddecl(); }
static V F_P_dtok__is(V a0, V a1) {
top:;
V s152 = a0;
if (TAG(FLD(s152, 0)) == 7) {
return F_Str_deq(FLD(FLD(s152, 0), 0), a1);
} else {
return IMM(0);
}
}
static V W_P_dtok__is(V *a) { (void)a; return F_P_dtok__is(a[0], a[1]); }
static V L156(V *a) {
return F_P_ddecl();
}
static V L155(V *a) {
return F_Parser_dbind(F_P_dnls(), mk_clo(L156, 1, 0, 0));
}
static V L154(V *a) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L155, 1, 0, 0));
}
static V S157(void) { static V c; if (!c) c = MKS("def"); return c; }
static V S158(void) { static V c; if (!c) c = MKS("type"); return c; }
static V S159(void) { static V c; if (!c) c = MKS("law"); return c; }
static V S160(void) { static V c; if (!c) c = MKS("import"); return c; }
static V F_P_ddecl_dat(V a0, V a1) {
top:;
V s153 = a0;
if ((s153) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L154, 1, 0, 0));
} else if ((s153) == IMM(0)) {
return F_P_ddecl_dgo(F_P_dtok__which__id(a1, C2(1, S157(), C2(1, S158(), C2(1, S159(), C2(1, S160(), IMM(0)))))));
} else { bend_fail("incomplete match"); }
}
static V W_P_ddecl_dat(V *a) { (void)a; return F_P_ddecl_dat(a[0], a[1]); }
static V F_P_dtok__which__id(V a0, V a1) {
top:;
V s161 = a0;
if (TAG(FLD(s161, 0)) == 0) {
return F_P_dwhich(FLD(FLD(s161, 0), 0), a1);
} else {
return 99u;
}
}
static V W_P_dtok__which__id(V *a) { (void)a; return F_P_dtok__which__id(a[0], a[1]); }
static V F_P_dwhich(V a0, V a1) {
top:;
V s162 = a1;
if ((s162) == IMM(0)) {
return 0u;
} else if (TAG(s162) == 1) {
return F_P_dwhich_dif(a0, FLD(s162, 1), F_String_deq(a0, FLD(s162, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_P_dwhich(V *a) { (void)a; return F_P_dwhich(a[0], a[1]); }
static V F_P_dwhich_dif(V a0, V a1, V a2) {
top:;
V s163 = a2;
if ((s163) == IMM(1)) {
return 0u;
} else if ((s163) == IMM(0)) {
return (F_P_dwhich(a0, a1) + 1);
} else { bend_fail("incomplete match"); }
}
static V W_P_dwhich_dif(V *a) { (void)a; return F_P_dwhich_dif(a[0], a[1], a[2]); }
static V S165(void) { static V c; if (!c) c = MKS("expected a declaration"); return c; }
static V S167(void) { static V c; if (!c) c = MKS(""); return c; }
static V S168(void) { static V c; if (!c) c = MKS(""); return c; }
static V L166(V *a) {
return F_Parser_dpure(C2(4, S167(), S168()));
}
static V F_P_ddecl_dgo(V a0) {
top:;
V s164 = a0;
if ((s164) == 0) {
return F_P_ddef();
} else if ((s164) == 1) {
return F_P_dtype();
} else if ((s164) == 2) {
return F_P_dlaw();
} else if ((s164) == 3) {
return F_P_dimport();
} else if ((s164) >= 4) {
return F_Parser_dbind(F_P_derr(S165()), mk_clo(L166, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_ddecl_dgo(V *a) { (void)a; return F_P_ddecl_dgo(a[0]); }
static V L169(V *a) {
return F_P_derr_dgo(a[0], a[1]);
}
static V F_P_derr(V a0) {
top:;
return mk_clo(L169, 2, 1, (V[]){a0});
}
static V W_P_derr(V *a) { (void)a; return F_P_derr(a[0]); }
static V S171(void) { static V c; if (!c) c = MKS("line "); return c; }
static V S172(void) { static V c; if (!c) c = MKS(": "); return c; }
static V S173(void) { static V c; if (!c) c = MKS(" (got '"); return c; }
static V S174(void) { static V c; if (!c) c = MKS("')"); return c; }
static V S175(void) { static V c; if (!c) c = MKS(" (at end)"); return c; }
static V F_P_derr_dgo(V a0, V a1) {
top:;
V s170 = a1;
if (TAG(s170) == 1 && TAG(FLD(FLD(s170, 0), 0)) == 12) {
return C2(0, IMM(0), C2(1, C3(0, C1(12, FLD(FLD(FLD(s170, 0), 0), 0)), FLD(FLD(s170, 0), 1), FLD(FLD(s170, 0), 2)), IMM(0)));
} else if (TAG(s170) == 1) {
return C2(0, IMM(0), C2(1, C3(0, C1(12, F_String_dappend(S171(), F_String_dappend(F_U32_dshow(FLD(FLD(s170, 0), 2)), F_String_dappend(S172(), F_String_dappend(a0, F_String_dappend(S173(), F_String_dappend(F_TK_dshow(FLD(FLD(s170, 0), 0)), S174()))))))), FLD(FLD(s170, 0), 1), FLD(FLD(s170, 0), 2)), IMM(0)));
} else if ((s170) == IMM(0)) {
return C2(0, IMM(0), C2(1, C3(0, C1(12, F_String_dappend(a0, S175())), IMM(1), 0u), IMM(0)));
} else { bend_fail("incomplete match"); }
}
static V W_P_derr_dgo(V *a) { (void)a; return F_P_derr_dgo(a[0], a[1]); }
static V S177(void) { static V c; if (!c) c = MKS("n"); return c; }
static V S178(void) { static V c; if (!c) c = MKS("n+"); return c; }
static V S179(void) { static V c; if (!c) c = MKS("'"); return c; }
static V S180(void) { static V c; if (!c) c = MKS("'"); return c; }
static V S181(void) { static V c; if (!c) c = MKS("\042"); return c; }
static V S182(void) { static V c; if (!c) c = MKS("\042"); return c; }
static V S183(void) { static V c; if (!c) c = MKS("<NL>\012"); return c; }
static V S184(void) { static V c; if (!c) c = MKS("<IN>"); return c; }
static V S185(void) { static V c; if (!c) c = MKS("<DE>"); return c; }
static V S186(void) { static V c; if (!c) c = MKS("<EOF>"); return c; }
static V S187(void) { static V c; if (!c) c = MKS("<ERR "); return c; }
static V S188(void) { static V c; if (!c) c = MKS(">"); return c; }
static V F_TK_dshow(V a0) {
top:;
V s176 = a0;
if (TAG(s176) == 0) {
return FLD(s176, 0);
} else if (TAG(s176) == 1) {
return F_String_dappend(F_U32_dshow(FLD(s176, 0)), S177());
} else if (TAG(s176) == 2) {
return F_String_dappend(F_U32_dshow(FLD(s176, 0)), S178());
} else if (TAG(s176) == 3) {
return F_U32_dshow(FLD(s176, 0));
} else if (TAG(s176) == 4) {
return FLD(s176, 0);
} else if (TAG(s176) == 5) {
return F_String_dappend(S179(), F_String_dappend(F_U32_dshow(FLD(s176, 0)), S180()));
} else if (TAG(s176) == 6) {
return F_String_dappend(S181(), F_String_dappend(FLD(s176, 0), S182()));
} else if (TAG(s176) == 7) {
return FLD(s176, 0);
} else if ((s176) == IMM(8)) {
return S183();
} else if ((s176) == IMM(9)) {
return S184();
} else if ((s176) == IMM(10)) {
return S185();
} else if ((s176) == IMM(11)) {
return S186();
} else if (TAG(s176) == 12) {
return F_String_dappend(S187(), F_String_dappend(FLD(s176, 0), S188()));
} else { bend_fail("incomplete match"); }
}
static V W_TK_dshow(V *a) { (void)a; return F_TK_dshow(a[0]); }
static V S192(void) { static V c; if (!c) c = MKS("as"); return c; }
static V L194(V *a) {
return F_Parser_dpure(C2(4, a[1], a[0]));
}
static V L193(V *a) {
return F_Parser_dbind(F_P_dskip__line(), mk_clo(L194, 3, 2, (V[]){a[1], a[0]}));
}
static V L191(V *a) {
return F_Parser_dbind(F_P_dimport_dalias(F_P_dtok__is__id(a[1], S192())), mk_clo(L193, 2, 1, (V[]){a[0]}));
}
static V L190(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L191, 2, 1, (V[]){a[0]}));
}
static V L189(V *a) {
return F_Parser_dbind(F_P_dimport_dpath(), mk_clo(L190, 1, 0, 0));
}
static V F_P_dimport(void) {
top:;
return F_Parser_dbind(F_P_dskip(), mk_clo(L189, 1, 0, 0));
}
static V W_P_dimport(V *a) { (void)a; return F_P_dimport(); }
static V L195(V *a) {
return C2(0, IMM(0), F_P_dskip__line_dgo(a[0]));
}
static V F_P_dskip__line(void) {
top:;
return mk_clo(L195, 1, 0, 0);
}
static V W_P_dskip__line(V *a) { (void)a; return F_P_dskip__line(); }
static V F_P_dskip__line_dgo(V a0) {
top:;
V s196 = a0;
if ((s196) == IMM(0)) {
return IMM(0);
} else if (TAG(s196) == 1 && (FLD(FLD(s196, 0), 0)) == IMM(8)) {
return C2(1, C3(0, IMM(8), FLD(FLD(s196, 0), 1), FLD(FLD(s196, 0), 2)), FLD(s196, 1));
} else if (TAG(s196) == 1 && (FLD(FLD(s196, 0), 0)) == IMM(10)) {
return C2(1, C3(0, IMM(10), FLD(FLD(s196, 0), 1), FLD(FLD(s196, 0), 2)), FLD(s196, 1));
} else if (TAG(s196) == 1 && (FLD(FLD(s196, 0), 0)) == IMM(11)) {
return C2(1, C3(0, IMM(11), FLD(FLD(s196, 0), 1), FLD(FLD(s196, 0), 2)), FLD(s196, 1));
} else if (TAG(s196) == 1 && TAG(FLD(FLD(s196, 0), 0)) == 12) {
return C2(1, C3(0, C1(12, FLD(FLD(FLD(s196, 0), 0), 0)), FLD(FLD(s196, 0), 1), FLD(FLD(s196, 0), 2)), FLD(s196, 1));
} else if (TAG(s196) == 1 && (FLD(FLD(s196, 0), 0)) == IMM(9)) {
return F_P_dskip__block_dgo(FLD(s196, 1), 1u);
} else if (TAG(s196) == 1) {
{ V t0 = FLD(s196, 1); a0 = t0; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_P_dskip__line_dgo(V *a) { (void)a; return F_P_dskip__line_dgo(a[0]); }
static V F_P_dskip__block_dgo(V a0, V a1) {
top:;
V s197 = a0;
if ((s197) == IMM(0)) {
return IMM(0);
} else if (TAG(s197) == 1 && (FLD(FLD(s197, 0), 0)) == IMM(9)) {
{ V t0 = FLD(s197, 1); V t1 = F_U32_dinc(a1); a0 = t0; a1 = t1; goto top; }
} else if (TAG(s197) == 1 && (FLD(FLD(s197, 0), 0)) == IMM(10)) {
return F_P_dskip__block_dde(FLD(s197, 1), a1, F_U32_dis__eq(a1, 1u));
} else if (TAG(s197) == 1 && (FLD(FLD(s197, 0), 0)) == IMM(11)) {
return C2(1, C3(0, IMM(11), FLD(FLD(s197, 0), 1), FLD(FLD(s197, 0), 2)), FLD(s197, 1));
} else if (TAG(s197) == 1) {
{ V t0 = FLD(s197, 1); V t1 = a1; a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_P_dskip__block_dgo(V *a) { (void)a; return F_P_dskip__block_dgo(a[0], a[1]); }
static V F_P_dskip__block_dde(V a0, V a1, V a2) {
top:;
V s198 = a2;
if ((s198) == IMM(1)) {
return a0;
} else if ((s198) == IMM(0)) {
return F_P_dskip__block_dgo(a0, F_U32_dsub(a1, 1u));
} else { bend_fail("incomplete match"); }
}
static V W_P_dskip__block_dde(V *a) { (void)a; return F_P_dskip__block_dde(a[0], a[1], a[2]); }
static V F_P_dtok__is__id(V a0, V a1) {
top:;
V s199 = a0;
if (TAG(FLD(s199, 0)) == 0) {
return F_Str_deq(FLD(FLD(s199, 0), 0), a1);
} else {
return IMM(0);
}
}
static V W_P_dtok__is__id(V *a) { (void)a; return F_P_dtok__is__id(a[0], a[1]); }
static V L201(V *a) {
return F_P_dident();
}
static V S202(void) { static V c; if (!c) c = MKS(""); return c; }
static V F_P_dimport_dalias(V a0) {
top:;
V s200 = a0;
if ((s200) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L201, 1, 0, 0));
} else if ((s200) == IMM(0)) {
return F_Parser_dpure(S202());
} else { bend_fail("incomplete match"); }
}
static V W_P_dimport_dalias(V *a) { (void)a; return F_P_dimport_dalias(a[0]); }
static V L203(V *a) {
return F_P_dident_dk(F_P_dtok__kind(a[0]));
}
static V F_P_dident(void) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L203, 1, 0, 0));
}
static V W_P_dident(V *a) { (void)a; return F_P_dident(); }
static V L205(V *a) {
return F_Parser_dpure(a[0]);
}
static V S206(void) { static V c; if (!c) c = MKS("expected an identifier"); return c; }
static V S208(void) { static V c; if (!c) c = MKS(""); return c; }
static V L207(V *a) {
return F_Parser_dpure(S208());
}
static V F_P_dident_dk(V a0) {
top:;
V s204 = a0;
if (TAG(s204) == 0) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L205, 2, 1, (V[]){FLD(s204, 0)}));
} else {
return F_Parser_dbind(F_P_derr(S206()), mk_clo(L207, 1, 0, 0));
}
}
static V W_P_dident_dk(V *a) { (void)a; return F_P_dident_dk(a[0]); }
static V L209(V *a) {
return F_P_dskip_dgo(a[0]);
}
static V F_P_dskip(void) {
top:;
return mk_clo(L209, 1, 0, 0);
}
static V W_P_dskip(V *a) { (void)a; return F_P_dskip(); }
static V F_P_dskip_dgo(V a0) {
top:;
V s210 = a0;
if ((s210) == IMM(0)) {
return C2(0, IMM(0), IMM(0));
} else if (TAG(s210) == 1) {
return F_P_dskip_dif(C3(0, FLD(FLD(s210, 0), 0), FLD(FLD(s210, 0), 1), FLD(FLD(s210, 0), 2)), FLD(s210, 1), F_P_dstuck(FLD(FLD(s210, 0), 0)));
} else { bend_fail("incomplete match"); }
}
static V W_P_dskip_dgo(V *a) { (void)a; return F_P_dskip_dgo(a[0]); }
static V F_P_dskip_dif(V a0, V a1, V a2) {
top:;
V s211 = a2;
if ((s211) == IMM(1)) {
return C2(0, IMM(0), C2(1, a0, a1));
} else if ((s211) == IMM(0)) {
return C2(0, IMM(0), a1);
} else { bend_fail("incomplete match"); }
}
static V W_P_dskip_dif(V *a) { (void)a; return F_P_dskip_dif(a[0], a[1], a[2]); }
static V L212(V *a) {
return F_P_dpeek_dgo(a[0]);
}
static V F_P_dpeek(void) {
top:;
return mk_clo(L212, 1, 0, 0);
}
static V W_P_dpeek(V *a) { (void)a; return F_P_dpeek(); }
static V F_P_dpeek_dgo(V a0) {
top:;
V s213 = a0;
if ((s213) == IMM(0)) {
return C2(0, F_P_deof__tok(), IMM(0));
} else if (TAG(s213) == 1) {
return C2(0, FLD(s213, 0), C2(1, FLD(s213, 0), FLD(s213, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_P_dpeek_dgo(V *a) { (void)a; return F_P_dpeek_dgo(a[0]); }
static V F_P_deof__tok(void) {
top:;
return C3(0, IMM(11), IMM(1), 0u);
}
static V W_P_deof__tok(V *a) { (void)a; return F_P_deof__tok(); }
static V L214(V *a) {
return F_P_dimport_dpath_dgo(a[0]);
}
static V F_P_dimport_dpath(void) {
top:;
return mk_clo(L214, 1, 0, 0);
}
static V W_P_dimport_dpath(V *a) { (void)a; return F_P_dimport_dpath(); }
static V S216(void) { static V c; if (!c) c = MKS("as"); return c; }
static V S217(void) { static V c; if (!c) c = MKS(""); return c; }
static V F_P_dimport_dpath_dgo(V a0) {
top:;
V s215 = a0;
if (TAG(s215) == 1 && TAG(FLD(FLD(s215, 0), 0)) == 0) {
return F_P_dimport_dpath_did(FLD(FLD(FLD(s215, 0), 0), 0), FLD(FLD(s215, 0), 1), FLD(FLD(s215, 0), 2), FLD(s215, 1), F_Str_deq(FLD(FLD(FLD(s215, 0), 0), 0), S216()));
} else if (TAG(s215) == 1 && TAG(FLD(FLD(s215, 0), 0)) == 7) {
return F_P_dimport_dpath_dcat(FLD(FLD(FLD(s215, 0), 0), 0), F_P_dimport_dpath_dgo(FLD(s215, 1)));
} else {
return C2(0, S217(), s215);
}
}
static V W_P_dimport_dpath_dgo(V *a) { (void)a; return F_P_dimport_dpath_dgo(a[0]); }
static V F_P_dimport_dpath_dcat(V a0, V a1) {
top:;
V v218 = a1;
return C2(0, F_String_dappend(a0, FLD(v218, 0)), FLD(v218, 1));
}
static V W_P_dimport_dpath_dcat(V *a) { (void)a; return F_P_dimport_dpath_dcat(a[0], a[1]); }
static V S220(void) { static V c; if (!c) c = MKS(""); return c; }
static V F_P_dimport_dpath_did(V a0, V a1, V a2, V a3, V a4) {
top:;
V s219 = a4;
if ((s219) == IMM(1)) {
return C2(0, S220(), C2(1, C3(0, C1(0, a0), a1, a2), a3));
} else if ((s219) == IMM(0)) {
return F_P_dimport_dpath_dcat(a0, F_P_dimport_dpath_dgo(a3));
} else { bend_fail("incomplete match"); }
}
static V W_P_dimport_dpath_did(V *a) { (void)a; return F_P_dimport_dpath_did(a[0], a[1], a[2], a[3], a[4]); }
static V S223(void) { static V c; if (!c) c = MKS(":"); return c; }
static V L226(V *a) {
return F_Parser_dpure(C2(2, a[0], a[1]));
}
static V L225(V *a) {
return F_Parser_dbind(F_P_dlaw_dlines(), mk_clo(L226, 2, 1, (V[]){a[0]}));
}
static V L224(V *a) {
return F_Parser_dbind(F_P_dexpect__in(), mk_clo(L225, 2, 1, (V[]){a[0]}));
}
static V L222(V *a) {
return F_Parser_dbind(F_P_dexpect(S223()), mk_clo(L224, 2, 1, (V[]){a[0]}));
}
static V L221(V *a) {
return F_Parser_dbind(F_P_dident(), mk_clo(L222, 1, 0, 0));
}
static V F_P_dlaw(void) {
top:;
return F_Parser_dbind(F_P_dskip(), mk_clo(L221, 1, 0, 0));
}
static V W_P_dlaw(V *a) { (void)a; return F_P_dlaw(); }
static V L228(V *a) {
return F_P_dlaw_dgo(a[0], F_Bool_dpick(F_P_dis__de(a[0]), 0u, F_Bool_dpick(F_P_dstuck(F_P_dtok__kind(a[0])), 1u, 2u)));
}
static V L227(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L228, 1, 0, 0));
}
static V F_P_dlaw_dlines(void) {
top:;
return F_Parser_dbind(F_P_dnls(), mk_clo(L227, 1, 0, 0));
}
static V W_P_dlaw_dlines(V *a) { (void)a; return F_P_dlaw_dlines(); }
static V F_P_dis__de(V a0) {
top:;
V s229 = a0;
if ((FLD(s229, 0)) == IMM(10)) {
return IMM(1);
} else {
return IMM(0);
}
}
static V W_P_dis__de(V *a) { (void)a; return F_P_dis__de(a[0]); }
static V L231(V *a) {
return F_Parser_dpure(IMM(0));
}
static V S232(void) { static V c; if (!c) c = MKS("for"); return c; }
static V F_P_dlaw_dgo(V a0, V a1) {
top:;
V s230 = a1;
if ((s230) == 0) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L231, 1, 0, 0));
} else if ((s230) == 1) {
return F_Parser_dpure(IMM(0));
} else if ((s230) >= 2) {
return F_P_dlaw_dline(F_P_dtok__which__id(a0, C2(1, S232(), IMM(0))));
} else { bend_fail("incomplete match"); }
}
static V W_P_dlaw_dgo(V *a) { (void)a; return F_P_dlaw_dgo(a[0], a[1]); }
static V L237(V *a) {
return F_Parser_dpure(C2(1, a[0], a[1]));
}
static V L236(V *a) {
return F_Parser_dbind(F_P_dlaw_dlines(), mk_clo(L237, 2, 1, (V[]){a[0]}));
}
static V L235(V *a) {
return F_Parser_dbind(F_P_dskip__line(), mk_clo(L236, 2, 1, (V[]){a[0]}));
}
static V L234(V *a) {
return F_Parser_dbind(F_P_dparam(), mk_clo(L235, 1, 0, 0));
}
static V L238(V *a) {
return F_P_dlaw_dlines();
}
static V F_P_dlaw_dline(V a0) {
top:;
V s233 = a0;
if ((s233) == 0) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L234, 1, 0, 0));
} else if ((s233) >= 1) {
return F_Parser_dbind(F_P_dskip__line(), mk_clo(L238, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dlaw_dline(V *a) { (void)a; return F_P_dlaw_dline(a[0]); }
static V S244(void) { static V c; if (!c) c = MKS(":"); return c; }
static V L243(V *a) {
return F_P_dparam_dty(a[1], a[0], F_P_dtok__is(a[2], S244()));
}
static V L242(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L243, 3, 2, (V[]){a[0], a[1]}));
}
static V L241(V *a) {
return F_Parser_dbind(F_P_dident(), mk_clo(L242, 2, 1, (V[]){a[0]}));
}
static V L240(V *a) {
return F_Parser_dbind(F_P_dparam_dskip__mode(a[0]), mk_clo(L241, 2, 1, (V[]){a[0]}));
}
static V L239(V *a) {
return F_Parser_dbind(F_Parser_dpure(F_P_dparam_dmode(a[0])), mk_clo(L240, 1, 0, 0));
}
static V F_P_dparam(void) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L239, 1, 0, 0));
}
static V W_P_dparam(V *a) { (void)a; return F_P_dparam(); }
static V L247(V *a) {
return F_Parser_dpure(C3(0, a[1], a[0], F_P_dhead(a[2])));
}
static V L246(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L247, 3, 2, (V[]){a[0], a[1]}));
}
static V S248(void) { static V c; if (!c) c = MKS(""); return c; }
static V F_P_dparam_dty(V a0, V a1, V a2) {
top:;
V s245 = a2;
if ((s245) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L246, 3, 2, (V[]){a1, a0}));
} else if ((s245) == IMM(0)) {
return F_Parser_dpure(C3(0, a0, F_Bool_dpick(F_U32_dis__zero(a1), 4u, a1), S248()));
} else { bend_fail("incomplete match"); }
}
static V W_P_dparam_dty(V *a) { (void)a; return F_P_dparam_dty(a[0], a[1], a[2]); }
static V S250(void) { static V c; if (!c) c = MKS(""); return c; }
static V F_P_dhead(V a0) {
top:;
V s249 = a0;
if (TAG(s249) == 0) {
return FLD(s249, 0);
} else if (TAG(s249) == 5 && TAG(FLD(s249, 0)) == 0) {
return FLD(FLD(s249, 0), 0);
} else if (TAG(s249) == 14) {
return FLD(s249, 0);
} else {
return S250();
}
}
static V W_P_dhead(V *a) { (void)a; return F_P_dhead(a[0]); }
static V F_P_dexpr(void) {
top:;
return F_P_dbin(1u);
}
static V W_P_dexpr(V *a) { (void)a; return F_P_dexpr(); }
static V L251(V *a) {
return F_P_dbin_dloop(a[0], a[1]);
}
static V F_P_dbin(V a0) {
top:;
return F_Parser_dbind(F_P_dterm(), mk_clo(L251, 2, 1, (V[]){a0}));
}
static V W_P_dbin(V *a) { (void)a; return F_P_dbin(a[0]); }
static V L252(V *a) {
return F_P_dbin_dloop_dop(a[1], a[0], F_P_dtok__op(a[2]));
}
static V F_P_dbin_dloop(V a0, V a1) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L252, 3, 2, (V[]){a1, a0}));
}
static V W_P_dbin_dloop(V *a) { (void)a; return F_P_dbin_dloop(a[0], a[1]); }
static V S254(void) { static V c; if (!c) c = MKS(""); return c; }
static V F_P_dtok__op(V a0) {
top:;
V s253 = a0;
if (TAG(FLD(s253, 0)) == 7 && (FLD(s253, 1)) == IMM(1)) {
return F_P_dop__find(FLD(FLD(s253, 0), 0), F_P_dops());
} else {
return C3(0, S254(), 0u, IMM(0));
}
}
static V W_P_dtok__op(V *a) { (void)a; return F_P_dtok__op(a[0]); }
static V S255(void) { static V c; if (!c) c = MKS("->"); return c; }
static V S256(void) { static V c; if (!c) c = MKS("|"); return c; }
static V S257(void) { static V c; if (!c) c = MKS("&"); return c; }
static V S258(void) { static V c; if (!c) c = MKS("<&>"); return c; }
static V S259(void) { static V c; if (!c) c = MKS("||"); return c; }
static V S260(void) { static V c; if (!c) c = MKS("&&"); return c; }
static V S261(void) { static V c; if (!c) c = MKS("<>"); return c; }
static V S262(void) { static V c; if (!c) c = MKS("++"); return c; }
static V S263(void) { static V c; if (!c) c = MKS("<"); return c; }
static V S264(void) { static V c; if (!c) c = MKS("<="); return c; }
static V S265(void) { static V c; if (!c) c = MKS(">"); return c; }
static V S266(void) { static V c; if (!c) c = MKS(">="); return c; }
static V S267(void) { static V c; if (!c) c = MKS(".|."); return c; }
static V S268(void) { static V c; if (!c) c = MKS(".^."); return c; }
static V S269(void) { static V c; if (!c) c = MKS(".&."); return c; }
static V S270(void) { static V c; if (!c) c = MKS("<<"); return c; }
static V S271(void) { static V c; if (!c) c = MKS(">>"); return c; }
static V S272(void) { static V c; if (!c) c = MKS("+"); return c; }
static V S273(void) { static V c; if (!c) c = MKS("-"); return c; }
static V S274(void) { static V c; if (!c) c = MKS("*"); return c; }
static V S275(void) { static V c; if (!c) c = MKS("/"); return c; }
static V S276(void) { static V c; if (!c) c = MKS("%"); return c; }
static V F_P_dops(void) {
top:;
return C2(1, C3(0, S255(), 1u, IMM(1)), C2(1, C3(0, S256(), 2u, IMM(1)), C2(1, C3(0, S257(), 3u, IMM(1)), C2(1, C3(0, S258(), 3u, IMM(1)), C2(1, C3(0, S259(), 4u, IMM(0)), C2(1, C3(0, S260(), 5u, IMM(0)), C2(1, C3(0, S261(), 6u, IMM(1)), C2(1, C3(0, S262(), 6u, IMM(1)), C2(1, C3(0, S263(), 7u, IMM(0)), C2(1, C3(0, S264(), 7u, IMM(0)), C2(1, C3(0, S265(), 7u, IMM(0)), C2(1, C3(0, S266(), 7u, IMM(0)), C2(1, C3(0, S267(), 8u, IMM(0)), C2(1, C3(0, S268(), 9u, IMM(0)), C2(1, C3(0, S269(), 10u, IMM(0)), C2(1, C3(0, S270(), 11u, IMM(0)), C2(1, C3(0, S271(), 11u, IMM(0)), C2(1, C3(0, S272(), 12u, IMM(0)), C2(1, C3(0, S273(), 12u, IMM(0)), C2(1, C3(0, S274(), 13u, IMM(0)), C2(1, C3(0, S275(), 13u, IMM(0)), C2(1, C3(0, S276(), 13u, IMM(0)), IMM(0)))))))))))))))))))))));
}
static V W_P_dops(V *a) { (void)a; return F_P_dops(); }
static V S278(void) { static V c; if (!c) c = MKS(""); return c; }
static V F_P_dop__find(V a0, V a1) {
top:;
V s277 = a1;
if ((s277) == IMM(0)) {
return C3(0, S278(), 0u, IMM(0));
} else if (TAG(s277) == 1) {
return F_P_dop__find_dif(a0, FLD(s277, 1), C3(0, FLD(FLD(s277, 0), 0), FLD(FLD(s277, 0), 1), FLD(FLD(s277, 0), 2)), F_String_deq(a0, FLD(FLD(s277, 0), 0)));
} else { bend_fail("incomplete match"); }
}
static V W_P_dop__find(V *a) { (void)a; return F_P_dop__find(a[0], a[1]); }
static V F_P_dop__find_dif(V a0, V a1, V a2, V a3) {
top:;
V s279 = a3;
if ((s279) == IMM(1)) {
return a2;
} else if ((s279) == IMM(0)) {
return F_P_dop__find(a0, a1);
} else { bend_fail("incomplete match"); }
}
static V W_P_dop__find_dif(V *a) { (void)a; return F_P_dop__find_dif(a[0], a[1], a[2], a[3]); }
static V F_P_dbin_dloop_dop(V a0, V a1, V a2) {
top:;
V v280 = a2;
return F_P_dbin_dloop_dgo(a0, a1, FLD(v280, 0), FLD(v280, 1), FLD(v280, 2), F_Bool_dand(F_U32_dis__ne(FLD(v280, 1), 0u), F_U32_dis__ge(FLD(v280, 1), a0)));
}
static V W_P_dbin_dloop_dop(V *a) { (void)a; return F_P_dbin_dloop_dop(a[0], a[1], a[2]); }
static V W_U32_dis__ne(V *a) { (void)a; return F_U32_dis__ne(a[0], a[1]); }
static V L283(V *a) {
return F_P_dbin_dloop(a[2], F_P_dmk__bin(a[1], a[0], a[3]));
}
static V L282(V *a) {
return F_Parser_dbind(F_P_dbin(F_Bool_dpick(a[4], a[3], F_U32_dinc(a[3]))), mk_clo(L283, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V F_P_dbin_dloop_dgo(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V s281 = a5;
if ((s281) == IMM(0)) {
return F_Parser_dpure(a1);
} else if ((s281) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L282, 6, 5, (V[]){a1, a2, a0, a3, a4}));
} else { bend_fail("incomplete match"); }
}
static V W_P_dbin_dloop_dgo(V *a) { (void)a; return F_P_dbin_dloop_dgo(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V S284(void) { static V c; if (!c) c = MKS("->"); return c; }
static V S285(void) { static V c; if (!c) c = MKS("|"); return c; }
static V S286(void) { static V c; if (!c) c = MKS("&"); return c; }
static V S287(void) { static V c; if (!c) c = MKS("<&>"); return c; }
static V S288(void) { static V c; if (!c) c = MKS("||"); return c; }
static V S289(void) { static V c; if (!c) c = MKS("&&"); return c; }
static V S290(void) { static V c; if (!c) c = MKS("<>"); return c; }
static V S291(void) { static V c; if (!c) c = MKS("++"); return c; }
static V F_P_dmk__bin(V a0, V a1, V a2) {
top:;
return F_P_dmk__bin_dgo(a0, a1, a2, F_P_dwhich(a0, C2(1, S284(), C2(1, S285(), C2(1, S286(), C2(1, S287(), C2(1, S288(), C2(1, S289(), C2(1, S290(), C2(1, S291(), IMM(0)))))))))));
}
static V W_P_dmk__bin(V *a) { (void)a; return F_P_dmk__bin(a[0], a[1], a[2]); }
static V S293(void) { static V c; if (!c) c = MKS("->"); return c; }
static V S294(void) { static V c; if (!c) c = MKS("|"); return c; }
static V S295(void) { static V c; if (!c) c = MKS("&"); return c; }
static V S296(void) { static V c; if (!c) c = MKS("#q"); return c; }
static V S297(void) { static V c; if (!c) c = MKS("Bool.or"); return c; }
static V S298(void) { static V c; if (!c) c = MKS("Bool.and"); return c; }
static V S299(void) { static V c; if (!c) c = MKS("Con"); return c; }
static V S300(void) { static V c; if (!c) c = MKS("String.append"); return c; }
static V F_P_dmk__bin_dgo(V a0, V a1, V a2, V a3) {
top:;
V s292 = a3;
if ((s292) == 0) {
return C2(14, S293(), C2(1, a1, C2(1, a2, IMM(0))));
} else if ((s292) == 1) {
return C2(14, S294(), C2(1, a1, C2(1, a2, IMM(0))));
} else if ((s292) == 2) {
return C2(14, S295(), C2(1, a1, C2(1, a2, IMM(0))));
} else if ((s292) == 3) {
return C2(14, S296(), IMM(0));
} else if ((s292) == 4) {
return C2(5, C1(0, S297()), C2(1, a1, C2(1, a2, IMM(0))));
} else if ((s292) == 5) {
return C2(5, C1(0, S298()), C2(1, a1, C2(1, a2, IMM(0))));
} else if ((s292) == 6) {
return C2(6, S299(), C2(1, a1, C2(1, a2, IMM(0))));
} else if ((s292) == 7) {
return C2(5, C1(0, S300()), C2(1, a1, C2(1, a2, IMM(0))));
} else if ((s292) >= 8) {
return C3(12, a0, a1, a2);
} else { bend_fail("incomplete match"); }
}
static V W_P_dmk__bin_dgo(V *a) { (void)a; return F_P_dmk__bin_dgo(a[0], a[1], a[2], a[3]); }
static V L301(V *a) {
return F_P_dpostfix(a[0]);
}
static V F_P_dterm(void) {
top:;
return F_Parser_dbind(F_P_dprimary(), mk_clo(L301, 1, 0, 0));
}
static V W_P_dterm(V *a) { (void)a; return F_P_dterm(); }
static V L302(V *a) {
return F_P_dpostfix_dt(a[0], a[1]);
}
static V F_P_dpostfix(V a0) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L302, 2, 1, (V[]){a0}));
}
static V W_P_dpostfix(V *a) { (void)a; return F_P_dpostfix(a[0]); }
static V S303(void) { static V c; if (!c) c = MKS("("); return c; }
static V S304(void) { static V c; if (!c) c = MKS("!"); return c; }
static V S305(void) { static V c; if (!c) c = MKS("["); return c; }
static V F_P_dpostfix_dt(V a0, V a1) {
top:;
return F_P_dpostfix_dk(a0, F_Bool_dpick(F_P_dtok__sp(a1), 9u, F_P_dtok__which(a1, C2(1, S303(), C2(1, S304(), C2(1, S305(), IMM(0)))))));
}
static V W_P_dpostfix_dt(V *a) { (void)a; return F_P_dpostfix_dt(a[0], a[1]); }
static V F_P_dtok__which(V a0, V a1) {
top:;
V s306 = a0;
if (TAG(FLD(s306, 0)) == 7) {
return F_P_dwhich(FLD(FLD(s306, 0), 0), a1);
} else {
return 99u;
}
}
static V W_P_dtok__which(V *a) { (void)a; return F_P_dtok__which(a[0], a[1]); }
static V F_P_dtok__sp(V a0) {
top:;
V v307 = a0;
return FLD(v307, 1);
}
static V W_P_dtok__sp(V *a) { (void)a; return F_P_dtok__sp(a[0]); }
static V S310(void) { static V c; if (!c) c = MKS(")"); return c; }
static V L311(V *a) {
return F_P_dpostfix(C2(5, a[0], a[1]));
}
static V L309(V *a) {
return F_Parser_dbind(F_P_dlist(S310()), mk_clo(L311, 2, 1, (V[]){a[0]}));
}
static V L312(V *a) {
return F_P_dpostfix(a[0]);
}
static V S315(void) { static V c; if (!c) c = MKS("]"); return c; }
static V S317(void) { static V c; if (!c) c = MKS("Array.get"); return c; }
static V S318(void) { static V c; if (!c) c = MKS("U32"); return c; }
static V L316(V *a) {
return F_P_dpostfix(C2(5, C1(0, S317()), C2(1, C2(14, S318(), IMM(0)), C2(1, a[1], C2(1, a[0], IMM(0))))));
}
static V L314(V *a) {
return F_Parser_dbind(F_P_dexpect(S315()), mk_clo(L316, 3, 2, (V[]){a[1], a[0]}));
}
static V L313(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L314, 2, 1, (V[]){a[0]}));
}
static V F_P_dpostfix_dk(V a0, V a1) {
top:;
V s308 = a1;
if ((s308) == 0) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L309, 2, 1, (V[]){a0}));
} else if ((s308) == 1) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L312, 2, 1, (V[]){a0}));
} else if ((s308) == 2) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L313, 2, 1, (V[]){a0}));
} else if ((s308) >= 3) {
return F_Parser_dpure(a0);
} else { bend_fail("incomplete match"); }
}
static V W_P_dpostfix_dk(V *a) { (void)a; return F_P_dpostfix_dk(a[0], a[1]); }
static V L319(V *a) {
return F_P_dexpect_dif(a[0], F_P_dtok__is(a[1], a[0]));
}
static V F_P_dexpect(V a0) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L319, 2, 1, (V[]){a0}));
}
static V W_P_dexpect(V *a) { (void)a; return F_P_dexpect(a[0]); }
static V S321(void) { static V c; if (!c) c = MKS("expected '"); return c; }
static V S322(void) { static V c; if (!c) c = MKS("'"); return c; }
static V F_P_dexpect_dif(V a0, V a1) {
top:;
V s320 = a1;
if ((s320) == IMM(1)) {
return F_P_dskip();
} else if ((s320) == IMM(0)) {
return F_P_derr(F_String_dappend(S321(), F_String_dappend(a0, S322())));
} else { bend_fail("incomplete match"); }
}
static V W_P_dexpect_dif(V *a) { (void)a; return F_P_dexpect_dif(a[0], a[1]); }
static V L323(V *a) {
return F_P_dlist_dstuck(a[0], a[1], F_P_dstuck(F_P_dtok__kind(a[1])));
}
static V F_P_dlist(V a0) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L323, 2, 1, (V[]){a0}));
}
static V W_P_dlist(V *a) { (void)a; return F_P_dlist(a[0]); }
static V S325(void) { static V c; if (!c) c = MKS("unterminated list"); return c; }
static V L326(V *a) {
return F_Parser_dpure(IMM(0));
}
static V F_P_dlist_dstuck(V a0, V a1, V a2) {
top:;
V s324 = a2;
if ((s324) == IMM(1)) {
return F_Parser_dbind(F_P_derr(S325()), mk_clo(L326, 1, 0, 0));
} else if ((s324) == IMM(0)) {
return F_P_dlist_dgo(a0, F_P_dtok__is(a1, a0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dlist_dstuck(V *a) { (void)a; return F_P_dlist_dstuck(a[0], a[1], a[2]); }
static V L328(V *a) {
return F_Parser_dpure(IMM(0));
}
static V F_P_dlist_dgo(V a0, V a1) {
top:;
V s327 = a1;
if ((s327) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L328, 1, 0, 0));
} else if ((s327) == IMM(0)) {
return F_P_dlist_ditem(a0);
} else { bend_fail("incomplete match"); }
}
static V W_P_dlist_dgo(V *a) { (void)a; return F_P_dlist_dgo(a[0], a[1]); }
static V S330(void) { static V c; if (!c) c = MKS(","); return c; }
static V L332(V *a) {
return F_Parser_dpure(C2(1, a[0], a[1]));
}
static V L331(V *a) {
return F_Parser_dbind(F_P_dlist_dmore(a[1], a[2]), mk_clo(L332, 2, 1, (V[]){a[0]}));
}
static V L329(V *a) {
return F_Parser_dbind(F_P_deat(S330()), mk_clo(L331, 3, 2, (V[]){a[1], a[0]}));
}
static V F_P_dlist_ditem(V a0) {
top:;
return F_Parser_dbind(F_P_dexpr(), mk_clo(L329, 2, 1, (V[]){a0}));
}
static V W_P_dlist_ditem(V *a) { (void)a; return F_P_dlist_ditem(a[0]); }
static V L334(V *a) {
return F_Parser_dpure(IMM(0));
}
static V F_P_dlist_dmore(V a0, V a1) {
top:;
V s333 = a1;
if ((s333) == IMM(1)) {
return F_P_dlist(a0);
} else if ((s333) == IMM(0)) {
return F_Parser_dbind(F_P_dexpect(a0), mk_clo(L334, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dlist_dmore(V *a) { (void)a; return F_P_dlist_dmore(a[0], a[1]); }
static V L335(V *a) {
return F_P_deat_dif(F_P_dtok__is(a[1], a[0]));
}
static V F_P_deat(V a0) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L335, 2, 1, (V[]){a0}));
}
static V W_P_deat(V *a) { (void)a; return F_P_deat(a[0]); }
static V L337(V *a) {
return F_Parser_dpure(IMM(1));
}
static V F_P_deat_dif(V a0) {
top:;
V s336 = a0;
if ((s336) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L337, 1, 0, 0));
} else if ((s336) == IMM(0)) {
return F_Parser_dpure(IMM(0));
} else { bend_fail("incomplete match"); }
}
static V W_P_deat_dif(V *a) { (void)a; return F_P_deat_dif(a[0]); }
static V L338(V *a) {
return F_P_dprimary_dk(F_P_dtok__kind(a[0]));
}
static V F_P_dprimary(void) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L338, 1, 0, 0));
}
static V W_P_dprimary(V *a) { (void)a; return F_P_dprimary(); }
static V L341(V *a) {
return F_P_dafter__id(a[0], a[1]);
}
static V L340(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L341, 2, 1, (V[]){a[0]}));
}
static V L342(V *a) {
return F_Parser_dpure(C1(1, a[0]));
}
static V L343(V *a) {
return F_Parser_dpure(C1(2, a[0]));
}
static V L345(V *a) {
return F_Parser_dpure(C2(11, a[0], a[1]));
}
static V L344(V *a) {
return F_Parser_dbind(F_P_dterm(), mk_clo(L345, 2, 1, (V[]){a[0]}));
}
static V L346(V *a) {
return F_Parser_dpure(C1(3, a[0]));
}
static V L347(V *a) {
return F_Parser_dpure(C1(1, a[0]));
}
static V L348(V *a) {
return F_Parser_dpure(C1(4, a[0]));
}
static V S349(void) { static V c; if (!c) c = MKS("("); return c; }
static V S350(void) { static V c; if (!c) c = MKS("["); return c; }
static V S351(void) { static V c; if (!c) c = MKS("{"); return c; }
static V S352(void) { static V c; if (!c) c = MKS("~"); return c; }
static V S353(void) { static V c; if (!c) c = MKS("+"); return c; }
static V S354(void) { static V c; if (!c) c = MKS("-"); return c; }
static V S355(void) { static V c; if (!c) c = MKS("@"); return c; }
static V S356(void) { static V c; if (!c) c = MKS("&"); return c; }
static V S357(void) { static V c; if (!c) c = MKS("\077"); return c; }
static V S358(void) { static V c; if (!c) c = MKS("expected an expression"); return c; }
static V S360(void) { static V c; if (!c) c = MKS(""); return c; }
static V L359(V *a) {
return F_Parser_dpure(C1(15, S360()));
}
static V F_P_dprimary_dk(V a0) {
top:;
V s339 = a0;
if (TAG(s339) == 0) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L340, 2, 1, (V[]){FLD(s339, 0)}));
} else if (TAG(s339) == 3) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L342, 2, 1, (V[]){FLD(s339, 0)}));
} else if (TAG(s339) == 1) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L343, 2, 1, (V[]){FLD(s339, 0)}));
} else if (TAG(s339) == 2) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L344, 2, 1, (V[]){FLD(s339, 0)}));
} else if (TAG(s339) == 4) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L346, 2, 1, (V[]){FLD(s339, 0)}));
} else if (TAG(s339) == 5) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L347, 2, 1, (V[]){FLD(s339, 0)}));
} else if (TAG(s339) == 6) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L348, 2, 1, (V[]){FLD(s339, 0)}));
} else if (TAG(s339) == 7) {
return F_P_dprimary_dsym(F_P_dwhich(FLD(s339, 0), C2(1, S349(), C2(1, S350(), C2(1, S351(), C2(1, S352(), C2(1, S353(), C2(1, S354(), C2(1, S355(), C2(1, S356(), C2(1, S357(), IMM(0))))))))))));
} else {
return F_Parser_dbind(F_P_derr(S358()), mk_clo(L359, 1, 0, 0));
}
}
static V W_P_dprimary_dk(V *a) { (void)a; return F_P_dprimary_dk(a[0]); }
static V L362(V *a) {
return F_P_dterm();
}
static V L363(V *a) {
return F_P_dterm();
}
static V L365(V *a) {
return F_Parser_dpure(F_P_dneg(a[0]));
}
static V L364(V *a) {
return F_Parser_dbind(F_P_dterm(), mk_clo(L365, 1, 0, 0));
}
static V L366(V *a) {
return F_P_ddep();
}
static V L368(V *a) {
return F_P_damp_dgo(a[0]);
}
static V L367(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L368, 1, 0, 0));
}
static V S371(void) { static V c; if (!c) c = MKS(""); return c; }
static V L370(V *a) {
return F_Parser_dpure(C2(14, S371(), IMM(0)));
}
static V L369(V *a) {
return F_Parser_dbind(F_P_dident(), mk_clo(L370, 1, 0, 0));
}
static V S372(void) { static V c; if (!c) c = MKS("unexpected symbol"); return c; }
static V S374(void) { static V c; if (!c) c = MKS(""); return c; }
static V L373(V *a) {
return F_Parser_dpure(C1(15, S374()));
}
static V F_P_dprimary_dsym(V a0) {
top:;
V s361 = a0;
if ((s361) == 0) {
return F_P_dparen();
} else if ((s361) == 1) {
return F_P_dbrack();
} else if ((s361) == 2) {
return F_P_dbrace();
} else if ((s361) == 3) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L362, 1, 0, 0));
} else if ((s361) == 4) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L363, 1, 0, 0));
} else if ((s361) == 5) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L364, 1, 0, 0));
} else if ((s361) == 6) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L366, 1, 0, 0));
} else if ((s361) == 7) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L367, 1, 0, 0));
} else if ((s361) == 8) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L369, 1, 0, 0));
} else if ((s361) >= 9) {
return F_Parser_dbind(F_P_derr(S372()), mk_clo(L373, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dprimary_dsym(V *a) { (void)a; return F_P_dprimary_dsym(a[0]); }
static V S377(void) { static V c; if (!c) c = MKS("#q"); return c; }
static V L376(V *a) {
return F_Parser_dpure(C2(14, S377(), IMM(0)));
}
static V F_P_damp_dgo(V a0) {
top:;
V s375 = a0;
if (TAG(FLD(s375, 0)) == 3) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L376, 1, 0, 0));
} else {
return F_P_ddep();
}
}
static V W_P_damp_dgo(V *a) { (void)a; return F_P_damp_dgo(a[0]); }
static V S378(void) { static V c; if (!c) c = MKS("-"); return c; }
static V S380(void) { static V c; if (!c) c = MKS("+"); return c; }
static V S383(void) { static V c; if (!c) c = MKS(":"); return c; }
static V S386(void) { static V c; if (!c) c = MKS(""); return c; }
static V L385(V *a) {
return F_Parser_dpure(C2(14, S386(), IMM(0)));
}
static V L384(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L385, 1, 0, 0));
}
static V L382(V *a) {
return F_Parser_dbind(F_P_dexpect(S383()), mk_clo(L384, 1, 0, 0));
}
static V L381(V *a) {
return F_Parser_dbind(F_P_dident(), mk_clo(L382, 1, 0, 0));
}
static V L379(V *a) {
return F_Parser_dbind(F_P_deat(S380()), mk_clo(L381, 1, 0, 0));
}
static V F_P_ddep(void) {
top:;
return F_Parser_dbind(F_P_deat(S378()), mk_clo(L379, 1, 0, 0));
}
static V W_P_ddep(V *a) { (void)a; return F_P_ddep(); }
static V S388(void) { static V c; if (!c) c = MKS("-"); return c; }
static V F_P_dneg(V a0) {
top:;
V s387 = a0;
if (TAG(s387) == 1) {
return C1(1, F_U32_dsub(0u, FLD(s387, 0)));
} else if (TAG(s387) == 3) {
return C1(3, F_String_dappend(S388(), FLD(s387, 0)));
} else {
return s387;
}
}
static V W_P_dneg(V *a) { (void)a; return F_P_dneg(a[0]); }
static V S391(void) { static V c; if (!c) c = MKS("=="); return c; }
static V L390(V *a) {
return F_P_dbrace_dgo(F_P_dtok__is(a[0], S391()));
}
static V L389(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L390, 1, 0, 0));
}
static V F_P_dbrace(void) {
top:;
return F_Parser_dbind(F_P_dskip(), mk_clo(L389, 1, 0, 0));
}
static V W_P_dbrace(V *a) { (void)a; return F_P_dbrace(); }
static V S394(void) { static V c; if (!c) c = MKS("}"); return c; }
static V S396(void) { static V c; if (!c) c = MKS(""); return c; }
static V L395(V *a) {
return F_Parser_dpure(C2(14, S396(), IMM(0)));
}
static V L393(V *a) {
return F_Parser_dbind(F_P_dexpect(S394()), mk_clo(L395, 1, 0, 0));
}
static V F_P_dbrace_dgo(V a0) {
top:;
V s392 = a0;
if ((s392) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L393, 1, 0, 0));
} else if ((s392) == IMM(0)) {
return F_P_dbrace_dbody();
} else { bend_fail("incomplete match"); }
}
static V W_P_dbrace_dgo(V *a) { (void)a; return F_P_dbrace_dgo(a[0]); }
static V S399(void) { static V c; if (!c) c = MKS("=="); return c; }
static V S400(void) { static V c; if (!c) c = MKS("!="); return c; }
static V S401(void) { static V c; if (!c) c = MKS(":"); return c; }
static V L398(V *a) {
return F_P_dbrace_dtail(a[0], F_P_dtok__which(a[1], C2(1, S399(), C2(1, S400(), C2(1, S401(), IMM(0))))));
}
static V L397(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L398, 2, 1, (V[]){a[0]}));
}
static V F_P_dbrace_dbody(void) {
top:;
return F_Parser_dbind(F_P_dexpr(), mk_clo(L397, 1, 0, 0));
}
static V W_P_dbrace_dbody(V *a) { (void)a; return F_P_dbrace_dbody(); }
static V S405(void) { static V c; if (!c) c = MKS(":"); return c; }
static V S408(void) { static V c; if (!c) c = MKS("}"); return c; }
static V S410(void) { static V c; if (!c) c = MKS(""); return c; }
static V L409(V *a) {
return F_Parser_dpure(C2(14, S410(), IMM(0)));
}
static V L407(V *a) {
return F_Parser_dbind(F_P_dexpect(S408()), mk_clo(L409, 1, 0, 0));
}
static V L406(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L407, 1, 0, 0));
}
static V L404(V *a) {
return F_Parser_dbind(F_P_dexpect(S405()), mk_clo(L406, 1, 0, 0));
}
static V L403(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L404, 1, 0, 0));
}
static V S413(void) { static V c; if (!c) c = MKS(":"); return c; }
static V S416(void) { static V c; if (!c) c = MKS("}"); return c; }
static V S418(void) { static V c; if (!c) c = MKS(""); return c; }
static V L417(V *a) {
return F_Parser_dpure(C2(14, S418(), IMM(0)));
}
static V L415(V *a) {
return F_Parser_dbind(F_P_dexpect(S416()), mk_clo(L417, 1, 0, 0));
}
static V L414(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L415, 1, 0, 0));
}
static V L412(V *a) {
return F_Parser_dbind(F_P_dexpect(S413()), mk_clo(L414, 1, 0, 0));
}
static V L411(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L412, 1, 0, 0));
}
static V S421(void) { static V c; if (!c) c = MKS("}"); return c; }
static V L422(V *a) {
return F_Parser_dpure(C2(13, a[1], F_P_dhead(a[0])));
}
static V L420(V *a) {
return F_Parser_dbind(F_P_dexpect(S421()), mk_clo(L422, 3, 2, (V[]){a[1], a[0]}));
}
static V L419(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L420, 2, 1, (V[]){a[0]}));
}
static V S423(void) { static V c; if (!c) c = MKS("}"); return c; }
static V L424(V *a) {
return F_Parser_dpure(a[0]);
}
static V F_P_dbrace_dtail(V a0, V a1) {
top:;
V s402 = a1;
if ((s402) == 0) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L403, 1, 0, 0));
} else if ((s402) == 1) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L411, 1, 0, 0));
} else if ((s402) == 2) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L419, 2, 1, (V[]){a0}));
} else if ((s402) >= 3) {
return F_Parser_dbind(F_P_dexpect(S423()), mk_clo(L424, 2, 1, (V[]){a0}));
} else { bend_fail("incomplete match"); }
}
static V W_P_dbrace_dtail(V *a) { (void)a; return F_P_dbrace_dtail(a[0], a[1]); }
static V S427(void) { static V c; if (!c) c = MKS("]"); return c; }
static V L426(V *a) {
return F_P_dbrack_dgo(F_P_dtok__is(a[0], S427()));
}
static V L425(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L426, 1, 0, 0));
}
static V F_P_dbrack(void) {
top:;
return F_Parser_dbind(F_P_dskip(), mk_clo(L425, 1, 0, 0));
}
static V W_P_dbrack(V *a) { (void)a; return F_P_dbrack(); }
static V S430(void) { static V c; if (!c) c = MKS("Nil"); return c; }
static V L429(V *a) {
return F_Parser_dpure(C2(6, S430(), IMM(0)));
}
static V F_P_dbrack_dgo(V a0) {
top:;
V s428 = a0;
if ((s428) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L429, 1, 0, 0));
} else if ((s428) == IMM(0)) {
return F_P_dbrack_dbody();
} else { bend_fail("incomplete match"); }
}
static V W_P_dbrack_dgo(V *a) { (void)a; return F_P_dbrack_dgo(a[0]); }
static V S433(void) { static V c; if (!c) c = MKS(":"); return c; }
static V L432(V *a) {
return F_P_dbrack_dtail(a[0], F_P_dtok__is(a[1], S433()));
}
static V L431(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L432, 2, 1, (V[]){a[0]}));
}
static V F_P_dbrack_dbody(void) {
top:;
return F_Parser_dbind(F_P_dexpr(), mk_clo(L431, 1, 0, 0));
}
static V W_P_dbrack_dbody(V *a) { (void)a; return F_P_dbrack_dbody(); }
static V S435(void) { static V c; if (!c) c = MKS(","); return c; }
static V S437(void) { static V c; if (!c) c = MKS("]"); return c; }
static V L438(V *a) {
return F_Parser_dpure(F_P_delist(C2(1, a[0], a[1])));
}
static V L436(V *a) {
return F_Parser_dbind(F_P_dlist(S437()), mk_clo(L438, 2, 1, (V[]){a[0]}));
}
static V F_P_dbrack_dtail(V a0, V a1) {
top:;
V s434 = a1;
if ((s434) == IMM(1)) {
return F_P_darr(a0);
} else if ((s434) == IMM(0)) {
return F_Parser_dbind(F_P_deat(S435()), mk_clo(L436, 2, 1, (V[]){a0}));
} else { bend_fail("incomplete match"); }
}
static V W_P_dbrack_dtail(V *a) { (void)a; return F_P_dbrack_dtail(a[0], a[1]); }
static V S440(void) { static V c; if (!c) c = MKS("Nil"); return c; }
static V S441(void) { static V c; if (!c) c = MKS("Con"); return c; }
static V F_P_delist(V a0) {
top:;
V s439 = a0;
if ((s439) == IMM(0)) {
return C2(6, S440(), IMM(0));
} else if (TAG(s439) == 1) {
return C2(6, S441(), C2(1, FLD(s439, 0), C2(1, F_P_delist(FLD(s439, 1)), IMM(0))));
} else { bend_fail("incomplete match"); }
}
static V W_P_delist(V *a) { (void)a; return F_P_delist(a[0]); }
static V S447(void) { static V c; if (!c) c = MKS("^"); return c; }
static V S449(void) { static V c; if (!c) c = MKS("]"); return c; }
static V S451(void) { static V c; if (!c) c = MKS("Array.new"); return c; }
static V S452(void) { static V c; if (!c) c = MKS(""); return c; }
static V L450(V *a) {
return F_Parser_dpure(C2(5, C1(0, S451()), C2(1, C2(14, S452(), IMM(0)), C2(1, a[1], C2(1, a[0], IMM(0))))));
}
static V L448(V *a) {
return F_Parser_dbind(F_P_dexpect(S449()), mk_clo(L450, 3, 2, (V[]){a[0], a[1]}));
}
static V L446(V *a) {
return F_Parser_dbind(F_P_darr_dsize(F_P_dtok__is(a[1], S447()), a[2]), mk_clo(L448, 2, 1, (V[]){a[0]}));
}
static V L445(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L446, 3, 2, (V[]){a[0], a[1]}));
}
static V L444(V *a) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L445, 3, 2, (V[]){a[0], a[1]}));
}
static V L443(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L444, 2, 1, (V[]){a[0]}));
}
static V L442(V *a) {
return F_Parser_dbind(F_P_dterm(), mk_clo(L443, 2, 1, (V[]){a[0]}));
}
static V F_P_darr(V a0) {
top:;
return F_Parser_dbind(F_P_dskip(), mk_clo(L442, 2, 1, (V[]){a0}));
}
static V W_P_darr(V *a) { (void)a; return F_P_darr(a[0]); }
static V F_P_darr_dsize(V a0, V a1) {
top:;
V s453 = a0;
if ((s453) == IMM(1)) {
return F_P_dterm();
} else if ((s453) == IMM(0)) {
return F_P_darr_dsize_dlit(a1);
} else { bend_fail("incomplete match"); }
}
static V W_P_darr_dsize(V *a) { (void)a; return F_P_darr_dsize(a[0], a[1]); }
static V L455(V *a) {
return F_Parser_dpure(C1(2, F_P_dlog2(a[0])));
}
static V S456(void) { static V c; if (!c) c = MKS("expected an array size"); return c; }
static V L457(V *a) {
return F_Parser_dpure(C1(2, 0u));
}
static V F_P_darr_dsize_dlit(V a0) {
top:;
V s454 = a0;
if (TAG(FLD(s454, 0)) == 1) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L455, 2, 1, (V[]){FLD(FLD(s454, 0), 0)}));
} else {
return F_Parser_dbind(F_P_derr(S456()), mk_clo(L457, 1, 0, 0));
}
}
static V W_P_darr_dsize_dlit(V *a) { (void)a; return F_P_darr_dsize_dlit(a[0]); }
static V F_P_dlog2(V a0) {
top:;
return F_U32_dfrom__nat(F_U32_dlog2(a0));
}
static V W_P_dlog2(V *a) { (void)a; return F_P_dlog2(a[0]); }
static V W_U32_dlog2(V *a) { (void)a; return F_U32_dlog2(a[0]); }
static V W_U32_dfrom__nat(V *a) { (void)a; return F_U32_dfrom__nat(a[0]); }
static V S460(void) { static V c; if (!c) c = MKS(")"); return c; }
static V L459(V *a) {
return F_P_dparen_dgo(F_P_dtok__is(a[0], S460()));
}
static V L458(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L459, 1, 0, 0));
}
static V F_P_dparen(void) {
top:;
return F_Parser_dbind(F_P_dskip(), mk_clo(L458, 1, 0, 0));
}
static V W_P_dparen(V *a) { (void)a; return F_P_dparen(); }
static V S463(void) { static V c; if (!c) c = MKS("Unit"); return c; }
static V L462(V *a) {
return F_Parser_dpure(C2(6, S463(), IMM(0)));
}
static V F_P_dparen_dgo(V a0) {
top:;
V s461 = a0;
if ((s461) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L462, 1, 0, 0));
} else if ((s461) == IMM(0)) {
return F_P_dparen_dbody();
} else { bend_fail("incomplete match"); }
}
static V W_P_dparen_dgo(V *a) { (void)a; return F_P_dparen_dgo(a[0]); }
static V S466(void) { static V c; if (!c) c = MKS(","); return c; }
static V S467(void) { static V c; if (!c) c = MKS(":"); return c; }
static V L465(V *a) {
return F_P_dparen_dtail(a[0], F_P_dtok__which(a[1], C2(1, S466(), C2(1, S467(), IMM(0)))));
}
static V L464(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L465, 2, 1, (V[]){a[0]}));
}
static V F_P_dparen_dbody(void) {
top:;
return F_Parser_dbind(F_P_dexpr(), mk_clo(L464, 1, 0, 0));
}
static V W_P_dparen_dbody(V *a) { (void)a; return F_P_dparen_dbody(); }
static V S470(void) { static V c; if (!c) c = MKS(")"); return c; }
static V L471(V *a) {
return F_Parser_dpure(F_P_dtuple(C2(1, a[0], a[1])));
}
static V L469(V *a) {
return F_Parser_dbind(F_P_dlist(S470()), mk_clo(L471, 2, 1, (V[]){a[0]}));
}
static V S474(void) { static V c; if (!c) c = MKS(")"); return c; }
static V L475(V *a) {
return F_Parser_dpure(C2(13, a[1], F_P_dhead(a[0])));
}
static V L473(V *a) {
return F_Parser_dbind(F_P_dexpect(S474()), mk_clo(L475, 3, 2, (V[]){a[1], a[0]}));
}
static V L472(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L473, 2, 1, (V[]){a[0]}));
}
static V S476(void) { static V c; if (!c) c = MKS(")"); return c; }
static V L477(V *a) {
return F_Parser_dpure(a[0]);
}
static V F_P_dparen_dtail(V a0, V a1) {
top:;
V s468 = a1;
if ((s468) == 0) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L469, 2, 1, (V[]){a0}));
} else if ((s468) == 1) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L472, 2, 1, (V[]){a0}));
} else if ((s468) >= 2) {
return F_Parser_dbind(F_P_dexpect(S476()), mk_clo(L477, 2, 1, (V[]){a0}));
} else { bend_fail("incomplete match"); }
}
static V W_P_dparen_dtail(V *a) { (void)a; return F_P_dparen_dtail(a[0], a[1]); }
static V S479(void) { static V c; if (!c) c = MKS("Unit"); return c; }
static V S480(void) { static V c; if (!c) c = MKS("Tuple"); return c; }
static V F_P_dtuple(V a0) {
top:;
V s478 = a0;
if ((s478) == IMM(0)) {
return C2(6, S479(), IMM(0));
} else if (TAG(s478) == 1 && (FLD(s478, 1)) == IMM(0)) {
return FLD(s478, 0);
} else if (TAG(s478) == 1) {
return C2(6, S480(), C2(1, FLD(s478, 0), C2(1, F_P_dtuple(FLD(s478, 1)), IMM(0))));
} else { bend_fail("incomplete match"); }
}
static V W_P_dtuple(V *a) { (void)a; return F_P_dtuple(a[0]); }
static V S481(void) { static V c; if (!c) c = MKS("{"); return c; }
static V S482(void) { static V c; if (!c) c = MKS("<"); return c; }
static V S483(void) { static V c; if (!c) c = MKS("=>"); return c; }
static V F_P_dafter__id(V a0, V a1) {
top:;
return F_P_dafter__id_dgo(a0, F_Bool_dpick(F_P_dtok__sp(a1), 3u, F_P_dtok__which(a1, C2(1, S481(), C2(1, S482(), IMM(0))))), F_P_dtok__is(a1, S483()));
}
static V W_P_dafter__id(V *a) { (void)a; return F_P_dafter__id(a[0], a[1]); }
static V L486(V *a) {
return F_Parser_dpure(C2(7, C1(0, a[0]), a[1]));
}
static V L485(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L486, 2, 1, (V[]){a[0]}));
}
static V F_P_dafter__id_dgo(V a0, V a1, V a2) {
top:;
V s484 = a2;
if ((s484) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L485, 2, 1, (V[]){a0}));
} else if ((s484) == IMM(0)) {
return F_P_dafter__id_dk(a0, a1);
} else { bend_fail("incomplete match"); }
}
static V W_P_dafter__id_dgo(V *a) { (void)a; return F_P_dafter__id_dgo(a[0], a[1], a[2]); }
static V S489(void) { static V c; if (!c) c = MKS("}"); return c; }
static V L490(V *a) {
return F_Parser_dpure(C2(6, a[0], a[1]));
}
static V L488(V *a) {
return F_Parser_dbind(F_P_dlist(S489()), mk_clo(L490, 2, 1, (V[]){a[0]}));
}
static V L492(V *a) {
return F_Parser_dpure(C2(14, a[0], a[1]));
}
static V L491(V *a) {
return F_Parser_dbind(F_P_dtyargs(), mk_clo(L492, 2, 1, (V[]){a[0]}));
}
static V F_P_dafter__id_dk(V a0, V a1) {
top:;
V s487 = a1;
if ((s487) == 0) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L488, 2, 1, (V[]){a0}));
} else if ((s487) == 1) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L491, 2, 1, (V[]){a0}));
} else if ((s487) >= 2) {
return F_Parser_dpure(C1(0, a0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dafter__id_dk(V *a) { (void)a; return F_P_dafter__id_dk(a[0], a[1]); }
static V L493(V *a) {
return F_P_dtyargs_dgo(a[0], F_P_dstuck(F_P_dtok__kind(a[0])));
}
static V F_P_dtyargs(void) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L493, 1, 0, 0));
}
static V W_P_dtyargs(V *a) { (void)a; return F_P_dtyargs(); }
static V F_P_dtyargs_dgo(V a0, V a1) {
top:;
V s494 = a1;
if ((s494) == IMM(1)) {
return F_Parser_dpure(IMM(0));
} else if ((s494) == IMM(0)) {
return F_P_dtyargs_dclose(F_P_dis__gt(a0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dtyargs_dgo(V *a) { (void)a; return F_P_dtyargs_dgo(a[0], a[1]); }
static V S495(void) { static V c; if (!c) c = MKS(">"); return c; }
static V S496(void) { static V c; if (!c) c = MKS(">>"); return c; }
static V S497(void) { static V c; if (!c) c = MKS(">="); return c; }
static V F_P_dis__gt(V a0) {
top:;
return F_Bool_dor(F_P_dtok__is(a0, S495()), F_Bool_dor(F_P_dtok__is(a0, S496()), F_P_dtok__is(a0, S497())));
}
static V W_P_dis__gt(V *a) { (void)a; return F_P_dis__gt(a[0]); }
static V L499(V *a) {
return F_Parser_dpure(IMM(0));
}
static V F_P_dtyargs_dclose(V a0) {
top:;
V s498 = a0;
if ((s498) == IMM(1)) {
return F_Parser_dbind(F_P_dgt(), mk_clo(L499, 1, 0, 0));
} else if ((s498) == IMM(0)) {
return F_P_dtyargs_ditem();
} else { bend_fail("incomplete match"); }
}
static V W_P_dtyargs_dclose(V *a) { (void)a; return F_P_dtyargs_dclose(a[0]); }
static V S501(void) { static V c; if (!c) c = MKS(","); return c; }
static V L503(V *a) {
return F_Parser_dpure(C2(1, a[0], a[1]));
}
static V L502(V *a) {
return F_Parser_dbind(F_P_dtyargs_dmore(a[1]), mk_clo(L503, 2, 1, (V[]){a[0]}));
}
static V L500(V *a) {
return F_Parser_dbind(F_P_deat(S501()), mk_clo(L502, 2, 1, (V[]){a[0]}));
}
static V F_P_dtyargs_ditem(void) {
top:;
return F_Parser_dbind(F_P_dexpr(), mk_clo(L500, 1, 0, 0));
}
static V W_P_dtyargs_ditem(V *a) { (void)a; return F_P_dtyargs_ditem(); }
static V L505(V *a) {
return F_Parser_dpure(IMM(0));
}
static V F_P_dtyargs_dmore(V a0) {
top:;
V s504 = a0;
if ((s504) == IMM(1)) {
return F_P_dtyargs();
} else if ((s504) == IMM(0)) {
return F_Parser_dbind(F_P_dgt(), mk_clo(L505, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dtyargs_dmore(V *a) { (void)a; return F_P_dtyargs_dmore(a[0]); }
static V L506(V *a) {
return F_P_dgt_dgo(a[0]);
}
static V F_P_dgt(void) {
top:;
return mk_clo(L506, 1, 0, 0);
}
static V W_P_dgt(V *a) { (void)a; return F_P_dgt(); }
static V S508(void) { static V c; if (!c) c = MKS(">"); return c; }
static V S509(void) { static V c; if (!c) c = MKS(">>"); return c; }
static V S510(void) { static V c; if (!c) c = MKS(">="); return c; }
static V S511(void) { static V c; if (!c) c = MKS("expected '>'"); return c; }
static V F_P_dgt_dgo(V a0) {
top:;
V s507 = a0;
if (TAG(s507) == 1 && TAG(FLD(FLD(s507, 0), 0)) == 7) {
return F_P_dgt_dif(FLD(FLD(FLD(s507, 0), 0), 0), FLD(FLD(s507, 0), 1), FLD(FLD(s507, 0), 2), FLD(s507, 1), F_P_dwhich(FLD(FLD(FLD(s507, 0), 0), 0), C2(1, S508(), C2(1, S509(), C2(1, S510(), IMM(0))))));
} else {
return F_P_derr_dgo(S511(), s507);
}
}
static V W_P_dgt_dgo(V *a) { (void)a; return F_P_dgt_dgo(a[0]); }
static V S513(void) { static V c; if (!c) c = MKS(">"); return c; }
static V S514(void) { static V c; if (!c) c = MKS("="); return c; }
static V S515(void) { static V c; if (!c) c = MKS("expected '>'"); return c; }
static V F_P_dgt_dif(V a0, V a1, V a2, V a3, V a4) {
top:;
V s512 = a4;
if ((s512) == 0) {
return C2(0, IMM(0), a3);
} else if ((s512) == 1) {
return C2(0, IMM(0), C2(1, C3(0, C1(7, S513()), IMM(0), a2), a3));
} else if ((s512) == 2) {
return C2(0, IMM(0), C2(1, C3(0, C1(7, S514()), IMM(0), a2), a3));
} else if ((s512) >= 3) {
return F_P_derr_dgo(S515(), C2(1, C3(0, C1(7, a0), a1, a2), a3));
} else { bend_fail("incomplete match"); }
}
static V W_P_dgt_dif(V *a) { (void)a; return F_P_dgt_dif(a[0], a[1], a[2], a[3], a[4]); }
static V F_P_dparam_dskip__mode(V a0) {
top:;
return F_P_dparam_dskip__mode_dgo(F_U32_dis__zero(a0));
}
static V W_P_dparam_dskip__mode(V *a) { (void)a; return F_P_dparam_dskip__mode(a[0]); }
static V F_P_dparam_dskip__mode_dgo(V a0) {
top:;
V s516 = a0;
if ((s516) == IMM(1)) {
return F_Parser_dpure(IMM(0));
} else if ((s516) == IMM(0)) {
return F_P_dskip();
} else { bend_fail("incomplete match"); }
}
static V W_P_dparam_dskip__mode_dgo(V *a) { (void)a; return F_P_dparam_dskip__mode_dgo(a[0]); }
static V S517(void) { static V c; if (!c) c = MKS("-"); return c; }
static V S518(void) { static V c; if (!c) c = MKS("+"); return c; }
static V S519(void) { static V c; if (!c) c = MKS("~"); return c; }
static V F_P_dparam_dmode(V a0) {
top:;
return F_Bool_dpick(F_P_dtok__is(a0, S517()), 1u, F_Bool_dpick(F_P_dtok__is(a0, S518()), 2u, F_Bool_dpick(F_P_dtok__is(a0, S519()), 3u, 0u)));
}
static V W_P_dparam_dmode(V *a) { (void)a; return F_P_dparam_dmode(a[0]); }
static V L520(V *a) {
return F_P_dnls_dif(F_P_dis__nl(a[0]));
}
static V F_P_dnls(void) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L520, 1, 0, 0));
}
static V W_P_dnls(V *a) { (void)a; return F_P_dnls(); }
static V F_P_dis__nl(V a0) {
top:;
V s521 = a0;
if ((FLD(s521, 0)) == IMM(8)) {
return IMM(1);
} else {
return IMM(0);
}
}
static V W_P_dis__nl(V *a) { (void)a; return F_P_dis__nl(a[0]); }
static V L523(V *a) {
return F_P_dnls();
}
static V F_P_dnls_dif(V a0) {
top:;
V s522 = a0;
if ((s522) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L523, 1, 0, 0));
} else if ((s522) == IMM(0)) {
return F_Parser_dpure(IMM(0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dnls_dif(V *a) { (void)a; return F_P_dnls_dif(a[0]); }
static V L524(V *a) {
return F_P_dexpect__in_dgo(F_P_dis__in(a[0]));
}
static V F_P_dexpect__in(void) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L524, 1, 0, 0));
}
static V W_P_dexpect__in(V *a) { (void)a; return F_P_dexpect__in(); }
static V F_P_dis__in(V a0) {
top:;
V s525 = a0;
if ((FLD(s525, 0)) == IMM(9)) {
return IMM(1);
} else {
return IMM(0);
}
}
static V W_P_dis__in(V *a) { (void)a; return F_P_dis__in(a[0]); }
static V S527(void) { static V c; if (!c) c = MKS("expected an indented block"); return c; }
static V F_P_dexpect__in_dgo(V a0) {
top:;
V s526 = a0;
if ((s526) == IMM(1)) {
return F_P_dskip();
} else if ((s526) == IMM(0)) {
return F_P_derr(S527());
} else { bend_fail("incomplete match"); }
}
static V W_P_dexpect__in_dgo(V *a) { (void)a; return F_P_dexpect__in_dgo(a[0]); }
static V S531(void) { static V c; if (!c) c = MKS("<"); return c; }
static V S532(void) { static V c; if (!c) c = MKS("<-"); return c; }
static V S536(void) { static V c; if (!c) c = MKS(":"); return c; }
static V L539(V *a) {
return F_Parser_dpure(C3(3, a[1], a[0], a[2]));
}
static V L538(V *a) {
return F_Parser_dbind(F_P_dtype_dbody(F_P_dis__in(a[2])), mk_clo(L539, 3, 2, (V[]){a[0], a[1]}));
}
static V L537(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L538, 3, 2, (V[]){a[0], a[1]}));
}
static V L535(V *a) {
return F_Parser_dbind(F_P_dexpect(S536()), mk_clo(L537, 3, 2, (V[]){a[0], a[1]}));
}
static V L534(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L535, 3, 2, (V[]){a[0], a[1]}));
}
static V L533(V *a) {
return F_Parser_dbind(F_P_duntil__is(), mk_clo(L534, 3, 2, (V[]){a[1], a[0]}));
}
static V L530(V *a) {
return F_Parser_dbind(F_P_dtparams_dopt(F_P_dtok__which(a[1], C2(1, S531(), C2(1, S532(), IMM(0))))), mk_clo(L533, 2, 1, (V[]){a[0]}));
}
static V L529(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L530, 2, 1, (V[]){a[0]}));
}
static V L528(V *a) {
return F_Parser_dbind(F_P_dident(), mk_clo(L529, 1, 0, 0));
}
static V F_P_dtype(void) {
top:;
return F_Parser_dbind(F_P_dskip(), mk_clo(L528, 1, 0, 0));
}
static V W_P_dtype(V *a) { (void)a; return F_P_dtype(); }
static V L541(V *a) {
return F_P_dctors();
}
static V F_P_dtype_dbody(V a0) {
top:;
V s540 = a0;
if ((s540) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L541, 1, 0, 0));
} else if ((s540) == IMM(0)) {
return F_Parser_dpure(IMM(0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dtype_dbody(V *a) { (void)a; return F_P_dtype_dbody(a[0]); }
static V L543(V *a) {
return F_P_dctors_dgo(a[0], F_Bool_dpick(F_P_dis__de(a[0]), 0u, F_Bool_dpick(F_P_dstuck(F_P_dtok__kind(a[0])), 1u, 2u)));
}
static V L542(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L543, 1, 0, 0));
}
static V F_P_dctors(void) {
top:;
return F_Parser_dbind(F_P_dnls(), mk_clo(L542, 1, 0, 0));
}
static V W_P_dctors(V *a) { (void)a; return F_P_dctors(); }
static V L545(V *a) {
return F_Parser_dpure(IMM(0));
}
static V S547(void) { static V c; if (!c) c = MKS("{"); return c; }
static V L550(V *a) {
return F_Parser_dpure(C2(1, C2(0, a[1], a[0]), a[2]));
}
static V L549(V *a) {
return F_Parser_dbind(F_P_dctors(), mk_clo(L550, 3, 2, (V[]){a[1], a[0]}));
}
static V L548(V *a) {
return F_Parser_dbind(F_P_dfields(), mk_clo(L549, 2, 1, (V[]){a[0]}));
}
static V L546(V *a) {
return F_Parser_dbind(F_P_dexpect(S547()), mk_clo(L548, 2, 1, (V[]){a[0]}));
}
static V F_P_dctors_dgo(V a0, V a1) {
top:;
V s544 = a1;
if ((s544) == 0) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L545, 1, 0, 0));
} else if ((s544) == 1) {
return F_Parser_dpure(IMM(0));
} else if ((s544) >= 2) {
return F_Parser_dbind(F_P_dident(), mk_clo(L546, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dctors_dgo(V *a) { (void)a; return F_P_dctors_dgo(a[0], a[1]); }
static V S552(void) { static V c; if (!c) c = MKS("}"); return c; }
static V L551(V *a) {
return F_P_dfields_dgo(F_Bool_dor(F_P_dtok__is(a[0], S552()), F_P_dstuck(F_P_dtok__kind(a[0]))));
}
static V F_P_dfields(void) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L551, 1, 0, 0));
}
static V W_P_dfields(V *a) { (void)a; return F_P_dfields(); }
static V L554(V *a) {
return F_Parser_dpure(IMM(0));
}
static V S555(void) { static V c; if (!c) c = MKS("+"); return c; }
static V S557(void) { static V c; if (!c) c = MKS("-"); return c; }
static V S560(void) { static V c; if (!c) c = MKS(":"); return c; }
static V S563(void) { static V c; if (!c) c = MKS(","); return c; }
static V L565(V *a) {
return F_Parser_dpure(C2(1, C2(0, a[1], a[0]), a[2]));
}
static V L564(V *a) {
return F_Parser_dbind(F_P_dfields(), mk_clo(L565, 3, 2, (V[]){a[0], a[1]}));
}
static V L562(V *a) {
return F_Parser_dbind(F_P_deat(S563()), mk_clo(L564, 3, 2, (V[]){a[1], a[0]}));
}
static V L561(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L562, 2, 1, (V[]){a[0]}));
}
static V L559(V *a) {
return F_Parser_dbind(F_P_dexpect(S560()), mk_clo(L561, 2, 1, (V[]){a[0]}));
}
static V L558(V *a) {
return F_Parser_dbind(F_P_dident(), mk_clo(L559, 1, 0, 0));
}
static V L556(V *a) {
return F_Parser_dbind(F_P_deat(S557()), mk_clo(L558, 1, 0, 0));
}
static V F_P_dfields_dgo(V a0) {
top:;
V s553 = a0;
if ((s553) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L554, 1, 0, 0));
} else if ((s553) == IMM(0)) {
return F_Parser_dbind(F_P_deat(S555()), mk_clo(L556, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dfields_dgo(V *a) { (void)a; return F_P_dfields_dgo(a[0]); }
static V L566(V *a) {
return C2(0, IMM(0), F_P_duntil__is_dgo(a[0]));
}
static V F_P_duntil__is(void) {
top:;
return mk_clo(L566, 1, 0, 0);
}
static V W_P_duntil__is(V *a) { (void)a; return F_P_duntil__is(); }
static V S568(void) { static V c; if (!c) c = MKS("is"); return c; }
static V F_P_duntil__is_dgo(V a0) {
top:;
V s567 = a0;
if ((s567) == IMM(0)) {
return IMM(0);
} else if (TAG(s567) == 1 && TAG(FLD(FLD(s567, 0), 0)) == 0) {
return F_P_duntil__is_dif(C3(0, C1(0, FLD(FLD(FLD(s567, 0), 0), 0)), FLD(FLD(s567, 0), 1), FLD(FLD(s567, 0), 2)), FLD(s567, 1), F_Str_deq(FLD(FLD(FLD(s567, 0), 0), 0), S568()));
} else if (TAG(s567) == 1 && (FLD(FLD(s567, 0), 0)) == IMM(11)) {
return C2(1, C3(0, IMM(11), FLD(FLD(s567, 0), 1), FLD(FLD(s567, 0), 2)), FLD(s567, 1));
} else if (TAG(s567) == 1 && TAG(FLD(FLD(s567, 0), 0)) == 12) {
return C2(1, C3(0, C1(12, FLD(FLD(FLD(s567, 0), 0), 0)), FLD(FLD(s567, 0), 1), FLD(FLD(s567, 0), 2)), FLD(s567, 1));
} else if (TAG(s567) == 1) {
{ V t0 = FLD(s567, 1); a0 = t0; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_P_duntil__is_dgo(V *a) { (void)a; return F_P_duntil__is_dgo(a[0]); }
static V F_P_duntil__is_dif(V a0, V a1, V a2) {
top:;
V s569 = a2;
if ((s569) == IMM(1)) {
return a1;
} else if ((s569) == IMM(0)) {
return F_P_duntil__is_dgo(a1);
} else { bend_fail("incomplete match"); }
}
static V W_P_duntil__is_dif(V *a) { (void)a; return F_P_duntil__is_dif(a[0], a[1], a[2]); }
static V L571(V *a) {
return F_P_dtparams();
}
static V L572(V *a) {
return F_P_dtparams();
}
static V F_P_dtparams_dopt(V a0) {
top:;
V s570 = a0;
if ((s570) == 0) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L571, 1, 0, 0));
} else if ((s570) == 1) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L572, 1, 0, 0));
} else if ((s570) >= 2) {
return F_Parser_dpure(IMM(0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dtparams_dopt(V *a) { (void)a; return F_P_dtparams_dopt(a[0]); }
static V S573(void) { static V c; if (!c) c = MKS("-"); return c; }
static V S577(void) { static V c; if (!c) c = MKS(","); return c; }
static V L579(V *a) {
return F_Parser_dpure(C2(1, a[0], a[1]));
}
static V L578(V *a) {
return F_Parser_dbind(F_P_dtparams_dmore(a[1]), mk_clo(L579, 2, 1, (V[]){a[0]}));
}
static V L576(V *a) {
return F_Parser_dbind(F_P_deat(S577()), mk_clo(L578, 2, 1, (V[]){a[0]}));
}
static V L575(V *a) {
return F_Parser_dbind(F_P_dskip__ann(), mk_clo(L576, 2, 1, (V[]){a[0]}));
}
static V L574(V *a) {
return F_Parser_dbind(F_P_dident(), mk_clo(L575, 1, 0, 0));
}
static V F_P_dtparams(void) {
top:;
return F_Parser_dbind(F_P_deat(S573()), mk_clo(L574, 1, 0, 0));
}
static V W_P_dtparams(V *a) { (void)a; return F_P_dtparams(); }
static V L581(V *a) {
return F_Parser_dpure(IMM(0));
}
static V F_P_dtparams_dmore(V a0) {
top:;
V s580 = a0;
if ((s580) == IMM(1)) {
return F_P_dtparams();
} else if ((s580) == IMM(0)) {
return F_Parser_dbind(F_P_dgt(), mk_clo(L581, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dtparams_dmore(V *a) { (void)a; return F_P_dtparams_dmore(a[0]); }
static V S583(void) { static V c; if (!c) c = MKS(":"); return c; }
static V L582(V *a) {
return F_P_dskip__ann_dgo(F_P_dtok__is(a[0], S583()));
}
static V F_P_dskip__ann(void) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L582, 1, 0, 0));
}
static V W_P_dskip__ann(V *a) { (void)a; return F_P_dskip__ann(); }
static V L586(V *a) {
return F_Parser_dpure(IMM(0));
}
static V L585(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L586, 1, 0, 0));
}
static V F_P_dskip__ann_dgo(V a0) {
top:;
V s584 = a0;
if ((s584) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L585, 1, 0, 0));
} else if ((s584) == IMM(0)) {
return F_Parser_dpure(IMM(0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dskip__ann_dgo(V *a) { (void)a; return F_P_dskip__ann_dgo(a[0]); }
static V S589(void) { static V c; if (!c) c = MKS("("); return c; }
static V S593(void) { static V c; if (!c) c = MKS("->"); return c; }
static V S595(void) { static V c; if (!c) c = MKS(":"); return c; }
static V S599(void) { static V c; if (!c) c = MKS("import"); return c; }
static V L598(V *a) {
return F_P_ddef_dbody(a[2], a[1], a[0], F_P_dtok__is__id(a[3], S599()));
}
static V L597(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L598, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V L596(V *a) {
return F_Parser_dbind(F_P_dexpect__in(), mk_clo(L597, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V L594(V *a) {
return F_Parser_dbind(F_P_dexpect(S595()), mk_clo(L596, 4, 3, (V[]){a[2], a[0], a[1]}));
}
static V L592(V *a) {
return F_Parser_dbind(F_P_dret_dgo(F_P_dtok__is(a[2], S593())), mk_clo(L594, 3, 2, (V[]){a[0], a[1]}));
}
static V L591(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L592, 3, 2, (V[]){a[1], a[0]}));
}
static V L590(V *a) {
return F_Parser_dbind(F_P_dparams(), mk_clo(L591, 2, 1, (V[]){a[0]}));
}
static V L588(V *a) {
return F_Parser_dbind(F_P_dexpect(S589()), mk_clo(L590, 2, 1, (V[]){a[0]}));
}
static V L587(V *a) {
return F_Parser_dbind(F_P_dident(), mk_clo(L588, 1, 0, 0));
}
static V F_P_ddef(void) {
top:;
return F_Parser_dbind(F_P_dskip(), mk_clo(L587, 1, 0, 0));
}
static V W_P_ddef(V *a) { (void)a; return F_P_ddef(); }
static V L603(V *a) {
return F_Parser_dpure(C2(1, a[1], a[0]));
}
static V L602(V *a) {
return F_Parser_dbind(F_P_dskip__rest(), mk_clo(L603, 3, 2, (V[]){a[0], a[1]}));
}
static V L601(V *a) {
return F_Parser_dbind(F_P_dnls(), mk_clo(L602, 3, 2, (V[]){a[0], a[1]}));
}
static V L604(V *a) {
return F_Parser_dpure(C4(0, a[2], a[1], F_Fold_dplain(a[3]), a[0]));
}
static V F_P_ddef_dbody(V a0, V a1, V a2, V a3) {
top:;
V s600 = a3;
if ((s600) == IMM(1)) {
return F_Parser_dbind(F_P_dskip__line(), mk_clo(L601, 3, 2, (V[]){a1, a0}));
} else if ((s600) == IMM(0)) {
return F_Parser_dbind(F_P_dstmts(), mk_clo(L604, 4, 3, (V[]){a2, a1, a0}));
} else { bend_fail("incomplete match"); }
}
static V W_P_ddef_dbody(V *a) { (void)a; return F_P_ddef_dbody(a[0], a[1], a[2], a[3]); }
static V S606(void) { static V c; if (!c) c = MKS("empty block"); return c; }
static V S607(void) { static V c; if (!c) c = MKS(""); return c; }
static V S608(void) { static V c; if (!c) c = MKS("_"); return c; }
static V F_Fold_dplain(V a0) {
top:;
V s605 = a0;
if ((s605) == IMM(0)) {
return C1(15, S606());
} else if (TAG(s605) == 1 && TAG(FLD(s605, 0)) == 0 && (FLD(s605, 1)) == IMM(0)) {
return FLD(FLD(s605, 0), 1);
} else if (TAG(s605) == 1 && TAG(FLD(s605, 0)) == 1 && (FLD(s605, 1)) == IMM(0)) {
return FLD(FLD(s605, 0), 1);
} else if (TAG(s605) == 1 && TAG(FLD(s605, 0)) == 2 && (FLD(s605, 1)) == IMM(0)) {
return FLD(FLD(s605, 0), 0);
} else if (TAG(s605) == 1 && TAG(FLD(s605, 0)) == 3 && (FLD(s605, 1)) == IMM(0)) {
return FLD(FLD(s605, 0), 0);
} else if (TAG(s605) == 1 && (FLD(s605, 0)) == IMM(4) && (FLD(s605, 1)) == IMM(0)) {
return C2(14, S607(), IMM(0));
} else if (TAG(s605) == 1 && TAG(FLD(s605, 0)) == 0) {
return C3(8, FLD(FLD(s605, 0), 0), FLD(FLD(s605, 0), 1), F_Fold_dplain(FLD(s605, 1)));
} else if (TAG(s605) == 1 && TAG(FLD(s605, 0)) == 1) {
return C3(8, C1(0, FLD(FLD(s605, 0), 0)), FLD(FLD(s605, 0), 1), F_Fold_dplain(FLD(s605, 1)));
} else if (TAG(s605) == 1 && TAG(FLD(s605, 0)) == 2) {
return FLD(FLD(s605, 0), 0);
} else if (TAG(s605) == 1 && TAG(FLD(s605, 0)) == 3) {
return C3(8, C1(0, S608()), FLD(FLD(s605, 0), 0), F_Fold_dplain(FLD(s605, 1)));
} else if (TAG(s605) == 1 && (FLD(s605, 0)) == IMM(4)) {
{ V t0 = FLD(s605, 1); a0 = t0; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Fold_dplain(V *a) { (void)a; return F_Fold_dplain(a[0]); }
static V L610(V *a) {
return F_P_dstmts_dgo(a[0], F_Bool_dpick(F_P_dis__de(a[0]), 0u, F_Bool_dpick(F_P_dstuck(F_P_dtok__kind(a[0])), 1u, 2u)));
}
static V L609(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L610, 1, 0, 0));
}
static V F_P_dstmts(void) {
top:;
return F_Parser_dbind(F_P_dnls(), mk_clo(L609, 1, 0, 0));
}
static V W_P_dstmts(V *a) { (void)a; return F_P_dstmts(); }
static V L612(V *a) {
return F_Parser_dpure(IMM(0));
}
static V L614(V *a) {
return F_Parser_dpure(F_List_dappend(a[0], a[1]));
}
static V L613(V *a) {
return F_Parser_dbind(F_P_dstmts(), mk_clo(L614, 2, 1, (V[]){a[0]}));
}
static V F_P_dstmts_dgo(V a0, V a1) {
top:;
V s611 = a1;
if ((s611) == 0) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L612, 1, 0, 0));
} else if ((s611) == 1) {
return F_Parser_dpure(IMM(0));
} else if ((s611) >= 2) {
return F_Parser_dbind(F_P_dstmt(), mk_clo(L613, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dstmts_dgo(V *a) { (void)a; return F_P_dstmts_dgo(a[0], a[1]); }
static V F_List_dappend(V a2, V a3) {
top:;
V s615 = a2;
if ((s615) == IMM(0)) {
return a3;
} else if (TAG(s615) == 1) {
return C2(1, FLD(s615, 0), F_List_dappend(FLD(s615, 1), a3));
} else { bend_fail("incomplete match"); }
}
static V W_List_dappend(V *a) { (void)a; return F_List_dappend(a[2], a[3]); }
static V S617(void) { static V c; if (!c) c = MKS("%"); return c; }
static V L616(V *a) {
return F_P_dstmt_dgo(a[0], F_P_dtok__is(a[0], S617()));
}
static V F_P_dstmt(void) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L616, 1, 0, 0));
}
static V W_P_dstmt(V *a) { (void)a; return F_P_dstmt(); }
static V L619(V *a) {
return F_Parser_dpure(C2(1, IMM(4), IMM(0)));
}
static V S620(void) { static V c; if (!c) c = MKS("match"); return c; }
static V S621(void) { static V c; if (!c) c = MKS("return"); return c; }
static V S622(void) { static V c; if (!c) c = MKS("do"); return c; }
static V F_P_dstmt_dgo(V a0, V a1) {
top:;
V s618 = a1;
if ((s618) == IMM(1)) {
return F_Parser_dbind(F_P_dskip__line(), mk_clo(L619, 1, 0, 0));
} else if ((s618) == IMM(0)) {
return F_P_dstmt_did(F_P_dtok__which__id(a0, C2(1, S620(), C2(1, S621(), C2(1, S622(), IMM(0))))));
} else { bend_fail("incomplete match"); }
}
static V W_P_dstmt_dgo(V *a) { (void)a; return F_P_dstmt_dgo(a[0], a[1]); }
static V L624(V *a) {
return F_Parser_dpure(C2(1, C1(3, a[0]), IMM(0)));
}
static V L626(V *a) {
return F_Parser_dpure(C2(1, C1(2, a[0]), IMM(0)));
}
static V L625(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L626, 1, 0, 0));
}
static V L627(V *a) {
return F_Parser_dpure(C2(1, C1(3, a[0]), IMM(0)));
}
static V L628(V *a) {
return F_P_dstmt_dscan(a[0]);
}
static V F_P_dstmt_did(V a0) {
top:;
V s623 = a0;
if ((s623) == 0) {
return F_Parser_dbind(F_P_dmatch(), mk_clo(L624, 1, 0, 0));
} else if ((s623) == 1) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L625, 1, 0, 0));
} else if ((s623) == 2) {
return F_Parser_dbind(F_P_ddo(), mk_clo(L627, 1, 0, 0));
} else if ((s623) >= 3) {
return F_Parser_dbind(F_P_dscan(), mk_clo(L628, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dstmt_did(V *a) { (void)a; return F_P_dstmt_did(a[0]); }
static V F_P_dstmt_dscan(V a0) {
top:;
return F_P_dstmt_dscan_dgo(F_U32_dto__nat(a0));
}
static V W_P_dstmt_dscan(V *a) { (void)a; return F_P_dstmt_dscan(a[0]); }
static V W_U32_dto__nat(V *a) { (void)a; return F_U32_dto__nat(a[0]); }
static V L630(V *a) {
return F_Parser_dpure(C2(1, C1(3, a[0]), IMM(0)));
}
static V F_P_dstmt_dscan_dgo(V a0) {
top:;
V s629 = a0;
if ((s629) == 0) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L630, 1, 0, 0));
} else if ((s629) == 1) {
return F_P_dlet__stmt();
} else if ((s629) >= 2) {
return F_P_dbind__stmt();
} else { bend_fail("incomplete match"); }
}
static V W_P_dstmt_dscan_dgo(V *a) { (void)a; return F_P_dstmt_dscan_dgo(a[0]); }
static V S631(void) { static V c; if (!c) c = MKS("+"); return c; }
static V S635(void) { static V c; if (!c) c = MKS("["); return c; }
static V L634(V *a) {
return F_P_dbind_darr(a[0], F_Bool_dand(F_P_dtok__is(a[1], S635()), F_Bool_dnot(F_P_dtok__sp(a[1]))));
}
static V L633(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L634, 2, 1, (V[]){a[0]}));
}
static V L632(V *a) {
return F_Parser_dbind(F_P_dident(), mk_clo(L633, 1, 0, 0));
}
static V F_P_dbind__stmt(void) {
top:;
return F_Parser_dbind(F_P_deat(S631()), mk_clo(L632, 1, 0, 0));
}
static V W_P_dbind__stmt(V *a) { (void)a; return F_P_dbind__stmt(); }
static V F_Bool_dnot(V a0) {
top:;
V s636 = a0;
if ((s636) == IMM(0)) {
return IMM(1);
} else if ((s636) == IMM(1)) {
return IMM(0);
} else { bend_fail("incomplete match"); }
}
static V W_Bool_dnot(V *a) { (void)a; return F_Bool_dnot(a[0]); }
static V S640(void) { static V c; if (!c) c = MKS("]"); return c; }
static V S642(void) { static V c; if (!c) c = MKS("<-"); return c; }
static V S645(void) { static V c; if (!c) c = MKS("Array.set"); return c; }
static V S646(void) { static V c; if (!c) c = MKS("U32"); return c; }
static V L644(V *a) {
return F_Parser_dpure(C2(1, C2(0, C1(0, a[1]), C2(5, C1(0, S645()), C2(1, C2(14, S646(), IMM(0)), C2(1, C1(0, a[1]), C2(1, a[0], C2(1, a[2], IMM(0))))))), IMM(0)));
}
static V L643(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L644, 3, 2, (V[]){a[0], a[1]}));
}
static V L641(V *a) {
return F_Parser_dbind(F_P_dexpect(S642()), mk_clo(L643, 3, 2, (V[]){a[0], a[1]}));
}
static V L639(V *a) {
return F_Parser_dbind(F_P_dexpect(S640()), mk_clo(L641, 3, 2, (V[]){a[1], a[0]}));
}
static V L638(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L639, 2, 1, (V[]){a[0]}));
}
static V S648(void) { static V c; if (!c) c = MKS("<-"); return c; }
static V L650(V *a) {
return F_Parser_dpure(C2(1, C2(1, a[0], a[1]), IMM(0)));
}
static V L649(V *a) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L650, 2, 1, (V[]){a[0]}));
}
static V L647(V *a) {
return F_Parser_dbind(F_P_dexpect(S648()), mk_clo(L649, 2, 1, (V[]){a[0]}));
}
static V F_P_dbind_darr(V a0, V a1) {
top:;
V s637 = a1;
if ((s637) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L638, 2, 1, (V[]){a0}));
} else if ((s637) == IMM(0)) {
return F_Parser_dbind(F_P_dskip__ann(), mk_clo(L647, 2, 1, (V[]){a0}));
} else { bend_fail("incomplete match"); }
}
static V W_P_dbind_darr(V *a) { (void)a; return F_P_dbind_darr(a[0], a[1]); }
static V S651(void) { static V c; if (!c) c = MKS("="); return c; }
static V S652(void) { static V c; if (!c) c = MKS(":"); return c; }
static V S655(void) { static V c; if (!c) c = MKS("="); return c; }
static V L657(V *a) {
return F_Parser_dpure(F_P_dlets(a[0], a[1]));
}
static V L656(V *a) {
return F_Parser_dbind(F_P_dexprs__n(F_List_dlength(a[0])), mk_clo(L657, 2, 1, (V[]){a[0]}));
}
static V L654(V *a) {
return F_Parser_dbind(F_P_dexpect(S655()), mk_clo(L656, 2, 1, (V[]){a[0]}));
}
static V L653(V *a) {
return F_Parser_dbind(F_P_dskip__ann(), mk_clo(L654, 2, 1, (V[]){a[0]}));
}
static V F_P_dlet__stmt(void) {
top:;
return F_Parser_dbind(F_P_dpat__seq(C2(1, S651(), C2(1, S652(), IMM(0)))), mk_clo(L653, 1, 0, 0));
}
static V W_P_dlet__stmt(V *a) { (void)a; return F_P_dlet__stmt(); }
static V F_P_dlets(V a0, V a1) {
top:;
V s658 = a0;
V s659 = a1;
if (TAG(s658) == 1 && TAG(s659) == 1) {
return C2(1, C2(0, FLD(s658, 0), FLD(s659, 0)), F_P_dlets(FLD(s658, 1), FLD(s659, 1)));
} else {
return IMM(0);
}
}
static V W_P_dlets(V *a) { (void)a; return F_P_dlets(a[0], a[1]); }
static V F_List_dlength(V a2) {
top:;
V s660 = a2;
if ((s660) == IMM(0)) {
return 0u;
} else if (TAG(s660) == 1) {
return (F_List_dlength(FLD(s660, 1)) + 1);
} else { bend_fail("incomplete match"); }
}
static V W_List_dlength(V *a) { (void)a; return F_List_dlength(a[2]); }
static V L663(V *a) {
return F_Parser_dpure(C2(1, a[0], a[1]));
}
static V L662(V *a) {
return F_Parser_dbind(F_P_dexprs__n(a[0]), mk_clo(L663, 2, 1, (V[]){a[1]}));
}
static V F_P_dexprs__n(V a0) {
top:;
V s661 = a0;
if ((s661) == 0) {
return F_Parser_dpure(IMM(0));
} else if ((s661) >= 1) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L662, 2, 1, (V[]){(s661 - 1)}));
} else { bend_fail("incomplete match"); }
}
static V W_P_dexprs__n(V *a) { (void)a; return F_P_dexprs__n(a[0]); }
static V L664(V *a) {
return F_P_dpat__seq_dgo(a[0], a[1], F_P_dpat__seq_dstop(a[0], a[1]));
}
static V F_P_dpat__seq(V a0) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L664, 2, 1, (V[]){a0}));
}
static V W_P_dpat__seq(V *a) { (void)a; return F_P_dpat__seq(a[0]); }
static V F_P_dpat__seq_dstop(V a0, V a1) {
top:;
return F_Bool_dor(F_P_dstuck(F_P_dtok__kind(a1)), F_Bool_dor(F_P_dis__nl(a1), F_Nat_dis__lt(F_P_dtok__which(a1, a0), F_List_dlength(a0))));
}
static V W_P_dpat__seq_dstop(V *a) { (void)a; return F_P_dpat__seq_dstop(a[0], a[1]); }
static V W_Nat_dis__lt(V *a) { (void)a; return F_Nat_dis__lt(a[0], a[1]); }
static V L667(V *a) {
return F_Parser_dpure(C2(1, a[0], a[1]));
}
static V L666(V *a) {
return F_Parser_dbind(F_P_dpat__seq(a[0]), mk_clo(L667, 2, 1, (V[]){a[1]}));
}
static V F_P_dpat__seq_dgo(V a0, V a1, V a2) {
top:;
V s665 = a2;
if ((s665) == IMM(1)) {
return F_Parser_dpure(IMM(0));
} else if ((s665) == IMM(0)) {
return F_Parser_dbind(F_P_dpat(), mk_clo(L666, 2, 1, (V[]){a0}));
} else { bend_fail("incomplete match"); }
}
static V W_P_dpat__seq_dgo(V *a) { (void)a; return F_P_dpat__seq_dgo(a[0], a[1], a[2]); }
static V S670(void) { static V c; if (!c) c = MKS("<>"); return c; }
static V L669(V *a) {
return F_P_dpat_dcons(a[0], F_P_dtok__is(a[1], S670()));
}
static V L668(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L669, 2, 1, (V[]){a[0]}));
}
static V F_P_dpat(void) {
top:;
return F_Parser_dbind(F_P_dpat1(), mk_clo(L668, 1, 0, 0));
}
static V W_P_dpat(V *a) { (void)a; return F_P_dpat(); }
static V S674(void) { static V c; if (!c) c = MKS("Con"); return c; }
static V L673(V *a) {
return F_Parser_dpure(C2(1, S674(), C2(1, a[0], C2(1, a[1], IMM(0)))));
}
static V L672(V *a) {
return F_Parser_dbind(F_P_dpat(), mk_clo(L673, 2, 1, (V[]){a[0]}));
}
static V F_P_dpat_dcons(V a0, V a1) {
top:;
V s671 = a1;
if ((s671) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L672, 2, 1, (V[]){a0}));
} else if ((s671) == IMM(0)) {
return F_Parser_dpure(a0);
} else { bend_fail("incomplete match"); }
}
static V W_P_dpat_dcons(V *a) { (void)a; return F_P_dpat_dcons(a[0], a[1]); }
static V L675(V *a) {
return F_P_dpat1_dk(F_P_dtok__kind(a[0]));
}
static V F_P_dpat1(void) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L675, 1, 0, 0));
}
static V W_P_dpat1(V *a) { (void)a; return F_P_dpat1(); }
static V S679(void) { static V c; if (!c) c = MKS("{"); return c; }
static V L678(V *a) {
return F_P_dpat_did(a[0], F_Bool_dand(F_P_dtok__is(a[1], S679()), F_Bool_dnot(F_P_dtok__sp(a[1]))));
}
static V L677(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L678, 2, 1, (V[]){a[0]}));
}
static V L680(V *a) {
return F_Parser_dpure(C1(2, a[0]));
}
static V L682(V *a) {
return F_Parser_dpure(C2(3, a[0], a[1]));
}
static V L681(V *a) {
return F_Parser_dbind(F_P_dpat1(), mk_clo(L682, 2, 1, (V[]){a[0]}));
}
static V L683(V *a) {
return F_Parser_dpure(C1(4, a[0]));
}
static V L684(V *a) {
return F_Parser_dpure(C1(4, a[0]));
}
static V L685(V *a) {
return F_Parser_dpure(F_P_dpstr(a[0]));
}
static V S686(void) { static V c; if (!c) c = MKS("+"); return c; }
static V S687(void) { static V c; if (!c) c = MKS("-"); return c; }
static V S688(void) { static V c; if (!c) c = MKS("("); return c; }
static V S689(void) { static V c; if (!c) c = MKS("["); return c; }
static V S690(void) { static V c; if (!c) c = MKS("expected a pattern"); return c; }
static V S692(void) { static V c; if (!c) c = MKS("_"); return c; }
static V L691(V *a) {
return F_Parser_dpure(C1(0, S692()));
}
static V F_P_dpat1_dk(V a0) {
top:;
V s676 = a0;
if (TAG(s676) == 0) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L677, 2, 1, (V[]){FLD(s676, 0)}));
} else if (TAG(s676) == 1) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L680, 2, 1, (V[]){FLD(s676, 0)}));
} else if (TAG(s676) == 2) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L681, 2, 1, (V[]){FLD(s676, 0)}));
} else if (TAG(s676) == 3) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L683, 2, 1, (V[]){FLD(s676, 0)}));
} else if (TAG(s676) == 5) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L684, 2, 1, (V[]){FLD(s676, 0)}));
} else if (TAG(s676) == 6) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L685, 2, 1, (V[]){FLD(s676, 0)}));
} else if (TAG(s676) == 7) {
return F_P_dpat_dsym(F_P_dwhich(FLD(s676, 0), C2(1, S686(), C2(1, S687(), C2(1, S688(), C2(1, S689(), IMM(0)))))));
} else {
return F_Parser_dbind(F_P_derr(S690()), mk_clo(L691, 1, 0, 0));
}
}
static V W_P_dpat1_dk(V *a) { (void)a; return F_P_dpat1_dk(a[0]); }
static V L694(V *a) {
return F_P_dpat1();
}
static V L695(V *a) {
return F_P_dpat1();
}
static V S697(void) { static V c; if (!c) c = MKS(")"); return c; }
static V L698(V *a) {
return F_Parser_dpure(F_P_dptuple(a[0]));
}
static V L696(V *a) {
return F_Parser_dbind(F_P_dpats(S697()), mk_clo(L698, 1, 0, 0));
}
static V S700(void) { static V c; if (!c) c = MKS("]"); return c; }
static V L701(V *a) {
return F_Parser_dpure(F_P_dplist(a[0]));
}
static V L699(V *a) {
return F_Parser_dbind(F_P_dpats(S700()), mk_clo(L701, 1, 0, 0));
}
static V S702(void) { static V c; if (!c) c = MKS("expected a pattern"); return c; }
static V S704(void) { static V c; if (!c) c = MKS("_"); return c; }
static V L703(V *a) {
return F_Parser_dpure(C1(0, S704()));
}
static V F_P_dpat_dsym(V a0) {
top:;
V s693 = a0;
if ((s693) == 0) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L694, 1, 0, 0));
} else if ((s693) == 1) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L695, 1, 0, 0));
} else if ((s693) == 2) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L696, 1, 0, 0));
} else if ((s693) == 3) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L699, 1, 0, 0));
} else if ((s693) >= 4) {
return F_Parser_dbind(F_P_derr(S702()), mk_clo(L703, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dpat_dsym(V *a) { (void)a; return F_P_dpat_dsym(a[0]); }
static V S706(void) { static V c; if (!c) c = MKS("Nil"); return c; }
static V S707(void) { static V c; if (!c) c = MKS("Con"); return c; }
static V F_P_dplist(V a0) {
top:;
V s705 = a0;
if ((s705) == IMM(0)) {
return C2(1, S706(), IMM(0));
} else if (TAG(s705) == 1) {
return C2(1, S707(), C2(1, FLD(s705, 0), C2(1, F_P_dplist(FLD(s705, 1)), IMM(0))));
} else { bend_fail("incomplete match"); }
}
static V W_P_dplist(V *a) { (void)a; return F_P_dplist(a[0]); }
static V L708(V *a) {
return F_P_dpats_dgo(a[0], a[1], F_P_dstuck(F_P_dtok__kind(a[1])));
}
static V F_P_dpats(V a0) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L708, 2, 1, (V[]){a0}));
}
static V W_P_dpats(V *a) { (void)a; return F_P_dpats(a[0]); }
static V F_P_dpats_dgo(V a0, V a1, V a2) {
top:;
V s709 = a2;
if ((s709) == IMM(1)) {
return F_Parser_dpure(IMM(0));
} else if ((s709) == IMM(0)) {
return F_P_dpats_dclose(a0, F_P_dtok__is(a1, a0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dpats_dgo(V *a) { (void)a; return F_P_dpats_dgo(a[0], a[1], a[2]); }
static V L711(V *a) {
return F_Parser_dpure(IMM(0));
}
static V F_P_dpats_dclose(V a0, V a1) {
top:;
V s710 = a1;
if ((s710) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L711, 1, 0, 0));
} else if ((s710) == IMM(0)) {
return F_P_dpats_ditem(a0);
} else { bend_fail("incomplete match"); }
}
static V W_P_dpats_dclose(V *a) { (void)a; return F_P_dpats_dclose(a[0], a[1]); }
static V S713(void) { static V c; if (!c) c = MKS(","); return c; }
static V L715(V *a) {
return F_Parser_dpure(C2(1, a[0], a[1]));
}
static V L714(V *a) {
return F_Parser_dbind(F_P_dpats_dmore(a[1], a[2]), mk_clo(L715, 2, 1, (V[]){a[0]}));
}
static V L712(V *a) {
return F_Parser_dbind(F_P_deat(S713()), mk_clo(L714, 3, 2, (V[]){a[1], a[0]}));
}
static V F_P_dpats_ditem(V a0) {
top:;
return F_Parser_dbind(F_P_dpat(), mk_clo(L712, 2, 1, (V[]){a0}));
}
static V W_P_dpats_ditem(V *a) { (void)a; return F_P_dpats_ditem(a[0]); }
static V L717(V *a) {
return F_Parser_dpure(IMM(0));
}
static V F_P_dpats_dmore(V a0, V a1) {
top:;
V s716 = a1;
if ((s716) == IMM(1)) {
return F_P_dpats(a0);
} else if ((s716) == IMM(0)) {
return F_Parser_dbind(F_P_dexpect(a0), mk_clo(L717, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dpats_dmore(V *a) { (void)a; return F_P_dpats_dmore(a[0], a[1]); }
static V S719(void) { static V c; if (!c) c = MKS("Unit"); return c; }
static V S720(void) { static V c; if (!c) c = MKS("Tuple"); return c; }
static V F_P_dptuple(V a0) {
top:;
V s718 = a0;
if ((s718) == IMM(0)) {
return C2(1, S719(), IMM(0));
} else if (TAG(s718) == 1 && (FLD(s718, 1)) == IMM(0)) {
return FLD(s718, 0);
} else if (TAG(s718) == 1) {
return C2(1, S720(), C2(1, FLD(s718, 0), C2(1, F_P_dptuple(FLD(s718, 1)), IMM(0))));
} else { bend_fail("incomplete match"); }
}
static V W_P_dptuple(V *a) { (void)a; return F_P_dptuple(a[0]); }
static V S722(void) { static V c; if (!c) c = MKS("SNil"); return c; }
static V S723(void) { static V c; if (!c) c = MKS("SCon"); return c; }
static V F_P_dpstr(V a0) {
top:;
V s721 = a0;
if ((s721) == IMM(0)) {
return C2(1, S722(), IMM(0));
} else if (TAG(s721) == 1) {
return C2(1, S723(), C2(1, C1(4, FLD(s721, 0)), C2(1, F_P_dpstr(FLD(s721, 1)), IMM(0))));
} else { bend_fail("incomplete match"); }
}
static V W_P_dpstr(V *a) { (void)a; return F_P_dpstr(a[0]); }
static V S726(void) { static V c; if (!c) c = MKS("}"); return c; }
static V L727(V *a) {
return F_Parser_dpure(C2(1, a[0], a[1]));
}
static V L725(V *a) {
return F_Parser_dbind(F_P_dpats(S726()), mk_clo(L727, 2, 1, (V[]){a[0]}));
}
static V F_P_dpat_did(V a0, V a1) {
top:;
V s724 = a1;
if ((s724) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L725, 2, 1, (V[]){a0}));
} else if ((s724) == IMM(0)) {
return F_Parser_dpure(C1(0, a0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dpat_did(V *a) { (void)a; return F_P_dpat_did(a[0], a[1]); }
static V L728(V *a) {
return F_P_dscan_dret(a[0]);
}
static V F_P_dscan(void) {
top:;
return mk_clo(L728, 1, 0, 0);
}
static V W_P_dscan(V *a) { (void)a; return F_P_dscan(); }
static V F_P_dscan_dret(V a0) {
top:;
return C2(0, F_P_dscan_dgo(a0, 0u), a0);
}
static V W_P_dscan_dret(V *a) { (void)a; return F_P_dscan_dret(a[0]); }
static V S730(void) { static V c; if (!c) c = MKS("="); return c; }
static V S731(void) { static V c; if (!c) c = MKS("<-"); return c; }
static V S732(void) { static V c; if (!c) c = MKS("("); return c; }
static V S733(void) { static V c; if (!c) c = MKS("["); return c; }
static V S734(void) { static V c; if (!c) c = MKS("{"); return c; }
static V S735(void) { static V c; if (!c) c = MKS(")"); return c; }
static V S736(void) { static V c; if (!c) c = MKS("]"); return c; }
static V S737(void) { static V c; if (!c) c = MKS("}"); return c; }
static V F_P_dscan_dgo(V a0, V a1) {
top:;
V s729 = a0;
if ((s729) == IMM(0)) {
return 0u;
} else if (TAG(s729) == 1 && TAG(FLD(FLD(s729, 0), 0)) == 7) {
return F_P_dscan_dsym(FLD(s729, 1), a1, F_P_dwhich(FLD(FLD(FLD(s729, 0), 0), 0), C2(1, S730(), C2(1, S731(), C2(1, S732(), C2(1, S733(), C2(1, S734(), C2(1, S735(), C2(1, S736(), C2(1, S737(), IMM(0)))))))))));
} else if (TAG(s729) == 1 && TAG(FLD(FLD(s729, 0), 0)) == 0) {
{ V t0 = FLD(s729, 1); V t1 = a1; a0 = t0; a1 = t1; goto top; }
} else if (TAG(s729) == 1 && (FLD(FLD(s729, 0), 0)) == IMM(8)) {
return F_P_dscan_dend(FLD(s729, 1), a1, F_U32_dis__zero(a1));
} else if (TAG(s729) == 1 && (FLD(FLD(s729, 0), 0)) == IMM(9)) {
return 0u;
} else if (TAG(s729) == 1 && (FLD(FLD(s729, 0), 0)) == IMM(10)) {
return 0u;
} else if (TAG(s729) == 1 && (FLD(FLD(s729, 0), 0)) == IMM(11)) {
return 0u;
} else if (TAG(s729) == 1 && TAG(FLD(FLD(s729, 0), 0)) == 12) {
return 0u;
} else if (TAG(s729) == 1) {
{ V t0 = FLD(s729, 1); V t1 = a1; a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_P_dscan_dgo(V *a) { (void)a; return F_P_dscan_dgo(a[0], a[1]); }
static V F_P_dscan_dend(V a0, V a1, V a2) {
top:;
V s738 = a2;
if ((s738) == IMM(1)) {
return 0u;
} else if ((s738) == IMM(0)) {
return F_P_dscan_dgo(a0, a1);
} else { bend_fail("incomplete match"); }
}
static V W_P_dscan_dend(V *a) { (void)a; return F_P_dscan_dend(a[0], a[1], a[2]); }
static V F_P_dscan_dsym(V a0, V a1, V a2) {
top:;
V s739 = a2;
if ((s739) == 0) {
return F_P_dscan_dtop(a0, a1, 1u, F_U32_dis__zero(a1));
} else if ((s739) == 1) {
return F_P_dscan_dtop(a0, a1, 2u, F_U32_dis__zero(a1));
} else if ((s739) == 2) {
return F_P_dscan_dgo(a0, F_U32_dinc(a1));
} else if ((s739) == 3) {
return F_P_dscan_dgo(a0, F_U32_dinc(a1));
} else if ((s739) == 4) {
return F_P_dscan_dgo(a0, F_U32_dinc(a1));
} else if ((s739) == 5) {
return F_P_dscan_dgo(a0, F_U32_dsub(a1, 1u));
} else if ((s739) == 6) {
return F_P_dscan_dgo(a0, F_U32_dsub(a1, 1u));
} else if ((s739) == 7) {
return F_P_dscan_dgo(a0, F_U32_dsub(a1, 1u));
} else if ((s739) >= 8) {
return F_P_dscan_dgo(a0, a1);
} else { bend_fail("incomplete match"); }
}
static V W_P_dscan_dsym(V *a) { (void)a; return F_P_dscan_dsym(a[0], a[1], a[2]); }
static V F_P_dscan_dtop(V a0, V a1, V a2, V a3) {
top:;
V s740 = a3;
if ((s740) == IMM(1)) {
return a2;
} else if ((s740) == IMM(0)) {
return F_P_dscan_dgo(a0, a1);
} else { bend_fail("incomplete match"); }
}
static V W_P_dscan_dtop(V *a) { (void)a; return F_P_dscan_dtop(a[0], a[1], a[2], a[3]); }
static V S743(void) { static V c; if (!c) c = MKS("<"); return c; }
static V S746(void) { static V c; if (!c) c = MKS(":"); return c; }
static V L749(V *a) {
return F_Parser_dpure(F_Fold_ddo(a[1], F_P_dinit(a[0]), F_P_dlast(a[0]), a[2]));
}
static V L748(V *a) {
return F_Parser_dbind(F_P_dstmts(), mk_clo(L749, 3, 2, (V[]){a[0], a[1]}));
}
static V L747(V *a) {
return F_Parser_dbind(F_P_dexpect__in(), mk_clo(L748, 3, 2, (V[]){a[0], a[1]}));
}
static V L745(V *a) {
return F_Parser_dbind(F_P_dexpect(S746()), mk_clo(L747, 3, 2, (V[]){a[1], a[0]}));
}
static V L744(V *a) {
return F_Parser_dbind(F_P_dtyargs(), mk_clo(L745, 2, 1, (V[]){a[0]}));
}
static V L742(V *a) {
return F_Parser_dbind(F_P_dexpect(S743()), mk_clo(L744, 2, 1, (V[]){a[0]}));
}
static V L741(V *a) {
return F_Parser_dbind(F_P_dident(), mk_clo(L742, 1, 0, 0));
}
static V F_P_ddo(void) {
top:;
return F_Parser_dbind(F_P_dskip(), mk_clo(L741, 1, 0, 0));
}
static V W_P_ddo(V *a) { (void)a; return F_P_ddo(); }
static V S751(void) { static V c; if (!c) c = MKS(""); return c; }
static V F_P_dlast(V a0) {
top:;
V s750 = a0;
if ((s750) == IMM(0)) {
return C2(14, S751(), IMM(0));
} else if (TAG(s750) == 1 && (FLD(s750, 1)) == IMM(0)) {
return FLD(s750, 0);
} else if (TAG(s750) == 1) {
{ V t0 = FLD(s750, 1); a0 = t0; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_P_dlast(V *a) { (void)a; return F_P_dlast(a[0]); }
static V F_P_dinit(V a0) {
top:;
V s752 = a0;
if ((s752) == IMM(0)) {
return IMM(0);
} else if (TAG(s752) == 1 && (FLD(s752, 1)) == IMM(0)) {
return IMM(0);
} else if (TAG(s752) == 1) {
return C2(1, FLD(s752, 0), F_P_dinit(FLD(s752, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_P_dinit(V *a) { (void)a; return F_P_dinit(a[0]); }
static V S754(void) { static V c; if (!c) c = MKS("empty do block"); return c; }
static V S755(void) { static V c; if (!c) c = MKS("pure"); return c; }
static V S756(void) { static V c; if (!c) c = MKS(""); return c; }
static V S757(void) { static V c; if (!c) c = MKS("bind"); return c; }
static V S758(void) { static V c; if (!c) c = MKS(""); return c; }
static V S759(void) { static V c; if (!c) c = MKS("pure"); return c; }
static V S760(void) { static V c; if (!c) c = MKS("bind"); return c; }
static V S761(void) { static V c; if (!c) c = MKS(""); return c; }
static V S762(void) { static V c; if (!c) c = MKS("_"); return c; }
static V F_Fold_ddo(V a0, V a1, V a2, V a3) {
top:;
V s753 = a3;
if ((s753) == IMM(0)) {
return C1(15, S754());
} else if (TAG(s753) == 1 && TAG(FLD(s753, 0)) == 0 && (FLD(s753, 1)) == IMM(0)) {
return FLD(FLD(s753, 0), 1);
} else if (TAG(s753) == 1 && TAG(FLD(s753, 0)) == 1 && (FLD(s753, 1)) == IMM(0)) {
return FLD(FLD(s753, 0), 1);
} else if (TAG(s753) == 1 && TAG(FLD(s753, 0)) == 2 && (FLD(s753, 1)) == IMM(0)) {
return F_Fold_dapp(a0, S755(), a1, C2(1, a2, C2(1, FLD(FLD(s753, 0), 0), IMM(0))));
} else if (TAG(s753) == 1 && TAG(FLD(s753, 0)) == 3 && (FLD(s753, 1)) == IMM(0)) {
return FLD(FLD(s753, 0), 0);
} else if (TAG(s753) == 1 && (FLD(s753, 0)) == IMM(4) && (FLD(s753, 1)) == IMM(0)) {
return C2(14, S756(), IMM(0));
} else if (TAG(s753) == 1 && TAG(FLD(s753, 0)) == 0) {
return C3(8, FLD(FLD(s753, 0), 0), FLD(FLD(s753, 0), 1), F_Fold_ddo(a0, a1, a2, FLD(s753, 1)));
} else if (TAG(s753) == 1 && TAG(FLD(s753, 0)) == 1) {
return F_Fold_dapp(a0, S757(), a1, C2(1, C2(14, S758(), IMM(0)), C2(1, a2, C2(1, FLD(FLD(s753, 0), 1), C2(1, C2(7, C1(0, FLD(FLD(s753, 0), 0)), F_Fold_ddo(a0, a1, a2, FLD(s753, 1))), IMM(0))))));
} else if (TAG(s753) == 1 && TAG(FLD(s753, 0)) == 2) {
return F_Fold_dapp(a0, S759(), a1, C2(1, a2, C2(1, FLD(FLD(s753, 0), 0), IMM(0))));
} else if (TAG(s753) == 1 && TAG(FLD(s753, 0)) == 3) {
return F_Fold_dapp(a0, S760(), a1, C2(1, C2(14, S761(), IMM(0)), C2(1, a2, C2(1, FLD(FLD(s753, 0), 0), C2(1, C2(7, C1(0, S762()), F_Fold_ddo(a0, a1, a2, FLD(s753, 1))), IMM(0))))));
} else if (TAG(s753) == 1 && (FLD(s753, 0)) == IMM(4)) {
{ V t0 = a0; V t1 = a1; V t2 = a2; V t3 = FLD(s753, 1); a0 = t0; a1 = t1; a2 = t2; a3 = t3; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Fold_ddo(V *a) { (void)a; return F_Fold_ddo(a[0], a[1], a[2], a[3]); }
static V S763(void) { static V c; if (!c) c = MKS("."); return c; }
static V F_Fold_dapp(V a0, V a1, V a2, V a3) {
top:;
return C2(5, C1(0, F_String_dappend(a0, F_String_dappend(S763(), a1))), F_List_dappend(a2, a3));
}
static V W_Fold_dapp(V *a) { (void)a; return F_Fold_dapp(a[0], a[1], a[2], a[3]); }
static V S766(void) { static V c; if (!c) c = MKS(":"); return c; }
static V L769(V *a) {
return F_Parser_dpure(C2(9, a[0], a[1]));
}
static V L768(V *a) {
return F_Parser_dbind(F_P_dmatch_dbody(F_P_dis__in(a[1])), mk_clo(L769, 2, 1, (V[]){a[0]}));
}
static V L767(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L768, 2, 1, (V[]){a[0]}));
}
static V L765(V *a) {
return F_Parser_dbind(F_P_dexpect(S766()), mk_clo(L767, 2, 1, (V[]){a[0]}));
}
static V L764(V *a) {
return F_Parser_dbind(F_P_dscrs(), mk_clo(L765, 1, 0, 0));
}
static V F_P_dmatch(void) {
top:;
return F_Parser_dbind(F_P_dskip(), mk_clo(L764, 1, 0, 0));
}
static V W_P_dmatch(V *a) { (void)a; return F_P_dmatch(); }
static V L771(V *a) {
return F_P_dcases();
}
static V F_P_dmatch_dbody(V a0) {
top:;
V s770 = a0;
if ((s770) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L771, 1, 0, 0));
} else if ((s770) == IMM(0)) {
return F_Parser_dpure(IMM(0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dmatch_dbody(V *a) { (void)a; return F_P_dmatch_dbody(a[0]); }
static V L773(V *a) {
return F_P_dcases_dde(F_P_dis__de(a[0]));
}
static V L772(V *a) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L773, 1, 0, 0));
}
static V F_P_dcases(void) {
top:;
return F_Parser_dbind(F_P_dnls(), mk_clo(L772, 1, 0, 0));
}
static V W_P_dcases(V *a) { (void)a; return F_P_dcases(); }
static V L775(V *a) {
return F_Parser_dpure(IMM(0));
}
static V S777(void) { static V c; if (!c) c = MKS("case"); return c; }
static V L776(V *a) {
return F_P_dcases_dgo(F_P_dtok__which__id(a[0], C2(1, S777(), IMM(0))));
}
static V F_P_dcases_dde(V a0) {
top:;
V s774 = a0;
if ((s774) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L775, 1, 0, 0));
} else if ((s774) == IMM(0)) {
return F_Parser_dbind(F_P_dpeek(), mk_clo(L776, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dcases_dde(V *a) { (void)a; return F_P_dcases_dde(a[0]); }
static V S780(void) { static V c; if (!c) c = MKS(":"); return c; }
static V S782(void) { static V c; if (!c) c = MKS(":"); return c; }
static V L785(V *a) {
return F_Parser_dpure(C2(1, C2(10, a[1], a[0]), a[2]));
}
static V L784(V *a) {
return F_Parser_dbind(F_P_dcases(), mk_clo(L785, 3, 2, (V[]){a[1], a[0]}));
}
static V L783(V *a) {
return F_Parser_dbind(F_P_dbody(), mk_clo(L784, 2, 1, (V[]){a[0]}));
}
static V L781(V *a) {
return F_Parser_dbind(F_P_dexpect(S782()), mk_clo(L783, 2, 1, (V[]){a[0]}));
}
static V L779(V *a) {
return F_Parser_dbind(F_P_dpat__seq(C2(1, S780(), IMM(0))), mk_clo(L781, 1, 0, 0));
}
static V F_P_dcases_dgo(V a0) {
top:;
V s778 = a0;
if ((s778) == 0) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L779, 1, 0, 0));
} else if ((s778) >= 1) {
return F_Parser_dpure(IMM(0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dcases_dgo(V *a) { (void)a; return F_P_dcases_dgo(a[0]); }
static V L787(V *a) {
return F_Parser_dpure(F_Fold_dplain(a[0]));
}
static V L786(V *a) {
return F_Parser_dbind(F_P_dstmts(), mk_clo(L787, 1, 0, 0));
}
static V F_P_dbody(void) {
top:;
return F_Parser_dbind(F_P_dexpect__in(), mk_clo(L786, 1, 0, 0));
}
static V W_P_dbody(V *a) { (void)a; return F_P_dbody(); }
static V S789(void) { static V c; if (!c) c = MKS(":"); return c; }
static V L788(V *a) {
return F_P_dscrs_dgo(a[0], F_Bool_dor(F_P_dtok__is(a[0], S789()), F_P_dstuck(F_P_dtok__kind(a[0]))));
}
static V F_P_dscrs(void) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L788, 1, 0, 0));
}
static V W_P_dscrs(V *a) { (void)a; return F_P_dscrs(); }
static V L792(V *a) {
return F_Parser_dpure(C2(1, a[0], a[1]));
}
static V L791(V *a) {
return F_Parser_dbind(F_P_dscrs(), mk_clo(L792, 2, 1, (V[]){a[0]}));
}
static V F_P_dscrs_dgo(V a0, V a1) {
top:;
V s790 = a1;
if ((s790) == IMM(1)) {
return F_Parser_dpure(IMM(0));
} else if ((s790) == IMM(0)) {
return F_Parser_dbind(F_P_dexpr(), mk_clo(L791, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dscrs_dgo(V *a) { (void)a; return F_P_dscrs_dgo(a[0], a[1]); }
static V L793(V *a) {
return C2(0, IMM(0), F_P_dskip__block_dgo(a[0], 1u));
}
static V F_P_dskip__rest(void) {
top:;
return mk_clo(L793, 1, 0, 0);
}
static V W_P_dskip__rest(V *a) { (void)a; return F_P_dskip__rest(); }
static V L795(V *a) {
return F_P_dexpr();
}
static V S796(void) { static V c; if (!c) c = MKS(""); return c; }
static V F_P_dret_dgo(V a0) {
top:;
V s794 = a0;
if ((s794) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L795, 1, 0, 0));
} else if ((s794) == IMM(0)) {
return F_Parser_dpure(C2(14, S796(), IMM(0)));
} else { bend_fail("incomplete match"); }
}
static V W_P_dret_dgo(V *a) { (void)a; return F_P_dret_dgo(a[0]); }
static V S798(void) { static V c; if (!c) c = MKS(")"); return c; }
static V L797(V *a) {
return F_P_dparams_dgo(F_Bool_dor(F_P_dtok__is(a[0], S798()), F_P_dstuck(F_P_dtok__kind(a[0]))));
}
static V F_P_dparams(void) {
top:;
return F_Parser_dbind(F_P_dpeek(), mk_clo(L797, 1, 0, 0));
}
static V W_P_dparams(V *a) { (void)a; return F_P_dparams(); }
static V L800(V *a) {
return F_Parser_dpure(IMM(0));
}
static V S802(void) { static V c; if (!c) c = MKS(","); return c; }
static V L804(V *a) {
return F_Parser_dpure(C2(1, a[0], a[1]));
}
static V L803(V *a) {
return F_Parser_dbind(F_P_dparams_dmore(a[1]), mk_clo(L804, 2, 1, (V[]){a[0]}));
}
static V L801(V *a) {
return F_Parser_dbind(F_P_deat(S802()), mk_clo(L803, 2, 1, (V[]){a[0]}));
}
static V F_P_dparams_dgo(V a0) {
top:;
V s799 = a0;
if ((s799) == IMM(1)) {
return F_Parser_dbind(F_P_dskip(), mk_clo(L800, 1, 0, 0));
} else if ((s799) == IMM(0)) {
return F_Parser_dbind(F_P_dparam(), mk_clo(L801, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dparams_dgo(V *a) { (void)a; return F_P_dparams_dgo(a[0]); }
static V S806(void) { static V c; if (!c) c = MKS(")"); return c; }
static V L807(V *a) {
return F_Parser_dpure(IMM(0));
}
static V F_P_dparams_dmore(V a0) {
top:;
V s805 = a0;
if ((s805) == IMM(1)) {
return F_P_dparams();
} else if ((s805) == IMM(0)) {
return F_Parser_dbind(F_P_dexpect(S806()), mk_clo(L807, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_P_dparams_dmore(V *a) { (void)a; return F_P_dparams_dmore(a[0]); }
static V F_P_dfile_dfin(V a0) {
top:;
V v808 = a0;
return C2(0, FLD(v808, 0), F_P_dfile_derr(FLD(v808, 1)));
}
static V W_P_dfile_dfin(V *a) { (void)a; return F_P_dfile_dfin(a[0]); }
static V S810(void) { static V c; if (!c) c = MKS(""); return c; }
static V F_P_dfile_derr(V a0) {
top:;
V s809 = a0;
if (TAG(s809) == 1 && TAG(FLD(FLD(s809, 0), 0)) == 12) {
return FLD(FLD(FLD(s809, 0), 0), 0);
} else {
return S810();
}
}
static V W_P_dfile_derr(V *a) { (void)a; return F_P_dfile_derr(a[0]); }
static V F_Main_dparse_dfin(V a0) {
top:;
V v811 = a0;
return F_Bool_dpick(F_String_dis__empty(FLD(v811, 1)), C1(1, FLD(v811, 0)), C1(0, FLD(v811, 1)));
}
static V W_Main_dparse_dfin(V *a) { (void)a; return F_Main_dparse_dfin(a[0]); }
static V F_String_dis__empty(V a0) {
top:;
V s812 = a0;
if ((s812) == IMM(0)) {
return IMM(1);
} else if (TAG(s812) == 1) {
return IMM(0);
} else { bend_fail("incomplete match"); }
}
static V W_String_dis__empty(V *a) { (void)a; return F_String_dis__empty(a[0]); }
static V S815(void) { static V c; if (!c) c = MKS("bendc: parse error in base: "); return c; }
static V S816(void) { static V c; if (!c) c = MKS("bendc: parse error: "); return c; }
static V F_Main_dcompile(V a0, V a1) {
top:;
V s813 = a0;
V s814 = a1;
if (TAG(s813) == 0) {
return F_IO_ddie(1u, F_String_dappend(S815(), FLD(s813, 0)));
} else if (TAG(s813) == 1 && TAG(s814) == 0) {
return F_IO_ddie(1u, F_String_dappend(S816(), FLD(s814, 0)));
} else if (TAG(s813) == 1 && TAG(s814) == 1) {
return F_Main_demit(F_Gen_dprogram(F_List_dappend(FLD(s813, 0), FLD(s814, 0))));
} else { bend_fail("incomplete match"); }
}
static V W_Main_dcompile(V *a) { (void)a; return F_Main_dcompile(a[0], a[1]); }
static V F_Gen_dprogram(V a0) {
top:;
V v817 = F_G_dnew(a0);
return F_Gen_dprogram_dfin(apply(F_Gen_dprogram_dm(v817), CN(0, 6, (V[]){0u, IMM(0), IMM(0), IMM(0), IMM(0), IMM(0)})));
}
static V W_Gen_dprogram(V *a) { (void)a; return F_Gen_dprogram(a[0]); }
static V S818(void) { static V c; if (!c) c = MKS("main"); return c; }
static V S820(void) { static V c; if (!c) c = MKS("main"); return c; }
static V L819(V *a) {
return F_Gen_dentry(a[0], F_G_dbody(a[0], S820()));
}
static V F_Gen_dprogram_dm(V a0) {
top:;
return F_Gen_dbind(F_Gen_dall(a0, C2(1, S818(), IMM(0)), F_Set_dnew()), mk_clo(L819, 2, 1, (V[]){a0}));
}
static V W_Gen_dprogram_dm(V *a) { (void)a; return F_Gen_dprogram_dm(a[0]); }
static V S822(void) { static V c; if (!c) c = MKS(""); return c; }
static V S823(void) { static V c; if (!c) c = MKS(""); return c; }
static V F_G_dbody(V a0, V a1) {
top:;
V v821 = a0;
return F_G_dget(C2(4, S822(), S823()), FLD(v821, 2), a1);
}
static V W_G_dbody(V *a) { (void)a; return F_G_dbody(a[0], a[1]); }
static V F_G_dget(V a1, V a2, V a3) {
top:;
return F_Pair_dsnd(F_Map_dget(a1, a2, a3));
}
static V W_G_dget(V *a) { (void)a; return F_G_dget(a[1], a[2], a[3]); }
static V F_Map_dget(V a1, V a2, V a3) {
top:;
V s824 = a2;
if ((s824) == IMM(0)) {
return C2(0, IMM(0), a1);
} else if (TAG(s824) == 1) {
return F_Map_dget_dleaf(a1, FLD(s824, 1), F_String_dcmp(a3, FLD(s824, 0)));
} else if (TAG(s824) == 2) {
return F_Map_dget_dbit(a1, FLD(s824, 1), FLD(s824, 2), FLD(s824, 0), F_Map_dbit(a3, FLD(s824, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Map_dget(V *a) { (void)a; return F_Map_dget(a[1], a[2], a[3]); }
static V F_Map_dbit(V a0, V a1) {
top:;
return F_Map_dbit_dat(a0, F_Nat_ddivmod(a1, 33u));
}
static V W_Map_dbit(V *a) { (void)a; return F_Map_dbit(a[0], a[1]); }
static V W_Nat_ddivmod(V *a) { (void)a; return F_Nat_ddivmod(a[0], a[1]); }
static V F_Map_dbit_dat(V a0, V a1) {
top:;
V v825 = a1;
return F_Map_dbit_dgo(a0, FLD(v825, 0), FLD(v825, 1));
}
static V W_Map_dbit_dat(V *a) { (void)a; return F_Map_dbit_dat(a[0], a[1]); }
static V F_Map_dbit_dgo(V a0, V a1, V a2) {
top:;
V s826 = a0;
if ((s826) == IMM(0)) {
return C2(0, IMM(0), IMM(0));
} else if (TAG(s826) == 1) {
V s827 = a1;
if ((s827) == 0) {
return F_Map_dbit_dgo_dchr(FLD(s826, 1), F_Map_dbit_dchr(FLD(s826, 0), a2));
} else if ((s827) >= 1) {
return F_Map_dbit_dgo_drec(FLD(s826, 0), F_Map_dbit_dgo(FLD(s826, 1), (s827 - 1), a2));
} else { bend_fail("incomplete match"); }
} else { bend_fail("incomplete match"); }
}
static V W_Map_dbit_dgo(V *a) { (void)a; return F_Map_dbit_dgo(a[0], a[1], a[2]); }
static V F_Map_dbit_dgo_drec(V a0, V a1) {
top:;
V v828 = a1;
return C2(0, C2(1, a0, FLD(v828, 0)), FLD(v828, 1));
}
static V W_Map_dbit_dgo_drec(V *a) { (void)a; return F_Map_dbit_dgo_drec(a[0], a[1]); }
static V F_Map_dbit_dchr(V a0, V a1) {
top:;
V s829 = a0;
V s830 = a1;
if ((s830) == 0) {
return C2(0, s829, IMM(1));
} else if ((s830) >= 1) {
return C2(0, s829, F_Map_dbit_du(s829, F_Nat_dsub(31u, (s830 - 1))));
} else { bend_fail("incomplete match"); }
}
static V W_Map_dbit_dchr(V *a) { (void)a; return F_Map_dbit_dchr(a[0], a[1]); }
static V W_Nat_dsub(V *a) { (void)a; return F_Nat_dsub(a[0], a[1]); }
static V F_Map_dbit_du(V a0, V a1) {
top:;
return F_U32_dis__ne(F_U32_dand(F_U32_dshrn(a0, a1), 1u), 0u);
}
static V W_Map_dbit_du(V *a) { (void)a; return F_Map_dbit_du(a[0], a[1]); }
static V W_U32_dshrn(V *a) { (void)a; return F_U32_dshrn(a[0], a[1]); }
static V W_U32_dand(V *a) { (void)a; return F_U32_dand(a[0], a[1]); }
static V F_Map_dbit_dgo_dchr(V a0, V a1) {
top:;
V v831 = a1;
return C2(0, C2(1, FLD(v831, 0), a0), FLD(v831, 1));
}
static V W_Map_dbit_dgo_dchr(V *a) { (void)a; return F_Map_dbit_dgo_dchr(a[0], a[1]); }
static V F_Map_dget_dbit(V a1, V a2, V a3, V a4, V a5) {
top:;
V v832 = a5;
V s833 = FLD(v832, 1);
if ((s833) == IMM(0)) {
return F_Map_dlo(a4, a3, F_Map_dget(a1, a2, FLD(v832, 0)));
} else if ((s833) == IMM(1)) {
return F_Map_dhi(a4, a2, F_Map_dget(a1, a3, FLD(v832, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Map_dget_dbit(V *a) { (void)a; return F_Map_dget_dbit(a[1], a[2], a[3], a[4], a[5]); }
static V F_Map_dhi(V a3, V a4, V a5) {
top:;
V v834 = a5;
return C2(0, C3(2, a3, a4, FLD(v834, 0)), FLD(v834, 1));
}
static V W_Map_dhi(V *a) { (void)a; return F_Map_dhi(a[3], a[4], a[5]); }
static V F_Map_dlo(V a3, V a4, V a5) {
top:;
V v835 = a5;
return C2(0, C3(2, a3, FLD(v835, 0), a4), FLD(v835, 1));
}
static V W_Map_dlo(V *a) { (void)a; return F_Map_dlo(a[3], a[4], a[5]); }
static V F_Map_dget_dleaf(V a1, V a2, V a3) {
top:;
V v836 = a3;
V s837 = FLD(v836, 1);
if ((s837) == IMM(0)) {
return C2(0, C2(1, FLD(FLD(v836, 0), 1), a2), a1);
} else if ((s837) == IMM(1)) {
return C2(0, C2(1, FLD(FLD(v836, 0), 1), a2), a2);
} else if ((s837) == IMM(2)) {
return C2(0, C2(1, FLD(FLD(v836, 0), 1), a2), a1);
} else { bend_fail("incomplete match"); }
}
static V W_Map_dget_dleaf(V *a) { (void)a; return F_Map_dget_dleaf(a[1], a[2], a[3]); }
static V F_Pair_dsnd(V a2) {
top:;
V v838 = a2;
return FLD(v838, 1);
}
static V W_Pair_dsnd(V *a) { (void)a; return F_Pair_dsnd(a[2]); }
static V S840(void) { static V c; if (!c) c = MKS("IO"); return c; }
static V S841(void) { static V c; if (!c) c = MKS("no main definition"); return c; }
static V S843(void) { static V c; if (!c) c = MKS(""); return c; }
static V L842(V *a) {
return F_Gen_dpure(S843());
}
static V F_Gen_dentry(V a0, V a1) {
top:;
V s839 = a1;
if (TAG(s839) == 0) {
return F_Gen_dentry_dty(a0, FLD(s839, 3), F_Str_deq(F_Ty_dhead(FLD(s839, 3)), S840()));
} else {
return F_Gen_dbind(F_Gen_derror(S841()), mk_clo(L842, 1, 0, 0));
}
}
static V W_Gen_dentry(V *a) { (void)a; return F_Gen_dentry(a[0], a[1]); }
static V L844(V *a) {
return C2(0, a[0], a[1]);
}
static V F_Gen_dpure(V a1) {
top:;
return mk_clo(L844, 2, 1, (V[]){a1});
}
static V W_Gen_dpure(V *a) { (void)a; return F_Gen_dpure(a[1]); }
static V L845(V *a) {
return F_Gen_derror_dgo(a[0], a[1]);
}
static V F_Gen_derror(V a0) {
top:;
return mk_clo(L845, 2, 1, (V[]){a0});
}
static V W_Gen_derror(V *a) { (void)a; return F_Gen_derror(a[0]); }
static V F_Gen_derror_dgo(V a0, V a1) {
top:;
V v846 = a1;
return C2(0, IMM(0), CN(0, 6, (V[]){FLD(v846, 0), FLD(v846, 1), FLD(v846, 2), FLD(v846, 3), C2(1, a0, FLD(v846, 4)), FLD(v846, 5)}));
}
static V W_Gen_derror_dgo(V *a) { (void)a; return F_Gen_derror_dgo(a[0], a[1]); }
static V L847(V *a) {
return F_Gen_dgo(apply(a[1], a[4]), a[0]);
}
static V F_Gen_dbind(V a2, V a3) {
top:;
return mk_clo(L847, 5, 4, (V[]){a3, a2, 0, 0});
}
static V W_Gen_dbind(V *a) { (void)a; return F_Gen_dbind(a[2], a[3]); }
static V F_Gen_dgo(V a2, V a3) {
top:;
V v848 = a2;
return apply(apply(a3, FLD(v848, 0)), FLD(v848, 1));
}
static V W_Gen_dgo(V *a) { (void)a; return F_Gen_dgo(a[2], a[3]); }
static V S850(void) { static V c; if (!c) c = MKS("\077"); return c; }
static V F_Ty_dhead(V a0) {
top:;
V s849 = a0;
if (TAG(s849) == 0) {
return FLD(s849, 0);
} else if (TAG(s849) == 14) {
return FLD(s849, 0);
} else if (TAG(s849) == 5 && TAG(FLD(s849, 0)) == 0) {
return FLD(FLD(s849, 0), 0);
} else {
return S850();
}
}
static V W_Ty_dhead(V *a) { (void)a; return F_Ty_dhead(a[0]); }
static V S852(void) { static V c; if (!c) c = MKS("int main(int argc, char **argv) { return bend_run(argc, argv, F_main); }\012"); return c; }
static V S854(void) { static V c; if (!c) c = MKS("int main(int argc, char **argv) { return bend_run_value(argc, argv, F_main, "); return c; }
static V S855(void) { static V c; if (!c) c = MKS("); }\012"); return c; }
static V L853(V *a) {
return F_Gen_dpure(F_String_dappend(S854(), F_String_dappend(a[0], S855())));
}
static V F_Gen_dentry_dty(V a0, V a1, V a2) {
top:;
V s851 = a2;
if ((s851) == IMM(1)) {
return F_Gen_dpure(S852());
} else if ((s851) == IMM(0)) {
return F_Gen_dbind(F_Gen_dprinter(a0, a1), mk_clo(L853, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dentry_dty(V *a) { (void)a; return F_Gen_dentry_dty(a[0], a[1], a[2]); }
static V L857(V *a) {
return F_Gen_dprinter_dmemo(a[2], a[1], a[0], a[3]);
}
static V F_Gen_dprinter(V a0, V a1) {
top:;
V v856 = F_Expr_dshow(a1);
return F_Gen_dbind(F_Gen_dmemo_dfind(v856), mk_clo(L857, 4, 3, (V[]){v856, a1, a0}));
}
static V W_Gen_dprinter(V *a) { (void)a; return F_Gen_dprinter(a[0], a[1]); }
static V S860(void) { static V c; if (!c) c = MKS("P"); return c; }
static V S863(void) { static V c; if (!c) c = MKS("static void "); return c; }
static V S864(void) { static V c; if (!c) c = MKS("(V v);\012"); return c; }
static V S867(void) { static V c; if (!c) c = MKS("static void "); return c; }
static V S868(void) { static V c; if (!c) c = MKS("(V v) {\012"); return c; }
static V S869(void) { static V c; if (!c) c = MKS("}\012"); return c; }
static V L870(V *a) {
return F_Gen_dpure(a[0]);
}
static V L866(V *a) {
return F_Gen_dbind(F_Gen_dcode(F_Doc_dlist(C2(1, C1(1, F_String_dappend(S867(), F_String_dappend(a[0], S868()))), C2(1, a[1], C2(1, C1(1, S869()), IMM(0)))))), mk_clo(L870, 2, 1, (V[]){a[0]}));
}
static V L865(V *a) {
return F_Gen_dbind(F_Gen_dprinter_dbody(a[2], a[1], F_Ty_dhead(a[1])), mk_clo(L866, 2, 1, (V[]){a[0]}));
}
static V L862(V *a) {
return F_Gen_dbind(F_Gen_dproto(C1(1, F_String_dappend(S863(), F_String_dappend(a[2], S864())))), mk_clo(L865, 4, 3, (V[]){a[2], a[0], a[1]}));
}
static V L861(V *a) {
return F_Gen_dbind(F_Gen_dmemo_dadd(C2(0, a[2], a[3])), mk_clo(L862, 4, 3, (V[]){a[0], a[1], a[3]}));
}
static V L859(V *a) {
return F_Gen_dbind(F_Gen_dpure(F_String_dappend(S860(), F_U32_dshow(a[3]))), mk_clo(L861, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V F_Gen_dprinter_dmemo(V a0, V a1, V a2, V a3) {
top:;
V s858 = a3;
if (TAG(s858) == 1) {
return F_Gen_dpure(FLD(s858, 0));
} else if ((s858) == IMM(0)) {
return F_Gen_dbind(F_Gen_dfresh(), mk_clo(L859, 4, 3, (V[]){a1, a0, a2}));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dprinter_dmemo(V *a) { (void)a; return F_Gen_dprinter_dmemo(a[0], a[1], a[2], a[3]); }
static V F_Doc_dlist(V a0) {
top:;
V s871 = a0;
if ((s871) == IMM(0)) {
return IMM(0);
} else if (TAG(s871) == 1) {
return C2(2, FLD(s871, 0), F_Doc_dlist(FLD(s871, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Doc_dlist(V *a) { (void)a; return F_Doc_dlist(a[0]); }
static V L872(V *a) {
return F_Gen_dcode_dgo(a[0], a[1]);
}
static V F_Gen_dcode(V a0) {
top:;
return mk_clo(L872, 2, 1, (V[]){a0});
}
static V W_Gen_dcode(V *a) { (void)a; return F_Gen_dcode(a[0]); }
static V F_Gen_dcode_dgo(V a0, V a1) {
top:;
V v873 = a1;
return C2(0, IMM(0), CN(0, 6, (V[]){FLD(v873, 0), FLD(v873, 1), C2(2, FLD(v873, 2), a0), FLD(v873, 3), FLD(v873, 4), FLD(v873, 5)}));
}
static V W_Gen_dcode_dgo(V *a) { (void)a; return F_Gen_dcode_dgo(a[0], a[1]); }
static V S874(void) { static V c; if (!c) c = MKS("U32"); return c; }
static V S875(void) { static V c; if (!c) c = MKS("Nat"); return c; }
static V S876(void) { static V c; if (!c) c = MKS("F32"); return c; }
static V S877(void) { static V c; if (!c) c = MKS("Char"); return c; }
static V S878(void) { static V c; if (!c) c = MKS("String"); return c; }
static V S879(void) { static V c; if (!c) c = MKS("List"); return c; }
static V S880(void) { static V c; if (!c) c = MKS("&"); return c; }
static V S881(void) { static V c; if (!c) c = MKS("->"); return c; }
static V F_Gen_dprinter_dbody(V a0, V a1, V a2) {
top:;
return F_Gen_dprinter_dhead(a0, a1, F_P_dwhich(a2, C2(1, S874(), C2(1, S875(), C2(1, S876(), C2(1, S877(), C2(1, S878(), C2(1, S879(), C2(1, S880(), C2(1, S881(), IMM(0)))))))))));
}
static V W_Gen_dprinter_dbody(V *a) { (void)a; return F_Gen_dprinter_dbody(a[0], a[1], a[2]); }
static V S883(void) { static V c; if (!c) c = MKS("pr_u32(v);\012"); return c; }
static V S884(void) { static V c; if (!c) c = MKS("pr_nat(v);\012"); return c; }
static V S885(void) { static V c; if (!c) c = MKS("pr_f32(v);\012"); return c; }
static V S886(void) { static V c; if (!c) c = MKS("pr_char(v);\012"); return c; }
static V S887(void) { static V c; if (!c) c = MKS("pr_str(v);\012"); return c; }
static V S889(void) { static V c; if (!c) c = MKS("pr_s(\042[\042);\012for (int i = 0; TAG(v) == 1; i++) { if (i) pr_s(\042, \042); "); return c; }
static V S890(void) { static V c; if (!c) c = MKS("(FLD(v, 0)); v = FLD(v, 1); }\012pr_s(\042]\042);\012"); return c; }
static V L888(V *a) {
return F_Gen_dpure(C1(1, F_String_dappend(S889(), F_String_dappend(a[0], S890()))));
}
static V S891(void) { static V c; if (!c) c = MKS("v"); return c; }
static V S893(void) { static V c; if (!c) c = MKS("pr_s(\042(\042);\012"); return c; }
static V S894(void) { static V c; if (!c) c = MKS("pr_s(\042)\042);\012"); return c; }
static V L892(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, C1(1, S893()), C2(1, a[0], C2(1, C1(1, S894()), IMM(0))))));
}
static V S895(void) { static V c; if (!c) c = MKS("(void)v; pr_s(\042<function>\042);\012"); return c; }
static V S896(void) { static V c; if (!c) c = MKS("%"); return c; }
static V F_Gen_dprinter_dhead(V a0, V a1, V a2) {
top:;
V s882 = a2;
if ((s882) == 0) {
return F_Gen_dpure(C1(1, S883()));
} else if ((s882) == 1) {
return F_Gen_dpure(C1(1, S884()));
} else if ((s882) == 2) {
return F_Gen_dpure(C1(1, S885()));
} else if ((s882) == 3) {
return F_Gen_dpure(C1(1, S886()));
} else if ((s882) == 4) {
return F_Gen_dpure(C1(1, S887()));
} else if ((s882) == 5) {
return F_Gen_dbind(F_Gen_dprinter(a0, F_P_dlast(F_Ty_dargs(a1))), mk_clo(L888, 1, 0, 0));
} else if ((s882) == 6) {
return F_Gen_dbind(F_Gen_dprinter_dtuple(a0, F_Ty_dtuple(a1), S891()), mk_clo(L892, 1, 0, 0));
} else if ((s882) == 7) {
return F_Gen_dpure(C1(1, S895()));
} else if ((s882) >= 8) {
return F_Gen_dprinter_dadt(a0, a1, F_G_dbody(a0, F_String_dappend(S896(), F_Ty_dhead(a1))));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dprinter_dhead(V *a) { (void)a; return F_Gen_dprinter_dhead(a[0], a[1], a[2]); }
static V S899(void) { static V c; if (!c) c = MKS("pr_s(\042\077\042);\012"); return c; }
static V L898(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, a[0], C2(1, C1(1, S899()), IMM(0)))));
}
static V S900(void) { static V c; if (!c) c = MKS("(void)v; pr_s(\042\077\042);\012"); return c; }
static V F_Gen_dprinter_dadt(V a0, V a1, V a2) {
top:;
V s897 = a2;
if (TAG(s897) == 3) {
return F_Gen_dbind(F_Gen_dprinter_dctors(a0, F_Ty_dbind(FLD(s897, 1), F_Ty_dargs(a1)), FLD(s897, 2)), mk_clo(L898, 1, 0, 0));
} else {
return F_Gen_dpure(C1(1, S900()));
}
}
static V W_Gen_dprinter_dadt(V *a) { (void)a; return F_Gen_dprinter_dadt(a[0], a[1], a[2]); }
static V F_Ty_dargs(V a0) {
top:;
V s901 = a0;
if (TAG(s901) == 14) {
return FLD(s901, 1);
} else if (TAG(s901) == 5) {
return FLD(s901, 1);
} else {
return IMM(0);
}
}
static V W_Ty_dargs(V *a) { (void)a; return F_Ty_dargs(a[0]); }
static V F_Ty_dbind(V a0, V a1) {
top:;
return F_Ty_dbind_dgo(F_List_dreverse(a0), F_List_dreverse(a1));
}
static V W_Ty_dbind(V *a) { (void)a; return F_Ty_dbind(a[0], a[1]); }
static V F_Ty_dbind_dgo(V a0, V a1) {
top:;
V s902 = a0;
V s903 = a1;
if (TAG(s902) == 1 && TAG(s903) == 1) {
return C2(1, C2(0, FLD(s902, 0), FLD(s903, 0)), F_Ty_dbind_dgo(FLD(s902, 1), FLD(s903, 1)));
} else {
return IMM(0);
}
}
static V W_Ty_dbind_dgo(V *a) { (void)a; return F_Ty_dbind_dgo(a[0], a[1]); }
static V L906(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, a[0], C2(1, a[1], IMM(0)))));
}
static V L905(V *a) {
return F_Gen_dbind(F_Gen_dprinter_dctors(a[2], a[1], a[0]), mk_clo(L906, 2, 1, (V[]){a[3]}));
}
static V F_Gen_dprinter_dctors(V a0, V a1, V a2) {
top:;
V s904 = a2;
if ((s904) == IMM(0)) {
return F_Gen_dpure(IMM(0));
} else if (TAG(s904) == 1) {
return F_Gen_dbind(F_Gen_dprinter_dctor(a0, a1, FLD(FLD(s904, 0), 0), FLD(FLD(s904, 0), 1), F_G_dctor(a0, FLD(FLD(s904, 0), 0))), mk_clo(L905, 4, 3, (V[]){FLD(s904, 1), a1, a0}));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dprinter_dctors(V *a) { (void)a; return F_Gen_dprinter_dctors(a[0], a[1], a[2]); }
static V F_G_dctor(V a0, V a1) {
top:;
V v907 = a0;
return F_Pair_dsnd(F_Map_dget(IMM(0), F_G_dopt__ctors(FLD(v907, 0)), a1));
}
static V W_G_dctor(V *a) { (void)a; return F_G_dctor(a[0], a[1]); }
static V F_G_dopt__ctors(V a0) {
top:;
V s908 = a0;
if ((s908) == IMM(0)) {
return IMM(0);
} else if (TAG(s908) == 1) {
return C2(1, FLD(s908, 0), C1(1, FLD(s908, 1)));
} else if (TAG(s908) == 2) {
return C3(2, FLD(s908, 0), F_G_dopt__ctors(FLD(s908, 1)), F_G_dopt__ctors(FLD(s908, 2)));
} else { bend_fail("incomplete match"); }
}
static V W_G_dopt__ctors(V *a) { (void)a; return F_G_dopt__ctors(a[0]); }
static V S910(void) { static V c; if (!c) c = MKS("v"); return c; }
static V S911(void) { static V c; if (!c) c = MKS("FLD(v, "); return c; }
static V S913(void) { static V c; if (!c) c = MKS(" { pr_s(\042"); return c; }
static V S914(void) { static V c; if (!c) c = MKS("{\042);\012"); return c; }
static V S915(void) { static V c; if (!c) c = MKS("pr_s(\042}\042); return; }\012"); return c; }
static V L912(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, C1(1, F_String_dappend(F_Gen_dprinter_dtest(a[3], a[2], a[1]), F_String_dappend(S913(), F_String_dappend(a[0], S914())))), C2(1, a[4], C2(1, C1(1, S915()), IMM(0))))));
}
static V F_Gen_dprinter_dctor(V a0, V a1, V a2, V a3, V a4) {
top:;
V s909 = a4;
if ((s909) == IMM(0)) {
return F_Gen_dpure(IMM(0));
} else if (TAG(s909) == 1) {
return F_Gen_dbind(F_Gen_dprinter_dfields(a0, a1, a3, F_Bool_dpick(F_U32_dis__eq(FLD(FLD(s909, 0), 2), 2u), S910(), S911()), 0u), mk_clo(L912, 5, 4, (V[]){a2, FLD(FLD(s909, 0), 3), FLD(FLD(s909, 0), 0), FLD(FLD(s909, 0), 2)}));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dprinter_dctor(V *a) { (void)a; return F_Gen_dprinter_dctor(a[0], a[1], a[2], a[3], a[4]); }
static V S916(void) { static V c; if (!c) c = MKS("if (1)"); return c; }
static V S917(void) { static V c; if (!c) c = MKS("if (v == IMM("); return c; }
static V S918(void) { static V c; if (!c) c = MKS("))"); return c; }
static V S919(void) { static V c; if (!c) c = MKS("if (!(v & 1) && TAG(v) == "); return c; }
static V S920(void) { static V c; if (!c) c = MKS(")"); return c; }
static V F_Gen_dprinter_dtest(V a0, V a1, V a2) {
top:;
return F_Bool_dpick(a2, S916(), F_Bool_dpick(F_U32_dis__eq(a0, 1u), F_String_dappend(S917(), F_String_dappend(F_U32_dshow(a1), S918())), F_String_dappend(S919(), F_String_dappend(F_U32_dshow(a1), S920()))));
}
static V W_Gen_dprinter_dtest(V *a) { (void)a; return F_Gen_dprinter_dtest(a[0], a[1], a[2]); }
static V S924(void) { static V c; if (!c) c = MKS(""); return c; }
static V S925(void) { static V c; if (!c) c = MKS("pr_s(\042, \042);\012"); return c; }
static V S926(void) { static V c; if (!c) c = MKS("("); return c; }
static V S927(void) { static V c; if (!c) c = MKS("v"); return c; }
static V S928(void) { static V c; if (!c) c = MKS("v"); return c; }
static V S929(void) { static V c; if (!c) c = MKS(")"); return c; }
static V S930(void) { static V c; if (!c) c = MKS(");\012"); return c; }
static V L923(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, C1(1, F_String_dappend(F_Bool_dpick(F_U32_dis__zero(a[2]), S924(), S925()), F_String_dappend(a[1], F_String_dappend(S926(), F_String_dappend(F_Bool_dpick(F_Str_deq(a[0], S927()), S928(), F_String_dappend(a[0], F_String_dappend(F_U32_dshow(a[2]), S929()))), S930()))))), C2(1, a[3], IMM(0)))));
}
static V L922(V *a) {
return F_Gen_dbind(F_Gen_dprinter_dfields(a[4], a[3], a[2], a[1], F_U32_dinc(a[0])), mk_clo(L923, 4, 3, (V[]){a[1], a[5], a[0]}));
}
static V F_Gen_dprinter_dfields(V a0, V a1, V a2, V a3, V a4) {
top:;
V s921 = a2;
if ((s921) == IMM(0)) {
return F_Gen_dpure(IMM(0));
} else if (TAG(s921) == 1) {
return F_Gen_dbind(F_Gen_dprinter(a0, F_Ty_dsubst(FLD(FLD(s921, 0), 1), a1)), mk_clo(L922, 6, 5, (V[]){a4, a3, FLD(s921, 1), a1, a0}));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dprinter_dfields(V *a) { (void)a; return F_Gen_dprinter_dfields(a[0], a[1], a[2], a[3], a[4]); }
static V F_Ty_dsubst(V a0, V a1) {
top:;
V s931 = a0;
if (TAG(s931) == 0) {
return F_Maybe_ddefault(F_Ty_dfind(a1, FLD(s931, 0)), C1(0, FLD(s931, 0)));
} else if (TAG(s931) == 14) {
return C2(14, FLD(s931, 0), F_Ty_dsubsts(FLD(s931, 1), a1));
} else if (TAG(s931) == 5) {
return C2(5, FLD(s931, 0), F_Ty_dsubsts(FLD(s931, 1), a1));
} else {
return s931;
}
}
static V W_Ty_dsubst(V *a) { (void)a; return F_Ty_dsubst(a[0], a[1]); }
static V F_Ty_dsubsts(V a0, V a1) {
top:;
V s932 = a0;
if ((s932) == IMM(0)) {
return IMM(0);
} else if (TAG(s932) == 1) {
return C2(1, F_Ty_dsubst(FLD(s932, 0), a1), F_Ty_dsubsts(FLD(s932, 1), a1));
} else { bend_fail("incomplete match"); }
}
static V W_Ty_dsubsts(V *a) { (void)a; return F_Ty_dsubsts(a[0], a[1]); }
static V F_Ty_dfind(V a0, V a1) {
top:;
V s933 = a0;
if ((s933) == IMM(0)) {
return IMM(0);
} else if (TAG(s933) == 1) {
return F_Ty_dfind_dif(FLD(FLD(s933, 0), 1), FLD(s933, 1), a1, F_String_deq(FLD(FLD(s933, 0), 0), a1));
} else { bend_fail("incomplete match"); }
}
static V W_Ty_dfind(V *a) { (void)a; return F_Ty_dfind(a[0], a[1]); }
static V F_Ty_dfind_dif(V a0, V a1, V a2, V a3) {
top:;
V s934 = a3;
if ((s934) == IMM(1)) {
return C1(1, a0);
} else if ((s934) == IMM(0)) {
return F_Ty_dfind(a1, a2);
} else { bend_fail("incomplete match"); }
}
static V W_Ty_dfind_dif(V *a) { (void)a; return F_Ty_dfind_dif(a[0], a[1], a[2], a[3]); }
static V F_Maybe_ddefault(V a2, V a3) {
top:;
V s935 = a2;
if ((s935) == IMM(0)) {
return a3;
} else if (TAG(s935) == 1) {
return FLD(s935, 0);
} else { bend_fail("incomplete match"); }
}
static V W_Maybe_ddefault(V *a) { (void)a; return F_Maybe_ddefault(a[2], a[3]); }
static V S937(void) { static V c; if (!c) c = MKS("&"); return c; }
static V F_Ty_dtuple(V a0) {
top:;
V s936 = a0;
if (TAG(s936) == 14) {
return F_Ty_dtuple_dgo(C2(14, FLD(s936, 0), FLD(s936, 1)), FLD(s936, 1), F_Str_deq(FLD(s936, 0), S937()));
} else {
return C2(1, s936, IMM(0));
}
}
static V W_Ty_dtuple(V *a) { (void)a; return F_Ty_dtuple(a[0]); }
static V F_Ty_dtuple_dgo(V a0, V a1, V a2) {
top:;
V s938 = a2;
if ((s938) == IMM(1)) {
return F_Ty_dtuple_dargs(a0, a1);
} else if ((s938) == IMM(0)) {
return C2(1, a0, IMM(0));
} else { bend_fail("incomplete match"); }
}
static V W_Ty_dtuple_dgo(V *a) { (void)a; return F_Ty_dtuple_dgo(a[0], a[1], a[2]); }
static V F_Ty_dtuple_dargs(V a0, V a1) {
top:;
V s939 = a1;
if (TAG(s939) == 1 && TAG(FLD(s939, 1)) == 1 && (FLD(FLD(s939, 1), 1)) == IMM(0)) {
return C2(1, FLD(s939, 0), F_Ty_dtuple(FLD(FLD(s939, 1), 0)));
} else {
return C2(1, a0, IMM(0));
}
}
static V W_Ty_dtuple_dargs(V *a) { (void)a; return F_Ty_dtuple_dargs(a[0], a[1]); }
static V S942(void) { static V c; if (!c) c = MKS("("); return c; }
static V S943(void) { static V c; if (!c) c = MKS(");\012"); return c; }
static V L941(V *a) {
return F_Gen_dpure(C1(1, F_String_dappend(a[1], F_String_dappend(S942(), F_String_dappend(a[0], S943())))));
}
static V S945(void) { static V c; if (!c) c = MKS("FLD("); return c; }
static V S946(void) { static V c; if (!c) c = MKS(", 1)"); return c; }
static V S948(void) { static V c; if (!c) c = MKS("(FLD("); return c; }
static V S949(void) { static V c; if (!c) c = MKS(", 0));\012pr_s(\042, \042);\012"); return c; }
static V L947(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, C1(1, F_String_dappend(a[1], F_String_dappend(S948(), F_String_dappend(a[0], S949())))), C2(1, a[2], IMM(0)))));
}
static V L944(V *a) {
return F_Gen_dbind(F_Gen_dprinter_dtuple(a[2], a[1], F_String_dappend(S945(), F_String_dappend(a[0], S946()))), mk_clo(L947, 3, 2, (V[]){a[0], a[3]}));
}
static V F_Gen_dprinter_dtuple(V a0, V a1, V a2) {
top:;
V s940 = a1;
if ((s940) == IMM(0)) {
return F_Gen_dpure(IMM(0));
} else if (TAG(s940) == 1 && (FLD(s940, 1)) == IMM(0)) {
return F_Gen_dbind(F_Gen_dprinter(a0, FLD(s940, 0)), mk_clo(L941, 2, 1, (V[]){a2}));
} else if (TAG(s940) == 1) {
return F_Gen_dbind(F_Gen_dprinter(a0, FLD(s940, 0)), mk_clo(L944, 4, 3, (V[]){a2, FLD(s940, 1), a0}));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dprinter_dtuple(V *a) { (void)a; return F_Gen_dprinter_dtuple(a[0], a[1], a[2]); }
static V L950(V *a) {
return F_Gen_dproto_dgo(a[0], a[1]);
}
static V F_Gen_dproto(V a0) {
top:;
return mk_clo(L950, 2, 1, (V[]){a0});
}
static V W_Gen_dproto(V *a) { (void)a; return F_Gen_dproto(a[0]); }
static V F_Gen_dproto_dgo(V a0, V a1) {
top:;
V v951 = a1;
return C2(0, IMM(0), CN(0, 6, (V[]){FLD(v951, 0), C2(2, FLD(v951, 1), a0), FLD(v951, 2), FLD(v951, 3), FLD(v951, 4), FLD(v951, 5)}));
}
static V W_Gen_dproto_dgo(V *a) { (void)a; return F_Gen_dproto_dgo(a[0], a[1]); }
static V L952(V *a) {
return F_Gen_dmemo_dadd_dgo(a[1], a[0]);
}
static V F_Gen_dmemo_dadd(V a0) {
top:;
return mk_clo(L952, 2, 1, (V[]){a0});
}
static V W_Gen_dmemo_dadd(V *a) { (void)a; return F_Gen_dmemo_dadd(a[0]); }
static V F_Gen_dmemo_dadd_dgo(V a0, V a1) {
top:;
V v953 = a0;
return C2(0, IMM(0), CN(0, 6, (V[]){FLD(v953, 0), FLD(v953, 1), FLD(v953, 2), FLD(v953, 3), FLD(v953, 4), C2(1, a1, FLD(v953, 5))}));
}
static V W_Gen_dmemo_dadd_dgo(V *a) { (void)a; return F_Gen_dmemo_dadd_dgo(a[0], a[1]); }
static V L954(V *a) {
return F_Gen_dfresh_dgo(a[0]);
}
static V F_Gen_dfresh(void) {
top:;
return mk_clo(L954, 1, 0, 0);
}
static V W_Gen_dfresh(V *a) { (void)a; return F_Gen_dfresh(); }
static V F_Gen_dfresh_dgo(V a0) {
top:;
V v955 = a0;
return C2(0, FLD(v955, 0), CN(0, 6, (V[]){F_U32_dinc(FLD(v955, 0)), FLD(v955, 1), FLD(v955, 2), FLD(v955, 3), FLD(v955, 4), FLD(v955, 5)}));
}
static V W_Gen_dfresh_dgo(V *a) { (void)a; return F_Gen_dfresh_dgo(a[0]); }
static V L956(V *a) {
return F_Gen_dmemo_dfind_dgo(a[1], a[0]);
}
static V F_Gen_dmemo_dfind(V a0) {
top:;
return mk_clo(L956, 2, 1, (V[]){a0});
}
static V W_Gen_dmemo_dfind(V *a) { (void)a; return F_Gen_dmemo_dfind(a[0]); }
static V F_Gen_dmemo_dfind_dgo(V a0, V a1) {
top:;
V v957 = a0;
return C2(0, F_Env_dfind(FLD(v957, 5), a1), CN(0, 6, (V[]){FLD(v957, 0), FLD(v957, 1), FLD(v957, 2), FLD(v957, 3), FLD(v957, 4), FLD(v957, 5)}));
}
static V W_Gen_dmemo_dfind_dgo(V *a) { (void)a; return F_Gen_dmemo_dfind_dgo(a[0], a[1]); }
static V F_Env_dfind(V a0, V a1) {
top:;
V s958 = a0;
if ((s958) == IMM(0)) {
return IMM(0);
} else if (TAG(s958) == 1) {
return F_Env_dfind_dif(FLD(FLD(s958, 0), 1), FLD(s958, 1), a1, F_String_deq(FLD(FLD(s958, 0), 0), a1));
} else { bend_fail("incomplete match"); }
}
static V W_Env_dfind(V *a) { (void)a; return F_Env_dfind(a[0], a[1]); }
static V F_Env_dfind_dif(V a0, V a1, V a2, V a3) {
top:;
V s959 = a3;
if ((s959) == IMM(1)) {
return C1(1, a0);
} else if ((s959) == IMM(0)) {
return F_Env_dfind(a1, a2);
} else { bend_fail("incomplete match"); }
}
static V W_Env_dfind_dif(V *a) { (void)a; return F_Env_dfind_dif(a[0], a[1], a[2], a[3]); }
static V S961(void) { static V c; if (!c) c = MKS("n"); return c; }
static V S962(void) { static V c; if (!c) c = MKS("\042"); return c; }
static V S963(void) { static V c; if (!c) c = MKS("\042"); return c; }
static V S964(void) { static V c; if (!c) c = MKS("("); return c; }
static V S965(void) { static V c; if (!c) c = MKS(" "); return c; }
static V S966(void) { static V c; if (!c) c = MKS(")"); return c; }
static V S967(void) { static V c; if (!c) c = MKS("{"); return c; }
static V S968(void) { static V c; if (!c) c = MKS("}"); return c; }
static V S969(void) { static V c; if (!c) c = MKS("(\134"); return c; }
static V S970(void) { static V c; if (!c) c = MKS(" "); return c; }
static V S971(void) { static V c; if (!c) c = MKS(")"); return c; }
static V S972(void) { static V c; if (!c) c = MKS("(let "); return c; }
static V S973(void) { static V c; if (!c) c = MKS(" "); return c; }
static V S974(void) { static V c; if (!c) c = MKS(" "); return c; }
static V S975(void) { static V c; if (!c) c = MKS(")"); return c; }
static V S976(void) { static V c; if (!c) c = MKS("(match ["); return c; }
static V S977(void) { static V c; if (!c) c = MKS("] "); return c; }
static V S978(void) { static V c; if (!c) c = MKS(")"); return c; }
static V S979(void) { static V c; if (!c) c = MKS("(case "); return c; }
static V S980(void) { static V c; if (!c) c = MKS(" => "); return c; }
static V S981(void) { static V c; if (!c) c = MKS(")"); return c; }
static V S982(void) { static V c; if (!c) c = MKS("("); return c; }
static V S983(void) { static V c; if (!c) c = MKS("n+ "); return c; }
static V S984(void) { static V c; if (!c) c = MKS(")"); return c; }
static V S985(void) { static V c; if (!c) c = MKS("("); return c; }
static V S986(void) { static V c; if (!c) c = MKS(" "); return c; }
static V S987(void) { static V c; if (!c) c = MKS(" "); return c; }
static V S988(void) { static V c; if (!c) c = MKS(")"); return c; }
static V S989(void) { static V c; if (!c) c = MKS("(: "); return c; }
static V S990(void) { static V c; if (!c) c = MKS(" "); return c; }
static V S991(void) { static V c; if (!c) c = MKS(")"); return c; }
static V S992(void) { static V c; if (!c) c = MKS("#"); return c; }
static V S993(void) { static V c; if (!c) c = MKS("(ERR "); return c; }
static V S994(void) { static V c; if (!c) c = MKS(")"); return c; }
static V F_Expr_dshow(V a0) {
top:;
V s960 = a0;
if (TAG(s960) == 0) {
return FLD(s960, 0);
} else if (TAG(s960) == 1) {
return F_U32_dshow(FLD(s960, 0));
} else if (TAG(s960) == 2) {
return F_String_dappend(F_U32_dshow(FLD(s960, 0)), S961());
} else if (TAG(s960) == 3) {
return FLD(s960, 0);
} else if (TAG(s960) == 4) {
return F_String_dappend(S962(), F_String_dappend(FLD(s960, 0), S963()));
} else if (TAG(s960) == 5) {
return F_String_dappend(S964(), F_String_dappend(F_Expr_dshow(FLD(s960, 0)), F_String_dappend(S965(), F_String_dappend(F_Exprs_dshow(FLD(s960, 1)), S966()))));
} else if (TAG(s960) == 6) {
return F_String_dappend(FLD(s960, 0), F_String_dappend(S967(), F_String_dappend(F_Exprs_dshow(FLD(s960, 1)), S968())));
} else if (TAG(s960) == 7) {
return F_String_dappend(S969(), F_String_dappend(F_Pat_dshow(FLD(s960, 0)), F_String_dappend(S970(), F_String_dappend(F_Expr_dshow(FLD(s960, 1)), S971()))));
} else if (TAG(s960) == 8) {
return F_String_dappend(S972(), F_String_dappend(F_Pat_dshow(FLD(s960, 0)), F_String_dappend(S973(), F_String_dappend(F_Expr_dshow(FLD(s960, 1)), F_String_dappend(S974(), F_String_dappend(F_Expr_dshow(FLD(s960, 2)), S975()))))));
} else if (TAG(s960) == 9) {
return F_String_dappend(S976(), F_String_dappend(F_Exprs_dshow(FLD(s960, 0)), F_String_dappend(S977(), F_String_dappend(F_Exprs_dshow(FLD(s960, 1)), S978()))));
} else if (TAG(s960) == 10) {
return F_String_dappend(S979(), F_String_dappend(F_Pats_dshow(FLD(s960, 0)), F_String_dappend(S980(), F_String_dappend(F_Expr_dshow(FLD(s960, 1)), S981()))));
} else if (TAG(s960) == 11) {
return F_String_dappend(S982(), F_String_dappend(F_U32_dshow(FLD(s960, 0)), F_String_dappend(S983(), F_String_dappend(F_Expr_dshow(FLD(s960, 1)), S984()))));
} else if (TAG(s960) == 12) {
return F_String_dappend(S985(), F_String_dappend(FLD(s960, 0), F_String_dappend(S986(), F_String_dappend(F_Expr_dshow(FLD(s960, 1)), F_String_dappend(S987(), F_String_dappend(F_Expr_dshow(FLD(s960, 2)), S988()))))));
} else if (TAG(s960) == 13) {
return F_String_dappend(S989(), F_String_dappend(F_Expr_dshow(FLD(s960, 0)), F_String_dappend(S990(), F_String_dappend(FLD(s960, 1), S991()))));
} else if (TAG(s960) == 14) {
return F_String_dappend(S992(), FLD(s960, 0));
} else if (TAG(s960) == 15) {
return F_String_dappend(S993(), F_String_dappend(FLD(s960, 0), S994()));
} else { bend_fail("incomplete match"); }
}
static V W_Expr_dshow(V *a) { (void)a; return F_Expr_dshow(a[0]); }
static V S996(void) { static V c; if (!c) c = MKS(""); return c; }
static V S997(void) { static V c; if (!c) c = MKS(" "); return c; }
static V F_Pats_dshow(V a0) {
top:;
V s995 = a0;
if ((s995) == IMM(0)) {
return S996();
} else if (TAG(s995) == 1 && (FLD(s995, 1)) == IMM(0)) {
return F_Pat_dshow(FLD(s995, 0));
} else if (TAG(s995) == 1) {
return F_String_dappend(F_Pat_dshow(FLD(s995, 0)), F_String_dappend(S997(), F_Pats_dshow(FLD(s995, 1))));
} else { bend_fail("incomplete match"); }
}
static V W_Pats_dshow(V *a) { (void)a; return F_Pats_dshow(a[0]); }
static V S999(void) { static V c; if (!c) c = MKS("{"); return c; }
static V S1000(void) { static V c; if (!c) c = MKS("}"); return c; }
static V S1001(void) { static V c; if (!c) c = MKS("n"); return c; }
static V S1002(void) { static V c; if (!c) c = MKS("n+"); return c; }
static V F_Pat_dshow(V a0) {
top:;
V s998 = a0;
if (TAG(s998) == 0) {
return FLD(s998, 0);
} else if (TAG(s998) == 1) {
return F_String_dappend(FLD(s998, 0), F_String_dappend(S999(), F_String_dappend(F_Pats_dshow(FLD(s998, 1)), S1000())));
} else if (TAG(s998) == 2) {
return F_String_dappend(F_U32_dshow(FLD(s998, 0)), S1001());
} else if (TAG(s998) == 3) {
return F_String_dappend(F_U32_dshow(FLD(s998, 0)), F_String_dappend(S1002(), F_Pat_dshow(FLD(s998, 1))));
} else if (TAG(s998) == 4) {
return F_U32_dshow(FLD(s998, 0));
} else { bend_fail("incomplete match"); }
}
static V W_Pat_dshow(V *a) { (void)a; return F_Pat_dshow(a[0]); }
static V S1004(void) { static V c; if (!c) c = MKS(""); return c; }
static V S1005(void) { static V c; if (!c) c = MKS(" "); return c; }
static V F_Exprs_dshow(V a0) {
top:;
V s1003 = a0;
if ((s1003) == IMM(0)) {
return S1004();
} else if (TAG(s1003) == 1 && (FLD(s1003, 1)) == IMM(0)) {
return F_Expr_dshow(FLD(s1003, 0));
} else if (TAG(s1003) == 1) {
return F_String_dappend(F_Expr_dshow(FLD(s1003, 0)), F_String_dappend(S1005(), F_Exprs_dshow(FLD(s1003, 1))));
} else { bend_fail("incomplete match"); }
}
static V W_Exprs_dshow(V *a) { (void)a; return F_Exprs_dshow(a[0]); }
static V F_Set_dnew(void) {
top:;
return F_Map_dnew();
}
static V W_Set_dnew(V *a) { (void)a; return F_Set_dnew(); }
static V F_Map_dnew(void) {
top:;
return IMM(0);
}
static V W_Map_dnew(V *a) { (void)a; return F_Map_dnew(); }
static V F_Gen_dall(V a0, V a1, V a2) {
top:;
V s1006 = a1;
if ((s1006) == IMM(0)) {
return F_Gen_dpure(IMM(0));
} else if (TAG(s1006) == 1) {
return F_Gen_dall_dseen(a0, FLD(s1006, 0), FLD(s1006, 1), F_Set_dhas(a2, FLD(s1006, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dall(V *a) { (void)a; return F_Gen_dall(a[0], a[1], a[2]); }
static V F_Set_dhas(V a0, V a1) {
top:;
return F_Map_dhas(a0, a1);
}
static V W_Set_dhas(V *a) { (void)a; return F_Set_dhas(a[0], a[1]); }
static V F_Map_dhas(V a2, V a3) {
top:;
V s1007 = a2;
if ((s1007) == IMM(0)) {
return C2(0, IMM(0), IMM(0));
} else if (TAG(s1007) == 1) {
return F_Map_dhas_dleaf(FLD(s1007, 1), F_String_dcmp(a3, FLD(s1007, 0)));
} else if (TAG(s1007) == 2) {
return F_Map_dhas_dbit(FLD(s1007, 1), FLD(s1007, 2), FLD(s1007, 0), F_Map_dbit(a3, FLD(s1007, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Map_dhas(V *a) { (void)a; return F_Map_dhas(a[2], a[3]); }
static V F_Map_dhas_dbit(V a2, V a3, V a4, V a5) {
top:;
V v1008 = a5;
V s1009 = FLD(v1008, 1);
if ((s1009) == IMM(0)) {
return F_Map_dlo(a4, a3, F_Map_dhas(a2, FLD(v1008, 0)));
} else if ((s1009) == IMM(1)) {
return F_Map_dhi(a4, a2, F_Map_dhas(a3, FLD(v1008, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Map_dhas_dbit(V *a) { (void)a; return F_Map_dhas_dbit(a[2], a[3], a[4], a[5]); }
static V F_Map_dhas_dleaf(V a2, V a3) {
top:;
V v1010 = a3;
return C2(0, C2(1, FLD(FLD(v1010, 0), 1), a2), F_Cmp_dis__eq(FLD(v1010, 1)));
}
static V W_Map_dhas_dleaf(V *a) { (void)a; return F_Map_dhas_dleaf(a[2], a[3]); }
static V F_Gen_dall_dseen(V a0, V a1, V a2, V a3) {
top:;
V v1011 = a3;
return F_Gen_dall_dgo(a0, a1, a2, FLD(v1011, 0), FLD(v1011, 1));
}
static V W_Gen_dall_dseen(V *a) { (void)a; return F_Gen_dall_dseen(a[0], a[1], a[2], a[3]); }
static V L1014(V *a) {
return F_Gen_dall(a[3], F_List_dappend(a[4], a[2]), F_Set_dadd(a[1], a[0]));
}
static V L1013(V *a) {
return F_Gen_dbind(F_Gen_dtake__refs(), mk_clo(L1014, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V F_Gen_dall_dgo(V a0, V a1, V a2, V a3, V a4) {
top:;
V s1012 = a4;
if ((s1012) == IMM(1)) {
return F_Gen_dall(a0, a2, a3);
} else if ((s1012) == IMM(0)) {
return F_Gen_dbind(F_Gen_ddef(a0, a1), mk_clo(L1013, 5, 4, (V[]){a1, a3, a2, a0}));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dall_dgo(V *a) { (void)a; return F_Gen_dall_dgo(a[0], a[1], a[2], a[3], a[4]); }
static V F_Set_dadd(V a0, V a1) {
top:;
return F_Map_dset(a0, a1, IMM(0));
}
static V W_Set_dadd(V *a) { (void)a; return F_Set_dadd(a[0], a[1]); }
static V F_Map_dset(V a2, V a3, V a4) {
top:;
return F_Map_dset_dgo(a4, F_Map_dseek(a2, a3));
}
static V W_Map_dset(V *a) { (void)a; return F_Map_dset(a[2], a[3], a[4]); }
static V F_Map_dseek(V a2, V a3) {
top:;
V s1015 = a2;
if ((s1015) == IMM(0)) {
return C2(0, IMM(0), C2(0, a3, IMM(0)));
} else if (TAG(s1015) == 1) {
return C2(0, C2(1, FLD(s1015, 0), FLD(s1015, 1)), C2(0, a3, C1(1, FLD(s1015, 0))));
} else if (TAG(s1015) == 2) {
return F_Map_dseek_dbit(FLD(s1015, 1), FLD(s1015, 2), FLD(s1015, 0), F_Map_dbit(a3, FLD(s1015, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Map_dseek(V *a) { (void)a; return F_Map_dseek(a[2], a[3]); }
static V F_Map_dseek_dbit(V a2, V a3, V a4, V a5) {
top:;
V v1016 = a5;
V s1017 = FLD(v1016, 1);
if ((s1017) == IMM(0)) {
return F_Map_dlo(a4, a3, F_Map_dseek(a2, FLD(v1016, 0)));
} else if ((s1017) == IMM(1)) {
return F_Map_dhi(a4, a2, F_Map_dseek(a3, FLD(v1016, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Map_dseek_dbit(V *a) { (void)a; return F_Map_dseek_dbit(a[2], a[3], a[4], a[5]); }
static V F_Map_dset_dgo(V a2, V a3) {
top:;
V v1018 = a3;
V s1019 = FLD(FLD(v1018, 1), 1);
if ((s1019) == IMM(0)) {
return C2(1, FLD(FLD(v1018, 1), 0), a2);
} else if (TAG(s1019) == 1) {
V v1020 = FLD(FLD(v1018, 1), 0);
return F_Map_dset_dfin(FLD(v1018, 0), v1020, a2, v1020, FLD(s1019, 0));
} else { bend_fail("incomplete match"); }
}
static V W_Map_dset_dgo(V *a) { (void)a; return F_Map_dset_dgo(a[2], a[3]); }
static V F_Map_dset_dfin(V a2, V a3, V a4, V a5, V a6) {
top:;
return F_Map_dset_dfin_dgo(a2, a3, a4, F_String_dcmp(a5, a6));
}
static V W_Map_dset_dfin(V *a) { (void)a; return F_Map_dset_dfin(a[2], a[3], a[4], a[5], a[6]); }
static V F_Map_dset_dfin_dgo(V a2, V a3, V a4, V a5) {
top:;
V v1021 = a5;
V s1022 = FLD(v1021, 1);
if ((s1022) == IMM(0)) {
return F_Map_dins(a2, a3, a4, F_Map_ddiff(FLD(FLD(v1021, 0), 0), FLD(FLD(v1021, 0), 1)));
} else if ((s1022) == IMM(1)) {
return F_Map_dput(a2, a3, a4);
} else if ((s1022) == IMM(2)) {
return F_Map_dins(a2, a3, a4, F_Map_ddiff(FLD(FLD(v1021, 0), 0), FLD(FLD(v1021, 0), 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Map_dset_dfin_dgo(V *a) { (void)a; return F_Map_dset_dfin_dgo(a[2], a[3], a[4], a[5]); }
static V F_Map_ddiff(V a0, V a1) {
top:;
V s1023 = a0;
V s1024 = a1;
if ((s1023) == IMM(0) && (s1024) == IMM(0)) {
return 0u;
} else if ((s1023) == IMM(0) && TAG(s1024) == 1) {
return 0u;
} else if (TAG(s1023) == 1 && (s1024) == IMM(0)) {
return 0u;
} else if (TAG(s1023) == 1 && TAG(s1024) == 1) {
return F_Map_ddiff_dfin(FLD(s1023, 1), FLD(s1024, 1), F_Map_ddiff_dstep(FLD(s1023, 0), FLD(s1024, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Map_ddiff(V *a) { (void)a; return F_Map_ddiff(a[0], a[1]); }
static V F_Map_ddiff_dstep(V a0, V a1) {
top:;
V s1025 = a0;
V s1026 = a1;
{
return C2(0, F_Map_ddiff_dchr(F_U32_dxor(s1025, s1026)), F_U32_dis__eq(s1025, s1026));
}
}
static V W_Map_ddiff_dstep(V *a) { (void)a; return F_Map_ddiff_dstep(a[0], a[1]); }
static V W_U32_dxor(V *a) { (void)a; return F_U32_dxor(a[0], a[1]); }
static V F_Map_ddiff_dchr(V a0) {
top:;
return F_Nat_dsub(33u, F_Map_dmsb_du(32u, a0));
}
static V W_Map_ddiff_dchr(V *a) { (void)a; return F_Map_ddiff_dchr(a[0]); }
static V F_Map_dmsb_du(V a0, V a1) {
top:;
V s1027 = a0;
if ((s1027) == 0) {
return 0u;
} else if ((s1027) >= 1) {
return F_Map_dmsb_du_dif((s1027 - 1), a1, F_U32_dis__zero(a1));
} else { bend_fail("incomplete match"); }
}
static V W_Map_dmsb_du(V *a) { (void)a; return F_Map_dmsb_du(a[0], a[1]); }
static V F_Map_dmsb_du_dif(V a0, V a1, V a2) {
top:;
V s1028 = a2;
if ((s1028) == IMM(1)) {
return 0u;
} else if ((s1028) == IMM(0)) {
return F_Nat_dadd(1u, F_Map_dmsb_du(a0, F_U32_dshr(a1)));
} else { bend_fail("incomplete match"); }
}
static V W_Map_dmsb_du_dif(V *a) { (void)a; return F_Map_dmsb_du_dif(a[0], a[1], a[2]); }
static V W_U32_dshr(V *a) { (void)a; return F_U32_dshr(a[0]); }
static V W_Nat_dadd(V *a) { (void)a; return F_Nat_dadd(a[0], a[1]); }
static V F_Map_ddiff_dfin(V a0, V a1, V a2) {
top:;
V v1029 = a2;
V s1030 = FLD(v1029, 1);
if ((s1030) == IMM(1)) {
return F_Nat_dadd(33u, F_Map_ddiff(a0, a1));
} else if ((s1030) == IMM(0)) {
return FLD(v1029, 0);
} else { bend_fail("incomplete match"); }
}
static V W_Map_ddiff_dfin(V *a) { (void)a; return F_Map_ddiff_dfin(a[0], a[1], a[2]); }
static V F_Map_dins(V a2, V a3, V a4, V a5) {
top:;
V s1031 = a2;
if ((s1031) == IMM(0)) {
return C2(1, a3, a4);
} else if (TAG(s1031) == 1) {
return F_Map_dins_dsplice(a5, a3, a4, C2(1, FLD(s1031, 0), FLD(s1031, 1)));
} else if (TAG(s1031) == 2) {
return F_Map_dins_dif(a3, a4, FLD(s1031, 1), FLD(s1031, 2), FLD(s1031, 0), a5, F_Nat_dis__lt(FLD(s1031, 0), a5));
} else { bend_fail("incomplete match"); }
}
static V W_Map_dins(V *a) { (void)a; return F_Map_dins(a[2], a[3], a[4], a[5]); }
static V F_Map_dins_dif(V a2, V a3, V a4, V a5, V a6, V a7, V a8) {
top:;
V s1032 = a8;
if ((s1032) == IMM(0)) {
return F_Map_dins_dsplice(a7, a2, a3, C3(2, a6, a4, a5));
} else if ((s1032) == IMM(1)) {
return F_Map_dins_ddeep(a3, a4, a5, a7, a6, F_Map_dbit(a2, a6));
} else { bend_fail("incomplete match"); }
}
static V W_Map_dins_dif(V *a) { (void)a; return F_Map_dins_dif(a[2], a[3], a[4], a[5], a[6], a[7], a[8]); }
static V F_Map_dins_ddeep(V a2, V a3, V a4, V a5, V a6, V a7) {
top:;
V v1033 = a7;
V s1034 = FLD(v1033, 1);
if ((s1034) == IMM(0)) {
return C3(2, a6, F_Map_dins(a3, FLD(v1033, 0), a2, a5), a4);
} else if ((s1034) == IMM(1)) {
return C3(2, a6, a3, F_Map_dins(a4, FLD(v1033, 0), a2, a5));
} else { bend_fail("incomplete match"); }
}
static V W_Map_dins_ddeep(V *a) { (void)a; return F_Map_dins_ddeep(a[2], a[3], a[4], a[5], a[6], a[7]); }
static V F_Map_dins_dsplice(V a2, V a3, V a4, V a5) {
top:;
return F_Map_dins_dsplice_dbit(a4, a5, a2, F_Map_dbit(a3, a2));
}
static V W_Map_dins_dsplice(V *a) { (void)a; return F_Map_dins_dsplice(a[2], a[3], a[4], a[5]); }
static V F_Map_dins_dsplice_dbit(V a2, V a3, V a4, V a5) {
top:;
V v1035 = a5;
V s1036 = FLD(v1035, 1);
if ((s1036) == IMM(0)) {
return C3(2, a4, C2(1, FLD(v1035, 0), a2), a3);
} else if ((s1036) == IMM(1)) {
return C3(2, a4, a3, C2(1, FLD(v1035, 0), a2));
} else { bend_fail("incomplete match"); }
}
static V W_Map_dins_dsplice_dbit(V *a) { (void)a; return F_Map_dins_dsplice_dbit(a[2], a[3], a[4], a[5]); }
static V F_Map_dput(V a2, V a3, V a4) {
top:;
V s1037 = a2;
if ((s1037) == IMM(0)) {
return C2(1, a3, a4);
} else if (TAG(s1037) == 1) {
return C2(1, FLD(s1037, 0), a4);
} else if (TAG(s1037) == 2) {
return F_Map_dput_dbit(a4, FLD(s1037, 0), FLD(s1037, 1), FLD(s1037, 2), F_Map_dbit(a3, FLD(s1037, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Map_dput(V *a) { (void)a; return F_Map_dput(a[2], a[3], a[4]); }
static V F_Map_dput_dbit(V a2, V a3, V a4, V a5, V a6) {
top:;
V v1038 = a6;
V s1039 = FLD(v1038, 1);
if ((s1039) == IMM(0)) {
return C3(2, a3, F_Map_dput(a4, FLD(v1038, 0), a2), a5);
} else if ((s1039) == IMM(1)) {
return C3(2, a3, a4, F_Map_dput(a5, FLD(v1038, 0), a2));
} else { bend_fail("incomplete match"); }
}
static V W_Map_dput_dbit(V *a) { (void)a; return F_Map_dput_dbit(a[2], a[3], a[4], a[5], a[6]); }
static V L1040(V *a) {
return F_Gen_dtake__refs_dgo(a[0]);
}
static V F_Gen_dtake__refs(void) {
top:;
return mk_clo(L1040, 1, 0, 0);
}
static V W_Gen_dtake__refs(V *a) { (void)a; return F_Gen_dtake__refs(); }
static V F_Gen_dtake__refs_dgo(V a0) {
top:;
V v1041 = a0;
return C2(0, FLD(v1041, 3), CN(0, 6, (V[]){FLD(v1041, 0), FLD(v1041, 1), FLD(v1041, 2), IMM(0), FLD(v1041, 4), FLD(v1041, 5)}));
}
static V W_Gen_dtake__refs_dgo(V *a) { (void)a; return F_Gen_dtake__refs_dgo(a[0]); }
static V F_Gen_ddef(V a0, V a1) {
top:;
return F_Gen_ddef_ddecl(a0, a1, F_G_ddef(a0, a1), F_G_dbody(a0, a1));
}
static V W_Gen_ddef(V *a) { (void)a; return F_Gen_ddef(a[0], a[1]); }
static V F_G_ddef(V a0, V a1) {
top:;
V v1042 = a0;
return F_G_dget(C2(0, 99u, IMM(0)), FLD(v1042, 1), a1);
}
static V W_G_ddef(V *a) { (void)a; return F_G_ddef(a[0], a[1]); }
static V F_Gen_ddef_ddecl(V a0, V a1, V a2, V a3) {
top:;
V v1043 = a2;
V s1044 = a3;
if (TAG(s1044) == 0) {
return F_Gen_ddef_dnative(a0, a1, FLD(v1043, 1), FLD(s1044, 2), F_Gen_dsig(FLD(s1044, 1), FLD(v1043, 1), 0u, C3(0, IMM(0), IMM(0), IMM(0))), F_U32_dis__eq(FLD(v1043, 0), 2u));
} else if (TAG(s1044) == 1) {
return F_Gen_ddef_deff(a1, F_Gen_dsig(FLD(s1044, 1), FLD(v1043, 1), 0u, C3(0, IMM(0), IMM(0), IMM(0))));
} else {
return F_Gen_ddef_dlaw(a1, FLD(v1043, 1), F_U32_dis__eq(FLD(v1043, 0), 2u));
}
}
static V W_Gen_ddef_ddecl(V *a) { (void)a; return F_Gen_ddef_ddecl(a[0], a[1], a[2], a[3]); }
static V F_Gen_ddef_dlaw(V a0, V a1, V a2) {
top:;
V s1045 = a2;
if ((s1045) == IMM(1)) {
return F_Gen_dwrapper(a0, F_Sig_dwargs(F_Gen_dsig(F_Gen_ddummy__params(a1), a1, 0u, C3(0, IMM(0), IMM(0), IMM(0)))));
} else if ((s1045) == IMM(0)) {
return F_Gen_dpure(IMM(0));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_ddef_dlaw(V *a) { (void)a; return F_Gen_ddef_dlaw(a[0], a[1], a[2]); }
static V S1047(void) { static V c; if (!c) c = MKS("_"); return c; }
static V S1048(void) { static V c; if (!c) c = MKS(""); return c; }
static V F_Gen_ddummy__params(V a0) {
top:;
V s1046 = a0;
if ((s1046) == IMM(0)) {
return IMM(0);
} else if (TAG(s1046) == 1) {
return C2(1, C3(0, S1047(), 0u, S1048()), F_Gen_ddummy__params(FLD(s1046, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_ddummy__params(V *a) { (void)a; return F_Gen_ddummy__params(a[0]); }
static V S1053(void) { static V c; if (!c) c = MKS("a"); return c; }
static V S1054(void) { static V c; if (!c) c = MKS("a["); return c; }
static V S1055(void) { static V c; if (!c) c = MKS("]"); return c; }
static V S1057(void) { static V c; if (!c) c = MKS("0"); return c; }
static V F_Gen_dsig(V a0, V a1, V a2, V a3) {
top:;
V s1049 = a0;
V s1050 = a1;
if (TAG(s1049) == 1 && TAG(s1050) == 1 && (FLD(s1050, 0)) == IMM(1)) {
V v1051 = a3;
V v1052 = F_String_dappend(S1053(), F_U32_dshow(a2));
{ V t0 = FLD(s1049, 1); V t1 = FLD(s1050, 1); V t2 = F_U32_dinc(a2); V t3 = C3(0, F_List_dappend(FLD(v1051, 0), C2(1, v1052, IMM(0))), C2(1, C2(0, FLD(FLD(s1049, 0), 0), v1052), FLD(v1051, 1)), F_List_dappend(FLD(v1051, 2), C2(1, F_String_dappend(S1054(), F_String_dappend(F_U32_dshow(a2), S1055())), IMM(0)))); a0 = t0; a1 = t1; a2 = t2; a3 = t3; goto top; }
} else if (TAG(s1049) == 1 && TAG(s1050) == 1 && (FLD(s1050, 0)) == IMM(0)) {
V v1056 = a3;
{ V t0 = FLD(s1049, 1); V t1 = FLD(s1050, 1); V t2 = F_U32_dinc(a2); V t3 = C3(0, FLD(v1056, 0), C2(1, C2(0, FLD(FLD(s1049, 0), 0), S1057()), FLD(v1056, 1)), FLD(v1056, 2)); a0 = t0; a1 = t1; a2 = t2; a3 = t3; goto top; }
} else {
return a3;
}
}
static V W_Gen_dsig(V *a) { (void)a; return F_Gen_dsig(a[0], a[1], a[2], a[3]); }
static V F_Sig_dwargs(V a0) {
top:;
V v1058 = a0;
return FLD(v1058, 2);
}
static V W_Sig_dwargs(V *a) { (void)a; return F_Sig_dwargs(a[0]); }
static V S1060(void) { static V c; if (!c) c = MKS("static V "); return c; }
static V S1061(void) { static V c; if (!c) c = MKS("(V *a);\012"); return c; }
static V S1063(void) { static V c; if (!c) c = MKS("static V "); return c; }
static V S1064(void) { static V c; if (!c) c = MKS("(V *a) { (void)a; return "); return c; }
static V S1065(void) { static V c; if (!c) c = MKS("("); return c; }
static V S1066(void) { static V c; if (!c) c = MKS(", "); return c; }
static V S1067(void) { static V c; if (!c) c = MKS("); }\012"); return c; }
static V L1062(V *a) {
return F_Gen_dcode(C1(1, F_String_dappend(S1063(), F_String_dappend(a[2], F_String_dappend(S1064(), F_String_dappend(F_Gen_df(a[1]), F_String_dappend(S1065(), F_String_dappend(F_String_djoin(a[0], S1066()), S1067()))))))));
}
static V F_Gen_dwrapper(V a0, V a1) {
top:;
V v1059 = F_Gen_dw(a0);
return F_Gen_dbind(F_Gen_dproto(C1(1, F_String_dappend(S1060(), F_String_dappend(v1059, S1061())))), mk_clo(L1062, 4, 3, (V[]){a1, a0, v1059}));
}
static V W_Gen_dwrapper(V *a) { (void)a; return F_Gen_dwrapper(a[0], a[1]); }
static V F_String_djoin(V a0, V a1) {
top:;
V s1068 = a0;
if ((s1068) == IMM(0)) {
return IMM(0);
} else if (TAG(s1068) == 1) {
return F_String_djoin_dgo(FLD(s1068, 1), FLD(s1068, 0), a1);
} else { bend_fail("incomplete match"); }
}
static V W_String_djoin(V *a) { (void)a; return F_String_djoin(a[0], a[1]); }
static V F_String_djoin_dgo(V a0, V a1, V a2) {
top:;
V s1069 = a0;
if ((s1069) == IMM(0)) {
return a1;
} else if (TAG(s1069) == 1) {
return F_String_dappend(a1, F_String_dappend(a2, F_String_djoin_dgo(FLD(s1069, 1), FLD(s1069, 0), a2)));
} else { bend_fail("incomplete match"); }
}
static V W_String_djoin_dgo(V *a) { (void)a; return F_String_djoin_dgo(a[0], a[1], a[2]); }
static V S1070(void) { static V c; if (!c) c = MKS("F_"); return c; }
static V F_Gen_df(V a0) {
top:;
return F_String_dappend(S1070(), F_Gen_dmangle(a0));
}
static V W_Gen_df(V *a) { (void)a; return F_Gen_df(a[0]); }
static V S1072(void) { static V c; if (!c) c = MKS(""); return c; }
static V F_Gen_dmangle(V a0) {
top:;
V s1071 = a0;
if ((s1071) == IMM(0)) {
return S1072();
} else if (TAG(s1071) == 1) {
return F_String_dappend(F_Gen_dmangle_dchr(FLD(s1071, 0)), F_Gen_dmangle(FLD(s1071, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dmangle(V *a) { (void)a; return F_Gen_dmangle(a[0]); }
static V S1073(void) { static V c; if (!c) c = MKS("_d"); return c; }
static V S1074(void) { static V c; if (!c) c = MKS("__"); return c; }
static V S1075(void) { static V c; if (!c) c = MKS("_x"); return c; }
static V F_Gen_dmangle_dchr(V a0) {
top:;
return F_Bool_dpick(F_U32_dis__eq(a0, 46u), S1073(), F_Bool_dpick(F_U32_dis__eq(a0, 95u), S1074(), F_Bool_dpick(F_Bool_dor(F_Char_dis__alpha(a0), F_Char_dis__digit(a0)), F_Str_dchr(a0), F_String_dappend(S1075(), F_U32_dshow(a0)))));
}
static V W_Gen_dmangle_dchr(V *a) { (void)a; return F_Gen_dmangle_dchr(a[0]); }
static V F_Str_dchr(V a0) {
top:;
return C2(1, a0, IMM(0));
}
static V W_Str_dchr(V *a) { (void)a; return F_Str_dchr(a[0]); }
static V S1076(void) { static V c; if (!c) c = MKS("W_"); return c; }
static V F_Gen_dw(V a0) {
top:;
return F_String_dappend(S1076(), F_Gen_dmangle(a0));
}
static V W_Gen_dw(V *a) { (void)a; return F_Gen_dw(a[0]); }
static V S1080(void) { static V c; if (!c) c = MKS("E_"); return c; }
static V S1082(void) { static V c; if (!c) c = MKS("static V "); return c; }
static V S1083(void) { static V c; if (!c) c = MKS("("); return c; }
static V S1084(void) { static V c; if (!c) c = MKS(")"); return c; }
static V S1085(void) { static V c; if (!c) c = MKS(";\012static V "); return c; }
static V S1086(void) { static V c; if (!c) c = MKS("(V *a);\012"); return c; }
static V S1088(void) { static V c; if (!c) c = MKS("static V "); return c; }
static V S1089(void) { static V c; if (!c) c = MKS("(V *a) { return apply(a["); return c; }
static V S1090(void) { static V c; if (!c) c = MKS("], H_"); return c; }
static V S1091(void) { static V c; if (!c) c = MKS("("); return c; }
static V S1092(void) { static V c; if (!c) c = MKS(", "); return c; }
static V S1093(void) { static V c; if (!c) c = MKS(")); }\012"); return c; }
static V S1095(void) { static V c; if (!c) c = MKS(" { return mk_clo("); return c; }
static V S1096(void) { static V c; if (!c) c = MKS(", "); return c; }
static V S1097(void) { static V c; if (!c) c = MKS(", "); return c; }
static V S1098(void) { static V c; if (!c) c = MKS(", "); return c; }
static V S1099(void) { static V c; if (!c) c = MKS("0"); return c; }
static V S1100(void) { static V c; if (!c) c = MKS("(V[]){"); return c; }
static V S1101(void) { static V c; if (!c) c = MKS(", "); return c; }
static V S1102(void) { static V c; if (!c) c = MKS("}"); return c; }
static V S1103(void) { static V c; if (!c) c = MKS("); }\012"); return c; }
static V L1104(V *a) {
return F_Gen_dwrapper(a[1], a[0]);
}
static V L1094(V *a) {
return F_Gen_dbind(F_Gen_dcode(C1(1, F_String_dappend(a[5], F_String_dappend(S1095(), F_String_dappend(a[4], F_String_dappend(S1096(), F_String_dappend(F_U32_dshow(F_U32_dadd(a[3], 2u)), F_String_dappend(S1097(), F_String_dappend(F_U32_dshow(a[3]), F_String_dappend(S1098(), F_String_dappend(F_Bool_dpick(F_U32_dis__zero(a[3]), S1099(), F_String_dappend(S1100(), F_String_dappend(F_String_djoin(a[2], S1101()), S1102()))), S1103()))))))))))), mk_clo(L1104, 3, 2, (V[]){a[0], a[1]}));
}
static V L1087(V *a) {
return F_Gen_dbind(F_Gen_dcode(C1(1, F_String_dappend(S1088(), F_String_dappend(a[5], F_String_dappend(S1089(), F_String_dappend(F_U32_dshow(F_U32_dinc(a[4])), F_String_dappend(S1090(), F_String_dappend(F_Gen_dhost(F_String_dto__lower(a[3])), F_String_dappend(S1091(), F_String_dappend(F_String_djoin(F_Gen_deff_dargs(F_U32_dto__nat(a[4]), 0u), S1092()), S1093())))))))))), mk_clo(L1094, 7, 6, (V[]){a[0], a[3], a[1], a[4], a[5], a[2]}));
}
static V F_Gen_ddef_deff(V a0, V a1) {
top:;
V v1077 = a1;
V v1078 = F_U32_dfrom__nat(F_List_dlength(FLD(v1077, 0)));
V v1079 = F_String_dappend(S1080(), F_Gen_dmangle(a0));
V v1081 = F_String_dappend(S1082(), F_String_dappend(F_Gen_df(a0), F_String_dappend(S1083(), F_String_dappend(F_Gen_dcparams(FLD(v1077, 0)), S1084()))));
return F_Gen_dbind(F_Gen_dproto(C1(1, F_String_dappend(v1081, F_String_dappend(S1085(), F_String_dappend(v1079, S1086()))))), mk_clo(L1087, 7, 6, (V[]){FLD(v1077, 2), FLD(v1077, 0), v1081, a0, v1078, v1079}));
}
static V W_Gen_ddef_deff(V *a) { (void)a; return F_Gen_ddef_deff(a[0], a[1]); }
static V S1106(void) { static V c; if (!c) c = MKS("a["); return c; }
static V S1107(void) { static V c; if (!c) c = MKS("]"); return c; }
static V F_Gen_deff_dargs(V a0, V a1) {
top:;
V s1105 = a0;
if ((s1105) == 0) {
return IMM(0);
} else if ((s1105) >= 1) {
return C2(1, F_String_dappend(S1106(), F_String_dappend(F_U32_dshow(a1), S1107())), F_Gen_deff_dargs((s1105 - 1), F_U32_dinc(a1)));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_deff_dargs(V *a) { (void)a; return F_Gen_deff_dargs(a[0], a[1]); }
static V F_String_dto__lower(V a0) {
top:;
V s1108 = a0;
if ((s1108) == IMM(0)) {
return IMM(0);
} else if (TAG(s1108) == 1) {
return C2(1, F_Char_dto__lower(FLD(s1108, 0)), F_String_dto__lower(FLD(s1108, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_String_dto__lower(V *a) { (void)a; return F_String_dto__lower(a[0]); }
static V F_Char_dto__lower(V a0) {
top:;
return F_U32_dadd(F_Char_dto__u32(a0), F_U32_dmul(F_Bool_dto__u32(F_Char_dis__upper(a0)), 32u));
}
static V W_Char_dto__lower(V *a) { (void)a; return F_Char_dto__lower(a[0]); }
static V F_Bool_dto__u32(V a0) {
top:;
V s1109 = a0;
if ((s1109) == IMM(0)) {
return 0u;
} else if ((s1109) == IMM(1)) {
return 1u;
} else { bend_fail("incomplete match"); }
}
static V W_Bool_dto__u32(V *a) { (void)a; return F_Bool_dto__u32(a[0]); }
static V S1111(void) { static V c; if (!c) c = MKS(""); return c; }
static V F_Gen_dhost(V a0) {
top:;
V s1110 = a0;
if ((s1110) == IMM(0)) {
return S1111();
} else if (TAG(s1110) == 1) {
return F_String_dappend(F_Gen_dhost_dchr(FLD(s1110, 0)), F_Gen_dhost(FLD(s1110, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dhost(V *a) { (void)a; return F_Gen_dhost(a[0]); }
static V S1112(void) { static V c; if (!c) c = MKS("_"); return c; }
static V F_Gen_dhost_dchr(V a0) {
top:;
return F_Bool_dpick(F_U32_dis__eq(a0, 46u), S1112(), F_Str_dchr(a0));
}
static V W_Gen_dhost_dchr(V *a) { (void)a; return F_Gen_dhost_dchr(a[0]); }
static V S1114(void) { static V c; if (!c) c = MKS("void"); return c; }
static V S1115(void) { static V c; if (!c) c = MKS(", "); return c; }
static V F_Gen_dcparams(V a0) {
top:;
V s1113 = a0;
if ((s1113) == IMM(0)) {
return S1114();
} else if (TAG(s1113) == 1) {
return F_String_djoin(F_Gen_dcparams_dgo(C2(1, FLD(s1113, 0), FLD(s1113, 1))), S1115());
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dcparams(V *a) { (void)a; return F_Gen_dcparams(a[0]); }
static V S1117(void) { static V c; if (!c) c = MKS("V "); return c; }
static V F_Gen_dcparams_dgo(V a0) {
top:;
V s1116 = a0;
if ((s1116) == IMM(0)) {
return IMM(0);
} else if (TAG(s1116) == 1) {
return C2(1, F_String_dappend(S1117(), FLD(s1116, 0)), F_Gen_dcparams_dgo(FLD(s1116, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dcparams_dgo(V *a) { (void)a; return F_Gen_dcparams_dgo(a[0]); }
static V F_Gen_ddef_dnative(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V s1118 = a5;
if ((s1118) == IMM(1)) {
return F_Gen_dwrapper(a1, F_Sig_dwargs(a4));
} else if ((s1118) == IMM(0)) {
return F_Gen_ddef_dbody(a0, a1, a2, a3, a4);
} else { bend_fail("incomplete match"); }
}
static V W_Gen_ddef_dnative(V *a) { (void)a; return F_Gen_ddef_dnative(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V S1121(void) { static V c; if (!c) c = MKS("static V "); return c; }
static V S1122(void) { static V c; if (!c) c = MKS("("); return c; }
static V S1123(void) { static V c; if (!c) c = MKS(")"); return c; }
static V S1124(void) { static V c; if (!c) c = MKS(";\012"); return c; }
static V S1126(void) { static V c; if (!c) c = MKS("Nat"); return c; }
static V S1128(void) { static V c; if (!c) c = MKS(" {\012top:;\012"); return c; }
static V S1129(void) { static V c; if (!c) c = MKS("}\012"); return c; }
static V L1130(V *a) {
return F_Gen_dwrapper(a[1], a[0]);
}
static V L1127(V *a) {
return F_Gen_dbind(F_Gen_dcode(F_Doc_dlist(C2(1, C1(1, F_String_dappend(a[2], S1128())), C2(1, a[3], C2(1, C1(1, S1129()), IMM(0)))))), mk_clo(L1130, 3, 2, (V[]){a[0], a[1]}));
}
static V L1125(V *a) {
return F_Gen_dbind(F_Gen_dstmt(a[7], a[6], C3(0, a[5], a[4], a[3]), IMM(0), F_R_dops(a[2], S1126())), mk_clo(L1127, 4, 3, (V[]){a[0], a[5], a[1]}));
}
static V F_Gen_ddef_dbody(V a0, V a1, V a2, V a3, V a4) {
top:;
V v1119 = a4;
V v1120 = F_String_dappend(S1121(), F_String_dappend(F_Gen_df(a1), F_String_dappend(S1122(), F_String_dappend(F_Gen_dcparams(FLD(v1119, 0)), S1123()))));
return F_Gen_dbind(F_Gen_dproto(C1(1, F_String_dappend(v1120, S1124()))), mk_clo(L1125, 9, 8, (V[]){FLD(v1119, 2), v1120, a3, FLD(v1119, 0), a2, a1, FLD(v1119, 1), a0}));
}
static V W_Gen_ddef_dbody(V *a) { (void)a; return F_Gen_ddef_dbody(a[0], a[1], a[2], a[3], a[4]); }
static V S1132(void) { static V c; if (!c) c = MKS("."); return c; }
static V F_R_dops(V a0, V a1) {
top:;
V s1131 = a0;
if (TAG(s1131) == 12) {
return C2(5, C1(0, F_String_dappend(a1, F_String_dappend(S1132(), F_R_dopname(FLD(s1131, 0))))), C2(1, F_R_dops(FLD(s1131, 1), a1), C2(1, F_R_dops(FLD(s1131, 2), a1), IMM(0))));
} else if (TAG(s1131) == 13) {
{ V t0 = FLD(s1131, 0); V t1 = F_Bool_dpick(F_String_dis__empty(FLD(s1131, 1)), a1, FLD(s1131, 1)); a0 = t0; a1 = t1; goto top; }
} else if (TAG(s1131) == 5) {
return C2(5, F_R_dops(FLD(s1131, 0), a1), F_R_dopss(FLD(s1131, 1), a1));
} else if (TAG(s1131) == 6) {
return C2(6, FLD(s1131, 0), F_R_dopss(FLD(s1131, 1), a1));
} else if (TAG(s1131) == 7) {
return C2(7, FLD(s1131, 0), F_R_dops(FLD(s1131, 1), a1));
} else if (TAG(s1131) == 8) {
return C3(8, FLD(s1131, 0), F_R_dops(FLD(s1131, 1), a1), F_R_dops(FLD(s1131, 2), a1));
} else if (TAG(s1131) == 9) {
return C2(9, F_R_dopss(FLD(s1131, 0), a1), F_R_dopss(FLD(s1131, 1), a1));
} else if (TAG(s1131) == 10) {
return C2(10, FLD(s1131, 0), F_R_dops(FLD(s1131, 1), a1));
} else if (TAG(s1131) == 11) {
return C2(11, FLD(s1131, 0), F_R_dops(FLD(s1131, 1), a1));
} else {
return s1131;
}
}
static V W_R_dops(V *a) { (void)a; return F_R_dops(a[0], a[1]); }
static V F_R_dopss(V a0, V a1) {
top:;
V s1133 = a0;
if ((s1133) == IMM(0)) {
return IMM(0);
} else if (TAG(s1133) == 1) {
return C2(1, F_R_dops(FLD(s1133, 0), a1), F_R_dopss(FLD(s1133, 1), a1));
} else { bend_fail("incomplete match"); }
}
static V W_R_dopss(V *a) { (void)a; return F_R_dopss(a[0], a[1]); }
static V S1134(void) { static V c; if (!c) c = MKS("+"); return c; }
static V S1135(void) { static V c; if (!c) c = MKS("-"); return c; }
static V S1136(void) { static V c; if (!c) c = MKS("*"); return c; }
static V S1137(void) { static V c; if (!c) c = MKS("/"); return c; }
static V S1138(void) { static V c; if (!c) c = MKS("%"); return c; }
static V S1139(void) { static V c; if (!c) c = MKS("<"); return c; }
static V S1140(void) { static V c; if (!c) c = MKS("<="); return c; }
static V S1141(void) { static V c; if (!c) c = MKS(">"); return c; }
static V S1142(void) { static V c; if (!c) c = MKS(">="); return c; }
static V S1143(void) { static V c; if (!c) c = MKS(".&."); return c; }
static V S1144(void) { static V c; if (!c) c = MKS(".|."); return c; }
static V S1145(void) { static V c; if (!c) c = MKS(".^."); return c; }
static V S1146(void) { static V c; if (!c) c = MKS("<<"); return c; }
static V S1147(void) { static V c; if (!c) c = MKS(">>"); return c; }
static V F_R_dopname(V a0) {
top:;
return F_R_dopname_dgo(F_P_dwhich(a0, C2(1, S1134(), C2(1, S1135(), C2(1, S1136(), C2(1, S1137(), C2(1, S1138(), C2(1, S1139(), C2(1, S1140(), C2(1, S1141(), C2(1, S1142(), C2(1, S1143(), C2(1, S1144(), C2(1, S1145(), C2(1, S1146(), C2(1, S1147(), IMM(0)))))))))))))))));
}
static V W_R_dopname(V *a) { (void)a; return F_R_dopname(a[0]); }
static V S1149(void) { static V c; if (!c) c = MKS("add"); return c; }
static V S1150(void) { static V c; if (!c) c = MKS("sub"); return c; }
static V S1151(void) { static V c; if (!c) c = MKS("mul"); return c; }
static V S1152(void) { static V c; if (!c) c = MKS("div"); return c; }
static V S1153(void) { static V c; if (!c) c = MKS("mod"); return c; }
static V S1154(void) { static V c; if (!c) c = MKS("is_lt"); return c; }
static V S1155(void) { static V c; if (!c) c = MKS("is_le"); return c; }
static V S1156(void) { static V c; if (!c) c = MKS("is_gt"); return c; }
static V S1157(void) { static V c; if (!c) c = MKS("is_ge"); return c; }
static V S1158(void) { static V c; if (!c) c = MKS("and"); return c; }
static V S1159(void) { static V c; if (!c) c = MKS("or"); return c; }
static V S1160(void) { static V c; if (!c) c = MKS("xor"); return c; }
static V S1161(void) { static V c; if (!c) c = MKS("shln"); return c; }
static V S1162(void) { static V c; if (!c) c = MKS("shrn"); return c; }
static V S1163(void) { static V c; if (!c) c = MKS("\077"); return c; }
static V F_R_dopname_dgo(V a0) {
top:;
V s1148 = a0;
if ((s1148) == 0) {
return S1149();
} else if ((s1148) == 1) {
return S1150();
} else if ((s1148) == 2) {
return S1151();
} else if ((s1148) == 3) {
return S1152();
} else if ((s1148) == 4) {
return S1153();
} else if ((s1148) == 5) {
return S1154();
} else if ((s1148) == 6) {
return S1155();
} else if ((s1148) == 7) {
return S1156();
} else if ((s1148) == 8) {
return S1157();
} else if ((s1148) == 9) {
return S1158();
} else if ((s1148) == 10) {
return S1159();
} else if ((s1148) == 11) {
return S1160();
} else if ((s1148) == 12) {
return S1161();
} else if ((s1148) == 13) {
return S1162();
} else if ((s1148) >= 14) {
return S1163();
} else { bend_fail("incomplete match"); }
}
static V W_R_dopname_dgo(V *a) { (void)a; return F_R_dopname_dgo(a[0]); }
static V L1165(V *a) {
return F_Gen_dpure(F_Gen_dret(a[0], a[1]));
}
static V F_Gen_dstmt(V a0, V a1, V a2, V a3, V a4) {
top:;
V s1164 = a4;
if (TAG(s1164) == 8) {
return F_Gen_dlet(a0, a1, a2, a3, FLD(s1164, 0), FLD(s1164, 1), FLD(s1164, 2));
} else if (TAG(s1164) == 9) {
return F_Gen_dmatch(a0, a1, a2, a3, FLD(s1164, 0), FLD(s1164, 1));
} else if (TAG(s1164) == 5 && TAG(FLD(s1164, 0)) == 0) {
return F_Gen_dstmt_dcall(a0, a1, a2, a3, FLD(FLD(s1164, 0), 0), FLD(s1164, 1), F_Gen_dis__tail(a1, a2, a3, FLD(FLD(s1164, 0), 0), FLD(s1164, 1)));
} else {
return F_Gen_dbind(F_Gen_dexpr(a0, a1, s1164), mk_clo(L1165, 2, 1, (V[]){a3}));
}
}
static V W_Gen_dstmt(V *a) { (void)a; return F_Gen_dstmt(a[0], a[1], a[2], a[3], a[4]); }
static V S1167(void) { static V c; if (!c) c = MKS("return "); return c; }
static V S1168(void) { static V c; if (!c) c = MKS(";\012"); return c; }
static V S1169(void) { static V c; if (!c) c = MKS(" = "); return c; }
static V S1170(void) { static V c; if (!c) c = MKS(";\012"); return c; }
static V F_Gen_dret(V a0, V a1) {
top:;
V s1166 = a0;
if ((s1166) == IMM(0)) {
return F_Doc_dlist(C2(1, C1(1, S1167()), C2(1, a1, C2(1, C1(1, S1168()), IMM(0)))));
} else if (TAG(s1166) == 1) {
return F_Doc_dlist(C2(1, C1(1, FLD(s1166, 0)), C2(1, C1(1, S1169()), C2(1, a1, C2(1, C1(1, S1170()), IMM(0))))));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dret(V *a) { (void)a; return F_Gen_dret(a[0], a[1]); }
static V S1172(void) { static V c; if (!c) c = MKS("u"); return c; }
static V S1173(void) { static V c; if (!c) c = MKS("u"); return c; }
static V S1174(void) { static V c; if (!c) c = MKS("VF("); return c; }
static V S1175(void) { static V c; if (!c) c = MKS("f)"); return c; }
static V S1177(void) { static V c; if (!c) c = MKS("("); return c; }
static V S1178(void) { static V c; if (!c) c = MKS(" + "); return c; }
static V S1179(void) { static V c; if (!c) c = MKS(")"); return c; }
static V L1176(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, C1(1, S1177()), C2(1, a[1], C2(1, C1(1, F_String_dappend(S1178(), F_String_dappend(F_U32_dshow(a[0]), S1179()))), IMM(0))))));
}
static V S1180(void) { static V c; if (!c) c = MKS("0"); return c; }
static V S1181(void) { static V c; if (!c) c = MKS("parse error: "); return c; }
static V S1183(void) { static V c; if (!c) c = MKS("0"); return c; }
static V L1182(V *a) {
return F_Gen_dpure(C1(1, S1183()));
}
static V S1184(void) { static V c; if (!c) c = MKS("unexpected expression: "); return c; }
static V S1186(void) { static V c; if (!c) c = MKS("0"); return c; }
static V L1185(V *a) {
return F_Gen_dpure(C1(1, S1186()));
}
static V F_Gen_dexpr(V a0, V a1, V a2) {
top:;
V s1171 = a2;
if (TAG(s1171) == 0) {
return F_Gen_dvar(a0, a1, FLD(s1171, 0));
} else if (TAG(s1171) == 1) {
return F_Gen_dpure(C1(1, F_String_dappend(F_U32_dshow(FLD(s1171, 0)), S1172())));
} else if (TAG(s1171) == 2) {
return F_Gen_dpure(C1(1, F_String_dappend(F_U32_dshow(FLD(s1171, 0)), S1173())));
} else if (TAG(s1171) == 3) {
return F_Gen_dpure(C1(1, F_String_dappend(S1174(), F_String_dappend(FLD(s1171, 0), S1175()))));
} else if (TAG(s1171) == 4) {
return F_Gen_dstr(FLD(s1171, 0));
} else if (TAG(s1171) == 5) {
return F_Gen_dcall(a0, a1, FLD(s1171, 0), FLD(s1171, 1));
} else if (TAG(s1171) == 6) {
return F_Gen_dctor(a0, a1, FLD(s1171, 0), FLD(s1171, 1));
} else if (TAG(s1171) == 7) {
return F_Gen_dlam(a0, a1, FLD(s1171, 0), FLD(s1171, 1));
} else if (TAG(s1171) == 8) {
return F_Gen_dblock(a0, a1, C3(8, FLD(s1171, 0), FLD(s1171, 1), FLD(s1171, 2)));
} else if (TAG(s1171) == 9) {
return F_Gen_dblock(a0, a1, C2(9, FLD(s1171, 0), FLD(s1171, 1)));
} else if (TAG(s1171) == 11) {
return F_Gen_dbind(F_Gen_dexpr(a0, a1, FLD(s1171, 1)), mk_clo(L1176, 2, 1, (V[]){FLD(s1171, 0)}));
} else if (TAG(s1171) == 14) {
return F_Gen_dpure(C1(1, S1180()));
} else if (TAG(s1171) == 15) {
return F_Gen_dbind(F_Gen_derror(F_String_dappend(S1181(), FLD(s1171, 0))), mk_clo(L1182, 1, 0, 0));
} else {
return F_Gen_dbind(F_Gen_derror(F_String_dappend(S1184(), F_Expr_dshow(s1171))), mk_clo(L1185, 1, 0, 0));
}
}
static V W_Gen_dexpr(V *a) { (void)a; return F_Gen_dexpr(a[0], a[1], a[2]); }
static V S1188(void) { static V c; if (!c) c = MKS("r"); return c; }
static V S1191(void) { static V c; if (!c) c = MKS("({ V "); return c; }
static V S1192(void) { static V c; if (!c) c = MKS(";\012"); return c; }
static V S1193(void) { static V c; if (!c) c = MKS("; })"); return c; }
static V L1190(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, C1(1, F_String_dappend(S1191(), F_String_dappend(a[0], S1192()))), C2(1, a[1], C2(1, C1(1, F_String_dappend(a[0], S1193())), IMM(0))))));
}
static V L1189(V *a) {
return F_Gen_dbind(F_Gen_dstmt(a[2], a[1], F_Self_dnone(), C1(1, a[3]), a[0]), mk_clo(L1190, 2, 1, (V[]){a[3]}));
}
static V L1187(V *a) {
return F_Gen_dbind(F_Gen_dpure(F_String_dappend(S1188(), F_U32_dshow(a[3]))), mk_clo(L1189, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V F_Gen_dblock(V a0, V a1, V a2) {
top:;
return F_Gen_dbind(F_Gen_dfresh(), mk_clo(L1187, 4, 3, (V[]){a2, a1, a0}));
}
static V W_Gen_dblock(V *a) { (void)a; return F_Gen_dblock(a[0], a[1], a[2]); }
static V S1194(void) { static V c; if (!c) c = MKS(""); return c; }
static V F_Self_dnone(void) {
top:;
return C3(0, S1194(), IMM(0), IMM(0));
}
static V W_Self_dnone(V *a) { (void)a; return F_Self_dnone(); }
static V S1198(void) { static V c; if (!c) c = MKS("L"); return c; }
static V S1200(void) { static V c; if (!c) c = MKS("static V "); return c; }
static V S1201(void) { static V c; if (!c) c = MKS("(V *a);\012"); return c; }
static V S1203(void) { static V c; if (!c) c = MKS("a["); return c; }
static V S1204(void) { static V c; if (!c) c = MKS("]"); return c; }
static V S1207(void) { static V c; if (!c) c = MKS("static V "); return c; }
static V S1208(void) { static V c; if (!c) c = MKS("(V *a) {\012"); return c; }
static V S1209(void) { static V c; if (!c) c = MKS("}\012"); return c; }
static V S1211(void) { static V c; if (!c) c = MKS("mk_clo("); return c; }
static V S1212(void) { static V c; if (!c) c = MKS(", "); return c; }
static V S1213(void) { static V c; if (!c) c = MKS(", "); return c; }
static V S1214(void) { static V c; if (!c) c = MKS(", "); return c; }
static V S1215(void) { static V c; if (!c) c = MKS(")"); return c; }
static V L1210(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, C1(1, F_String_dappend(S1211(), F_String_dappend(a[2], F_String_dappend(S1212(), F_String_dappend(F_U32_dshow(F_U32_dinc(a[1])), F_String_dappend(S1213(), F_String_dappend(F_U32_dshow(a[1]), S1214()))))))), C2(1, F_Gen_darr(F_Gen_dcaps_douter(a[0])), C2(1, C1(1, S1215()), IMM(0))))));
}
static V L1206(V *a) {
return F_Gen_dbind(F_Gen_dcode(F_Doc_dlist(C2(1, C1(1, F_String_dappend(S1207(), F_String_dappend(a[2], S1208()))), C2(1, a[3], C2(1, C1(1, S1209()), IMM(0)))))), mk_clo(L1210, 4, 3, (V[]){a[0], a[1], a[2]}));
}
static V L1205(V *a) {
return F_Gen_dbind(F_Gen_dstmt(a[4], F_List_dappend(a[5], F_Gen_dcaps_dinner(a[3], 0u)), F_Self_dnone(), IMM(0), a[2]), mk_clo(L1206, 4, 3, (V[]){a[3], a[0], a[1]}));
}
static V L1202(V *a) {
return F_Gen_dbind(F_Gen_dpure(F_PatR_dbinds(F_Gen_dpat(a[5], a[4], F_String_dappend(S1203(), F_String_dappend(F_U32_dshow(a[3]), S1204())), C2(0, IMM(0), IMM(0))))), mk_clo(L1205, 6, 5, (V[]){a[3], a[0], a[1], a[2], a[5]}));
}
static V L1199(V *a) {
return F_Gen_dbind(F_Gen_dproto(C1(1, F_String_dappend(S1200(), F_String_dappend(a[5], S1201())))), mk_clo(L1202, 7, 6, (V[]){a[5], a[0], a[1], a[2], a[3], a[4]}));
}
static V L1197(V *a) {
return F_Gen_dbind(F_Gen_dpure(F_String_dappend(S1198(), F_U32_dshow(a[5]))), mk_clo(L1199, 6, 5, (V[]){a[0], a[1], a[2], a[3], a[4]}));
}
static V F_Gen_dlam(V a0, V a1, V a2, V a3) {
top:;
V v1195 = F_Gen_dcaps(F_FV_dexpr(a3, F_Pat_dvars(a2, IMM(0)), IMM(0)), a1);
V v1196 = F_U32_dfrom__nat(F_List_dlength(v1195));
return F_Gen_dbind(F_Gen_dfresh(), mk_clo(L1197, 6, 5, (V[]){a3, v1195, v1196, a2, a0}));
}
static V W_Gen_dlam(V *a) { (void)a; return F_Gen_dlam(a[0], a[1], a[2], a[3]); }
static V F_Gen_dcaps_douter(V a0) {
top:;
V s1216 = a0;
if ((s1216) == IMM(0)) {
return IMM(0);
} else if (TAG(s1216) == 1) {
return C2(1, C1(1, FLD(FLD(s1216, 0), 1)), F_Gen_dcaps_douter(FLD(s1216, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dcaps_douter(V *a) { (void)a; return F_Gen_dcaps_douter(a[0]); }
static V S1218(void) { static V c; if (!c) c = MKS("0"); return c; }
static V S1219(void) { static V c; if (!c) c = MKS("(V[]){"); return c; }
static V S1220(void) { static V c; if (!c) c = MKS("}"); return c; }
static V F_Gen_darr(V a0) {
top:;
V s1217 = a0;
if ((s1217) == IMM(0)) {
return C1(1, S1218());
} else if (TAG(s1217) == 1) {
return F_Doc_dlist(C2(1, C1(1, S1219()), C2(1, F_Gen_dcommas(C2(1, FLD(s1217, 0), FLD(s1217, 1))), C2(1, C1(1, S1220()), IMM(0)))));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_darr(V *a) { (void)a; return F_Gen_darr(a[0]); }
static V S1221(void) { static V c; if (!c) c = MKS(", "); return c; }
static V F_Gen_dcommas(V a0) {
top:;
return F_Doc_dsep(a0, S1221());
}
static V W_Gen_dcommas(V *a) { (void)a; return F_Gen_dcommas(a[0]); }
static V F_Doc_dsep(V a0, V a1) {
top:;
V s1222 = a0;
if ((s1222) == IMM(0)) {
return IMM(0);
} else if (TAG(s1222) == 1) {
return C2(2, FLD(s1222, 0), F_Doc_dsep_dgo(FLD(s1222, 1), a1));
} else { bend_fail("incomplete match"); }
}
static V W_Doc_dsep(V *a) { (void)a; return F_Doc_dsep(a[0], a[1]); }
static V F_Doc_dsep_dgo(V a0, V a1) {
top:;
V s1223 = a0;
if ((s1223) == IMM(0)) {
return IMM(0);
} else if (TAG(s1223) == 1) {
return C2(2, C1(1, a1), C2(2, FLD(s1223, 0), F_Doc_dsep_dgo(FLD(s1223, 1), a1)));
} else { bend_fail("incomplete match"); }
}
static V W_Doc_dsep_dgo(V *a) { (void)a; return F_Doc_dsep_dgo(a[0], a[1]); }
static V S1225(void) { static V c; if (!c) c = MKS("a["); return c; }
static V S1226(void) { static V c; if (!c) c = MKS("]"); return c; }
static V F_Gen_dcaps_dinner(V a0, V a1) {
top:;
V s1224 = a0;
if ((s1224) == IMM(0)) {
return IMM(0);
} else if (TAG(s1224) == 1) {
return C2(1, C2(0, FLD(FLD(s1224, 0), 0), F_String_dappend(S1225(), F_String_dappend(F_U32_dshow(a1), S1226()))), F_Gen_dcaps_dinner(FLD(s1224, 1), F_U32_dinc(a1)));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dcaps_dinner(V *a) { (void)a; return F_Gen_dcaps_dinner(a[0], a[1]); }
static V S1228(void) { static V c; if (!c) c = MKS("("); return c; }
static V S1229(void) { static V c; if (!c) c = MKS(") == "); return c; }
static V S1230(void) { static V c; if (!c) c = MKS("("); return c; }
static V S1231(void) { static V c; if (!c) c = MKS(" - "); return c; }
static V S1232(void) { static V c; if (!c) c = MKS(")"); return c; }
static V S1233(void) { static V c; if (!c) c = MKS("("); return c; }
static V S1234(void) { static V c; if (!c) c = MKS(") >= "); return c; }
static V S1235(void) { static V c; if (!c) c = MKS("("); return c; }
static V S1236(void) { static V c; if (!c) c = MKS(") == "); return c; }
static V F_Gen_dpat(V a0, V a1, V a2, V a3) {
top:;
V s1227 = a1;
if (TAG(s1227) == 0) {
return F_Gen_dpat_dvar(FLD(s1227, 0), a2, a3);
} else if (TAG(s1227) == 1) {
return F_Gen_dpat_dctor(a0, F_G_dctor(a0, FLD(s1227, 0)), FLD(s1227, 0), FLD(s1227, 1), a2, a3);
} else if (TAG(s1227) == 2) {
return F_Gen_dpat_dcond(F_String_dappend(S1228(), F_String_dappend(a2, F_String_dappend(S1229(), F_U32_dshow(FLD(s1227, 0))))), a3);
} else if (TAG(s1227) == 3) {
{ V t0 = a0; V t1 = FLD(s1227, 1); V t2 = F_String_dappend(S1230(), F_String_dappend(a2, F_String_dappend(S1231(), F_String_dappend(F_U32_dshow(FLD(s1227, 0)), S1232())))); V t3 = F_Gen_dpat_dcond(F_String_dappend(S1233(), F_String_dappend(a2, F_String_dappend(S1234(), F_U32_dshow(FLD(s1227, 0))))), a3); a0 = t0; a1 = t1; a2 = t2; a3 = t3; goto top; }
} else if (TAG(s1227) == 4) {
return F_Gen_dpat_dcond(F_String_dappend(S1235(), F_String_dappend(a2, F_String_dappend(S1236(), F_U32_dshow(FLD(s1227, 0))))), a3);
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dpat(V *a) { (void)a; return F_Gen_dpat(a[0], a[1], a[2], a[3]); }
static V F_Gen_dpat_dcond(V a0, V a1) {
top:;
V v1237 = a1;
return C2(0, C2(1, a0, FLD(v1237, 0)), FLD(v1237, 1));
}
static V W_Gen_dpat_dcond(V *a) { (void)a; return F_Gen_dpat_dcond(a[0], a[1]); }
static V S1239(void) { static V c; if (!c) c = MKS("0 /* unknown constructor "); return c; }
static V S1240(void) { static V c; if (!c) c = MKS(" */"); return c; }
static V F_Gen_dpat_dctor(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V s1238 = a1;
if ((s1238) == IMM(0)) {
return F_Gen_dpat_dcond(F_String_dappend(S1239(), F_String_dappend(a2, S1240())), a5);
} else if (TAG(s1238) == 1) {
return F_Gen_dpat_dkind(a0, F_U32_dto__nat(FLD(FLD(s1238, 0), 2)), FLD(FLD(s1238, 0), 0), FLD(FLD(s1238, 0), 3), a3, a4, a5);
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dpat_dctor(V *a) { (void)a; return F_Gen_dpat_dctor(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V S1242(void) { static V c; if (!c) c = MKS("TAG("); return c; }
static V S1243(void) { static V c; if (!c) c = MKS(") == "); return c; }
static V S1244(void) { static V c; if (!c) c = MKS("("); return c; }
static V S1245(void) { static V c; if (!c) c = MKS(") == IMM("); return c; }
static V S1246(void) { static V c; if (!c) c = MKS(")"); return c; }
static V S1247(void) { static V c; if (!c) c = MKS("("); return c; }
static V S1248(void) { static V c; if (!c) c = MKS(") == 0"); return c; }
static V S1249(void) { static V c; if (!c) c = MKS("("); return c; }
static V S1250(void) { static V c; if (!c) c = MKS(" - 1)"); return c; }
static V S1251(void) { static V c; if (!c) c = MKS("("); return c; }
static V S1252(void) { static V c; if (!c) c = MKS(") != 0"); return c; }
static V F_Gen_dpat_dkind(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V s1241 = a1;
if ((s1241) == 0) {
return F_Gen_dpat_dfields(a0, a4, a5, 0u, F_Gen_dpat_dtag(a3, F_String_dappend(S1242(), F_String_dappend(a5, F_String_dappend(S1243(), F_U32_dshow(a2)))), a6));
} else if ((s1241) == 1) {
return F_Gen_dpat_dtag(a3, F_String_dappend(S1244(), F_String_dappend(a5, F_String_dappend(S1245(), F_String_dappend(F_U32_dshow(a2), S1246())))), a6);
} else if ((s1241) == 2) {
return F_Gen_dpat_dfields(a0, a4, a5, 99u, a6);
} else if ((s1241) == 3) {
return F_Gen_dpat_dcond(F_String_dappend(S1247(), F_String_dappend(a5, S1248())), a6);
} else if ((s1241) >= 4) {
return F_Gen_dpat_dfields(a0, a4, F_String_dappend(S1249(), F_String_dappend(a5, S1250())), 99u, F_Gen_dpat_dcond(F_String_dappend(S1251(), F_String_dappend(a5, S1252())), a6));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dpat_dkind(V *a) { (void)a; return F_Gen_dpat_dkind(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V S1254(void) { static V c; if (!c) c = MKS("FLD("); return c; }
static V S1255(void) { static V c; if (!c) c = MKS(", "); return c; }
static V S1256(void) { static V c; if (!c) c = MKS(")"); return c; }
static V F_Gen_dpat_dfields(V a0, V a1, V a2, V a3, V a4) {
top:;
V s1253 = a1;
if ((s1253) == IMM(0)) {
return a4;
} else if (TAG(s1253) == 1) {
{ V t0 = a0; V t1 = FLD(s1253, 1); V t2 = a2; V t3 = F_U32_dinc(a3); V t4 = F_Gen_dpat(a0, FLD(s1253, 0), F_Bool_dpick(F_U32_dis__eq(a3, 99u), a2, F_String_dappend(S1254(), F_String_dappend(a2, F_String_dappend(S1255(), F_String_dappend(F_U32_dshow(a3), S1256()))))), a4); a0 = t0; a1 = t1; a2 = t2; a3 = t3; a4 = t4; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dpat_dfields(V *a) { (void)a; return F_Gen_dpat_dfields(a[0], a[1], a[2], a[3], a[4]); }
static V F_Gen_dpat_dtag(V a0, V a1, V a2) {
top:;
V s1257 = a0;
if ((s1257) == IMM(1)) {
return a2;
} else if ((s1257) == IMM(0)) {
return F_Gen_dpat_dcond(a1, a2);
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dpat_dtag(V *a) { (void)a; return F_Gen_dpat_dtag(a[0], a[1], a[2]); }
static V S1259(void) { static V c; if (!c) c = MKS("_"); return c; }
static V F_Gen_dpat_dvar(V a0, V a1, V a2) {
top:;
V v1258 = a2;
return C2(0, FLD(v1258, 0), F_Bool_dpick(F_Str_deq(a0, S1259()), FLD(v1258, 1), C2(1, C2(0, a0, a1), FLD(v1258, 1))));
}
static V W_Gen_dpat_dvar(V *a) { (void)a; return F_Gen_dpat_dvar(a[0], a[1], a[2]); }
static V F_PatR_dbinds(V a0) {
top:;
V v1260 = a0;
return FLD(v1260, 1);
}
static V W_PatR_dbinds(V *a) { (void)a; return F_PatR_dbinds(a[0]); }
static V F_Pat_dvars(V a0, V a1) {
top:;
V s1261 = a0;
if (TAG(s1261) == 0) {
return C2(1, FLD(s1261, 0), a1);
} else if (TAG(s1261) == 1) {
return F_Pats_dvars(FLD(s1261, 1), a1);
} else if (TAG(s1261) == 3) {
{ V t0 = FLD(s1261, 1); V t1 = a1; a0 = t0; a1 = t1; goto top; }
} else {
return a1;
}
}
static V W_Pat_dvars(V *a) { (void)a; return F_Pat_dvars(a[0], a[1]); }
static V F_Pats_dvars(V a0, V a1) {
top:;
V s1262 = a0;
if ((s1262) == IMM(0)) {
return a1;
} else if (TAG(s1262) == 1) {
{ V t0 = FLD(s1262, 1); V t1 = F_Pat_dvars(FLD(s1262, 0), a1); a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Pats_dvars(V *a) { (void)a; return F_Pats_dvars(a[0], a[1]); }
static V F_FV_dexpr(V a0, V a1, V a2) {
top:;
V s1263 = a0;
if (TAG(s1263) == 0) {
return F_FV_dvar(FLD(s1263, 0), a1, a2);
} else if (TAG(s1263) == 5) {
return F_FV_dexprs(FLD(s1263, 1), a1, F_FV_dexpr(FLD(s1263, 0), a1, a2));
} else if (TAG(s1263) == 6) {
return F_FV_dexprs(FLD(s1263, 1), a1, a2);
} else if (TAG(s1263) == 7) {
{ V t0 = FLD(s1263, 1); V t1 = F_Pat_dvars(FLD(s1263, 0), a1); V t2 = a2; a0 = t0; a1 = t1; a2 = t2; goto top; }
} else if (TAG(s1263) == 8) {
{ V t0 = FLD(s1263, 2); V t1 = F_Pat_dvars(FLD(s1263, 0), a1); V t2 = F_FV_dexpr(FLD(s1263, 1), a1, a2); a0 = t0; a1 = t1; a2 = t2; goto top; }
} else if (TAG(s1263) == 9) {
return F_FV_dexprs(FLD(s1263, 1), a1, F_FV_dexprs(FLD(s1263, 0), a1, a2));
} else if (TAG(s1263) == 10) {
{ V t0 = FLD(s1263, 1); V t1 = F_Pats_dvars(FLD(s1263, 0), a1); V t2 = a2; a0 = t0; a1 = t1; a2 = t2; goto top; }
} else if (TAG(s1263) == 11) {
{ V t0 = FLD(s1263, 1); V t1 = a1; V t2 = a2; a0 = t0; a1 = t1; a2 = t2; goto top; }
} else if (TAG(s1263) == 12) {
{ V t0 = FLD(s1263, 2); V t1 = a1; V t2 = F_FV_dexpr(FLD(s1263, 1), a1, a2); a0 = t0; a1 = t1; a2 = t2; goto top; }
} else if (TAG(s1263) == 13) {
{ V t0 = FLD(s1263, 0); V t1 = a1; V t2 = a2; a0 = t0; a1 = t1; a2 = t2; goto top; }
} else {
return a2;
}
}
static V W_FV_dexpr(V *a) { (void)a; return F_FV_dexpr(a[0], a[1], a[2]); }
static V F_FV_dexprs(V a0, V a1, V a2) {
top:;
V s1264 = a0;
if ((s1264) == IMM(0)) {
return a2;
} else if (TAG(s1264) == 1) {
{ V t0 = FLD(s1264, 1); V t1 = a1; V t2 = F_FV_dexpr(FLD(s1264, 0), a1, a2); a0 = t0; a1 = t1; a2 = t2; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_FV_dexprs(V *a) { (void)a; return F_FV_dexprs(a[0], a[1], a[2]); }
static V F_FV_dvar(V a0, V a1, V a2) {
top:;
return F_Bool_dpick(F_Bool_dor(F_Str_dhas(a1, a0), F_Str_dhas(a2, a0)), a2, C2(1, a0, a2));
}
static V W_FV_dvar(V *a) { (void)a; return F_FV_dvar(a[0], a[1], a[2]); }
static V F_Str_dhas(V a0, V a1) {
top:;
return F_List_dcontains(mk_clo(W_String_deq, 2, 0, 0), a0, a1);
}
static V W_Str_dhas(V *a) { (void)a; return F_Str_dhas(a[0], a[1]); }
static V F_Gen_dcaps(V a0, V a1) {
top:;
V s1265 = a0;
if ((s1265) == IMM(0)) {
return IMM(0);
} else if (TAG(s1265) == 1) {
return F_Gen_dcaps_dput(FLD(s1265, 0), F_Env_dfind(a1, FLD(s1265, 0)), F_Gen_dcaps(FLD(s1265, 1), a1));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dcaps(V *a) { (void)a; return F_Gen_dcaps(a[0], a[1]); }
static V F_Gen_dcaps_dput(V a0, V a1, V a2) {
top:;
V s1266 = a1;
if ((s1266) == IMM(0)) {
return a2;
} else if (TAG(s1266) == 1) {
return C2(1, C2(0, a0, FLD(s1266, 0)), a2);
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dcaps_dput(V *a) { (void)a; return F_Gen_dcaps_dput(a[0], a[1], a[2]); }
static V F_Gen_dctor(V a0, V a1, V a2, V a3) {
top:;
return F_Gen_dctor_dinfo(a0, a1, a2, F_G_dctor(a0, a2), a3);
}
static V W_Gen_dctor(V *a) { (void)a; return F_Gen_dctor(a[0], a[1], a[2], a[3]); }
static V S1268(void) { static V c; if (!c) c = MKS("unknown constructor: "); return c; }
static V S1270(void) { static V c; if (!c) c = MKS("0"); return c; }
static V L1269(V *a) {
return F_Gen_dpure(C1(1, S1270()));
}
static V L1271(V *a) {
return F_Gen_dpure(F_Gen_dctor_dkind(a[1], F_U32_dto__nat(a[0]), a[2]));
}
static V F_Gen_dctor_dinfo(V a0, V a1, V a2, V a3, V a4) {
top:;
V s1267 = a3;
if ((s1267) == IMM(0)) {
return F_Gen_dbind(F_Gen_derror(F_String_dappend(S1268(), a2)), mk_clo(L1269, 1, 0, 0));
} else if (TAG(s1267) == 1) {
return F_Gen_dbind(F_Gen_dexprs(a0, a1, a4), mk_clo(L1271, 3, 2, (V[]){FLD(FLD(s1267, 0), 2), FLD(FLD(s1267, 0), 0)}));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dctor_dinfo(V *a) { (void)a; return F_Gen_dctor_dinfo(a[0], a[1], a[2], a[3], a[4]); }
static V S1273(void) { static V c; if (!c) c = MKS("IMM("); return c; }
static V S1274(void) { static V c; if (!c) c = MKS(")"); return c; }
static V S1275(void) { static V c; if (!c) c = MKS("0"); return c; }
static V S1276(void) { static V c; if (!c) c = MKS("("); return c; }
static V S1277(void) { static V c; if (!c) c = MKS(" + 1)"); return c; }
static V F_Gen_dctor_dkind(V a0, V a1, V a2) {
top:;
V s1272 = a1;
if ((s1272) == 0) {
return F_Gen_dctor_dnode(a0, a2);
} else if ((s1272) == 1) {
return C1(1, F_String_dappend(S1273(), F_String_dappend(F_U32_dshow(a0), S1274())));
} else if ((s1272) == 2) {
return F_Doc_dlist(a2);
} else if ((s1272) == 3) {
return C1(1, S1275());
} else if ((s1272) >= 4) {
return F_Doc_dlist(C2(1, C1(1, S1276()), C2(1, F_Doc_dlist(a2), C2(1, C1(1, S1277()), IMM(0)))));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dctor_dkind(V *a) { (void)a; return F_Gen_dctor_dkind(a[0], a[1], a[2]); }
static V S1279(void) { static V c; if (!c) c = MKS("C"); return c; }
static V S1280(void) { static V c; if (!c) c = MKS("("); return c; }
static V S1281(void) { static V c; if (!c) c = MKS(", "); return c; }
static V S1282(void) { static V c; if (!c) c = MKS(")"); return c; }
static V S1283(void) { static V c; if (!c) c = MKS("CN("); return c; }
static V S1284(void) { static V c; if (!c) c = MKS(", "); return c; }
static V S1285(void) { static V c; if (!c) c = MKS(", "); return c; }
static V S1286(void) { static V c; if (!c) c = MKS(")"); return c; }
static V F_Gen_dctor_dnode(V a0, V a1) {
top:;
V v1278 = F_Gen_dlen(a1);
return F_Bool_dpick(F_U32_dis__le(v1278, 4u), F_Doc_dlist(C2(1, C1(1, F_String_dappend(S1279(), F_String_dappend(F_U32_dshow(v1278), F_String_dappend(S1280(), F_String_dappend(F_U32_dshow(a0), S1281()))))), C2(1, F_Gen_dcommas(a1), C2(1, C1(1, S1282()), IMM(0))))), F_Doc_dlist(C2(1, C1(1, F_String_dappend(S1283(), F_String_dappend(F_U32_dshow(a0), F_String_dappend(S1284(), F_String_dappend(F_U32_dshow(v1278), S1285()))))), C2(1, F_Gen_darr(a1), C2(1, C1(1, S1286()), IMM(0))))));
}
static V W_Gen_dctor_dnode(V *a) { (void)a; return F_Gen_dctor_dnode(a[0], a[1]); }
static V F_Gen_dlen(V a0) {
top:;
return F_U32_dfrom__nat(F_List_dlength(a0));
}
static V W_Gen_dlen(V *a) { (void)a; return F_Gen_dlen(a[0]); }
static V L1289(V *a) {
return F_Gen_dpure(C2(1, a[0], a[1]));
}
static V L1288(V *a) {
return F_Gen_dbind(F_Gen_dexprs(a[2], a[1], a[0]), mk_clo(L1289, 2, 1, (V[]){a[3]}));
}
static V F_Gen_dexprs(V a0, V a1, V a2) {
top:;
V s1287 = a2;
if ((s1287) == IMM(0)) {
return F_Gen_dpure(IMM(0));
} else if (TAG(s1287) == 1) {
return F_Gen_dbind(F_Gen_dexpr(a0, a1, FLD(s1287, 0)), mk_clo(L1288, 4, 3, (V[]){FLD(s1287, 1), a1, a0}));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dexprs(V *a) { (void)a; return F_Gen_dexprs(a[0], a[1], a[2]); }
static V F_Gen_dcall(V a0, V a1, V a2, V a3) {
top:;
V s1290 = a2;
if (TAG(s1290) == 0) {
return F_Gen_dcall_dvar(a0, a1, FLD(s1290, 0), a3, F_Env_dhas(a1, FLD(s1290, 0)));
} else {
return F_Gen_dcall_dlocal(a0, a1, s1290, a3);
}
}
static V W_Gen_dcall(V *a) { (void)a; return F_Gen_dcall(a[0], a[1], a[2], a[3]); }
static V L1292(V *a) {
return F_Gen_dpure(F_Gen_dapply(a[1], a[0]));
}
static V L1291(V *a) {
return F_Gen_dbind(F_Gen_dexprs(a[2], a[1], a[0]), mk_clo(L1292, 2, 1, (V[]){a[3]}));
}
static V F_Gen_dcall_dlocal(V a0, V a1, V a2, V a3) {
top:;
return F_Gen_dbind(F_Gen_dexpr(a0, a1, a2), mk_clo(L1291, 4, 3, (V[]){a3, a1, a0}));
}
static V W_Gen_dcall_dlocal(V *a) { (void)a; return F_Gen_dcall_dlocal(a[0], a[1], a[2], a[3]); }
static V S1294(void) { static V c; if (!c) c = MKS("apply("); return c; }
static V S1295(void) { static V c; if (!c) c = MKS(", "); return c; }
static V S1296(void) { static V c; if (!c) c = MKS(")"); return c; }
static V F_Gen_dapply(V a0, V a1) {
top:;
V s1293 = a0;
if ((s1293) == IMM(0)) {
return a1;
} else if (TAG(s1293) == 1) {
{ V t0 = FLD(s1293, 1); V t1 = F_Doc_dlist(C2(1, C1(1, S1294()), C2(1, a1, C2(1, C1(1, S1295()), C2(1, FLD(s1293, 0), C2(1, C1(1, S1296()), IMM(0))))))); a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dapply(V *a) { (void)a; return F_Gen_dapply(a[0], a[1]); }
static V F_Env_dhas(V a0, V a1) {
top:;
return F_Maybe_dis__some(F_Env_dfind(a0, a1));
}
static V W_Env_dhas(V *a) { (void)a; return F_Env_dhas(a[0], a[1]); }
static V F_Maybe_dis__some(V a2) {
top:;
V s1297 = a2;
if ((s1297) == IMM(0)) {
return IMM(0);
} else if (TAG(s1297) == 1) {
return IMM(1);
} else { bend_fail("incomplete match"); }
}
static V W_Maybe_dis__some(V *a) { (void)a; return F_Maybe_dis__some(a[2]); }
static V F_Gen_dcall_dvar(V a0, V a1, V a2, V a3, V a4) {
top:;
V s1298 = a4;
if ((s1298) == IMM(1)) {
return F_Gen_dcall_dlocal(a0, a1, C1(0, a2), a3);
} else if ((s1298) == IMM(0)) {
return F_Gen_dcall_ddef(a0, a1, a2, F_G_ddef(a0, a2), a3);
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dcall_dvar(V *a) { (void)a; return F_Gen_dcall_dvar(a[0], a[1], a[2], a[3], a[4]); }
static V F_Gen_dcall_ddef(V a0, V a1, V a2, V a3, V a4) {
top:;
V v1299 = a3;
return F_Gen_dcall_dkind(a0, a1, a2, F_U32_dto__nat(FLD(v1299, 0)), FLD(v1299, 1), F_Gen_dsplit(FLD(v1299, 1), a4, C4(0, IMM(0), IMM(0), IMM(0), IMM(0))));
}
static V W_Gen_dcall_ddef(V *a) { (void)a; return F_Gen_dcall_ddef(a[0], a[1], a[2], a[3], a[4]); }
static V S1306(void) { static V c; if (!c) c = MKS(""); return c; }
static V F_Gen_dsplit(V a0, V a1, V a2) {
top:;
V s1300 = a0;
V s1301 = a1;
if ((s1300) == IMM(0)) {
V v1302 = a2;
return C4(0, FLD(v1302, 0), FLD(v1302, 1), s1301, IMM(1));
} else if (TAG(s1300) == 1 && (s1301) == IMM(0)) {
V v1303 = a2;
return C4(0, FLD(v1303, 0), FLD(v1303, 1), IMM(0), IMM(0));
} else if (TAG(s1300) == 1 && (FLD(s1300, 0)) == IMM(1) && TAG(s1301) == 1) {
V v1304 = a2;
{ V t0 = FLD(s1300, 1); V t1 = FLD(s1301, 1); V t2 = C4(0, F_List_dappend(FLD(v1304, 0), C2(1, FLD(s1301, 0), IMM(0))), F_List_dappend(FLD(v1304, 1), C2(1, FLD(s1301, 0), IMM(0))), FLD(v1304, 2), FLD(v1304, 3)); a0 = t0; a1 = t1; a2 = t2; goto top; }
} else if (TAG(s1300) == 1 && (FLD(s1300, 0)) == IMM(0) && TAG(s1301) == 1) {
V v1305 = a2;
{ V t0 = FLD(s1300, 1); V t1 = FLD(s1301, 1); V t2 = C4(0, FLD(v1305, 0), F_List_dappend(FLD(v1305, 1), C2(1, C2(14, S1306(), IMM(0)), IMM(0))), FLD(v1305, 2), FLD(v1305, 3)); a0 = t0; a1 = t1; a2 = t2; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dsplit(V *a) { (void)a; return F_Gen_dsplit(a[0], a[1], a[2]); }
static V S1308(void) { static V c; if (!c) c = MKS("0"); return c; }
static V S1309(void) { static V c; if (!c) c = MKS("unknown function: "); return c; }
static V S1311(void) { static V c; if (!c) c = MKS("0"); return c; }
static V L1310(V *a) {
return F_Gen_dpure(C1(1, S1311()));
}
static V L1312(V *a) {
return F_Gen_dcall_dsplit(a[4], a[3], a[2], a[1], a[0]);
}
static V F_Gen_dcall_dkind(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V s1307 = a3;
if ((s1307) == 3) {
return F_Gen_dpure(C1(1, S1308()));
} else if ((s1307) == 99) {
return F_Gen_dbind(F_Gen_derror(F_String_dappend(S1309(), a2)), mk_clo(L1310, 1, 0, 0));
} else {
return F_Gen_dbind(F_Gen_dref(a2), mk_clo(L1312, 6, 5, (V[]){a5, a4, a2, a1, a0}));
}
}
static V W_Gen_dcall_dkind(V *a) { (void)a; return F_Gen_dcall_dkind(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V F_Gen_dcall_dsplit(V a0, V a1, V a2, V a3, V a4) {
top:;
V v1313 = a4;
return F_Gen_dcall_dfull(a0, a1, a2, a3, FLD(v1313, 0), FLD(v1313, 1), FLD(v1313, 2), FLD(v1313, 3));
}
static V W_Gen_dcall_dsplit(V *a) { (void)a; return F_Gen_dcall_dsplit(a[0], a[1], a[2], a[3], a[4]); }
static V S1317(void) { static V c; if (!c) c = MKS("("); return c; }
static V S1318(void) { static V c; if (!c) c = MKS(")"); return c; }
static V L1316(V *a) {
return F_Gen_dpure(F_Gen_dapply(a[2], F_Doc_dlist(C2(1, C1(1, F_String_dappend(F_Gen_df(a[1]), S1317())), C2(1, F_Gen_dcommas(a[0]), C2(1, C1(1, S1318()), IMM(0)))))));
}
static V L1315(V *a) {
return F_Gen_dbind(F_Gen_dexprs(a[3], a[2], a[1]), mk_clo(L1316, 3, 2, (V[]){a[4], a[0]}));
}
static V S1320(void) { static V c; if (!c) c = MKS("mk_clo("); return c; }
static V S1321(void) { static V c; if (!c) c = MKS(", "); return c; }
static V S1322(void) { static V c; if (!c) c = MKS(", "); return c; }
static V S1323(void) { static V c; if (!c) c = MKS(", "); return c; }
static V S1324(void) { static V c; if (!c) c = MKS(")"); return c; }
static V L1319(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, C1(1, F_String_dappend(S1320(), F_String_dappend(F_Gen_dw(a[1]), F_String_dappend(S1321(), F_String_dappend(F_U32_dshow(F_U32_dfrom__nat(F_List_dlength(a[0]))), F_String_dappend(S1322(), F_String_dappend(F_U32_dshow(F_Gen_dlen(a[2])), S1323()))))))), C2(1, F_Gen_darr(a[2]), C2(1, C1(1, S1324()), IMM(0))))));
}
static V F_Gen_dcall_dfull(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7) {
top:;
V s1314 = a7;
if ((s1314) == IMM(1)) {
return F_Gen_dbind(F_Gen_dexprs(a0, a1, a4), mk_clo(L1315, 5, 4, (V[]){a2, a6, a1, a0}));
} else if ((s1314) == IMM(0)) {
return F_Gen_dbind(F_Gen_dexprs(a0, a1, a5), mk_clo(L1319, 3, 2, (V[]){a3, a2}));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dcall_dfull(V *a) { (void)a; return F_Gen_dcall_dfull(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]); }
static V L1325(V *a) {
return F_Gen_dref_dgo(a[0], a[1]);
}
static V F_Gen_dref(V a0) {
top:;
return mk_clo(L1325, 2, 1, (V[]){a0});
}
static V W_Gen_dref(V *a) { (void)a; return F_Gen_dref(a[0]); }
static V F_Gen_dref_dgo(V a0, V a1) {
top:;
V v1326 = a1;
return C2(0, IMM(0), CN(0, 6, (V[]){FLD(v1326, 0), FLD(v1326, 1), FLD(v1326, 2), C2(1, a0, FLD(v1326, 3)), FLD(v1326, 4), FLD(v1326, 5)}));
}
static V W_Gen_dref_dgo(V *a) { (void)a; return F_Gen_dref_dgo(a[0], a[1]); }
static V S1328(void) { static V c; if (!c) c = MKS("S"); return c; }
static V S1330(void) { static V c; if (!c) c = MKS("static V "); return c; }
static V S1331(void) { static V c; if (!c) c = MKS("(void);\012"); return c; }
static V S1333(void) { static V c; if (!c) c = MKS("static V "); return c; }
static V S1334(void) { static V c; if (!c) c = MKS("(void) { static V c; if (!c) c = MKS(\042"); return c; }
static V S1335(void) { static V c; if (!c) c = MKS("\042); return c; }\012"); return c; }
static V S1337(void) { static V c; if (!c) c = MKS("()"); return c; }
static V L1336(V *a) {
return F_Gen_dpure(C1(1, F_String_dappend(a[0], S1337())));
}
static V L1332(V *a) {
return F_Gen_dbind(F_Gen_dcode(C1(1, F_String_dappend(S1333(), F_String_dappend(a[1], F_String_dappend(S1334(), F_String_dappend(F_Gen_dlit(a[0]), S1335())))))), mk_clo(L1336, 2, 1, (V[]){a[1]}));
}
static V L1329(V *a) {
return F_Gen_dbind(F_Gen_dproto(C1(1, F_String_dappend(S1330(), F_String_dappend(a[1], S1331())))), mk_clo(L1332, 3, 2, (V[]){a[0], a[1]}));
}
static V L1327(V *a) {
return F_Gen_dbind(F_Gen_dpure(F_String_dappend(S1328(), F_U32_dshow(a[1]))), mk_clo(L1329, 2, 1, (V[]){a[0]}));
}
static V F_Gen_dstr(V a0) {
top:;
return F_Gen_dbind(F_Gen_dfresh(), mk_clo(L1327, 2, 1, (V[]){a0}));
}
static V W_Gen_dstr(V *a) { (void)a; return F_Gen_dstr(a[0]); }
static V S1339(void) { static V c; if (!c) c = MKS(""); return c; }
static V F_Gen_dlit(V a0) {
top:;
V s1338 = a0;
if ((s1338) == IMM(0)) {
return S1339();
} else if (TAG(s1338) == 1) {
return F_String_dappend(F_Gen_dlit__chr(FLD(s1338, 0)), F_Gen_dlit(FLD(s1338, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dlit(V *a) { (void)a; return F_Gen_dlit(a[0]); }
static V S1340(void) { static V c; if (!c) c = MKS("\042"); return c; }
static V S1341(void) { static V c; if (!c) c = MKS("\134"); return c; }
static V S1342(void) { static V c; if (!c) c = MKS("\077"); return c; }
static V F_Gen_dlit__chr(V a0) {
top:;
return F_Bool_dpick(F_Bool_dand(F_Bool_dand(F_U32_dis__ge(a0, 32u), F_U32_dis__lt(a0, 127u)), F_Bool_dnot(F_Str_dhas(C2(1, S1340(), C2(1, S1341(), C2(1, S1342(), IMM(0)))), F_Str_dchr(a0)))), F_Str_dchr(a0), F_Gen_dutf8(a0));
}
static V W_Gen_dlit__chr(V *a) { (void)a; return F_Gen_dlit__chr(a[0]); }
static V F_Gen_dutf8(V a0) {
top:;
return F_Bool_dpick(F_U32_dis__lt(a0, 128u), F_Gen_doct(a0), F_Bool_dpick(F_U32_dis__lt(a0, 2048u), F_String_dappend(F_Gen_doct(F_U32_dor(192u, F_U32_dshrn(a0, 6u))), F_Gen_doct(F_U32_dor(128u, F_U32_dand(a0, 63u)))), F_Bool_dpick(F_U32_dis__lt(a0, 65536u), F_String_dappend(F_Gen_doct(F_U32_dor(224u, F_U32_dshrn(a0, 12u))), F_String_dappend(F_Gen_doct(F_U32_dor(128u, F_U32_dand(F_U32_dshrn(a0, 6u), 63u))), F_Gen_doct(F_U32_dor(128u, F_U32_dand(a0, 63u))))), F_String_dappend(F_Gen_doct(F_U32_dor(240u, F_U32_dshrn(a0, 18u))), F_String_dappend(F_Gen_doct(F_U32_dor(128u, F_U32_dand(F_U32_dshrn(a0, 12u), 63u))), F_String_dappend(F_Gen_doct(F_U32_dor(128u, F_U32_dand(F_U32_dshrn(a0, 6u), 63u))), F_Gen_doct(F_U32_dor(128u, F_U32_dand(a0, 63u)))))))));
}
static V W_Gen_dutf8(V *a) { (void)a; return F_Gen_dutf8(a[0]); }
static V W_U32_dor(V *a) { (void)a; return F_U32_dor(a[0], a[1]); }
static V S1343(void) { static V c; if (!c) c = MKS("\134"); return c; }
static V F_Gen_doct(V a0) {
top:;
return F_String_dappend(S1343(), F_String_dappend(F_Str_dchr(F_U32_dadd(48u, F_U32_dand(F_U32_dshrn(a0, 6u), 7u))), F_String_dappend(F_Str_dchr(F_U32_dadd(48u, F_U32_dand(F_U32_dshrn(a0, 3u), 7u))), F_Str_dchr(F_U32_dadd(48u, F_U32_dand(a0, 7u))))));
}
static V W_Gen_doct(V *a) { (void)a; return F_Gen_doct(a[0]); }
static V W_U32_dis__lt(V *a) { (void)a; return F_U32_dis__lt(a[0], a[1]); }
static V F_Gen_dvar(V a0, V a1, V a2) {
top:;
return F_Gen_dvar_dfound(a0, a2, F_Env_dfind(a1, a2));
}
static V W_Gen_dvar(V *a) { (void)a; return F_Gen_dvar(a[0], a[1], a[2]); }
static V S1345(void) { static V c; if (!c) c = MKS("_"); return c; }
static V F_Gen_dvar_dfound(V a0, V a1, V a2) {
top:;
V s1344 = a2;
if (TAG(s1344) == 1) {
return F_Gen_dpure(C1(1, FLD(s1344, 0)));
} else if ((s1344) == IMM(0)) {
return F_Gen_dvar_dglobal(a0, a1, F_Str_deq(a1, S1345()));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dvar_dfound(V *a) { (void)a; return F_Gen_dvar_dfound(a[0], a[1], a[2]); }
static V S1347(void) { static V c; if (!c) c = MKS("0"); return c; }
static V F_Gen_dvar_dglobal(V a0, V a1, V a2) {
top:;
V s1346 = a2;
if ((s1346) == IMM(1)) {
return F_Gen_dpure(C1(1, S1347()));
} else if ((s1346) == IMM(0)) {
return F_Gen_dvar_ddef(a1, F_G_ddef(a0, a1));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dvar_dglobal(V *a) { (void)a; return F_Gen_dvar_dglobal(a[0], a[1], a[2]); }
static V F_Gen_dvar_ddef(V a0, V a1) {
top:;
V v1348 = a1;
return F_Gen_dvar_dkind(a0, F_U32_dto__nat(FLD(v1348, 0)), F_U32_dfrom__nat(F_List_dlength(FLD(v1348, 1))));
}
static V W_Gen_dvar_ddef(V *a) { (void)a; return F_Gen_dvar_ddef(a[0], a[1]); }
static V S1350(void) { static V c; if (!c) c = MKS("0"); return c; }
static V S1351(void) { static V c; if (!c) c = MKS("unknown name: "); return c; }
static V S1353(void) { static V c; if (!c) c = MKS("0"); return c; }
static V L1352(V *a) {
return F_Gen_dpure(C1(1, S1353()));
}
static V S1355(void) { static V c; if (!c) c = MKS("()"); return c; }
static V S1356(void) { static V c; if (!c) c = MKS("mk_clo("); return c; }
static V S1357(void) { static V c; if (!c) c = MKS(", "); return c; }
static V S1358(void) { static V c; if (!c) c = MKS(", 0, 0)"); return c; }
static V L1354(V *a) {
return F_Gen_dpure(F_Bool_dpick(F_U32_dis__zero(a[1]), C1(1, F_String_dappend(F_Gen_df(a[0]), S1355())), C1(1, F_String_dappend(S1356(), F_String_dappend(F_Gen_dw(a[0]), F_String_dappend(S1357(), F_String_dappend(F_U32_dshow(a[1]), S1358())))))));
}
static V F_Gen_dvar_dkind(V a0, V a1, V a2) {
top:;
V s1349 = a1;
if ((s1349) == 3) {
return F_Gen_dpure(C1(1, S1350()));
} else if ((s1349) == 99) {
return F_Gen_dbind(F_Gen_derror(F_String_dappend(S1351(), a0)), mk_clo(L1352, 1, 0, 0));
} else {
return F_Gen_dbind(F_Gen_dref(a0), mk_clo(L1354, 3, 2, (V[]){a0, a2}));
}
}
static V W_Gen_dvar_dkind(V *a) { (void)a; return F_Gen_dvar_dkind(a[0], a[1], a[2]); }
static V F_Gen_dis__tail(V a0, V a1, V a2, V a3, V a4) {
top:;
V v1359 = a1;
return F_Bool_dand(F_Bool_dand(F_Gen_dis__ret(a2), F_Str_deq(FLD(v1359, 0), a3)), F_Bool_dand(F_Bool_dnot(F_Env_dhas(a0, a3)), F_Nat_dis__eq(F_List_dlength(FLD(v1359, 1)), F_List_dlength(a4))));
}
static V W_Gen_dis__tail(V *a) { (void)a; return F_Gen_dis__tail(a[0], a[1], a[2], a[3], a[4]); }
static V W_Nat_dis__eq(V *a) { (void)a; return F_Nat_dis__eq(a[0], a[1]); }
static V F_Gen_dis__ret(V a0) {
top:;
V s1360 = a0;
if ((s1360) == IMM(0)) {
return IMM(1);
} else if (TAG(s1360) == 1) {
return IMM(0);
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dis__ret(V *a) { (void)a; return F_Gen_dis__ret(a[0]); }
static V L1362(V *a) {
return F_Gen_dpure(F_Gen_dret(a[0], a[1]));
}
static V F_Gen_dstmt_dcall(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V s1361 = a6;
if ((s1361) == IMM(1)) {
return F_Gen_dtail_dself(a0, a1, a2, a5);
} else if ((s1361) == IMM(0)) {
return F_Gen_dbind(F_Gen_dcall(a0, a1, C1(0, a4), a5), mk_clo(L1362, 2, 1, (V[]){a3}));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dstmt_dcall(V *a) { (void)a; return F_Gen_dstmt_dcall(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V F_Gen_dtail_dself(V a0, V a1, V a2, V a3) {
top:;
V v1363 = a2;
return F_Gen_dtail(a0, a1, FLD(v1363, 2), F_Gen_dsplit(FLD(v1363, 1), a3, C4(0, IMM(0), IMM(0), IMM(0), IMM(0))));
}
static V W_Gen_dtail_dself(V *a) { (void)a; return F_Gen_dtail_dself(a[0], a[1], a[2], a[3]); }
static V S1366(void) { static V c; if (!c) c = MKS("{ "); return c; }
static V S1367(void) { static V c; if (!c) c = MKS("goto top; }\012"); return c; }
static V L1365(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, C1(1, S1366()), C2(1, F_Gen_dtail_dtemps(a[1], 0u), C2(1, F_Gen_dtail_dassign(a[0], 0u), C2(1, C1(1, S1367()), IMM(0)))))));
}
static V F_Gen_dtail(V a0, V a1, V a2, V a3) {
top:;
V v1364 = a3;
return F_Gen_dbind(F_Gen_dexprs(a0, a1, FLD(v1364, 0)), mk_clo(L1365, 2, 1, (V[]){a2}));
}
static V W_Gen_dtail(V *a) { (void)a; return F_Gen_dtail(a[0], a[1], a[2], a[3]); }
static V S1369(void) { static V c; if (!c) c = MKS(" = t"); return c; }
static V S1370(void) { static V c; if (!c) c = MKS("; "); return c; }
static V F_Gen_dtail_dassign(V a0, V a1) {
top:;
V s1368 = a0;
if ((s1368) == IMM(0)) {
return IMM(0);
} else if (TAG(s1368) == 1) {
return F_Doc_dlist(C2(1, C1(1, F_String_dappend(FLD(s1368, 0), F_String_dappend(S1369(), F_String_dappend(F_U32_dshow(a1), S1370())))), C2(1, F_Gen_dtail_dassign(FLD(s1368, 1), F_U32_dinc(a1)), IMM(0))));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dtail_dassign(V *a) { (void)a; return F_Gen_dtail_dassign(a[0], a[1]); }
static V S1372(void) { static V c; if (!c) c = MKS("V t"); return c; }
static V S1373(void) { static V c; if (!c) c = MKS(" = "); return c; }
static V S1374(void) { static V c; if (!c) c = MKS("; "); return c; }
static V F_Gen_dtail_dtemps(V a0, V a1) {
top:;
V s1371 = a0;
if ((s1371) == IMM(0)) {
return IMM(0);
} else if (TAG(s1371) == 1) {
return F_Doc_dlist(C2(1, C1(1, F_String_dappend(S1372(), F_String_dappend(F_U32_dshow(a1), S1373()))), C2(1, FLD(s1371, 0), C2(1, C1(1, S1374()), C2(1, F_Gen_dtail_dtemps(FLD(s1371, 1), F_U32_dinc(a1)), IMM(0))))));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dtail_dtemps(V *a) { (void)a; return F_Gen_dtail_dtemps(a[0], a[1]); }
static V L1375(V *a) {
return F_Gen_dmatch_dgo(a[4], a[3], a[2], a[1], a[0], a[5]);
}
static V F_Gen_dmatch(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
return F_Gen_dbind(F_Gen_dscrs(a0, a1, a4), mk_clo(L1375, 6, 5, (V[]){a5, a3, a2, a1, a0}));
}
static V W_Gen_dmatch(V *a) { (void)a; return F_Gen_dmatch(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V L1377(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, a[0], C2(1, a[1], IMM(0)))));
}
static V F_Gen_dmatch_dgo(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V v1376 = a5;
return F_Gen_dbind(F_Gen_dcases(a0, a1, a2, a3, FLD(v1376, 0), a4), mk_clo(L1377, 2, 1, (V[]){FLD(v1376, 1)}));
}
static V W_Gen_dmatch_dgo(V *a) { (void)a; return F_Gen_dmatch_dgo(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V S1379(void) { static V c; if (!c) c = MKS("{ bend_fail(\042incomplete match\042); }\012"); return c; }
static V L1383(V *a) {
return F_Gen_dcases_dnext(a[6], a[5], a[4], a[3], a[2], a[1], F_List_dreverse(a[0]), a[7]);
}
static V F_Gen_dcases(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V s1378 = a5;
if ((s1378) == IMM(0)) {
return F_Gen_dpure(C1(1, S1379()));
} else if (TAG(s1378) == 1 && TAG(FLD(s1378, 0)) == 10) {
V v1380 = F_Gen_dpats(a0, FLD(FLD(s1378, 0), 0), a4, C2(0, IMM(0), IMM(0)));
V v1381 = F_PatR_dconds(v1380);
V v1382 = F_PatR_dbinds(v1380);
return F_Gen_dbind(F_Gen_dstmt(a0, F_List_dappend(v1382, a1), a2, a3, FLD(FLD(s1378, 0), 1)), mk_clo(L1383, 8, 7, (V[]){v1381, FLD(s1378, 1), a4, a3, a2, a1, a0}));
} else if (TAG(s1378) == 1) {
{ V t0 = a0; V t1 = a1; V t2 = a2; V t3 = a3; V t4 = a4; V t5 = FLD(s1378, 1); a0 = t0; a1 = t1; a2 = t2; a3 = t3; a4 = t4; a5 = t5; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dcases(V *a) { (void)a; return F_Gen_dcases(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V S1385(void) { static V c; if (!c) c = MKS("{\012"); return c; }
static V S1386(void) { static V c; if (!c) c = MKS("}\012"); return c; }
static V S1388(void) { static V c; if (!c) c = MKS("if ("); return c; }
static V S1389(void) { static V c; if (!c) c = MKS(") {\012"); return c; }
static V S1390(void) { static V c; if (!c) c = MKS("} else "); return c; }
static V L1387(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, C1(1, F_String_dappend(S1388(), F_String_dappend(F_Gen_dand(C2(1, a[2], a[1])), S1389()))), C2(1, a[0], C2(1, C1(1, S1390()), C2(1, a[3], IMM(0)))))));
}
static V F_Gen_dcases_dnext(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7) {
top:;
V s1384 = a6;
if ((s1384) == IMM(0)) {
return F_Gen_dpure(F_Doc_dlist(C2(1, C1(1, S1385()), C2(1, a7, C2(1, C1(1, S1386()), IMM(0))))));
} else if (TAG(s1384) == 1) {
return F_Gen_dbind(F_Gen_dcases(a0, a1, a2, a3, a4, a5), mk_clo(L1387, 4, 3, (V[]){a7, FLD(s1384, 1), FLD(s1384, 0)}));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dcases_dnext(V *a) { (void)a; return F_Gen_dcases_dnext(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]); }
static V S1392(void) { static V c; if (!c) c = MKS("1"); return c; }
static V S1393(void) { static V c; if (!c) c = MKS(" && "); return c; }
static V F_Gen_dand(V a0) {
top:;
V s1391 = a0;
if ((s1391) == IMM(0)) {
return S1392();
} else if (TAG(s1391) == 1 && (FLD(s1391, 1)) == IMM(0)) {
return FLD(s1391, 0);
} else if (TAG(s1391) == 1) {
return F_String_dappend(FLD(s1391, 0), F_String_dappend(S1393(), F_Gen_dand(FLD(s1391, 1))));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dand(V *a) { (void)a; return F_Gen_dand(a[0]); }
static V F_PatR_dconds(V a0) {
top:;
V v1394 = a0;
return FLD(v1394, 0);
}
static V W_PatR_dconds(V *a) { (void)a; return F_PatR_dconds(a[0]); }
static V F_Gen_dpats(V a0, V a1, V a2, V a3) {
top:;
V s1395 = a1;
V s1396 = a2;
if (TAG(s1395) == 1 && TAG(s1396) == 1) {
{ V t0 = a0; V t1 = FLD(s1395, 1); V t2 = FLD(s1396, 1); V t3 = F_Gen_dpat(a0, FLD(s1395, 0), FLD(s1396, 0), a3); a0 = t0; a1 = t1; a2 = t2; a3 = t3; goto top; }
} else {
return a3;
}
}
static V W_Gen_dpats(V *a) { (void)a; return F_Gen_dpats(a[0], a[1], a[2], a[3]); }
static V S1399(void) { static V c; if (!c) c = MKS("s"); return c; }
static V L1402(V *a) {
return F_Gen_dpure(F_Gen_dscrs_dput(a[1], a[0], a[2]));
}
static V L1401(V *a) {
return F_Gen_dbind(F_Gen_dscrs(a[3], a[2], a[1]), mk_clo(L1402, 3, 2, (V[]){a[4], a[0]}));
}
static V L1400(V *a) {
return F_Gen_dbind(F_Gen_dexpr(a[3], a[2], a[1]), mk_clo(L1401, 5, 4, (V[]){a[4], a[0], a[2], a[3]}));
}
static V L1398(V *a) {
return F_Gen_dbind(F_Gen_dpure(F_String_dappend(S1399(), F_U32_dshow(a[4]))), mk_clo(L1400, 5, 4, (V[]){a[0], a[1], a[2], a[3]}));
}
static V F_Gen_dscrs(V a0, V a1, V a2) {
top:;
V s1397 = a2;
if ((s1397) == IMM(0)) {
return F_Gen_dpure(C2(0, IMM(0), IMM(0)));
} else if (TAG(s1397) == 1) {
return F_Gen_dbind(F_Gen_dfresh(), mk_clo(L1398, 5, 4, (V[]){FLD(s1397, 1), FLD(s1397, 0), a1, a0}));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dscrs(V *a) { (void)a; return F_Gen_dscrs(a[0], a[1], a[2]); }
static V S1404(void) { static V c; if (!c) c = MKS("V "); return c; }
static V S1405(void) { static V c; if (!c) c = MKS(" = "); return c; }
static V S1406(void) { static V c; if (!c) c = MKS(";\012"); return c; }
static V F_Gen_dscrs_dput(V a0, V a1, V a2) {
top:;
V v1403 = a2;
return C2(0, C2(1, a0, FLD(v1403, 0)), F_Doc_dlist(C2(1, C1(1, F_String_dappend(S1404(), F_String_dappend(a0, S1405()))), C2(1, a1, C2(1, C1(1, S1406()), C2(1, FLD(v1403, 1), IMM(0)))))));
}
static V W_Gen_dscrs_dput(V *a) { (void)a; return F_Gen_dscrs_dput(a[0], a[1], a[2]); }
static V S1408(void) { static V c; if (!c) c = MKS("_"); return c; }
static V S1410(void) { static V c; if (!c) c = MKS("v"); return c; }
static V S1415(void) { static V c; if (!c) c = MKS("V "); return c; }
static V S1416(void) { static V c; if (!c) c = MKS(" = "); return c; }
static V S1417(void) { static V c; if (!c) c = MKS(";\012"); return c; }
static V L1414(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, C1(1, F_String_dappend(S1415(), F_String_dappend(a[1], S1416()))), C2(1, a[0], C2(1, C1(1, S1417()), C2(1, a[2], IMM(0)))))));
}
static V L1413(V *a) {
return F_Gen_dbind(F_Gen_dstmt(a[6], F_List_dappend(a[7], a[5]), a[4], a[3], a[2]), mk_clo(L1414, 3, 2, (V[]){a[0], a[1]}));
}
static V L1412(V *a) {
return F_Gen_dbind(F_Gen_dpure(F_PatR_dbinds(F_Gen_dpat(a[6], a[5], a[4], C2(0, IMM(0), IMM(0))))), mk_clo(L1413, 8, 7, (V[]){a[7], a[4], a[0], a[1], a[2], a[3], a[6]}));
}
static V L1411(V *a) {
return F_Gen_dbind(F_Gen_dexpr(a[6], a[5], a[4]), mk_clo(L1412, 8, 7, (V[]){a[0], a[1], a[2], a[5], a[7], a[3], a[6]}));
}
static V L1409(V *a) {
return F_Gen_dbind(F_Gen_dpure(F_String_dappend(S1410(), F_U32_dshow(a[7]))), mk_clo(L1411, 8, 7, (V[]){a[0], a[1], a[2], a[3], a[4], a[5], a[6]}));
}
static V F_Gen_dlet(V a0, V a1, V a2, V a3, V a4, V a5, V a6) {
top:;
V s1407 = a4;
if (TAG(s1407) == 0) {
return F_Gen_dlet_dvar(a0, a1, a2, a3, FLD(s1407, 0), a5, a6, F_Str_deq(FLD(s1407, 0), S1408()));
} else {
return F_Gen_dbind(F_Gen_dfresh(), mk_clo(L1409, 8, 7, (V[]){a6, a3, a2, s1407, a5, a1, a0}));
}
}
static V W_Gen_dlet(V *a) { (void)a; return F_Gen_dlet(a[0], a[1], a[2], a[3], a[4], a[5], a[6]); }
static V S1421(void) { static V c; if (!c) c = MKS("(void)("); return c; }
static V S1422(void) { static V c; if (!c) c = MKS(");\012"); return c; }
static V L1420(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, C1(1, S1421()), C2(1, a[0], C2(1, C1(1, S1422()), C2(1, a[1], IMM(0)))))));
}
static V L1419(V *a) {
return F_Gen_dbind(F_Gen_dstmt(a[4], a[3], a[2], a[1], a[0]), mk_clo(L1420, 2, 1, (V[]){a[5]}));
}
static V S1424(void) { static V c; if (!c) c = MKS("v"); return c; }
static V S1428(void) { static V c; if (!c) c = MKS("V "); return c; }
static V S1429(void) { static V c; if (!c) c = MKS(" = "); return c; }
static V S1430(void) { static V c; if (!c) c = MKS(";\012"); return c; }
static V L1427(V *a) {
return F_Gen_dpure(F_Doc_dlist(C2(1, C1(1, F_String_dappend(S1428(), F_String_dappend(a[1], S1429()))), C2(1, a[0], C2(1, C1(1, S1430()), C2(1, a[2], IMM(0)))))));
}
static V L1426(V *a) {
return F_Gen_dbind(F_Gen_dstmt(a[6], C2(1, C2(0, a[5], a[4]), a[3]), a[2], a[1], a[0]), mk_clo(L1427, 3, 2, (V[]){a[7], a[4]}));
}
static V L1425(V *a) {
return F_Gen_dbind(F_Gen_dexpr(a[6], a[5], a[4]), mk_clo(L1426, 8, 7, (V[]){a[0], a[1], a[2], a[5], a[7], a[3], a[6]}));
}
static V L1423(V *a) {
return F_Gen_dbind(F_Gen_dpure(F_String_dappend(S1424(), F_U32_dshow(a[7]))), mk_clo(L1425, 8, 7, (V[]){a[0], a[1], a[2], a[3], a[4], a[5], a[6]}));
}
static V F_Gen_dlet_dvar(V a0, V a1, V a2, V a3, V a4, V a5, V a6, V a7) {
top:;
V s1418 = a7;
if ((s1418) == IMM(1)) {
return F_Gen_dbind(F_Gen_dexpr(a0, a1, a5), mk_clo(L1419, 6, 5, (V[]){a6, a3, a2, a1, a0}));
} else if ((s1418) == IMM(0)) {
return F_Gen_dbind(F_Gen_dfresh(), mk_clo(L1423, 8, 7, (V[]){a6, a3, a2, a4, a5, a1, a0}));
} else { bend_fail("incomplete match"); }
}
static V W_Gen_dlet_dvar(V *a) { (void)a; return F_Gen_dlet_dvar(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]); }
static V S1433(void) { static V c; if (!c) c = MKS("#include \042bendrt.h\042\012\012"); return c; }
static V S1434(void) { static V c; if (!c) c = MKS("\012"); return c; }
static V S1435(void) { static V c; if (!c) c = MKS("\012"); return c; }
static V F_Gen_dprogram_dfin(V a0) {
top:;
V v1431 = a0;
V v1432 = FLD(v1431, 1);
return C2(0, F_Doc_dflat(F_Doc_dlist(C2(1, C1(1, S1433()), C2(1, FLD(v1432, 1), C2(1, C1(1, S1434()), C2(1, FLD(v1432, 2), C2(1, C1(1, F_String_dappend(S1435(), FLD(v1431, 0))), IMM(0)))))))), FLD(v1432, 4));
}
static V W_Gen_dprogram_dfin(V *a) { (void)a; return F_Gen_dprogram_dfin(a[0]); }
static V F_Doc_dflat(V a0) {
top:;
return F_Doc_dgo(a0, IMM(0));
}
static V W_Doc_dflat(V *a) { (void)a; return F_Doc_dflat(a[0]); }
static V F_Doc_dgo(V a0, V a1) {
top:;
V s1436 = a0;
if ((s1436) == IMM(0)) {
return a1;
} else if (TAG(s1436) == 1) {
return F_String_dappend(FLD(s1436, 0), a1);
} else if (TAG(s1436) == 2) {
{ V t0 = FLD(s1436, 0); V t1 = F_Doc_dgo(FLD(s1436, 1), a1); a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Doc_dgo(V *a) { (void)a; return F_Doc_dgo(a[0], a[1]); }
static V F_G_dnew(V a0) {
top:;
return F_G_dbuild(a0, F_G_dlaws(a0, IMM(0)), C3(0, IMM(0), IMM(0), IMM(0)));
}
static V W_G_dnew(V *a) { (void)a; return F_G_dnew(a[0]); }
static V F_G_dlaws(V a0, V a1) {
top:;
V s1437 = a0;
if ((s1437) == IMM(0)) {
return a1;
} else if (TAG(s1437) == 1 && TAG(FLD(s1437, 0)) == 2) {
{ V t0 = FLD(s1437, 1); V t1 = F_Map_dset(a1, FLD(FLD(s1437, 0), 0), FLD(FLD(s1437, 0), 1)); a0 = t0; a1 = t1; goto top; }
} else if (TAG(s1437) == 1) {
{ V t0 = FLD(s1437, 1); V t1 = a1; a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_G_dlaws(V *a) { (void)a; return F_G_dlaws(a[0], a[1]); }
static V F_G_dbuild(V a0, V a1, V a2) {
top:;
V s1438 = a0;
if ((s1438) == IMM(0)) {
return a2;
} else if (TAG(s1438) == 1) {
{ V t0 = FLD(s1438, 1); V t1 = a1; V t2 = F_G_dadd(FLD(s1438, 0), a1, a2); a0 = t0; a1 = t1; a2 = t2; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_G_dbuild(V *a) { (void)a; return F_G_dbuild(a[0], a[1], a[2]); }
static V F_G_dadd(V a0, V a1, V a2) {
top:;
V s1439 = a0;
if (TAG(s1439) == 3) {
return F_G_dadd_dtype(FLD(s1439, 0), FLD(s1439, 1), FLD(s1439, 2), a2);
} else if (TAG(s1439) == 2) {
return F_G_dadd_dlaw(FLD(s1439, 0), FLD(s1439, 1), a2);
} else if (TAG(s1439) == 0) {
return F_G_dadd_ddef(FLD(s1439, 0), FLD(s1439, 1), FLD(s1439, 2), FLD(s1439, 3), a1, a2);
} else if (TAG(s1439) == 1) {
return F_G_dadd_deff(FLD(s1439, 0), FLD(s1439, 1), a2);
} else if (TAG(s1439) == 4) {
return a2;
} else { bend_fail("incomplete match"); }
}
static V W_G_dadd(V *a) { (void)a; return F_G_dadd(a[0], a[1], a[2]); }
static V F_G_dadd_deff(V a0, V a1, V a2) {
top:;
V v1440 = a2;
return C3(0, FLD(v1440, 0), F_Map_dset(FLD(v1440, 1), a0, C2(0, 1u, F_G_dmask(a1))), F_Map_dset(FLD(v1440, 2), a0, C2(1, a0, a1)));
}
static V W_G_dadd_deff(V *a) { (void)a; return F_G_dadd_deff(a[0], a[1], a[2]); }
static V F_G_dmask(V a0) {
top:;
V s1441 = a0;
if ((s1441) == IMM(0)) {
return IMM(0);
} else if (TAG(s1441) == 1) {
return C2(1, F_G_dkeep(FLD(s1441, 0)), F_G_dmask(FLD(s1441, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_G_dmask(V *a) { (void)a; return F_G_dmask(a[0]); }
static V F_G_dkeep(V a0) {
top:;
V v1442 = a0;
return F_Bool_dnot(F_Bool_dor(F_Bool_dor(F_U32_dis__eq(FLD(v1442, 1), 1u), F_U32_dis__eq(FLD(v1442, 1), 4u)), F_G_derased__ty(FLD(v1442, 2))));
}
static V W_G_dkeep(V *a) { (void)a; return F_G_dkeep(a[0]); }
static V S1443(void) { static V c; if (!c) c = MKS("Type"); return c; }
static V S1444(void) { static V c; if (!c) c = MKS("Data"); return c; }
static V S1445(void) { static V c; if (!c) c = MKS("Quant"); return c; }
static V S1446(void) { static V c; if (!c) c = MKS("Kind"); return c; }
static V F_G_derased__ty(V a0) {
top:;
return F_Str_dhas(C2(1, S1443(), C2(1, S1444(), C2(1, S1445(), C2(1, S1446(), IMM(0))))), a0);
}
static V W_G_derased__ty(V *a) { (void)a; return F_G_derased__ty(a[0]); }
static V F_G_dadd_ddef(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V v1447 = a5;
return C3(0, FLD(v1447, 0), F_Map_dset(FLD(v1447, 1), a0, C2(0, F_Bool_dpick(F_G_dis__native(a0), 2u, 0u), F_G_dmask(F_G_dparams(a4, a0, a1)))), F_Map_dset(FLD(v1447, 2), a0, C4(0, a0, a1, a2, a3)));
}
static V W_G_dadd_ddef(V *a) { (void)a; return F_G_dadd_ddef(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V F_G_dparams(V a0, V a1, V a2) {
top:;
return F_G_dparams_dgo(F_G_dget(IMM(0), a0, a1), a2);
}
static V W_G_dparams(V *a) { (void)a; return F_G_dparams(a[0], a[1], a[2]); }
static V F_G_dparams_dgo(V a0, V a1) {
top:;
V s1448 = a0;
if ((s1448) == IMM(0)) {
return a1;
} else if (TAG(s1448) == 1) {
return C2(1, FLD(s1448, 0), FLD(s1448, 1));
} else { bend_fail("incomplete match"); }
}
static V W_G_dparams_dgo(V *a) { (void)a; return F_G_dparams_dgo(a[0], a[1]); }
static V F_G_dis__native(V a0) {
top:;
return F_Str_dhas(F_Natives(), a0);
}
static V W_G_dis__native(V *a) { (void)a; return F_G_dis__native(a[0]); }
static V S1449(void) { static V c; if (!c) c = MKS("U32.inc"); return c; }
static V S1450(void) { static V c; if (!c) c = MKS("U32.add"); return c; }
static V S1451(void) { static V c; if (!c) c = MKS("U32.sub"); return c; }
static V S1452(void) { static V c; if (!c) c = MKS("U32.mul"); return c; }
static V S1453(void) { static V c; if (!c) c = MKS("U32.div"); return c; }
static V S1454(void) { static V c; if (!c) c = MKS("U32.mod"); return c; }
static V S1455(void) { static V c; if (!c) c = MKS("U32.not"); return c; }
static V S1456(void) { static V c; if (!c) c = MKS("U32.and"); return c; }
static V S1457(void) { static V c; if (!c) c = MKS("U32.or"); return c; }
static V S1458(void) { static V c; if (!c) c = MKS("U32.xor"); return c; }
static V S1459(void) { static V c; if (!c) c = MKS("U32.shl"); return c; }
static V S1460(void) { static V c; if (!c) c = MKS("U32.shr"); return c; }
static V S1461(void) { static V c; if (!c) c = MKS("U32.shln"); return c; }
static V S1462(void) { static V c; if (!c) c = MKS("U32.shrn"); return c; }
static V S1463(void) { static V c; if (!c) c = MKS("U32.cmp"); return c; }
static V S1464(void) { static V c; if (!c) c = MKS("U32.is_eq"); return c; }
static V S1465(void) { static V c; if (!c) c = MKS("U32.is_ne"); return c; }
static V S1466(void) { static V c; if (!c) c = MKS("U32.is_lt"); return c; }
static V S1467(void) { static V c; if (!c) c = MKS("U32.is_le"); return c; }
static V S1468(void) { static V c; if (!c) c = MKS("U32.is_gt"); return c; }
static V S1469(void) { static V c; if (!c) c = MKS("U32.is_ge"); return c; }
static V S1470(void) { static V c; if (!c) c = MKS("U32.is_zero"); return c; }
static V S1471(void) { static V c; if (!c) c = MKS("U32.is_even"); return c; }
static V S1472(void) { static V c; if (!c) c = MKS("U32.to_nat"); return c; }
static V S1473(void) { static V c; if (!c) c = MKS("U32.from_nat"); return c; }
static V S1474(void) { static V c; if (!c) c = MKS("U32.min"); return c; }
static V S1475(void) { static V c; if (!c) c = MKS("U32.max"); return c; }
static V S1476(void) { static V c; if (!c) c = MKS("U32.pow"); return c; }
static V S1477(void) { static V c; if (!c) c = MKS("U32.log2"); return c; }
static V S1478(void) { static V c; if (!c) c = MKS("U32.to_f32"); return c; }
static V S1479(void) { static V c; if (!c) c = MKS("Nat.double"); return c; }
static V S1480(void) { static V c; if (!c) c = MKS("Nat.add"); return c; }
static V S1481(void) { static V c; if (!c) c = MKS("Nat.sub"); return c; }
static V S1482(void) { static V c; if (!c) c = MKS("Nat.mul"); return c; }
static V S1483(void) { static V c; if (!c) c = MKS("Nat.divmod"); return c; }
static V S1484(void) { static V c; if (!c) c = MKS("Nat.div"); return c; }
static V S1485(void) { static V c; if (!c) c = MKS("Nat.mod"); return c; }
static V S1486(void) { static V c; if (!c) c = MKS("Nat.cmp"); return c; }
static V S1487(void) { static V c; if (!c) c = MKS("Nat.is_eq"); return c; }
static V S1488(void) { static V c; if (!c) c = MKS("Nat.is_ne"); return c; }
static V S1489(void) { static V c; if (!c) c = MKS("Nat.is_lt"); return c; }
static V S1490(void) { static V c; if (!c) c = MKS("Nat.is_le"); return c; }
static V S1491(void) { static V c; if (!c) c = MKS("Nat.is_gt"); return c; }
static V S1492(void) { static V c; if (!c) c = MKS("Nat.is_ge"); return c; }
static V S1493(void) { static V c; if (!c) c = MKS("Nat.min"); return c; }
static V S1494(void) { static V c; if (!c) c = MKS("Nat.max"); return c; }
static V S1495(void) { static V c; if (!c) c = MKS("Nat.pow"); return c; }
static V S1496(void) { static V c; if (!c) c = MKS("F32.add"); return c; }
static V S1497(void) { static V c; if (!c) c = MKS("F32.sub"); return c; }
static V S1498(void) { static V c; if (!c) c = MKS("F32.mul"); return c; }
static V S1499(void) { static V c; if (!c) c = MKS("F32.div"); return c; }
static V S1500(void) { static V c; if (!c) c = MKS("F32.mod"); return c; }
static V S1501(void) { static V c; if (!c) c = MKS("F32.pow"); return c; }
static V S1502(void) { static V c; if (!c) c = MKS("F32.atan2"); return c; }
static V S1503(void) { static V c; if (!c) c = MKS("F32.is_eq"); return c; }
static V S1504(void) { static V c; if (!c) c = MKS("F32.is_ne"); return c; }
static V S1505(void) { static V c; if (!c) c = MKS("F32.is_lt"); return c; }
static V S1506(void) { static V c; if (!c) c = MKS("F32.is_le"); return c; }
static V S1507(void) { static V c; if (!c) c = MKS("F32.is_gt"); return c; }
static V S1508(void) { static V c; if (!c) c = MKS("F32.is_ge"); return c; }
static V S1509(void) { static V c; if (!c) c = MKS("F32.neg"); return c; }
static V S1510(void) { static V c; if (!c) c = MKS("F32.abs"); return c; }
static V S1511(void) { static V c; if (!c) c = MKS("F32.sqrt"); return c; }
static V S1512(void) { static V c; if (!c) c = MKS("F32.exp"); return c; }
static V S1513(void) { static V c; if (!c) c = MKS("F32.log"); return c; }
static V S1514(void) { static V c; if (!c) c = MKS("F32.log2"); return c; }
static V S1515(void) { static V c; if (!c) c = MKS("F32.log10"); return c; }
static V S1516(void) { static V c; if (!c) c = MKS("F32.sin"); return c; }
static V S1517(void) { static V c; if (!c) c = MKS("F32.cos"); return c; }
static V S1518(void) { static V c; if (!c) c = MKS("F32.tan"); return c; }
static V S1519(void) { static V c; if (!c) c = MKS("F32.asin"); return c; }
static V S1520(void) { static V c; if (!c) c = MKS("F32.acos"); return c; }
static V S1521(void) { static V c; if (!c) c = MKS("F32.atan"); return c; }
static V S1522(void) { static V c; if (!c) c = MKS("F32.sinh"); return c; }
static V S1523(void) { static V c; if (!c) c = MKS("F32.cosh"); return c; }
static V S1524(void) { static V c; if (!c) c = MKS("F32.tanh"); return c; }
static V S1525(void) { static V c; if (!c) c = MKS("F32.floor"); return c; }
static V S1526(void) { static V c; if (!c) c = MKS("F32.ceil"); return c; }
static V S1527(void) { static V c; if (!c) c = MKS("F32.trunc"); return c; }
static V S1528(void) { static V c; if (!c) c = MKS("F32.bits"); return c; }
static V S1529(void) { static V c; if (!c) c = MKS("F32.to_u32"); return c; }
static V S1530(void) { static V c; if (!c) c = MKS("F32.show"); return c; }
static V S1531(void) { static V c; if (!c) c = MKS("F32.read"); return c; }
static V F_Natives(void) {
top:;
return C2(1, S1449(), C2(1, S1450(), C2(1, S1451(), C2(1, S1452(), C2(1, S1453(), C2(1, S1454(), C2(1, S1455(), C2(1, S1456(), C2(1, S1457(), C2(1, S1458(), C2(1, S1459(), C2(1, S1460(), C2(1, S1461(), C2(1, S1462(), C2(1, S1463(), C2(1, S1464(), C2(1, S1465(), C2(1, S1466(), C2(1, S1467(), C2(1, S1468(), C2(1, S1469(), C2(1, S1470(), C2(1, S1471(), C2(1, S1472(), C2(1, S1473(), C2(1, S1474(), C2(1, S1475(), C2(1, S1476(), C2(1, S1477(), C2(1, S1478(), C2(1, S1479(), C2(1, S1480(), C2(1, S1481(), C2(1, S1482(), C2(1, S1483(), C2(1, S1484(), C2(1, S1485(), C2(1, S1486(), C2(1, S1487(), C2(1, S1488(), C2(1, S1489(), C2(1, S1490(), C2(1, S1491(), C2(1, S1492(), C2(1, S1493(), C2(1, S1494(), C2(1, S1495(), C2(1, S1496(), C2(1, S1497(), C2(1, S1498(), C2(1, S1499(), C2(1, S1500(), C2(1, S1501(), C2(1, S1502(), C2(1, S1503(), C2(1, S1504(), C2(1, S1505(), C2(1, S1506(), C2(1, S1507(), C2(1, S1508(), C2(1, S1509(), C2(1, S1510(), C2(1, S1511(), C2(1, S1512(), C2(1, S1513(), C2(1, S1514(), C2(1, S1515(), C2(1, S1516(), C2(1, S1517(), C2(1, S1518(), C2(1, S1519(), C2(1, S1520(), C2(1, S1521(), C2(1, S1522(), C2(1, S1523(), C2(1, S1524(), C2(1, S1525(), C2(1, S1526(), C2(1, S1527(), C2(1, S1528(), C2(1, S1529(), C2(1, S1530(), C2(1, S1531(), IMM(0))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))));
}
static V W_Natives(V *a) { (void)a; return F_Natives(); }
static V F_G_dadd_dlaw(V a0, V a1, V a2) {
top:;
V v1532 = a2;
return C3(0, FLD(v1532, 0), F_Map_dset(FLD(v1532, 1), a0, C2(0, F_Bool_dpick(F_G_dis__native(a0), 2u, 3u), F_G_dmask(a1))), FLD(v1532, 2));
}
static V W_G_dadd_dlaw(V *a) { (void)a; return F_G_dadd_dlaw(a[0], a[1], a[2]); }
static V S1535(void) { static V c; if (!c) c = MKS("%"); return c; }
static V F_G_dadd_dtype(V a0, V a1, V a2, V a3) {
top:;
V v1533 = a3;
V v1534 = F_U32_dfrom__nat(F_List_dlength(a2));
return C3(0, F_G_dctors(a0, a2, 0u, v1534, FLD(v1533, 0)), F_Map_dset(FLD(v1533, 1), a0, C2(0, 3u, IMM(0))), F_Map_dset(FLD(v1533, 2), F_String_dappend(S1535(), a0), C3(3, a0, a1, a2)));
}
static V W_G_dadd_dtype(V *a) { (void)a; return F_G_dadd_dtype(a[0], a[1], a[2], a[3]); }
static V F_G_dctors(V a0, V a1, V a2, V a3, V a4) {
top:;
V s1536 = a1;
if ((s1536) == IMM(0)) {
return a4;
} else if (TAG(s1536) == 1) {
V v1537 = F_U32_dfrom__nat(F_List_dlength(FLD(FLD(s1536, 0), 1)));
{ V t0 = a0; V t1 = FLD(s1536, 1); V t2 = F_U32_dinc(a2); V t3 = a3; V t4 = F_Map_dset(a4, FLD(FLD(s1536, 0), 0), C4(0, a2, v1537, F_G_dctor__kind(a0, FLD(FLD(s1536, 0), 0), a3, v1537), F_U32_dis__eq(a3, 1u))); a0 = t0; a1 = t1; a2 = t2; a3 = t3; a4 = t4; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_G_dctors(V *a) { (void)a; return F_G_dctors(a[0], a[1], a[2], a[3], a[4]); }
static V S1538(void) { static V c; if (!c) c = MKS("Nat"); return c; }
static V S1539(void) { static V c; if (!c) c = MKS("Zero"); return c; }
static V F_G_dctor__kind(V a0, V a1, V a2, V a3) {
top:;
return F_Bool_dpick(F_Str_deq(a0, S1538()), F_Bool_dpick(F_Str_deq(a1, S1539()), 3u, 4u), F_Bool_dpick(F_Bool_dand(F_U32_dis__eq(a2, 1u), F_U32_dis__eq(a3, 1u)), 2u, F_Bool_dpick(F_U32_dis__zero(a3), 1u, 0u)));
}
static V W_G_dctor__kind(V *a) { (void)a; return F_G_dctor__kind(a[0], a[1], a[2], a[3]); }
static V S1542(void) { static V c; if (!c) c = MKS("\012"); return c; }
static V S1544(void) { static V c; if (!c) c = MKS("bendc: compilation failed"); return c; }
static V L1543(V *a) {
return F_IO_ddie(1u, S1544());
}
static V F_Main_demit(V a0) {
top:;
V v1540 = a0;
V s1541 = FLD(v1540, 1);
if ((s1541) == IMM(0)) {
return F_IO_dwrite(FLD(v1540, 0));
} else if (TAG(s1541) == 1) {
return F_IO_dbind(F_IO_dprint__err(F_String_djoin(F_List_dreverse(C2(1, FLD(s1541, 0), FLD(s1541, 1))), S1542())), mk_clo(L1543, 1, 0, 0));
} else { bend_fail("incomplete match"); }
}
static V W_Main_demit(V *a) { (void)a; return F_Main_demit(a[0]); }
static V E_IO_dprint__err(V *a) { return apply(a[2], H_io_print_err(a[0])); }
static V F_IO_dprint__err(V a0) { return mk_clo(E_IO_dprint__err, 3, 1, (V[]){a0}); }
static V W_IO_dprint__err(V *a) { (void)a; return F_IO_dprint__err(a[0]); }
static V L1547(V *a) {
return apply(apply(apply(a[2], a[3]), a[1]), a[0]);
}
static V L1546(V *a) {
return apply(apply(a[2], a[1]), mk_clo(L1547, 4, 3, (V[]){a[3], a[1], a[0]}));
}
static V L1545(V *a) {
return mk_clo(L1546, 4, 3, (V[]){a[0], a[2], a[1]});
}
static V F_IO_dbind(V a2, V a3) {
top:;
return mk_clo(L1545, 3, 2, (V[]){a3, a2});
}
static V W_IO_dbind(V *a) { (void)a; return F_IO_dbind(a[2], a[3]); }
static V E_IO_dwrite(V *a) { return apply(a[2], H_io_write(a[0])); }
static V F_IO_dwrite(V a0) { return mk_clo(E_IO_dwrite, 3, 1, (V[]){a0}); }
static V W_IO_dwrite(V *a) { (void)a; return F_IO_dwrite(a[0]); }
static V S1549(void) { static V c; if (!c) c = MKS("bendc: imports nested too deeply at "); return c; }
static V L1550(V *a) {
return F_Main_dload_dparsed(a[1], F_Mod_ddir(a[0]), a[0], F_Main_dparse(a[2]));
}
static V F_Main_dload(V a0, V a1) {
top:;
V s1548 = a0;
if ((s1548) == 0) {
return F_IO_ddie(1u, F_String_dappend(S1549(), a1));
} else if ((s1548) >= 1) {
return F_IO_dbind(F_IO_dread__file(a1), mk_clo(L1550, 3, 2, (V[]){a1, (s1548 - 1)}));
} else { bend_fail("incomplete match"); }
}
static V W_Main_dload(V *a) { (void)a; return F_Main_dload(a[0], a[1]); }
static V F_Mod_ddir(V a0) {
top:;
return F_Str_drev(F_Mod_ddir_dgo(F_Str_drev(a0)));
}
static V W_Mod_ddir(V *a) { (void)a; return F_Mod_ddir(a[0]); }
static V F_Mod_ddir_dgo(V a0) {
top:;
V s1551 = a0;
if ((s1551) == IMM(0)) {
return IMM(0);
} else if (TAG(s1551) == 1) {
return F_Mod_ddir_dif(FLD(s1551, 0), FLD(s1551, 1), F_U32_dis__eq(FLD(s1551, 0), 47u));
} else { bend_fail("incomplete match"); }
}
static V W_Mod_ddir_dgo(V *a) { (void)a; return F_Mod_ddir_dgo(a[0]); }
static V F_Mod_ddir_dif(V a0, V a1, V a2) {
top:;
V s1552 = a2;
if ((s1552) == IMM(1)) {
return C2(1, a0, a1);
} else if ((s1552) == IMM(0)) {
return F_Mod_ddir_dgo(a1);
} else { bend_fail("incomplete match"); }
}
static V W_Mod_ddir_dif(V *a) { (void)a; return F_Mod_ddir_dif(a[0], a[1], a[2]); }
static V S1554(void) { static V c; if (!c) c = MKS("bendc: parse error in "); return c; }
static V S1555(void) { static V c; if (!c) c = MKS(": "); return c; }
static V L1556(V *a) {
return F_IO_dpure(F_List_dappend(a[1], a[0]));
}
static V F_Main_dload_dparsed(V a0, V a1, V a2, V a3) {
top:;
V s1553 = a3;
if (TAG(s1553) == 0) {
return F_IO_ddie(1u, F_String_dappend(S1554(), F_String_dappend(a2, F_String_dappend(S1555(), FLD(s1553, 0)))));
} else if (TAG(s1553) == 1) {
return F_IO_dbind(F_Main_dimports(a0, a1, FLD(s1553, 0)), mk_clo(L1556, 2, 1, (V[]){FLD(s1553, 0)}));
} else { bend_fail("incomplete match"); }
}
static V W_Main_dload_dparsed(V *a) { (void)a; return F_Main_dload_dparsed(a[0], a[1], a[2], a[3]); }
static V L1558(V *a) {
return apply(a[1], a[0]);
}
static V L1557(V *a) {
return mk_clo(L1558, 2, 1, (V[]){a[0]});
}
static V F_IO_dpure(V a1) {
top:;
return mk_clo(L1557, 2, 1, (V[]){a1});
}
static V W_IO_dpure(V *a) { (void)a; return F_IO_dpure(a[1]); }
static V S1560(void) { static V c; if (!c) c = MKS("Base"); return c; }
static V F_Main_dimports(V a0, V a1, V a2) {
top:;
V s1559 = a2;
if ((s1559) == IMM(0)) {
return F_IO_dpure(IMM(0));
} else if (TAG(s1559) == 1 && TAG(FLD(s1559, 0)) == 4) {
return F_Main_dimports_done(a0, a1, FLD(FLD(s1559, 0), 0), FLD(FLD(s1559, 0), 1), FLD(s1559, 1), F_Str_deq(FLD(FLD(s1559, 0), 0), S1560()));
} else if (TAG(s1559) == 1) {
{ V t0 = a0; V t1 = a1; V t2 = FLD(s1559, 1); a0 = t0; a1 = t1; a2 = t2; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Main_dimports(V *a) { (void)a; return F_Main_dimports(a[0], a[1], a[2]); }
static V L1563(V *a) {
return F_IO_dpure(F_List_dappend(F_Mod_dqualify(a[1], a[0]), a[2]));
}
static V L1562(V *a) {
return F_IO_dbind(F_Main_dimports(a[3], a[2], a[1]), mk_clo(L1563, 3, 2, (V[]){a[4], a[0]}));
}
static V F_Main_dimports_done(V a0, V a1, V a2, V a3, V a4, V a5) {
top:;
V s1561 = a5;
if ((s1561) == IMM(1)) {
return F_Main_dimports(a0, a1, a4);
} else if ((s1561) == IMM(0)) {
return F_IO_dbind(F_Main_dload(a0, F_String_dappend(a1, a2)), mk_clo(L1562, 5, 4, (V[]){a3, a4, a1, a0}));
} else { bend_fail("incomplete match"); }
}
static V W_Main_dimports_done(V *a) { (void)a; return F_Main_dimports_done(a[0], a[1], a[2], a[3], a[4], a[5]); }
static V F_Mod_dqualify(V a0, V a1) {
top:;
return F_Mod_ddecls(C2(0, a0, F_Mod_dnames(a1, IMM(0))), a1);
}
static V W_Mod_dqualify(V *a) { (void)a; return F_Mod_dqualify(a[0], a[1]); }
static V F_Mod_dnames(V a0, V a1) {
top:;
V s1564 = a0;
if ((s1564) == IMM(0)) {
return a1;
} else if (TAG(s1564) == 1 && TAG(FLD(s1564, 0)) == 0) {
{ V t0 = FLD(s1564, 1); V t1 = C2(1, FLD(FLD(s1564, 0), 0), a1); a0 = t0; a1 = t1; goto top; }
} else if (TAG(s1564) == 1 && TAG(FLD(s1564, 0)) == 1) {
{ V t0 = FLD(s1564, 1); V t1 = C2(1, FLD(FLD(s1564, 0), 0), a1); a0 = t0; a1 = t1; goto top; }
} else if (TAG(s1564) == 1 && TAG(FLD(s1564, 0)) == 2) {
{ V t0 = FLD(s1564, 1); V t1 = C2(1, FLD(FLD(s1564, 0), 0), a1); a0 = t0; a1 = t1; goto top; }
} else if (TAG(s1564) == 1 && TAG(FLD(s1564, 0)) == 3) {
{ V t0 = FLD(s1564, 1); V t1 = C2(1, FLD(FLD(s1564, 0), 0), F_Mod_dctor__names(FLD(FLD(s1564, 0), 2), a1)); a0 = t0; a1 = t1; goto top; }
} else if (TAG(s1564) == 1 && TAG(FLD(s1564, 0)) == 4) {
{ V t0 = FLD(s1564, 1); V t1 = a1; a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Mod_dnames(V *a) { (void)a; return F_Mod_dnames(a[0], a[1]); }
static V F_Mod_dctor__names(V a0, V a1) {
top:;
V s1565 = a0;
if ((s1565) == IMM(0)) {
return a1;
} else if (TAG(s1565) == 1) {
{ V t0 = FLD(s1565, 1); V t1 = C2(1, FLD(FLD(s1565, 0), 0), a1); a0 = t0; a1 = t1; goto top; }
} else { bend_fail("incomplete match"); }
}
static V W_Mod_dctor__names(V *a) { (void)a; return F_Mod_dctor__names(a[0], a[1]); }
static V F_Mod_ddecls(V a0, V a1) {
top:;
V s1566 = a1;
if ((s1566) == IMM(0)) {
return IMM(0);
} else if (TAG(s1566) == 1) {
return C2(1, F_Mod_ddecl(a0, FLD(s1566, 0)), F_Mod_ddecls(a0, FLD(s1566, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Mod_ddecls(V *a) { (void)a; return F_Mod_ddecls(a[0], a[1]); }
static V F_Mod_ddecl(V a0, V a1) {
top:;
V s1567 = a1;
if (TAG(s1567) == 0) {
return C4(0, F_Mod_dq(a0, FLD(s1567, 0)), FLD(s1567, 1), F_Mod_dexpr(a0, F_Mod_dparam__names(FLD(s1567, 1)), FLD(s1567, 2)), F_Mod_dexpr(a0, IMM(0), FLD(s1567, 3)));
} else if (TAG(s1567) == 1) {
return C2(1, F_Mod_dq(a0, FLD(s1567, 0)), FLD(s1567, 1));
} else if (TAG(s1567) == 2) {
return C2(2, F_Mod_dq(a0, FLD(s1567, 0)), FLD(s1567, 1));
} else if (TAG(s1567) == 3) {
return C3(3, F_Mod_dq(a0, FLD(s1567, 0)), FLD(s1567, 1), F_Mod_dctors(a0, FLD(s1567, 2)));
} else if (TAG(s1567) == 4) {
return C2(4, FLD(s1567, 0), FLD(s1567, 1));
} else { bend_fail("incomplete match"); }
}
static V W_Mod_ddecl(V *a) { (void)a; return F_Mod_ddecl(a[0], a[1]); }
static V F_Mod_dctors(V a0, V a1) {
top:;
V s1568 = a1;
if ((s1568) == IMM(0)) {
return IMM(0);
} else if (TAG(s1568) == 1) {
return C2(1, C2(0, F_Mod_dq(a0, FLD(FLD(s1568, 0), 0)), F_Mod_dfields(a0, FLD(FLD(s1568, 0), 1))), F_Mod_dctors(a0, FLD(s1568, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Mod_dctors(V *a) { (void)a; return F_Mod_dctors(a[0], a[1]); }
static V F_Mod_dfields(V a0, V a1) {
top:;
V s1569 = a1;
if ((s1569) == IMM(0)) {
return IMM(0);
} else if (TAG(s1569) == 1) {
return C2(1, C2(0, FLD(FLD(s1569, 0), 0), F_Mod_dexpr(a0, IMM(0), FLD(FLD(s1569, 0), 1))), F_Mod_dfields(a0, FLD(s1569, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Mod_dfields(V *a) { (void)a; return F_Mod_dfields(a[0], a[1]); }
static V F_Mod_dexpr(V a0, V a1, V a2) {
top:;
V s1570 = a2;
if (TAG(s1570) == 0) {
return C1(0, F_Mod_dvar(a0, a1, FLD(s1570, 0)));
} else if (TAG(s1570) == 5) {
return C2(5, F_Mod_dexpr(a0, a1, FLD(s1570, 0)), F_Mod_dexprs(a0, a1, FLD(s1570, 1)));
} else if (TAG(s1570) == 6) {
return C2(6, F_Mod_dq(a0, FLD(s1570, 0)), F_Mod_dexprs(a0, a1, FLD(s1570, 1)));
} else if (TAG(s1570) == 7) {
return C2(7, F_Mod_dpat(a0, FLD(s1570, 0)), F_Mod_dexpr(a0, F_Pat_dvars(FLD(s1570, 0), a1), FLD(s1570, 1)));
} else if (TAG(s1570) == 8) {
return C3(8, F_Mod_dpat(a0, FLD(s1570, 0)), F_Mod_dexpr(a0, a1, FLD(s1570, 1)), F_Mod_dexpr(a0, F_Pat_dvars(FLD(s1570, 0), a1), FLD(s1570, 2)));
} else if (TAG(s1570) == 9) {
return C2(9, F_Mod_dexprs(a0, a1, FLD(s1570, 0)), F_Mod_dexprs(a0, a1, FLD(s1570, 1)));
} else if (TAG(s1570) == 10) {
return C2(10, F_Mod_dpats(a0, FLD(s1570, 0)), F_Mod_dexpr(a0, F_Pats_dvars(FLD(s1570, 0), a1), FLD(s1570, 1)));
} else if (TAG(s1570) == 11) {
return C2(11, FLD(s1570, 0), F_Mod_dexpr(a0, a1, FLD(s1570, 1)));
} else if (TAG(s1570) == 12) {
return C3(12, FLD(s1570, 0), F_Mod_dexpr(a0, a1, FLD(s1570, 1)), F_Mod_dexpr(a0, a1, FLD(s1570, 2)));
} else if (TAG(s1570) == 13) {
return C2(13, F_Mod_dexpr(a0, a1, FLD(s1570, 0)), F_Mod_dvar(a0, a1, FLD(s1570, 1)));
} else if (TAG(s1570) == 14) {
return C2(14, F_Mod_dvar(a0, a1, FLD(s1570, 0)), F_Mod_dexprs(a0, a1, FLD(s1570, 1)));
} else {
return s1570;
}
}
static V W_Mod_dexpr(V *a) { (void)a; return F_Mod_dexpr(a[0], a[1], a[2]); }
static V F_Mod_dexprs(V a0, V a1, V a2) {
top:;
V s1571 = a2;
if ((s1571) == IMM(0)) {
return IMM(0);
} else if (TAG(s1571) == 1) {
return C2(1, F_Mod_dexpr(a0, a1, FLD(s1571, 0)), F_Mod_dexprs(a0, a1, FLD(s1571, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Mod_dexprs(V *a) { (void)a; return F_Mod_dexprs(a[0], a[1], a[2]); }
static V F_Mod_dvar(V a0, V a1, V a2) {
top:;
return F_Bool_dpick(F_Str_dhas(a1, a2), a2, F_Mod_dq(a0, a2));
}
static V W_Mod_dvar(V *a) { (void)a; return F_Mod_dvar(a[0], a[1], a[2]); }
static V S1573(void) { static V c; if (!c) c = MKS("."); return c; }
static V F_Mod_dq(V a0, V a1) {
top:;
V v1572 = a0;
return F_Bool_dpick(F_Str_dhas(FLD(v1572, 1), a1), F_String_dappend(FLD(v1572, 0), F_String_dappend(S1573(), a1)), a1);
}
static V W_Mod_dq(V *a) { (void)a; return F_Mod_dq(a[0], a[1]); }
static V F_Mod_dpats(V a0, V a1) {
top:;
V s1574 = a1;
if ((s1574) == IMM(0)) {
return IMM(0);
} else if (TAG(s1574) == 1) {
return C2(1, F_Mod_dpat(a0, FLD(s1574, 0)), F_Mod_dpats(a0, FLD(s1574, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Mod_dpats(V *a) { (void)a; return F_Mod_dpats(a[0], a[1]); }
static V F_Mod_dpat(V a0, V a1) {
top:;
V s1575 = a1;
if (TAG(s1575) == 1) {
return C2(1, F_Mod_dq(a0, FLD(s1575, 0)), F_Mod_dpats(a0, FLD(s1575, 1)));
} else if (TAG(s1575) == 3) {
return C2(3, FLD(s1575, 0), F_Mod_dpat(a0, FLD(s1575, 1)));
} else {
return s1575;
}
}
static V W_Mod_dpat(V *a) { (void)a; return F_Mod_dpat(a[0], a[1]); }
static V F_Mod_dparam__names(V a0) {
top:;
V s1576 = a0;
if ((s1576) == IMM(0)) {
return IMM(0);
} else if (TAG(s1576) == 1) {
return C2(1, FLD(FLD(s1576, 0), 0), F_Mod_dparam__names(FLD(s1576, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Mod_dparam__names(V *a) { (void)a; return F_Mod_dparam__names(a[0]); }
static V S1577(void) { static V c; if (!c) c = MKS("r"); return c; }
static V L1579(V *a) {
return F_IO_dread__fin(a[0]);
}
static V L1578(V *a) {
return F_IO_dbind(F_File_dread(a[0], 2000000000u), mk_clo(L1579, 1, 0, 0));
}
static V F_IO_dread__file(V a0) {
top:;
return F_IO_dbind(F_IO_dtry(F_File_dopen(a0, S1577())), mk_clo(L1578, 1, 0, 0));
}
static V W_IO_dread__file(V *a) { (void)a; return F_IO_dread__file(a[0]); }
static V L1581(V *a) {
return F_IO_dpass(a[0]);
}
static V F_IO_dread__fin(V a0) {
top:;
V v1580 = a0;
return F_IO_dbind(F_File_dclose(FLD(v1580, 0)), mk_clo(L1581, 2, 1, (V[]){FLD(v1580, 1)}));
}
static V W_IO_dread__fin(V *a) { (void)a; return F_IO_dread__fin(a[0]); }
static V F_IO_dpass(V a1) {
top:;
V s1582 = a1;
if (TAG(s1582) == 1) {
return F_IO_dpure(FLD(s1582, 0));
} else if (TAG(s1582) == 0) {
return F_IO_ddie(FLD(FLD(s1582, 0), 0), FLD(FLD(s1582, 0), 1));
} else { bend_fail("incomplete match"); }
}
static V W_IO_dpass(V *a) { (void)a; return F_IO_dpass(a[1]); }
static V E_File_dclose(V *a) { return apply(a[2], H_file_close(a[0])); }
static V F_File_dclose(V a0) { return mk_clo(E_File_dclose, 3, 1, (V[]){a0}); }
static V W_File_dclose(V *a) { (void)a; return F_File_dclose(a[0]); }
static V E_File_dread(V *a) { return apply(a[3], H_file_read(a[0], a[1])); }
static V F_File_dread(V a0, V a1) { return mk_clo(E_File_dread, 4, 2, (V[]){a0, a1}); }
static V W_File_dread(V *a) { (void)a; return F_File_dread(a[0], a[1]); }
static V E_File_dopen(V *a) { return apply(a[3], H_file_open(a[0], a[1])); }
static V F_File_dopen(V a0, V a1) { return mk_clo(E_File_dopen, 4, 2, (V[]){a0, a1}); }
static V W_File_dopen(V *a) { (void)a; return F_File_dopen(a[0], a[1]); }
static V F_IO_dtry(V a1) {
top:;
return F_IO_dbind(a1, mk_clo(W_IO_dpass, 2, 1, (V[]){0}));
}
static V W_IO_dtry(V *a) { (void)a; return F_IO_dtry(a[1]); }
static V S1584(void) { static V c; if (!c) c = MKS("bendc: parse error: "); return c; }
static V F_Main_dast(V a0) {
top:;
V s1583 = a0;
if (TAG(s1583) == 0) {
return F_IO_ddie(1u, F_String_dappend(S1584(), FLD(s1583, 0)));
} else if (TAG(s1583) == 1) {
return F_IO_dwrite(F_Decls_dshow(FLD(s1583, 0)));
} else { bend_fail("incomplete match"); }
}
static V W_Main_dast(V *a) { (void)a; return F_Main_dast(a[0]); }
static V F_Decls_dshow(V a0) {
top:;
return F_Decls_dshow_dgo(a0);
}
static V W_Decls_dshow(V *a) { (void)a; return F_Decls_dshow(a[0]); }
static V S1586(void) { static V c; if (!c) c = MKS(""); return c; }
static V S1587(void) { static V c; if (!c) c = MKS("\012"); return c; }
static V F_Decls_dshow_dgo(V a0) {
top:;
V s1585 = a0;
if ((s1585) == IMM(0)) {
return S1586();
} else if (TAG(s1585) == 1) {
return F_String_dappend(F_Decl_dshow(FLD(s1585, 0)), F_String_dappend(S1587(), F_Decls_dshow_dgo(FLD(s1585, 1))));
} else { bend_fail("incomplete match"); }
}
static V W_Decls_dshow_dgo(V *a) { (void)a; return F_Decls_dshow_dgo(a[0]); }
static V S1589(void) { static V c; if (!c) c = MKS("def "); return c; }
static V S1590(void) { static V c; if (!c) c = MKS("("); return c; }
static V S1591(void) { static V c; if (!c) c = MKS(") = "); return c; }
static V S1592(void) { static V c; if (!c) c = MKS("eff "); return c; }
static V S1593(void) { static V c; if (!c) c = MKS("("); return c; }
static V S1594(void) { static V c; if (!c) c = MKS(")"); return c; }
static V S1595(void) { static V c; if (!c) c = MKS("law "); return c; }
static V S1596(void) { static V c; if (!c) c = MKS("("); return c; }
static V S1597(void) { static V c; if (!c) c = MKS(")"); return c; }
static V S1598(void) { static V c; if (!c) c = MKS("type "); return c; }
static V S1599(void) { static V c; if (!c) c = MKS(" "); return c; }
static V S1600(void) { static V c; if (!c) c = MKS("import "); return c; }
static V S1601(void) { static V c; if (!c) c = MKS(" as "); return c; }
static V F_Decl_dshow(V a0) {
top:;
V s1588 = a0;
if (TAG(s1588) == 0) {
return F_String_dappend(S1589(), F_String_dappend(FLD(s1588, 0), F_String_dappend(S1590(), F_String_dappend(F_Params_dshow(FLD(s1588, 1)), F_String_dappend(S1591(), F_Expr_dshow(FLD(s1588, 2)))))));
} else if (TAG(s1588) == 1) {
return F_String_dappend(S1592(), F_String_dappend(FLD(s1588, 0), F_String_dappend(S1593(), F_String_dappend(F_Params_dshow(FLD(s1588, 1)), S1594()))));
} else if (TAG(s1588) == 2) {
return F_String_dappend(S1595(), F_String_dappend(FLD(s1588, 0), F_String_dappend(S1596(), F_String_dappend(F_Params_dshow(FLD(s1588, 1)), S1597()))));
} else if (TAG(s1588) == 3) {
return F_String_dappend(S1598(), F_String_dappend(FLD(s1588, 0), F_String_dappend(S1599(), F_Ctors_dshow(FLD(s1588, 2)))));
} else if (TAG(s1588) == 4) {
return F_String_dappend(S1600(), F_String_dappend(FLD(s1588, 0), F_String_dappend(S1601(), FLD(s1588, 1))));
} else { bend_fail("incomplete match"); }
}
static V W_Decl_dshow(V *a) { (void)a; return F_Decl_dshow(a[0]); }
static V S1603(void) { static V c; if (!c) c = MKS(""); return c; }
static V S1604(void) { static V c; if (!c) c = MKS(" "); return c; }
static V F_Ctors_dshow(V a0) {
top:;
V s1602 = a0;
if ((s1602) == IMM(0)) {
return S1603();
} else if (TAG(s1602) == 1) {
return F_String_dappend(F_Ctor_dshow(FLD(s1602, 0)), F_String_dappend(S1604(), F_Ctors_dshow(FLD(s1602, 1))));
} else { bend_fail("incomplete match"); }
}
static V W_Ctors_dshow(V *a) { (void)a; return F_Ctors_dshow(a[0]); }
static V S1606(void) { static V c; if (!c) c = MKS("{"); return c; }
static V S1607(void) { static V c; if (!c) c = MKS("}"); return c; }
static V F_Ctor_dshow(V a0) {
top:;
V v1605 = a0;
return F_String_dappend(FLD(v1605, 0), F_String_dappend(S1606(), F_String_dappend(F_Fields_dshow(FLD(v1605, 1)), S1607())));
}
static V W_Ctor_dshow(V *a) { (void)a; return F_Ctor_dshow(a[0]); }
static V S1609(void) { static V c; if (!c) c = MKS(""); return c; }
static V S1610(void) { static V c; if (!c) c = MKS(":"); return c; }
static V S1611(void) { static V c; if (!c) c = MKS(" "); return c; }
static V F_Fields_dshow(V a0) {
top:;
V s1608 = a0;
if ((s1608) == IMM(0)) {
return S1609();
} else if (TAG(s1608) == 1) {
return F_String_dappend(FLD(FLD(s1608, 0), 0), F_String_dappend(S1610(), F_String_dappend(F_Expr_dshow(FLD(FLD(s1608, 0), 1)), F_String_dappend(S1611(), F_Fields_dshow(FLD(s1608, 1))))));
} else { bend_fail("incomplete match"); }
}
static V W_Fields_dshow(V *a) { (void)a; return F_Fields_dshow(a[0]); }
static V S1613(void) { static V c; if (!c) c = MKS(""); return c; }
static V S1614(void) { static V c; if (!c) c = MKS(" "); return c; }
static V F_Params_dshow(V a0) {
top:;
V s1612 = a0;
if ((s1612) == IMM(0)) {
return S1613();
} else if (TAG(s1612) == 1) {
return F_String_dappend(F_Param_dshow(FLD(s1612, 0)), F_String_dappend(S1614(), F_Params_dshow(FLD(s1612, 1))));
} else { bend_fail("incomplete match"); }
}
static V W_Params_dshow(V *a) { (void)a; return F_Params_dshow(a[0]); }
static V S1616(void) { static V c; if (!c) c = MKS(":"); return c; }
static V F_Param_dshow(V a0) {
top:;
V v1615 = a0;
return F_String_dappend(F_U32_dshow(FLD(v1615, 1)), F_String_dappend(FLD(v1615, 0), F_String_dappend(S1616(), FLD(v1615, 2))));
}
static V W_Param_dshow(V *a) { (void)a; return F_Param_dshow(a[0]); }
static V S1618(void) { static V c; if (!c) c = MKS(""); return c; }
static V F_Toks_dshow(V a0) {
top:;
V s1617 = a0;
if ((s1617) == IMM(0)) {
return S1618();
} else if (TAG(s1617) == 1) {
return F_String_dappend(F_Tok_dshow(FLD(s1617, 0)), F_Toks_dshow(FLD(s1617, 1)));
} else { bend_fail("incomplete match"); }
}
static V W_Toks_dshow(V *a) { (void)a; return F_Toks_dshow(a[0]); }
static V S1620(void) { static V c; if (!c) c = MKS(" "); return c; }
static V S1621(void) { static V c; if (!c) c = MKS(""); return c; }
static V F_Tok_dshow(V a0) {
top:;
V v1619 = a0;
return F_String_dappend(F_Bool_dpick(FLD(v1619, 1), S1620(), S1621()), F_TK_dshow(FLD(v1619, 0)));
}
static V W_Tok_dshow(V *a) { (void)a; return F_Tok_dshow(a[0]); }
static V E_IO_dprint(V *a) { return apply(a[2], H_io_print(a[0])); }
static V F_IO_dprint(V a0) { return mk_clo(E_IO_dprint, 3, 1, (V[]){a0}); }
static V W_IO_dprint(V *a) { (void)a; return F_IO_dprint(a[0]); }
static V E_IO_dargs(V *a) { return apply(a[1], H_io_args()); }
static V F_IO_dargs(void) { return mk_clo(E_IO_dargs, 2, 0, 0); }
static V W_IO_dargs(V *a) { (void)a; return F_IO_dargs(); }

int main(int argc, char **argv) { return bend_run(argc, argv, F_main); }
