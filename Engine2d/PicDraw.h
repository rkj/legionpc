#ifndef D_PICDRAW_H_D
#define D_PICDRAW_H_D

namespace Gfx {

class Pic;

class PicDraw {
private:
	Pic *pic;
	unsigned char* buf;
	int data_mode, sls, ps;
	int w,h;
	int r,g,b,a;
public:
	PicDraw(Pic *dst_pic);

	void Color(int gray);
	void Color(int red,int green,int blue,int alpha=255);
	void Cls();
	void Plot(int x,int y);
	void Line(int x1,int y1,int x2,int y2,bool dotet=false);
	void Box(int x1, int y1, int x2, int y2,bool doted=false);
};

}

#endif // D_PICDRAW_H_D



