/*
Implementacja czesci funkcjonalnosci Amosa
*/

#include <string>
#include <cstdio>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>

#include <GL/gl.h>

#include <Engine2d/Core.h>
#include <Engine2d/Gfx.h>
#include <Engine2d/Sfx.h>

#include "main.h"
#include "Amos.h"
#include "AmosMusic.h"
#include "AmosImage.h"

using namespace std;

aint Param;
astr Param_S;
aflt Param_F;


class CBobLimit {
public:
	int x1,y1,x2,y2;
	bool onoff;
	CBobLimit(void) { Reset(); }
	CBobLimit(int px1,int py1,int px2,int py2) : x1(px1), y1(py1), x2(px2), y2(py2), onoff(true) {}
	~CBobLimit() {}
	void Reset(void) { x1=y1=x2=y2=0; onoff=false; }
	void Set(int px1,int py1,int px2,int py2) {
		x1=px1; y1=py1; x2=px2; y2=py2; onoff=true;
	}
	bool operator==(const CBobLimit& b) const {
		if( (b.x1 != x1) || (b.y1 != y1) || (b.x2 != x2) || (b.y2 != y2) )
			return false;
		return true;
	}
	void operator=(const CBobLimit& b) {
		x1=b.x1;
		y1=b.y1;
		x2=b.x2;
		y2=b.y2;
		onoff=b.onoff;
	}
	void And(const CBobLimit& b) {
		if( b.x1 > x1 ) x1=b.x1;
		if( b.x2 < x2 ) x2=b.x2;
		if( b.y1 > y1 ) y1=b.y1;
		if( b.y2 < y2 ) y2=b.y2;
		if( x1 > x2 ) x1=x2;
		if( y1 > y2 ) y1=y2;
	}
	bool isActive(void) {
		return onoff;
	}
};


static _Screen screens[16];
static int act_screen = -1;

static Gfx::TextureManager amos_sp_bank[16];
static int act_sp_bank = 0;
static float amos_sp_xscale[1024], amos_sp_yscale[1024];

static SDL_Surface *pictures[16], *pictures_pal[16];
static Mix_Music *musics[16];
static bool ib_track_loop = false;
static int ii_track_playing=-1;

static Sfx::SampleManager amos_sam_bank[16];
static int ii_act_sam_bank = -1;
static bool ib_sam_loop = false;

static Gfx::FontManager ic_font_mgr;
static int font_cnt = -1;
static Gfx::Font* font_tab[1024];
static int font_siz[1024];

static long vbl_counter = 0;

static Gfx::Bob sprites[16];
static bool sprites_onoff[16], sprites_set[16];
//static int sprites_img[16];
static bool ib_sprite_auto_update = true;

static Gfx::Bob bobs[256];
static int bobs_img[256], bobs_screen[256];
static bool bobs_onoff[256], bobs_set[256];
static CBobLimit bobs_limit[256];
//static float bobs_scalex[256], bobs_scaley[256];
static bool ib_bob_auto_update = true;
static Gfx::Alan alan;

static bool ib_lmb = false, ib_rmb = false, ib_mouse_clicked = false, ib_mouse_clicked_read = false;
static long il_mousex = 0, il_mousey = 0;
static long il_mouse_min_x, il_mouse_min_y, il_mouse_max_x, il_mouse_max_y;

static queue<int> key_buf;				//kolejka wcisnietych klawiszy (amos moze nie pobierac ich na biezaco)
static queue<unsigned short> keymod_buf;
static bool key_state[SDLK_LAST];	//bufor stanow

static bool ib_true = true, ib_false = false;
static bool ib_pblist = false;
static PBList* ic_act_pblist = 0;

static float if_scalex = 1.0, if_scaley = 1.0;

static float if_hq_scalex = 0.5, if_hq_scaley = 0.5;


class CStoreBuffer {
public:
	int x,y,w,h;
	int xx,yy,ww,hh;
	GLbyte *buf;
	CStoreBuffer(int p_x,int p_y,int p_w,int p_h) : x(p_x), y(p_y), w(p_w), h(p_h) {
		buf = 0;
		xx = 0;
		yy = 0;
		ww = 0;
		hh = 0;
	}
	~CStoreBuffer() {
		delete[] buf;
	}
	void Store(void) {
		glFlush();
		glPixelStorei(GL_PACK_ALIGNMENT,1);
		glPixelStorei(GL_PACK_ROW_LENGTH,0);
		glPixelStorei(GL_PACK_SKIP_ROWS,0);
		glPixelStorei(GL_PACK_SKIP_PIXELS,0);
		glReadBuffer(GL_BACK);

		ww = (int)(w * if_scalex + 0.5);
		hh = (int)(h * if_scaley + 0.5);

		delete[] buf;
		buf = new GLbyte[ww*hh*4];

		int xr = (int)(x * if_scalex + 0.5);
		int yr = (int)((DISPLAY_HEIGHT - y - h)*if_scaley+0.5);
		xx = x;
		yy = y+h;
		glReadPixels(xr,yr,ww,hh,GL_RGBA,GL_UNSIGNED_BYTE,buf);
	}
	void Store(int px,int py,int pw,int ph) {
		x=px;
		y=py;
		w=pw;
		h=ph;
		Store();
	}
	void Draw(int p_x,int p_y) {
		if( 0==buf ) return;
		glPixelStorei(GL_UNPACK_ALIGNMENT,1);
		glPixelStorei(GL_UNPACK_ROW_LENGTH,0);
		glPixelStorei(GL_UNPACK_SKIP_ROWS,0);
		glPixelStorei(GL_UNPACK_SKIP_PIXELS,0);
		glPixelZoom(1,1);
		glRasterPos2i(p_x,p_y);
		glDrawPixels(ww,hh,GL_RGBA,GL_UNSIGNED_BYTE,buf);
	}
	void Restore(void) {
		Draw(xx,yy);
	}
};

class CPicture {
protected:
  Gfx::TextureManager *tx_mgr;
  int ii_tw, ii_th;
public:
  CPicture(void) {
    tx_mgr = new Gfx::TextureManager();
    ii_tw = 0;
    ii_th = 0;
  }
  ~CPicture() {
    delete tx_mgr;
  }
  void Free(void) {
  	tx_mgr->DelAll();
  	ii_tw = 0;
  	ii_th = 0;
  }
  void Set(SDL_Surface *image) {
    if( 0 == image ) return;

    int w = image->w
      , h = image->h
      , tw = w/128 + ((w%128) > 0 ? 1 : 0)
      , th = h/128 + ((h%128) > 0 ? 1 : 0)
      ;

		Free();
    ii_tw = tw;
    ii_th = th;

    unsigned char buf[128*128*4], buf_2x[128*128*4*2*2];
    Uint8 *pix = (Uint8*)(image->pixels);
    Uint8 *p;
    Gfx::PTex *ptex;

    int tx,ty, ww, hh, sw, sh, i, j, cnt;
    sh = 0;
    cnt = 0;
    for( ty = 0; ty < th; ++ty ) {
      sh += 128;
      if( sh <= h ) {
        hh = 128;
      } else {
        hh = h - (sh-128);
      }

      sw = 0;
      for( tx = 0; tx < tw; ++tx ) {
        sw += 128;
        if( sw <= w ) {
          ww = 128;
        } else {
          ww = w - (sw-128);
        }

        if( ww<128 || hh<128 ) {
          for( j=0; j<128; ++j ) {
            for( i=0; i<128; ++i ) {
              buf[(i+j*128)*4+0] = 0;
              buf[(i+j*128)*4+1] = 0;
              buf[(i+j*128)*4+2] = 0;
              buf[(i+j*128)*4+3] = 0;
            }
          }
        }

        p = pix + (tx+ty*w) * 128 * 4;
        for( j=0; j<hh; ++j ) {
          for( i=0; i<ww; ++i ) {
            buf[(i+j*128)*4+0] = p[(i+j*w)*4+0];
            buf[(i+j*128)*4+1] = p[(i+j*w)*4+1];
            buf[(i+j*128)*4+2] = p[(i+j*w)*4+2];
            buf[(i+j*128)*4+3] = p[(i+j*w)*4+3];
          }
        }

        ptex = new Gfx::PTex();
        if( SCLT_NONE == HQScaleType ) {
					ptex->Set(buf,128,128);
        } else {
					ImageScale2x(buf,buf_2x,128,128);
					ptex->Set(buf_2x,256,256);
        }

        tx_mgr->AddPTex(toString(cnt),ptex);
        tx_mgr->AddLTex(toString(cnt),new Gfx::LTex(ptex));

        ++cnt;

      }
    }
  }

  void Draw(float x,float y,float sx,float sy) {
  	if( ii_tw < 0 || ii_th < 0 ) return;
    Gfx::BeginBobBlits();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
      glTranslatef(x,y,0);
      glScalef(sx,sy,0);
      int i,j,cnt;
      Gfx::LTex *ltx;
      cnt=0;
      for( j=0; j<ii_th; ++j ) {
        for( i=0; i<ii_tw; ++i ) {
          glPushMatrix();
          glTranslatef(i*128,j*128,0);
          ltx = tx_mgr->GetLTex(toString(cnt));
          glBindTexture(GL_TEXTURE_2D, ltx->GetTextureID() );
          glBegin(GL_QUADS);
            glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
            glTexCoord2f( ltx->Getfx1(), ltx->Getfy1() );		glVertex2f(   0.0f,   0.0f );
            glTexCoord2f( ltx->Getfx2(), ltx->Getfy1() );		glVertex2f( 128.0f,	  0.0f );
            glTexCoord2f( ltx->Getfx2(), ltx->Getfy2() );		glVertex2f( 128.0f, 128.0f );
            glTexCoord2f( ltx->Getfx1(), ltx->Getfy2() );		glVertex2f(   0.0f, 128.0f );
          glEnd();
          glPopMatrix();
          ++cnt;
        }
      }
    glPopMatrix();
    Gfx::EndBobBlits();
  }

};

static CPicture pix[16];

int ii_clip_x, ii_clip_y, ii_clip_w,ii_clip_h;
bool ib_clip_onoff = false;
void _clip(int x,int y,int w,int h) {
	ii_clip_x = x;
	ii_clip_y = y;
	ii_clip_w = w;
	ii_clip_h = h;
}
void _clip_on(void) {
	glScissor( (int)(ii_clip_x*if_scalex)
					 , (int)(ii_clip_y*if_scaley)
					 , (int)(ii_clip_w*if_scalex)
					 , (int)(ii_clip_h*if_scaley) );
	glEnable(GL_SCISSOR_TEST);
	ib_clip_onoff = true;
}
void _clip_off(void) {
	ib_clip_onoff = false;
	glDisable(GL_SCISSOR_TEST);
}

Uint32 _VblCallback(Uint32 interval,void *usedata) {
	++vbl_counter;
	alan.process(( (float)interval)/1000.0 );
	return 20;	//1000/50
}
void _mouse_button(int button,int x,int y,Core::UserData udata) {
	bool state = *((bool*)udata);
	if( SDL_BUTTON_LEFT == button ) {
		ib_lmb = state;
		if( state ) {
			ib_mouse_clicked = true;
		}
	} else if( SDL_BUTTON_RIGHT == button ) {
		ib_rmb = state;
	}
}
void _mouse_move(int x,int y,int xrel, int yrel,Core::UserData udata) {
	il_mousex = (long)(((float)x)/(2.0*if_scalex)) + XBASE;
	il_mousey = (long)(((float)y)/(2.0*if_scaley)) + YBASE;
	if( il_mousex < il_mouse_min_x ) il_mousex = il_mouse_min_x;
	if( il_mousey < il_mouse_min_y ) il_mousey = il_mouse_min_y;
	if( il_mousex > il_mouse_max_x ) il_mousex = il_mouse_max_x;
	if( il_mousey > il_mouse_max_y ) il_mousey = il_mouse_max_y;
}
void _key_down(int key,Core::UserData udata) {
	unsigned short keymod = Core::ModifiersState();
	key_buf.push(key);
	keymod_buf.push(keymod);
	if( key >= 0 && key < SDLK_LAST ) key_state[key]=true;
}
void _key_up(int key,Core::UserData udata) {
	if( key >= 0 && key < SDLK_LAST ) key_state[key]=false;
}
void _resize(int w,int h,Core::UserData udata) {
	glViewport(0,0,w,h);
	//Core::ProjectionOrtho(0,DISPLAY_WIDTH,DISPLAY_HEIGHT,0);
	if_scalex = w;
	if_scalex /= DISPLAY_WIDTH;
	if_scaley = h;
	if_scaley /= DISPLAY_HEIGHT;
	if( ib_clip_onoff ) _clip_on();
}
void _ProcessEvents(void) {
	if( ib_mouse_clicked_read ) {
		ib_mouse_clicked = false;
		ib_mouse_clicked_read = false;
	}
	bool quit = Core::ProcessEvents();	//i na koniec przetwarzamy zdarzenia
	if( quit ) {
		_AmosFinish();
		exit(0);
	}
}
void ProcessEvents(void) {
	SDL_Delay(1);
	_ProcessEvents();
}
void WaitVbl(void) {

	//rysujemy boby
	if( ib_bob_auto_update )
		BobUpdate();

	//rysujemy sprite
	if( ib_sprite_auto_update )
		_SpriteUpdate();

	//debugowe dane
	//Gfx::Color(1.0f,1.0f,1.0f);
	//Text(20,20,"MouseX="+toString(il_mousex));
	//Text(20,40,"MouseY="+toString(il_mousey));

	//czekamy na nast ramke
	long cnt = vbl_counter;
	while( cnt == vbl_counter ) {		//vbl_counter jest zmieniany w callbacku Timera
		SDL_Delay(1);
	}

	//zamieniamy bufory
	Core::SwapBuffers();

	Core::FrameTiming(Core::FTM_NEW_FRAME);		//i zaczynamy nowa ramke

	//!@# - aby zasymulowac swapbuffer mode flip
//
//	static int ii_buf=0;
//	if( ii_buf == 0 ) {
//		ii_buf = 1;
//    if( ib_clip_onoff ) {
//      _clip_off();
//      Gfx::Cls(0,0,0);
//      _clip_on();
//    } else {
//      Gfx::Cls(0,0,0);
//    }
//	} else {
//		ii_buf = 0;
//    if( ib_clip_onoff ) {
//      _clip_off();
//      Gfx::Cls(1,0,0);
//      _clip_on();
//    } else {
//      Gfx::Cls(1,0,0);
//    }
//	}


  //czyszczenie ramki
/*
	if( ib_clip_onoff ) {
	  _clip_off();
	  Gfx::Cls(0,0,0);
	  _clip_on();
	} else {
	  Gfx::Cls(0,0,0);
	}
*/

	_ProcessEvents();
}
void Wait(int cnt) {
	SDL_Delay(cnt * 20);
}
void WaitMilisec(int cnt) {
	int bef, aft;
	bef = Core::FrameTiming(Core::FTM_FRAME_TIME);
	SDL_Delay(cnt);
	do {
		aft = Core::FrameTiming(Core::FTM_FRAME_TIME);
		LOG("Waited " + toString(aft-bef) + " have to " + toString(cnt) );
	} while( aft - bef < cnt );
}
void SwapBuffers(void) {
	Core::SwapBuffers();
}


void _AmosInit(void) {
	for(int i = 0; i < 16; ++i ) {
		pictures[i] = 0;
		pictures_pal[i] = 0;
		musics[i] = 0;
	}
	for(int i = 0; i < 1024; ++i ) {
		font_tab[i] = 0;
		font_siz[i] = 0;
	}
	for(int i = 0; i < 16; ++ i ) {
		sprites_onoff[i] = true;
		sprites_set[i] = false;
	}
	for(int i = 0; i < 256; ++ i ) {
		bobs_onoff[i] = true;
		bobs_set[i] = false;
		bobs_img[i] = 0;
		bobs_screen[i] = 0;
	}

	il_mouse_min_x = 0;
	il_mouse_min_y = 0;
	il_mouse_max_x = 639;
	il_mouse_max_y = 511;

	if( SCLT_NONE == HQScaleType ) {
		if_hq_scalex = 1.0;
		if_hq_scaley = 1.0;
	} else {
		if_hq_scalex = 0.5;
		if_hq_scaley = 0.5;
	}

	for(int i = 0; i < SDLK_LAST; ++i ) {
		key_state[i] = false;
	}

	if( 0 == (SDL_WasInit(SDL_INIT_TIMER) & SDL_INIT_TIMER) )
		SDL_InitSubSystem(SDL_INIT_TIMER);
	SDL_AddTimer(20,_VblCallback,0);

	Core::RegisterMouseButtonDownEvent(_mouse_button,&ib_true);
	Core::RegisterMouseButtonUpEvent(_mouse_button,&ib_false);
	Core::RegisterMouseMotionEvent(_mouse_move,0);
	Core::RegisterKeyDownEvent(_key_down,0);
	Core::RegisterKeyUpEvent(_key_up,0);
	Core::RegisterResizeEvent(_resize,0);

	Core::RandomizeTimer();
}
void _AmosFinish(void) {
	//zamykamy wszystkie ekrany
	for(int i=0;i<16;++i) {
		ScreenClose(i);
	}
	//usuwamy wszystkie banki
	EraseAll();
}


//to aby sledzic, do ktorego pojemnika zaladowac IFFa
void _ScreenClip(int nr) {
	if( nr < 0 || nr >= 16 ) return;
	int w = screens[nr].vw * screens[nr].sx
	  , h = screens[nr].vh * screens[nr].sy
	  , x, y;
	x = XSCRN(screens[nr].x);
	y = YSCRN(screens[nr].y);
	_clip( x, DISPLAY_HEIGHT-h-y, w, h );
	_clip_on();
}
void _SetActScreen(int nr) {
	if( nr < 0 || nr >= 16 ) return;
	act_screen = nr;
	_ScreenClip(nr);
}
void ScreenOpen(int nr,int w,int h,int dep,int res) {
	LOG("nr="+toString(nr));
	if( nr < 0 || nr >= 16 ) return;
	screens[nr].Set(w,h,dep,res);
	_SetActScreen(nr);
}
void Screen(int nr) {
	_SetActScreen(nr);
}
int Screen(void) {
	return act_screen;
}
void ScreenDisplay(int nr,int x,int y,int vw,int vh) {
	if( nr < 0 || nr >= 16 ) return;
	if( NOPARI == x ) x = screens[nr].x;
	if( NOPARI == y ) y = screens[nr].y;
	if( NOPARI == vw ) vw = screens[nr].vw;
	if( NOPARI == vh ) vh = screens[nr].vh;
	screens[nr].SetDisp(x,y,vw,vh);
	if( nr == act_screen ) _SetActScreen(nr);	//aby zastosowac ograniczanie do ekranu
}
void ScreenOffset(int nr,int ox,int oy) {
	if( nr < 0 || nr >= 16 ) return;
	if( NOPARI == ox ) ox = screens[nr].ox;
	if( NOPARI == oy ) oy = screens[nr].oy;
	screens[nr].SetOffset(ox,oy);
}
void ScreenClose(int nr) {
	LOG("nr="+toString(nr));
	if( nr < 0 || nr >= 16 ) return;

	screens[nr].Del();

	if( pictures[nr] ) {
		SDL_FreeSurface(pictures[nr]);
		pictures[nr] = 0;
	}

	if( pictures_pal[nr] ) {
		SDL_FreeSurface(pictures_pal[nr]);
		pictures_pal[nr] = 0;
	}

	pix[nr].Free();

	if( nr == act_screen ) {
		act_screen = -1;
		for( int i=0; i<16; ++i ) {
			if( screens[i].isOpened() ) {
				act_screen = i;
				break;
			}
		}
	}
}
int _GetXOffset(int nr) {
	if( nr < 0 || nr >= 16 ) return 0;
	return XSCRN(screens[nr].x) - screens[nr].ox * screens[nr].sx;
}
int _GetYOffset(int nr) {
	if( nr < 0 || nr >= 16 ) return 0;
	return YSCRN(screens[nr].y) - screens[nr].oy * screens[nr].sy;
}
int _GetXScale(int nr) {
	if( nr < 0 || nr >= 16 ) return 1;
	return (screens[nr].sx);
}
int _GetYScale(int nr) {
	if( nr < 0 || nr >= 16 ) return 1;
	return screens[nr].sy;
}
int XScreen(int x) {
	if( act_screen < 0 ) return 0;
	return (x - screens[act_screen].x + screens[act_screen].ox) * (3 - screens[act_screen].sx);
}
int YScreen(int y) {
	if( act_screen < 0 ) return 0;
	return (y - screens[act_screen].y + screens[act_screen].oy) * (3 - screens[act_screen].sy);
}
int ScreenX(void) {
	if( act_screen < 0 ) return -1;
	return _GetXOffset(act_screen);
}
int ScreenY(void) {
	if( act_screen < 0 ) return -1;
	return _GetYOffset(act_screen);
}


void _DrawIff(int nr,int x,int y) {
	if( nr < 0 ) nr = act_screen;
	if( nr < 0 ) return;
	if( 0 == pictures[nr] ) return;
  pix[nr].Draw(  (int)( _GetXOffset(nr) )
                ,(int)( _GetYOffset(nr) )
                ,_GetXScale(nr)
                ,_GetYScale(nr) );
}
int _PointIff(int x,int y) {
	if( act_screen < 0 ) return -1;
	if( pictures_pal[act_screen] == 0 ) return -1;
	if( x < 0 || y < 0 || x >=  pictures_pal[act_screen]->w || y >= pictures_pal[act_screen]->h ) return -1;	//wskazany punkt poza obrazkiem
	SDL_PixelFormat *fmt = pictures_pal[act_screen]->format;
	if( fmt->BitsPerPixel > 8 ) return -1;	//format nie paletowy - odpada
	Uint8 *pix = (Uint8*)(pictures_pal[act_screen]->pixels);
	int idx;
	idx = pix[ x + y*pictures_pal[act_screen]->pitch ];
	return idx;
}
LTex* _GetImage(int bank,int img) {
	if( bank < 0 ) bank = act_sp_bank;
	Gfx::TextureManager *txm = &(amos_sp_bank[bank]);
	Gfx::LTex *ltex = txm->GetLTex(toString(img));
	return ltex;
}
void _ClipImage(int bank,int img,int hsiz,int vsiz) {
	Gfx::LTex *ltex = _GetImage(bank,img);
	if( 0 == ltex ) return;

	int x1,y1,x2,y2,w,h;
	x1 = (int)ltex->Getix1();
	y1 = (int)ltex->Getiy1();
	x2 = (int)ltex->Getix2();
	y2 = (int)ltex->Getiy2();

	w = x2 - x1;
	if( hsiz > 0 ) {
		//ustaw rozmiar na wskazany
		if( hsiz < w ) {
			w = hsiz;
		}
	} else if( hsiz < 0 ) {
		//zmniejsz rozmiar o wskazana wartosc
		if( -hsiz <= w ) {
			w += hsiz;
		} else {
			w = 0;
		}
	}

	h = y2 - y1;
	if( vsiz > 0 ) {
		//ustaw rozmiar na wskazany
		if( vsiz < h ) {
			h = vsiz;
		}
	} else if( vsiz < 0 ) {
		//zmniejsz rozmiar o wskazana wartosc
		if( -vsiz <= h ) {
			h += vsiz;
		} else {
			h = 0;
		}
	}

	ltex->Set( ltex->GetPTex(), x1, y1, x2, y1 + h );
}


void Sprite(int nr,int x,int y,int img_nr) {
	if( nr < 0 || nr >= 16 ) return;

	if( img_nr == NOPARI ) {
//		img_nr = sprites_img[nr];
	} else {
		Gfx::LTex *ltex = _GetImage(1,img_nr);
		if( ltex )
			sprites[nr].SetTex( ltex );
	}

	sprites[nr].SetPos( XSCRN(x), YSCRN(y) );
	sprites[nr].SetScale(2*if_hq_scalex,2*if_hq_scaley);
	sprites_onoff[nr] = true;
	sprites_set[nr] = true;
//	sprites_img[nr] = img_nr;
}
void SpriteOnOff(int nr,bool onoff) {
	if( nr < 0 ) {
		for( int i=0; i<16; ++i )
			sprites_onoff[i] = onoff;
	} else if( nr < 16 ) {
		sprites_onoff[nr] = onoff;
	}
}
void _SpriteUpdate(void) {
	_clip_off();
	for(int i = 15; i >= 0; --i ) {
		if( sprites_onoff[i] && sprites_set[i] ) sprites[i].Blit();
	}
	_clip_on();
}
void SpriteUpdateOnOff(bool onoff) {
	ib_sprite_auto_update = onoff;
}

void Amal(int nr,const string& code) {
	alan.closeChannel(toString(nr));
	try {
		alan.openChannel(toString(nr),code);
	} catch(...) {
		LOG("exception")
	}
	alan.stopChannel(toString(nr));
}
void AmalOnOff(int nr,bool onoff) {
	if( nr < 0 ) {
		for( int i=0; i<64; ++i ) {
			if( onoff )
				alan.startChannel(toString(i));
			else {
				alan.stopChannel(toString(i));
				alan.closeChannel(toString(i));
			}
		}
	} else {
		if( onoff )
			alan.startChannel(toString(nr));
		else {
			alan.stopChannel(toString(nr));
			alan.closeChannel(toString(nr));
		}
	}
}
void AmalFreeze(int nr) {
	if( nr < 0 ) {
		for( int i=0; i<64; ++i ) {
			alan.stopChannel(toString(i));
		}
	} else {
		alan.stopChannel(toString(nr));
	}
}
void ChannelToSprite(int ch_nr,int spr_nr) {
	alan.bindObject(toString(ch_nr),&(sprites[spr_nr]));
	alan.setTextureMgr(toString(ch_nr),&(amos_sp_bank[1]));
}
void ChannelToBob(int ch_nr,int bob_nr) {
	alan.bindObject(toString(ch_nr),&(bobs[bob_nr]));
	alan.setTextureMgr(toString(ch_nr),&(amos_sp_bank[1]));
}

PBList* _NewPBList(void) {
	PBList* pbl = new PBList();
	ic_act_pblist = pbl;
	return pbl;
}
void PBListOnoff(bool onoff) {
	ib_pblist = onoff;
}

unsigned int _ImgNr(int img_nr) {
	return ((unsigned int) img_nr) & 0x3fff;
}
void _Bob(int nr,int x,int y,int img_nr) {
	if( nr < 0 || nr >= 256 ) return;

	float xf = x, yf = y, sx=2,sy=2;

	if( NOPARI == x ) xf = bobs[nr].GetX();
	if( NOPARI == y ) yf = bobs[nr].GetY();
	if( NOPARI == img_nr ) img_nr = bobs_img[nr];

	Gfx::LTex *ltex = _GetImage(1,_ImgNr(img_nr));
	if( ltex )
		bobs[nr].SetTex( ltex );
	bobs[nr].SetPos( xf, yf );
	if( act_screen >= 0 ) {
		sx = screens[act_screen].sx;
		sy = screens[act_screen].sy;
	}
	sx *= amos_sp_xscale[_ImgNr(img_nr)] * if_hq_scalex;
	sy *= amos_sp_yscale[_ImgNr(img_nr)] * if_hq_scaley;
	if( IsHrev(img_nr) ) sx *= -1.0;
	if( IsVrev(img_nr) ) sy *= -1.0;
	bobs[nr].SetScale(sx,sy);
	bobs_onoff[nr] = true;
	bobs_set[nr] = true;
	bobs_img[nr] = img_nr;
	bobs_screen[nr] = act_screen;
}
void PasteBob(int x,int y,int img_nr) {
	PasteBob(x,y,img_nr,1.0);
}
void PasteBob(int x,int y,int img_nr,float scale) {
	if( ib_pblist && ic_act_pblist ) {
		ic_act_pblist->Add(x,y,_ImgNr(img_nr),IsHrev(img_nr),IsVrev(img_nr),scale);
		return;
	}
	_PasteBob(x,y,_ImgNr(img_nr),IsHrev(img_nr),IsVrev(img_nr),scale);
}
void _PasteBob(int x,int y,int img_nr,bool hrev,bool vrev,float scale) {
	if( act_screen < 0 ) return;
	Gfx::LTex *ltex = _GetImage(1,img_nr);
	if( 0 == ltex ) return;
	static Gfx::Bob b;
	b.SetTex(ltex);
	b.SetPos( x * _GetXScale(act_screen) + _GetXOffset(act_screen)
	        , y * _GetYScale(act_screen) + _GetYOffset(act_screen) );
	float hsc=scale,vsc=scale, hsx=b.GetHotSpotX(), hsy=b.GetHotSpotY();
	hsc *= amos_sp_xscale[img_nr] * if_hq_scalex;
	vsc *= amos_sp_yscale[img_nr] * if_hq_scaley;
	if( hrev ) {
		hsc=-hsc;
		hsx=b.GetWidth()-hsx;
	}
	if( vrev ) {
		vsc=-vsc;
		hsy=b.GetHeight()-hsy;
	}
	b.SetScale(_GetXScale(act_screen)*hsc,_GetYScale(act_screen)*vsc);
	b.SetHotSpot(hsx,hsy);
	b.Blit();
}

void BobOnOff(int nr,bool onoff) {
	if( nr < 0 ) {
		for( int i=0; i<256; ++i )
			bobs_onoff[i] = onoff;
	} else {
		bobs_onoff[nr] = onoff;
	}
}
bool bob_pos_cmp( int a, int b ) {
	return bobs[a].GetY() < bobs[b].GetY();
}
void BobUpdate(void) {
	int idx[256], i, cnt=0;
	for(i = 0; i < 256; ++i ) {
		if( bobs_onoff[i] && bobs_set[i] ) {
			idx[cnt] = i;
			++cnt;
		}
	}

	if( cnt > 1 ) {
		sort( idx, idx+cnt, bob_pos_cmp );
	}

	CBobLimit bob_limit, pbob_limit, scr_limit;
	int scr,pscr=-1,w,h,x,y;
	for(int j = 0; j < cnt; ++j ) {
		i = idx[j];
		scr = bobs_screen[i];
		if( screens[scr].isOpened() ) {
			if( scr != pscr ) {
				pscr = scr;
				scr_limit.Set(screens[scr].ox,screens[scr].oy,screens[scr].ox+screens[scr].vw,screens[scr].oy+screens[scr].vh);
				pbob_limit.Reset();
				_ScreenClip(scr);
			}
			if( bobs_limit[i].isActive() ) {
				if( !(pbob_limit==bobs_limit[i]) ) {
					pbob_limit = bobs_limit[i];
					bob_limit = bobs_limit[i];
					bob_limit.And(scr_limit);
					w = (bob_limit.x2 - bob_limit.x1) * _GetXScale(scr);
					h = (bob_limit.y2 - bob_limit.y1) * _GetYScale(scr);
					x = _GetXOffset(scr) + bob_limit.x1 * _GetXScale(scr);
					y = _GetYOffset(scr) + bob_limit.y1 * _GetYScale(scr);
					_clip( x, DISPLAY_HEIGHT - h - y, w, h );
					_clip_on();
				}
			} else {
				if( pbob_limit.isActive() ) {
					pbob_limit.Reset();
					_ScreenClip(scr);
				}
			}

			bobs[i].Blit( bobs[i].GetX() * (_GetXScale(bobs_screen[i])-1) + _GetXOffset(bobs_screen[i])
									, bobs[i].GetY() * (_GetYScale(bobs_screen[i])-1) + _GetYOffset(bobs_screen[i]));
		}
	}

}
void BobUpdateOnOff(bool onoff) {
	ib_bob_auto_update = onoff;
}
void DelBob(int nr) {
	int len = amos_sp_bank[1].CountLTex();
	amos_sp_bank[1].DelLTex(toString(nr));
	amos_sp_bank[1].DelPTex(toString(nr));
	Gfx::LTex *ltex;
	Gfx::PTex *ptex;
	for( int i=nr+1; i<=len; ++i ) {
		ptex = amos_sp_bank[1].RemPTex(toString(i));
		ltex = amos_sp_bank[1].RemLTex(toString(i));
		amos_sp_bank[1].AddPTex(toString(i-1),ptex);
		amos_sp_bank[1].AddLTex(toString(i-1),ltex);
	}
}
void LimitBob(int nr,int x1,int y1,int x2,int y2) {
	if( nr < 0 || nr >= 256 ) return;
	bobs_limit[nr].Set(x1,y1,x2,y2);
}
void HotSpot(int img,int hs) {
	Gfx::LTex *ltex = _GetImage(-1,img);
	if( 0==ltex ) return;
	float hsx=0.0, hsy=0.0;
	if( hs & 0x01 ) hsy=0.5;
	if( hs & 0x02 ) hsy=1.0;
	if( hs & 0x10 ) hsx=0.5;
	if( hs & 0x20 ) hsx=1.0;
	ltex->SetHotSpot(hsx,hsy);
}
unsigned int Hrev(unsigned int img_nr) {
	return (img_nr ^ 0x8000);
}
unsigned int Vrev(unsigned int img_nr) {
	return (img_nr ^ 0x4000);
}
bool IsHrev(unsigned int img_nr) {
	return 0 != (img_nr & 0x8000);
}
bool IsVrev(unsigned int img_nr) {
	return 0 != (img_nr & 0x4000);
}
void GetSprite(int nr,unsigned char *buf,int w,int h) {
	if( nr < 0 ) return;

	Gfx::LTex *ltex;
	Gfx::PTex *ptex;

	amos_sp_bank[1].DelLTex(toString(nr));
	amos_sp_bank[1].DelPTex(toString(nr));

	ptex = new Gfx::PTex();
  if( SCLT_NONE == HQScaleType ) {
		ImageHQShadow(buf,w,h);
		ptex->Set(buf,w,h);
  } else {
		unsigned char buf_2x[w*2*h*2*4];
		ImageHQShadow(buf,w,h);
		ImageScale2x(buf,buf_2x,w,h);
		ptex->Set(buf_2x,w*2,h*2);
  }

	ltex = new Gfx::LTex(ptex);
	amos_sp_bank[1].AddPTex(toString(nr),ptex);
	amos_sp_bank[1].AddLTex(toString(nr),ltex);

	amos_sp_xscale[nr] = 1.0;
	amos_sp_yscale[nr] = 1.0;
}
void GetSprite(int nr,int x1,int y1,int x2,int y2) {
	if( nr < 0 ) return;
	int w=(x2-x1)+1, h=(y2-y1)+1;
	CStoreBuffer *sb = (CStoreBuffer*)StoreBuffer(x1,y1,w,h);
	GetSprite(nr,(unsigned char*)sb->buf,sb->ww,sb->hh);
	amos_sp_xscale[nr] = 1.0/(_GetXScale(act_screen)*if_scalex);
	amos_sp_yscale[nr] = -1.0/(_GetYScale(act_screen)*if_scaley);
	HotSpot(nr,0x02);
	FreeBuffer((void*)sb);
}


long GetByte(unsigned char *data,long pos,long len) {
	if( pos >= len ) { return 0; }
	long d;
	d = data[pos];
	return d;
}
long GetWord(unsigned char *data,long pos,long len) {
	if( pos >= len-1 ) { return 0; }
	long d;
	d = data[pos]; ++pos;
	d *= 256;
	d += data[pos];
	return d;
}
long GetLong(unsigned char *data,long pos,long len) {
	if( pos >= len-3 ) { return 0; }
	long d;
	d = data[pos]; ++pos;
	d *= 256;
	d += data[pos]; ++pos;
	d *= 256;
	d += data[pos]; ++pos;
	d *= 256;
	d += data[pos];
	return d;
}
string GetHunkID(unsigned char *data,long pos,long len) {
	if( pos >= len-3 ) { return string(""); }
	char buf[5];
	buf[0] = data[pos+0];
	buf[1] = data[pos+1];
	buf[2] = data[pos+2];
	buf[3] = data[pos+3];
	buf[4] = 0;
	return string(buf);
}
void SetHunkID(unsigned char *data,long pos,long len,const string& id) {
	if( pos >= len-3 ) { return; }
	char buf[4];
	for( int i=0; i<4; ++i ) {
		if( i < (int)id.size() )
			buf[i] = id[i];
		else
			buf[i] = 0;
	}
	data[pos+0] = buf[0];
	data[pos+1] = buf[1];
	data[pos+2] = buf[2];
	data[pos+3] = buf[3];
	return;
}
long GetHunkLen(unsigned char *data,long pos,long blen) {
	if( pos >= blen-3 ) { return -1; }
	unsigned long len = 0;
	len  = (unsigned long)data[pos+0];
	len *= 256;
	len += (unsigned long)data[pos+1];
	len *= 256;
	len += (unsigned long)data[pos+2];
	len *= 256;
	len += (unsigned long)data[pos+3];
	return (long)len;
}

void RepairTexture(unsigned char *tex,int w,int h) {
	Pic pic;
	pic.Set(tex,w,h,PDM_RGBA);
	pic.FixAlphaZero();
}

class AmosImg {
public:
	int w,h,d,hsx,hsy;
	unsigned char *bpls;
	AmosImg(void) { bpls = 0; }
	~AmosImg() {}

	//konwertuje obrazek bitplanowy do textury
	Gfx::PTex* Conv2Tex(unsigned long *pal) {
		if( 0 == bpls ) return 0;

		unsigned char rgba[w*16*h*4], *out;
		unsigned char *bpa[8];
		unsigned long bp[8];

		//ustalamy adresy kolejnych bitplanow
		for( int i = 0; i < 8; ++i ) {
			if( i < d )
				bpa[i] = bpls + i * w * 2 * h;
			else
				bpa[i] = 0;
			bp[i] = 0;
		}

		//konwertujemy do RGBA
		int x,y,i,k;
		unsigned long col, w1,w2;
		out = rgba;
		for( y=0; y<h; ++y ) {
			for( x=0; x<w; ++x ) {
				for( i=0; i<d; ++i ) {
					w1 = *( bpa[i] + (x + y*w)*2 );
					w2 = *( bpa[i] + (x + y*w)*2 + 1);
					bp[i] = (w1 << 8) | w2;
					//bpa[i] = bpa[i] + 2;
				}
				for( i=0; i<16; ++i ) {
					k  = (bp[0] & 0x8000) == 0 ? 0 : 1;
					k += (bp[1] & 0x8000) == 0 ? 0 : 2;
					k += (bp[2] & 0x8000) == 0 ? 0 : 4;
					k += (bp[3] & 0x8000) == 0 ? 0 : 8;
					k += (bp[4] & 0x8000) == 0 ? 0 : 16;
					k += (bp[5] & 0x8000) == 0 ? 0 : 32;
					k += (bp[6] & 0x8000) == 0 ? 0 : 64;
					k += (bp[7] & 0x8000) == 0 ? 0 : 128;
					bp[0] <<= 1;
					bp[1] <<= 1;
					bp[2] <<= 1;
					bp[3] <<= 1;
					bp[4] <<= 1;
					bp[5] <<= 1;
					bp[6] <<= 1;
					bp[7] <<= 1;

					//mamy juz indeks do palety
					col = pal[k];
					*out = ((col & 0x0f00) >> 4) | ((col & 0x0f00) >> 8); ++out;
					*out = ((col & 0x00f0) >> 0) | ((col & 0x00f0) >> 4); ++out;
					*out = ((col & 0x000f) << 4) | ((col & 0x000f) >> 0); ++out;
					if( 0 == k )
						*out = 0;
					else
						*out = 255;
					++out;
				}
			}
		}

		RepairTexture(rgba,w*16,h);

		Gfx::PTex *ptex = new Gfx::PTex();
    if( SCLT_NONE == HQScaleType ) {
			ImageHQShadow(rgba,w*16,h);
			ptex->Set(rgba,w*16,h);
    } else {
			unsigned char rgba_sized2[w*16*h*4 * 2*2];
			ImageHQShadow(rgba,w*16,h);
			ImageScale2x(rgba,rgba_sized2,w*16,h);
			ptex->Set(rgba_sized2,w*16*2,h*2);
    }

		return ptex;
	}
};

void Erase(int bnr) {
	if( bnr < 0 || bnr >= 16 ) return;

	if( bnr == 1 ) {	//bank spritow
		for(int i=0;i<16;++i)
			sprites_set[i] = false;
		for(int i=0;i<256;++i)
			bobs_set[i] = false;
	}

	amos_sp_bank[bnr].DelAll();
	amos_sam_bank[bnr].DelAll();

	if( ii_track_playing == bnr ) {
		TrackStop();
		MusicStop();
	}
	if( 0 != musics[bnr] ) {
		Mix_FreeMusic(musics[bnr]);
		musics[bnr] = 0;
	}

}
void EraseAll(void) {
	for(int i=0; i<16; ++i )
		Erase(i);
}

int LoadAbkSp(const string& fname,int bank_nr) {
	if( bank_nr < 0 ) bank_nr = 1;

	FILE *f = fopen(fname.c_str(),"rb");
	if( 0 == f ) {
		return -1;
	}
	fseek(f,0,SEEK_END);
	long len;
	len = ftell(f);
	fseek(f,0,SEEK_SET);

	if( len <= 0 ) {
		fclose(f);
		return -2;
	}

	unsigned char *buf = new unsigned char[len];
	fread(buf,len,1,f);
	fclose(f);

	if( "AmSp" != GetHunkID(buf,0,len) &&
	    "BLTD" != GetHunkID(buf,0,len) ) {
		delete[] buf;
		return -3;
	}

	//amos_sp_bank[bank_nr].DelAll();
	long bob_num = GetWord(buf,4,len);
	if( 0 == bob_num ) {
		delete[] buf;
		return 0;	//nie ma obrazkow
	}

	long pos = 6;
	AmosImg *images[bob_num];
	for( int i=0; i < bob_num; ++i ) {
		images[i] = new AmosImg();
		images[i]->w = GetWord(buf,pos,len); pos += 2;
		images[i]->h = GetWord(buf,pos,len); pos += 2;
		images[i]->d = GetWord(buf,pos,len); pos += 2;
		images[i]->hsx = GetWord(buf,pos,len); pos += 2;
		images[i]->hsy = GetWord(buf,pos,len); pos += 2;
		images[i]->bpls = buf + pos;
		pos += images[i]->w * 2 * images[i]->h * images[i]->d;
	}

	unsigned long pal[256];
	for( int i=0; i<32; ++i ) {
		pal[i] = GetWord(buf,pos,len); pos += 2;
		pal[i+32] = (((pal[i] & 0x0f00) / 2) & 0x0f00) | (((pal[i] & 0x00f0) / 2) & 0x00f0) | (((pal[i] & 0x000f) / 2) & 0x000f);
	}

	Gfx::PTex *ptex;
	Gfx::LTex *ltex;
	float hsx,hsy;
	int inr = amos_sp_bank[bank_nr].CountLTex();
	for( int i=0; i < bob_num; ++i ) {
		ptex = images[i]->Conv2Tex(pal);
		if( 0 != ptex ) {
			amos_sp_bank[bank_nr].AddPTex(toString(inr+i+1),ptex);
			ltex = new Gfx::LTex(ptex);
			hsx = images[i]->hsx; hsx /= images[i]->w * 16;
			hsy = images[i]->hsy; hsy /= images[i]->h;
			ltex->SetHotSpot( hsx, hsy );
			amos_sp_bank[bank_nr].AddLTex(toString(inr+i+1),ltex);
			amos_sp_xscale[inr+i+1]=1.0;
			amos_sp_yscale[inr+i+1]=1.0;
		}
		delete images[i];
	}

	delete[] buf;

	act_sp_bank = bank_nr;
	return bob_num;
}
void _DemangleHunkIDs(unsigned char *buf,int len) {
	string id;
	long ln, pos=0;
	while( pos < len ) {
		id = GetHunkID(buf,pos,len);
		if( id == "RAWD" ) SetHunkID(buf,pos,len,"FORM");
		if( id == "RAWM" ) SetHunkID(buf,pos,len,"ILBM");
		if( id == "TRFF" ) SetHunkID(buf,pos,len,"BMHD");
		if( id == "PAMC" ) SetHunkID(buf,pos,len,"CMAP");
		if( id == "MGCA" ) SetHunkID(buf,pos,len,"CAMG");
		if( id == "BCCR" ) SetHunkID(buf,pos,len,"BODY");
		pos += 4;
		if( (id == "RAWM") || (id == "ILBM") ) goto dalej;	//po tym ID nie ma dlugosci
		ln = GetHunkLen(buf,pos,len);
		pos += 4;
		if( ln < 0 ) break;
		if( id != "RAWD" ) {
			if( ln % 2 == 1 ) ln+=1;
			pos += ln;	//przeskakujemy dane hunka, oczywiscie poza ROOTem, bo przeskoczymy plik ;-)
		}
		dalej: ;
	}
}
int LoadIff(const string& fname,int screen_nr) {

	SDL_Surface *image = 0, *rgba_img = 0;
	Uint32 dkey;

	FILE *file;
	file = fopen(fname.c_str(),"rb");
	if( 0 == file ) {
		return -1;
	}

	fseek(file,0,SEEK_END);
	long len;
	len = ftell(file);
	fseek(file,0,SEEK_SET);

	if( len <= 0 ) {
		fclose(file);
		return -2;
	}

	unsigned char *buf = new unsigned char[len];
	fread(buf,len,1,file);
	fclose(file);

	if( "RAWD" == GetHunkID(buf,0,len) ) {
		//plik jest w formacie IFF, ale jest "zmanglowany"
		_DemangleHunkIDs(buf,len);
	} else if( "RAWP" == GetHunkID(buf,0,len) ) {
		//plik jest w formacie PNG, ale jest "zmanglowany"
		buf[0] = 0x89;
		buf[1] = 'P';
		buf[2] = 'N';
		buf[3] = 'G';
	}

	SDL_RWops *rwop;
	rwop=SDL_RWFromMem(buf,len);
	if( 0 == rwop ) {
		delete[] buf;
		return -3;
	}

	image = (SDL_Surface *) IMG_Load_RW(rwop,0);
	SDL_FreeRW(rwop);
	delete[] buf;
	if( 0 == image ) {
		return -4;
	}

	if( screen_nr < 0 ) screen_nr = act_screen;
	if( 0 != pictures_pal[screen_nr] ) {
		SDL_FreeSurface(pictures_pal[screen_nr]);
	}
	pictures_pal[screen_nr] = image;

	//konwersja wczytanego obrazka do bytemapy RGBA
	Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000; gmask = 0x00ff0000; bmask = 0x0000ff00;	amask = 0x000000ff;
#else
	rmask = 0x000000ff;	gmask = 0x0000ff00;	bmask = 0x00ff0000;	amask = 0xff000000;
#endif
	rgba_img = SDL_CreateRGBSurface(SDL_SWSURFACE, image->w, image->h, 32, rmask, gmask, bmask, amask);

	//na rysunku docelowym wszystko jest przezroczyste :-)
	dkey = SDL_MapRGBA(rgba_img->format,	0, 0, 0, 255);
	SDL_FillRect(rgba_img, NULL, dkey);
	//na rysunku zrodlowym ustawiamy kolor przezroczysty

	SDL_SetAlpha(image,0,255);
	SDL_SetAlpha(rgba_img,0,255);

	//kopiujemy zrodlo do celu (przezroczystosc bedzie uwzgledniona)
	SDL_BlitSurface(image, 0, rgba_img, 0);
	//SDL_FreeSurface(image);		//nie zwalniamy bo jest zapisane jako pictures_pal[screen_nr]
	image = rgba_img;

	if( 0 != pictures[screen_nr] ) {
		SDL_FreeSurface(pictures[screen_nr]);
	}
	pictures[screen_nr] = image;

  pix[screen_nr].Set(image);

	return 1;
}
int LoadAbkMus(const string& fname,int bank_nr) {

	if( bank_nr < 0 || bank_nr > 15 ) return -1;

	unsigned char *abk = 0;
	long len;
	FILE *fin = fopen(fname.c_str(),"rb");
	if( 0==fin ) {
		return -1;
	}
	fseek(fin,0,SEEK_END);
	len=ftell(fin);
	fseek(fin,0,SEEK_SET);

	if( len <=0 ) {
		return -1;
	}

	abk = new unsigned char[len];
	fread(abk,1,len,fin);
	fclose(fin);

	unsigned char *mod;
	long mod_len;
	mod = convert_abk2mod(abk,len,mod_len);
	delete[] abk;
	if( mod == 0 ) {
		return -1;
	}

	FILE *fout = fopen("tmp.mod","wb");
	if( 0==fout ) {
		delete[] mod;
		return -1;
	}
	fwrite(mod,1,mod_len,fout);
	fclose(fout);

	delete[] mod;

	Mix_Music *mus = 0;

	mus = Mix_LoadMUS("tmp.mod");
	if( 0 == mus ) {
		return -1;
	}

	if( 0 != musics[bank_nr] ) {
		Mix_FreeMusic(musics[bank_nr]);
	}

	musics[bank_nr] = mus;

	return 1;
}
int LoadAbkSnd(const string& fname,int bank_nr) {
	if( bank_nr < 0 ) bank_nr = 4;

	FILE *f = fopen(fname.c_str(),"rb");
	if( 0 == f ) {
		return -1;
	}
	fseek(f,0,SEEK_END);
	long len;
	len = ftell(f);
	fseek(f,0,SEEK_SET);

	if( len <= 0 ) {
		fclose(f);
		return -2;
	}

	unsigned char *buf = new unsigned char[len];
	fread(buf,len,1,f);
	fclose(f);

	if( "AmBk" != GetHunkID(buf,0,len) &&
	    "Smpl" != GetHunkID(buf,0,len) ) {
		delete[] buf;
		return -3;
	}

	unsigned char *b = buf;

	//amos_sam_bank[bank_nr].DelAll();
	b += 20;	//skip amos bank header
	long sam_num = GetWord(b,0,len);
	if( 0 == sam_num ) {
		delete[] buf;
		return 0;	//nie ma sampli
	}

	long pos = 2;
	long offs[sam_num];
	for( int i=0; i < sam_num; ++i ) {
		offs[i] = GetLong(b,pos,len); pos += 4;
	}

	Sfx::PSam *psam;
	Sfx::LSam *lsam;
	Mix_Chunk *sdl_sample;
	int inr = amos_sam_bank[bank_nr].CountLSam();
	int freq, sam_len;
	for( int i=0; i < sam_num; ++i ) {
		//pobieramy info o samplu
		freq = GetWord(b,offs[i]+8,len);
		sam_len = GetLong(b,offs[i]+10,len);
		INFO("Sample[" + toString(i) + "] freq=" + toString(freq) + " len=" + toString(sam_len));
		sdl_sample = convert_sam2mixchunk(b+offs[i]+14,sam_len,freq);
		if( 0 != sdl_sample ) {
			psam = new Sfx::PSam();
			psam->Set(sdl_sample);
			lsam = new Sfx::LSam(psam);
			amos_sam_bank[bank_nr].AddPSam(toString(inr+i+1),psam);
			amos_sam_bank[bank_nr].AddLSam(toString(inr+i+1),lsam);
		}
	}

	delete[] buf;

	ii_act_sam_bank = bank_nr;
	return sam_num;
}
int LoadTrack(const string& fname,int bank_nr) {

	if( bank_nr < 0 || bank_nr > 15 ) return -1;

	Mix_Music *mus = 0;

	mus = Mix_LoadMUS(fname.c_str());
	if( 0 == mus ) {
		return -1;
	}

	if( 0 != musics[bank_nr] ) {
		Mix_FreeMusic(musics[bank_nr]);
	}

	musics[bank_nr] = mus;

	return 1;
}

int _IffWidth(int scr) {
	if( scr < 0 ) scr = act_screen;
	if( scr < 0 || scr >= 16 ) return 0;
	if( pictures[scr] == 0 ) return 0;
	return pictures[scr]->w;
}
int _IffHeight(int scr) {
	if( scr < 0 ) scr = act_screen;
	if( scr < 0 || scr >= 16 ) return 0;
	if( pictures[scr] == 0 ) return 0;
	return pictures[scr]->h;
}

void TrackLoop(bool onoff) {
	ib_track_loop = onoff;
}
void TrackPlay(int nr) {
	if( 0 == musics[nr] ) return;
	Mix_VolumeMusic(SDL_MIX_MAXVOLUME);
	int cnt;
	if( ib_track_loop ) cnt = -1; else cnt = 1;
	Mix_PlayMusic(musics[nr],cnt);
	ii_track_playing = nr;
}
void TrackFade(int speed) {
	if( speed <= 0 ) {
		Mix_HaltMusic();
	} else {
		Mix_FadeOutMusic( 63*20 / speed );
	}
	ii_track_playing = -1;
}
void TrackStop(void) {
	Mix_HaltMusic();
	ii_track_playing = -1;
}
void Mvolume(int vol) {
	Mix_VolumeMusic(SDL_MIX_MAXVOLUME*vol/64);
}
void Music(int mus) {
	if( 0 == musics[3] ) return;	//muzyka zawsze w banku nr 3
	Mix_VolumeMusic(SDL_MIX_MAXVOLUME);
	int cnt = -1;
	Mix_PlayMusic(musics[3],cnt);
	ii_track_playing = 3;
}
void MusicStop(void) {
	Mix_HaltMusic();
	ii_track_playing = -1;
}
void SamBank(int bnr) {
	ii_act_sam_bank = bnr;
}
void SamLoop(bool onoff) {
	ib_sam_loop = onoff;
}
void SamPlay(int snr) {
	if( ii_act_sam_bank < 0 || ii_act_sam_bank >= 16) return;
	Sfx::LSam *sam = 0;
	sam = amos_sam_bank[ii_act_sam_bank].GetLSam(toString(snr));
	if( 0 != sam ) {
		if( ib_sam_loop )
			Sfx::PlaySample(sam,MIX_MAX_VOLUME*3/4,-1);
		else
			Sfx::PlaySample(sam,MIX_MAX_VOLUME*3/4,0);
	}
}
void SamStop(int snr) {
	Mix_HaltChannel(-1);
}

bool Exists(const string& fname) {
	FILE *f = fopen(fname.c_str(),"rb");
	if( 0 == f )
		return false;
	fclose(f);
	return true;
}
bool DirExists(const string& fname) {
//TODO bool DirExists(const string& fname) {
//	FILE *f = fopen(fname.c_str(),"rb");
//	if( 0 == f )
//		return false;
//	fclose(f);
	return true;
}

void ChangeMouse(int nr) {
//TODO void ChangeMouse(int nr) {
}
void LimitMouse(int x1,int y1,int x2,int y2) {
	il_mouse_min_x = x1;
	il_mouse_min_y = y1;
	il_mouse_max_x = x2;
	il_mouse_max_y = y2;
}
bool MouseClick(void) {
	ib_mouse_clicked_read = true;
	return ib_mouse_clicked;
}
int XMouse(void) {
	return il_mousex;
}
int YMouse(void) {
	return il_mousey;
}
int MouseKey(void) {
	if( ib_lmb ) return 1;
	if( ib_rmb ) return 2;
	return 0;
}
int XHard(int x) {
	return _GetXOffset(act_screen) + x*_GetXScale(act_screen);
}
int YHard(int y) {
	return _GetYOffset(act_screen) + y*_GetYScale(act_screen);
}
void SetXMouse(int x) {
	//TODO !@# void SetXMouse(int x) {
}
void SetYMouse(int y) {
	//TODO !@# void SetYMouse(int y) {
}


int SetFont(const string& id,const string& fname,int siz,bool pb_antialiasing) {
	LOG("Begin <"+id+"> <"+fname+"> "+toString(siz)+" act_screen="+toString(act_screen));
	if( act_screen < 0 ) return -1;

	int li_ret;
	Gfx::Font *font = ic_font_mgr.Get(id,siz);
	if( 0 == font ) {
		LOG("  Not found... Loading");
		//nie zaladowano jeszcze takiego fontu
		font = new Gfx::Font();
		font->SetAntialiasing(pb_antialiasing);
		li_ret = font->Load(fname,siz);
		if( li_ret < 0 ) {
			LOG("  Load error");
			delete font;
			return -1;
		}
		ic_font_mgr.Add(id,siz,font);
		font_cnt++;
		font_tab[font_cnt] = font;
		font_siz[font_cnt] = siz;
		screens[act_screen].act_font = font_cnt;
		screens[act_screen].act_font_siz = siz;
		LOG("End1");
		return font_cnt;
	} else {
		for( int idx = 0; idx < 1024; ++idx ) {
			if( font_tab[idx] == font ) {
				screens[act_screen].act_font = idx;
				screens[act_screen].act_font_siz = font_siz[font_cnt];
				LOG("End2 idx="+toString(idx));
				return idx;
			}
		}
	}
	LOG("End3 - error");
	return -1;
}
int SetFont(int nr) {
	LOG("Begin act_screen="+toString(act_screen));
	if( nr < 0 || nr >= 1024 ) return -1;
	if( act_screen < 0 ) return -1;
	screens[act_screen].act_font = nr;
	screens[act_screen].act_font_siz = font_siz[nr];
	LOG("End");
	return nr;
}

void Text(int x,int y,const string& s) {
	Text(x,y,s,1.0f);
}
void Text(int x,int y,const string& s,float scale) {
	if( act_screen < 0 || act_screen >= 16 ) { LOG("Bad act_screen"); return; }
	Gfx::Font *font;
	if( screens[act_screen].act_font < 0 || screens[act_screen].act_font >= 1024 ) { LOG("Bad act_font: screen="+toString(act_screen)); return; }

	font = font_tab[screens[act_screen].act_font];
	if( 0 == font ) { LOG("No font"); return; }

	x *= _GetXScale(act_screen);
	x += _GetXOffset(act_screen);
	y *= _GetYScale(act_screen);
	y += _GetYOffset(act_screen);

	Gfx::Text(font,s,x,y,screens[act_screen].act_font_siz*_GetXScale(act_screen)*scale,screens[act_screen].act_font_siz*_GetYScale(act_screen)*scale);
}
void DbgRenderFont(void) {
	if( act_screen < 0 || act_screen >= 16 ) { LOG("Bad act_screen"); return; }
	Gfx::Font *font;
	if( screens[act_screen].act_font < 0 || screens[act_screen].act_font >= 1024 ) { LOG("Bad act_font: screen="+toString(act_screen)); return; }
	font = font_tab[screens[act_screen].act_font];
	if( 0 == font ) { LOG("No font"); return; }
	Gfx::_render_font(font);
}
int TextLength(const string& s) {
	if( act_screen < 0 || act_screen >= 16 ) { LOG("Bad act_screen"); return 0; }
	Gfx::Font *font;
	if( screens[act_screen].act_font < 0 || screens[act_screen].act_font >= 1024 ) { LOG("Bad act_font: screen="+toString(act_screen)); return 0; }

	font = font_tab[screens[act_screen].act_font];
	if( 0 == font ) { LOG("No font"); return 0; }

	int ret=(int)Gfx::TextLength(font,s,screens[act_screen].act_font_siz);
	return ret;
}
int TextBase(void) {
	if( act_screen < 0 ) return 0;
	return (screens[act_screen].act_font_siz * 2) / 3 ;
}
void _Bar(int x1,int y1,int x2,int y2) {
	if( act_screen < 0 || act_screen >= 16 ) return;
	x1 = x1 * _GetXScale(act_screen) + _GetXOffset(act_screen);
	y1 = y1 * _GetYScale(act_screen) + _GetYOffset(act_screen);
	x2 = x2 * _GetXScale(act_screen) + _GetXOffset(act_screen);
	y2 = y2 * _GetYScale(act_screen) + _GetYOffset(act_screen);
	Gfx::Bar(x1,y1,x2,y2);
}
void _Box(int x1,int y1,int x2,int y2) {
	if( act_screen < 0 || act_screen >= 16 ) return;
	x1 = x1 * _GetXScale(act_screen) + _GetXOffset(act_screen);
	y1 = y1 * _GetYScale(act_screen) + _GetYOffset(act_screen);
	x2 = x2 * _GetXScale(act_screen) + _GetXOffset(act_screen);
	y2 = y2 * _GetYScale(act_screen) + _GetYOffset(act_screen);
	Gfx::Box(x1,y1,x2,y2);

	bool lb_draw = false;
	if( _GetXScale(act_screen) > 1 ) {
		++x1; ++x2;
		lb_draw = true;
	}
	if( _GetYScale(act_screen) > 1 ) {
		++y1; ++y2;
		lb_draw = true;
	}
	if( lb_draw )
		Gfx::Box(x1,y1,x2,y2);
}
void _Rainbow(int x1,int y1,int x2,int y2,float *rb,int rows) {
	if( act_screen < 0 || act_screen >= 16 ) return;
	x1 = x1 * _GetXScale(act_screen) + _GetXOffset(act_screen);
	y1 = y1 * _GetYScale(act_screen) + _GetYOffset(act_screen);
	x2 = x2 * _GetXScale(act_screen) + _GetXOffset(act_screen);
	y2 = y2 * _GetYScale(act_screen) + _GetYOffset(act_screen);
	Gfx::Rainbow(x1,y1,x2,y2,rb,rows);
}
void _Line(int x1,int y1,int x2,int y2) {
	if( act_screen < 0 || act_screen >= 16 ) return;
	x1 = x1 * _GetXScale(act_screen) + _GetXOffset(act_screen);
	y1 = y1 * _GetYScale(act_screen) + _GetYOffset(act_screen);
	x2 = x2 * _GetXScale(act_screen) + _GetXOffset(act_screen);
	y2 = y2 * _GetYScale(act_screen) + _GetYOffset(act_screen);
	Gfx::Line(x1,y1,x2,y2);

	bool lb_draw = false;
	if( _GetXScale(act_screen) > 1 ) {
		++x1; ++x2;
		lb_draw = true;
	}
	if( _GetYScale(act_screen) > 1 ) {
		++y1; ++y2;
		lb_draw = true;
	}
	if( lb_draw )
		Gfx::Line(x1,y1,x2,y2);
}
void _Draw(int x1,int y1,int x2,int y2) {
	_Line(x1,y1,x2,y2);
}
void Clip(void) {
	//TODO !@# void Clip(void) {
}
void Clip(int x1,int y1,int x2,int y2) {
	//TODO !@# void Clip(int x1,int y1,int x2,int y2) {
}

void Fade(float intense) {
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	Gfx::Color(0.0f,0.0f,0.0f,intense);
	Bar(0,0,DISPLAY_WIDTH,DISPLAY_HEIGHT);

	glDisable(GL_BLEND);
}

class Zone {
public:
	int x1,y1,x2,y2;
	Zone(void) : x1(-1), y1(-1), x2(-2), y2(-2) {}
	Zone(int p_x1,int p_y1,int p_x2,int p_y2) {
		Set(p_x1,p_y1,p_x2,p_y2);
	}
	void Clear(void) {
		x1=-1; y1=-1; x2=-2; y2=-2;
	}
	void Set(int p_x1,int p_y1,int p_x2,int p_y2) {
		x1=p_x1;
		y1=p_y1;
		x2=p_x2;
		y2=p_y2;
	}
	bool Test(int x,int y) {
		if( x >= x1 && x <= x2 && y >= y1 && y <= y2 ) return true;
		return false;
	}
	Zone& operator=(const Zone& z) {
		x1 = z.x1;
		y1 = z.y1;
		x2 = z.x2;
		y2 = z.y2;
		return *this;
	}
};


vector<Zone> zones[16];

void ReserveZone(int cnt) {
	if( act_screen < 0 || act_screen >= 16 ) return;
	zones[act_screen].reserve(cnt+1);
	while( (int)zones[act_screen].size() < cnt + 1 )
		zones[act_screen].push_back(Zone());
	for( int i=1; i<(int)zones[act_screen].size(); ++i )
		zones[act_screen][i].Clear();
}
void SetZone(int nr,int x1,int y1,int x2,int y2) {
	if( act_screen < 0 || act_screen >= 16 ) return;
	zones[act_screen][nr].Set(x1,y1,x2,y2);
}
void ResetZone(int nr) {
	if( act_screen < 0 || act_screen >= 16 ) return;
	if( nr >= 0 )
		zones[act_screen][nr].Clear();
	else {
		for(int i=1; i<(int)zones[act_screen].size(); ++i )
			zones[act_screen][i].Clear();
	}
}
int _GetZone(int x,int y) {
	if( act_screen < 0 || act_screen >= 16 ) return 0;
	for( int i=1; i<(int)zones[act_screen].size(); ++i )
		if( zones[act_screen][i].Test(x,y) ) return i;
	return 0;
}
int _Zone(int x,int y) {
	return _GetZone(x,y);
}
int MouseZone(void) {
	return _GetZone(XScreen(il_mousex),YScreen(il_mousey));
}

void DbgDrawZones(int scr) {
	if( scr < 0 || scr >= 16 ) return;
	int screen = Screen();
	Screen(scr);
	if( scr==0 )
		Gfx::Color(1.0f,1.0f,1.0f);
	else if( scr==1 )
		Gfx::Color(1.0f,0.5f,0.5f);
	else
		Gfx::Color(0.5f,1.0f,0.5f);
	for( int i=1; i<(int)zones[scr].size(); ++i ) {
		_Box(zones[scr][i].x1,zones[scr][i].y1,zones[scr][i].x2,zones[scr][i].y2);
	}
	Screen(screen);
}

void ClearKey(void) {
	while( key_buf.size() > 0 )
		key_buf.pop();
	while( keymod_buf.size() > 0 )
		keymod_buf.pop();
}
static int last_key=0;
static short last_keymod=0;
void _get_key(int &key,unsigned short &mod) {
	if( key_buf.size() <= 0 ) {
		key = 0;
		mod = 0;
		last_key = 0;
		last_keymod = 0;
		return;
	}
	key = key_buf.front(); key_buf.pop();
	mod = keymod_buf.front(); keymod_buf.pop();
	last_key = key;
	last_keymod = mod;
}
string Inkey_S(void) {
	int key;
	unsigned short mod;
	string s="";
	_get_key(key,mod);
	if( 0 == key ) return s;
	if( key < 32 || key > 255 ) return s;
	s = Chr_S(key);
	if( mod & KMOD_SHIFT ) {
		s = Upper_S(s);
	}
	if( mod & KMOD_ALT ) {
		switch( s.c_str()[0] ) {
			case 'A': s="¥"; break;
			case 'C': s="Æ"; break;
			case 'E': s="Ê"; break;
			case 'L': s="£"; break;
			case 'N': s="Ñ"; break;
			case 'O': s="Ó"; break;
			case 'S': s=""; break;
			case 'Z': s="¯"; break;
			case 'X': s=""; break;

			case 'a': s="¹"; break;
			case 'c': s="æ"; break;
			case 'e': s="ê"; break;
			case 'l': s="³"; break;
			case 'n': s="ñ"; break;
			case 'o': s="ó"; break;
			case 's': s=""; break;
			case 'z': s="¿"; break;
			case 'x': s=""; break;
		}
	}
	return s;
}
int _keysym2scancode(int key) {
	switch(key) {
		case SDLK_UP:			return 76;
		case SDLK_DOWN:		return 77;
		case SDLK_RIGHT:	return 78;
		case SDLK_LEFT:		return 79;
		case SDLK_F1:			return 80;
		case SDLK_F2:			return 81;
		case SDLK_F3:			return 82;
		case SDLK_F4:			return 83;
		case SDLK_F5:			return 84;
		case SDLK_F6:			return 85;
		case SDLK_F7:			return 86;
		case SDLK_F8:			return 87;
		case SDLK_F9:			return 88;
		case SDLK_F10:		return 89;
		case SDLK_ESCAPE:	return 69;
		case SDLK_BACKSPACE:	return 65;
		case SDLK_RETURN:	return 68;

		case SDLK_F11:		return 1000+90;
		case SDLK_F12:		return 1000+91;
	}
	return 0;
}
int _scancode2keysym(int sc) {
	switch(sc) {
		case 76:	return SDLK_UP;
		case 77:	return SDLK_DOWN;
		case 78:	return SDLK_RIGHT;
		case 79:	return SDLK_LEFT;
		case 80:	return SDLK_F1;
		case 81:	return SDLK_F2;
		case 82:	return SDLK_F3;
		case 83:	return SDLK_F4;
		case 84:	return SDLK_F5;
		case 85:	return SDLK_F6;
		case 86:	return SDLK_F7;
		case 87:	return SDLK_F8;
		case 88:	return SDLK_F9;
		case 89:	return SDLK_F10;
		case 69:	return SDLK_ESCAPE;
		case 65:	return SDLK_BACKSPACE;
		case 68:	return SDLK_RETURN;

		case 1090:	return SDLK_F11;
		case 1091:	return SDLK_F12;
	}
	return 0;
}
int ScanCode(void) {
	return _keysym2scancode(last_key);
}
int KeyState(int sc) {
	return key_state[_scancode2keysym(sc)];
}
string Chr_S(int i) {
	char buf[2];
	buf[0]=(char)i;
	buf[1]=0;
	return string(buf);
}
string Str_S(int i) {
	if( i <= 0 )
		return toString(i);
	else
		return " " + toString(i);	//amos liczby dodatnie poprzedza spacja
}
int Asc(const string& str) {
	if(str.size()>0)
		return str[0];
	return 0;
}
int Len(const string& str) {
	return str.size();
}
string Left_S(const string& str,aint cnt) {
	return str.substr(0,cnt);
}
string Right_S(const string& str,aint cnt) {
	return str.substr(str.size()-cnt,cnt);
}
string Mid_S(const string& str,aint pos,aint cnt) {
	return str.substr(pos-1,cnt);
}
string Upper_S(const string& str) {
	string s="";
	for( int i=0; i<(int)str.size(); ++i )
		s += (char)(toupper( str[i] ));
	return s;
}
string Minus_S(const string& str1,const string& str2) {
	string s=str1;
	string::size_type i;
	while( (i=s.find(str2,0)) != string::npos ) {
		s.erase(i,str2.length());
	}
	return s;
}
int Instr(const string& str,const string& pat) {
	return str.find(pat);
}
int Val(const string& str) {
	return atol(str.c_str());
}
int Rnd(int b) {
	return Core::Randi(b);
}

int Sgn(int x) {
	if( x<0 ) return -1;
	if( x>0 ) return 1;
	return 0;
}
float Sgn(float x) {
	if( x<0.0 ) return -1.0;
	if( x>0.0 ) return 1.0;
	return 0.0;
}
int Abs(int x) {
	if( x<0 ) return -x;
	return x;
}
float Abs(float x) {
	if( x<0.0 ) return -x;
	return x;
}
int Sqr(int x) {
	return (int)sqrt(x);
}
float Sqr(float x) {
	return sqrt(x);
}


int Peek(unsigned char *adr) {
	unsigned long data;
	data = adr[0];
	return data;
}
int Deek(unsigned char *adr) {
	unsigned long data;
	data = adr[0];
	data *= 256;
	data += adr[1];
	return data;
}
int Leek(unsigned char *adr) {
	unsigned long data;
	data = adr[0];
	data *= 256;
	data += adr[1];
	data *= 256;
	data += adr[2];
	data *= 256;
	data += adr[3];
	return data;
}
string Peek_S(unsigned char *adr,int len) {
	string s="";
	for( long i=0; i<len; ++i ) {
		s += adr[i];
	}
	return s;
}

void Poke(unsigned char *adr,int data) {
	unsigned long d = data;
	adr[0] = (unsigned char)d;
}
void Doke(unsigned char *adr,int data) {
	unsigned long d = data;
	adr[0] = (unsigned char)((d/256)&0xff);
	adr[1] = (unsigned char)(d&0xff);
}
void Loke(unsigned char *adr,int data) {
	unsigned long d = data;
	adr[0] = (unsigned char)((d/(256*256*256))&0xff);
	adr[1] = (unsigned char)((d/(256*256))&0xff);
	adr[2] = (unsigned char)((d/256)&0xff);
	adr[3] = (unsigned char)(d&0xff);
}
void Poke_S(unsigned char *adr,string data) {
	int len=data.length();
	for( long i=0; i<len; ++i ) {
		adr[i] = data[i];
	}
}


void _ClearRaster(void) {
	_clip_off();
	Gfx::Cls();
	_clip_on();
}
void _ClearRaster(float x1,float y1,float x2,float y2) {
	_clip_off();
	Gfx::Bar(x1,y1,x2,y2);
	_clip_on();
}

void* ReserveBuffer(int x,int y,int w,int h) {
	if( act_screen < 0 || act_screen >= 16 ) return 0;
	x = x * _GetXScale(act_screen) + _GetXOffset(act_screen);
	y = y * _GetYScale(act_screen) + _GetYOffset(act_screen);
	w = w * _GetXScale(act_screen);
	h = h * _GetYScale(act_screen);

	CStoreBuffer *sb = new CStoreBuffer(x,y,w,h);
	return (void*)sb;
}
void* StoreBuffer(int x,int y,int w,int h) {
	void *s = ReserveBuffer(x,y,w,h);
	if( 0 == s ) return 0;
	CStoreBuffer *sb = (CStoreBuffer*)s;
	sb->Store();
	return sb;
}
void StoreBuffer(void *s,int x,int y,int w,int h) {
	if( 0 == s ) return;
	if( act_screen < 0 || act_screen >= 16 ) return;
	x = x * _GetXScale(act_screen) + _GetXOffset(act_screen);
	y = y * _GetYScale(act_screen) + _GetYOffset(act_screen);
	w = w * _GetXScale(act_screen);
	h = h * _GetYScale(act_screen);

	CStoreBuffer *sb = (CStoreBuffer*)s;
	sb->Store(x,y,w,h);
	return;
}
void RestoreBuffer(void *s) {
	if( 0 == s ) return;
	CStoreBuffer *sb = (CStoreBuffer*)s;
	sb->Restore();
}
void FreeBuffer(void *s) {
	if( 0 == s ) return;
	CStoreBuffer *sb = (CStoreBuffer*)s;
	delete sb;
}
void WriteBuffer2File(void *s,const string& filename) {
	if( 0 == s ) return;
	CStoreBuffer *sb = (CStoreBuffer*)s;
	Pic pic;
	pic.Set((unsigned char*)(sb->buf),sb->ww,sb->hh,Gfx::PDM_RGBA);
	pic.SavePNG(filename);
}


static unsigned char *buf_ptr=0;
static int buf_w=0, buf_h=0;
static unsigned char buf_col_r=0, buf_col_g=0, buf_col_b=0, buf_col_a=255;
void _BufSet(unsigned char *buf,int w,int h) {
	buf_ptr = buf;
	buf_w = w;
	buf_h = h;
	for( int i=w*h*4; i>0; i-=4 ) {
		*(buf++) = buf_col_r;
		*(buf++) = buf_col_g;
		*(buf++) = buf_col_b;
		*(buf++) = buf_col_a;
	}
}
void _BufColor(float r,float g,float b,float a) {
	buf_col_r = (unsigned char)(r * 255.0);
	buf_col_g = (unsigned char)(g * 255.0);
	buf_col_b = (unsigned char)(b * 255.0);
	buf_col_a = (unsigned char)(a * 255.0);
}
void _BufPlot(float x,float y) {
	if( 0==buf_ptr )
		return;
	int li_x=(int)x, li_y=(int)y;
	if( li_x<0 || li_x>=buf_w || li_y<0 || li_y>=buf_h )
		return;
	unsigned char *b=buf_ptr + (li_x+li_y*buf_w)*4;
	b[0] = buf_col_r;
	b[1] = buf_col_g;
	b[2] = buf_col_b;
	b[3] = buf_col_a;
	return;
}

void _ShowCursor(bool vis) {
	Core::ShowMouseCursor(vis);
}
