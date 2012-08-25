#include <iostream>

//#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/glext.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "Textures.h"
#include "Utils.h"
#include "Settings.h"
#include "Pictures.h"

using namespace std;
using namespace Core;

namespace Gfx {

char PTex::ic_default_filtering = FM_BILINEAR;

void PTex :: _reset(void) {
	texnum = 0;
	texbinded = false;
	w = 0;
	h = 0;
	img_w = 0;
	img_h = 0;
	ic_filtering = ic_default_filtering;
}
void PTex :: _destroy(void) {
	if( texbinded ) {
		glDeleteTextures(1,&texnum);
		texbinded = false;
	}
}
PTex :: PTex(void) {
	_reset();
}
PTex :: PTex(const string& name) {
	_reset();
	Load(name);
}
PTex :: PTex(const PTex& tex) {
	_reset();
	texnum = tex.texnum;
	w = tex.w;
	h = tex.h;
}
PTex :: ~PTex() {
	_destroy();
}
void PTex :: SetFiltering(char mode) {
	ic_filtering = mode;
}
void PTex :: SetDefaultFiltering(char mode) {
	ic_default_filtering = mode;
}
int PTex :: Set(Pic *pic,GLint format) {
	if( ! pic ) {
		ERROR("PTex::Set: Null pointer picture");
		return -1;
	}
	return Set(pic->GetBuffer(),pic->GetWidth(),pic->GetHeight(),format);
}
int PTex :: Set(SDL_Surface *image,GLint format) {
	if( ! image ) {
		ERROR("PTex::Set: Null pointer image");
		return -1;
	}
	return Set((unsigned char*)image->pixels,image->w,image->h,format);
}
int PTex :: Set(const unsigned char *buf,int width, int height,GLint format) {
	if( ! buf ) {
		ERROR("PTex::Set: Null pointer buf");
		return -1;
	}

	//sprawdzamy czy nie jest wiekszy niz na to pozwala OpenGL
	int max_size;
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max_size);
	if( (width > max_size) || (height > max_size) ) {
		ERROR("Image size exceeds max texture size, which is "+toString(max_size)+" pixels for each side");
		return -2;
	}

	glGenTextures( 1, &texnum );
	texbinded = true;
	glBindTexture( GL_TEXTURE_2D, texnum );

//	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
//	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
//	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER );
//	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER );

	switch( ic_filtering ) {
		case FM_NEAREST:
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
			break;
		case FM_LINEAR:
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
			break;
		case FM_BILINEAR:
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );
			break;
		default:
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
			break;
	}

/*
	gluBuild2DMipmapLevels(	GL_TEXTURE_2D,
										 			GL_RGBA,
													image->w, image->h,
													GL_RGBA,
													GL_UNSIGNED_BYTE,
													0,	//mipmap image level
													0,	//mipmap base level
													0,	//mipmap max level
													image->pixels );
*/

	gluBuild2DMipmaps(	GL_TEXTURE_2D,
								 			format,
											width, height,
											format,
											GL_UNSIGNED_BYTE,
											buf );

	img_w = width;
	img_h = height;

	GLint par;
	glGetTexLevelParameteriv( GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &par);
	w = par;
	glGetTexLevelParameteriv( GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &par);
	h = par;

	return 1;
}
//int PTex :: Load(const string& name) {
//
//	SDL_Surface *image, *rgba_img;
//	Uint32 dkey;
//
//
//	//ladujemy obrazek
//	image = (SDL_Surface *) IMG_Load(name.c_str());
//	if( 0 == image ) {
//		ERROR("Error while loading image file >"+name+"<:");
//		return -1;
//	}
//
//	//sprawdzamy czy nie jest wiekszy niz na to pozwala OpenGL
//	int max_size;
//	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max_size);
//	if( (image->w > max_size) || (image->h > max_size) ) {
//		ERROR("Image size exceeds max texture size, which is "+toString(max_size)+" pixels for each side");
//		SDL_FreeSurface(image);
//		return -2;
//	}
//
////	img_w = image->w;
////	img_h = image->h;
//
//	//konwersja wczytanego obrazka do bytemapy RGBA
//	Uint32 rmask, gmask, bmask, amask;
//#if SDL_BYTEORDER == SDL_BIG_ENDIAN
//	rmask = 0xff000000; gmask = 0x00ff0000; bmask = 0x0000ff00;	amask = 0x000000ff;
//#else
//	rmask = 0x000000ff;	gmask = 0x0000ff00;	bmask = 0x00ff0000;	amask = 0xff000000;
//#endif
//	rgba_img = SDL_CreateRGBSurface(SDL_SWSURFACE, image->w, image->h, 32, rmask, gmask, bmask, amask);
//
//
////	printf(name.c_str()); printf("\n");
////	printf("SBPP=%d\n",image->format->BytesPerPixel);
////	printf("DBPP=%d\n",rgba_img->format->BytesPerPixel);
////	unsigned int a;
////	Uint8 *bits;
//
////bits = ((Uint8 *)image->pixels);
////for( int i = 0; i < 256; ++i ) {
////	printf("%2.2x,",(int)(bits[i]));
////	if( i%4 == 3 ) printf(" ");
////}
//
//	//na rysunku docelowym wszystko jest przezroczyste :-)
//	dkey = SDL_MapRGBA(rgba_img->format,	0, 0, 0, 255);
//	SDL_FillRect(rgba_img, NULL, dkey);
//	//na rysunku zrodlowym ustawiamy kolor przezroczysty
//
//	SDL_SetAlpha(image,0,255);
//	SDL_SetAlpha(rgba_img,0,255);
//
//	//kopiujemy zrodlo do celu (przezroczystosc bedzie uwzgledniona)
//	SDL_BlitSurface(image, 0, rgba_img, 0);
//	SDL_FreeSurface(image);
//	image = rgba_img;
//
////printf("\n");
////bits = ((Uint8 *)image->pixels);
////for( int i = 0; i < 256; ++i ) {
////	printf("%2.2x,",(int)(bits[i]));
////	if( i%4 == 3 ) printf(" ");
////}
//
//
///*
//	glGenTextures( 1, &texnum );
//	texbinded = true;
//	glBindTexture( GL_TEXTURE_2D, texnum );
//	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
//	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
//	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
//	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );
//*/
///*
//	gluBuild2DMipmapLevels(	GL_TEXTURE_2D,
//										 			GL_RGBA,
//													image->w, image->h,
//													GL_RGBA,
//													GL_UNSIGNED_BYTE,
//													0,	//mipmap image level
//													0,	//mipmap base level
//													0,	//mipmap max level
//													image->pixels );
//*/
///*
//	gluBuild2DMipmaps(	GL_TEXTURE_2D,
//										 			GL_RGBA,
//													image->w, image->h,
//													GL_RGBA,
//													GL_UNSIGNED_BYTE,
//													image->pixels );
//
//	GLint par;
//	glGetTexLevelParameteriv( GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &par);
//	w = par;
//	glGetTexLevelParameteriv( GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &par);
//	h = par;
//*/
//	if( Set(image) < 0 ) {
//		SDL_FreeSurface(image);
//		return -1;
//	}
//
//	SDL_FreeSurface(image);
//
//	return 1;
//}

int PTex :: Load(const string& name) {

	int li_ret;

	Pic pic;
	li_ret = pic.Load(name.c_str());
	if( li_ret < 0 ) {
		ERROR("Error while loading image file >"+name+"<:");
		return -1;
	}

	li_ret = Set(&pic);
	return li_ret;
}


void LTex :: _reset(void) {
	tex = 0;
	ix1 = 0; iy1 = 0; ix2 = 0; iy2 = 0;
	fx1 = 0.0; fy1 = 0.0; fx2 = 0.0; fy2 = 0.0;
	fhsx = 0.0; fhsy = 0.0;
}
void LTex :: _destroy(void) {
}
float LTex :: _i2fw(int v) const {
	float f = v;
	f /= tex->img_w;
	return f;
}
float LTex :: _i2fh(int v) const {
	float f = v;
	f /= tex->img_h;
	return f;
}
int LTex :: _f2iw(float v) const {
	int i = (int)(tex->img_w * v);
	return i;
}
int LTex :: _f2ih(float v) const {
	int i = (int)(tex->img_h * v);
	return i;
}
LTex :: LTex(void) {
	_reset();
}
LTex :: LTex( const PTex* tex ) {
	_reset();
	Set(tex);
}
LTex :: LTex( const PTex* tex, int x1, int y1, int x2, int y2 ) {
	_reset();
	Set(tex,x1,y1,x2,y2);
}
LTex :: LTex( const PTex* tex, float x1, float y1, float x2, float y2 ) {
	_reset();
	Set(tex,x1,y1,x2,y2);
}
LTex :: ~LTex() {
	_destroy();
}
void LTex :: Set( const PTex* tex ) {
	this->tex = tex;
	ix1 = 0;
	iy1 = 0;
	ix2 = tex->img_w;
	iy2 = tex->img_h;
	fx1 = 0.0f;
	fy1 = 0.0f;
	fx2 = 1.0f;
	fy2 = 1.0f;
}
void LTex :: Set( const PTex* tex, int x1, int y1, int x2, int y2 ) {
	this->tex = tex;
	ix1 = x1;
	iy1 = y1;
	ix2 = x2;
	iy2 = y2;
	fx1 = _i2fw(ix1);
	fy1 = _i2fh(iy1);
	fx2 = _i2fw(ix2);
	fy2 = _i2fh(iy2);

}
void LTex :: Set( const PTex* tex, float x1, float y1, float x2, float y2 ) {
	this->tex = tex;
	fx1 = x1;
	fy1 = y1;
	fx2 = x2;
	fy2 = y2;
	ix1 = _f2iw(fx1);
	iy1 = _f2ih(fy1);
	ix2 = _f2iw(fx2);
	iy2 = _f2ih(fy2);

}
GLuint LTex :: GetTextureID(void) const {
	if( tex )
		return tex->texnum;
	else
		return 0;
}


void TextureManager :: _reset(void) {
	ptex.clear();
	ltex.clear();
	ptex_flags.clear();
	ltex_flags.clear();
}
void TextureManager :: _destroy(void) {
	LTex* lt;
	map<string,LTex*>::iterator lit;
	map<string,unsigned char>::iterator itf;
	for( lit=ltex.begin(); lit != ltex.end(); ++lit ) {
		//usuwamy obiekt ale tylgo gdy nie ma flagi FL_ISREF
		itf = ltex_flags.find(lit->first);
		if( itf != ltex_flags.end() ) {
			if( 0==(itf->second & FL_ISREF) ) {
				lt = lit->second;
				delete lt;
			}
		}
	}

	PTex* pt;
	map<string,PTex*>::iterator pit;
	for( pit=ptex.begin(); pit != ptex.end(); ++pit ) {
		//usuwamy obiekt ale tylgo gdy nie ma flagi FL_ISREF
		itf = ptex_flags.find(pit->first);
		if( itf != ptex_flags.end() ) {
			if( 0==(itf->second & FL_ISREF) ) {
				pt = pit->second;
				delete pt;
			}
		}
	}
}
TextureManager :: TextureManager(void) {
	_reset();
}
TextureManager :: ~TextureManager() {
	_destroy();
}
bool TextureManager :: ExistsPTex(const string& id) {
	return ptex.find(id) != ptex.end();
}
bool TextureManager :: ExistsLTex(const string& id) {
	return ltex.find(id) != ltex.end();
}
void TextureManager :: AddPTex(const string& id,PTex* t,bool overwrite,bool ref) {
	if( ExistsPTex(id) ) {
		if( overwrite ) {
			DelPTex(id);	//usuwamy poprzednia teksture
		} else {
			return;				//jest juz i nienadpisujemy, wiec koniec
		}
	}
	ptex[id] = t;
	ptex_flags[id] = (ref ? FL_ISREF : 0);
	return;
}
void TextureManager :: AddLTex(const string& id,LTex* t,bool overwrite,bool ref) {
	if( ExistsLTex(id) ) {
		if( overwrite ) {
			DelLTex(id);	//usuwamy poprzednia teksture
		} else {
			return;				//jest juz i nienadpisujemy, wiec koniec
		}
	}
	ltex[id] = t;
	ltex_flags[id] = (ref ? FL_ISREF : 0);
	return;
}

PTex* TextureManager :: GetPTex(const string& id) {
	map<string,PTex*>::const_iterator it;
	it = ptex.find(id);
	if( it != ptex.end() )
		return it->second;
	return 0;
}

LTex* TextureManager :: GetLTex(const string& id) {
	map<string,LTex*>::const_iterator it;
	it = ltex.find(id);
	if( it != ltex.end() )
		return it->second;
	return 0;
}

PTex* TextureManager :: RemPTex(const string& id) {
	PTex* t = 0;
	map<string,PTex*>::iterator it;
	it = ptex.find(id);
	if( it != ptex.end() ) {
		t = it->second;
		ptex.erase(it);
	}
	return t;
}

LTex* TextureManager :: RemLTex(const string& id) {
	LTex* t = 0;
	map<string,LTex*>::iterator it;
	it = ltex.find(id);
	if( it != ltex.end() ) {
		t = it->second;
		ltex.erase(it);
	}
	return t;
}

void TextureManager :: DelPTex(const string& id) {
	PTex* t;
	map<string,PTex*>::iterator it;
	map<string,unsigned char>::iterator itf;
	it = ptex.find(id);
	if( it != ptex.end() ) {
		//usuwamy obiekt ale tylgo gdy nie ma flagi FL_ISREF
		itf = ptex_flags.find(id);
		if( itf != ptex_flags.end() ) {
			if( 0==(itf->second & FL_ISREF) ) {
				t = it->second;
				delete t;
			}
		}
		ptex.erase(it);
	}
}

void TextureManager :: DelLTex(const string& id) {
	LTex* t;
	map<string,LTex*>::iterator it;
	map<string,unsigned char>::iterator itf;
	it = ltex.find(id);
	if( it != ltex.end() ) {
		//usuwamy obiekt ale tylgo gdy nie ma flagi FL_ISREF
		itf = ltex_flags.find(id);
		if( itf != ltex_flags.end() ) {
			if( 0==(itf->second & FL_ISREF) ) {
				t = it->second;
				delete t;
			}
		}
		ltex.erase(it);
	}
}

void TextureManager :: DelAll(void) {
	_destroy();
	_reset();
}

int TextureManager :: CountPTex(void) {
	return ptex.size();
}

int TextureManager :: CountLTex(void) {
	return ltex.size();
}


int TextureManager :: Load(const string& filename,const string& root) {
	Settings sets;
	int ret = sets.ReadFile(filename);
	if( ret < 0 ) {
		ERROR("Blad wczytywania pliku z opisem tekstur: " + sets.ErrorMsg());
		return -1;
	}
	return Load(sets,root);
}

int TextureManager :: Load(const Settings& sets,const string& root) {
	if( ! sets.isValid() ) {
		ERROR("Obiekt opisuj¹cy tekstury jest niewa¿ny");
		return -2;
	}

	Settings s, s1;
	int n, li_ret;
	string id, pid, file_name;
	PTex *pt;
	LTex *lt;
	int ix1, ix2, iy1, iy2, ihsx, ihsy;
	double fhsx, fhsy;

	//usuwamy wszystko
	_destroy();
	_reset();

	//ladujemy tekstury fizyczne
	if( root != "" )
		s = sets.Extract(root + ".Phisical");
	else
		s = sets.Extract(root + "Phisical");
	if( ! s.isValid() ) {
		ERROR("Blad pobierania danych na temat tekstur fizycznych: " + s.ErrorMsg() );
		return -3;
	}
	INFO(s.Dump());

	//TODO - dorobic pobieranie ilosci wpisow o tekturach
	n = 1;
	s1 = s.Extract("Phisical["+toString(n)+"]");
	while( s1.isValid() ) {
		INFO("tekstura<" + toString(n) + ">");
		INFO(s1.Dump());

		id = s1.GetValS("Phisical.ID");
		file_name = s1.GetValS("Phisical.FileName");
		INFO("plik: " + id + " : " + file_name);

		pt = new PTex();
		li_ret = pt->Load(file_name);
		if( li_ret < 0 ) {
			delete pt;
			ERROR("Error loading the texture file (filename=" + file_name + ") !" );
			return -4;
		}

		AddPTex(id,pt);
		INFO("Dodano teksture o id=" + id );

		n++;
		s1 = s.Extract("Phisical["+toString(n)+"]");
	}
	INFO("Blad: " + s1.ErrorMsg() );

	//ladujemy tekstury logiczne
	if( root != "" )
		s = sets.Extract(root + ".Logical");
	else
		s = sets.Extract(root + "Logical");
	if( ! s.isValid() ) {
		ERROR("Blad pobierania danych na temat tekstur logicznych: " + s.ErrorMsg() );
		return -4;
	}
	INFO( s.Dump() );

	//TODO - dorobic pobieranie ilosci wpisow o tekturach
	n = 1;
	s1 = s.Extract("Logical["+toString(n)+"]");
	while( s1.isValid() ) {
		INFO( "tekstura<" + toString(n) + ">" );
		INFO( s1.Dump() );

		id = s1.GetValS("Logical.ID");
		pid = s1.GetValS("Logical.PID");
		ix1 = s1.GetValI("Logical.Pos",0);
		iy1 = s1.GetValI("Logical.Pos",1);
		ix2 = s1.GetValI("Logical.Pos",2);
		iy2 = s1.GetValI("Logical.Pos",3);
		if( ix2 < 0 ) ix2 = ix1 - ix2;
		if( iy2 < 0 ) iy2 = iy1 - iy2;

		if( s1.IsValF("Logical.HotSpot") ) {
			fhsx = s1.GetValF("Logical.HotSpot",0);
			fhsy = s1.GetValF("Logical.HotSpot",1);
		} else {
			ihsx = s1.GetValI("Logical.HotSpot",0);
			ihsy = s1.GetValI("Logical.HotSpot",1);
			fhsx = ((GLfloat)(ihsx - ix1))/(ix2-ix1);
			fhsy = ((GLfloat)(ihsy - iy1))/(iy2-iy1);
		}


		pt = GetPTex(pid);
		if( 0 == pt ) {
			ERROR("Brak tekstury fizycznej o ID=\"" + pid + "\". Tekstura logiczna o ID=\"" + id + "\" nie mo¿e byæ utworzona !!!");
		} else {
			lt = new LTex();
			lt->Set(pt,ix1,iy1,ix2,iy2);
			lt->SetHotSpot( fhsx, fhsy );
			AddLTex(id,lt);
			INFO( "Dodano teksture o id=" + id );
		}

		n++;
		s1 = s.Extract("Logical["+toString(n)+"]");
	}
	INFO("Blad: " + s1.ErrorMsg());


	INFO("Koniec textur");

	return 1;
}

};	//namespace
