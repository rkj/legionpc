#ifndef D_BASIC_H_D
#define D_BASIC_H_D

#include <GL/gl.h>

namespace Gfx {

class Pic;

/// Sk³adowa czerwona bie¿¹cego koloru [0.0,1.0]
extern GLfloat red;
/// Sk³adowa zielona bie¿¹cego koloru [0.0,1.0]
extern GLfloat green;
/// Sk³adowa niebieska bie¿¹cego koloru [0.0,1.0]
extern GLfloat blue;
/// Sk³adowa alfa (przeŸroczystoœæ) bie¿¹cego koloru [0.0,1.0]
extern GLfloat alpha;

/// Ustawia bie¿¹cy kolor (czyli kolor, który bêd¹ rysowane "prymitywy")
void Color(GLfloat r,GLfloat g,GLfloat b,GLfloat a=1.0f);

/// Ustawia bie¿¹cy kolor (czyli kolor, który bêd¹ rysowane "prymitywy")
void Color(int r,int g,int b,int a=255);

/// Rysuje punkt
void Plot(GLfloat x,GLfloat y);

/// Rysuje liniê
void Line(GLfloat x1,GLfloat y1,GLfloat x2,GLfloat y2);

/// Rysuje prostok¹t
void Box(GLfloat x1,GLfloat y1,GLfloat x2,GLfloat y2);

/// Rysuje wype³niony prostok¹t
void Bar(GLfloat x1,GLfloat y1,GLfloat x2,GLfloat y2);

/// Rysuje têczê
void Rainbow(GLfloat x1,GLfloat y1,GLfloat x2,GLfloat y2,float *rb, int rows);

/// Rysuje têczê w poziomie
void RainbowH(GLfloat x1,GLfloat y1,GLfloat x2,GLfloat y2,float *rb, int rows);

/// Rysuje okr¹g
void Circle(GLfloat x,GLfloat y,GLfloat r);

/// Rysuje ko³o
void Disc(GLfloat x,GLfloat y,GLfloat r);

/// Rysuje elipsê
void Elipse(GLfloat x,GLfloat y,GLfloat rx,GLfloat ry);

/// Rysuje wype³nion¹ elipsê
void SolidElipse(GLfloat x,GLfloat y,GLfloat rx,GLfloat ry);

/// Rysuje pixmapê (rysunek)
void Blit2Raster(int x,int y,unsigned char *rgba,int w,int h);
void Blit2Raster(int x,int y,unsigned char *rgba,int w,int h,float sx,float sy);

/// Pobiera okreslona czesc bufora i tworzy z tego obiekt typu Pic
Pic* ReadRaster(int x,int y,int w,int h);

/// Czyœci bufor ekranu (bie¿¹cym kolorem)
void Cls(void);

/// Czyœci bufor ekranu wskazanym kolorem (bie¿¹cy nie bêdzie zmieniony)
void Cls(GLfloat r,GLfloat g,GLfloat b,GLfloat a=1.0f);

/// Ustawia bufory, w ktorych ma byc rysowana grafika
void SetDrawBuffer(int buf);

void Clip(int x,int y,int w,int h);
void ClipOff();

/// Stale definiujace bufory
enum BUFFERID {
	DB_NONE							= GL_NONE
,	DB_FRONT						= GL_FRONT
, DB_BACK							= GL_BACK
, DB_BOTH							= GL_FRONT_AND_BACK
, DB_FRONT_AND_BACK		= GL_FRONT_AND_BACK
};

};

#endif
