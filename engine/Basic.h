#ifndef D_BASIC_H_D
#define D_BASIC_H_D

#include <GL/gl.h>

namespace Gfx {

class Pic;

/// Sk�adowa czerwona bie��cego koloru [0.0,1.0]
extern GLfloat red;
/// Sk�adowa zielona bie��cego koloru [0.0,1.0]
extern GLfloat green;
/// Sk�adowa niebieska bie��cego koloru [0.0,1.0]
extern GLfloat blue;
/// Sk�adowa alfa (prze�roczysto��) bie��cego koloru [0.0,1.0]
extern GLfloat alpha;

/// Ustawia bie��cy kolor (czyli kolor, kt�ry b�d� rysowane "prymitywy")
void Color(GLfloat r,GLfloat g,GLfloat b,GLfloat a=1.0f);

/// Ustawia bie��cy kolor (czyli kolor, kt�ry b�d� rysowane "prymitywy")
void Color(int r,int g,int b,int a=255);

/// Rysuje punkt
void Plot(GLfloat x,GLfloat y);

/// Rysuje lini�
void Line(GLfloat x1,GLfloat y1,GLfloat x2,GLfloat y2);

/// Rysuje prostok�t
void Box(GLfloat x1,GLfloat y1,GLfloat x2,GLfloat y2);

/// Rysuje wype�niony prostok�t
void Bar(GLfloat x1,GLfloat y1,GLfloat x2,GLfloat y2);

/// Rysuje t�cz�
void Rainbow(GLfloat x1,GLfloat y1,GLfloat x2,GLfloat y2,float *rb, int rows);

/// Rysuje t�cz� w poziomie
void RainbowH(GLfloat x1,GLfloat y1,GLfloat x2,GLfloat y2,float *rb, int rows);

/// Rysuje okr�g
void Circle(GLfloat x,GLfloat y,GLfloat r);

/// Rysuje ko�o
void Disc(GLfloat x,GLfloat y,GLfloat r);

/// Rysuje elips�
void Elipse(GLfloat x,GLfloat y,GLfloat rx,GLfloat ry);

/// Rysuje wype�nion� elips�
void SolidElipse(GLfloat x,GLfloat y,GLfloat rx,GLfloat ry);

/// Rysuje pixmap� (rysunek)
void Blit2Raster(int x,int y,unsigned char *rgba,int w,int h);
void Blit2Raster(int x,int y,unsigned char *rgba,int w,int h,float sx,float sy);

/// Pobiera okreslona czesc bufora i tworzy z tego obiekt typu Pic
Pic* ReadRaster(int x,int y,int w,int h);

/// Czy�ci bufor ekranu (bie��cym kolorem)
void Cls(void);

/// Czy�ci bufor ekranu wskazanym kolorem (bie��cy nie b�dzie zmieniony)
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
