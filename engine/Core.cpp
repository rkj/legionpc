
#include <iostream>

#include "Core.h"
#include "Utils.h"
#include "Bob.h"
#include "Collision.h"

namespace Core {

using namespace std;
using namespace Gfx;

bool ib_gfx_enable = true;
bool ib_snd_enable = true;
long il_screen_width = 640;
long il_screen_height = 480;
bool ib_double_buffer = true;
bool ib_zbuffer = false;
int ii_zbuffer_depth = 16;
bool ib_full_screen = false;
bool ib_resizable = false;

string is_screen_title = "Engine2d";
SDL_Surface *screen = 0;
Mix_Music *sound = 0;

Uint32 _ii_video_flags = 0;
int _ii_video_bpp = 0;

int Init(void) {

	  //////////////////////////
	 // Ogólna inicjalizacja //
	//////////////////////////
	unsigned long ll_mask = 0;
	if( ib_gfx_enable ) ll_mask |= SDL_INIT_VIDEO;
	if( ib_snd_enable ) ll_mask |= SDL_INIT_AUDIO;
	if(SDL_Init(ll_mask) < 0) {
		ERROR("Video initialization failed: " + SDL_GetError());
		exit(-1);
	}

	atexit(SDL_Quit);


	  ///////////////////
	 // Grafika, okno //
	///////////////////
	const SDL_VideoInfo* info = 0;
	int width = il_screen_width;
	int height = il_screen_height;
	int bpp = 0;
	Uint32 flags = 0;

	info = SDL_GetVideoInfo();
	bpp = info->vfmt->BitsPerPixel;

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);

	if( ib_zbuffer )
		SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, ii_zbuffer_depth );

	if( ib_double_buffer )
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	else
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 0);

	flags = SDL_OPENGL;
	if( ib_full_screen )
		flags |= SDL_FULLSCREEN;
	if( ib_resizable )
		flags |= SDL_RESIZABLE;

	//zapamietujemy parametry na potrzeby zdarzenia RESIZE
	_ii_video_bpp = bpp;
	_ii_video_flags = flags;

	if((screen = SDL_SetVideoMode(width, height, bpp, flags)) == 0) {
		ERROR("Video mode set failed: " + SDL_GetError());
    exit(-1);
	}

	SDL_WM_SetCaption(is_screen_title.c_str(), NULL);

	if( ib_zbuffer )
		glEnable(GL_DEPTH);
	else
		glDisable(GL_DEPTH);

	//ustawiamy domyslne rzutowanie swiata na ekran
	ProjectionOrtho();


	  /////////////////////
	 // Dzwiêki, muzyka //
	/////////////////////
//	int audio_rate,audio_channels
	int	audio_buffers=1024;
//	Uint16 audio_format;
//	Uint32 t;
//	int volume=SDL_MIX_MAXVOLUME;

	if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,audio_buffers)<0) {
		ERROR("Audio mixer failed: " + SDL_GetError());
    exit(-1);
	}


	  ////////////////
	 // Klawiatura //
	////////////////
	SDL_EnableKeyRepeat(0,0);

	return 1;
}

int Finish(void) {
	SDL_Quit();
	return 1;
}

void _CoreResizeEvent(int w,int h) {
//	Uint32 flags = _ii_video_flags;
//	if((screen = SDL_SetVideoMode(w, h, _ii_video_bpp, flags)) == 0) {
//		ERROR("Video mode set failed: " + SDL_GetError());
//    exit(-1);
//	}
	il_screen_width = w;
	il_screen_height = h;
}

//Obsluga czasow ramek
int FrameTiming(int mode) {
	Uint32 current, interval;
	static Uint32 first = 0, last = 0, five = 0, nframes = 0;
	static long last_col_test = 0;
	static bool first_call = true;

	current = SDL_GetTicks();
	switch( mode ) {
		case FTM_NEW_FRAME:
			nframes++;

			if( first_call ) {
				first_call = false;	//pierwszy raz mamy juz za soba
				first = current;
				last = current;
				five = current;
			}

			if (current - five > 5*1000) {
				INFO( toString( (unsigned long)nframes )
				    + " frames in 5 seconds = "
						+ toString( (float)nframes/5.0f,"%.1f" )
						+ " FPS  bobblits="
						+ toString( (unsigned long)Gfx::bobblit_cnt )
						+ " = "
						+ toString( (float)Gfx::bobblit_cnt/nframes,"%.1f")
						+ " BPF col_tests="
						+ toString( (unsigned long)(Fzx::collision_test_cnt - last_col_test) )
						+ " = "
						+ toString( (float)(Fzx::collision_test_cnt - last_col_test)/nframes,"%.1f" )
						+ " CTPF" );
				Gfx::bobblit_cnt = 0;
				last_col_test = Fzx::collision_test_cnt;
				nframes = 0;
				five = current;
			}

			interval = current - last;
			last = current;

			return interval;
		case FTM_FRAME_TIME:
			return current - last;
		case FTM_ALL_FRAMES_TIME:
			return current - first;
		case FTM_RAW_TICKS:
		default:
			return current;
	}
}

long FrameWait(Uint32 frame_time) {
	long interval;
	interval = frame_time - FrameTiming(Core::FTM_FRAME_TIME);
	if( interval > 0 ) {		//pozostalo troche czasu do zalozonego czasu ramki
		SDL_Delay(interval);
	}
	return interval;
}

void Wait(long pl_milisec) {
	SDL_Delay(pl_milisec);
}

void SwapBuffers(void) {
	BreakBobBlits();
	glFlush();							//oprozniamy kolejki OpenGL (czekamy az sie wszystko narysuje)
	SDL_GL_SwapBuffers();
}

void ProjectionOrtho(GLfloat minx,GLfloat maxx,GLfloat miny,GLfloat maxy,GLfloat minz,GLfloat maxz) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(minx,maxx,miny,maxy,minz,maxz);
	glMatrixMode(GL_MODELVIEW);
}

void ProjectionOrtho(void) {
	ProjectionOrtho(0, Core::il_screen_width, Core::il_screen_height, 0);
}

void ShowMouseCursor(bool visible) {
	if( visible ) {
		SDL_ShowCursor(SDL_ENABLE);
	} else {
		SDL_ShowCursor(SDL_DISABLE);
	}
}

}	//namespace Core
