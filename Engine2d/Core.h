#ifndef D_CORE_H_D
#define D_CORE_H_D

#include <string>

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

//ponizsze includy po to aby program korzystajacy z biblioteki nie musial bawic sie w szczegolowe
//wyliczanie includow
#include "Settings.h"
#include "Grid.h"
#include "Rand.h"
#include "Types.h"
#include "Events.h"

namespace Core {
	/// Czy podczas inicjacji Engine'a włączyć obsługę grafiki (domyślnie true)
	extern bool ib_gfx_enable;
	/// Czy podczas inicjacji Engine'a włączyć obsługę dzwięku (domyślnie true)
	extern bool ib_snd_enable;
	/// Szerokość ekranu (okna) otworzonego podczas inicjacji Engine'a (domyślnie 640)
	extern long il_screen_width;
	/// Wysokość ekranu (okna) otworzonego podczas inicjacji Engine'a (domyślnie 480)
	extern long il_screen_height;
	/// Czy ekran ma mieć podwójne buforowanie (domyślnie true)
	extern bool ib_double_buffer;
	/** Czy będziemy wykorzystywać bufor głębokości (domyślnie false)
	    Słowo wyjaśnienia: niby engine2d, a tu bufor głęnokości ?
	    1) Można bufor głębokości wykorzystać do nadania priorytetu Bob'om
	    2) Przyda się przy rzutowaniu izometrycznym
	    3) Gra wcale nie musi być 2d, chodzi tylko o to, że engine, na tym etapie rozwoju nie wpomaga 3d (ale wiele elementów jest wspólnych z 3d, np. ładownie tekstur, muzyka, ...)
	 */
	extern bool ib_zbuffer;
	/// Głębokość zbuffora. Wielkiego wyboru nie ma: 16 lub 24 (domyślnie 16)
	extern int ii_zbuffer_depth;
	/// Czy okno ma być otwarte w trybie fullscreen (domyślnie false)
	extern bool ib_full_screen;
	/// Czy okno może być rezizowane
	extern bool ib_resizable;

	/// Główny ekran (okno)
	extern SDL_Surface *screen;

	/// Nazwa głównego okna
	extern std::string is_screen_title;

	/// Mixer
	extern Mix_Music *sound;

	/// Inicjuje Engine, otwiera główne okno, mixer dzwięku, itp.
	int Init(void);

	/// Zamyka Engine
	int Finish(void);

	/// Funkcja służy do pomiaru czasu ramek (klatek animacji)
	int FrameTiming(int mode);

	/// Określają tryb wywołwania funkcji FrameTiming
	enum FT_MODES {
		/// Rozpoczynamy nową ramkę, zwróć czas właśnie zakończonej ramki
		FTM_NEW_FRAME				= 0
		/// Zwróć czas jaki upłynął od poczatku bieżącej ramki
	, FTM_FRAME_TIME			= 1
		/// Zwróć czas jaki upłynął od początku pierwszej ramki
	, FTM_ALL_FRAMES_TIME	= 2
		/// Zwróć surowe, nieprzetworzone ticki zegara
	, FTM_RAW_TICKS				= 3
	};

	/** Czeka tyle czasu, aby bieżąca ramka trwała podany jako parametr czas.<BR>
		@param frame_time zakładany czas trwania ramki
		@return ile czasu trzeba bylo poczekac (wartosci ujemne swiadczą o niewyrabianiu się animacji w założonym framerate)
	 */
	long FrameWait(Uint32 frame_time);

	/// Czeka wskazaną ilość milisekund (tysięcznych części sekundy)
	void Wait(long pl_milisec);

	/// Przerzuca bufory ekranu (o ile są dwa)
	void SwapBuffers(void);

	/** Ustawia rzutowanie swiata na ekran
	 @param minx - taka współrzędna świata przyporządkowana zostanie lewej krawędzi ekranu
	 @param maxx - taka współrzędna świata przyporządkowana zostanie prawej krawędzi ekranu
	 @param miny - taka współrzędna świata przyporządkowana zostanie dolnej krawędzi ekranu
	 @param maxy - taka współrzędna świata przyporządkowana zostanie górnej krawędzi ekranu
	 @param minz - taka współrzędna świata przyporządkowana zostanie płaszczyźnie ekranu
	 @param maxz - taka współrzędna świata przyporządkowana zostanie horyzontowi świata (dalej nic nie będzie widać)
	 */
	void ProjectionOrtho(GLfloat minx,GLfloat maxx,GLfloat miny,GLfloat maxy,GLfloat minz = 0.0,GLfloat maxz = 1.0);

	/// Ustawia rzutowanie swiata na ekran w ten sposob, ze jeden pixel to jedna jednosta miary swiata
	/// (równoważne: ProjectionOrtho(0,il_screen_width,il_screen_height,0,0,1);
	void ProjectionOrtho(void);

	/// Wyświetla lub chowa kursor myszy
	void ShowMouseCursor(bool visible);

};

#endif
