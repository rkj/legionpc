#ifndef D_COLLISION_H_D
#define D_COLLISION_H_D

#include <GL/gl.h>

namespace Fzx {

	class ColSphere;

	/** Klasa bazowa obiekt�w do wykrywania kolizji
	 */
	class Col {
		protected:
			/// id typu obiektu kolizyjnego - inny dla ka�dej klasy wyprowadzonej z tej
			unsigned char type_id;

			/// maska bitowa w�a�ciwo�ci (czym jest ten obiekt, np. statek, pocisk)
			unsigned long props;

			/// maska bitowa kolizyjno�ci (z czym mo�e kolidowa� ten obiekt, np. ze statkiem, pociskiem)
			unsigned long	mask;

			/// Po�o�enie obiektu kolizyjnego
			GLfloat x,y,a;

			/// Dane dla programisty (np. wskazanie na boba, funkcj�, etc.)
			void *user_data;

			/// Ustawia warto�ci inicjalne obiektu
			void _reset(void);

			/// Niszczy sk�adowe obiektu
			void _destroy(void);

			/// Zbi�r mo�liwych typ�w obiektu kolizyjnego
			enum TYPE_IDS {
				/// Okr�g
				ID_SPHERE		= 0
			};
		public:

			/// Konstruktor
			Col(void);

			/// Destruktor
			virtual ~Col();

			/// Ustawia mask� w�a�ciwo�ci
			void SetProperties(unsigned long p) { props = p; }

			/// Ustawia mask� kolizyjno�ci
			void SetMask(unsigned long m) { mask = m; }

			/// Ustawia dane programisty
			void SetUserData(void *ud) { user_data = ud; }

			/// Zwraca mask� w�a�ciwo�ci
			unsigned long GetProperties(void) const { return props; }

			/// Zwraca mask� kolizyjno�ci
			unsigned long GetMask(void) const { return mask; }

			/// Zwraca dane programisty
			void* GetUserData(void) const { return user_data; }

			/// Uaktualnia po�o�enie obiektu kolizyjnego
			void UpdatePos(GLfloat x,GLfloat y,GLfloat a) { this->x = x; this->y = y; this->a = a; }

			/** Testuje kolizj� z innym obiektem kolizyjnym.
			    Je�eli zostanie wykryta kolizja wo�ana jest metoda OnCollision().
			    Metoda ta mo�e zablokowa� kolizj� zwracaj�c <b>false</b>.
			  @param c obiekt, z kt�rym ma by� testowana kolizja tego obiektu
			  @return <b>true</b> je�eli obiekty koliduj�
			 */
			bool Collide(const Col* c);

			/** Testuje kolizj� z innym obiektem kolizyjnym typu okr�g.
			    Je�eli zostanie wykryta kolizja wo�ana jest metoda OnCollision().
			    Metoda ta mo�e zablokowa� kolizj� zwracaj�c <b>false</b>.
			  @param c obiekt, z kt�rym ma by� testowana kolizja tego obiektu
			  @return <b>true</b> je�eli obiekty koliduj�
			 */
			virtual bool Collide(const ColSphere* c) = 0;

			/** Rysuje ksza�t obiektu kolizyjnego
			    (wymy�lone do test�w, ale kto wie jakie zasosowanie kto� wymy�li)
			 */
			virtual void Draw(void) { /* do nothing */ }

			/** Metoda wo�ana w czasie wykrycia kolizji.
			    Wynik tej metody mo�e zablokowa� kolizj� (wymusi� jej brak)
			 */
			virtual bool OnCollision(const Col* c) const { /* do nothing and do not block collision */ return true; }
	};

	/** Klasa obiektu kolizyjnego w ksztalcie okr�gu.
	 */
	class ColSphere : public Col {
		public:

			/// Promie� okr�gu
			GLfloat r;

			/// Konstruktor - okr�g o promieniu zero
			ColSphere(void) { r=0.0f; }

			/// Konstruktor - okr�g o podanym promieniu
			ColSphere(GLfloat r) : r(r) {}

			/// Destruktor
			virtual ~ColSphere() {}

			/// Metoda wykrywa kolizj� z innym okr�giem
			virtual bool Collide(const ColSphere* c);

			/** Rysuje ksza�t obiektu kolizyjnego
			    (wymy�lone do test�w, ale kto wie jakie zasosowanie kto� wymy�li)
			 */
			virtual void Draw(void);

			/** Metoda wo�ana w czasie wykrycia kolizji.
			    Wynik tej metody mo�e zablokowa� kolizj� (wymusi� jej brak)
			 */
			virtual bool OnCollision(const Col* c) const { /* do nothing and do not block collision */ return true; }
	};

	/// Licznik test�w kolizji - do cel�w diagnostycznych
	extern long collision_test_cnt;

};

#endif /*D_COLLISION_H_D*/
