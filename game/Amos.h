#ifndef D_AMOS_H_D
#define D_AMOS_H_D

#include <vector>
#include <Engine2d/Core.h>
#include <Engine2d/Gfx.h>

#include "amos_types.h"

using namespace std;
using namespace Gfx;

//#define XSCRN(A)	(((A)-112)*2)
//#define YSCRN(A)	(((A)-42)*2)
//#define XHARD(A)	(((A)+112)/2)
//#define YHARD(A)	(((A)+42)/2)

#define	XBASE 130
#define YBASE 40

#define XSCRN(A)	(((A)-XBASE)*2)
#define YSCRN(A)	(((A)-YBASE)*2)
#define XHARD(A)	((A)/2+XBASE)
#define YHARD(A)	((A)/2+YBASE)

#define NOPARI	999888777

#define LOWRES	0x0000
#define HIRES		0x8000
#define LACED		0x0004


#undef  __CR_FUNC__
#ifdef  __GNUC__	/* GCC */
#define __CR_FUNC__ __PRETTY_FUNCTION__
#else					/* ANSI C */
#define __CR_FUNC__ __func__
#endif

#undef  __CR_FILE__
#define __CR_FILE__ __FILE__

#undef  __CR_LINE__
#define __CR_LINE__ __LINE__

//#define LOG(TEXT) {cout << toString(__CR_LINE__) << "(" << __CR_FUNC__ << ")" << TEXT << endl; cout.flush(); }
#define LOG(TEXT)

template<typename T>
void clip(T &v,T min,T max) {
	if( v < min ) v=min;
	if( v > max ) v=max;
}

template<typename T>
void rclip(T &v,T min,T max) {
	if( v < min ) v=max;
	if( v > max ) v=min;
}

template<typename T>
void clipl(T &v,T min) {
	if( v < min ) v=min;
}

template<typename T>
void clipu(T &v,T max) {
	if( v > max ) v=max;
}

template<typename T>
void Add(T &v,T step,T min,T max) {
	v += step;
	if( v < min ) v=max;
	if( v > max ) v=min;
}

void _resize(int w,int h,Core::UserData udata);

void _ProcessEvents(void);
void ProcessEvents(void);

void _PasteBob(int x,int y,int img_nr,bool hrev,bool vrev,float scale);

class _Screen {
public:
	int x,y,w,h,d,r,vw,vh,sx,sy,ox,oy,act_font,act_font_siz;
	_Screen(void) {
		Del();
	}
	~_Screen(void) {}
	void Set(int p_w,int p_h,int p_d,int p_r) {
		w = p_w;
		h = p_h;
		d = p_d;
		r = p_r;
		x=XBASE; y=YBASE;
		if( r & HIRES )
			sx = 1;
		else
			sx = 2;
		if( r & LACED )
			sy = 1;
		else
			sy = 2;
		ox = 0;
		oy = 0;
		if( w * sx > 640 )
			vw = 640 / sx;
		else
			vw = w;
		if( h * sy > 512 )
			vh = 512 / sy;
		else
			vh = h;
	}
	void SetDisp(int p_x,int p_y,int p_vw,int p_vh) {
		x=p_x;
		y=p_y;
		vw=p_vw;
		vh=p_vh;
	}
	void SetOffset(int p_ox,int p_oy) {
		if( p_ox > w - vw ) p_ox = w - vw;
		if( p_oy > h - vh ) p_oy = h - vh;
		if( p_ox < 0 ) p_ox = 0;
		if( p_oy < 0 ) p_oy = 0;
		ox = p_ox;
		oy = p_oy;
	}
	void Del(void) {
		x=XBASE; y=YBASE;
		w=h=d=r=vw=vh=ox=oy=0;
		sx=sy=2;
		act_font=-1; act_font_siz=-1;
	}
	bool isOpened(void) {
		return w>0;
	}
};
class PBnode {
public:
	int x,y,bnr;
	bool hr,vr;
	float sc;
	PBnode(void) {bnr=-1;}
	PBnode(int px,int py,int pbnr,bool phrev,bool pvrev,float scale) : x(px), y(py), bnr(pbnr), hr(phrev), vr(pvrev), sc(scale) {}
	~PBnode() {}
};
class PBList : std::vector<PBnode*> {
public:
	PBList(void) {}
	~PBList() {
		PBList::iterator it;
		for( it=this->begin(); it!=this->end(); ++it ) {
			delete (*it);
			(*it)=0;
		}
	}
	void Add(int x,int y,int nr,bool hrev, bool vrev,float scale) {
		this->push_back( new PBnode(x,y,nr,hrev,vrev,scale) );
	}
	void Draw(void) {
		PBList::iterator it;
		PBnode *pbn;
		for( it=this->begin(); it!=this->end(); ++it ) {
			pbn = *it;
			_PasteBob( pbn->x, pbn->y, pbn->bnr, pbn->hr, pbn->vr, pbn->sc );
		}
	}
};

PBList* _NewPBList(void);
void PBListOnoff(bool onoff);

void ScreenOpen(int nr,int w,int h,int dep,int res);
void ScreenDisplay(int nr,int x,int y,int vw,int vh);
void ScreenOffset(int nr,int ox,int oy);
void Screen(int nr);
int Screen(void);
void ScreenClose(int nr);
int XScreen(int x);
int YScreen(int y);
int ScreenX(void);
int ScreenY(void);

void _AmosInit(void);
void _AmosFinish(void);
void _DrawIff(int nr,int x,int y);
int _PointIff(int x,int y);
LTex* _GetImage(int bank,int img);
void _ClipImage(int bank,int img,int hsiz,int vsiz);

void Sprite(int nr,int x,int y,int img_nr);
void SpriteOnOff(int nr,bool onoff);
void _SpriteUpdate(void);
void SpriteUpdateOnOff(bool onoff);

void Amal(int nr,const string& code);
void AmalOnOff(int nr,bool onoff);
void AmalFreeze(int nr);
void ChannelToSprite(int ch_nr,int spr_nr);
void ChannelToBob(int ch_nr,int bob_nr);

void BobUpdate(void);
void BobUpdateOnOff(bool onoff);
void _Bob(int nr,int x,int y,int img_nr);
void BobOnOff(int nr,bool onoff);
void PasteBob(int x,int y,int img_nr);
void PasteBob(int x,int y,int img_nr,float scale);
void DelBob(int nr);
void LimitBob(int nr,int x1,int y1,int x2,int y2);
void HotSpot(int nr,int hs);
unsigned int Hrev(unsigned int img_nr);
unsigned int Vrev(unsigned int img_nr);
bool IsHrev(unsigned int img_nr);
bool IsVrev(unsigned int img_nr);
void GetSprite(int nr,unsigned char *buf,int w,int h);
void GetSprite(int nr,int x1,int y1,int x2,int y2);

void ChangeMouse(int nr);
void LimitMouse(int x1,int y1,int x2,int y2);

void Erase(int bnr);
void EraseAll(void);
int LoadAbkSp(const string& fname,int bank_nr);
int LoadIff(const string& fname,int screen_nr);
int LoadAbkMus(const string& fname,int bank_nr);
int LoadAbkSnd(const string& fname,int bank_nr);
int LoadTrack(const string& fname,int bank_nr);

int _IffWidth(int scr);
int _IffHeight(int scr);

bool Exists(const string& fname);
bool DirExists(const string& fname);
void TrackLoop(bool onoff);
void TrackPlay(int nr);
void TrackFade(int speed);
void TrackStop(void);
void Mvolume(int vol);
void Music(int mus);
void MusicStop(void);
void SamBank(int bnr);
void SamLoop(bool onoff);
void SamPlay(int sam);

void WaitVbl(void);
void Wait(int cnt);
void WaitMilisec(int cnt);
void SwapBuffers(void);
bool MouseClick(void);
int XMouse(void);
int YMouse(void);
int MouseKey(void);
int XHard(int x);
int YHard(int y);
void SetXMouse(int x);
void SetYMouse(int y);

int SetFont(const string& id,const string& fname,int siz,bool pb_antialiasing);
int SetFont(int nr);
void Text(int x,int y,const string& s);
void Text(int x,int y,const string& s,float scale);
void DbgRenderFont(void);
int TextLength(const string& s);
int TextBase(void);
void Fade(float intense);
void _Bar(int x1,int y1,int x2,int y2);
void _Box(int x1,int y1,int x2,int y2);
void _Rainbow(int x1,int y1,int x2,int y2,float *rb,int rows);
void _Line(int x1,int y1,int x2,int y2);
void _Draw(int x1,int y1,int x2,int y2);
void Clip(void);
void Clip(int x1,int y1,int x2,int y2);

void ReserveZone(int cnt);
void SetZone(int nr,int x1,int y1,int x2,int y2);
void ResetZone(int nr);
int _Zone(int x,int y);
int MouseZone(void);
void DbgDrawZones(int scr);

void ClearKey(void);
string Inkey_S(void);
int ScanCode(void);
int KeyState(int key);
string Chr_S(int i);
string Str_S(int i);
int Asc(const string& str);
int Len(const string& str);
string Left_S(const string& str,aint cnt);
string Right_S(const string& str,aint cnt);
string Mid_S(const string& str,aint pos,aint cnt);
string Upper_S(const string& str);
string Minus_S(const string& str1,const string& str2);
int Instr(const string& str,const string& pat);
int Val(const string& str);
int Sgn(int x);
float Sgn(float x);
int Abs(int x);
float Abs(float x);
int Sqr(int x);
float Sqr(float x);
int Rnd(int b);

int Peek(unsigned char *adr);
int Deek(unsigned char *adr);
int Leek(unsigned char *adr);
string Peek_S(unsigned char *adr,int len);

void Poke(unsigned char *adr,int data);
void Doke(unsigned char *adr,int data);
void Loke(unsigned char *adr,int data);
void Poke_S(unsigned char *adr,string data);

void _ClearRaster(void);
void _ClearRaster(float x1,float y1,float x2,float y2);

void* ReserveBuffer(int x,int y,int w,int h);
void StoreBuffer(void *s,int x,int y,int w,int h);
void* StoreBuffer(int x,int y,int w,int h);
void RestoreBuffer(void *s);
void FreeBuffer(void *s);
void WriteBuffer2File(void *s,const string& filename);

void SamStop(int snr);

void _BufSet(unsigned char *buf,int w,int h);
void _BufColor(float r,float g,float b,float a);
void _BufPlot(float x,float y);

void _ShowCursor(bool vis);

#endif
