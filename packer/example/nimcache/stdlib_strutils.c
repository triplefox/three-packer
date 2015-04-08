/* Generated by Nim Compiler v0.10.2 */
/*   (c) 2014 Andreas Rumpf */
/* The generated code is subject to the original license. */
/* Compiled for: Windows, i386, gcc */
/* Command for C compiler:
   gcc.exe -c  -w  -IC:\Nim\lib -o c:\dropbox\2015\nim\packer\example\nimcache\stdlib_strutils.o c:\dropbox\2015\nim\packer\example\nimcache\stdlib_strutils.c */
#define NIM_INTBITS 32
#include "nimbase.h"

#include <string.h>
typedef struct NimStringDesc NimStringDesc;
typedef struct TGenericSeq TGenericSeq;
typedef struct valueerror3249 valueerror3249;
typedef struct Exception Exception;
typedef struct TNimObject TNimObject;
typedef struct TNimType TNimType;
typedef struct TNimNode TNimNode;
typedef struct tcell44933 tcell44933;
typedef struct tcellseq44949 tcellseq44949;
typedef struct tgcheap47016 tgcheap47016;
typedef struct tcellset44945 tcellset44945;
typedef struct tpagedesc44941 tpagedesc44941;
typedef struct tmemregion27210 tmemregion27210;
typedef struct tsmallchunk26440 tsmallchunk26440;
typedef struct tllchunk27204 tllchunk27204;
typedef struct tbigchunk26442 tbigchunk26442;
typedef struct tintset26417 tintset26417;
typedef struct ttrunk26413 ttrunk26413;
typedef struct tavlnode27208 tavlnode27208;
typedef struct tgcstat47014 tgcstat47014;
typedef struct tbasechunk26438 tbasechunk26438;
typedef struct tfreecell26430 tfreecell26430;
struct  TGenericSeq  {
NI len;
NI reserved;
};
struct  NimStringDesc  {
  TGenericSeq Sup;
NIM_CHAR data[SEQ_DECL_SIZE];
};
typedef N_NIMCALL_PTR(void, TY3089) (void* p, NI op);
typedef N_NIMCALL_PTR(void*, TY3094) (void* p);
struct  TNimType  {
NI size;
NU8 kind;
NU8 flags;
TNimType* base;
TNimNode* node;
void* finalizer;
TY3089 marker;
TY3094 deepcopy;
};
struct  TNimObject  {
TNimType* m_type;
};
struct  Exception  {
  TNimObject Sup;
Exception* parent;
NCSTRING name;
NimStringDesc* message;
NimStringDesc* trace;
};
struct  valueerror3249  {
  Exception Sup;
};
struct  TNimNode  {
NU8 kind;
NI offset;
TNimType* typ;
NCSTRING name;
NI len;
TNimNode** sons;
};
struct  tcell44933  {
NI Refcount;
TNimType* Typ;
};
struct  tcellseq44949  {
NI Len;
NI Cap;
tcell44933** D;
};
struct  tcellset44945  {
NI Counter;
NI Max;
tpagedesc44941* Head;
tpagedesc44941** Data;
};
typedef tsmallchunk26440* TY27222[512];
typedef ttrunk26413* ttrunkbuckets26415[256];
struct  tintset26417  {
ttrunkbuckets26415 Data;
};
struct  tmemregion27210  {
NI Minlargeobj;
NI Maxlargeobj;
TY27222 Freesmallchunks;
tllchunk27204* Llmem;
NI Currmem;
NI Maxmem;
NI Freemem;
NI Lastsize;
tbigchunk26442* Freechunkslist;
tintset26417 Chunkstarts;
tavlnode27208* Root;
tavlnode27208* Deleted;
tavlnode27208* Last;
tavlnode27208* Freeavlnodes;
};
struct  tgcstat47014  {
NI Stackscans;
NI Cyclecollections;
NI Maxthreshold;
NI Maxstacksize;
NI Maxstackcells;
NI Cycletablesize;
NI64 Maxpause;
};
struct  tgcheap47016  {
void* Stackbottom;
NI Cyclethreshold;
tcellseq44949 Zct;
tcellseq44949 Decstack;
tcellset44945 Cycleroots;
tcellseq44949 Tempstack;
NI Recgclock;
tmemregion27210 Region;
tgcstat47014 Stat;
};
typedef NU8 TY75869[32];
typedef NI TY26420[16];
struct  tpagedesc44941  {
tpagedesc44941* Next;
NI Key;
TY26420 Bits;
};
struct  tbasechunk26438  {
NI Prevsize;
NI Size;
NIM_BOOL Used;
};
struct  tsmallchunk26440  {
  tbasechunk26438 Sup;
tsmallchunk26440* Next;
tsmallchunk26440* Prev;
tfreecell26430* Freelist;
NI Free;
NI Acc;
NF Data;
};
struct  tllchunk27204  {
NI Size;
NI Acc;
tllchunk27204* Next;
};
struct  tbigchunk26442  {
  tbasechunk26438 Sup;
tbigchunk26442* Next;
tbigchunk26442* Prev;
NI Align;
NF Data;
};
struct  ttrunk26413  {
ttrunk26413* Next;
NI Key;
TY26420 Bits;
};
typedef tavlnode27208* TY27214[2];
struct  tavlnode27208  {
TY27214 Link;
NI Key;
NI Upperbound;
NI Level;
};
struct  tfreecell26430  {
tfreecell26430* Next;
NI Zerofield;
};
N_NIMCALL(NimStringDesc*, mnewString)(NI len);
N_NIMCALL(NimStringDesc*, mnewString)(NI len);
static N_INLINE(NI, subInt)(NI a, NI b);
N_NOINLINE(void, raiseOverflow)(void);
N_NOINLINE(void, raiseIndexError)(void);
static N_INLINE(NI, addInt)(NI a, NI b);
static N_INLINE(void, nimFrame)(TFrame* s);
N_NOINLINE(void, stackoverflow_18801)(void);
static N_INLINE(void, popFrame)(void);
N_NIMCALL(NI, npuParseBiggestInt)(NimStringDesc* s, NI64* number, NI start);
N_NIMCALL(void*, newObj)(TNimType* typ, NI size);
static N_INLINE(void, appendString)(NimStringDesc* dest, NimStringDesc* src);
N_NIMCALL(NimStringDesc*, rawNewString)(NI space);
static N_INLINE(void, asgnRefNoCycle)(void** dest, void* src);
static N_INLINE(tcell44933*, usrtocell_48646)(void* usr);
static N_INLINE(void, rtladdzct_50204)(tcell44933* c);
N_NOINLINE(void, addzct_48617)(tcellseq44949* s, tcell44933* c);
N_NIMCALL(void, raiseException)(Exception* e, NCSTRING ename);
N_NIMCALL(NI, npuParseFloat)(NimStringDesc* s, NF* number, NI start);
N_NIMCALL(NimStringDesc*, rawNewString)(NI cap);
N_NIMCALL(void, nsuAddf)(NimStringDesc** s, NimStringDesc* formatstr, NimStringDesc** a, NI aLen0);
N_NOINLINE(void, invalidformatstring_98671)(void);
N_NIMCALL(NimStringDesc*, copyStringRC1)(NimStringDesc* src);
static N_INLINE(void, nimGCunrefNoCycle)(void* p);
N_NIMCALL(NimStringDesc*, resizeString)(NimStringDesc* dest, NI addlen);
N_NIMCALL(NimStringDesc*, addChar)(NimStringDesc* s, NIM_CHAR c);
N_NIMCALL(NI, mulInt)(NI a, NI b);
N_NIMCALL(NI, findnormalized_98638)(NimStringDesc* x, NimStringDesc** inarray, NI inarrayLen0);
N_NIMCALL(NI, nsuCmpIgnoreStyle)(NimStringDesc* a, NimStringDesc* b);
N_NIMCALL(NIM_CHAR, nsuToLowerChar)(NIM_CHAR c);
static N_INLINE(NI, chckRange)(NI i, NI a, NI b);
N_NOINLINE(void, raiseRangeError)(NI64 val);
N_NIMCALL(NimStringDesc*, copyStrLast)(NimStringDesc* s, NI start_74828, NI last);
N_NIMCALL(NimStringDesc*, copyStrLast)(NimStringDesc* s, NI first, NI last);
N_NIMCALL(NI, nsuFindCharSet)(NimStringDesc* s, TY75869 chars, NI start);
static N_INLINE(NI64, addInt64)(NI64 a, NI64 b);
N_NIMCALL(NimStringDesc*, nimIntToStr)(NI x);
static N_INLINE(void, appendChar)(NimStringDesc* dest, NIM_CHAR c);
STRING_LITERAL(TMP232, "invalid integer: ", 17);
STRING_LITERAL(TMP234, "invalid float: ", 15);
STRING_LITERAL(TMP238, "invalid format string", 21);
STRING_LITERAL(TMP324, "0123456789ABCDEF", 16);
extern TFrame* frameptr_16242;
extern TNimType NTI21601; /* ref ValueError */
extern TNimType NTI3249; /* ValueError */
extern tgcheap47016 gch_47044;

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

N_NIMCALL(NimStringDesc*, nsuRepeatChar)(NI count, NIM_CHAR c) {
	NimStringDesc* result;
	nimfr("repeatChar", "strutils.nim")
	result = 0;
	nimln(512, "strutils.nim");
	nimln(512, "strutils.nim");
	result = mnewString(count);
	{
		NI i_95993;
		NI HEX3Atmp_95995;
		NI TMP190;
		NI res_95998;
		i_95993 = 0;
		HEX3Atmp_95995 = 0;
		nimln(513, "strutils.nim");
		nimln(513, "strutils.nim");
		TMP190 = subInt(count, 1);
		HEX3Atmp_95995 = (NI32)(TMP190);
		nimln(1576, "system.nim");
		res_95998 = 0;
		{
			nimln(1577, "system.nim");
			while (1) {
				nimln(1577, "system.nim");
				if (!(res_95998 <= HEX3Atmp_95995)) goto LA3;
				nimln(1576, "system.nim");
				i_95993 = res_95998;
				nimln(513, "strutils.nim");
				if ((NU)(i_95993) > (NU)(result->Sup.len)) raiseIndexError();
				result->data[i_95993] = c;
				nimln(1579, "system.nim");
				res_95998 = addInt(res_95998, 1);
			} LA3: ;
		}
	}
	popFrame();
	return result;
}

static N_INLINE(void, appendString)(NimStringDesc* dest, NimStringDesc* src) {
	memcpy(((NCSTRING) ((&(*dest).data[((*dest).Sup.len)- 0]))), ((NCSTRING) ((*src).data)), (NI32)((*src).Sup.len + 1));
	(*dest).Sup.len += (*src).Sup.len;
}

static N_INLINE(tcell44933*, usrtocell_48646)(void* usr) {
	tcell44933* result;
	nimfr("usrToCell", "gc.nim")
	result = 0;
	nimln(118, "gc.nim");
	nimln(118, "gc.nim");
	nimln(118, "gc.nim");
	result = ((tcell44933*) ((NI)((NU32)(((NI) (usr))) - (NU32)(((NI)sizeof(tcell44933))))));
	popFrame();
	return result;
}

static N_INLINE(void, rtladdzct_50204)(tcell44933* c) {
	nimfr("rtlAddZCT", "gc.nim")
	nimln(199, "gc.nim");
	addzct_48617((&gch_47044.Zct), c);
	popFrame();
}

static N_INLINE(void, asgnRefNoCycle)(void** dest, void* src) {
	nimfr("asgnRefNoCycle", "gc.nim")
	nimln(251, "gc.nim");
	{
		tcell44933* c;
		nimln(251, "gc.nim");
		nimln(251, "gc.nim");
		if (!!((src == NIM_NIL))) goto LA3;
		nimln(252, "gc.nim");
		c = usrtocell_48646(src);
		nimln(169, "gc.nim");
		(*c).Refcount += 8;
	}
	LA3: ;
	nimln(254, "gc.nim");
	{
		tcell44933* c;
		nimln(254, "gc.nim");
		nimln(254, "gc.nim");
		if (!!(((*dest) == NIM_NIL))) goto LA7;
		nimln(255, "gc.nim");
		c = usrtocell_48646((*dest));
		nimln(256, "gc.nim");
		{
			nimln(167, "gc.nim");
			(*c).Refcount -= 8;
			nimln(168, "gc.nim");
			if (!((NU32)((*c).Refcount) < (NU32)(8))) goto LA11;
			nimln(257, "gc.nim");
			rtladdzct_50204(c);
		}
		LA11: ;
	}
	LA7: ;
	nimln(258, "gc.nim");
	(*dest) = src;
	popFrame();
}

N_NIMCALL(NI64, nsuParseBiggestInt)(NimStringDesc* s) {
	NI64 result;
	NI l;
	nimfr("parseBiggestInt", "strutils.nim")
	result = 0;
	nimln(430, "strutils.nim");
	l = npuParseBiggestInt(s, (&result), 0);
	nimln(431, "strutils.nim");
	{
		NIM_BOOL LOC3;
		valueerror3249* e_95690;
		NimStringDesc* LOC7;
		nimln(431, "strutils.nim");
		LOC3 = 0;
		nimln(431, "strutils.nim");
		nimln(431, "strutils.nim");
		nimln(431, "strutils.nim");
		LOC3 = !((l == s->Sup.len));
		if (LOC3) goto LA4;
		nimln(431, "strutils.nim");
		LOC3 = (l == 0);
		LA4: ;
		if (!LOC3) goto LA5;
		e_95690 = 0;
		nimln(2149, "system.nim");
		e_95690 = (valueerror3249*) newObj((&NTI21601), sizeof(valueerror3249));
		(*e_95690).Sup.Sup.m_type = (&NTI3249);
		nimln(2150, "system.nim");
		nimln(432, "strutils.nim");
		LOC7 = 0;
		LOC7 = rawNewString(s->Sup.len + 17);
appendString(LOC7, ((NimStringDesc*) &TMP232));
appendString(LOC7, s);
		asgnRefNoCycle((void**) (&(*e_95690).Sup.message), LOC7);
		nimln(432, "strutils.nim");
		raiseException((Exception*)e_95690, "ValueError");
	}
	LA5: ;
	popFrame();
	return result;
}

N_NIMCALL(NF, nsuParseFloat)(NimStringDesc* s) {
	NF result;
	NI l;
	nimfr("parseFloat", "strutils.nim")
	result = 0;
	nimln(439, "strutils.nim");
	l = npuParseFloat(s, (&result), 0);
	nimln(440, "strutils.nim");
	{
		NIM_BOOL LOC3;
		valueerror3249* e_95723;
		NimStringDesc* LOC7;
		nimln(440, "strutils.nim");
		LOC3 = 0;
		nimln(440, "strutils.nim");
		nimln(440, "strutils.nim");
		nimln(440, "strutils.nim");
		LOC3 = !((l == s->Sup.len));
		if (LOC3) goto LA4;
		nimln(440, "strutils.nim");
		LOC3 = (l == 0);
		LA4: ;
		if (!LOC3) goto LA5;
		e_95723 = 0;
		nimln(2149, "system.nim");
		e_95723 = (valueerror3249*) newObj((&NTI21601), sizeof(valueerror3249));
		(*e_95723).Sup.Sup.m_type = (&NTI3249);
		nimln(2150, "system.nim");
		nimln(441, "strutils.nim");
		LOC7 = 0;
		LOC7 = rawNewString(s->Sup.len + 15);
appendString(LOC7, ((NimStringDesc*) &TMP234));
appendString(LOC7, s);
		asgnRefNoCycle((void**) (&(*e_95723).Sup.message), LOC7);
		nimln(441, "strutils.nim");
		raiseException((Exception*)e_95723, "ValueError");
	}
	LA5: ;
	popFrame();
	return result;
}

static N_INLINE(void, nimGCunrefNoCycle)(void* p) {
	tcell44933* c;
	nimfr("nimGCunrefNoCycle", "gc.nim")
	nimln(233, "gc.nim");
	c = usrtocell_48646(p);
	nimln(235, "gc.nim");
	{
		nimln(167, "gc.nim");
		(*c).Refcount -= 8;
		nimln(168, "gc.nim");
		if (!((NU32)((*c).Refcount) < (NU32)(8))) goto LA3;
		nimln(236, "gc.nim");
		rtladdzct_50204(c);
	}
	LA3: ;
	popFrame();
}

N_NOINLINE(void, invalidformatstring_98671)(void) {
	valueerror3249* e_98675;
	NimStringDesc* LOC1;
	nimfr("invalidFormatString", "strutils.nim")
	e_98675 = 0;
	nimln(2149, "system.nim");
	e_98675 = (valueerror3249*) newObj((&NTI21601), sizeof(valueerror3249));
	(*e_98675).Sup.Sup.m_type = (&NTI3249);
	nimln(2150, "system.nim");
	LOC1 = 0;
	LOC1 = (*e_98675).Sup.message; (*e_98675).Sup.message = copyStringRC1(((NimStringDesc*) &TMP238));
	if (LOC1) nimGCunrefNoCycle(LOC1);
	nimln(1264, "strutils.nim");
	raiseException((Exception*)e_98675, "ValueError");
	popFrame();
}

static N_INLINE(NI, chckRange)(NI i, NI a, NI b) {
	NI result;
	result = 0;
	{
		NIM_BOOL LOC3;
		LOC3 = 0;
		LOC3 = (a <= i);
		if (!(LOC3)) goto LA4;
		LOC3 = (i <= b);
		LA4: ;
		if (!LOC3) goto LA5;
		result = i;
		goto BeforeRet;
	}
	goto LA1;
	LA5: ;
	{
		raiseRangeError(((NI64) (i)));
	}
	LA1: ;
	BeforeRet: ;
	return result;
}

N_NIMCALL(NIM_CHAR, nsuToLowerChar)(NIM_CHAR c) {
	NIM_CHAR result;
	nimfr("toLower", "strutils.nim")
	result = 0;
	nimln(69, "strutils.nim");
	{
		NI TMP245;
		nimln(69, "strutils.nim");
		if (!(((NU8)(c)) >= ((NU8)(65)) && ((NU8)(c)) <= ((NU8)(90)))) goto LA3;
		nimln(70, "strutils.nim");
		nimln(70, "strutils.nim");
		nimln(70, "strutils.nim");
		nimln(70, "strutils.nim");
		TMP245 = addInt(((NI) (((NU8)(c)))), 32);
		result = ((NIM_CHAR) (((NI)chckRange((NI32)(TMP245), 0, 255))));
	}
	goto LA1;
	LA3: ;
	{
		nimln(72, "strutils.nim");
		result = c;
	}
	LA1: ;
	popFrame();
	return result;
}

N_NIMCALL(NI, nsuCmpIgnoreStyle)(NimStringDesc* a, NimStringDesc* b) {
	NI result;
	NI i;
	NI j;
	nimfr("cmpIgnoreStyle", "strutils.nim")
	result = 0;
	i = 0;
	j = 0;
	{
		while (1) {
			NIM_CHAR aa;
			NIM_CHAR bb;
			{
				while (1) {
					if (!((NU8)(a->data[i]) == (NU8)(95))) goto LA4;
					i += 1;
				} LA4: ;
			}
			{
				while (1) {
					if (!((NU8)(b->data[j]) == (NU8)(95))) goto LA6;
					j += 1;
				} LA6: ;
			}
			aa = nsuToLowerChar(a->data[i]);
			bb = nsuToLowerChar(b->data[j]);
			result = (NI32)(((NI) (((NU8)(aa)))) - ((NI) (((NU8)(bb)))));
			{
				NIM_BOOL LOC9;
				LOC9 = 0;
				LOC9 = !((result == 0));
				if (LOC9) goto LA10;
				LOC9 = ((NU8)(aa) == (NU8)(0));
				LA10: ;
				if (!LOC9) goto LA11;
				goto LA1;
			}
			LA11: ;
			i += 1;
			j += 1;
		}
	} LA1: ;
	popFrame();
	return result;
}

N_NIMCALL(NI, findnormalized_98638)(NimStringDesc* x, NimStringDesc** inarray, NI inarrayLen0) {
	NI result;
	NI i;
	nimfr("findNormalized", "strutils.nim")
	result = 0;
	nimln(1256, "strutils.nim");
	i = 0;
	{
		nimln(1257, "strutils.nim");
		while (1) {
			nimln(1257, "strutils.nim");
			nimln(1257, "strutils.nim");
			if (!(i < (inarrayLen0-1))) goto LA2;
			nimln(1258, "strutils.nim");
			{
				NI LOC5;
				nimln(1258, "strutils.nim");
				nimln(1258, "strutils.nim");
				if ((NU)(i) >= (NU)(inarrayLen0)) raiseIndexError();
				LOC5 = 0;
				LOC5 = nsuCmpIgnoreStyle(x, inarray[i]);
				if (!(LOC5 == 0)) goto LA6;
				nimln(1258, "strutils.nim");
				nimln(1258, "strutils.nim");
				result = i;
				goto BeforeRet;
			}
			LA6: ;
			nimln(1259, "strutils.nim");
			i = addInt(i, 2);
		} LA2: ;
	}
	nimln(1261, "strutils.nim");
	nimln(1261, "strutils.nim");
	result = -1;
	goto BeforeRet;
	BeforeRet: ;
	popFrame();
	return result;
}

N_NIMCALL(void, nsuAddf)(NimStringDesc** s, NimStringDesc* formatstr, NimStringDesc** a, NI aLen0) {
	NI i;
	NI num;
	nimfr("addf", "strutils.nim")
	nimln(1270, "strutils.nim");
	i = 0;
	nimln(1271, "strutils.nim");
	num = 0;
	{
		nimln(1272, "strutils.nim");
		while (1) {
			nimln(1272, "strutils.nim");
			nimln(1272, "strutils.nim");
			if (!(i < formatstr->Sup.len)) goto LA2;
			nimln(1273, "strutils.nim");
			{
				NI TMP237;
				nimln(1273, "strutils.nim");
				if ((NU)(i) > (NU)(formatstr->Sup.len)) raiseIndexError();
				if (!((NU8)(formatstr->data[i]) == (NU8)(36))) goto LA5;
				nimln(1274, "strutils.nim");
				nimln(1274, "strutils.nim");
				TMP237 = addInt(i, 1);
				if ((NU)((NI32)(TMP237)) > (NU)(formatstr->Sup.len)) raiseIndexError();
				switch (((NU8)(formatstr->data[(NI32)(TMP237)]))) {
				case 35:
				{
					nimln(1277, "strutils.nim");
					{
						nimln(1277, "strutils.nim");
						nimln(1277, "strutils.nim");
						if (!((NU32)((aLen0-1)) < (NU32)(num))) goto LA10;
						nimln(1277, "strutils.nim");
						invalidformatstring_98671();
					}
					LA10: ;
					nimln(1278, "strutils.nim");
					if ((NU)(num) >= (NU)(aLen0)) raiseIndexError();
					(*s) = resizeString((*s), a[num]->Sup.len + 0);
appendString((*s), a[num]);
					nimln(1279, "strutils.nim");
					i = addInt(i, 2);
					nimln(1280, "strutils.nim");
					num = addInt(num, 1);
				}
				break;
				case 36:
				{
					nimln(1282, "strutils.nim");
					(*s) = addChar((*s), 36);
					nimln(1283, "strutils.nim");
					i = addInt(i, 2);
				}
				break;
				case 49 ... 57:
				case 45:
				{
					NI j;
					NIM_BOOL negative;
					NI idx;
					nimln(1285, "strutils.nim");
					j = 0;
					nimln(1286, "strutils.nim");
					i = addInt(i, 1);
					nimln(1287, "strutils.nim");
					nimln(1287, "strutils.nim");
					if ((NU)(i) > (NU)(formatstr->Sup.len)) raiseIndexError();
					negative = ((NU8)(formatstr->data[i]) == (NU8)(45));
					nimln(1288, "strutils.nim");
					{
						if (!negative) goto LA16;
						nimln(1288, "strutils.nim");
						i = addInt(i, 1);
					}
					LA16: ;
					{
						nimln(1289, "strutils.nim");
						while (1) {
							NI TMP239;
							NI TMP240;
							NI TMP241;
							nimln(1289, "strutils.nim");
							if ((NU)(i) > (NU)(formatstr->Sup.len)) raiseIndexError();
							if (!(((NU8)(formatstr->data[i])) >= ((NU8)(48)) && ((NU8)(formatstr->data[i])) <= ((NU8)(57)))) goto LA19;
							nimln(1290, "strutils.nim");
							nimln(1290, "strutils.nim");
							nimln(1290, "strutils.nim");
							nimln(1290, "strutils.nim");
							TMP239 = mulInt(j, 10);
							nimln(1290, "strutils.nim");
							if ((NU)(i) > (NU)(formatstr->Sup.len)) raiseIndexError();
							TMP240 = addInt((NI32)(TMP239), ((NI) (((NU8)(formatstr->data[i])))));
							TMP241 = subInt((NI32)(TMP240), 48);
							j = (NI32)(TMP241);
							nimln(1291, "strutils.nim");
							i = addInt(i, 1);
						} LA19: ;
					}
					nimln(1292, "strutils.nim");
					nimln(1292, "strutils.nim");
					{
						NI TMP242;
						nimln(1292, "strutils.nim");
						if (!!(negative)) goto LA22;
						nimln(1292, "strutils.nim");
						TMP242 = subInt(j, 1);
						idx = (NI32)(TMP242);
					}
					goto LA20;
					LA22: ;
					{
						NI TMP243;
						nimln(1292, "strutils.nim");
						nimln(1292, "strutils.nim");
						TMP243 = subInt(aLen0, j);
						idx = (NI32)(TMP243);
					}
					LA20: ;
					nimln(1293, "strutils.nim");
					{
						nimln(1293, "strutils.nim");
						nimln(1293, "strutils.nim");
						if (!((NU32)((aLen0-1)) < (NU32)(idx))) goto LA27;
						nimln(1293, "strutils.nim");
						invalidformatstring_98671();
					}
					LA27: ;
					nimln(1294, "strutils.nim");
					if ((NU)(idx) >= (NU)(aLen0)) raiseIndexError();
					(*s) = resizeString((*s), a[idx]->Sup.len + 0);
appendString((*s), a[idx]);
				}
				break;
				case 123:
				{
					NI j;
					NI TMP244;
					NI x;
					NI TMP246;
					NI TMP247;
					NimStringDesc* LOC32;
					NI TMP249;
					nimln(1296, "strutils.nim");
					nimln(1296, "strutils.nim");
					TMP244 = addInt(i, 1);
					j = (NI32)(TMP244);
					{
						nimln(1297, "strutils.nim");
						while (1) {
							nimln(1297, "strutils.nim");
							nimln(1297, "strutils.nim");
							if ((NU)(j) > (NU)(formatstr->Sup.len)) raiseIndexError();
							if (!!((((NU8)(formatstr->data[j])) == ((NU8)(0)) || ((NU8)(formatstr->data[j])) == ((NU8)(125))))) goto LA31;
							nimln(1297, "strutils.nim");
							j = addInt(j, 1);
						} LA31: ;
					}
					nimln(1298, "strutils.nim");
					nimln(1298, "strutils.nim");
					nimln(1298, "strutils.nim");
					TMP246 = addInt(i, 2);
					nimln(1298, "strutils.nim");
					TMP247 = subInt(j, 1);
					LOC32 = 0;
					LOC32 = copyStrLast(formatstr, (NI32)(TMP246), (NI32)(TMP247));
					x = findnormalized_98638(LOC32, a, aLen0);
					nimln(1299, "strutils.nim");
					{
						NIM_BOOL LOC35;
						NI TMP248;
						nimln(1299, "strutils.nim");
						LOC35 = 0;
						nimln(1299, "strutils.nim");
						LOC35 = (0 <= x);
						if (!(LOC35)) goto LA36;
						nimln(1299, "strutils.nim");
						nimln(1299, "strutils.nim");
						LOC35 = (x < (aLen0-1));
						LA36: ;
						if (!LOC35) goto LA37;
						nimln(1299, "strutils.nim");
						nimln(1299, "strutils.nim");
						TMP248 = addInt(x, 1);
						if ((NU)((NI32)(TMP248)) >= (NU)(aLen0)) raiseIndexError();
						(*s) = resizeString((*s), a[(NI32)(TMP248)]->Sup.len + 0);
appendString((*s), a[(NI32)(TMP248)]);
					}
					goto LA33;
					LA37: ;
					{
						nimln(1300, "strutils.nim");
						invalidformatstring_98671();
					}
					LA33: ;
					nimln(1301, "strutils.nim");
					nimln(1301, "strutils.nim");
					TMP249 = addInt(j, 1);
					i = (NI32)(TMP249);
				}
				break;
				case 97 ... 122:
				case 65 ... 90:
				case 128 ... 255:
				case 95:
				{
					NI j;
					NI TMP250;
					NI x;
					NI TMP251;
					NI TMP252;
					NimStringDesc* LOC43;
					nimln(1303, "strutils.nim");
					nimln(1303, "strutils.nim");
					TMP250 = addInt(i, 1);
					j = (NI32)(TMP250);
					{
						nimln(1304, "strutils.nim");
						while (1) {
							nimln(1304, "strutils.nim");
							if ((NU)(j) > (NU)(formatstr->Sup.len)) raiseIndexError();
							if (!(((NU8)(formatstr->data[j])) >= ((NU8)(97)) && ((NU8)(formatstr->data[j])) <= ((NU8)(122)) || ((NU8)(formatstr->data[j])) >= ((NU8)(65)) && ((NU8)(formatstr->data[j])) <= ((NU8)(90)) || ((NU8)(formatstr->data[j])) >= ((NU8)(48)) && ((NU8)(formatstr->data[j])) <= ((NU8)(57)) || ((NU8)(formatstr->data[j])) >= ((NU8)(128)) && ((NU8)(formatstr->data[j])) <= ((NU8)(255)) || ((NU8)(formatstr->data[j])) == ((NU8)(95)))) goto LA42;
							nimln(1304, "strutils.nim");
							j = addInt(j, 1);
						} LA42: ;
					}
					nimln(1305, "strutils.nim");
					nimln(1305, "strutils.nim");
					nimln(1305, "strutils.nim");
					TMP251 = addInt(i, 1);
					nimln(1305, "strutils.nim");
					TMP252 = subInt(j, 1);
					LOC43 = 0;
					LOC43 = copyStrLast(formatstr, (NI32)(TMP251), (NI32)(TMP252));
					x = findnormalized_98638(LOC43, a, aLen0);
					nimln(1306, "strutils.nim");
					{
						NIM_BOOL LOC46;
						NI TMP253;
						nimln(1306, "strutils.nim");
						LOC46 = 0;
						nimln(1306, "strutils.nim");
						LOC46 = (0 <= x);
						if (!(LOC46)) goto LA47;
						nimln(1306, "strutils.nim");
						nimln(1306, "strutils.nim");
						LOC46 = (x < (aLen0-1));
						LA47: ;
						if (!LOC46) goto LA48;
						nimln(1306, "strutils.nim");
						nimln(1306, "strutils.nim");
						TMP253 = addInt(x, 1);
						if ((NU)((NI32)(TMP253)) >= (NU)(aLen0)) raiseIndexError();
						(*s) = resizeString((*s), a[(NI32)(TMP253)]->Sup.len + 0);
appendString((*s), a[(NI32)(TMP253)]);
					}
					goto LA44;
					LA48: ;
					{
						nimln(1307, "strutils.nim");
						invalidformatstring_98671();
					}
					LA44: ;
					nimln(1308, "strutils.nim");
					i = j;
				}
				break;
				default:
				{
					nimln(1310, "strutils.nim");
					invalidformatstring_98671();
				}
				break;
				}
			}
			goto LA3;
			LA5: ;
			{
				nimln(1312, "strutils.nim");
				if ((NU)(i) > (NU)(formatstr->Sup.len)) raiseIndexError();
				(*s) = addChar((*s), formatstr->data[i]);
				nimln(1313, "strutils.nim");
				i = addInt(i, 1);
			}
			LA3: ;
		} LA2: ;
	}
	popFrame();
}

N_NIMCALL(NimStringDesc*, nsuFormatOpenArray)(NimStringDesc* formatstr, NimStringDesc** a, NI aLen0) {
	NimStringDesc* result;
	NI TMP236;
	nimfr("%", "strutils.nim")
	result = 0;
	nimln(1357, "strutils.nim");
	nimln(1357, "strutils.nim");
	nimln(1357, "strutils.nim");
	nimln(1357, "strutils.nim");
	nimln(1357, "strutils.nim");
	nimln(1357, "strutils.nim");
	TMP236 = addInt(formatstr->Sup.len, (NI)((NU32)(aLen0) << (NU32)(4)));
	result = rawNewString((NI32)(TMP236));
	nimln(1358, "strutils.nim");
	nsuAddf((&result), formatstr, a, aLen0);
	popFrame();
	return result;
}

N_NIMCALL(NI, nsuFindCharSet)(NimStringDesc* s, TY75869 chars, NI start) {
	NI result;
	nimfr("find", "strutils.nim")
	result = 0;
	{
		NI i_96947;
		NI HEX3Atmp_96962;
		NI TMP267;
		NI res_96965;
		i_96947 = 0;
		HEX3Atmp_96962 = 0;
		nimln(787, "strutils.nim");
		nimln(787, "strutils.nim");
		nimln(787, "strutils.nim");
		TMP267 = subInt(s->Sup.len, 1);
		HEX3Atmp_96962 = (NI32)(TMP267);
		nimln(1576, "system.nim");
		res_96965 = start;
		{
			nimln(1577, "system.nim");
			while (1) {
				nimln(1577, "system.nim");
				if (!(res_96965 <= HEX3Atmp_96962)) goto LA3;
				nimln(1576, "system.nim");
				i_96947 = res_96965;
				nimln(788, "strutils.nim");
				{
					nimln(788, "strutils.nim");
					if ((NU)(i_96947) > (NU)(s->Sup.len)) raiseIndexError();
					if (!((chars[((NU8)(s->data[i_96947]))/8] &(1<<(((NU8)(s->data[i_96947]))%8)))!=0)) goto LA6;
					nimln(788, "strutils.nim");
					nimln(788, "strutils.nim");
					result = i_96947;
					goto BeforeRet;
				}
				LA6: ;
				nimln(1579, "system.nim");
				res_96965 = addInt(res_96965, 1);
			} LA3: ;
		}
	}
	nimln(789, "strutils.nim");
	nimln(789, "strutils.nim");
	result = -1;
	goto BeforeRet;
	BeforeRet: ;
	popFrame();
	return result;
}

N_NIMCALL(NIM_BOOL, contains_97267)(NimStringDesc* s, TY75869 chars) {
	NIM_BOOL result;
	NI LOC1;
	nimfr("contains", "strutils.nim")
	result = 0;
	nimln(867, "strutils.nim");
	nimln(867, "strutils.nim");
	nimln(867, "strutils.nim");
	nimln(867, "strutils.nim");
	LOC1 = 0;
	LOC1 = nsuFindCharSet(s, chars, 0);
	result = (0 <= LOC1);
	goto BeforeRet;
	BeforeRet: ;
	popFrame();
	return result;
}

static N_INLINE(NI64, addInt64)(NI64 a, NI64 b) {
	NI64 result;
	result = 0;
	result = (NI64)((NU64)(a) + (NU64)(b));
	{
		NIM_BOOL LOC3;
		LOC3 = 0;
		LOC3 = (IL64(0) <= (NI64)(result ^ a));
		if (LOC3) goto LA4;
		LOC3 = (IL64(0) <= (NI64)(result ^ b));
		LA4: ;
		if (!LOC3) goto LA5;
		goto BeforeRet;
	}
	LA5: ;
	raiseOverflow();
	BeforeRet: ;
	return result;
}

N_NIMCALL(NimStringDesc*, nsuToHex)(NI64 x, NI len) {
	NimStringDesc* result;
	NI64 shift;
	nimfr("toHex", "strutils.nim")
	result = 0;
	shift = 0;
	nimln(399, "strutils.nim");
	nimln(399, "strutils.nim");
	result = mnewString(len);
	{
		NI j_95588;
		NI HEX3Atmp_95592;
		NI TMP323;
		NI res_95595;
		j_95588 = 0;
		HEX3Atmp_95592 = 0;
		nimln(400, "strutils.nim");
		nimln(400, "strutils.nim");
		TMP323 = subInt(len, 1);
		HEX3Atmp_95592 = (NI32)(TMP323);
		nimln(1560, "system.nim");
		res_95595 = HEX3Atmp_95592;
		{
			nimln(1561, "system.nim");
			while (1) {
				NI64 TMP325;
				nimln(1561, "system.nim");
				if (!(0 <= res_95595)) goto LA3;
				nimln(1560, "system.nim");
				j_95588 = res_95595;
				nimln(401, "strutils.nim");
				if ((NU)(j_95588) > (NU)(result->Sup.len)) raiseIndexError();
				nimln(401, "strutils.nim");
				nimln(401, "strutils.nim");
				nimln(401, "strutils.nim");
				if ((NU)((NI32)(((NI32)(NU32)(NU64)((NI64)((NU64)(x) >> (NU64)(shift)))) & ((NI32) 15))) > (NU)(((NimStringDesc*) &TMP324)->Sup.len)) raiseIndexError();
				result->data[j_95588] = ((NimStringDesc*) &TMP324)->data[(NI32)(((NI32)(NU32)(NU64)((NI64)((NU64)(x) >> (NU64)(shift)))) & ((NI32) 15))];
				nimln(402, "strutils.nim");
				nimln(402, "strutils.nim");
				TMP325 = addInt64(shift, IL64(4));
				shift = (NI64)(TMP325);
				nimln(1563, "system.nim");
				res_95595 = subInt(res_95595, 1);
			} LA3: ;
		}
	}
	popFrame();
	return result;
}

static N_INLINE(void, appendChar)(NimStringDesc* dest, NIM_CHAR c) {
	(*dest).data[((*dest).Sup.len)- 0] = c;
	(*dest).data[((NI32)((*dest).Sup.len + 1))- 0] = 0;
	(*dest).Sup.len += 1;
}

N_NIMCALL(NimStringDesc*, nsuIntToStr)(NI x, NI minchars) {
	NimStringDesc* result;
	nimfr("intToStr", "strutils.nim")
	result = 0;
	nimln(410, "strutils.nim");
	nimln(410, "strutils.nim");
	nimln(410, "strutils.nim");
	if (x == (-2147483647 -1)) raiseOverflow();
	result = nimIntToStr((x > 0? (x) : -(x)));
	{
		NI i_95626;
		NI HEX3Atmp_95629;
		NI TMP555;
		NI res_95632;
		i_95626 = 0;
		HEX3Atmp_95629 = 0;
		nimln(411, "strutils.nim");
		nimln(411, "strutils.nim");
		nimln(411, "strutils.nim");
		TMP555 = subInt(minchars, result->Sup.len);
		HEX3Atmp_95629 = (NI32)(TMP555);
		nimln(1576, "system.nim");
		res_95632 = 1;
		{
			nimln(1577, "system.nim");
			while (1) {
				NimStringDesc* LOC4;
				nimln(1577, "system.nim");
				if (!(res_95632 <= HEX3Atmp_95629)) goto LA3;
				nimln(1576, "system.nim");
				i_95626 = res_95632;
				nimln(412, "strutils.nim");
				nimln(412, "strutils.nim");
				LOC4 = 0;
				LOC4 = rawNewString(result->Sup.len + 1);
appendChar(LOC4, 48);
appendString(LOC4, result);
				result = LOC4;
				nimln(1579, "system.nim");
				res_95632 = addInt(res_95632, 1);
			} LA3: ;
		}
	}
	nimln(413, "strutils.nim");
	{
		NimStringDesc* LOC9;
		nimln(413, "strutils.nim");
		if (!(x < 0)) goto LA7;
		nimln(414, "strutils.nim");
		nimln(414, "strutils.nim");
		LOC9 = 0;
		LOC9 = rawNewString(result->Sup.len + 1);
appendChar(LOC9, 45);
appendString(LOC9, result);
		result = LOC9;
	}
	LA7: ;
	popFrame();
	return result;
}
NIM_EXTERNC N_NOINLINE(void, stdlib_strutilsInit)(void) {
	nimfr("strutils", "strutils.nim")
	popFrame();
}

NIM_EXTERNC N_NOINLINE(void, stdlib_strutilsDatInit)(void) {
}
