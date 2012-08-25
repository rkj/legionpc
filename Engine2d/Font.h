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

/** Klasa reprezentuje font (czcionkê).
    Obs³ugiwane s¹ czcionki wektorowe (TrueType).
 */
class Font {
protected:
	/// fizyczna tekstura przechowuj¹ca wygl¹d literek
	PTex *ptex;

	/// logiczna tekstura przechowuj¹ca wygl¹d literek
	LTex *ltex;

	/// tablica szerokoœci literek
	float *glyphs_width;

	/// tablica wysokoœæ literek
	float *glyphs_height;

	/// tablica przesuniêæ literek w poziomie
	float *glyphs_xshift;

	/// tablica przesuniêæ literek w pionie
	float *glyphs_yshift;

	/// tablica przesuniêæ do nastêpnej literki (o ile trzeba zwiêkszyæ pozycjê X aby wydrukowaæ kolejn¹ literkê wystêpuj¹c¹ po tej)
	float *glyphs_advance;

	/// Typ filtrowania przy rysowaniu (musi byc okreslone przed zaladowaniem fontu)
	bool ib_antialiasing;

	/// Ustawia wartoœci inicjalne obiektu
	void _reset(void);

	/// Niszczy sk³adowe obiektu
	void _destroy(void);
public:

	/// Konstuktor
	Font(void);

	/// Destruktor
	~Font();

	/// Ustawia tryb rysowania fontow
	void SetAntialiasing(bool pb_aa);

	/** £aduje font z pliku i tworzy na jego podstawie tekstury s³u¿¹ce do pisania po ekranie.
	 */
	int Load(const std::string& name,int ptx);

	friend void _render_font(Font *font);
	friend void Text(Font *font,const std::string& text, float x, float y, float sizh, float sizv);
	friend float TextLength(Font *font,const std::string& text,float sizh);
};


	/**
		Klasa reprezentuje managera (zarz¹dce) fontów
		<BR>
				 Klasa przechowuje fonty i przypisuje im identyfikatory (stringi),
				 dziêki którym mo¿liwe jest pos³ugiwanie si¿ nazwami fontów zamiast adresami obiektów.
				 Dodatkowo mo¿liwe jest za³adowanie i inicjacja ca³ego zbioru fontów
				 na podstawie definicji zapisanej w pliku konfiguracyjnym.
	*/
	class FontManager {
		protected:
			/// Zbiór fontów
			std::map<std::string,Font*> fonts;

			/// Ustawia wartoœci inicjalne obiektu
			void _reset(void);

			/// Niszczy sk³adowe obiektu
			void _destroy(void);

			/// tworzy klucz indeksujacy zbior fontow
			std::string _key(const std::string& id,int siz);

		public:

			/// Konstruktor
			FontManager(void);

			/// Destruktor
			~FontManager();

			/** Zwraca <B>true</B> je¿eli w zbiorze fontów istnieje font o podanym ID i rozmiarze
			 @param id ID fontu
			 @param siz rozmiar fontu
			 */
			bool Exists(const std::string& id,int siz);

			/** Dodaje do zbioru fontów nowy font
			 @param id ID fontu
			 @param siz rozmiar fontu
			 @param t wskazanie na dodawany font
			 @param overwrite mówi o tym czy nale¿y nadpisaæ font je¿eli
			                  w zbiorze istnieje ju¿ font o podanym ID i rozmiarze
			 */
			void Add(const std::string& id,int siz,Font* t,bool overwrite=false);

			/** Zwraca wskazanie na font okreœlon¹ poprzez przekazane ID i rozmiar
			 @param id ID tekstury
			 @param siz rozmiar fontu
			 @return wskazanie na font lub 0 je¿eli w zbiorze nie istnieje font o podanym ID i rozmiarze
			 */
			Font* Get(const std::string& id,int siz);

			/** Usuwa font ze zbioru a nastêpnie zwraca wskazanie na niego.
			    Font jako obiekt nie jest niszczona a jedynie usuwana ze zbioru.
			 @param id ID rozmiar
			 @param siz rozmiar fontu
			 @return wskazanie na font lub 0 je¿eli w zbiorze nie istnieje font o podanym ID i rozmiarze
			 */
			Font* Rem(const std::string& id,int siz);

			/** Usuwa font ze zbioru a nastêpnie niszczy obiekt opisuj¹cy go.
			 @param id ID fontu
			 @param siz rozmiar fontu
			 */
			void Del(const std::string& id,int siz);

			/** Automatycznie tworzy obiekty fontow na podstawie
			    opisu w pliku konfiguracyjnym.
			    Stworzone obiekty s¹ nastêpnie dodawane do zbiorów.
			 @param filename nazwa pliku konfiguracyjnego
			 @param root scie¿ka do opisu fontow w pliku konfiguracyjnym
			 */
			int Load(const std::string& filename,const std::string& root="");

			/** Automatycznie tworzy obiekty fontow na podstawie
			    opisu w obiekcie konfiguracyjnym.
			    Stworzone obiekty s¹ nastêpnie dodawane do zbiorów.
			 @param sets obiekt z konfiguracj¹
			 @param root scie¿ka do opisu tekstur w pliku konfiguracyjnym
			 */
			int Load(const Core::Settings& sets,const std::string& root="");
	};


/** Rysuje na ekranie napis.
  @param font czcionka jak¹ ma byæ rysowany napis
  @param text napis
  @param x wspó³rzêdna pozioma pocz¹tku napisu
  @param y wspó³rzêdna pionowa lini bazowej napisu
  @param sizh rozmiar (skala) poziomy czcionki (je¿eli literki maj¹ mieæ zachowane proporcje nale¿y podaæ tak¹ sam¹ wartoœæ jak w sizv)
  @param sizv rozmiar (skala) pionowa czcionki (np. 12 oznacza 12 pixli)
 */
void Text(Font *font,const std::string& text, float x, float y, float sizh, float sizv);

/** Zwraca szerokosc tekstu wyrazona w pixlach (tyle miejsca zajmie napis na ekranie)
  @param font czcionka jak¹ ma byæ rysowany napis
  @param text napis
  @param sizh rozmiar (skala) poziomy czcionki (je¿eli literki maj¹ mieæ zachowane proporcje nale¿y podaæ tak¹ sam¹ wartoœæ jak w sizv)
  @param sizv rozmiar (skala) pionowa czcionki (np. 12 oznacza 12 pixli)
 */
float TextLength(Font *font,const std::string& text,float sizh);

/** Rysuje na ekranie podgl¹d fontu (ca³¹ teksturê)
 */
void _render_font(Font *font);


};	//namespace

#endif /*D_FONT_H_D*/
