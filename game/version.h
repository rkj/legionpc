#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "22";
	static const char MONTH[] = "05";
	static const char YEAR[] = "2009";
	static const double UBUNTU_VERSION_STYLE = 9.05;
	
	//Software Status
	static const char STATUS[] = "Beta";
	static const char STATUS_SHORT[] = "b";
	
	//Standard Version Type
	static const long MAJOR = 1;
	static const long MINOR = 0;
	static const long BUILD = 53;
	static const long REVISION = 21;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT = 547;
	#define RC_FILEVERSION 1,0,53,21
	#define RC_FILEVERSION_STRING "1, 0, 53, 21\0"
	static const char FULLVERSION_STRING[] = "1.0.53.21";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY = 23;
	

}
#endif //VERSION_h
