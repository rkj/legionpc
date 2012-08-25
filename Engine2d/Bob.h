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

  /** Klasa bazowa reprezentuj�ca obiekt graficzny wype�niony tekstur�.
   */
	class Blitable {
		protected:
			/// Wskazanie na tektur� logiczn�
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

			/// Zwraca tekstur� logiczn� skojarzon� z obiektem
			virtual const LTex* GetTex(void) const { return tex; }

			/// Zmienia tekstur� logiczn� obiektu
			virtual void SetTex(const LTex *t) { tex=t; }

	};


  /** Klasa reprezentuje obiekt graficzny (ruchomy b�d� nie) wype�niony tekstur�.
	    Wszystko inne jest napisane po to aby na ekranie pojawi� si� obiekt graficzny.
      Bob to nic innego jak wyteksturowany prostok�t po�o�ony w dowolnym miejscu
      pola gry (nawet poza cz�ci� widoczn� na ekranie).
      Bob to rowniez mozliwosc kontrolowania polozenia, rozmiaru i wygladu obiektu
      graficznego za pomoca jezyka ALAN.
   */
	class Bob : public Blitable, public AlanControlable {
		protected:

			/// Ustawia warto�ci inicjalne obiektu
			void _reset(void);

			/// Niszczy sk�adowe obiektu
			void _destroy(void);

			/// Wp�rz�dna X polo�enie obiektu na polu gry (+ x_hotspot)
			GLfloat x;

			/// Wp�rz�dna y polo�enie obiektu na polu gry (+ y_hotspot)
			GLfloat y;

			/// K�t obrotu wok� po�o�enia
			GLfloat	alpha;

			/// Szeroko�� boba w pixlach (brana z tekstury)
			GLfloat	w;

			/// Wysoko�� boba w pixlach (brana z tekstury)
			GLfloat h;

			/// Skala pozioma (rozci�gni�cie w poziomie)
			GLfloat sx;

			/// Skala pionowa (rozci�gni�cie w pionie)
			GLfloat sy;

			/// Odleglosc od prawego gornego rogu do punktu, kt�ry chcemy uwa�a� za po�o�enie oraz �rodek obrotu
			GLfloat x_hotspot;

			/// Odleglosc od prawego gornego rogu do punktu, kt�ry chcemy uwa�a� za po�o�enie oraz �rodek obrotu
			GLfloat y_hotspot;

			/// Promie� Boba = MAX(w,h) (do szybkiego poruszania sie po siatce)
			GLfloat	radius;

			/// Wskazania na siatk�, w kt�r� jest wpi�ty bob
			Core::Grid *grid;

			/// Wskazanie na obiekt okreslaj�cy kolizyjno�� boba
			Fzx::Col  *col;

			/// Czy Bob mo�e si� przemieszcza� (wa�na wskaz�wka dla siatki)
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

			/// Uwzgl�dnienie zmiany polo�enia boba na siatce
			void Actualize(void);

			/// Zwraca wspo�rz�dn� X po�o�enia boba
			GLfloat GetX(void) const { return x + x_hotspot; }

			/// Zwraca wspo�rz�dn� Y po�o�enia boba
			GLfloat GetY(void) const { return y + y_hotspot; }

			/// Zwraca sum� po�o�enia X + x_hotspot boba
			GLfloat GetXH(void) const { return x; }

			/// Zwraca sum� po�o�enia Y + y_hotspot boba
			GLfloat GetYH(void) const { return y; }

			/// Zwraca k�t obrotu wok� punktu po�o�enia (X,Y)
			GLfloat GetRot(void) const { return alpha; }

			/// Zwraca szeroko�� boba
			GLfloat GetWidth(void) const { return w; }

			/// Zwraca wysoko�� boba
			GLfloat GetHeight(void) const { return h; }

			/// Zwrac skal� boba w poziomie
			GLfloat GetScaleX(void) const { return sx; }

			/// Zwrac skal� boba w poziomie
			GLfloat GetScaleY(void) const { return sy; }

			/// Zwraca przesuni�cie poziome punktu po�o�enia wzgl�dem prawego-g�rnego rogu boba
			GLfloat GetHotSpotX(void) const { return x_hotspot; }

			/// Zwraca przesuni�cie pionowe punktu po�o�enia wzgl�dem prawego-g�rnego rogu boba
			GLfloat GetHotSpotY(void) const { return y_hotspot; }

			/// Zwraca siatk�, w kt�r� wpi�ty jest bob
			Core::Grid* GetGrid(void) const { return grid; }

			/// Zwraca obiekt kolizji skojarzony z bobem
			Fzx::Col* GetCol(void) const { return col; }

			/// Zwraca <b>true</b> je�eli bob mo�e si� porusza�
			bool IsMovable(void) { return movable; }

			/// Zmienia pozycj� boba
			void SetPos(GLfloat x,GLfloat y) { this->x = x - x_hotspot; this->y = y - y_hotspot; if( grid ) grid->ActObj(this); }

			/// Zmienia pozycj� i obr�t boba
			void SetPos(GLfloat x,GLfloat y,GLfloat alpha) { this->x = x - x_hotspot; this->y = y - y_hotspot; this->alpha = alpha; if( grid ) grid->ActObj(this); }

			/// Zmienia rozmiar boba
			void SetSize(GLfloat w,GLfloat h) { this->w = w; this->h = h; this->radius = Max(w,h); if( grid ) grid->ActObj(this); }

			/// Zmienia obr�t boba
			void SetRot(GLfloat a) { alpha = a; }

			/// Zmienia skal� boba
			void SetScale(GLfloat sx,GLfloat sy) { this->sx = sx; this->sy = sy; }

			/// Zmienia przesuni�cie punktu po�o�enia wzgl�dem prawego-g�rnego rogu
			void SetHotSpot(GLfloat xhs,GLfloat yhs) { x += x_hotspot - xhs; y += y_hotspot - yhs; x_hotspot = xhs; y_hotspot = yhs; if( grid ) grid->ActObj(this); }

			/// Zmienia tekstur� logiczn� boba
			void SetTex(const LTex *t,bool preserve_size, bool preserve_hotspot);

			/// Zmienia tekstur� logiczn� boba
			void SetTex(const LTex *t) { SetTex(t,false,false); }

			/// Zmienia siatk�, w kt�ra wpi�ty jest bob
			void SetGrid(Core::Grid *g) { grid = g; }

			/// Zmienia obiekt kolizyjno�ci boba
			void SetCol(Fzx::Col *c) { col = c; if( grid ) grid->ActObjCol(this); }

			/// Zmienia w�asno�� "ruchomo�ci" boba
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

	/// Informuje engine, �e teraz nast�pi seria rysowa� bob�w (mo�na tego nie robi�, ale zwi�ksza to wydajno��)
	void BeginBobBlits(void);
	/// Informuje engine, �e teraz zako�czy�a si� seria rysowa� bob�w (mo�na tego nie robi�, ale zwi�ksza to wydajno��)
	void EndBobBlits(void);
	/// Informuje engine, �e nast�pi�a inna operacja graficzna ni� rysowanie boba i seria rysowa� zosta�a przerwana
	void BreakBobBlits(void);

	///licznik wykonanych blitow (narysowan Bobow) - do celow diagnostycznych
	extern int bobblit_cnt;

};

#endif
