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

/** Klasa reprezentuje font (czcionkę).
    Obsługiwane są czcionki wektorowe (TrueType).
 */
class Font {
protected:
	/// fizyczna tekstura przechowująca wygląd literek
	PTex *ptex;

	/// logiczna tekstura przechowująca wygląd literek
	LTex *ltex;

	/// tablica szerokości literek
	float *glyphs_width;

	/// tablica wysokość literek
	float *glyphs_height;

	/// tablica przesunięć literek w poziomie
	float *glyphs_xshift;

	/// tablica przesunięć literek w pionie
	float *glyphs_yshift;

	/// tablica przesunięć do następnej literki (o ile trzeba zwiększyć pozycję X aby wydrukować kolejną literkę występującą po tej)
	float *glyphs_advance;

	/// Typ filtrowania przy rysowaniu (musi byc okreslone przed zaladowaniem fontu)
	bool ib_antialiasing;

	/// Ustawia wartości inicjalne obiektu
	void _reset(void);

	/// Niszczy składowe obiektu
	void _destroy(void);
public:

	/// Konstuktor
	Font(void);

	/// Destruktor
	~Font();

	/// Ustawia tryb rysowania fontow
	void SetAntialiasing(bool pb_aa);

	/** Ładuje font z pliku i tworzy na jego podstawie tekstury służące do pisania po ekranie.
	 */
	int Load(const std::string& name,int ptx);

	friend void _render_font(Font *font);
	friend void Text(Font *font,const std::string& text, float x, float y, float sizh, float sizv);
	friend float TextLength(Font *font,const std::string& text,float sizh);
};


	/**
		Klasa reprezentuje managera (zarządce) fontów
		<BR>
				 Klasa przechowuje fonty i przypisuje im identyfikatory (stringi),
				 dzięki którym możliwe jest posługiwanie siż nazwami fontów zamiast adresami obiektów.
				 Dodatkowo możliwe jest załadowanie i inicjacja całego zbioru fontów
				 na podstawie definicji zapisanej w pliku konfiguracyjnym.
	*/
	class FontManager {
		protected:
			/// Zbiór fontów
			std::map<std::string,Font*> fonts;

			/// Ustawia wartości inicjalne obiektu
			void _reset(void);

			/// Niszczy składowe obiektu
			void _destroy(void);

			/// tworzy klucz indeksujacy zbior fontow
			std::string _key(const std::string& id,int siz);

		public:

			/// Konstruktor
			FontManager(void);

			/// Destruktor
			~FontManager();

			/** Zwraca <B>true</B> jeżeli w zbiorze fontów istnieje font o podanym ID i rozmiarze
			 @param id ID fontu
			 @param siz rozmiar fontu
			 */
			bool Exists(const std::string& id,int siz);

			/** Dodaje do zbioru fontów nowy font
			 @param id ID fontu
			 @param siz rozmiar fontu
			 @param t wskazanie na dodawany font
			 @param overwrite mówi o tym czy należy nadpisać font jeżeli
			                  w zbiorze istnieje już font o podanym ID i rozmiarze
			 */
			void Add(const std::string& id,int siz,Font* t,bool overwrite=false);

			/** Zwraca wskazanie na font określoną poprzez przekazane ID i rozmiar
			 @param id ID tekstury
			 @param siz rozmiar fontu
			 @return wskazanie na font lub 0 jeżeli w zbiorze nie istnieje font o podanym ID i rozmiarze
			 */
			Font* Get(const std::string& id,int siz);

			/** Usuwa font ze zbioru a następnie zwraca wskazanie na niego.
			    Font jako obiekt nie jest niszczona a jedynie usuwana ze zbioru.
			 @param id ID rozmiar
			 @param siz rozmiar fontu
			 @return wskazanie na font lub 0 jeżeli w zbiorze nie istnieje font o podanym ID i rozmiarze
			 */
			Font* Rem(const std::string& id,int siz);

			/** Usuwa font ze zbioru a następnie niszczy obiekt opisujący go.
			 @param id ID fontu
			 @param siz rozmiar fontu
			 */
			void Del(const std::string& id,int siz);

			/** Automatycznie tworzy obiekty fontow na podstawie
			    opisu w pliku konfiguracyjnym.
			    Stworzone obiekty są następnie dodawane do zbiorów.
			 @param filename nazwa pliku konfiguracyjnego
			 @param root scieżka do opisu fontow w pliku konfiguracyjnym
			 */
			int Load(const std::string& filename,const std::string& root="");

			/** Automatycznie tworzy obiekty fontow na podstawie
			    opisu w obiekcie konfiguracyjnym.
			    Stworzone obiekty są następnie dodawane do zbiorów.
			 @param sets obiekt z konfiguracją
			 @param root scieżka do opisu tekstur w pliku konfiguracyjnym
			 */
			int Load(const Core::Settings& sets,const std::string& root="");
	};


/** Rysuje na ekranie napis.
  @param font czcionka jaką ma być rysowany napis
  @param text napis
  @param x współrzędna pozioma początku napisu
  @param y współrzędna pionowa lini bazowej napisu
  @param sizh rozmiar (skala) poziomy czcionki (jeżeli literki mają mieć zachowane proporcje należy podać taką samą wartość jak w sizv)
  @param sizv rozmiar (skala) pionowa czcionki (np. 12 oznacza 12 pixli)
 */
void Text(Font *font,const std::string& text, float x, float y, float sizh, float sizv);

/** Zwraca szerokosc tekstu wyrazona w pixlach (tyle miejsca zajmie napis na ekranie)
  @param font czcionka jaką ma być rysowany napis
  @param text napis
  @param sizh rozmiar (skala) poziomy czcionki (jeżeli literki mają mieć zachowane proporcje należy podać taką samą wartość jak w sizv)
  @param sizv rozmiar (skala) pionowa czcionki (np. 12 oznacza 12 pixli)
 */
float TextLength(Font *font,const std::string& text,float sizh);

/** Rysuje na ekranie podgląd fontu (całą teksturę)
 */
void _render_font(Font *font);


};	//namespace

#endif /*D_FONT_H_D*/
