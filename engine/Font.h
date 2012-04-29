#ifndef D_FONT_H_D
#define D_FONT_H_D

#include <string>
#include <map>

namespace Core {
	class Settings;
};

namespace Gfx {
	class PTex;
	class LTex;

/** Klasa reprezentuje font (czcionk�).
    Obs�ugiwane s� czcionki wektorowe (TrueType).
 */
class Font {
protected:
	/// fizyczna tekstura przechowuj�ca wygl�d literek
	PTex *ptex;

	/// logiczna tekstura przechowuj�ca wygl�d literek
	LTex *ltex;

	/// tablica szeroko�ci literek
	float *glyphs_width;

	/// tablica wysoko�� literek
	float *glyphs_height;

	/// tablica przesuni�� literek w poziomie
	float *glyphs_xshift;

	/// tablica przesuni�� literek w pionie
	float *glyphs_yshift;

	/// tablica przesuni�� do nast�pnej literki (o ile trzeba zwi�kszy� pozycj� X aby wydrukowa� kolejn� literk� wyst�puj�c� po tej)
	float *glyphs_advance;

	/// Typ filtrowania przy rysowaniu (musi byc okreslone przed zaladowaniem fontu)
	bool ib_antialiasing;

	/// Ustawia warto�ci inicjalne obiektu
	void _reset(void);

	/// Niszczy sk�adowe obiektu
	void _destroy(void);
public:

	/// Konstuktor
	Font(void);

	/// Destruktor
	~Font();

	/// Ustawia tryb rysowania fontow
	void SetAntialiasing(bool pb_aa);

	/** �aduje font z pliku i tworzy na jego podstawie tekstury s�u��ce do pisania po ekranie.
	 */
	int Load(const std::string& name,int ptx);

	friend void _render_font(Font *font);
	friend void Text(Font *font,const std::string& text, float x, float y, float sizh, float sizv);
	friend float TextLength(Font *font,const std::string& text,float sizh);
};


	/**
		Klasa reprezentuje managera (zarz�dce) font�w
		<BR>
				 Klasa przechowuje fonty i przypisuje im identyfikatory (stringi),
				 dzi�ki kt�rym mo�liwe jest pos�ugiwanie si� nazwami font�w zamiast adresami obiekt�w.
				 Dodatkowo mo�liwe jest za�adowanie i inicjacja ca�ego zbioru font�w
				 na podstawie definicji zapisanej w pliku konfiguracyjnym.
	*/
	class FontManager {
		protected:
			/// Zbi�r font�w
			std::map<std::string,Font*> fonts;

			/// Ustawia warto�ci inicjalne obiektu
			void _reset(void);

			/// Niszczy sk�adowe obiektu
			void _destroy(void);

			/// tworzy klucz indeksujacy zbior fontow
			std::string _key(const std::string& id,int siz);

		public:

			/// Konstruktor
			FontManager(void);

			/// Destruktor
			~FontManager();

			/** Zwraca <B>true</B> je�eli w zbiorze font�w istnieje font o podanym ID i rozmiarze
			 @param id ID fontu
			 @param siz rozmiar fontu
			 */
			bool Exists(const std::string& id,int siz);

			/** Dodaje do zbioru font�w nowy font
			 @param id ID fontu
			 @param siz rozmiar fontu
			 @param t wskazanie na dodawany font
			 @param overwrite m�wi o tym czy nale�y nadpisa� font je�eli
			                  w zbiorze istnieje ju� font o podanym ID i rozmiarze
			 */
			void Add(const std::string& id,int siz,Font* t,bool overwrite=false);

			/** Zwraca wskazanie na font okre�lon� poprzez przekazane ID i rozmiar
			 @param id ID tekstury
			 @param siz rozmiar fontu
			 @return wskazanie na font lub 0 je�eli w zbiorze nie istnieje font o podanym ID i rozmiarze
			 */
			Font* Get(const std::string& id,int siz);

			/** Usuwa font ze zbioru a nast�pnie zwraca wskazanie na niego.
			    Font jako obiekt nie jest niszczona a jedynie usuwana ze zbioru.
			 @param id ID rozmiar
			 @param siz rozmiar fontu
			 @return wskazanie na font lub 0 je�eli w zbiorze nie istnieje font o podanym ID i rozmiarze
			 */
			Font* Rem(const std::string& id,int siz);

			/** Usuwa font ze zbioru a nast�pnie niszczy obiekt opisuj�cy go.
			 @param id ID fontu
			 @param siz rozmiar fontu
			 */
			void Del(const std::string& id,int siz);

			/** Automatycznie tworzy obiekty fontow na podstawie
			    opisu w pliku konfiguracyjnym.
			    Stworzone obiekty s� nast�pnie dodawane do zbior�w.
			 @param filename nazwa pliku konfiguracyjnego
			 @param root scie�ka do opisu fontow w pliku konfiguracyjnym
			 */
			int Load(const std::string& filename,const std::string& root="");

			/** Automatycznie tworzy obiekty fontow na podstawie
			    opisu w obiekcie konfiguracyjnym.
			    Stworzone obiekty s� nast�pnie dodawane do zbior�w.
			 @param sets obiekt z konfiguracj�
			 @param root scie�ka do opisu tekstur w pliku konfiguracyjnym
			 */
			int Load(const Core::Settings& sets,const std::string& root="");
	};


/** Rysuje na ekranie napis.
  @param font czcionka jak� ma by� rysowany napis
  @param text napis
  @param x wsp�rz�dna pozioma pocz�tku napisu
  @param y wsp�rz�dna pionowa lini bazowej napisu
  @param sizh rozmiar (skala) poziomy czcionki (je�eli literki maj� mie� zachowane proporcje nale�y poda� tak� sam� warto�� jak w sizv)
  @param sizv rozmiar (skala) pionowa czcionki (np. 12 oznacza 12 pixli)
 */
void Text(Font *font,const std::string& text, float x, float y, float sizh, float sizv);

/** Zwraca szerokosc tekstu wyrazona w pixlach (tyle miejsca zajmie napis na ekranie)
  @param font czcionka jak� ma by� rysowany napis
  @param text napis
  @param sizh rozmiar (skala) poziomy czcionki (je�eli literki maj� mie� zachowane proporcje nale�y poda� tak� sam� warto�� jak w sizv)
  @param sizv rozmiar (skala) pionowa czcionki (np. 12 oznacza 12 pixli)
 */
float TextLength(Font *font,const std::string& text,float sizh);

/** Rysuje na ekranie podgl�d fontu (ca�� tekstur�)
 */
void _render_font(Font *font);


};	//namespace

#endif /*D_FONT_H_D*/
