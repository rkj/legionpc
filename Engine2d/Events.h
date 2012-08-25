#ifndef D_EVENTS_H_D
#define D_EVENTS_H_D

namespace Core {
	
	typedef void* UserData;
	typedef void (*QuitEvent)(UserData udata);
	typedef void (*KeyDownEvent)(int key,UserData udata);
	typedef void (*KeyUpEvent)(int key,UserData udata);
	typedef void (*MouseButtonDownEvent)(int button,int x,int y,UserData udata);
	typedef void (*MouseButtonUpEvent)(int button,int x,int y,UserData udata);
	typedef void (*MouseMotionEvent)(int x,int y,int xrel, int yrel,UserData udata);
	typedef void (*ResizeEvent)(int w,int h,UserData udata);

	/// Rejestruje funkcjê jako obs³ugê zdarzenia QUIT (zamkniêcie okna, aplikacji)
	QuitEvent RegisterQuitEvent( QuitEvent e, UserData udata = 0 );
	/// Rejestruje funkcjê jako obs³ugê zdarzenia KEYDOWN (wciœniêcia klawisza klawiatury)
	KeyDownEvent RegisterKeyDownEvent( KeyDownEvent e, UserData udata = 0 );
	/// Rejestruje funkcjê jako obs³ugê zdarzenia KEYUP (puszczenia klawisza klawiatury)
	KeyUpEvent RegisterKeyUpEvent( KeyUpEvent e, UserData udata = 0 );
	/// Rejestruje funkcjê jako obs³ugê zdarzenia MOUSE_BUTTON_DOWN (wciœniêcia klawisza myszy)
	MouseButtonDownEvent RegisterMouseButtonDownEvent( MouseButtonDownEvent e, UserData udata = 0 );
	/// Rejestruje funkcjê jako obs³ugê zdarzenia MOUSE_BUTTON_UP (puszczenia klawisza myszy)
	MouseButtonUpEvent RegisterMouseButtonUpEvent( MouseButtonUpEvent e, UserData udata = 0 );
	/// Rejestruje funkcjê jako obs³ugê zdarzenia MOUSE_MOTION (zmiany polozenia myszy)
	MouseMotionEvent RegisterMouseMotionEvent( MouseMotionEvent e, UserData udata = 0 );
	/// Rejestruje funkcjê jako obs³ugê zdarzenia VIDEORESIZE (zmiany rozmiaru okna)
	ResizeEvent RegisterResizeEvent( ResizeEvent e, UserData udata = 0 );
	
	/** Przetwarza kolejkê oczekuj¹cych zdarzeñ.
	 *  Je¿eli s¹ zarejestrowane jakieœ funkcjê obs³ugi zdarzeñ to bêd¹ one wywo³ane.
	 */
	bool ProcessEvents(void);

	/// Zwraca polozenie x myszy
	int MouseX(void);
	/// Zwraca polozenie y myszy
	int MouseY(void);
	/// Zwraca zmiane polozenia x myszy
	int MouseXRel(void);
	/// Zwraca zmiane polozenia y myszy
	int MouseYRel(void);
	/// Czy wcisniety jest lewy przycisk myszy
	bool MouseLeftButton(void);
	/// Czy wcisniety jest srodkowy przycisk myszy
	bool MouseMiddleButton(void);
	/// Czy wcisniety jest prawy przycisk myszy
	bool MouseRightButton(void);
	/// Czy wcisniety jest przycisk myszy o podanym numerze
	bool MouseButton(int nr);
	/// Zwraca stan klawiszy modyfikujacych (shifty, alty, ...)
	unsigned short ModifiersState(void);

}	//namespace Core

#endif
