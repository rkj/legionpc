
#include "Locale.h"

using namespace std;

static const string gs_empty = "";

static string decode_escapes(const string& src) {
	string s="";
	char prev=0, cur;
	int len=src.length();
	for( int i=0; i<len; ++i ) {
		cur=src[i];
		if( '\\'==prev ) {
			switch(cur) {
				case 'n':	s+='\n'; break;
				case 't':	s+='\t'; break;
				default:	s+=cur;  break;
			}
			prev=0;
		} else {
			if( '\\'==cur ) {
				prev=cur;
			} else {
				s+=cur;
			}
		}
	}
	return s;
}

namespace Extras {

Locale::Locale(void) {
	db.clear();
}
Locale::~Locale() {
	db.clear();
}
void Locale::Add(const string& key,const string& text) {
	db.insert(make_pair(key,text));
}
void Locale::Rem(const string& key) {
	db.erase(key);
}
const string& Locale::Get(const string& key) {
  TTextDB::iterator iter;
	iter = db.find(key);
  if( iter != db.end() )
    return iter->second;
	return gs_empty;
}


LocaleMgr::LocaleMgr(void) {
	db.clear();
	def_loc=0;
	lang="";
}
LocaleMgr::~LocaleMgr() {
	Locale* l;
	TLocaleDB::iterator it;
	for( it=db.begin(); it != db.end(); ++it ) {
		l = it->second;
		delete l;
	}
	db.clear();
}
Locale* LocaleMgr::GetLocale(const string& lang) {
  TLocaleDB::iterator iter;
	iter = db.find(lang);
  if( iter != db.end() )
    return iter->second;
	return 0;
}
void LocaleMgr::Add(const string& lang,const string& key,const string& text) {
	Locale *loc = GetLocale(lang);
	if( 0==loc ) {
		loc = new Locale();
		db.insert(make_pair(lang,loc));
	}
	loc->Add(key,text);
}
const string& LocaleMgr::Get(const string& lang,const string& key) {
	Locale *loc = GetLocale(lang);
	if( 0==loc )
		return gs_empty;
	return loc->Get(key);
}
bool LocaleMgr::SetLang(const string& lang) {
	def_loc = GetLocale(lang);
	if( def_loc ) {
		this->lang=lang;
	} else {
		this->lang="";
	}
	return 0!=def_loc;
}
const std::string& LocaleMgr::GetLang(void) {
	return lang;
}
bool LocaleMgr::ExistsLang(const std::string& lang) {
	return 0!=GetLocale(lang);
}

const string& LocaleMgr::Get(const string& key) {
	if( 0==def_loc )
		return gs_empty;
	return def_loc->Get(key);
}
void LocaleMgr::Add(const char* def[]) {
	string d, lang="", key;
	unsigned int pos;
	for( int i=0; 0!=def[i]; i++ ) {
		d=def[i];
		//wyodrebniamy jezyk
		pos=d.find(":",0);
		if( pos!=string::npos ) {
			if( 0!=pos ) {
				//zmieniamy jezyk tylko wtedy gdy jest, w przeciwnym wypadku zakladamy, ze jezyk jest taki sam jak w poprzednim opisie frazy
				lang=d.substr(0,pos);
			}
			d=d.substr(pos+1);
		}
		//wyodrebniamy klucz
		pos=d.find(":",0);
		if( pos!=string::npos ) {
			key=d.substr(0,pos);
			d=d.substr(pos+1);
		} else {
			key="";
		}
		if( lang!="" && key!="" )
			Add(lang,key,decode_escapes(d));
	}
}

}

//int main(int argc,char*argv[]) {
//
//	LocaleMgr lm;
//
//	lm.Add("PL","0001","Ala ma kota");
//	lm.Add("PL","0002","Dupa");
//	lm.Add("PL","9999","o co chodzi ?");
//
//	lm.Add("EN","0001","Alice has a cat");
//	lm.Add("EN","0002","Ass");
//	lm.Add("EN","9999","What's up doc ?");
//
//	char *def[] = {"PL:0003:Je\\st\\nem\\tnajlep\\\\szy",":0004:Kim jesteœ?","EN:0003:I'm the best",":0004:Who you are?",0};
//	lm.Add(def);
//
//	lm.SetLang("PL");
//
//	if( argc>2 ) {
//		cout << "text:" << lm.Get(argv[1],argv[2]) << endl;
//		cout << "def_text:" << lm.Get(argv[2]) << endl;
//	}
//
//	return 0;
//}

