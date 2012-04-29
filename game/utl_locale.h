#ifndef UTL_LOCALE_H
#define UTL_LOCALE_H

#include <string>

using namespace std;

const string& GS(const string& id);
void SetLang(const string& lang_id);
const string& GetLang(void);
bool ExistsLang(const string& lang_id);
void InitLocale(void);

#endif
