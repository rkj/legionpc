#ifndef D_SAMPLES_H_D
#define D_SAMPLES_H_D

#include <string>
#include <map>

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

namespace Core {
	class Settings;
};

namespace Sfx {

    class LSam;

    int PlaySample(const LSam *sam,int loops=0);
    int PlaySample(const LSam *sam,int vol,int loops=0);

	class PSam {
	protected:
		Mix_Chunk *sample;
		int len;
	public:
		PSam(void);
		~PSam();
		void Set(Mix_Chunk *sam);
		int Load(const std::string& name);
		int GetLength(void) const;
		friend class LSam;
	};

	class LSam {
	protected:
		const PSam *sam;
		int offset,len;
		void _reset(void);
		void _destroy(void);
		Mix_Chunk* _GetMixChunk(void) const;
	public:
		LSam(void);
		LSam(const PSam *sam);
		LSam(const PSam *sam,int offset,int len);
		~LSam();
		void Set(const PSam *sam);
		void Set(const PSam *sam,int offset,int len);
		int GetOffset(void) const;
		int GetLength(void) const;
		friend int PlaySample(const LSam *sam,int loops);
		friend int PlaySample(const LSam *sam,int vol,int loops);
	};


	/**
		Klasa reprezentuje managera (zarz¹dce) sampli
		<BR>
				 Mo¿na ca³kowicie zrezygnowaæ z korzystania z tej klasy, ale po co siê mêczyæ? ;-)
				 Klasa przechowuje sample (dŸwiêki) fizyczne i logiczne i przypisuje im identyfikatory (stringi),
				 dziêki którym mo¿liwe jest pos³ugiwanie siê nazwami zamiast adresami obiektów.
				 Dodatkowo mo¿liwe jest za³adowanie i inicjacja ca³ego zbioru sampli fizycznych i logicznych
				 na podstawie definicji zapisanej w pliku konfiguracyjnym.
	*/
	class SampleManager {
		protected:
			/// Zbiór sampli fizycznych
			std::map<std::string,PSam*> psam;

			/// Zbiór sampli logicznych
			std::map<std::string,LSam*> lsam;

			/// Ustawia wartoœci inicjalne obiektu
			void _reset(void);

			/// Niszczy sk³adowe obiektu
			void _destroy(void);

		public:

			/// Konstruktor
			SampleManager(void);

			/// Destruktor
			~SampleManager();

			/** Zwraca <B>true</B> je¿eli w zbiorze sampli fizycznych istnieje sampel o podanym ID
			 @param id ID sampla
			 */
			bool ExistsPSam(const std::string& id);

			/** Zwraca <B>true</B> je¿eli w zbiorze sampli logicznych istnieje sampel o podanym ID
			 @param id ID sampel
			 */
			bool ExistsLSam(const std::string& id);

			/** Dodaje do zbioru sampli fizycznych nowy sampel
			 @param id ID sampla
			 @param t wskazanie na dodawany sampel
			 @param overwrite mówi o tym czy nale¿y nadpisaæ sampel je¿eli
			                  w zbiorze istnieje ju¿ sampel o podanym ID
			 */
			void AddPSam(const std::string& id,PSam* s,bool overwrite=false);

			/** Dodaje do zbioru sampli logicznych nowy sampel
			 @param id ID sampla
			 @param t wskazanie na dodawany sampel
			 @param overwrite mówi o tym czy nale¿y nadpisaæ sampel je¿eli
			                  w zbiorze istnieje ju¿ sampel o podanym ID
			 */
			void AddLSam(const std::string& id,LSam* s,bool overwrite=false);

			/** Zwraca wskazanie na sampel fizyczny okreœlony poprzez przekazane ID
			 @param id ID sampla
			 @return wskazanie na sampel lub 0 je¿eli w zbiorze nie istnieje sampel o podanym ID
			 */
			PSam* GetPSam(const std::string& id);

			/** Zwraca wskazanie na sampel logiczny okreœlony poprzez przekazane ID
			 @param id ID sampla
			 @return wskazanie na sampel lub 0 je¿eli w zbiorze nie istnieje sampel o podanym ID
			 */
			LSam* GetLSam(const std::string& id);

			/** Usuwa sampel fizyczny ze zbioru a nastêpnie zwraca wskazanie na niego.
			    Sampel jako obiekt nie jest niszczony a jedynie usuwany ze zbioru.
			 @param id ID sampla
			 @return wskazanie na sampel lub 0 je¿eli w zbiorze nie istnieje sampel o podanym ID
			 */
			PSam* RemPSam(const std::string& id);

			/** Usuwa sampel logiczny ze zbioru a nastêpnie zwraca wskazanie na niego.
			    Sampel jako obiekt nie jest niszczony a jedynie usuwany ze zbioru.
			 @param id ID sampla
			 @return wskazanie na sampel lub 0 je¿eli w zbiorze nie istnieje sampel o podanym ID
			 */
			LSam* RemLSam(const std::string& id);

			/** Usuwa sampel fizyczny ze zbioru a nastêpnie niszczy obiekt opisuj¹cy go.
			 @param id ID sampla
			 */
			void DelPSam(const std::string& id);

			/** Usuwa sampel logiczny ze zbioru a nastêpnie niszczy obiekt opisuj¹cy go.
			 @param id ID sampla
			 */
			void DelLSam(const std::string& id);

			/** Usuwa wszystkie sample ze zbioru a nastêpnie niszczy obiekty opisuj¹ce je.
			 */
			void DelAll(void);

			/** Zwraca ilosc sampli fizycznych
			 */
		  int CountPSam(void);

			/** Zwraca ilosc sampli logicznych
			 */
		  int CountLSam(void);

			/** Automatycznie tworzy obiekty sampli fizycznych i logicznych na podstawie
			    opisu w pliku konfiguracyjnym.
			    Stworzone obiekty s¹ nastêpnie dodawane do zbiorów.
			    Oprócz zebrania opisu sampli w jednym miejscu dodatkow¹ zalet¹ wykorzystania
			    managera sampli i metody <B>Load</B> jest uniezale¿nienie pracy dŸwiêkowca od pracy
			    programisty (zmiany w samplach nie poci¹gaj¹ za sob¹ koniecznoœci kompilacji).
			 @param filename nazwa pliku konfiguracyjnego
			 @param root scie¿ka do opisu sampli w pliku konfiguracyjnym
			 @example Czêœæ pliku konfiguracyjnego odpowiedzialna za sample wygl¹da nastêpuj¹co: <BR>
			          <CODE>
Samples { <BR>
	Phisical { <BR>
		ID = "main" <BR>
		FileName = "Data/sounds.wav" <BR>
	} <BR>
	Logical { <BR>
		ID = "ship" <BR>
		PID = "main" <BR>
		Offset = 1000 <BR>
		Length = 15000 <BR>
	} <BR>
	Logical { <BR>
		ID = "bullet" <BR>
		PID = "main" <BR>
		Offset = 0 <BR>
		Length = 999 <BR>
	} <BR>
} <BR>
			          </CODE>
			 */
			int Load(const std::string& filename,const std::string& root="");

			/** Automatycznie tworzy obiekty sampli fizycznych i logicznych na podstawie
			    opisu w obiekcie konfiguracyjnym.
			    Stworzone obiekty s¹ nastêpnie dodawane do zbiorów.
			 @param sets obiekt z konfiguracj¹
			 @param root scie¿ka do opisu tekstur w pliku konfiguracyjnym
			 */
			int Load(const Core::Settings& sets,const std::string& root="");
	};

};

#endif
