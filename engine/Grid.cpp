
#include "Grid.h"
#include "Collision.h"
#include "Types.h"
#include "Bob.h"
#include "Basic.h"

using namespace std;
using namespace Gfx;
using namespace Fzx;

namespace Core {

bool draw_grid = false;

void Grid :: _reset(void) {
	xmin = 0.0f;
	xmax = 0.0f;
	ymin = 0.0f;
	xmax = 0.0f;
	for( int c = 0; c < C_CHILD_CNT; ++c )
		child[c] = 0;
	parent = 0;
	left = 0;
	right = 0;
	up = 0;
	down = 0;
	level = 0;
	draw_list.clear();
	col_list.clear();
}
void Grid :: _destroy(void) {
	for( int c = 0; c < C_CHILD_CNT; ++c )
		delete child[c];
}
Grid :: Grid(void) {
	_reset();
}
Grid :: Grid(Grid *parent) {
	_reset();
	this->parent = parent;
}
Grid :: ~Grid() {
	_destroy();
}
void Grid :: _Set(GLfloat x1,GLfloat y1,GLfloat x2,GLfloat y2,GLfloat minw,GLfloat minh,unsigned short int lev) {
	this->xmin = x1;
	this->ymin = y1;
	this->xmax = x2;
	this->ymax = y2;
	this->level = lev;

	GLfloat w = (this->xmax - this->xmin)/2.0f,
					h = (this->ymax - this->ymin)/2.0f;

	if( w > minw ) {
		if( h > minh ) {
			child[0] = new Grid(this); child[0]->_Set(xmin,ymin,xmin+w,ymin+h,minw,minh,level+1);
			child[1] = new Grid(this); child[1]->_Set(xmin+w,ymin,xmax,ymin+h,minw,minh,level+1);
			child[2] = new Grid(this); child[2]->_Set(xmin,ymin+h,xmin+w,ymax,minw,minh,level+1);
			child[3] = new Grid(this); child[3]->_Set(xmin+w,ymin+h,xmax,ymax,minw,minh,level+1);
		} else {
			child[0] = new Grid(this); child[0]->_Set(xmin,ymin,xmin+w,ymax,minw,minh,level+1);
			child[1] = new Grid(this); child[1]->_Set(xmin+w,ymin,xmax,ymax,minw,minh,level+1);
			child[2] = 0;
			child[3] = 0;
		}
	} else {
		if( h > minh ) {
			child[0] = new Grid(this); child[0]->_Set(xmin,ymin,xmax,ymin+h,minw,minh,level+1);
			child[1] = new Grid(this); child[1]->_Set(xmin,ymin+h,xmax,ymax,minw,minh,level+1);
			child[2] = 0;
			child[3] = 0;
		} else {
			child[0] = 0;
			child[1] = 0;
			child[2] = 0;
			child[3] = 0;
		}
	}
}
void Grid :: _FindNeightbours(void) {
	//poniewaz to ojciec wie z kim zadaja sie jego dzieci ;-) to powiezamy zadanie
	//wyszukania sasiadow wlasnie ojcu

	if( child[0] ) {
		child[0]->up		= ( up ? up->child[2] : 0 );
		child[0]->right	= child[1];
		child[0]->down	= child[2];
		child[0]->left	= ( left ? left->child[1] : 0 );
		child[0]->_FindNeightbours();
	}

	if( child[1] ) {
		child[1]->up		= ( up ? up->child[3] : 0 );
		child[1]->right	= ( right ? right->child[0] : 0 );
		child[1]->down	= child[3];
		child[1]->left	= child[0];
		child[1]->_FindNeightbours();
	}

	if( child[2] ) {
		child[2]->up		= child[0];
		child[2]->right	= child[3];
		child[2]->down	= ( down ? down->child[0] : 0 );
		child[2]->left	= ( left ? left->child[3] : 0 );
		child[2]->_FindNeightbours();
	}

	if( child[3] ) {
		child[3]->up		= child[1];
		child[3]->right	= ( right ? right->child[2] : 0 );
		child[3]->down	= ( down ? down->child[1] : 0 );
		child[3]->left	= child[2];
		child[3]->_FindNeightbours();
	}

}
void Grid :: Set(const Rect& rect,GLfloat minw,GLfloat minh) {
	_Set(rect.x1,rect.y1,rect.x2,rect.y2,minw,minh,0);
	_FindNeightbours();
}
void Grid :: Set(GLfloat x1,GLfloat y1,GLfloat x2,GLfloat y2,GLfloat minw,GLfloat minh) {
	_Set(x1,y1,x2,y2,minw,minh,0);
	_FindNeightbours();
}
//dodaje obiekt do wskazanej kratki
void Grid :: _AddObj(Bob *obj) {
	//1) obiekty kolizyjne trzymamy na oddzielnej liscie
	//2) objekty ruchome dodajemy na poczatku listy
	//   (przy aktualizacji polozenia sa one usuwane (przeszukanie listy od poczatku)
	//   tak wiec zostana szybciej odnalezione na liscie. Co wiecej, im bardziej sie
	//   ruszaja tym wieksza szansa,ze znajda sie na samym poczatku listy.)
	if( obj->col ) {	//kolizyjny
		if( obj->IsMovable() ) {
			col_list.push_front(obj);
		} else {
			col_list.push_back(obj);
		}
	} else {	//nie kolizyjny
		if( obj->IsMovable() ) {
			draw_list.push_front(obj);
		} else {
			draw_list.push_back(obj);
		}
	}
	obj->grid = this;
}
//usuwa obiekt z listy (niezaleznie na ktorej liscie sie znajduje)
int Grid :: _RemObjAnyList(Bob *obj) {
	list<Bob*>::iterator it;

	for( it = col_list.begin(); it != col_list.end(); ++it ) {
		if( (*it) == obj ) {
			col_list.erase(it);
			return 1;
		}
	}

	for( it = draw_list.begin(); it != draw_list.end(); ++it ) {
		if( (*it) == obj ) {
			draw_list.erase(it);
			return 1;
		}
	}

	return 0;
}
//usuwa obiekt z listy zgodnej z jego parametrami
int Grid :: _RemObj(Bob *obj) {
	list<Bob*>::iterator it;
	if( obj->col ) {
		//obiekt kolizyjny wiec usuwamy go z listy kolizyjnych
		for( it = col_list.begin(); it != col_list.end(); ++it ) {
			if( (*it) == obj ) {
				col_list.erase(it);
				return 1;
			}
		}
	} else {
		//obiekt nie kolizyjny wiec usuwamy go z listy nie kolizyjnych
		for( it = draw_list.begin(); it != draw_list.end(); ++it ) {
			if( (*it) == obj ) {
				draw_list.erase(it);
				return 1;
			}
		}
	}
	return 0;
}
//wykrywa kolizje
void Grid :: _DetectCollisionOnlyThis(Bob *obj) {
	list<Bob*>::iterator it;
	Bob *o;
	for( it = col_list.begin(); it != col_list.end(); ++it ) {
		o = (Bob*)(*it);
		if( o != obj ) {	//nie wykrywamy kolizji z samym soba
			obj->col->Collide( o->col );
		}
	}
}
void Grid :: _DetectCollisionAsc(Bob *obj) {
	//na poczatek sprawdzamy kolizje w tej kratce
	_DetectCollisionOnlyThis(obj);


	//teraz sprawdzamy kolizje z sasiadami
	if( up ) {
		up->_DetectCollisionOnlyThis(obj);
		if( up->right )
			up->right->_DetectCollisionOnlyThis(obj);
	}
	if( right ) {
		right->_DetectCollisionOnlyThis(obj);
		if( right->down )
			right->down->_DetectCollisionOnlyThis(obj);
	}
	if( down ) {
		down->_DetectCollisionOnlyThis(obj);
		if( down->left )
			down->left->_DetectCollisionOnlyThis(obj);
	}
	if( left ) {
		left->_DetectCollisionOnlyThis(obj);
		if( left->up )
			left->up->_DetectCollisionOnlyThis(obj);
	}

	//na koniec sprawdzamy kolizje z ojcem (i jego sasiadami)
	if( parent ) parent->_DetectCollisionAsc(obj);
}
void Grid :: _DetectCollisionThisAndChilds(Bob *obj) {
	_DetectCollisionOnlyThis(obj);
	if( child[0] ) child[0]->_DetectCollisionThisAndChilds(obj);
	if( child[1] ) child[1]->_DetectCollisionThisAndChilds(obj);
	if( child[2] ) child[2]->_DetectCollisionThisAndChilds(obj);
	if( child[3] ) child[3]->_DetectCollisionThisAndChilds(obj);
}
void Grid :: _DetectCollisionOnlyChilds(Bob *obj) {
	if( child[0] ) child[0]->_DetectCollisionThisAndChilds(obj);
	if( child[1] ) child[1]->_DetectCollisionThisAndChilds(obj);
	if( child[2] ) child[2]->_DetectCollisionThisAndChilds(obj);
	if( child[3] ) child[3]->_DetectCollisionThisAndChilds(obj);
}
void Grid :: _DetectCollisionDesc(Bob *obj) {
	//na poczatek sprawdzamy kolizje w tej kratce
	_DetectCollisionOnlyChilds(obj);

	//teraz sprawdzamy kolizje z sasiadami
	if( up ) {
		up->_DetectCollisionOnlyChilds(obj);
		if( up->right )
			up->right->_DetectCollisionOnlyChilds(obj);
	}
	if( right ) {
		right->_DetectCollisionOnlyChilds(obj);
		if( right->down )
			right->down->_DetectCollisionOnlyChilds(obj);
	}
	if( down ) {
		down->_DetectCollisionOnlyChilds(obj);
		if( down->left )
			down->left->_DetectCollisionOnlyChilds(obj);
	}
	if( left ) {
		left->_DetectCollisionOnlyChilds(obj);
		if( left->up )
			left->up->_DetectCollisionOnlyChilds(obj);
	}
}
//dodaje obiekt do wskazanej kratki lub jezeli sie do ktoregos z dzieciakow tej kratki
int Grid :: AddObj(Bob *obj) {
	if( 0 == obj ) return -1;

	//obiekt wpadnie do tej kratki jezeli w calosci sie w niej miesci
	if( obj->x < xmin || obj->x >= xmax || obj->y < ymin || obj->y >= ymax ) return 0;	//poza gridem

	//probujemy wcisnac obiekt ktoremus z dzieciakow
	for( int c = 0; c < C_CHILD_CNT; ++c )
		if( child[c] && child[c]->AddObj(obj) > 0 ) return 2;	//dodano do dzieciaka

	//nie udalo sie dodac do dzieciaka, a miesci sie w tej kratce wiec dodajemy go do tej kratki
	_AddObj(obj);

	return 1;	//dodano do tego grida
}
int Grid :: AddObjReverse(Bob *obj) {
	if( 0 == obj ) return -1;

	//sprawdzamy czy miesci sie kratce
	if( obj->x < xmin || obj->x >= xmax || obj->y < ymin || obj->y >= ymax ) {
		//nie miesci sie w tej kratce probujemy go wcisnac ojcowi
		if( parent ) return parent->AddObjReverse(obj);
		return 0;	//poza gridem (bo nie ma parenta czyli nie zmiescil sie w roocie)
	}

	//miesci sie w tej kratce wiec na poczatek probujemy go wcisnac dzieciakowi
	for( int c = 0; c < C_CHILD_CNT; ++c )
		if( child[c] && child[c]->AddObj(obj) > 0 ) return 2;	//dodano do dzieciaka

	//nie udalo sie wcisnac dzieciakowi wiec dodajemy go w tej kratce
	_AddObj(obj);

	return 1;	//dodano do tego grida
}
int Grid :: RemObj(Bob *obj) {
	if( 0 == obj ) return -1;
	_RemObj(obj);
	obj->grid = 0;	//nie jest juz w siatce
	return 1;
}
int Grid :: ActObj(Bob *obj) {
	if( 0 == obj ) return -1;

	if( obj->x >= xmin && obj->x < xmax && obj->y >= ymin && obj->y < ymax ) return 1;	//nie trzeba zmieniac grida

	//trzeba zmienic grida
	//w tym celu wypinamy go ze wskazanego grida
	RemObj(obj);
	//i wpinamy go do siatki idac od dolu
	if( parent ) return parent->AddObjReverse(obj);

	return 0;	//nie ma parenta wiec jestesmy poza gridem
}
int Grid :: ActObjCol(Bob *obj) {
	if( 0 == obj ) return -1;
	//zmienila sie kolizyjnosc obiektu
	//w tym celu wypinamy go (z dowolnej listy - mogl byc wczesniej kolizyjny lub nie kolizyjny)
	_RemObjAnyList(obj);
	//i ponownie wpinamy zgodnie z aktualnymi parametrami
	_AddObj(obj);

	return 1;	//dodano do tego grida
}
void Grid :: DetectCollision(Bob *obj) {
	if( 0 == obj ) return;
	if( obj->col ) {
		_DetectCollisionAsc(obj);
		_DetectCollisionDesc(obj);
	}
	return;
}

void Grid :: _DrawR(const Rect& rect) {
	//sprawdzamy, czy kratka zachacza o okreslony prostokat widocznosci
	if( rect.x1 >= xmax || rect.x2 < xmin || rect.y1 >= ymax || rect.y2 < ymin ) return;

	//rysujemy obiekty tylko rysowalne :-)
	if( draw_list.size() > 0 ) {
		//rysujemy ramke oznaczajaca, ze w kratce jest jakis obiekt
		if( draw_grid ) {
			GLfloat w = 3.0f,
							h = 3.0f;
			Color(1.0f, 0.0f, 1.0f, 1.0f);
			Box( xmin+w, ymin+h, xmax-w, ymax-h );
		}
		//rysujemy same obiekty
		list<Bob*>::iterator it;
		for( it = draw_list.begin(); it != draw_list.end(); ++it ) {
			if( *it )	(*it)->Blit();
		}
	}
	//rysujemy obiekty kolizyjne
	if( col_list.size() > 0 ) {
		//rysujemy ramke oznaczajaca, ze w kratce jest jakis obiekt
		if( draw_grid ) {
			GLfloat w = 3.0f,
							h = 3.0f;
			Color(1.0f, 0.0f, 1.0f, 1.0f);
			Box( xmin+w, ymin+h, xmax-w, ymax-h );
		}
		//rysujemy same obiekty
		list<Bob*>::iterator it;
		for( it = col_list.begin(); it != col_list.end(); ++it ) {
			if( *it )	(*it)->Blit();
		}
	}
	//rysujemy obiekty dzieciakow
	for( int c = 0; c < C_CHILD_CNT; ++c )
		if( child[c] ) child[c]->_DrawR(rect);
}
void Grid :: Draw(const Rect& rect) {
	if( draw_grid ) {
		//rysujemy ramke widocznosci
		Color(1.0f, 1.0f, 0.0f, 1.0f);
		Box( rect.x1, rect.y1, rect.x2, rect.y2 );
	}
	_DrawR(rect);
}
void Grid :: DrawGrid(int level) {

	if( ! draw_grid ) return;

	if( 0 == level ) {
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
	}

	for( int c = 0; c < C_CHILD_CNT; ++c )
		if( child[c] ) child[c]->DrawGrid(level+1);

	//rysujemy ramke
	Color(1.0f - ((float)level)/8.0, 0.0f, 0.0f, 1.0f);
	Box( xmin, ymin, xmax, ymax );

	//rysujemy powiazania do obiektow
	if( draw_list.size() > 0 ) {
		Bob *bob;
		list<Bob*>::iterator it;
		for( it = draw_list.begin(); it != draw_list.end(); ++it ) {
			bob = *it;
			if( bob ) {
				if( bob->movable ) {
					if( bob->col )
						Color(1.0f, 0.5f, 0.0f, 1.0f);
					else
						Color(0.0f, 0.5f, 0.0f, 1.0f);
				} else {
					if( bob->col )
						Color(1.0f, 0.5f, 0.5f, 1.0f);
					else
						Color(0.0f, 0.5f, 0.5f, 1.0f);
				}
				Line( (xmin+xmax)/2.0f, (ymin+ymax)/2.0f,
							bob->x, bob->y );
				if( bob->col ) {
					bob->col->Draw();
				}
				if( bob->radius > 0.0f ) {
					Color( 4.0f, 0.0f, 1.0f, 4.0f );
					Box( bob->x - bob->radius / 2.0f, bob->y - bob->radius / 2.0f,
							 bob->x + bob->radius / 2.0f, bob->y + bob->radius / 2.0f );
				}
			}
		}
	}

	//rysujemy powiazania do obiektow
	if( col_list.size() > 0 ) {
		Bob *bob;
		list<Bob*>::iterator it;
		for( it = col_list.begin(); it != col_list.end(); ++it ) {
			bob = *it;
			if( bob ) {
				if( bob->movable ) {
					if( bob->col )
						Color(1.0f, 0.5f, 0.0f, 1.0f);
					else
						Color(0.0f, 0.5f, 0.0f, 1.0f);
				} else {
					if( bob->col )
						Color(1.0f, 0.5f, 0.5f, 1.0f);
					else
						Color(0.0f, 0.5f, 0.5f, 1.0f);
				}
				Line( (xmin+xmax)/2.0f, (ymin+ymax)/2.0f,	bob->x, bob->y );
				if( bob->col ) {
					bob->col->Draw();
				}
				if( bob->radius > 0.0f ) {
					Color( 4.0f, 0.0f, 1.0f, 4.0f );
					Box( bob->x - bob->radius / 2.0f, bob->y - bob->radius / 2.0f,
							 bob->x + bob->radius / 2.0f, bob->y + bob->radius / 2.0f );
				}
			}
		}
	}

	if( 0 == level ) {
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
	}
}


};	//namespace Gfx
