
#include <SDL/SDL.h>

#include "Events.h"

namespace Core {
	
extern void _CoreResizeEvent(int w,int h);

//wskazniki na funkcjê, ktore beda wolane w przypadku zdarzenia
static QuitEvent						ifp_quit = 0;
static KeyDownEvent					ifp_keydown = 0;
static KeyUpEvent						ifp_keyup = 0;
static MouseButtonDownEvent	ifp_mousebuttondown = 0;
static MouseButtonUpEvent		ifp_mousebuttonup = 0;
static MouseMotionEvent			ifp_mousemotion = 0;
static ResizeEvent					ifp_resize = 0;

//wskazniki na dane programisty (przekazywane spowrotem do zarejestrowanych funkcji obslugi)
static UserData iud_quit = 0
			 				, iud_keydown = 0
			 				, iud_keyup = 0
			 				, iud_mousebuttondown = 0
							, iud_mousebuttonup = 0
							, iud_mousemotion = 0
							, iud_resize = 0;

#define REG_EVENT(TYPE,FPTR,UDATA)\
	TYPE Register##TYPE( TYPE e, UserData udata ) {\
		TYPE pe = FPTR;\
		FPTR = e;\
		UDATA = udata;\
		return pe;\
	}

REG_EVENT(QuitEvent,ifp_quit,iud_quit)
REG_EVENT(KeyDownEvent,ifp_keydown,iud_keydown)
REG_EVENT(KeyUpEvent,ifp_keyup,iud_keyup)
REG_EVENT(MouseButtonDownEvent,ifp_mousebuttondown,iud_mousebuttondown)
REG_EVENT(MouseButtonUpEvent,ifp_mousebuttonup,iud_mousebuttonup)
REG_EVENT(MouseMotionEvent,ifp_mousemotion,iud_mousemotion)
REG_EVENT(ResizeEvent,ifp_resize,iud_resize)

bool ProcessEvents(void) {
	SDL_Event event;
	bool ib_quit = false;
	
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			
			case SDL_QUIT:
				ib_quit = true;
				if( ifp_quit ) ifp_quit(iud_quit);				//wolamy funkcje obslugi zdarzenia
				break;
				
			case SDL_KEYDOWN:
				if( ifp_keydown) ifp_keydown(event.key.keysym.sym,iud_keydown);		//wolamy funkcje obslugi zdarzenia
				break;

			case SDL_KEYUP:
				if( ifp_keyup) ifp_keyup(event.key.keysym.sym,iud_keyup);					//wolamy funkcje obslugi zdarzenia
				break;
				
			case SDL_MOUSEBUTTONDOWN:
				if( ifp_mousebuttondown ) ifp_mousebuttondown(event.button.button,event.button.x,event.button.y,iud_mousebuttondown);					//wolamy funkcje obslugi zdarzenia
				break;
				
			case SDL_MOUSEBUTTONUP:
				if( ifp_mousebuttonup ) ifp_mousebuttonup(event.button.button,event.button.x,event.button.y,iud_mousebuttonup);					//wolamy funkcje obslugi zdarzenia
				break;

			case SDL_MOUSEMOTION:
				if( ifp_mousemotion ) ifp_mousemotion(event.motion.x,event.motion.y,event.motion.xrel,event.motion.yrel,iud_mousemotion);					//wolamy funkcje obslugi zdarzenia
				break;

			case SDL_VIDEORESIZE:
				_CoreResizeEvent(event.resize.w,event.resize.h);
				if( ifp_resize ) ifp_resize(event.resize.w,event.resize.h,iud_resize);					//wolamy funkcje obslugi zdarzenia
				break;

			default:
				break;

		}
	}
	
	return ib_quit;
}



int MouseX(void) {
	int x;
	SDL_GetMouseState(&x,0);
	return x;
}
int MouseY(void) {
	int y;
	SDL_GetMouseState(0,&y);
	return y;
}
int MouseXRel(void) {
	int x;
	SDL_GetRelativeMouseState(&x,0);
	return x;
}
int MouseYRel(void) {
	int y;
	SDL_GetRelativeMouseState(0,&y);
	return y;
}
bool MouseLeftButton(void) {
	return 0 != (SDL_GetMouseState(0,0) & SDL_BUTTON_LMASK);
}
bool MouseMiddleButton(void) {
	return 0 != (SDL_GetMouseState(0,0) & SDL_BUTTON_MMASK);
}
bool MouseRightButton(void) {
	return 0 != (SDL_GetMouseState(0,0) & SDL_BUTTON_RMASK);
}
bool MouseButton(int nr) {
	return 0 != (SDL_GetMouseState(0,0) & SDL_BUTTON(nr));
}
unsigned short ModifiersState(void) {
	return SDL_GetModState();
}



}	//namespace Core
