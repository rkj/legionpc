#ifndef D_BOB_H_D
#define D_BOB_H_D

namespace Fzx {
class Col;
};

#include "Grid.h"
#include "Utils.h"
#include "Alan.h"

namespace Gfx {

	class LTex;

  /** Klasa bazowa reprezentująca obiekt graficzny wypełniony teksturą.
   */
	class Blitable {
		protected:
			/// Wskazanie na tekturę logiczną
			const LTex *tex;
		public:
			/// Konstruktor
			Blitable(void) { tex=0; };

			/// Destruktor
			virtual ~Blitable() {};

			/// Rysuje obiekt na ekranie
			virtual void Blit(void) = 0;

			/// Rysuje obiekt na ekranie przesuniety o podane offsety
			virtual void Blit(float xo,float yo) = 0;

			/// Zwraca teksturę logiczną skojarzoną z obiektem
			virtual const LTex* GetTex(void) const { return tex; }

			/// Zmienia teksturę logiczną obiektu
			virtual void SetTex(const LTex *t) { tex=t; }

	};


  /** Klasa reprezentuje obiekt graficzny (ruchomy bądź nie) wypełniony teksturą.
	    Wszystko inne jest napisane po to aby na ekranie pojawił się obiekt graficzny.
      Bob to nic innego jak wyteksturowany prostokąt położony w dowolnym miejscu
      pola gry (nawet poza częścią widoczną na ekranie).
      Bob to rowniez mozliwosc kontrolowania polozenia, rozmiaru i wygladu obiektu
      graficznego za pomoca jezyka ALAN.
   */
	class Bob : public Blitable, public AlanControlable {
		protected:

			/// Ustawia wartości inicjalne obiektu
			void _reset(void);

			/// Niszczy składowe obiektu
			void _destroy(void);

			/// Wpółrzędna X polożenie obiektu na polu gry (+ x_hotspot)
			GLfloat x;

			/// Wpółrzędna y polożenie obiektu na polu gry (+ y_hotspot)
			GLfloat y;

			/// Kąt obrotu wokół położenia
			GLfloat	alpha;

			/// Szerokość boba w pixlach (brana z tekstury)
			GLfloat	w;

			/// Wysokość boba w pixlach (brana z tekstury)
			GLfloat h;

			/// Skala pozioma (rozciągnięcie w poziomie)
			GLfloat sx;

			/// Skala pionowa (rozciągnięcie w pionie)
			GLfloat sy;

			/// Odleglosc od prawego gornego rogu do punktu, który chcemy uważać za położenie oraz środek obrotu
			GLfloat x_hotspot;

			/// Odleglosc od prawego gornego rogu do punktu, który chcemy uważać za położenie oraz środek obrotu
			GLfloat y_hotspot;

			/// Promień Boba = MAX(w,h) (do szybkiego poruszania sie po siatce)
			GLfloat	radius;

			/// Wskazania na siatkę, w którą jest wpięty bob
			Core::Grid *grid;

			/// Wskazanie na obiekt okreslający kolizyjność boba
			Fzx::Col  *col;

			/// Czy Bob może się przemieszczać (ważna wskazówka dla siatki)
			bool movable;

			/// Kolor rysowanego boba
			GLfloat color_r, color_g, color_b, color_a;

		public:
			/// Konstruktor
			Bob(void);

			/// Destruktor
			~Bob();

			/// Rysuje boba na ekranie
			void Blit(void);

			/// Rysuje boba na ekranie przesunietego o podane offsety
			void Blit(float xo,float yo);

			/// Uwzględnienie zmiany polożenia boba na siatce
			void Actualize(void);

			/// Zwraca wspołrzędną X położenia boba
			GLfloat GetX(void) const { return x + x_hotspot; }

			/// Zwraca wspołrzędną Y położenia boba
			GLfloat GetY(void) const { return y + y_hotspot; }

			/// Zwraca sumę położenia X + x_hotspot boba
			GLfloat GetXH(void) const { return x; }

			/// Zwraca sumę położenia Y + y_hotspot boba
			GLfloat GetYH(void) const { return y; }

			/// Zwraca kąt obrotu wokół punktu położenia (X,Y)
			GLfloat GetRot(void) const { return alpha; }

			/// Zwraca szerokość boba
			GLfloat GetWidth(void) const { return w; }

			/// Zwraca wysokość boba
			GLfloat GetHeight(void) const { return h; }

			/// Zwrac skalę boba w poziomie
			GLfloat GetScaleX(void) const { return sx; }

			/// Zwrac skalę boba w poziomie
			GLfloat GetScaleY(void) const { return sy; }

			/// Zwraca przesunięcie poziome punktu położenia względem prawego-górnego rogu boba
			GLfloat GetHotSpotX(void) const { return x_hotspot; }

			/// Zwraca przesunięcie pionowe punktu położenia względem prawego-górnego rogu boba
			GLfloat GetHotSpotY(void) const { return y_hotspot; }

			/// Zwraca siatkę, w którą wpięty jest bob
			Core::Grid* GetGrid(void) const { return grid; }

			/// Zwraca obiekt kolizji skojarzony z bobem
			Fzx::Col* GetCol(void) const { return col; }

			/// Zwraca <b>true</b> jeżeli bob może się poruszać
			bool IsMovable(void) { return movable; }

			/// Zmienia pozycję boba
			void SetPos(GLfloat x,GLfloat y) { this->x = x - x_hotspot; this->y = y - y_hotspot; if( grid ) grid->ActObj(this); }

			/// Zmienia pozycję i obrót boba
			void SetPos(GLfloat x,GLfloat y,GLfloat alpha) { this->x = x - x_hotspot; this->y = y - y_hotspot; this->alpha = alpha; if( grid ) grid->ActObj(this); }

			/// Zmienia rozmiar boba
			void SetSize(GLfloat w,GLfloat h) { this->w = w; this->h = h; this->radius = Max(w,h); if( grid ) grid->ActObj(this); }

			/// Zmienia obrót boba
			void SetRot(GLfloat a) { alpha = a; }

			/// Zmienia skalę boba
			void SetScale(GLfloat sx,GLfloat sy) { this->sx = sx; this->sy = sy; }

			/// Zmienia przesunięcie punktu położenia względem prawego-górnego rogu
			void SetHotSpot(GLfloat xhs,GLfloat yhs) { x += x_hotspot - xhs; y += y_hotspot - yhs; x_hotspot = xhs; y_hotspot = yhs; if( grid ) grid->ActObj(this); }

			/// Zmienia teksturę logiczną boba
			void SetTex(const LTex *t,bool preserve_size, bool preserve_hotspot);

			/// Zmienia teksturę logiczną boba
			void SetTex(const LTex *t) { SetTex(t,false,false); }

			/// Zmienia siatkę, w która wpięty jest bob
			void SetGrid(Core::Grid *g) { grid = g; }

			/// Zmienia obiekt kolizyjności boba
			void SetCol(Fzx::Col *c) { col = c; if( grid ) grid->ActObjCol(this); }

			/// Zmienia własność "ruchomości" boba
			void Movable(bool m) { movable = m; }

			/// Zmienia kolor rysowanego boba
			void SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a ) { color_r = r; color_g = g; color_b = b; color_a = a; }

			/// Implementacja metod sluzacych do kontrolowania Boba z poziomu ALANa
			float AlanGetX(void) { return GetX(); }
			float AlanGetY(void) { return GetY(); }
			float AlanGetRot(void) { return GetRot(); }
			float AlanGetScaleX(void) { return GetScaleX(); }
			float AlanGetScaleY(void) { return GetScaleY(); }
			void AlanSetPos(float x,float y) { SetPos(x,y); }
			void AlanSetRot(float r) { SetRot(r); }
			void AlanSetScale(float sx,float sy) { SetScale(sx,sy); }
			void AlanSetTex(LTex* tex) { SetTex(tex); }

			friend class Core::Grid;
	};

	/// Informuje engine, że teraz nastąpi seria rysowań bobów (można tego nie robić, ale zwiększa to wydajność)
	void BeginBobBlits(void);
	/// Informuje engine, że teraz zakończyła się seria rysowań bobów (można tego nie robić, ale zwiększa to wydajność)
	void EndBobBlits(void);
	/// Informuje engine, że nastąpiła inna operacja graficzna niż rysowanie boba i seria rysowań została przerwana
	void BreakBobBlits(void);

	///licznik wykonanych blitow (narysowan Bobow) - do celow diagnostycznych
	extern int bobblit_cnt;

};

#endif
