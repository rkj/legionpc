#ifndef D_AMOSIMAGE_H_D
#define D_AMOSIMAGE_H_D

enum SCALETYPE {
	SCLT_NONE			= 0
, SCLT_SCALE2X	= 1
, SCLT_HQ2X			= 2
};

extern int HQScaleType;
extern bool HQShadows;

void ImageHQShadow(unsigned char *src,int wid,int hei);
void ImageScale2x(unsigned char *src,unsigned char* dst,int w,int h);

#endif // D_AMOSIMAGE_H_D

