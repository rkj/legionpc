#include "PicDraw.h"
#include "Pictures.h"
#include "Utils.h"


namespace Gfx {

PicDraw::PicDraw(Pic *dst_pic) {
	pic = dst_pic;
	buf = dst_pic->GetBufferWR();
	data_mode = dst_pic->GetDataMode();
	sls = dst_pic->GetScanlineSize();
	ps = dst_pic->GetPixelSize();
	w = dst_pic->GetWidth();
	h = dst_pic->GetHeight();
}

void PicDraw::Color(int gray) {
	r = gray;
	a = 255;
}

void PicDraw::Color(int red,int green,int blue,int alpha) {
	r = red;
	g = green;
	b = blue;
	a = alpha;
}


void PicDraw::Cls() {
	int p, s;
	s = h * sls;

	switch( data_mode ) {
		case PDM_RGB:
			for(p=0;p<s;p+=ps) {
				buf[p+0] = r;
				buf[p+1] = g;
				buf[p+2] = b;
			}
			break;
		case PDM_RGBA:
			for(p=0;p<s;p+=ps) {
				buf[p+0] = r;
				buf[p+1] = g;
				buf[p+2] = b;
				buf[p+3] = a;
			}
			break;
		case PDM_GRAY8:
			for(p=0;p<s;p+=ps) {
				buf[p+0] = r;
			}
			break;
		default:
			break;
	}
}

void PicDraw::Plot(int x,int y) {
	if( x<0 || y<0 || x>=w || y>=h ) return;

	unsigned char *pix = buf + x*ps + y*sls;
	switch( data_mode ) {
		case PDM_RGB:
			pix[0] = r;
			pix[1] = g;
			pix[2] = b;
			break;
		case PDM_RGBA:
			pix[0] = r;
			pix[1] = g;
			pix[2] = b;
			pix[3] = a;
			break;
		case PDM_GRAY8:
			pix[0] = r;
			break;
		default:
			break;
	}
}

void PicDraw::Line(int x1,int y1,int x2,int y2,bool doted) {
	//TODO - ulepszyc obciecie do granic obrazka
	if (x1 <  0) x1 = 0;
	if (x1 >= w) x1 = w - 1;
	if (x2 <  0) x2 = 0;
	if (x2 >= w) x2 = w - 1;
	if (y1 <  0) y1 = 0;
	if (y1 >= h) y1 = h - 1;
	if (y2 <  0) y2 = 0;
	if (y2 >= h) y2 = h - 1;

	int dh = x2 - x1,
		dv = y2 - y1,
		d;
	int x, y;
	bool odd = true;

	if( Abs(dh) > Abs(dv) )	{
		//bardziej pozioma
		if( x2 < x1 ) { //jak trzeba to zamieniami konce miejscami
			x = x2;
			x2 = x1;
			x1 = x;
			y = y2;
			y2 = y1;
			y1 = y;
			dh = -dh;
			dv = -dv;
		}
		//rysujemy
		y = y1;
		d = 0;
		for (x = x1; x <= x2; ++x) {
			if( doted ) {
				if( odd ) Plot(x,y);
				odd = !odd;
			} else
				Plot(x,y);
			d += dv;
			if(d > dh) {
				++y;
				d -= dh;
			} else if(d < -dh) {
				--y;
				d += dh;
			}
		}
	} else {
		//bardziej pionowa
		if(y2 < y1)	{ //jak trzeba to zamieniami konce miejscami
			y = y2;
			y2 = y1;
			y1 = y;
			x = x2;
			x2 = x1;
			x1 = x;
			dh = -dh;
			dv = -dv;
		}
		//rysujemy
		x = x1;
		d = 0;
		for(y = y1; y <= y2; ++y) {
			if( doted ) {
				if( odd ) Plot(x,y);
				odd = !odd;
			} else
				Plot(x,y);
			d += dh;
			if(d > dv) {
				++x;
				d -= dv;
			} else if(d < -dv) {
				--x;
				d += dv;
			}
		}
	}
}

void PicDraw::Box(int x1, int y1, int x2, int y2,bool doted) {
	Line(x1, y1, x2, y1, doted);
	Line(x2, y1, x2, y2, doted);
	Line(x2, y2, x1, y2, doted);
	Line(x1, y2, x1, y1, doted);
}




}	//namespace
