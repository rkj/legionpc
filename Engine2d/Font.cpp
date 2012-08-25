
#include <cstdio>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include <GL/gl.h>
//#include <GL/glut.h>

#include "Font.h"
#include "Utils.h"
#include "Textures.h"
#include "Bob.h"
#include "Basic.h"
#include "Settings.h"

using namespace std;
using namespace Core;

namespace Gfx {

void Font :: _reset(void) {
	ptex = 0;
	ltex = 0;
	glyphs_width = 0;
	glyphs_height = 0;
	glyphs_xshift = 0;
	glyphs_yshift = 0;
	glyphs_advance = 0;
	ib_antialiasing = true;
}
void Font :: _destroy(void) {
	delete ptex;
	delete[] ltex;
	delete[] glyphs_width;
	delete[] glyphs_height;
	delete[] glyphs_xshift;
	delete[] glyphs_yshift;
	delete[] glyphs_advance;
}
Font :: Font(void) {
	_reset();
}
Font :: ~Font() {
	_destroy();
}
void Font :: SetAntialiasing(bool pb_aa) {
	ib_antialiasing = pb_aa;
}
int Font :: Load(const string& name,int ptx) {

	//inicjujemy SDL_ttf
	if( TTF_Init() < 0 ) {
    ERROR("TTF_Init: " + TTF_GetError());
    return -1;
	}

	//ladujemy font do pamieci
	TTF_Font *font;
	font = TTF_OpenFontIndex(name.c_str(), ptx, 0);
	if( !font ) {
    ERROR("TTF_OpenFontIndex: " + TTF_GetError());
    return -2;
	}

	//inicjujemy atrybuty
	ptex = new PTex();
	ltex = new LTex[256];
	glyphs_width = new float[256];
	glyphs_height = new float[256];
	glyphs_xshift = new float[256];
	glyphs_yshift = new float[256];
	glyphs_advance = new float[256];

	//zbieramy statystyki o znaczkach
	int minx, maxx, miny, maxy, advance;
	int w,h,maxh,maxw,avgw;
	int li_ret;
	int gw[256], gh[256];
	float font_height = TTF_FontHeight(font);
//	float font_ascent = TTF_FontAscent(font);
//	float font_descent = TTF_FontDescent(font);
	maxh = 0; maxw = 0; avgw = 0;
	for( int i=0; i < 256; ++i ) {
		li_ret = TTF_GlyphMetrics( font, i, &minx, &maxx, &miny, &maxy, &advance);
		if( li_ret < 0 ) {
	    ERROR("TTF_GlyphMetrics: " + TTF_GetError());
	    return -3;
		}

		w = maxx - minx;
		h = maxy - miny;
		gw[i] = w;
		gh[i] = h;

//INFO(toString(i,"$%2x")+": "+char(i)+" w="+toString(w)+" h="+toString(h)+" adv="+toString(advance)+" minx="+toString(minx)+" maxy="+toString(maxy));

		glyphs_width[i]  = w / font_height;
		glyphs_height[i] = h / font_height;
		glyphs_xshift[i] =  minx / font_height;
		glyphs_yshift[i] = -maxy / font_height;
		glyphs_advance[i] = advance / font_height;

		avgw += w;
		if( h > maxh ) {
			maxh = h;
		}
		if( w > maxw ) {
			maxw = w;
		}
	}
	INFO("MAX FONT HEIGHT=" + toString((float)maxh));
	INFO("AVG FONT WIDTH=" + toString(((float)avgw+256.0)/256.0f));

	//obliczenie rozmiaru tekstury
	int tx_w, tx_h;
	tx_h = 16 * (maxh+1);
	tx_w = tx_h;

	//tworzymy teksture
	SDL_Surface *rgba_img;
	Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000; gmask = 0x00ff0000; bmask = 0x0000ff00;	amask = 0x000000ff;
#else
	rmask = 0x000000ff;	gmask = 0x0000ff00;	bmask = 0x00ff0000;	amask = 0xff000000;
#endif
	rgba_img = SDL_CreateRGBSurface(SDL_SWSURFACE, tx_w, tx_h, 8, rmask, gmask, bmask, amask);
	if( ! rgba_img ) {
		ERROR("SDL_CreateRGBSurface:");
		return -4;
	}

	//rysujemy literkami po teksturze
	Uint32 dkey;
	dkey = SDL_MapRGBA(rgba_img->format,	0, 0, 0, 0);
	SDL_FillRect(rgba_img, NULL, dkey);

	int xo = 0
	   ,yo = 0;
	SDL_Surface *glyph;
	SDL_Rect drect;
	SDL_Color fg,bg;
	fg.r = 255;	fg.g = 255;	fg.b = 255;
	bg.r = 0;	bg.g = 0;	bg.b = 0;
	for( int i = 0; i < 256; ++i ) {
		if( gw[i] > 0 ) {

			glyph = TTF_RenderGlyph_Shaded(font, i, fg, bg);

			if( !glyph ) {
		    ERROR("TTF_GlyphMetrics: " + TTF_GetError());
			} else {
				//kopiujemy znaczek na teksture
				if( xo > 0 && xo + gw[i] >= tx_w ) {
					//znaczek nie zmiesci sie w tym wierszu
					yo += maxh + 1;
					xo = 0;
				}

				SDL_SetAlpha(glyph, 0, 0);

				drect.x = xo;
				drect.y = yo;
				drect.w = gw[i];
				drect.h = maxh;

				SDL_BlitSurface(glyph,0,rgba_img,&drect);
				SDL_FreeSurface(glyph);

				xo += gw[i] + 1;
			}
		}
	}

	if( ib_antialiasing )
		ptex->SetFiltering(ptex->FM_LINEAR);
	else
		ptex->SetFiltering(ptex->FM_NEAREST);
	ptex->Set(rgba_img,GL_ALPHA);
	INFO("FONT_IMG_SIZE: " +  toString(ptex->GetImgWidth()) + "," + toString(ptex->GetImgHeight()) );
	INFO("FONT_TEXT_SIZE: " + toString(ptex->GetWidth()) + "," + toString(ptex->GetHeight()) );

	SDL_FreeSurface(rgba_img);

	//zwalniamy pamiec
	TTF_CloseFont(font);

	//zamykamy SDL_ttf
	TTF_Quit();

	//wyliczmy jeszcze tekstury logiczne
	xo = 0;	yo = 0;
	for( int i = 0; i < 256; ++i ) {
		if( gw[i] > 0 ) {
			//kopiujemy znaczek na teksture
			if( xo > 0 && xo + gw[i] >= tx_w ) {
				//znaczek nie zmiesci sie w tym wierszu
				yo += maxh + 1;
				xo = 0;
			}

//			ltex[i].Set( ptex, xo, yo, xo+gw[i], yo + maxh );
			ltex[i].Set( ptex, xo, yo, xo+gw[i], yo + gh[i] );

			xo += gw[i] + 1;
		} else {
			ltex[i].Set( ptex, xo,yo, xo,yo );
		}
	}

	return 1;
}


void FontManager :: _reset(void) {
	fonts.clear();
}
void FontManager :: _destroy(void) {
	Font* f;
	map<string,Font*>::iterator fit;
	for( fit=fonts.begin(); fit != fonts.end(); ++fit ) {
		f = fit->second;
		delete f;
	}
	fonts.clear();
}
string FontManager :: _key(const string& id,int siz) {
	return id + "|" + toString((int)siz);
}
FontManager :: FontManager(void) {
	_reset();
}
FontManager :: ~FontManager() {
	_destroy();
}
bool FontManager :: Exists(const string& id,int siz) {
	return fonts.find(_key(id,siz)) != fonts.end();
}
void FontManager :: Add(const string& id,int siz,Font* t,bool overwrite) {
	if( Exists(id,siz) ) {
		if( overwrite ) {
			Del(id,siz);	//usuwamy poprzednia teksture
		} else {
			return;				//jest juz i nienadpisujemy, wiec koniec
		}
	}
	fonts[_key(id,siz)] = t;
	return;
}
Font* FontManager :: Get(const string& id,int siz) {
	map<string,Font*>::const_iterator it;
	it = fonts.find(_key(id,siz));
	if( it != fonts.end() )
		return it->second;
	return 0;
}
Font* FontManager :: Rem(const string& id,int siz) {
	Font* t = 0;
	map<string,Font*>::iterator it;
	it = fonts.find(_key(id,siz));
	if( it != fonts.end() ) {
		t = it->second;
		fonts.erase(it);
	}
	return t;
}
void FontManager :: Del(const string& id,int siz) {
	Font* t;
	map<string,Font*>::iterator it;
	it = fonts.find(_key(id,siz));
	if( it != fonts.end() ) {
		t = it->second;
		delete t;
		fonts.erase(it);
	}
}
int FontManager :: Load(const string& filename,const string& root) {
	Settings sets;
	int ret = sets.ReadFile(filename);
	if( ret < 0 ) {
		ERROR("Blad wczytywania pliku z opisem fontów: " + sets.ErrorMsg());
		return -1;
	}
	return Load(sets,root);
}

int FontManager :: Load(const Settings& sets,const string& root) {
	if( ! sets.isValid() ) {
		ERROR("Obiekt opisuj¹cy tekstury jest niewa¿ny");
		return -2;
	}

	//!@# TODO
	return -1000;

//
//
//	Settings s, s1;
//	int n, li_ret;
//	string id, pid, file_name;
//	PTex *pt;
//	LTex *lt;
//	int ix1, ix2, iy1, iy2, ihsx, ihsy;
//
//	//usuwamy wszystko
//	_destroy();
//	_reset();
//
//	//ladujemy tekstury fizyczne
//	if( root != "" )
//		s = sets.Extract(root + ".Phisical");
//	else
//		s = sets.Extract(root + "Phisical");
//	if( ! s.isValid() ) {
//		ERROR("Blad pobierania danych na temat tekstur fizycznych: " + s.ErrorMsg());
//		return -3;
//	}
//	cout << s.Dump() << endl;
//
//	//TODO - dorobic pobieranie ilosci wpisow o tekturach
//	n = 1;
//	s1 = s.Extract("Phisical["+toString(n)+"]");
//	while( s1.isValid() ) {
//		cout << "tekstura<" + toString(n) + ">" << endl;
//		cout << s1.Dump() << endl;
//
//		id = s1.GetValS("Phisical.ID");
//		file_name = s1.GetValS("Phisical.FileName");
//		cout << "plik: " << id << " : " << file_name << endl;
//
//		pt = new PTex();
//		li_ret = pt->Load(file_name);
//		if( li_ret < 0 ) {
//			delete pt;
//			ERROR("Error loading the texture file (filename=" + file_name + ") !");
//			return -4;
//		}
//
//		AddPTex(id,pt);
//		cout << "Dodano teksture o id=" << id << endl;
//
//		n++;
//		s1 = s.Extract("Phisical["+toString(n)+"]");
//	}
//	cout << "Blad: " << s1.ErrorMsg() << endl;
//
//	//ladujemy tekstury logiczne
//	if( root != "" )
//		s = sets.Extract(root + ".Logical");
//	else
//		s = sets.Extract(root + "Logical");
//	if( ! s.isValid() ) {
//		ERROR("Blad pobierania danych na temat tekstur logicznych: " + s.ErrorMsg());
//		return -4;
//	}
//	cout << s.Dump() << endl;
//
//	//TODO - dorobic pobieranie ilosci wpisow o tekturach
//	n = 1;
//	s1 = s.Extract("Logical["+toString(n)+"]");
//	while( s1.isValid() ) {
//		cout << "tekstura<" + toString(n) + ">" << endl;
//		cout << s1.Dump() << endl;
//
//		id = s1.GetValS("Logical.ID");
//		pid = s1.GetValS("Logical.PID");
//		ix1 = s1.GetValI("Logical.Pos",0);
//		iy1 = s1.GetValI("Logical.Pos",1);
//		ix2 = s1.GetValI("Logical.Pos",2);
//		iy2 = s1.GetValI("Logical.Pos",3);
//		ihsx = s1.GetValI("Logical.HotSpot",0);
//		ihsy = s1.GetValI("Logical.HotSpot",1);
//
//		pt = GetPTex(pid);
//		if( 0 == pt ) {
//			ERROR("Brak tekstury fizycznej o ID=\"" + pid + "\". Tekstura logiczna o ID=\"" + id + "\" nie mo¿e byæ utworzona !!!");
//		} else {
//			lt = new LTex();
//			lt->Set(pt,ix1,iy1,ix2,iy2);
//			lt->SetHotSpot( ((GLfloat)(ihsx - ix1))/lt->GetWidth(), ((GLfloat)(ihsy - iy1))/lt->GetHeight() );
//			AddLTex(id,lt);
//			cout << "Dodano teksture o id=" << id << endl;
//		}
//
//		n++;
//		s1 = s.Extract("Logical["+toString(n)+"]");
//	}
//	cout << "Blad: " << s1.ErrorMsg() << endl;
//
//
//	cout << "Koniec textur" << endl;
//
//	return 1;
}



void Text(Font *font,const string& text, float x, float y, float sizh, float sizv) {

	int len = text.length();
	if( len <= 0 ) {
		return;
	}

	BeginBobBlits();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

		glTranslatef(x, y, 0.0f);
		glScalef(sizh,sizv,1.0f);

		glBindTexture(GL_TEXTURE_2D, font->ptex->GetTexNum() );

			glColor4f(red,green,blue,alpha);

			GLfloat x1, x2, y1, y2;
			int c;
			for( int ci = 0; ci < len; ++ci ) {
				c = (unsigned char)text.at(ci);
				x1 = font->glyphs_xshift[c];
				x2 = x1 + font->glyphs_width[c];
				y1 = font->glyphs_yshift[c];
				y2 = y1 + font->glyphs_height[c];

				LTex &ltex = *(font->ltex + c);
				glBegin(GL_QUADS);
					glTexCoord2f( ltex.Getfx1(), ltex.Getfy1() );		glVertex2f( x1, y1 );
					glTexCoord2f( ltex.Getfx2(), ltex.Getfy1() );		glVertex2f( x2,	y1 );
					glTexCoord2f( ltex.Getfx2(), ltex.Getfy2() );		glVertex2f( x2, y2 );
					glTexCoord2f( ltex.Getfx1(), ltex.Getfy2() );		glVertex2f( x1, y2 );
				glEnd();

				glTranslatef(font->glyphs_advance[c],0.0f,0.0f);

			}


	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	EndBobBlits();
}

float TextLength(Font *font,const std::string& text,float sizh) {
	int len = text.length();
	if( len <= 0 ) {
		return 0.0f;
	}

	float ret=0.0f;
	int c;
	for( int ci = 0; ci < len; ++ci ) {
		c = (unsigned char)text.at(ci);
		ret += font->glyphs_advance[c] * sizh;
	}

	return ret;
}

void _render_font(Font *font) {
	BeginBobBlits();

	LTex ltex(font->ptex);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

		glTranslatef(0.0f, 0.0f, 0.0f);

		glBindTexture(GL_TEXTURE_2D, ltex.GetTextureID() );
		glColor4f(red,green,blue,alpha);
		glBegin(GL_QUADS);
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			glTexCoord2f( ltex.Getfx1(), ltex.Getfy1() );		glVertex2f( 0.0f, 0.0f );
			glTexCoord2f( ltex.Getfx2(), ltex.Getfy1() );		glVertex2f(  1024/2,	0.0f );
			glTexCoord2f( ltex.Getfx2(), ltex.Getfy2() );		glVertex2f(  1024/2,  1024/2 );
			glTexCoord2f( ltex.Getfx1(), ltex.Getfy2() );		glVertex2f( 0.0f,  1024/2 );
		glEnd();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();



	EndBobBlits();
}

};	//namespace Gfx

