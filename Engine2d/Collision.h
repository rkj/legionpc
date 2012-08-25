#ifndef D_COLLISION_H_D
#define D_COLLISION_H_D

#include <GL/gl.h>

namespace Fzx {

	class ColSphere;

	/** Klasa bazowa obiektów do wykrywania kolizji
	 */
	class Col {
		protected:
			/// id typu obiektu kolizyjnego - inny dla każdej klasy wyprowadzonej z tej
			unsigned char type_id;

			/// maska bitowa właściwości (czym jest ten obiekt, np. statek, pocisk)
			unsigned long props;

			/// maska bitowa kolizyjności (z czym może kolidować ten obiekt, np. ze statkiem, pociskiem)
			unsigned long	mask;

			/// Położenie obiektu kolizyjnego
			GLfloat x,y,a;

			/// Dane dla programisty (np. wskazanie na boba, funkcję, etc.)
			void *user_data;

			/// Ustawia wartości inicjalne obiektu
			void _reset(void);

			/// Niszczy składowe obiektu
			void _destroy(void);

			/// Zbiór możliwych typów obiektu kolizyjnego
			enum TYPE_IDS {
				/// Okrąg
				ID_SPHERE		= 0
			};
		public:

			/// Konstruktor
			Col(void);

			/// Destruktor
			virtual ~Col();

			/// Ustawia maskę właściwości
			void SetProperties(unsigned long p) { props = p; }

			/// Ustawia maskę kolizyjności
			void SetMask(unsigned long m) { mask = m; }

			/// Ustawia dane programisty
			void SetUserData(void *ud) { user_data = ud; }

			/// Zwraca maskę właściwości
			unsigned long GetProperties(void) const { return props; }

			/// Zwraca maskę kolizyjności
			unsigned long GetMask(void) const { return mask; }

			/// Zwraca dane programisty
			void* GetUserData(void) const { return user_data; }

			/// Uaktualnia położenie obiektu kolizyjnego
			void UpdatePos(GLfloat x,GLfloat y,GLfloat a) { this->x = x; this->y = y; this->a = a; }

			/** Testuje kolizję z innym obiektem kolizyjnym.
			    Jeżeli zostanie wykryta kolizja wołana jest metoda OnCollision().
			    Metoda ta może zablokować kolizję zwracając <b>false</b>.
			  @param c obiekt, z którym ma być testowana kolizja tego obiektu
			  @return <b>true</b> jeżeli obiekty kolidują
			 */
			bool Collide(const Col* c);

			/** Testuje kolizję z innym obiektem kolizyjnym typu okrąg.
			    Jeżeli zostanie wykryta kolizja wołana jest metoda OnCollision().
			    Metoda ta może zablokować kolizję zwracając <b>false</b>.
			  @param c obiekt, z którym ma być testowana kolizja tego obiektu
			  @return <b>true</b> jeżeli obiekty kolidują
			 */
			virtual bool Collide(const ColSphere* c) = 0;

			/** Rysuje kszałt obiektu kolizyjnego
			    (wymyślone do testów, ale kto wie jakie zasosowanie ktoś wymyśli)
			 */
			virtual void Draw(void) { /* do nothing */ }

			/** Metoda wołana w czasie wykrycia kolizji.
			    Wynik tej metody może zablokować kolizję (wymusić jej brak)
			 */
			virtual bool OnCollision(const Col* c) const { /* do nothing and do not block collision */ return true; }
	};

	/** Klasa obiektu kolizyjnego w ksztalcie okręgu.
	 */
	class ColSphere : public Col {
		public:

			/// Promień okręgu
			GLfloat r;

			/// Konstruktor - okrąg o promieniu zero
			ColSphere(void) { r=0.0f; }

			/// Konstruktor - okrąg o podanym promieniu
			ColSphere(GLfloat r) : r(r) {}

			/// Destruktor
			virtual ~ColSphere() {}

			/// Metoda wykrywa kolizję z innym okręgiem
			virtual bool Collide(const ColSphere* c);

			/** Rysuje kszałt obiektu kolizyjnego
			    (wymyślone do testów, ale kto wie jakie zasosowanie ktoś wymyśli)
			 */
			virtual void Draw(void);

			/** Metoda wołana w czasie wykrycia kolizji.
			    Wynik tej metody może zablokować kolizję (wymusić jej brak)
			 */
			virtual bool OnCollision(const Col* c) const { /* do nothing and do not block collision */ return true; }
	};

	/// Licznik testów kolizji - do celów diagnostycznych
	extern long collision_test_cnt;

};

#endif /*D_COLLISION_H_D*/
