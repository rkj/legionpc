
#include "Collision.h"
#include "Basic.h"

namespace Fzx {

void Col :: _reset(void) {
	type_id = ID_SPHERE;
	props = 0;	//obiekt jest niczym
	mask = 0;		//i zniczym sie nie zderza
	x = 0.0f;
	y = 0.0f;
	a = 0.0f;
	user_data = 0;
}
void Col :: _destroy(void) {
}
Col :: Col(void) {
	_reset();
}
Col :: ~Col() {
	_destroy();
}
bool Col :: Collide(const Col* c) {
	++collision_test_cnt;
	switch( c->type_id ) {
		case ID_SPHERE:		if( Collide((const ColSphere*)c) ) {
												bool	a = OnCollision(c),
															b = c->OnCollision(this);
												return a || b;
											}
											return false;

		default:					return false;
	}
}

bool ColSphere :: Collide(const ColSphere* c) {
	if( (mask & c->props) | (props & c->mask) ) {
		GLfloat dx, dy, r2;
		dx  = x - c->x;
		dy  = y - c->y;
		r2  = r + c->r;
		dx *= dx;
		dy *= dy;
		r2 *= r2;
		if( r2 > dx + dy ) return true;
	}
	return false;
}
void ColSphere :: Draw(void) {
	Gfx::Color(1.0f,0.0f,0.0f);
	Gfx::Circle(x,y,r);
}


long collision_test_cnt = 0;


};	//namespace
