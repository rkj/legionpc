#ifndef D_TYPES_H_D
#define D_TYPES_H_D

#ifndef M_PI
	#define M_PI 3.14159265358979323846
#endif


namespace Core {

	class Rect {
		public:
			GLfloat x1,y1,x2,y2;
			Rect(void) {}
			Rect(GLfloat x1,GLfloat y1,GLfloat x2,GLfloat y2) : x1(x1), y1(y1), x2(x2), y2(y2) {}
			~Rect() {} 
	};
	class Point {
		public:
			GLfloat x,y;
			Point(void) {}
			Point(GLfloat x,GLfloat y) : x(x), y(y) {}
			~Point() {}
	};


};

#endif /*D_TYPES_H_D*/
