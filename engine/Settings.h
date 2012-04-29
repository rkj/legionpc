#ifndef D_SETTINGS_H_D
#define D_SETTINGS_H_D

#include <string>

namespace Core {

/** Klasa reprezentuje plik ustawieñ.
    Pod pojêciem ustawieñ rozumiem drzewo, którego wêz³y maj¹ etykiety (nazwy - niekoniecznie unikalne)
    i które mog¹ przyjmowaæ wartoœci spoœród typów: long, double, string
    lub tablice elementów tych typów.
    Wartoœci mog¹ posiadaæ jedynie liœcie.
    Zapis drzewa w pliku ma nastêpuj¹c¹ formê: <BR>
		<CODE>
		root {	<br>
			wezel1 {	<br>
				lisc1 = 1234						//wartosc typu int	<br>
				lisc2 = 98.765					//wartosc typu double	<br>
				lisc3 = "ala ma kota"		//wartosc typu string	<br>
			}	<br>
			wezel2 {	<br>
				lisc1 = (1,2,3,5,8,13)		//tablica wartosci typu int	<br>
				lisc2 = (0.0, 1.0, 3.141)	//tablica wartosci typu double	<br>
				lisc3 = ("A","B","C")			//tablica wartosci typu string	<br>
			}	<br>
			bob {	<br>
				x = 10	<br>
				y = 10	<br>
			}	<br>
			bob {	<br>
				x = 20	<br>
				y = 50	<br>
			}	<br>
			pliki { <br>
				nazwa = "c:\a.txt" <br>
				nazwa = "c:\b.jpg" <br>
			} <br>
		}	<br>
		</CODE>
		Dostêp do wartoœci nastêpuje poprzez podanie œcie¿ki, czyli nazw wêz³ów oddzielonych kropk¹, np: <br>
		<code>
			root.wezel2.lisc3		<br>
		</code>
		Je¿eli na danym poziomie jest kilka wêz³ów o tej samej etykiecie mo¿na wskazaæ, o który wêze³
		chodzi za pomoc¹ inkesu np.: <br>
		<code>
			root.bob[2].y		<br>
		</code>
		Je¿eli jednoznaczne jest o jaki wêze³ chodzi, w œcie¿ce mo¿na pomin¹æ nazwê wez³a, np: <br>
		<code>
			.wezel2.lisc3  = 	root.wezel2.lisc3	<br>
			root.pliki.[1] =  root.pliki.nazwa[1]	<br>
		</code>

 */
class Settings {
protected:
	/// dane (ukrycie w³aœciwej struktury przechowuj¹cej ustawienia)
	void* data;

	/// czy nale¿y zniszczyæ dane podczas niszczenia tego obiektu
	bool destroy_data;

	/// ostatni komunikat b³êdu jaki wyst¹pi³
	std::string last_errm;

	/// ostatni kod b³êdu jaki wyst¹pi³
	int last_errc;

	/// Ustawia wartoœci inicjalne obiektu
	void _reset(void);

	/// Niszczy sk³adowe obiektu
	void _destroy(void);

	/// Sprawdza czy dane ustawieñ s¹ wa¿ne
	bool _checkValid(void);
public:

	/// Konstruktor
	Settings(void);

	/// Destruktor
	~Settings(void);

	/// Przepisuje dane z jednego obiektu do drugiego
	Settings& operator=(const Settings& sets);

	/// Czyta dane z pliku i buduje na ich podstawie drzewo ustawieñ
	int ReadFile(const std::string& file_name);

	/// Czyta dane z pamiêci i buduje na ich podstawie drzewo ustawieñ
	int ReadBuf(const char* buf);

	/// Czyta dane z pamiêci i buduje na ich podstawie drzewo ustawieñ
	int ReadBuf(const std::string& buf);

	/// Sprawdza czy drzewo ustawieñ jest poprawnie zbudowane
	bool isValid(void) const;

	/// Zwraca drzewo bêd¹ce okreœlon¹ ga³êzi¹ tego drzewa
	Settings Extract(const std::string& path) const;

	/// Sprawdza czy istnieje liœæ o podanym indeksie tablicy wartoœci
	bool Exists(int vidx=0);

	/// Sprawdza czy istnieje liœæ o podanym numerze i o podanym indeksie tablicy wartoœci
	bool Exists(int cidx,int vidx);

	/// Sprawdza czy istnieje liœæ o podanej œcie¿ce i o podanym indeksie tablicy wartoœci
	bool Exists(const std::string& path,int vidx=0);

	/// Zwraca wartoœæ ca³kowit¹ liœcia o podanym indeksie tablicy wartoœci
	bool GetValB(int vidx=0);

	/// Zwraca wartoœæ ca³kowit¹ liœcia o podanym numerze i o podanym indeksie tablicy wartoœci
	bool GetValB(int cidx,int vidx);

	/// Zwraca wartoœæ ca³kowit¹ liœcia o podanej œcie¿ce i o podanym indeksie tablicy wartoœci
	bool GetValB(const std::string& path,int vidx=0);

	/// Zwraca wartoœæ ca³kowit¹ liœcia o podanym indeksie tablicy wartoœci
	long GetValI(int vidx=0);

	/// Zwraca wartoœæ ca³kowit¹ liœcia o podanym numerze i o podanym indeksie tablicy wartoœci
	long GetValI(int cidx,int vidx);

	/// Zwraca wartoœæ ca³kowit¹ liœcia o podanej œcie¿ce i o podanym indeksie tablicy wartoœci
	long GetValI(const std::string& path,int vidx=0);

	/// Zwraca wartoœæ zmiennoprzecinkow¹ liœcia o podanym indeksie tablicy wartoœci
	double GetValF(int vidx=0);

	/// Zwraca wartoœæ zmiennoprzecinkow¹ liœcia o podanym numerze i o podanym indeksie tablicy wartoœci
	double GetValF(int cidx,int vidx);

	/// Zwraca wartoœæ zmiennoprzecinkow¹ liœcia o podanej œcie¿ce i o podanym indeksie tablicy wartoœci
	double GetValF(const std::string& path,int vidx=0);

	/// Zwraca wartoœæ napisow¹ liœcia o podanym indeksie tablicy wartoœci
	const std::string& GetValS(int vidx=0);

	/// Zwraca wartoœæ napisow¹ liœcia o podanym numerze i o podanym indeksie tablicy wartoœci
	const std::string& GetValS(int cidx,int vidx);

	/// Zwraca wartoœæ napisow¹ liœcia o podanej œcie¿ce i o podanym indeksie tablicy wartoœci
	const std::string& GetValS(const std::string& path,int vidx=0);

	bool IsValB();
	bool IsValB(int cidx);
	bool IsValB(const std::string& path);
	bool IsValI();
	bool IsValI(int cidx);
	bool IsValI(const std::string& path);
	bool IsValF();
	bool IsValF(int cidx);
	bool IsValF(const std::string& path);
	bool IsValS();
	bool IsValS(int cidx);
	bool IsValS(const std::string& path);

	/// Zrzuca dane drzewo do stringa - dla celów diagnostycznych
	std::string Dump(void) const;

	/// Zwraca komunikat ostatniego b³êdu
	std::string ErrorMsg(void) const;
};

};	//namespace Core

#endif
