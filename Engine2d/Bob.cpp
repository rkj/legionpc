
#include "Bob.h"
#include "Textures.h"

namespace Gfx {

int bobblit_cnt = 0;

void Bob :: _reset(void) {
	x = 0.0f;
	y = 0.0f;
	w = 1.0f;
	h = 1.0f;
	sx = 1.0f;
	sy = 1.0f;
	alpha = 0.0f;
	x_hotspot = 0.0f;
	y_hotspot = 0.0f;
	radius = 0.0f;
	tex = 0;
	grid = 0;
	col = 0;
	movable = true;
	color_r = color_g = color_b = color_a = 1.0f;
}
void Bob :: _destroy(void) {
	if( grid ) grid->RemObj(this);	//wypinamy obiekt z siatki
}
Bob :: Bob(void) {
	_reset();
}
Bob :: ~Bob() {
	_destroy();
}
void Bob :: SetTex(const LTex *t,bool preserve_size, bool preserve_hotspot) {
	tex = t;
	if( !preserve_size ) {
		w = t->GetWidth();
		h = t->GetHeight();
	}
	if( !preserve_hotspot ) {
		x_hotspot = t->GetHotSpotX() * w;
		y_hotspot = t->GetHotSpotY() * h;
	}
}
void Bob :: Blit(void) {

	if( 0 == tex) return;	//nie ma czym rysowac

	++bobblit_cnt;

	BeginBobBlits();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

//		glTranslatef(x-2*x_hotspot, y-2*y_hotspot, 0.0f);
//		glScalef(sx, sy, 0.0f);
//		glRotatef(alpha, 0.0f, 0.0f, 1.0f);

		glTranslatef(x+x_hotspot, y+y_hotspot, 0.0f);
		glRotatef(alpha, 0.0f, 0.0f, 1.0f);
		glScalef(sx, sy, 0.0f);
		glTranslatef(-x_hotspot, -y_hotspot, 0.0f);

//		glTranslatef(-w/2.0f,-h/2.0f,0.0f);
//		glTranslatef(2*x_hotspot, 2*y_hotspot, 0.0f);
//		glTranslatef(x_hotspot, y_hotspot, 0.0f);


		glBindTexture(GL_TEXTURE_2D, tex->GetTextureID() );
		glBegin(GL_QUADS);
			glColor4f(color_r, color_g, color_b, color_a);
			glTexCoord2f( tex->fx1, tex->fy1 );		glVertex2f( 0.0f, 0.0f );
			glTexCoord2f( tex->fx2, tex->fy1 );		glVertex2f(    w,	0.0f );
			glTexCoord2f( tex->fx2, tex->fy2 );		glVertex2f(    w,    h );
			glTexCoord2f( tex->fx1, tex->fy2 );		glVertex2f( 0.0f,    h );
		glEnd();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	EndBobBlits();
}

void Bob :: Blit(float xo,float yo) {
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

		glTranslatef(xo, yo, 0.0f);
		Blit();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}


static int ii_bobblits = 0;

void BeginBobBlits(void) {
	if( ii_bobblits++ > 0 ) return;

	glEnable(GL_TEXTURE_2D);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	glMatrixMode(GL_TEXTURE);
  glLoadIdentity();
  glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
}
void EndBobBlits(void) {

	if( --ii_bobblits > 0 ) return;

	ii_bobblits = 0;
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	return;
}
void BreakBobBlits(void) {
	if( ii_bobblits > 0 ) {
		ii_bobblits = 0;
		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);
	}
	return;
}

};	//namespace
