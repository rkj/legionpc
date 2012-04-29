#ifndef D_UTILS_H_D
#define D_UTILS_H_D

#include <string>
#include <iostream>

/// Szablon funkcji zwracaj¹cej wartoœæ bezwzglêdn¹
template<typename TYP>
TYP Abs(TYP v) {
	if(v<0) return -v; return v;
}

/// Szablon funkcji zwracaj¹cej wartoœæ maksymaln¹
template<typename TYP>
TYP Max(TYP a,TYP b) {
	if(a<b) return b; return a;
}

/// Szablon funkcji zwracaj¹cej wartoœæ minimaln¹
template<typename TYP>
TYP Min(TYP a,TYP b) {
	if(a<b) return a; return b;
}

/// funkcja konwertuje wartosc ca³kowit¹ na string
std::string toString(int v,const std::string& fmt = "%d");

/// funkcja konwertuje wartosc ca³kowit¹ na string
std::string toString(long v,const std::string& fmt = "%ld");

/// funkcja konwertuje wartosc ca³kowit¹ na string
std::string toString(unsigned long v,const std::string& fmt = "%lu");

/// funkcja konwertuje wartosc zmiennoprzecinkow¹ na string
std::string toString(float v,const std::string& fmt = "%f");

/// funkcja konwertuje wartosc zmiennoprzecinkow¹ na string
std::string toString(double v,const std::string& fmt = "%lf");

/// funkcja konwertuje string na wartosc int
int toInt(const std::string& v,const std::string& fmt = "%d");

/// funkcja konwertuje string na wartosc long
long toLong(const std::string& v,const std::string& fmt = "%ld");

/// funkcja konwertuje string na wartosc long bez znaku
unsigned long toULong(const std::string& v,const std::string& fmt = "%lu");

/// funkcja konwertuje string na wartosc float
float toFloat(const std::string& v,const std::string& fmt = "%f");

/// funkcja konwertuje string na wartosc double
double toDouble(const std::string& v,const std::string& fmt = "%lf");

//#define NDEBUG


/// zapewnia, ze jakis warunek jest spelniony
#ifndef NDEBUG
#define ASSERT(A,B)	{ if(!(A)) _Msg(__FILE__":"+std::string(__func__)+":"+toString(__LINE__)+":\n\t"+B); }
#else
#define ASSERT(A,B) /* NULL */
#endif
//void _Assert(bool cond,const string& msg);
void _Msg(const std::string& msg);


/// wypisuje komunikat bledu i konczy dzialanie programu
#ifndef NDEBUG
#undef ERROR
#define ERROR(A)	_Msg(__FILE__":"+std::string(__func__)+":"+toString(__LINE__)+":\n\t"+A)
#else
#define ERROR(A) /* NULL */
#endif
//void _Error(const string& msg);

#ifndef NDEBUG
#undef INFO
#define INFO(A)	_Msg(A)
#else
#define INFO(A) /* NULL */
#endif

#endif /*D_UTILS_H_D*/
