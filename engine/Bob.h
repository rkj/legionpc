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

  /** Klasa bazowa reprezentuj¹ca obiekt graficzny wype³niony tekstur¹.
   */
	class Blitable {
		protected:
			/// Wskazanie na tekturê logiczn¹
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

			/// Zwraca teksturê logiczn¹ skojarzon¹ z obiektem
			virtual const LTex* GetTex(void) const { return tex; }

			/// Zmienia teksturê logiczn¹ obiektu
			virtual void SetTex(const LTex *t) { tex=t; }

	};


  /** Klasa reprezentuje obiekt graficzny (ruchomy b¹dŸ nie) wype³niony tekstur¹.
	    Wszystko inne jest napisane po to aby na ekranie pojawi³ siê obiekt graficzny.
      Bob to nic innego jak wyteksturowany prostok¹t po³o¿ony w dowolnym miejscu
      pola gry (nawet poza czêœci¹ widoczn¹ na ekranie).
      Bob to rowniez mozliwosc kontrolowania polozenia, rozmiaru i wygladu obiektu
      graficznego za pomoca jezyka ALAN.
   */
	class Bob : public Blitable, public AlanControlable {
		protected:

			/// Ustawia wartoœci inicjalne obiektu
			void _reset(void);

			/// Niszczy sk³adowe obiektu
			void _destroy(void);

			/// Wpó³rzêdna X polo¿enie obiektu na polu gry (+ x_hotspot)
			GLfloat x;

			/// Wpó³rzêdna y polo¿enie obiektu na polu gry (+ y_hotspot)
			GLfloat y;

			/// K¹t obrotu wokó³ po³o¿enia
			GLfloat	alpha;

			/// Szerokoœæ boba w pixlach (brana z tekstury)
			GLfloat	w;

			/// Wysokoœæ boba w pixlach (brana z tekstury)
			GLfloat h;

			/// Skala pozioma (rozci¹gniêcie w poziomie)
			GLfloat sx;

			/// Skala pionowa (rozci¹gniêcie w pionie)
			GLfloat sy;

			/// Odleglosc od prawego gornego rogu do punktu, który chcemy uwa¿aæ za po³o¿enie oraz œrodek obrotu
			GLfloat x_hotspot;

			/// Odleglosc od prawego gornego rogu do punktu, który chcemy uwa¿aæ za po³o¿enie oraz œrodek obrotu
			GLfloat y_hotspot;

			/// Promieñ Boba = MAX(w,h) (do szybkiego poruszania sie po siatce)
			GLfloat	radius;

			/// Wskazania na siatkê, w któr¹ jest wpiêty bob
			Core::Grid *grid;

			/// Wskazanie na obiekt okreslaj¹cy kolizyjnoœæ boba
			Fzx::Col  *col;

			/// Czy Bob mo¿e siê przemieszczaæ (wa¿na wskazówka dla siatki)
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

			/// Uwzglêdnienie zmiany polo¿enia boba na siatce
			void Actualize(void);

			/// Zwraca wspo³rzêdn¹ X po³o¿enia boba
			GLfloat GetX(void) const { return x + x_hotspot; }

			/// Zwraca wspo³rzêdn¹ Y po³o¿enia boba
			GLfloat GetY(void) const { return y + y_hotspot; }

			/// Zwraca sumê po³o¿enia X + x_hotspot boba
			GLfloat GetXH(void) const { return x; }

			/// Zwraca sumê po³o¿enia Y + y_hotspot boba
			GLfloat GetYH(void) const { return y; }

			/// Zwraca k¹t obrotu wokó³ punktu po³o¿enia (X,Y)
			GLfloat GetRot(void) const { return alpha; }

			/// Zwraca szerokoœæ boba
			GLfloat GetWidth(void) const { return w; }

			/// Zwraca wysokoœæ boba
			GLfloat GetHeight(void) const { return h; }

			/// Zwrac skalê boba w poziomie
			GLfloat GetScaleX(void) const { return sx; }

			/// Zwrac skalê boba w poziomie
			GLfloat GetScaleY(void) const { return sy; }

			/// Zwraca przesuniêcie poziome punktu po³o¿enia wzglêdem prawego-górnego rogu boba
			GLfloat GetHotSpotX(void) const { return x_hotspot; }

			/// Zwraca przesuniêcie pionowe punktu po³o¿enia wzglêdem prawego-górnego rogu boba
			GLfloat GetHotSpotY(void) const { return y_hotspot; }

			/// Zwraca siatkê, w któr¹ wpiêty jest bob
			Core::Grid* GetGrid(void) const { return grid; }

			/// Zwraca obiekt kolizji skojarzony z bobem
			Fzx::Col* GetCol(void) const { return col; }

			/// Zwraca <b>true</b> je¿eli bob mo¿e siê poruszaæ
			bool IsMovable(void) { return movable; }

			/// Zmienia pozycjê boba
			void SetPos(GLfloat x,GLfloat y) { this->x = x - x_hotspot; this->y = y - y_hotspot; if( grid ) grid->ActObj(this); }

			/// Zmienia pozycjê i obrót boba
			void SetPos(GLfloat x,GLfloat y,GLfloat alpha) { this->x = x - x_hotspot; this->y = y - y_hotspot; this->alpha = alpha; if( grid ) grid->ActObj(this); }

			/// Zmienia rozmiar boba
			void SetSize(GLfloat w,GLfloat h) { this->w = w; this->h = h; this->radius = Max(w,h); if( grid ) grid->ActObj(this); }

			/// Zmienia obrót boba
			void SetRot(GLfloat a) { alpha = a; }

			/// Zmienia skalê boba
			void SetScale(GLfloat sx,GLfloat sy) { this->sx = sx; this->sy = sy; }

			/// Zmienia przesuniêcie punktu po³o¿enia wzglêdem prawego-górnego rogu
			void SetHotSpot(GLfloat xhs,GLfloat yhs) { x += x_hotspot - xhs; y += y_hotspot - yhs; x_hotspot = xhs; y_hotspot = yhs; if( grid ) grid->ActObj(this); }

			/// Zmienia teksturê logiczn¹ boba
			void SetTex(const LTex *t,bool preserve_size, bool preserve_hotspot);

			/// Zmienia teksturê logiczn¹ boba
			void SetTex(const LTex *t) { SetTex(t,false,false); }

			/// Zmienia siatkê, w która wpiêty jest bob
			void SetGrid(Core::Grid *g) { grid = g; }

			/// Zmienia obiekt kolizyjnoœci boba
			void SetCol(Fzx::Col *c) { col = c; if( grid ) grid->ActObjCol(this); }

			/// Zmienia w³asnoœæ "ruchomoœci" boba
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

	/// Informuje engine, ¿e teraz nast¹pi seria rysowañ bobów (mo¿na tego nie robiæ, ale zwiêksza to wydajnoœæ)
	void BeginBobBlits(void);
	/// Informuje engine, ¿e teraz zakoñczy³a siê seria rysowañ bobów (mo¿na tego nie robiæ, ale zwiêksza to wydajnoœæ)
	void EndBobBlits(void);
	/// Informuje engine, ¿e nast¹pi³a inna operacja graficzna ni¿ rysowanie boba i seria rysowañ zosta³a przerwana
	void BreakBobBlits(void);

	///licznik wykonanych blitow (narysowan Bobow) - do celow diagnostycznych
	extern int bobblit_cnt;

};

#endif
