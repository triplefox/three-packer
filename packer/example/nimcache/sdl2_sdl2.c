/* Generated by Nim Compiler v0.10.2 */
/*   (c) 2014 Andreas Rumpf */
/* The generated code is subject to the original license. */
/* Compiled for: Windows, i386, gcc */
/* Command for C compiler:
   gcc.exe -c  -w  -IC:\Nim\lib -o c:\dropbox\2015\nim\packer\example\nimcache\sdl2_sdl2.o c:\dropbox\2015\nim\packer\example\nimcache\sdl2_sdl2.c */
#define NIM_INTBITS 32
#include "nimbase.h"
typedef struct TGenericSeq TGenericSeq;
typedef struct NimStringDesc NimStringDesc;
typedef struct rendererptrHEX3Aobjecttype132578 rendererptrHEX3Aobjecttype132578;
typedef struct rect132277 rect132277;
typedef struct surface132715 surface132715;
typedef struct pixelformat132709 pixelformat132709;
typedef struct textureptrHEX3Aobjecttype132579 textureptrHEX3Aobjecttype132579;
typedef struct blitmapptrHEX3Aobjecttype132757 blitmapptrHEX3Aobjecttype132757;
typedef struct TNimType TNimType;
typedef struct TNimNode TNimNode;
typedef struct palette132707 palette132707;
typedef struct color132705 color132705;
struct  TGenericSeq  {
NI len;
NI reserved;
};
struct  NimStringDesc  {
  TGenericSeq Sup;
NIM_CHAR data[SEQ_DECL_SIZE];
};
typedef N_CDECL_PTR(NI32, TY142006) (rendererptrHEX3Aobjecttype132578* renderer, rect132277* rect);
typedef N_CDECL_PTR(NI32, TY141981) (rendererptrHEX3Aobjecttype132578* renderer, rect132277* rect);
typedef N_CDECL_PTR(NI32, TY141945) (rendererptrHEX3Aobjecttype132578* renderer, int x, int y);
typedef N_CDECL_PTR(NI32, TY141433) (rendererptrHEX3Aobjecttype132578* renderer, NU8 r, NU8 g, NU8 b, NU8 a);
typedef N_CDECL_PTR(rendererptrHEX3Aobjecttype132578*, TY141757) (surface132715* surface);
typedef N_CDECL_PTR(void, TY141475) (rendererptrHEX3Aobjecttype132578* renderer);
typedef N_CDECL_PTR(pixelformat132709*, TY143141) (NU32 pixelformat);
typedef N_CDECL_PTR(surface132715*, TY142099) (int flags, int width, int height, int depth, NU32 rmask, NU32 gmask, NU32 bmask, NU32 amask);
typedef N_CDECL_PTR(void, TY143151) (pixelformat132709* format);
typedef N_CDECL_PTR(NU32, TY143131) (int bpp, NU32 rmask, NU32 gmask, NU32 bmask, NU32 amask);
typedef N_CDECL_PTR(textureptrHEX3Aobjecttype132579*, TY141786) (rendererptrHEX3Aobjecttype132578* renderer, surface132715* surface);
typedef N_CDECL_PTR(NI32, TY142023) (rendererptrHEX3Aobjecttype132578* renderer, textureptrHEX3Aobjecttype132579* texture, rect132277* srcrect, rect132277* dstrect);
typedef N_CDECL_PTR(void, TY141469) (textureptrHEX3Aobjecttype132579* texture);
struct rect132277 {
int Field0;
int Field1;
int Field2;
int Field3;
};
struct  surface132715  {
NU32 Flags;
pixelformat132709* Format;
NI32 W;
NI32 H;
NI32 Pitch;
void* Pixels;
void* Userdata;
NI32 Locked;
void* Lockdata;
rect132277 Cliprect;
blitmapptrHEX3Aobjecttype132757* Map;
int Refcount;
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
struct  TNimNode  {
NU8 kind;
NI offset;
TNimType* typ;
NCSTRING name;
NI len;
TNimNode** sons;
};
typedef NU8 TY132739[2];
struct  pixelformat132709  {
NU32 Format;
palette132707* Palette;
NU8 Bitsperpixel;
NU8 Bytesperpixel;
TY132739 Padding;
NU32 Rmask;
NU32 Gmask;
NU32 Bmask;
NU32 Amask;
NU8 Rloss;
NU8 Gloss;
NU8 Bloss;
NU8 Aloss;
NU8 Rshift;
NU8 Gshift;
NU8 Bshift;
NU8 Ashift;
int Refcount;
pixelformat132709* Next;
};
struct  palette132707  {
int Ncolors;
color132705* Colors;
NU32 Version;
int Refcount;
};
struct color132705 {
NU8 Field0;
NU8 Field1;
NU8 Field2;
NU8 Field3;
};
struct  blitmapptrHEX3Aobjecttype132757  {
char dummy;
};
typedef N_CDECL_PTR(surface132715*, TY142292) (surface132715* src, NU32 pixelformat, NU32 flags);
typedef N_CDECL_PTR(void, TY142126) (surface132715* surface);
typedef N_CDECL_PTR(NCSTRING, TY143102) (void);
typedef N_CDECL_PTR(NCSTRING, TY143112) (NU32 format);
struct  rendererptrHEX3Aobjecttype132578  {
char dummy;
};
struct  textureptrHEX3Aobjecttype132579  {
char dummy;
};
N_NIMCALL(void*, nimLoadLibrary)(NimStringDesc* path);
N_NOINLINE(void, nimLoadLibraryError)(NimStringDesc* path);
N_NIMCALL(void*, nimGetProcAddr)(void* lib, NCSTRING name);
static N_INLINE(void, nimFrame)(TFrame* s);
N_NOINLINE(void, stackoverflow_18801)(void);
static N_INLINE(void, popFrame)(void);
STRING_LITERAL(TMP610, "SDL2.dll", 8);
STRING_LITERAL(TMP611, "SDL2.dll", 8);
static void* TMP609;
TY142006 Dl_142005;
TY141981 Dl_141980;
TY141945 Dl_141944;
TY141433 Dl_141432;
TY141757 Dl_141756;
TY141475 Dl_141474;
TY143141 Dl_143140;
TY142099 Dl_142098;
TY143151 Dl_143150;
TY143131 Dl_143130;
TY141786 Dl_141785;
TY142023 Dl_142022;
TY141469 Dl_141468;
TNimType NTI132715; /* Surface */
extern TNimType NTI124; /* uint32 */
TNimType NTI132709; /* PixelFormat */
TNimType NTI132707; /* Palette */
extern TNimType NTI5611; /* cint */
TNimType NTI132705; /* Color */
extern TNimType NTI120; /* uint8 */
TNimType NTI132730; /* ptr Color */
TNimType NTI132735; /* ptr Palette */
TNimType NTI132739; /* array[0..1, uint8] */
TNimType NTI143143; /* ptr PixelFormat */
extern TNimType NTI114; /* int32 */
extern TNimType NTI153; /* pointer */
TNimType NTI132277; /* Rect */
TNimType NTI132757; /* BlitMapPtr:ObjectType */
TNimType NTI132711; /* BlitMapPtr */
TNimType NTI132713; /* SurfacePtr */
TY142292 Dl_142291;
TY142126 Dl_142125;
TY143102 Dl_143101;
TY143112 Dl_143111;
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
NIM_EXTERNC N_NOINLINE(void, sdl2_sdl2Init)(void) {
	nimfr("sdl2", "sdl2.nim")
	popFrame();
}

NIM_EXTERNC N_NOINLINE(void, sdl2_sdl2DatInit)(void) {
static TNimNode* TMP648[12];
static TNimNode* TMP649[19];
static TNimNode* TMP650[4];
static TNimNode* TMP651[4];
static TNimNode* TMP652[4];
static TNimNode TMP347[49];
NTI132715.size = sizeof(surface132715);
NTI132715.kind = 18;
NTI132715.base = 0;
NTI132715.flags = 3;
TMP648[0] = &TMP347[1];
TMP347[1].kind = 1;
TMP347[1].offset = offsetof(surface132715, Flags);
TMP347[1].typ = (&NTI124);
TMP347[1].name = "flags";
TMP648[1] = &TMP347[2];
NTI132709.size = sizeof(pixelformat132709);
NTI132709.kind = 18;
NTI132709.base = 0;
NTI132709.flags = 3;
TMP649[0] = &TMP347[4];
TMP347[4].kind = 1;
TMP347[4].offset = offsetof(pixelformat132709, Format);
TMP347[4].typ = (&NTI124);
TMP347[4].name = "format";
TMP649[1] = &TMP347[5];
NTI132707.size = sizeof(palette132707);
NTI132707.kind = 18;
NTI132707.base = 0;
NTI132707.flags = 3;
TMP650[0] = &TMP347[7];
TMP347[7].kind = 1;
TMP347[7].offset = offsetof(palette132707, Ncolors);
TMP347[7].typ = (&NTI5611);
TMP347[7].name = "ncolors";
TMP650[1] = &TMP347[8];
NTI132705.size = sizeof(color132705);
NTI132705.kind = 18;
NTI132705.base = 0;
NTI132705.flags = 3;
TMP651[0] = &TMP347[10];
TMP347[10].kind = 1;
TMP347[10].offset = offsetof(color132705, Field0);
TMP347[10].typ = (&NTI120);
TMP347[10].name = "Field0";
TMP651[1] = &TMP347[11];
TMP347[11].kind = 1;
TMP347[11].offset = offsetof(color132705, Field1);
TMP347[11].typ = (&NTI120);
TMP347[11].name = "Field1";
TMP651[2] = &TMP347[12];
TMP347[12].kind = 1;
TMP347[12].offset = offsetof(color132705, Field2);
TMP347[12].typ = (&NTI120);
TMP347[12].name = "Field2";
TMP651[3] = &TMP347[13];
TMP347[13].kind = 1;
TMP347[13].offset = offsetof(color132705, Field3);
TMP347[13].typ = (&NTI120);
TMP347[13].name = "Field3";
TMP347[9].len = 4; TMP347[9].kind = 2; TMP347[9].sons = &TMP651[0];
NTI132705.node = &TMP347[9];
NTI132730.size = sizeof(color132705*);
NTI132730.kind = 21;
NTI132730.base = (&NTI132705);
NTI132730.flags = 3;
TMP347[8].kind = 1;
TMP347[8].offset = offsetof(palette132707, Colors);
TMP347[8].typ = (&NTI132730);
TMP347[8].name = "colors";
TMP650[2] = &TMP347[14];
TMP347[14].kind = 1;
TMP347[14].offset = offsetof(palette132707, Version);
TMP347[14].typ = (&NTI124);
TMP347[14].name = "version";
TMP650[3] = &TMP347[15];
TMP347[15].kind = 1;
TMP347[15].offset = offsetof(palette132707, Refcount);
TMP347[15].typ = (&NTI5611);
TMP347[15].name = "refcount";
TMP347[6].len = 4; TMP347[6].kind = 2; TMP347[6].sons = &TMP650[0];
NTI132707.node = &TMP347[6];
NTI132735.size = sizeof(palette132707*);
NTI132735.kind = 21;
NTI132735.base = (&NTI132707);
NTI132735.flags = 3;
TMP347[5].kind = 1;
TMP347[5].offset = offsetof(pixelformat132709, Palette);
TMP347[5].typ = (&NTI132735);
TMP347[5].name = "palette";
TMP649[2] = &TMP347[16];
TMP347[16].kind = 1;
TMP347[16].offset = offsetof(pixelformat132709, Bitsperpixel);
TMP347[16].typ = (&NTI120);
TMP347[16].name = "BitsPerPixel";
TMP649[3] = &TMP347[17];
TMP347[17].kind = 1;
TMP347[17].offset = offsetof(pixelformat132709, Bytesperpixel);
TMP347[17].typ = (&NTI120);
TMP347[17].name = "BytesPerPixel";
TMP649[4] = &TMP347[18];
NTI132739.size = sizeof(TY132739);
NTI132739.kind = 16;
NTI132739.base = (&NTI120);
NTI132739.flags = 3;
TMP347[18].kind = 1;
TMP347[18].offset = offsetof(pixelformat132709, Padding);
TMP347[18].typ = (&NTI132739);
TMP347[18].name = "padding";
TMP649[5] = &TMP347[19];
TMP347[19].kind = 1;
TMP347[19].offset = offsetof(pixelformat132709, Rmask);
TMP347[19].typ = (&NTI124);
TMP347[19].name = "Rmask";
TMP649[6] = &TMP347[20];
TMP347[20].kind = 1;
TMP347[20].offset = offsetof(pixelformat132709, Gmask);
TMP347[20].typ = (&NTI124);
TMP347[20].name = "Gmask";
TMP649[7] = &TMP347[21];
TMP347[21].kind = 1;
TMP347[21].offset = offsetof(pixelformat132709, Bmask);
TMP347[21].typ = (&NTI124);
TMP347[21].name = "Bmask";
TMP649[8] = &TMP347[22];
TMP347[22].kind = 1;
TMP347[22].offset = offsetof(pixelformat132709, Amask);
TMP347[22].typ = (&NTI124);
TMP347[22].name = "Amask";
TMP649[9] = &TMP347[23];
TMP347[23].kind = 1;
TMP347[23].offset = offsetof(pixelformat132709, Rloss);
TMP347[23].typ = (&NTI120);
TMP347[23].name = "Rloss";
TMP649[10] = &TMP347[24];
TMP347[24].kind = 1;
TMP347[24].offset = offsetof(pixelformat132709, Gloss);
TMP347[24].typ = (&NTI120);
TMP347[24].name = "Gloss";
TMP649[11] = &TMP347[25];
TMP347[25].kind = 1;
TMP347[25].offset = offsetof(pixelformat132709, Bloss);
TMP347[25].typ = (&NTI120);
TMP347[25].name = "Bloss";
TMP649[12] = &TMP347[26];
TMP347[26].kind = 1;
TMP347[26].offset = offsetof(pixelformat132709, Aloss);
TMP347[26].typ = (&NTI120);
TMP347[26].name = "Aloss";
TMP649[13] = &TMP347[27];
TMP347[27].kind = 1;
TMP347[27].offset = offsetof(pixelformat132709, Rshift);
TMP347[27].typ = (&NTI120);
TMP347[27].name = "Rshift";
TMP649[14] = &TMP347[28];
TMP347[28].kind = 1;
TMP347[28].offset = offsetof(pixelformat132709, Gshift);
TMP347[28].typ = (&NTI120);
TMP347[28].name = "Gshift";
TMP649[15] = &TMP347[29];
TMP347[29].kind = 1;
TMP347[29].offset = offsetof(pixelformat132709, Bshift);
TMP347[29].typ = (&NTI120);
TMP347[29].name = "Bshift";
TMP649[16] = &TMP347[30];
TMP347[30].kind = 1;
TMP347[30].offset = offsetof(pixelformat132709, Ashift);
TMP347[30].typ = (&NTI120);
TMP347[30].name = "Ashift";
TMP649[17] = &TMP347[31];
TMP347[31].kind = 1;
TMP347[31].offset = offsetof(pixelformat132709, Refcount);
TMP347[31].typ = (&NTI5611);
TMP347[31].name = "refcount";
TMP649[18] = &TMP347[32];
TMP347[32].kind = 1;
TMP347[32].offset = offsetof(pixelformat132709, Next);
TMP347[32].typ = (&NTI143143);
TMP347[32].name = "next";
TMP347[3].len = 19; TMP347[3].kind = 2; TMP347[3].sons = &TMP649[0];
NTI132709.node = &TMP347[3];
NTI143143.size = sizeof(pixelformat132709*);
NTI143143.kind = 21;
NTI143143.base = (&NTI132709);
NTI143143.flags = 3;
TMP347[2].kind = 1;
TMP347[2].offset = offsetof(surface132715, Format);
TMP347[2].typ = (&NTI143143);
TMP347[2].name = "format";
TMP648[2] = &TMP347[33];
TMP347[33].kind = 1;
TMP347[33].offset = offsetof(surface132715, W);
TMP347[33].typ = (&NTI114);
TMP347[33].name = "w";
TMP648[3] = &TMP347[34];
TMP347[34].kind = 1;
TMP347[34].offset = offsetof(surface132715, H);
TMP347[34].typ = (&NTI114);
TMP347[34].name = "h";
TMP648[4] = &TMP347[35];
TMP347[35].kind = 1;
TMP347[35].offset = offsetof(surface132715, Pitch);
TMP347[35].typ = (&NTI114);
TMP347[35].name = "pitch";
TMP648[5] = &TMP347[36];
TMP347[36].kind = 1;
TMP347[36].offset = offsetof(surface132715, Pixels);
TMP347[36].typ = (&NTI153);
TMP347[36].name = "pixels";
TMP648[6] = &TMP347[37];
TMP347[37].kind = 1;
TMP347[37].offset = offsetof(surface132715, Userdata);
TMP347[37].typ = (&NTI153);
TMP347[37].name = "userdata";
TMP648[7] = &TMP347[38];
TMP347[38].kind = 1;
TMP347[38].offset = offsetof(surface132715, Locked);
TMP347[38].typ = (&NTI114);
TMP347[38].name = "locked";
TMP648[8] = &TMP347[39];
TMP347[39].kind = 1;
TMP347[39].offset = offsetof(surface132715, Lockdata);
TMP347[39].typ = (&NTI153);
TMP347[39].name = "lock_data";
TMP648[9] = &TMP347[40];
NTI132277.size = sizeof(rect132277);
NTI132277.kind = 18;
NTI132277.base = 0;
NTI132277.flags = 3;
TMP652[0] = &TMP347[42];
TMP347[42].kind = 1;
TMP347[42].offset = offsetof(rect132277, Field0);
TMP347[42].typ = (&NTI5611);
TMP347[42].name = "Field0";
TMP652[1] = &TMP347[43];
TMP347[43].kind = 1;
TMP347[43].offset = offsetof(rect132277, Field1);
TMP347[43].typ = (&NTI5611);
TMP347[43].name = "Field1";
TMP652[2] = &TMP347[44];
TMP347[44].kind = 1;
TMP347[44].offset = offsetof(rect132277, Field2);
TMP347[44].typ = (&NTI5611);
TMP347[44].name = "Field2";
TMP652[3] = &TMP347[45];
TMP347[45].kind = 1;
TMP347[45].offset = offsetof(rect132277, Field3);
TMP347[45].typ = (&NTI5611);
TMP347[45].name = "Field3";
TMP347[41].len = 4; TMP347[41].kind = 2; TMP347[41].sons = &TMP652[0];
NTI132277.node = &TMP347[41];
TMP347[40].kind = 1;
TMP347[40].offset = offsetof(surface132715, Cliprect);
TMP347[40].typ = (&NTI132277);
TMP347[40].name = "clip_rect";
TMP648[10] = &TMP347[46];
NTI132757.size = sizeof(blitmapptrHEX3Aobjecttype132757);
NTI132757.kind = 18;
NTI132757.base = 0;
NTI132757.flags = 3;
TMP347[47].len = 0; TMP347[47].kind = 2;
NTI132757.node = &TMP347[47];
NTI132711.size = sizeof(blitmapptrHEX3Aobjecttype132757*);
NTI132711.kind = 21;
NTI132711.base = (&NTI132757);
NTI132711.flags = 3;
TMP347[46].kind = 1;
TMP347[46].offset = offsetof(surface132715, Map);
TMP347[46].typ = (&NTI132711);
TMP347[46].name = "map";
TMP648[11] = &TMP347[48];
TMP347[48].kind = 1;
TMP347[48].offset = offsetof(surface132715, Refcount);
TMP347[48].typ = (&NTI5611);
TMP347[48].name = "refcount";
TMP347[0].len = 12; TMP347[0].kind = 2; TMP347[0].sons = &TMP648[0];
NTI132715.node = &TMP347[0];
NTI132713.size = sizeof(surface132715*);
NTI132713.kind = 21;
NTI132713.base = (&NTI132715);
NTI132713.flags = 3;
if (!((TMP609 = nimLoadLibrary((NimStringDesc*) &TMP610))
)) nimLoadLibraryError((NimStringDesc*) &TMP611);
	Dl_142005 = (TY142006) nimGetProcAddr(TMP609, "SDL_RenderFillRect");
	Dl_141980 = (TY141981) nimGetProcAddr(TMP609, "SDL_RenderDrawRect");
	Dl_141944 = (TY141945) nimGetProcAddr(TMP609, "SDL_RenderDrawPoint");
	Dl_141432 = (TY141433) nimGetProcAddr(TMP609, "SDL_SetRenderDrawColor");
	Dl_141756 = (TY141757) nimGetProcAddr(TMP609, "SDL_CreateSoftwareRenderer");
	Dl_141474 = (TY141475) nimGetProcAddr(TMP609, "SDL_DestroyRenderer");
	Dl_143140 = (TY143141) nimGetProcAddr(TMP609, "SDL_AllocFormat");
	Dl_142098 = (TY142099) nimGetProcAddr(TMP609, "SDL_CreateRGBSurface");
	Dl_143150 = (TY143151) nimGetProcAddr(TMP609, "SDL_FreeFormat");
	Dl_143130 = (TY143131) nimGetProcAddr(TMP609, "SDL_MasksToPixelFormatEnum");
	Dl_141785 = (TY141786) nimGetProcAddr(TMP609, "SDL_CreateTextureFromSurface");
	Dl_142022 = (TY142023) nimGetProcAddr(TMP609, "SDL_RenderCopy");
	Dl_141468 = (TY141469) nimGetProcAddr(TMP609, "SDL_DestroyTexture");
	Dl_142291 = (TY142292) nimGetProcAddr(TMP609, "SDL_ConvertSurfaceFormat");
	Dl_142125 = (TY142126) nimGetProcAddr(TMP609, "SDL_FreeSurface");
	Dl_143101 = (TY143102) nimGetProcAddr(TMP609, "SDL_GetError");
	Dl_143111 = (TY143112) nimGetProcAddr(TMP609, "SDL_GetPixelFormatName");
}
