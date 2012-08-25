#ifndef D_TEXTURES_H_D
#define D_TEXTURES_H_D

#include <string>
#include <map>

#include <GL/gl.h>
#include <SDL/SDL_image.h>

#include "Utils.h"

namespace Core {
	class Settings;
};

namespace Gfx {

	class Pic;

	/**
		Klasa reprezentuje fizyczn¹ teksturê (bity, piksle, teksele, czy jak to siê jeszcze zwie)
		<BR>
				 Zadaniem klasy jest zaladowanie obrazka, wykonanie ewentualnej konwersji
				 i podlaczenie pixelmapy jako tekstury w systemie OpenGL.
				 Poniewaz tesktury w OpenGL musza miec szerokosc i wysokosc okreslona jako
				 potega dwojki (1,2,4,8,16,32,64,128,256,512,1024) konieczne jest dostosowanie
				 ladowanego obrazka do tego wymogu.
	  @example <BR>
	  		 <CODE>
	  		 PTex *pt = new PTex();
	  		 pt->Load("tekstury.png");
	  		 </CODE>
	*/
	class PTex {

		protected:
			/// ID tekstury w bibliotece OGL
			GLuint texnum;
			/// Szerokosc tekstury w pikslach (tekstury w sensie bufora OGL)
			GLint w;
			/// Wysokosc tekstury w pikslach (tekstury w sensie bufora OGL)
			GLint h;
			/// Szerokosc obrazka sluzacego jako zrodlo tekstury
			int img_w;
			/// Szerokosc obrazka sluzacego jako zrodlo tekstury
			int img_h;
			/// Przelacznik informujacy o tym czy tekstura jest juz "zbindowana" w OpenGL
			bool texbinded;
			/// Tryb filtrowania tekstur
			char ic_filtering;
			/// Domyslny tryb filtrowania tekstur
			static char ic_default_filtering;
			/// Ustawia wartosci inicjalne obiektu
			void _reset(void);
			/// Niszczy skladowe obiektu
			void _destroy(void);
		public:
			/// Tryby filtrowania
			enum FilteringModes {
				FM_NEAREST = 0
			, FM_LINEAR = 1
			, FM_BILINEAR = 2
			, FM_TRILINEAR = 3
			, FM_ANISOTROPIC = 4
			};

			/// Kontruktor - tworzy jedynie obiekt
			PTex(void);
			/// Konstruktor - tworzy obiekt i laduje teksture na podstawie obrazka o podanej nazwie pliku
			PTex(const std::string& name);
			/// Konstruktor - tworzy obiekt na podstawie innego juz istniejacego obiektu
			PTex(const PTex& tex);
			/// Destruktor
			~PTex();
			/// Ustala tryb filtrowania
			void SetFiltering(char mode);
			/// Ustala domyslny tryb filtrowania
			static void SetDefaultFiltering(char mode);
			/// Tworzy teksture na podstawie obrazka w formacie Engine2d
			int Set(Pic *pic,GLint format=GL_RGBA);
			/// Tworzy teksture na podstawie obrazka w formacie SDL
			int Set(SDL_Surface *image,GLint format=GL_RGBA);
			/// Tworzy teksture na podstawie obrazka zapisanego w buforze
			int Set(const unsigned char *buf,int w, int h,GLint format=GL_RGBA);
			/// Tworzy teksture na podstawie obrazka z pliku o podanej nazwie
			int Load(const std::string& name);
			/// Zwraca ID tekstury, ktorym posluguje sie OpenGL
			GLuint GetTexNum(void) { return texnum; }
			/// Zwraca szerokosc tekstury
			int GetWidth(void) { return w; }
			/// Zwraca wysokosc tekstury
			int GetHeight(void) { return h; }
			/// Zwraca szerokosc obrazka, ktory uzyty byl jako zrodlo tekstury
			int GetImgWidth(void) { return img_w; }
			/// Zwraca wysokosc obrazka, ktory uzyty byl jako zrodlo tekstury
			int GetImgHeight(void) { return img_h; }
			friend class LTex;
	};

	/**
		Klasa reprezentuje logiczna teksture
		<BR>
				 Pod pojeciem tekstury logicznej najlepiej rozumiec fragment tekstury fizycznej.
				 Fragment, czyli dowolny wycinek, w tym rowniez cala tekstura fizyczna.
				 Przy wskazywaniu tekstury, ktora ma byc uzywana do rysowania poslugiwac bedziemy
				 sie wlasnie wskazaniem na teksture logiczna.
				 Tekstury logiczne wprowadzone zostaly po to, aby dosc latwo i naturalnie
				 mozna bylo na jednym obrazku umiescic kilka obiektow graficznych.
				 Ulatwia to edycje obrazkow w programach graficznych jak rowniez przyspiesza
				 rysowanie przez OpenGL (mniejsza ilosc przelaczen tekstury - rysowane obiekty sa rozne,
				 ale fizyczna tekstura ta sama)
		@example <BR>
						 <CODE>
			  		 PTex *pt = new PTex(); <BR>
			  		 pt->Load("tekstury.png"); <BR>
						 LTex *lt0 = new LTex(pt); //calosc <BR>
		         LTex *lt1 = new LTex(pt,0.0,0.0,0.5,0.5); //prawa-gorna cwiartka <BR>
		         LTex *lt2 = new LTex(pt,0.5,0.0,1.0,1.0); //prawa polowa <BR>
		         LTex lt3; <BR>
		         lt3.Set(pt,0.0,0.5,0.5,1.0);	//lewa-dolna cwiartka <BR>
		         </CODE>

	*/
	class LTex {
		protected:
			/// Wskazanie na teksture fizyczna
			const PTex	*tex;
			/// Lewy gorny rog fragmentu (wyrazony w pikslach obrazka zrodlowego)
			GLint	ix1;
			/// Lewy gorny rog fragmentu (wyrazony w pikslach obrazka zrodlowego)
			GLint iy1;
			/// Prawy dolny gorny rog fragmentu (wyrazony w pikslach obrazka zrodlowego)
			GLint ix2;
			/// Prawy dolny gorny rog fragmentu (wyrazony w pikslach obrazka zrodlowego)
			GLint iy2;
			/// Lewy gorny rog fragmentu (wyrazony jako ulamek szerokosci obrazka zrodlowego)
			GLfloat	fx1;
			/// Lewy gorny rog fragmentu (wyrazony jako ulamek wysokosci obrazka zrodlowego)
			GLfloat fy1;
			/// Prawy dolny rog fragmentu (wyrazony jako ulamek szerokosci obrazka zrodlowego)
			GLfloat fx2;
			/// Prawy dolny rog fragmentu (wyrazony jako ulamek wysokosci obrazka zrodlowego)
			GLfloat fy2;
			/// Punkt zaczepienia wyrazonyw w ulamku szerokosci tekstury
			GLfloat fhsx;
			/// Punkt zaczepienia wyrazonyw w ulamku wysokosci tekstury
			GLfloat fhsy;
			/// Ustawia wartosci inicjalne obiektu
			void	_reset(void);
			/// Niszczy skladowe obiektu
			void	_destroy(void);
			/// Funkcja konwertuje wspolrzedne pixlowe na ulamek szerokosci
			float	_i2fw(int v) const;
			/// Funkcja konwertuje wspolrzedne pixlowe na ulamek wysokosci
			float	_i2fh(int v) const;
			/// Funkcja konwertuje ulamek szerokosci na wspolrzedne pixlowe
			int		_f2iw(float v) const;
			/// Funkcja konwertuje ulamek wysokosci na wspolrzedne pixlowe
			int		_f2ih(float v) const;
		public:
			/// Konstruktor - tworzy pusty obiekt
			LTex(void);
			/// Konstruktor - tworzy teksture logiczna pokrywajaca cala teksture fizyczna
			LTex( const PTex* tex );
			/// Konstruktor - tworzy teksture logiczna jako fragment tekstury fizycznej wyrazony we wspolrzednych pixlowych
			LTex( const PTex* tex, int x1, int y1, int x2, int y2 );
			/// Konstruktor - tworzy teksture logiczna jako fragment tekstury fizycznej wyrazony we wspolrzednych ulamkowych
			LTex( const PTex* tex, float x1, float y1, float x2, float y2 );
			/// Tworzy teksture logiczna pokrywajaca cala teksture fizyczna
			void Set( const PTex* tex );
			/// Tworzy teksture logiczna jako fragment tekstury fizycznej wyrazony we wspolrzednych pixlowych
			void Set( const PTex* tex, int x1, int y1, int x2, int y2 );
			/// Tworzy teksture logiczna jako fragment tekstury fizycznej wyrazony we wspolrzednych ulamkowych
			void Set( const PTex* tex, float x1, float y1, float x2, float y2 );
			/// Ustawia punkt zaczepienia
			void SetHotSpot( float xs, float ys ) {
				fhsx = xs; fhsy = ys;
			}
			/// Destruktor
			~LTex();
			/// Zwraca ID tekstury wykorzystywane przez OpenGL
			GLuint GetTextureID(void) const;
			/// Zwraca wpolrzedna ulamkowa X prawego gornego rogu fragmentu
			GLfloat Getfx1(void) const { return fx1; }
			/// Zwraca wpolrzedna ulamkowa Y prawego gornego rogu fragmentu
			GLfloat Getfy1(void) const { return fy1; }
			/// Zwraca wpolrzedna ulamkowa X lewego dolnego rogu fragmentu
			GLfloat Getfx2(void) const { return fx2; }
			/// Zwraca wpolrzedna ulamkowa Y lewego dolnego rogu fragmentu
			GLfloat Getfy2(void) const { return fy2; }
			/// Zwraca wpolrzedna pikslowa X prawego gornego rogu fragmentu
			GLfloat Getix1(void) const { return ix1; }
			/// Zwraca wpolrzedna pikslowa Y prawego gornego rogu fragmentu
			GLfloat Getiy1(void) const { return iy1; }
			/// Zwraca wpolrzedna pikslowa X lewego dolnego rogu fragmentu
			GLfloat Getix2(void) const { return ix2; }
			/// Zwraca wpolrzedna pikslowa Y lewego dolnego rogu fragmentu
			GLfloat Getiy2(void) const { return iy2; }
			/// Zwraca szerokosc tekstury w pixlach
			int GetWidth(void) const { return Abs(ix2 - ix1); }
			/// Zwraca wysokosc tekstury w pixlach
			int GetHeight(void) const { return Abs(iy2 - iy1); }
			/// Zwraca wsp. X punktu zaczepienia
			float GetHotSpotX(void) const { return fhsx; }
			/// Zwraca wsp. Y punktu zaczepienia
			float GetHotSpotY(void) const { return fhsy; }
			/// Zwraca teksture fizyczna, z ktora skojarzona jest ta tekstura logiczna
			const PTex* GetPTex(void) { return tex; }
			friend class Bob;
	};

	/**
		Klasa reprezentuje managera (zarz¹dce) tekstur
		<BR>
				 Aby ¿ycie by³o jeszcze prostrze wprowadzone zostaje pojêcie zarz¹dcy tekstur.
				 Mo¿na ca³kowicie zrezygnowaæ z korzystania z tej klasy, ale po co ? ;-)
				 Klasa przechowuje tekstury fizyczne i logiczne i przypisuje im identyfikatory (stringi),
				 dziêki którym mo¿liwe jest pos³ugiwanie si¿ nazwami tekstur zamiast adresami obiektów.
				 Dodatkowo mo¿liwe jest za³adowanie i inicjacja ca³ego zbioru tekstur fizycznych i logicznych
				 na podstawie definicji zapisanej w pliku konfiguracyjnym.
	*/
	class TextureManager {
		protected:
			/// Zbiór tekstur fizycznych
			std::map<std::string,PTex*> ptex;

			/// Zbiór tekstur logicznych
			std::map<std::string,LTex*> ltex;

			/// Zbiór flag dotycz¹cych tekstur fizycznych
			std::map<std::string,unsigned char> ptex_flags;

			/// Zbiór flag dotycz¹cych tekstur logicznych
			std::map<std::string,unsigned char> ltex_flags;

			/// Ustawia wartoœci inicjalne obiektu
			void _reset(void);

			/// Niszczy sk³adowe obiektu
			void _destroy(void);

			///Flagi
			enum Flags {
				FL_ISREF	= 0x01
			};

		public:

			/// Konstruktor
			TextureManager(void);

			/// Destruktor
			~TextureManager();

			/** Zwraca <B>true</B> je¿eli w zbiorze tekstur fizycznych istnieje tekstura o podanym ID
			 @param id ID tekstury
			 */
			bool ExistsPTex(const std::string& id);

			/** Zwraca <B>true</B> je¿eli w zbiorze tekstur logicznych istnieje tekstura o podanym ID
			 @param id ID tekstury
			 */
			bool ExistsLTex(const std::string& id);

			/** Dodaje do zbioru tekstur fizycznych now¹ teksturê
			 @param id ID tekstury
			 @param t wskazanie na dodawan¹ teksturê
			 @param overwrite mówi o tym czy nale¿y nadpisaæ teksturê je¿eli
			                  w zbiorze istnieje ju¿ tekstura o podanym ID
			 @param ref mówi o tym czy nie nale¿y usuwaæ tekstury (manager nie stanie siê w³aœcicielem obiektu je¿eli ref=true)
			 */
			void AddPTex(const std::string& id,PTex* t,bool overwrite=false,bool ref=false);

			/** Dodaje do zbioru tekstur logicznych now¹ teksturê
			 @param id ID tekstury
			 @param t wskazanie na dodawan¹ teksturê
			 @param overwrite mówi o tym czy nale¿y nadpisaæ teksturê je¿eli
			                  w zbiorze istnieje ju¿ tekstura o podanym ID
			 @param ref mówi o tym czy nie nale¿y usuwaæ tekstury (manager nie stanie siê w³aœcicielem obiektu je¿eli ref=true)
			 */
			void AddLTex(const std::string& id,LTex* t,bool overwrite=false,bool ref=false);

			/** Zwraca wskazanie na teksture fizyczn¹ okreœlon¹ poprzez przekazane ID
			 @param id ID tekstury
			 @return wskazanie na teksturê lub 0 je¿eli w zbiorze nie istnieje tekstura o podanym ID
			 */
			PTex* GetPTex(const std::string& id);

			/** Zwraca wskazanie na teksture logiczn¹ okreœlon¹ poprzez przekazane ID
			 @param id ID tekstury
			 @return wskazanie na teksturê lub 0 je¿eli w zbiorze nie istnieje tekstura o podanym ID
			 */
			LTex* GetLTex(const std::string& id);

			/** Usuwa teksture fizyczn¹ ze zbioru a nastêpnie zwraca wskazanie na ni¹.
			    Tekstura jako obiekt nie jest niszczona a jedynie usuwana ze zbioru.
			 @param id ID tekstury
			 @return wskazanie na teksturê lub 0 je¿eli w zbiorze nie istnieje tekstura o podanym ID
			 */
			PTex* RemPTex(const std::string& id);

			/** Usuwa teksture logiczn¹ ze zbioru a nastêpnie zwraca wskazanie na ni¹.
			    Tekstura jako obiekt nie jest niszczona a jedynie usuwana ze zbioru.
			 @param id ID tekstury
			 @return wskazanie na teksturê lub 0 je¿eli w zbiorze nie istnieje tekstura o podanym ID
			 */
			LTex* RemLTex(const std::string& id);

			/** Usuwa teksture fizyczn¹ ze zbioru a nastêpnie niszczy obiekt opisuj¹cy j¹.
			 @param id ID tekstury
			 */
			void DelPTex(const std::string& id);

			/** Usuwa teksture logiczn¹ ze zbioru a nastêpnie niszczy obiekt opisuj¹cy j¹.
			 @param id ID tekstury
			 */
			void DelLTex(const std::string& id);

			/** Usuwa wszystkie tekstury ze zbioru a nastêpnie niszczy obiekty opisuj¹ce je.
			 */
			void DelAll(void);

			/** Zwraca ilosc tesktur fizycznych
			 */
		  int CountPTex(void);

			/** Zwraca ilosc tesktur logicznych
			 */
		  int CountLTex(void);

			/** Automatycznie tworzy obiekty tekstur fizycznych i logicznych na podstawie
			    opisu w pliku konfiguracyjnym.
			    Stworzone obiekty s¹ nastêpnie dodawane do zbiorów.
			    Oprócz zebrania opisu tekstur w jednym miejscu dodatkow¹ zalet¹ wykorzystania
			    managera tekstur i metody <B>Load</B> jest uniezale¿nienie pracy grafika od pracy
			    programisty (zmiany w teksturach nie poci¹gaj¹ za sob¹ koniecznoœci kompilacji).
			 @param filename nazwa pliku konfiguracyjnego
			 @param root scie¿ka do opisu tekstur w pliku konfiguracyjnym
			 @example Czêœæ pliku konfiguracyjnego odpowiedzialna za tekstury wygl¹da nastêpuj¹co: <BR>
			          <CODE>
Textures { <BR>
	Phisical { <BR>
		ID = "bobs" <BR>
		FileName = "Data/tekstury_new.png" <BR>
	} <BR>
	Logical { <BR>
		ID = "ship" <BR>
		PID = "bobs" <BR>
		Pos = (158,6,210,70) <BR>
		HotSpot = (185,37) <BR>
	} <BR>
	Logical { <BR>
		ID = "bullet" <BR>
		PID = "bobs" <BR>
		Pos = (89,75,98,92) <BR>
		HotSpot = (94,79) <BR>
	} <BR>
	Logical { <BR>
		ID = "base" <BR>
		PID = "bobs" <BR>
		Pos = (4,196,98,294) <BR>
		HotSpot = (50,245) <BR>
	} <BR>
	Logical { <BR>
		ID = "meteor" <BR>
		PID = "bobs" <BR>
		Pos = (107,58,124,75) <BR>
		HotSpot = (116,66) <BR>
	} <BR>
	Logical { <BR>
		ID = "star" <BR>
		PID = "bobs" <BR>
		Pos = (131,61,144,73) <BR>
		HotSpot = (138,67) <BR>
	} <BR>
} <BR>
			          </CODE>
			 */
			int Load(const std::string& filename,const std::string& root="");

			/** Automatycznie tworzy obiekty tekstur fizycznych i logicznych na podstawie
			    opisu w obiekcie konfiguracyjnym.
			    Stworzone obiekty s¹ nastêpnie dodawane do zbiorów.
			 @param sets obiekt z konfiguracj¹
			 @param root scie¿ka do opisu tekstur w pliku konfiguracyjnym
			 */
			int Load(const Core::Settings& sets,const std::string& root="");
	};

};

#endif
