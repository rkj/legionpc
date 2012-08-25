#ifndef D_SETTINGS_H_D
#define D_SETTINGS_H_D

#include <string>

namespace Core {

/** Klasa reprezentuje plik ustawień.
    Pod pojęciem ustawień rozumiem drzewo, którego węzły mają etykiety (nazwy - niekoniecznie unikalne)
    i które mogą przyjmować wartości spośród typów: long, double, string
    lub tablice elementów tych typów.
    Wartości mogą posiadać jedynie liście.
    Zapis drzewa w pliku ma następującą formę: <BR>
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
		Dostęp do wartości następuje poprzez podanie ścieżki, czyli nazw węzłów oddzielonych kropką, np: <br>
		<code>
			root.wezel2.lisc3		<br>
		</code>
		Jeżeli na danym poziomie jest kilka węzłów o tej samej etykiecie można wskazać, o który węzeł
		chodzi za pomocą inkesu np.: <br>
		<code>
			root.bob[2].y		<br>
		</code>
		Jeżeli jednoznaczne jest o jaki węzeł chodzi, w ścieżce można pominąć nazwę wezła, np: <br>
		<code>
			.wezel2.lisc3  = 	root.wezel2.lisc3	<br>
			root.pliki.[1] =  root.pliki.nazwa[1]	<br>
		</code>

 */
class Settings {
protected:
	/// dane (ukrycie właściwej struktury przechowującej ustawienia)
	void* data;

	/// czy należy zniszczyć dane podczas niszczenia tego obiektu
	bool destroy_data;

	/// ostatni komunikat błędu jaki wystąpił
	std::string last_errm;

	/// ostatni kod błędu jaki wystąpił
	int last_errc;

	/// Ustawia wartości inicjalne obiektu
	void _reset(void);

	/// Niszczy składowe obiektu
	void _destroy(void);

	/// Sprawdza czy dane ustawień są ważne
	bool _checkValid(void);
public:

	/// Konstruktor
	Settings(void);

	/// Destruktor
	~Settings(void);

	/// Przepisuje dane z jednego obiektu do drugiego
	Settings& operator=(const Settings& sets);

	/// Czyta dane z pliku i buduje na ich podstawie drzewo ustawień
	int ReadFile(const std::string& file_name);

	/// Czyta dane z pamięci i buduje na ich podstawie drzewo ustawień
	int ReadBuf(const char* buf);

	/// Czyta dane z pamięci i buduje na ich podstawie drzewo ustawień
	int ReadBuf(const std::string& buf);

	/// Sprawdza czy drzewo ustawień jest poprawnie zbudowane
	bool isValid(void) const;

	/// Zwraca drzewo będące określoną gałęzią tego drzewa
	Settings Extract(const std::string& path) const;

	/// Sprawdza czy istnieje liść o podanym indeksie tablicy wartości
	bool Exists(int vidx=0);

	/// Sprawdza czy istnieje liść o podanym numerze i o podanym indeksie tablicy wartości
	bool Exists(int cidx,int vidx);

	/// Sprawdza czy istnieje liść o podanej ścieżce i o podanym indeksie tablicy wartości
	bool Exists(const std::string& path,int vidx=0);

	/// Zwraca wartość całkowitą liścia o podanym indeksie tablicy wartości
	bool GetValB(int vidx=0);

	/// Zwraca wartość całkowitą liścia o podanym numerze i o podanym indeksie tablicy wartości
	bool GetValB(int cidx,int vidx);

	/// Zwraca wartość całkowitą liścia o podanej ścieżce i o podanym indeksie tablicy wartości
	bool GetValB(const std::string& path,int vidx=0);

	/// Zwraca wartość całkowitą liścia o podanym indeksie tablicy wartości
	long GetValI(int vidx=0);

	/// Zwraca wartość całkowitą liścia o podanym numerze i o podanym indeksie tablicy wartości
	long GetValI(int cidx,int vidx);

	/// Zwraca wartość całkowitą liścia o podanej ścieżce i o podanym indeksie tablicy wartości
	long GetValI(const std::string& path,int vidx=0);

	/// Zwraca wartość zmiennoprzecinkową liścia o podanym indeksie tablicy wartości
	double GetValF(int vidx=0);

	/// Zwraca wartość zmiennoprzecinkową liścia o podanym numerze i o podanym indeksie tablicy wartości
	double GetValF(int cidx,int vidx);

	/// Zwraca wartość zmiennoprzecinkową liścia o podanej ścieżce i o podanym indeksie tablicy wartości
	double GetValF(const std::string& path,int vidx=0);

	/// Zwraca wartość napisową liścia o podanym indeksie tablicy wartości
	const std::string& GetValS(int vidx=0);

	/// Zwraca wartość napisową liścia o podanym numerze i o podanym indeksie tablicy wartości
	const std::string& GetValS(int cidx,int vidx);

	/// Zwraca wartość napisową liścia o podanej ścieżce i o podanym indeksie tablicy wartości
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

	/// Zwraca komunikat ostatniego błędu
	std::string ErrorMsg(void) const;
};

};	//namespace Core

#endif
