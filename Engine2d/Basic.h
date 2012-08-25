#ifndef D_BASIC_H_D
#define D_BASIC_H_D

#include <GL/gl.h>

namespace Gfx {

class Pic;

/// Składowa czerwona bieżącego koloru [0.0,1.0]
extern GLfloat red;
/// Składowa zielona bieżącego koloru [0.0,1.0]
extern GLfloat green;
/// Składowa niebieska bieżącego koloru [0.0,1.0]
extern GLfloat blue;
/// Składowa alfa (przeźroczystość) bieżącego koloru [0.0,1.0]
extern GLfloat alpha;

/// Ustawia bieżący kolor (czyli kolor, który będą rysowane "prymitywy")
void Color(GLfloat r,GLfloat g,GLfloat b,GLfloat a=1.0f);

/// Ustawia bieżący kolor (czyli kolor, który będą rysowane "prymitywy")
void Color(int r,int g,int b,int a=255);

/// Rysuje punkt
void Plot(GLfloat x,GLfloat y);

/// Rysuje linię
void Line(GLfloat x1,GLfloat y1,GLfloat x2,GLfloat y2);

/// Rysuje prostokąt
void Box(GLfloat x1,GLfloat y1,GLfloat x2,GLfloat y2);

/// Rysuje wypełniony prostokąt
void Bar(GLfloat x1,GLfloat y1,GLfloat x2,GLfloat y2);

/// Rysuje tęczę
void Rainbow(GLfloat x1,GLfloat y1,GLfloat x2,GLfloat y2,float *rb, int rows);

/// Rysuje tęczę w poziomie
void RainbowH(GLfloat x1,GLfloat y1,GLfloat x2,GLfloat y2,float *rb, int rows);

/// Rysuje okrąg
void Circle(GLfloat x,GLfloat y,GLfloat r);

/// Rysuje koło
void Disc(GLfloat x,GLfloat y,GLfloat r);

/// Rysuje elipsę
void Elipse(GLfloat x,GLfloat y,GLfloat rx,GLfloat ry);

/// Rysuje wypełnioną elipsę
void SolidElipse(GLfloat x,GLfloat y,GLfloat rx,GLfloat ry);

/// Rysuje pixmapę (rysunek)
void Blit2Raster(int x,int y,unsigned char *rgba,int w,int h);
void Blit2Raster(int x,int y,unsigned char *rgba,int w,int h,float sx,float sy);

/// Pobiera okreslona czesc bufora i tworzy z tego obiekt typu Pic
Pic* ReadRaster(int x,int y,int w,int h);

/// Czyści bufor ekranu (bieżącym kolorem)
void Cls(void);

/// Czyści bufor ekranu wskazanym kolorem (bieżący nie będzie zmieniony)
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
