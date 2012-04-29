#ifndef D_SETTINGS_H_D
#define D_SETTINGS_H_D

#include <string>

namespace Core {

/** Klasa reprezentuje plik ustawie�.
    Pod poj�ciem ustawie� rozumiem drzewo, kt�rego w�z�y maj� etykiety (nazwy - niekoniecznie unikalne)
    i kt�re mog� przyjmowa� warto�ci spo�r�d typ�w: long, double, string
    lub tablice element�w tych typ�w.
    Warto�ci mog� posiada� jedynie li�cie.
    Zapis drzewa w pliku ma nast�puj�c� form�: <BR>
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
		Dost�p do warto�ci nast�puje poprzez podanie �cie�ki, czyli nazw w�z��w oddzielonych kropk�, np: <br>
		<code>
			root.wezel2.lisc3		<br>
		</code>
		Je�eli na danym poziomie jest kilka w�z��w o tej samej etykiecie mo�na wskaza�, o kt�ry w�ze�
		chodzi za pomoc� inkesu np.: <br>
		<code>
			root.bob[2].y		<br>
		</code>
		Je�eli jednoznaczne jest o jaki w�ze� chodzi, w �cie�ce mo�na pomin�� nazw� wez�a, np: <br>
		<code>
			.wezel2.lisc3  = 	root.wezel2.lisc3	<br>
			root.pliki.[1] =  root.pliki.nazwa[1]	<br>
		</code>

 */
class Settings {
protected:
	/// dane (ukrycie w�a�ciwej struktury przechowuj�cej ustawienia)
	void* data;

	/// czy nale�y zniszczy� dane podczas niszczenia tego obiektu
	bool destroy_data;

	/// ostatni komunikat b��du jaki wyst�pi�
	std::string last_errm;

	/// ostatni kod b��du jaki wyst�pi�
	int last_errc;

	/// Ustawia warto�ci inicjalne obiektu
	void _reset(void);

	/// Niszczy sk�adowe obiektu
	void _destroy(void);

	/// Sprawdza czy dane ustawie� s� wa�ne
	bool _checkValid(void);
public:

	/// Konstruktor
	Settings(void);

	/// Destruktor
	~Settings(void);

	/// Przepisuje dane z jednego obiektu do drugiego
	Settings& operator=(const Settings& sets);

	/// Czyta dane z pliku i buduje na ich podstawie drzewo ustawie�
	int ReadFile(const std::string& file_name);

	/// Czyta dane z pami�ci i buduje na ich podstawie drzewo ustawie�
	int ReadBuf(const char* buf);

	/// Czyta dane z pami�ci i buduje na ich podstawie drzewo ustawie�
	int ReadBuf(const std::string& buf);

	/// Sprawdza czy drzewo ustawie� jest poprawnie zbudowane
	bool isValid(void) const;

	/// Zwraca drzewo b�d�ce okre�lon� ga��zi� tego drzewa
	Settings Extract(const std::string& path) const;

	/// Sprawdza czy istnieje li�� o podanym indeksie tablicy warto�ci
	bool Exists(int vidx=0);

	/// Sprawdza czy istnieje li�� o podanym numerze i o podanym indeksie tablicy warto�ci
	bool Exists(int cidx,int vidx);

	/// Sprawdza czy istnieje li�� o podanej �cie�ce i o podanym indeksie tablicy warto�ci
	bool Exists(const std::string& path,int vidx=0);

	/// Zwraca warto�� ca�kowit� li�cia o podanym indeksie tablicy warto�ci
	bool GetValB(int vidx=0);

	/// Zwraca warto�� ca�kowit� li�cia o podanym numerze i o podanym indeksie tablicy warto�ci
	bool GetValB(int cidx,int vidx);

	/// Zwraca warto�� ca�kowit� li�cia o podanej �cie�ce i o podanym indeksie tablicy warto�ci
	bool GetValB(const std::string& path,int vidx=0);

	/// Zwraca warto�� ca�kowit� li�cia o podanym indeksie tablicy warto�ci
	long GetValI(int vidx=0);

	/// Zwraca warto�� ca�kowit� li�cia o podanym numerze i o podanym indeksie tablicy warto�ci
	long GetValI(int cidx,int vidx);

	/// Zwraca warto�� ca�kowit� li�cia o podanej �cie�ce i o podanym indeksie tablicy warto�ci
	long GetValI(const std::string& path,int vidx=0);

	/// Zwraca warto�� zmiennoprzecinkow� li�cia o podanym indeksie tablicy warto�ci
	double GetValF(int vidx=0);

	/// Zwraca warto�� zmiennoprzecinkow� li�cia o podanym numerze i o podanym indeksie tablicy warto�ci
	double GetValF(int cidx,int vidx);

	/// Zwraca warto�� zmiennoprzecinkow� li�cia o podanej �cie�ce i o podanym indeksie tablicy warto�ci
	double GetValF(const std::string& path,int vidx=0);

	/// Zwraca warto�� napisow� li�cia o podanym indeksie tablicy warto�ci
	const std::string& GetValS(int vidx=0);

	/// Zwraca warto�� napisow� li�cia o podanym numerze i o podanym indeksie tablicy warto�ci
	const std::string& GetValS(int cidx,int vidx);

	/// Zwraca warto�� napisow� li�cia o podanej �cie�ce i o podanym indeksie tablicy warto�ci
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

	/// Zrzuca dane drzewo do stringa - dla cel�w diagnostycznych
	std::string Dump(void) const;

	/// Zwraca komunikat ostatniego b��du
	std::string ErrorMsg(void) const;
};

};	//namespace Core

#endif
