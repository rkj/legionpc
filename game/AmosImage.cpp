
#include "AmosImage.h"

int HQScaleType = SCLT_HQ2X;
bool HQShadows;

typedef unsigned char uchar;
typedef unsigned short ushort;

template<typename TYP> TYP Abs(TYP x) { return x < 0 ? -x : x; }
template<typename TYP> TYP Pow(TYP x) { return x*x; }

class Pixel {
public:
	uchar r,g,b,a;
	Pixel(void) {}
	~Pixel() {}
	void Set(const Pixel& p) {
		r = p.r;
		g = p.g;
		b = p.b;
		a = p.a;
	}
	void Read(uchar *buf,int x,int y,int w,int h) {
		if( x<0 || x>=w || y<0 || y>=h ) {
			r=0; g=0; b=0; a=0;
			return;
		}
		uchar *p = buf + (x+y*w)*4;
		r = *p;
		g = *(++p);
		b = *(++p);
		a = *(++p);
	}
	void Write(uchar *buf,int x,int y,int w,int h) {
		if( x<0 || x>=w || y<0 || y>=h ) {
			return;
		}
		uchar *p = buf + (x+y*w)*4;
		*p = r;
		*(++p) = g;
		*(++p) = b;
		*(++p) = a;
	}
	bool Equ(const Pixel& p) {
		int dist = Pow(r - p.r) + Pow(g - p.g) + Pow(b - p.b) + Pow(a - p.a);
		if( dist <= 16 )
			return true;
		else
			return false;
	}
	bool operator==(const Pixel& p) {
		return Equ(p);
	}
	bool operator!=(const Pixel& p) {
		return !Equ(p);
	}
};


void ImageHQShadow(uchar *src,int wid,int hei) {
/*
	A B C
	D P E
	F G H
*/

#define MARK_A(V) wtd[(x-1)+(y-1)*wid] = V;
#define MARK_B(V) wtd[(x  )+(y-1)*wid] = V;
#define MARK_C(V) wtd[(x+1)+(y-1)*wid] = V;
#define MARK_D(V) wtd[(x-1)+(y  )*wid] = V;
#define MARK_P(V) wtd[(x  )+(y  )*wid] = V;
#define MARK_E(V) wtd[(x+1)+(y  )*wid] = V;
#define MARK_F(V) wtd[(x-1)+(y+1)*wid] = V;
#define MARK_G(V) wtd[(x  )+(y+1)*wid] = V;
#define MARK_H(V) wtd[(x+1)+(y+1)*wid] = V;

	if( !HQShadows ) return;

	uchar buf[wid*hei*4], wtd[wid*hei];
	int x,y;
	Pixel p,a,b,c,d,e,f,g,h;

	for(y=0; y<hei; ++y) {
		for(x=0; x<wid; ++x ) {
			wtd[x+y*wid] = 0;	//co robic
		}
	}

	for(y=0; y<hei; ++y) {
		for(x=0; x<wid; ++x ) {
			a.Read(src,x-1,y-1,wid,hei);
			b.Read(src,x,y-1,wid,hei);
			c.Read(src,x+1,y-1,wid,hei);
			d.Read(src,x-1,y,wid,hei);
			p.Read(src,x,y,wid,hei);
			e.Read(src,x+1,y,wid,hei);
			f.Read(src,x-1,y+1,wid,hei);
			g.Read(src,x,y+1,wid,hei);
			h.Read(src,x+1,y+1,wid,hei);

			if( p==b || p==d || p==e || p==g ) continue;

//			if( b!=d && b!=e && b!=g && (d!=e || d!=g || e!=g) ) continue;
//			if( d!=b && d!=g && d!=e && (b!=e || b!=g || e!=g) ) continue;
//			if( e!=b && e!=d && e!=g && (b!=d || b!=g || d!=g) ) continue;
//			if( g!=b && g!=d && g!=e && (b!=d || b!=e || d!=e) ) continue;


			if( p==a && p==c && p==f && a==h ) {
				MARK_P(1);
				MARK_A(2);
				MARK_C(2);
				MARK_F(2);
				MARK_H(2);
				continue;
			}
			if( p==a && p==c && p==f ) {	//bez h
				MARK_P(1);
				MARK_A(2);
				MARK_C(2);
				MARK_F(2);
				continue;
			}
			if( p==c && p==f && p==h ) {	//bez a
				MARK_P(1);
				MARK_C(2);
				MARK_F(2);
				MARK_H(2);
				continue;
			}
			if( p==a && p==f && p==h ) {	//bez c
				MARK_P(1);
				MARK_A(2);
				MARK_F(2);
				MARK_H(2);
				continue;
			}
			if( p==a && p==c && p==h ) {	//bez f
				MARK_P(1);
				MARK_A(2);
				MARK_C(2);
				MARK_H(2);
				continue;
			}

			if( p==a && p==f ) {
				MARK_P(1);
				MARK_A(2);
				MARK_F(2);
				MARK_B(3);
				MARK_D(3);
				MARK_G(3);
				continue;
			}
			if( p==a && p==c ) {
				MARK_P(1);
				MARK_A(2);
				MARK_C(2);
				MARK_D(3);
				MARK_B(3);
				MARK_E(3);
				continue;
			}
			if( p==h && p==c ) {
				MARK_P(1);
				MARK_H(2);
				MARK_C(2);
				MARK_B(3);
				MARK_E(3);
				MARK_G(3);
				continue;
			}
			if( p==h && p==f ) {
				MARK_P(1);
				MARK_H(2);
				MARK_F(2);
				MARK_D(3);
				MARK_E(3);
				MARK_G(3);
				continue;
			}


		}
	}

	int cr,cg,cb,ca;
	for(y=0; y<hei; ++y) {
		for(x=0; x<wid; ++x ) {
			if( wtd[x+y*wid]>0 ) {

				b.Read(src,x,y-1,wid,hei);
				d.Read(src,x-1,y,wid,hei);
				p.Read(src,x,y,wid,hei);
				e.Read(src,x+1,y,wid,hei);
				g.Read(src,x,y+1,wid,hei);

				cr = p.r * 4;
				cg = p.g * 4;
				cb = p.b * 4;
				ca = p.a * 4;

				cr += b.r;
				cg += b.g;
				cb += b.b;
				ca += b.a;

				cr += d.r;
				cg += d.g;
				cb += d.b;
				ca += d.a;

				cr += e.r;
				cg += e.g;
				cb += e.b;
				ca += e.a;

				cr += g.r;
				cg += g.g;
				cb += g.b;
				ca += g.a;

				p.r = cr / 8;
				p.g = cg / 8;
				p.b = cb / 8;
				p.a = ca / 8;

				p.Write(buf,x,y,wid,hei);
			} else {
				p.Read(src,x,y,wid,hei);
				p.Write(buf,x,y,wid,hei);
			}
		}
	}

	cr = wid*hei*4;
	for(int i=0;i<cr;++i) {
		src[i] = buf[i];
	}



}

//Scale2x/AdvMAME2x
void Scale2x(uchar *src,uchar* dst,int w,int h) {

/*
  A    --\ 1 2
C P B  --/ 3 4
  D
 1=P; 2=P; 3=P; 4=P;
 IF C==A AND C!=D AND A!=B => 1=A
 IF A==B AND A!=C AND B!=D => 2=B
 IF B==D AND B!=A AND D!=C => 4=D
 IF D==C AND D!=B AND C!=A => 3=C
*/

	int x,y,w2=w*2,h2=h*2;
	Pixel p,a,b,c,d,d1,d2,d3,d4;

	for(y=0; y<h; ++y) {
		for(x=0; x<w; ++x ) {
			p.Read(src,x,y,w,h);
			a.Read(src,x,y-1,w,h);
			b.Read(src,x+1,y,w,h);
			c.Read(src,x-1,y,w,h);
			d.Read(src,x,y+1,w,h);

			d1.Set(p); d2.Set(p); d3.Set(p); d4.Set(p);

			if( c.Equ(a) && !c.Equ(d) && !a.Equ(b) ) d1.Set(a);
			if( a.Equ(b) && !a.Equ(c) && !b.Equ(d) ) d2.Set(b);
			if( d.Equ(c) && !d.Equ(b) && !c.Equ(a) ) d3.Set(c);
			if( b.Equ(d) && !b.Equ(a) && !d.Equ(c) ) d4.Set(d);

			d1.Write(dst,x*2,y*2,w2,h2);
			d2.Write(dst,x*2+1,y*2,w2,h2);
			d3.Write(dst,x*2,y*2+1,w2,h2);
			d4.Write(dst,x*2+1,y*2+1,w2,h2);

		}
	}

}

void Conv32_16(uchar *src,ushort *dst,int w,int h) {
	int siz = w*h;
	uchar *s;
	ushort *d,r,g,b,a;
	s = src;
	d = dst;
	for(int i=0; i<siz; ++i ) {
		r = (*(s++)) >> 3;
		g = (*(s++)) >> 2;
		b = (*(s++)) >> 3;
		a = (*(s++));
		*(d++) = (r << 11) + (g << 5) + b;
	}
}

void Conv32A_16(uchar *src,ushort *dst,int w,int h) {
	int siz = w*h;
	uchar *s;
	ushort *d,r,g,b,a;
	s = src;
	d = dst;
	for(int i=0; i<siz; ++i ) {
		s += 3;
		a = (*(s++));
		r = a >> 3;
		g = a >> 2;
		b = a >> 3;
		*(d++) = (r << 11) + (g << 5) + b;
	}
}

void SetAlpha(uchar *dst,int w,int h,uchar a) {
	int siz = w*h;
	uchar r,g,b;
	for(int i=0; i<siz; ++i ) {
		b = dst[0];
		g = dst[1];
		r = dst[2];
		*(dst++) = r;
		*(dst++) = g;
		*(dst++) = b;
		*(dst++) = a;
	}
}

void SetAlphaG(uchar *dst,int w,int h,uchar *src) {
	int siz = w*h;
	uchar r,g,b;
	for(int i=0; i<siz; ++i ) {
		b = dst[0];
		g = dst[1];
		r = dst[2];
		*(dst++) = r;
		*(dst++) = g;
		*(dst++) = b;
		*(dst++) = src[1];
		src+=4;
	}
}

void InitLUTs(void);
void hq2x_32( unsigned char * pIn, unsigned char * pOut, int Xres, int Yres, int BpL );


void ImageScale2x(uchar *src,uchar* dst,int w,int h) {
    ushort *buf16 = new ushort[w*h*2];
    uchar  *buf32 = new uchar[w*h*4*4];

	switch( HQScaleType ) {
		case SCLT_SCALE2X:
			//ImageHQShadow(src,w,h);
			Scale2x(src,dst,w,h);
			break;
		case SCLT_HQ2X:

			Conv32_16(src,buf16,w,h);

			//skalujemy kolory
			InitLUTs();	//TODO: moze wystarczy tylko raz wywolac?
			hq2x_32( (uchar*)buf16, dst, w, h, w*2*4 );

			//skalujemy kanal alpha
			Conv32A_16(src,buf16,w,h);
			hq2x_32( (uchar*)buf16, buf32, w, h, w*2*4 );

			//laczymy kolory i kanal alpha
			SetAlphaG(dst,w*2,h*2,buf32);

			delete[] buf32;
			delete[] buf16;

			break;
		default:
			break;
	}
}

