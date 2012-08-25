
#include <math.h>

#include "Basic.h"
#include "Bob.h"
#include "Types.h"
#include "Pictures.h"

namespace Gfx {

GLfloat red		= 1.0
			, green	= 1.0
			, blue	= 1.0
			, alpha	= 1.0;

static int draw_buffer = DB_FRONT;

void Color(GLfloat r,GLfloat g,GLfloat b,GLfloat a) {
	red = r;
	green = g;
	blue = b;
	alpha = a;
}
void Color(int r,int g,int b,int a) {
	red = ((GLfloat)r)/255.0f;
	green = ((GLfloat)g)/255.0f;
	blue = ((GLfloat)b)/255.0f;
	alpha = ((GLfloat)a)/255.0f;
}

void Plot(GLfloat x,GLfloat y) {
	BreakBobBlits();
	glBegin(GL_POINTS);
		glColor4f(red,green,blue,alpha);
		glVertex2f( x, y );
	glEnd();
}
void Line(GLfloat x1,GLfloat y1,GLfloat x2,GLfloat y2) {
	BreakBobBlits();
	glBegin(GL_LINES);
		glColor4f(red,green,blue,alpha);
		glVertex2f( x1, y1 );
		glVertex2f( x2, y2 );
	glEnd();
}
void Box(GLfloat x1,GLfloat y1,GLfloat x2,GLfloat y2) {
	BreakBobBlits();
	glBegin(GL_LINE_LOOP);
		glColor4f(red,green,blue,alpha);
		glVertex2f( x1, y1 );
		glVertex2f( x2, y1 );
		glVertex2f( x2, y2 );
		glVertex2f( x1, y2 );
	glEnd();
}
void Bar(GLfloat x1,GLfloat y1,GLfloat x2,GLfloat y2) {
	BreakBobBlits();
	glBegin(GL_QUADS);
		glColor4f(red,green,blue,alpha);
		glVertex2f( x1, y1 );
		glVertex2f( x2, y1 );
		glVertex2f( x2, y2 );
		glVertex2f( x1, y2 );
	glEnd();
}
void Rainbow(GLfloat x1,GLfloat y1,GLfloat x2,GLfloat y2,float *rb, int rows) {
	//na poczatek wyznaczamy MIN i MAX sposrod wag - wagi powinny byc rosnace, wiec korzystamy z tego faktu
	float min = rb[0]
	    , max = rb[(rows-1)*5];
	float d = (y2 - y1) / (max - min);
	float y = y1;
	BreakBobBlits();
	glBegin(GL_QUAD_STRIP);
		glColor4f(rb[1],rb[2],rb[3],rb[4]);
		glVertex2f( x1, y );
		glVertex2f( x2, y );
		for( int i = 1; i < rows; ++i ) {
			rb += 5;	//przeskakujemy do nast wiersza
			y = y1 + (rb[0] - min) * d;
			glColor4f(rb[1],rb[2],rb[3],rb[4]);
			glVertex2f( x1, y );
			glVertex2f( x2, y );
		}
	glEnd();
}
void RainbowH(GLfloat x1,GLfloat y1,GLfloat x2,GLfloat y2,float *rb, int rows) {
	//na poczatek wyznaczamy MIN i MAX sposrod wag - wagi powinny byc rosnace, wiec korzystamy z tego faktu
	float min = rb[0]
	    , max = rb[(rows-1)*5];
	float d = (x2 - x1) / (max - min);
	float x = x1;
	BreakBobBlits();
	glBegin(GL_QUAD_STRIP);
		glColor4f(rb[1],rb[2],rb[3],rb[4]);
		glVertex2f( x, y1 );
		glVertex2f( x, y2 );
		for( int i = 1; i < rows; ++i ) {
			rb += 5;	//przeskakujemy do nast wiersza
			x = x1 + (rb[0] - min) * d;
			glColor4f(rb[1],rb[2],rb[3],rb[4]);
			glVertex2f( x, y1 );
			glVertex2f( x, y2 );
		}
	glEnd();
}
void Circle(GLfloat x,GLfloat y,GLfloat r) {
	BreakBobBlits();
	glBegin(GL_LINE_LOOP);
		GLfloat k, dk;
		if( Abs(r) > 10.0f ) {
			dk = M_PI / Abs(r);
		} else {
			dk = M_PI / 10.0f;
		}
		glColor4f(red,green,blue,alpha);
		for( k = 0.0f; k < 2.0f * M_PI; k += dk ) {
			glVertex2f( x + r * cos(k), y - r * sin(k) );
		}
	glEnd();
}
void Disc(GLfloat x,GLfloat y,GLfloat r) {
	BreakBobBlits();
	glBegin(GL_TRIANGLE_FAN);
		GLfloat k, dk;
		if( Abs(r) > 10.0f ) {
			dk = M_PI / Abs(r);
		} else {
			dk = M_PI / 10.0f;
		}
		glColor4f(red,green,blue,alpha);
		glVertex2f(x,y);
		for( k = 0.0f; k < 2.0f * M_PI; k += dk ) {
			glVertex2f( x + r * cos(k), y - r * sin(k) );
		}
		glVertex2f( x + r * cos(k), y - r * sin(k) );
	glEnd();
}
void Elipse(GLfloat x,GLfloat y,GLfloat rx,GLfloat ry) {
	BreakBobBlits();
	glBegin(GL_LINE_LOOP);
		GLfloat k, dk;
		if( Abs(rx + ry) > 10.0f ) {
			dk = M_PI / Abs(rx + ry);
		} else {
			dk = M_PI / 10.0f;
		}
		glColor4f(red,green,blue,alpha);
		for( k = 0.0f; k < 2.0f * M_PI; k += dk ) {
			glVertex2f( x + rx * cos(k), y - ry * sin(k) );
		}
	glEnd();
}
void SolidElipse(GLfloat x,GLfloat y,GLfloat rx,GLfloat ry) {
	BreakBobBlits();
	glBegin(GL_TRIANGLE_FAN);
		GLfloat k, dk;
		if( Abs(rx + ry) > 10.0f ) {
			dk = M_PI / Abs(rx + ry);
		} else {
			dk = M_PI / 10.0f;
		}
		glColor4f(red,green,blue,alpha);
		glVertex2f(x,y);
		for( k = 0.0f; k < 2.0f * M_PI; k += dk ) {
			glVertex2f( x + rx * cos(k), y - ry * sin(k) );
		}
		glVertex2f( x + rx * cos(k), y - ry * sin(k) );
	glEnd();
}

void Blit2Raster(int x,int y,unsigned char *rgba,int w,int h,float sx,float sy) {
	BreakBobBlits();

	if( y < 0 ) {
//		rgba += w * 4 * -y / (int)sy;
//		h += y / (int)sy;
//		y = 0;
		int dy = (int)((float)y / sy);
		rgba += w * -4 * dy;
		h += dy;
		y = 0;
	}
	if( h <= 0 ) return;

	if( x < 0 ) {
//		rgba += 4 * -x / (int)sx;
//		//w += x / (int)sx;
//		x = 0;
		int dx = (int)((float)x / sx);
		rgba += -4 * dx;
		x = 0;
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
  glPixelStorei(GL_UNPACK_ROW_LENGTH,0);
  glPixelStorei(GL_UNPACK_SKIP_ROWS,0);
  glPixelStorei(GL_UNPACK_SKIP_PIXELS,0);

	glPixelZoom(sx,-sy);
	glRasterPos2i(x,y);
//	glPixelZoom(sx,-sy);
//	glRasterPos2i(x,y+h);
	glDrawPixels(w,h,GL_RGBA,GL_UNSIGNED_BYTE,rgba);
}
void Blit2Raster(int x,int y,unsigned char *rgba,int w,int h) {
	Blit2Raster(x,y,rgba,w,h,1.0f,1.0f);
}

Pic* ReadRaster(int x,int y,int w,int h) {

	Pic *pic = new Pic();
	if( 0 == pic ) return pic;
	pic->Set(w,h,PDM_RGBA);

	glFlush();
	glPixelStorei(GL_PACK_ALIGNMENT,1);
	glPixelStorei(GL_PACK_ROW_LENGTH,0);
	glPixelStorei(GL_PACK_SKIP_ROWS,0);
	glPixelStorei(GL_PACK_SKIP_PIXELS,0);
	glReadBuffer(draw_buffer);

	glReadPixels(x,y,w,h,GL_RGBA,GL_UNSIGNED_BYTE,pic->GetBufferWR());
	return pic;
}


void Cls(void) {
	Cls(red,green,blue,alpha);
}

void Cls(GLfloat r,GLfloat g,GLfloat b,GLfloat a) {
	BreakBobBlits();
	glClearColor(r,g,b,a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void SetDrawBuffer(int buf) {
	draw_buffer = buf;
	glDrawBuffer(buf);
}
void Clip(int x,int y,int w,int h) {
	glScissor( x, y, w, h );
	glEnable(GL_SCISSOR_TEST);
}
void ClipOff() {
	glDisable(GL_SCISSOR_TEST);
}


};	//namespace
