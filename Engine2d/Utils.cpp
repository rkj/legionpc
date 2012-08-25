
#include <cstdio>

#include "Utils.h"

using namespace std;

string toString(int v,const string& fmt) {
	char buf[255];
	sprintf(buf,fmt.c_str(),v);
	return string(buf);
}

string toString(long v,const string& fmt) {
	char buf[255];
	sprintf(buf,fmt.c_str(),v);
	return string(buf);
}

string toString(unsigned long v,const string& fmt) {
	char buf[255];
	sprintf(buf,fmt.c_str(),v);
	return string(buf);
}

string toString(float v,const string& fmt) {
	char buf[255];
	sprintf(buf,fmt.c_str(),v);
	return string(buf);
}

string toString(double v,const string& fmt) {
	char buf[255];
	sprintf(buf,fmt.c_str(),v);
	return string(buf);
}

int toInt(const string& v,const string& fmt) {
	int ret;
	sscanf(v.c_str(),fmt.c_str(),&ret);
	return ret;
}

long toLong(const string& v,const string& fmt) {
	long ret;
	sscanf(v.c_str(),fmt.c_str(),&ret);
	return ret;
}

unsigned long toULong(const string& v,const string& fmt) {
	unsigned long ret;
	sscanf(v.c_str(),fmt.c_str(),&ret);
	return ret;
}

float toFloat(const string& v,const string& fmt) {
	float ret;
	sscanf(v.c_str(),fmt.c_str(),&ret);
	return ret;
}

double toDouble(const string& v,const string& fmt) {
	double ret;
	sscanf(v.c_str(),fmt.c_str(),&ret);
	return ret;
}


void _Msg(const string& msg) {
	cerr << msg << endl; cerr.flush();
}

void _Assert(bool cond,const string& msg) {
	if( ! cond ) {
		cerr << msg << endl; cerr.flush();
//		exit(0);
	}
}

void _Error(const string& msg) {
	cerr << msg << endl; cerr.flush();
//	exit(0);
}

