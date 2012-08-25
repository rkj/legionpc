#ifndef D_LOCALE_H_D
#define D_LOCALE_H_D

#include <string>
#include <map>

namespace Extras {

class Locale {
protected:
	typedef std::map<std::string,std::string> TTextDB;
	TTextDB db;
public:
	Locale(void);
	~Locale();
	void Add(const std::string& key,const std::string& text);
	void Rem(const std::string& key);
	const std::string& Get(const std::string& key);
};

class LocaleMgr {
protected:
	typedef std::map<std::string,Locale*> TLocaleDB;
	TLocaleDB db;
	Locale *def_loc;
	std::string lang;
public:
	LocaleMgr(void);
	~LocaleMgr();
	Locale* GetLocale(const std::string& lang);
	void Add(const std::string& lang,const std::string& key,const std::string& text);
	void Add(const char* def[]);
	const std::string& Get(const std::string& lang,const std::string& key);
	const std::string& Get(const std::string& key);
	bool SetLang(const std::string& lang);
	const std::string& GetLang(void);
	bool ExistsLang(const std::string& lang);
};

}

#endif
