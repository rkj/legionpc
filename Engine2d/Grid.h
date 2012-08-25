#ifndef D_GRID_H_D
#define D_GRID_H_D

#include <list>
#include <GL/gl.h>

#include "Types.h"

namespace Gfx {
	class Bob;
};

namespace Core {

	class Grid {
		protected:
			enum { C_CHILD_CNT = 4 };
			GLfloat xmin, xmax, ymin, ymax;
			Grid *child[C_CHILD_CNT];
			Grid *parent, *left, *right, *up, *down;
			unsigned short int level;

			std::list<Gfx::Bob*>	draw_list,			//lista obiektow tylko rysowalnych
														col_list;				//lista obiektow kolizyjnych

			void _reset(void);
			void _destroy(void);
			void _DrawR(const Rect& rect);
			void _AddObj(Gfx::Bob *obj);
			int _RemObj(Gfx::Bob *obj);
			int _RemObjAnyList(Gfx::Bob *obj);
			void _DetectCollisionOnlyThis(Gfx::Bob *obj);
			void _DetectCollisionThisAndChilds(Gfx::Bob *obj);
			void _DetectCollisionOnlyChilds(Gfx::Bob *obj);
			void _DetectCollisionDesc(Gfx::Bob *obj);
			void _DetectCollisionAsc(Gfx::Bob *obj);
			void _Set(GLfloat x1,GLfloat y1,GLfloat x2,GLfloat y2,GLfloat minw,GLfloat minh,unsigned short int lev);
			void _FindNeightbours(void);

		public:
			Grid(void);
			Grid(Grid *parent);
			~Grid();
			void Set(const Rect& rect,GLfloat minw,GLfloat minh);
			void Set(GLfloat x1,GLfloat y1,GLfloat x2,GLfloat y2,GLfloat minw,GLfloat minh);
			int AddObj(Gfx::Bob *obj);
			int AddObjReverse(Gfx::Bob *obj);
			int RemObj(Gfx::Bob *obj);
			int ActObj(Gfx::Bob *obj);
			int ActObjCol(Gfx::Bob *obj);
			void DetectCollision(Gfx::Bob *obj);

			void Draw(const Rect& rect);
			void DrawGrid(int level);
	};

	///wlacznik rysowania siatki
	extern bool draw_grid;

};

#endif /*D_GRID_H_D*/
