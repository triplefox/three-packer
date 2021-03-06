/* Generated by Nim Compiler v0.10.2 */
/*   (c) 2014 Andreas Rumpf */
/* The generated code is subject to the original license. */
/* Compiled for: Windows, i386, gcc */
/* Command for C compiler:
   gcc.exe -c  -w  -IC:\Nim\lib -o c:\dropbox\2015\nim\packer\example\nimcache\stdlib_parseutils.o c:\dropbox\2015\nim\packer\example\nimcache\stdlib_parseutils.c */
#define NIM_INTBITS 32
#include "nimbase.h"

#include <string.h>
typedef struct slice86066 slice86066;
typedef struct NimStringDesc NimStringDesc;
typedef struct TGenericSeq TGenericSeq;
struct  slice86066  {
NI A;
NI B;
};
struct  TGenericSeq  {
NI len;
NI reserved;
};
struct  NimStringDesc  {
  TGenericSeq Sup;
NIM_CHAR data[SEQ_DECL_SIZE];
};
static N_INLINE(slice86066, HEX2EHEX2E_92098)(NI a_92102, NI b_92104);
static N_INLINE(void, nimFrame)(TFrame* s);
N_NOINLINE(void, stackoverflow_18801)(void);
static N_INLINE(void, popFrame)(void);
N_NIMCALL(NI, rawparseint_91808)(NimStringDesc* s, NI64* b, NI start);
N_NOINLINE(void, raiseIndexError)(void);
static N_INLINE(NI, addInt)(NI a, NI b);
N_NOINLINE(void, raiseOverflow)(void);
N_NIMCALL(NI64, mulInt64)(NI64 a, NI64 b);
static N_INLINE(NI, subInt)(NI a, NI b);
static N_INLINE(NI64, subInt64)(NI64 a, NI64 b);
N_NIMCALL(NI, nimParseBiggestFloat)(NimStringDesc* s, NF* number, NI start);
N_NIMCALL(NI, nimParseBiggestFloat)(NimStringDesc* s, NF* number, NI start);
extern TFrame* frameptr_16242;

static N_INLINE(void, nimFrame)(TFrame* s) {
	NI LOC1;
	LOC1 = 0;
	{
		if (!(frameptr_16242 == NIM_NIL)) goto LA4;
		LOC1 = 0;
	}
	goto LA2;
	LA4: ;
	{
		LOC1 = ((NI) ((NI16)((*frameptr_16242).calldepth + ((NI16) 1))));
	}
	LA2: ;
	(*s).calldepth = ((NI16) (LOC1));
	(*s).prev = frameptr_16242;
	frameptr_16242 = s;
	{
		if (!((*s).calldepth == ((NI16) 2000))) goto LA9;
		stackoverflow_18801();
	}
	LA9: ;
}

static N_INLINE(void, popFrame)(void) {
	frameptr_16242 = (*frameptr_16242).prev;
}

static N_INLINE(slice86066, HEX2EHEX2E_92098)(NI a_92102, NI b_92104) {
	slice86066 result;
	nimfr("..", "system.nim")
	memset((void*)(&result), 0, sizeof(result));
	nimln(226, "system.nim");
	result.A = a_92102;
	nimln(227, "system.nim");
	result.B = b_92104;
	popFrame();
	return result;
}

static N_INLINE(NI, addInt)(NI a, NI b) {
	NI result;
	result = 0;
	result = (NI)((NU32)(a) + (NU32)(b));
	{
		NIM_BOOL LOC3;
		LOC3 = 0;
		LOC3 = (0 <= (NI)(result ^ a));
		if (LOC3) goto LA4;
		LOC3 = (0 <= (NI)(result ^ b));
		LA4: ;
		if (!LOC3) goto LA5;
		goto BeforeRet;
	}
	LA5: ;
	raiseOverflow();
	BeforeRet: ;
	return result;
}

static N_INLINE(NI, subInt)(NI a, NI b) {
	NI result;
	result = 0;
	result = (NI)((NU32)(a) - (NU32)(b));
	{
		NIM_BOOL LOC3;
		LOC3 = 0;
		LOC3 = (0 <= (NI)(result ^ a));
		if (LOC3) goto LA4;
		LOC3 = (0 <= (NI)(result ^ (NI)((NU32) ~(b))));
		LA4: ;
		if (!LOC3) goto LA5;
		goto BeforeRet;
	}
	LA5: ;
	raiseOverflow();
	BeforeRet: ;
	return result;
}

static N_INLINE(NI64, subInt64)(NI64 a, NI64 b) {
	NI64 result;
	result = 0;
	result = (NI64)((NU64)(a) - (NU64)(b));
	{
		NIM_BOOL LOC3;
		LOC3 = 0;
		LOC3 = (IL64(0) <= (NI64)(result ^ a));
		if (LOC3) goto LA4;
		LOC3 = (IL64(0) <= (NI64)(result ^ (NI64)((NU64) ~(b))));
		LA4: ;
		if (!LOC3) goto LA5;
		goto BeforeRet;
	}
	LA5: ;
	raiseOverflow();
	BeforeRet: ;
	return result;
}

N_NIMCALL(NI, rawparseint_91808)(NimStringDesc* s, NI64* b, NI start) {
	NI result;
	NI64 sign;
	NI i;
	nimfr("rawParseInt", "parseutils.nim")
	result = 0;
	nimln(194, "parseutils.nim");
	sign = IL64(-1);
	nimln(195, "parseutils.nim");
	i = start;
	nimln(196, "parseutils.nim");
	{
		nimln(196, "parseutils.nim");
		if ((NU)(i) > (NU)(s->Sup.len)) raiseIndexError();
		if (!((NU8)(s->data[i]) == (NU8)(43))) goto LA3;
		nimln(196, "parseutils.nim");
		i = addInt(i, 1);
	}
	goto LA1;
	LA3: ;
	{
		nimln(197, "parseutils.nim");
		if ((NU)(i) > (NU)(s->Sup.len)) raiseIndexError();
		if (!((NU8)(s->data[i]) == (NU8)(45))) goto LA6;
		nimln(198, "parseutils.nim");
		i = addInt(i, 1);
		nimln(199, "parseutils.nim");
		sign = IL64(1);
	}
	goto LA1;
	LA6: ;
	LA1: ;
	nimln(200, "parseutils.nim");
	{
		NI64 TMP230;
		NI TMP231;
		nimln(200, "parseutils.nim");
		if ((NU)(i) > (NU)(s->Sup.len)) raiseIndexError();
		if (!(((NU8)(s->data[i])) >= ((NU8)(48)) && ((NU8)(s->data[i])) <= ((NU8)(57)))) goto LA10;
		nimln(201, "parseutils.nim");
		(*b) = IL64(0);
		{
			nimln(202, "parseutils.nim");
			while (1) {
				NI64 TMP227;
				NI TMP228;
				NI64 TMP229;
				nimln(202, "parseutils.nim");
				if ((NU)(i) > (NU)(s->Sup.len)) raiseIndexError();
				if (!(((NU8)(s->data[i])) >= ((NU8)(48)) && ((NU8)(s->data[i])) <= ((NU8)(57)))) goto LA13;
				nimln(203, "parseutils.nim");
				nimln(203, "parseutils.nim");
				nimln(203, "parseutils.nim");
				TMP227 = mulInt64((*b), IL64(10));
				nimln(203, "parseutils.nim");
				nimln(203, "parseutils.nim");
				if ((NU)(i) > (NU)(s->Sup.len)) raiseIndexError();
				TMP228 = subInt(((NI) (((NU8)(s->data[i])))), 48);
				TMP229 = subInt64((NI64)(TMP227), ((NI64) ((NI32)(TMP228))));
				(*b) = (NI64)(TMP229);
				nimln(204, "parseutils.nim");
				i = addInt(i, 1);
				{
					nimln(205, "parseutils.nim");
					while (1) {
						nimln(205, "parseutils.nim");
						if ((NU)(i) > (NU)(s->Sup.len)) raiseIndexError();
						if (!((NU8)(s->data[i]) == (NU8)(95))) goto LA15;
						nimln(205, "parseutils.nim");
						i = addInt(i, 1);
					} LA15: ;
				}
			} LA13: ;
		}
		nimln(206, "parseutils.nim");
		nimln(206, "parseutils.nim");
		TMP230 = mulInt64((*b), sign);
		(*b) = (NI64)(TMP230);
		nimln(207, "parseutils.nim");
		nimln(207, "parseutils.nim");
		TMP231 = subInt(i, start);
		result = (NI32)(TMP231);
	}
	LA10: ;
	popFrame();
	return result;
}

N_NIMCALL(NI, npuParseBiggestInt)(NimStringDesc* s, NI64* number, NI start) {
	NI result;
	NI64 res;
	nimfr("parseBiggestInt", "parseutils.nim")
	result = 0;
	res = 0;
	nimln(218, "parseutils.nim");
	result = rawparseint_91808(s, (&res), start);
	nimln(219, "parseutils.nim");
	(*number) = res;
	popFrame();
	return result;
}

N_NIMCALL(NI, npuParseFloat)(NimStringDesc* s, NF* number, NI start) {
	NI result;
	NF bf;
	nimfr("parseFloat", "parseutils.nim")
	result = 0;
	bf = 0;
	nimln(246, "parseutils.nim");
	nimln(246, "parseutils.nim");
	result = nimParseBiggestFloat(s, (&bf), start);
	nimln(247, "parseutils.nim");
	(*number) = bf;
	popFrame();
	return result;
}
NIM_EXTERNC N_NOINLINE(void, stdlib_parseutilsInit)(void) {
	nimfr("parseutils", "parseutils.nim")
	popFrame();
}

NIM_EXTERNC N_NOINLINE(void, stdlib_parseutilsDatInit)(void) {
}

