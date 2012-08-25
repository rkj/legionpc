#ifndef D_COLLISION_H_D
#define D_COLLISION_H_D

#include <GL/gl.h>

namespace Fzx {

	class ColSphere;

	/** Klasa bazowa obiektów do wykrywania kolizji
	 */
	class Col {
		protected:
			/// id typu obiektu kolizyjnego - inny dla ka¿dej klasy wyprowadzonej z tej
			unsigned char type_id;

			/// maska bitowa w³aœciwoœci (czym jest ten obiekt, np. statek, pocisk)
			unsigned long props;

			/// maska bitowa kolizyjnoœci (z czym mo¿e kolidowaæ ten obiekt, np. ze statkiem, pociskiem)
			unsigned long	mask;

			/// Po³o¿enie obiektu kolizyjnego
			GLfloat x,y,a;

			/// Dane dla programisty (np. wskazanie na boba, funkcjê, etc.)
			void *user_data;

			/// Ustawia wartoœci inicjalne obiektu
			void _reset(void);

			/// Niszczy sk³adowe obiektu
			void _destroy(void);

			/// Zbiór mo¿liwych typów obiektu kolizyjnego
			enum TYPE_IDS {
				/// Okr¹g
				ID_SPHERE		= 0
			};
		public:

			/// Konstruktor
			Col(void);

			/// Destruktor
			virtual ~Col();

			/// Ustawia maskê w³aœciwoœci
			void SetProperties(unsigned long p) { props = p; }

			/// Ustawia maskê kolizyjnoœci
			void SetMask(unsigned long m) { mask = m; }

			/// Ustawia dane programisty
			void SetUserData(void *ud) { user_data = ud; }

			/// Zwraca maskê w³aœciwoœci
			unsigned long GetProperties(void) const { return props; }

			/// Zwraca maskê kolizyjnoœci
			unsigned long GetMask(void) const { return mask; }

			/// Zwraca dane programisty
			void* GetUserData(void) const { return user_data; }

			/// Uaktualnia po³o¿enie obiektu kolizyjnego
			void UpdatePos(GLfloat x,GLfloat y,GLfloat a) { this->x = x; this->y = y; this->a = a; }

			/** Testuje kolizjê z innym obiektem kolizyjnym.
			    Je¿eli zostanie wykryta kolizja wo³ana jest metoda OnCollision().
			    Metoda ta mo¿e zablokowaæ kolizjê zwracaj¹c <b>false</b>.
			  @param c obiekt, z którym ma byæ testowana kolizja tego obiektu
			  @return <b>true</b> je¿eli obiekty koliduj¹
			 */
			bool Collide(const Col* c);

			/** Testuje kolizjê z innym obiektem kolizyjnym typu okr¹g.
			    Je¿eli zostanie wykryta kolizja wo³ana jest metoda OnCollision().
			    Metoda ta mo¿e zablokowaæ kolizjê zwracaj¹c <b>false</b>.
			  @param c obiekt, z którym ma byæ testowana kolizja tego obiektu
			  @return <b>true</b> je¿eli obiekty koliduj¹
			 */
			virtual bool Collide(const ColSphere* c) = 0;

			/** Rysuje ksza³t obiektu kolizyjnego
			    (wymyœlone do testów, ale kto wie jakie zasosowanie ktoœ wymyœli)
			 */
			virtual void Draw(void) { /* do nothing */ }

			/** Metoda wo³ana w czasie wykrycia kolizji.
			    Wynik tej metody mo¿e zablokowaæ kolizjê (wymusiæ jej brak)
			 */
			virtual bool OnCollision(const Col* c) const { /* do nothing and do not block collision */ return true; }
	};

	/** Klasa obiektu kolizyjnego w ksztalcie okrêgu.
	 */
	class ColSphere : public Col {
		public:

			/// Promieñ okrêgu
			GLfloat r;

			/// Konstruktor - okr¹g o promieniu zero
			ColSphere(void) { r=0.0f; }

			/// Konstruktor - okr¹g o podanym promieniu
			ColSphere(GLfloat r) : r(r) {}

			/// Destruktor
			virtual ~ColSphere() {}

			/// Metoda wykrywa kolizjê z innym okrêgiem
			virtual bool Collide(const ColSphere* c);

			/** Rysuje ksza³t obiektu kolizyjnego
			    (wymyœlone do testów, ale kto wie jakie zasosowanie ktoœ wymyœli)
			 */
			virtual void Draw(void);

			/** Metoda wo³ana w czasie wykrycia kolizji.
			    Wynik tej metody mo¿e zablokowaæ kolizjê (wymusiæ jej brak)
			 */
			virtual bool OnCollision(const Col* c) const { /* do nothing and do not block collision */ return true; }
	};

	/// Licznik testów kolizji - do celów diagnostycznych
	extern long collision_test_cnt;

};

#endif /*D_COLLISION_H_D*/
