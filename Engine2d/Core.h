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
	/// Czy podczas inicjacji Engine'a w��czy� obs�ug� grafiki (domy�lnie true)
	extern bool ib_gfx_enable;
	/// Czy podczas inicjacji Engine'a w��czy� obs�ug� dzwi�ku (domy�lnie true)
	extern bool ib_snd_enable;
	/// Szeroko�� ekranu (okna) otworzonego podczas inicjacji Engine'a (domy�lnie 640)
	extern long il_screen_width;
	/// Wysoko�� ekranu (okna) otworzonego podczas inicjacji Engine'a (domy�lnie 480)
	extern long il_screen_height;
	/// Czy ekran ma mie� podw�jne buforowanie (domy�lnie true)
	extern bool ib_double_buffer;
	/** Czy b�dziemy wykorzystywa� bufor g��boko�ci (domy�lnie false)
	    S�owo wyja�nienia: niby engine2d, a tu bufor g��noko�ci ?
	    1) Mo�na bufor g��boko�ci wykorzysta� do nadania priorytetu Bob'om
	    2) Przyda si� przy rzutowaniu izometrycznym
	    3) Gra wcale nie musi by� 2d, chodzi tylko o to, �e engine, na tym etapie rozwoju nie wpomaga 3d (ale wiele element�w jest wsp�lnych z 3d, np. �adownie tekstur, muzyka, ...)
	 */
	extern bool ib_zbuffer;
	/// G��boko�� zbuffora. Wielkiego wyboru nie ma: 16 lub 24 (domy�lnie 16)
	extern int ii_zbuffer_depth;
	/// Czy okno ma by� otwarte w trybie fullscreen (domy�lnie false)
	extern bool ib_full_screen;
	/// Czy okno mo�e by� rezizowane
	extern bool ib_resizable;

	/// G��wny ekran (okno)
	extern SDL_Surface *screen;

	/// Nazwa g��wnego okna
	extern std::string is_screen_title;

	/// Mixer
	extern Mix_Music *sound;

	/// Inicjuje Engine, otwiera g��wne okno, mixer dzwi�ku, itp.
	int Init(void);

	/// Zamyka Engine
	int Finish(void);

	/// Funkcja s�u�y do pomiaru czasu ramek (klatek animacji)
	int FrameTiming(int mode);

	/// Okre�laj� tryb wywo�wania funkcji FrameTiming
	enum FT_MODES {
		/// Rozpoczynamy now� ramk�, zwr�� czas w�a�nie zako�czonej ramki
		FTM_NEW_FRAME				= 0
		/// Zwr�� czas jaki up�yn�� od poczatku bie��cej ramki
	, FTM_FRAME_TIME			= 1
		/// Zwr�� czas jaki up�yn�� od pocz�tku pierwszej ramki
	, FTM_ALL_FRAMES_TIME	= 2
		/// Zwr�� surowe, nieprzetworzone ticki zegara
	, FTM_RAW_TICKS				= 3
	};

	/** Czeka tyle czasu, aby bie��ca ramka trwa�a podany jako parametr czas.<BR>
		@param frame_time zak�adany czas trwania ramki
		@return ile czasu trzeba bylo poczekac (wartosci ujemne swiadcz� o niewyrabianiu si� animacji w za�o�onym framerate)
	 */
	long FrameWait(Uint32 frame_time);

	/// Czeka wskazan� ilo�� milisekund (tysi�cznych cz�ci sekundy)
	void Wait(long pl_milisec);

	/// Przerzuca bufory ekranu (o ile s� dwa)
	void SwapBuffers(void);

	/** Ustawia rzutowanie swiata na ekran
	 @param minx - taka wsp�rz�dna �wiata przyporz�dkowana zostanie lewej kraw�dzi ekranu
	 @param maxx - taka wsp�rz�dna �wiata przyporz�dkowana zostanie prawej kraw�dzi ekranu
	 @param miny - taka wsp�rz�dna �wiata przyporz�dkowana zostanie dolnej kraw�dzi ekranu
	 @param maxy - taka wsp�rz�dna �wiata przyporz�dkowana zostanie g�rnej kraw�dzi ekranu
	 @param minz - taka wsp�rz�dna �wiata przyporz�dkowana zostanie p�aszczy�nie ekranu
	 @param maxz - taka wsp�rz�dna �wiata przyporz�dkowana zostanie horyzontowi �wiata (dalej nic nie b�dzie wida�)
	 */
	void ProjectionOrtho(GLfloat minx,GLfloat maxx,GLfloat miny,GLfloat maxy,GLfloat minz = 0.0,GLfloat maxz = 1.0);

	/// Ustawia rzutowanie swiata na ekran w ten sposob, ze jeden pixel to jedna jednosta miary swiata
	/// (r�wnowa�ne: ProjectionOrtho(0,il_screen_width,il_screen_height,0,0,1);
	void ProjectionOrtho(void);

	/// Wy�wietla lub chowa kursor myszy
	void ShowMouseCursor(bool visible);

};

#endif
