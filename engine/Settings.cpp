
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "settings_parser.hh"
#include "Settings.h"

using namespace std;

namespace Core {
using namespace cppcc;

static const string gs_null = "";

void Settings :: _reset(void) {
	data = 0;
	destroy_data = false;
	last_errm = "";
	last_errc = 0;
}

void Settings :: _destroy(void) {
	if( data && destroy_data ) {
		delete (Symbol*)data;
	}
}

Settings :: Settings(void) {
	_reset();
}

Settings :: ~Settings(void) {
	_destroy();
}

Settings& Settings :: operator=(const Settings& sets) {
	_destroy();
	_reset();
	data = ((Symbol*)(sets.data));
	destroy_data = false;
	last_errm = gs_null;
	last_errc = 0;
	return *this;
}

int Settings :: ReadFile(const string& file_name) {

	istream *ifs = 0;
	Symbol *sym = 0;
	SettingsParser *parser = 0;

	//otwieramy strumien
	try {
		ifs = new ifstream(file_name.c_str());
	} catch(...) {
		last_errm = "B³¹d otwierania pliku " + file_name;
		last_errc = -1;
		goto blad;
	}

	//tworzymy parser
	parser = new SettingsParser(ifs);

	//parsujemy plik
	try {
		sym = parser->parse();
	} catch(ScanException &scex) {
		last_errm = (string)scex;
		last_errc = -2;
		goto blad;
	} catch(ParseException &pex) {
		last_errm = (string) pex + "( before: " + parser->scanner.la(0)->image()
							+ " " + parser->scanner.la(1)->image() + ")";
		last_errc = -3;
		goto blad;
	} catch(...) {
		last_errm = "Nieznany wyj³tek";
		last_errc = -5;
		goto blad;
	}

	if( 0 == sym ) {
		last_errm = "Pusty plik";
		last_errc = -4;
		goto blad;
	}

	//i gotowe - zapamietujemy sparsowana strukture
	_destroy();
	data = (void*)sym;
	destroy_data = true;
	last_errm = "";
	last_errc = 0;
blad:
	if( parser ) delete parser;
	if( ifs ) delete ifs;
	return last_errc;
}

int Settings :: ReadBuf(const char* buf) {
	return ReadBuf(string(buf));
}

int Settings :: ReadBuf(const string& buf) {

	istringstream *ifs = 0;
	Symbol *sym = 0;
	SettingsParser *parser = 0;

	//otwieramy strumien
	try {
		ifs = new istringstream(buf);
	} catch(...) {
		last_errm = "B³¹d otwierania strumienia na buforze";
		last_errc = -1;
		goto blad;
	}

	//tworzymy parser
	parser = new SettingsParser(ifs);

	//parsujemy plik
	try {
		sym = parser->parse();
	} catch(ScanException &scex) {
		last_errm = (string)scex;
		last_errc = -2;
		goto blad;
	} catch(ParseException &pex) {
		last_errm = (string) pex + "( before: " + parser->scanner.la(0)->image()
							+ " " + parser->scanner.la(1)->image() + ")";
		last_errc = -3;
		goto blad;
	}

	if( 0 == sym ) {
		last_errm = "Pusty plik";
		last_errc = -4;
		goto blad;
	}

	//i gotowe - zapamietujemy sparsowana strukture
	_destroy();
	data = (void*)sym;
	destroy_data = true;
	last_errm = "";
	last_errc = 0;
blad:
	if( parser ) delete parser;
	if( ifs ) delete ifs;
	return last_errc;
}

bool Settings :: isValid(void) const {
	return 0 != data;
}

bool Settings :: _checkValid(void) {
	if( ! isValid() ) {
		last_errm = "Obiekt ustawieñ nie jest wa¿ny";
		last_errc = -100;
		return false;
	}
	return true;
}

Settings Settings :: Extract(const string& path) const {

	Settings s;

	if( ! isValid() ) {
		s.last_errm = "Obiekt ustawieñ nie jest wa¿ny";
		s.last_errc = -100;
		return s;
	}

	//otwieramy strumien
	istringstream  *ifs;
		try {
		ifs = new istringstream(path);
	} catch(...) {
		s.last_errm = "B³¹d otwierania strumienia na buforze";
		s.last_errc = -1;
		return s;
	}

	//tworzymy parser
	SettingsParser parser(ifs);

	//parsujemy plik
	Symbol *sym = 0;
	try {
		sym = parser.extract((Symbol*)this->data);
	} catch(ScanException &scex) {
		s.last_errm = (string)scex;
		s.last_errc = -2;
		return s;
	} catch(ParseException &pex) {
		s.last_errm = (string) pex + "( before: " + parser.scanner.la(0)->image()
							+ " " + parser.scanner.la(1)->image() + ")";
		s.last_errc = -3;
		return s;
	}

	if( 0 == sym ) {
		s.last_errm = "Pusty plik lub niew³aœciwa œcie¿ka (" + path + ")";
		s.last_errc = -4;
		return s;
	}

	s.data = sym;
	s.destroy_data = false;	//co prawda dostalismy nowy obiekt, ale zwracamy dane przez wartosc - czyli z wykozystaniem operatora =, ktory przepisuje wskaznik na symbole, a nie kopiuje je
	s.last_errm = "";
	s.last_errc = 0;
	return s;
}

bool Settings :: Exists(int vidx) {
	if( ! _checkValid() )	return false;
	return ((Symbol*)(this->data))->Exists(0,vidx);
}
bool Settings :: Exists(int cidx,int vidx) {
	if( ! _checkValid() )	return false;
	return ((Symbol*)(this->data))->Exists(cidx,vidx);
}
bool Settings :: Exists(const string& path,int vidx) {
	if( ! _checkValid() )	return false;
	Settings s = Extract(path);
	if( s.last_errc < 0 ) {
		this->last_errc = s.last_errc;
		this->last_errm = s.last_errm;
		return false;
	}
	return ((Symbol*)(s.data))->Exists(0,vidx);
}


double Settings :: GetValF(int vidx) {
	if( ! _checkValid() )	return 0.0;
	return ((Symbol*)(this->data))->GetValF(0,vidx);
}
double Settings :: GetValF(int cidx,int vidx) {
	if( ! _checkValid() )	return 0.0;
	return ((Symbol*)(this->data))->GetValF(cidx,vidx);
}
double Settings :: GetValF(const string& path,int vidx) {
	if( ! _checkValid() )	return 0.0;
	Settings s = Extract(path);
	if( s.last_errc < 0 ) {
		this->last_errc = s.last_errc;
		this->last_errm = s.last_errm;
		return 0.0;
	}
	return ((Symbol*)(s.data))->GetValF(0,vidx);
}

long Settings :: GetValI(int vidx) {
	if( ! _checkValid() )	return 0;
	return ((Symbol*)(this->data))->GetValI(0,vidx);
}
long Settings :: GetValI(int cidx,int vidx) {
	if( ! _checkValid() )	return 0;
	return ((Symbol*)(this->data))->GetValI(cidx,vidx);
}
long Settings :: GetValI(const string& path,int vidx) {
	if( ! _checkValid() )	return 0;
	Settings s = Extract(path);
	if( s.last_errc < 0 ) {
		this->last_errc = s.last_errc;
		this->last_errm = s.last_errm;
		return 0;
	}
	return ((Symbol*)(s.data))->GetValI(0,vidx);
}

bool Settings :: GetValB(int vidx) {
	if( ! _checkValid() )	return false;
	return ((Symbol*)(this->data))->GetValB(0,vidx);
}
bool Settings :: GetValB(int cidx,int vidx) {
	if( ! _checkValid() )	return false;
	return ((Symbol*)(this->data))->GetValB(cidx,vidx);
}
bool Settings :: GetValB(const string& path,int vidx) {
	if( ! _checkValid() )	return false;
	Settings s = Extract(path);
	if( s.last_errc < 0 ) {
		this->last_errc = s.last_errc;
		this->last_errm = s.last_errm;
		return false;
	}
	return ((Symbol*)(s.data))->GetValB(0,vidx);
}


const string& Settings :: GetValS(int vidx) {
	if( ! _checkValid() )	return gs_null;
	return ((Symbol*)(this->data))->GetValS(0,vidx);
}
const string& Settings :: GetValS(int cidx,int vidx) {
	if( ! _checkValid() )	return gs_null;
	return ((Symbol*)(this->data))->GetValS(cidx,vidx);
}
const string& Settings :: GetValS(const string& path,int vidx) {
	if( ! _checkValid() )	return gs_null;
	Settings s = Extract(path);
	if( s.last_errc < 0 ) {
		this->last_errc = s.last_errc;
		this->last_errm = s.last_errm;
		return gs_null;
	}
	return ((Symbol*)(s.data))->GetValS(0,vidx);
}


bool Settings :: IsValB() {
	if( ! _checkValid() ) return false;
	return ((Symbol*)(this->data))->IsValB(0);
}
bool Settings :: IsValB(int cidx) {
	if( ! _checkValid() ) return false;
	return ((Symbol*)(this->data))->IsValB(cidx);
}
bool Settings :: IsValB(const std::string& path) {
	if( ! _checkValid() ) return false;
	Settings s = Extract(path);
	if( s.last_errc < 0 ) {
		this->last_errc = s.last_errc;
		this->last_errm = s.last_errm;
		return false;
	}
	return ((Symbol*)(s.data))->IsValB(0);
}
bool Settings :: IsValI() {
	if( ! _checkValid() ) return false;
	return ((Symbol*)(this->data))->IsValI(0);
}
bool Settings :: IsValI(int cidx) {
	if( ! _checkValid() ) return false;
	return ((Symbol*)(this->data))->IsValI(cidx);
}
bool Settings :: IsValI(const std::string& path) {
	if( ! _checkValid() ) return false;
	Settings s = Extract(path);
	if( s.last_errc < 0 ) {
		this->last_errc = s.last_errc;
		this->last_errm = s.last_errm;
		return false;
	}
	return ((Symbol*)(s.data))->IsValI(0);
}
bool Settings :: IsValF() {
	if( ! _checkValid() ) return false;
	return ((Symbol*)(this->data))->IsValF(0);
}
bool Settings :: IsValF(int cidx) {
	if( ! _checkValid() ) return false;
	return ((Symbol*)(this->data))->IsValF(cidx);
}
bool Settings :: IsValF(const std::string& path) {
	if( ! _checkValid() ) return false;
	Settings s = Extract(path);
	if( s.last_errc < 0 ) {
		this->last_errc = s.last_errc;
		this->last_errm = s.last_errm;
		return false;
	}
	return ((Symbol*)(s.data))->IsValF(0);
}
bool Settings :: IsValS() {
	if( ! _checkValid() ) return false;
	return ((Symbol*)(this->data))->IsValS(0);
}
bool Settings :: IsValS(int cidx) {
	if( ! _checkValid() ) return false;
	return ((Symbol*)(this->data))->IsValS(cidx);
}
bool Settings :: IsValS(const std::string& path) {
	if( ! _checkValid() ) return false;
	Settings s = Extract(path);
	if( s.last_errc < 0 ) {
		this->last_errc = s.last_errc;
		this->last_errm = s.last_errm;
		return false;
	}
	return ((Symbol*)(s.data))->IsValS(0);
}


string Settings :: Dump(void) const {
	if( 0 == data ) return "";
	Symbol *sym = (Symbol*)data;
	return sym->dump();
}

string Settings :: ErrorMsg(void) const {
	return last_errm;
}

}; //namespace Core
