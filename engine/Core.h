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
	/// Czy podczas inicjacji Engine'a w³¹czyæ obs³ugê grafiki (domyœlnie true)
	extern bool ib_gfx_enable;
	/// Czy podczas inicjacji Engine'a w³¹czyæ obs³ugê dzwiêku (domyœlnie true)
	extern bool ib_snd_enable;
	/// Szerokoœæ ekranu (okna) otworzonego podczas inicjacji Engine'a (domyœlnie 640)
	extern long il_screen_width;
	/// Wysokoœæ ekranu (okna) otworzonego podczas inicjacji Engine'a (domyœlnie 480)
	extern long il_screen_height;
	/// Czy ekran ma mieæ podwójne buforowanie (domyœlnie true)
	extern bool ib_double_buffer;
	/** Czy bêdziemy wykorzystywaæ bufor g³êbokoœci (domyœlnie false)
	    S³owo wyjaœnienia: niby engine2d, a tu bufor g³ênokoœci ?
	    1) Mo¿na bufor g³êbokoœci wykorzystaæ do nadania priorytetu Bob'om
	    2) Przyda siê przy rzutowaniu izometrycznym
	    3) Gra wcale nie musi byæ 2d, chodzi tylko o to, ¿e engine, na tym etapie rozwoju nie wpomaga 3d (ale wiele elementów jest wspólnych z 3d, np. ³adownie tekstur, muzyka, ...)
	 */
	extern bool ib_zbuffer;
	/// G³êbokoœæ zbuffora. Wielkiego wyboru nie ma: 16 lub 24 (domyœlnie 16)
	extern int ii_zbuffer_depth;
	/// Czy okno ma byæ otwarte w trybie fullscreen (domyœlnie false)
	extern bool ib_full_screen;
	/// Czy okno mo¿e byæ rezizowane
	extern bool ib_resizable;

	/// G³ówny ekran (okno)
	extern SDL_Surface *screen;

	/// Nazwa g³ównego okna
	extern std::string is_screen_title;

	/// Mixer
	extern Mix_Music *sound;

	/// Inicjuje Engine, otwiera g³ówne okno, mixer dzwiêku, itp.
	int Init(void);

	/// Zamyka Engine
	int Finish(void);

	/// Funkcja s³u¿y do pomiaru czasu ramek (klatek animacji)
	int FrameTiming(int mode);

	/// Okreœlaj¹ tryb wywo³wania funkcji FrameTiming
	enum FT_MODES {
		/// Rozpoczynamy now¹ ramkê, zwróæ czas w³aœnie zakoñczonej ramki
		FTM_NEW_FRAME				= 0
		/// Zwróæ czas jaki up³yn¹³ od poczatku bie¿¹cej ramki
	, FTM_FRAME_TIME			= 1
		/// Zwróæ czas jaki up³yn¹³ od pocz¹tku pierwszej ramki
	, FTM_ALL_FRAMES_TIME	= 2
		/// Zwróæ surowe, nieprzetworzone ticki zegara
	, FTM_RAW_TICKS				= 3
	};

	/** Czeka tyle czasu, aby bie¿¹ca ramka trwa³a podany jako parametr czas.<BR>
		@param frame_time zak³adany czas trwania ramki
		@return ile czasu trzeba bylo poczekac (wartosci ujemne swiadcz¹ o niewyrabianiu siê animacji w za³o¿onym framerate)
	 */
	long FrameWait(Uint32 frame_time);

	/// Czeka wskazan¹ iloœæ milisekund (tysiêcznych czêœci sekundy)
	void Wait(long pl_milisec);

	/// Przerzuca bufory ekranu (o ile s¹ dwa)
	void SwapBuffers(void);

	/** Ustawia rzutowanie swiata na ekran
	 @param minx - taka wspó³rzêdna œwiata przyporz¹dkowana zostanie lewej krawêdzi ekranu
	 @param maxx - taka wspó³rzêdna œwiata przyporz¹dkowana zostanie prawej krawêdzi ekranu
	 @param miny - taka wspó³rzêdna œwiata przyporz¹dkowana zostanie dolnej krawêdzi ekranu
	 @param maxy - taka wspó³rzêdna œwiata przyporz¹dkowana zostanie górnej krawêdzi ekranu
	 @param minz - taka wspó³rzêdna œwiata przyporz¹dkowana zostanie p³aszczyŸnie ekranu
	 @param maxz - taka wspó³rzêdna œwiata przyporz¹dkowana zostanie horyzontowi œwiata (dalej nic nie bêdzie widaæ)
	 */
	void ProjectionOrtho(GLfloat minx,GLfloat maxx,GLfloat miny,GLfloat maxy,GLfloat minz = 0.0,GLfloat maxz = 1.0);

	/// Ustawia rzutowanie swiata na ekran w ten sposob, ze jeden pixel to jedna jednosta miary swiata
	/// (równowa¿ne: ProjectionOrtho(0,il_screen_width,il_screen_height,0,0,1);
	void ProjectionOrtho(void);

	/// Wyœwietla lub chowa kursor myszy
	void ShowMouseCursor(bool visible);

};

#endif
