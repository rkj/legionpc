
#include <string>
#include <cstdio>
#include <libpng12/png.h>

extern "C" {
	#include <jpeglib.h>
}
#undef HAVE_STDLIB_H	//SDL definiuje to w ciemno, tak samo JPEGLIB i w rezultacie dostajemy ostrzezenie, czego nie lubie ;-)

#include <SDL/SDL_image.h>

#include "Pictures.h"
#include "Utils.h"

using namespace std;

namespace Gfx {

static int ii_def_hint = PICH_NONE
				 , ii_def_compression = 80
				 ;
static unsigned int iui_def_flags = PICF_NONE;


static int data_mode_size(int dm) {
	switch( dm ) {
		case PDM_GRAY:				return 1;
		case PDM_GRAY_ALPHA:	return 2;
		case PDM_RGB:					return 3;
		case PDM_RGBA:				return 4;
		case PDM_GRAY16:			return 2;
		case PDM_GRAY32:			return 4;
		default:							return 0;
	}
}


int PicWriteHint(int hint) {
	int ret = ii_def_hint;
	ii_def_hint = hint;
	return ret;
}
int PicCompressionStrength(int str) {
	int ret = ii_def_compression;
	ii_def_compression = str;
	return ret;
}
unsigned int PicWriteFlags(unsigned int flags) {
	unsigned int ret = iui_def_flags;
	iui_def_flags = flags;
	return ret;
}
static int WritePNG(const std::string& filename,unsigned char *data,int w,int h,int mode,int hint,int compress,unsigned int flags) {

	int li_ret = -1;
	FILE *fp = 0;
	png_structp png_ptr = 0;
	png_infop info_ptr = 0;
	int png_mode, pixel_skip;
	png_byte *row_pointers[h];

	  ///////////////////
	 // Inicjalizacja //
	///////////////////

	//otwieramy plik do zapisu
	fp = fopen(filename.c_str(),"wb");
	if( 0 == fp ) {
		li_ret = -1;
		goto error_ret;
	}

	//tworzymy podstawowa strukture zapisu
	png_ptr = png_create_write_struct( PNG_LIBPNG_VER_STRING
																	 , (png_voidp)0
																	 , 0
																	 , 0);
	if( 0== png_ptr ) {
		li_ret = -2;
		goto error_ret;
	}

	//tworzymy strukture informacyjna
	info_ptr = png_create_info_struct(png_ptr);
	if( 0 == info_ptr ) {
		li_ret = -3;
		goto error_ret;
	}

	//kiedy w PNG cos nie zabangla zostanie wykonane to co jest w IFie ponizej
	//(i nie jest wazne, ze wylozy sie ktoras z funkcji wolanych ponizej tego IFa)
	if( setjmp(png_jmpbuf(png_ptr)) ) {
		li_ret = -4;
		goto error_ret;
	}

	//ustawiamy kanal zapisu
	png_init_io(png_ptr, fp);


	//jezeli chcielibysmy progress bara to mozna ustawic ten callback
	//(ale nie chcemy ;-) )
	//--png_set_write_status_fn(png_ptr, write_row_callback);

	//mozna rowniez zdefiniowac filtry jakie maja zadzialac podczas kompresji
	/*
	png_set_filter(png_ptr, 0,
				 PNG_FILTER_NONE  | PNG_FILTER_VALUE_NONE |
				 PNG_FILTER_SUB   | PNG_FILTER_VALUE_SUB  |
				 PNG_FILTER_UP    | PNG_FILTER_VALUE_UP   |
				 PNG_FILTER_AVE   | PNG_FILTER_VALUE_AVE  |
				 PNG_FILTER_PAETH | PNG_FILTER_VALUE_PAETH|
				 PNG_ALL_FILTERS);
	*/

	//mozna tez pobawic sie w ustawianie poziomu kompresji ZLIB
  //--png_set_compression_level(png_ptr,Z_BEST_COMPRESSION);

	  ///////////////////////
	 // Generowanie pliku //
	///////////////////////

	switch( mode ) {
		case PDM_GRAY:				png_mode = PNG_COLOR_TYPE_GRAY; pixel_skip=1; break;
		case PDM_GRAY_ALPHA:	png_mode = PNG_COLOR_TYPE_GRAY_ALPHA; pixel_skip=2; break;
		case PDM_RGB:					png_mode = PNG_COLOR_TYPE_RGB; pixel_skip=3; break;
		case PDM_RGBA:				png_mode = PNG_COLOR_TYPE_RGB_ALPHA; pixel_skip=4; break;
		default:							li_ret = -5; goto error_ret;
	}

	//naglowek
	png_set_IHDR(png_ptr, info_ptr
							, w, h													//pic size
							, 8															//bit_depth
							, png_mode											//color_type
							, PNG_INTERLACE_NONE						//interlace_type
							, PNG_COMPRESSION_TYPE_DEFAULT	//compression_type
							, PNG_FILTER_TYPE_DEFAULT				//filter_method
							);


	//zapis danych informacyjnych
	png_write_info(png_ptr, info_ptr);

	//informujemy o sposobie zapisu i filtrowania danych
	png_set_filler(png_ptr, 0, PNG_FILLER_BEFORE);

	//zapisujemy dane
	if( 0 != (flags & PICF_VREV) ) {
		for(int y=0; y<h; ++y ) {
			row_pointers[h-1-y] = (png_byte *)(data + y*w*pixel_skip);
		}
	} else {
		for(int y=0; y<h; ++y ) {
			row_pointers[y] = (png_byte *)(data + y*w*pixel_skip);
		}
	}
	png_write_image(png_ptr, row_pointers);

	//konczymy zapis
	png_write_end(png_ptr, info_ptr);


	li_ret = 1;	//NO ERROR

error_ret:
	if( png_ptr || info_ptr ) {
		 png_destroy_write_struct(&png_ptr,&info_ptr);
	}
	if( fp ) {
		fclose(fp);
	}
	return li_ret;
}
static int WriteJPG(const std::string& filename,unsigned char *data,int w,int h,int mode,int hint,int compress,unsigned int flags) {
	int li_ret = -1;
	FILE *fp = 0;
	J_COLOR_SPACE jpg_mode;
	int pixel_skip;
	struct jpeg_compress_struct cinfo;
	struct jpeg_error_mgr jerr;
	JSAMPROW row_pointers[h];

	  ///////////////////
	 // Inicjalizacja //
	///////////////////

	//otwieramy plik do zapisu
	fp = fopen(filename.c_str(),"wb");
	if( 0 == fp ) {
		li_ret = -1;
		goto error_ret;
	}

	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_compress(&cinfo);

	jpeg_stdio_dest(&cinfo,fp);

	switch( mode ) {
		case PDM_GRAY:				jpg_mode = JCS_GRAYSCALE; pixel_skip=1; break;
		case PDM_RGB:					jpg_mode = JCS_RGB; pixel_skip=3; break;
		default:							li_ret = -5; goto error_ret;
	}
	cinfo.image_width = w; 								/* image width and height, in pixels */
	cinfo.image_height = h;
	cinfo.input_components = pixel_skip;	/* # of color components per pixel */
	cinfo.in_color_space = jpg_mode; 			/* colorspace of input image */

	jpeg_set_defaults(&cinfo);						//ustawiamy domyslne nastawy, a potem co nieco pozmieniamy

	jpeg_set_colorspace(&cinfo,jpg_mode);	//upewniamy sie, ze na wyjsciu bedzie to co chcemy

	if( ii_def_compression >= 0 ) {
		int q = 100 - ii_def_compression;
		if( q < 0 ) q = 0;
		jpeg_set_quality(&cinfo,q,true);		//true zapobiega tworzeniu malutkich w rozmiarze, ale nieczytelnych obrazkow
	}	//jezeli compresja < 0 to znaczy, ze ma byc domyslna

	//jaki algorytm DCT ?
	if( ii_def_hint & PICH_QUALITY ) {
		if( ii_def_hint & PICH_FAST ) {
			cinfo.dct_method = JDCT_ISLOW;	//dokladne, staloprzecinkowe
		} else {
			cinfo.dct_method = JDCT_FLOAT;	//najdokladniejsze
		}
	} else {
		if( ii_def_hint & PICH_FAST ) {
			cinfo.dct_method = JDCT_IFAST;	//szybko, ale niedokladnie
		} else {
			cinfo.dct_method = JDCT_ISLOW;	//dobrze i w miare szybko
		}
	}

	//jaki algorytm pakowania ?
	if( ii_def_hint & PICH_SIZE ) {
		if( ii_def_hint & PICH_FAST ) {
			cinfo.optimize_coding = false;
		} else {
			cinfo.optimize_coding = true;			//kosztem czasu (ale nie jakosci) zwieksza o kilkaprocent kompresje
		}
	} else {
		cinfo.optimize_coding = false;
	}

	  ///////////////////////
	 // Generowanie pliku //
	///////////////////////

	jpeg_start_compress(&cinfo, TRUE);


	//zapisujemy dane
	if( 0 != (flags & PICF_VREV) ) {
		for(int y=0; y<h; ++y ) {
			row_pointers[h-1-y] = (JSAMPROW)(data + y*w*pixel_skip);
		}
	} else {
		for(int y=0; y<h; ++y ) {
			row_pointers[y] = (JSAMPROW)(data + y*w*pixel_skip);
		}
	}
	jpeg_write_scanlines(&cinfo, row_pointers, h);

	jpeg_finish_compress(&cinfo);

	li_ret = 1;	//NO ERROR

error_ret:
	jpeg_destroy_compress(&cinfo);
	if( fp ) {
		fclose(fp);
	}
	return li_ret;
}

inline static void FixAlphaZeroPixel(unsigned char *tex,int ps,int sl) {
	if( 0==*(tex+3) ) {
		unsigned int r,g,b,a,sa;
		unsigned char *buf;

		buf = tex - sl - ps;
		a = (*(buf+3)) * 3;
		r = (*(buf+0)) * a;
		g = (*(buf+1)) * a;
		b = (*(buf+2)) * a;
		sa = a;

		buf = tex - sl;
		a  = (*(buf+3)) * 5;
		r += (*(buf+0)) * a;
		g += (*(buf+1)) * a;
		b += (*(buf+2)) * a;
		sa += a;

		buf = tex - sl + ps;
		a  = (*(buf+3)) * 3;
		r += (*(buf+0)) * a;
		g += (*(buf+1)) * a;
		b += (*(buf+2)) * a;
		sa += a;

		buf = tex - ps;
		a  = (*(buf+3)) * 5;
		r += (*(buf+0)) * a;
		g += (*(buf+1)) * a;
		b += (*(buf+2)) * a;
		sa += a;

		buf = tex + ps;
		a  = (*(buf+3)) * 5;
		r += (*(buf+0)) * a;
		g += (*(buf+1)) * a;
		b += (*(buf+2)) * a;
		sa += a;

		buf = tex + sl - ps;
		a  = (*(buf+3)) * 3;
		r += (*(buf+0)) * a;
		g += (*(buf+1)) * a;
		b += (*(buf+2)) * a;
		sa += a;

		buf = tex + sl;
		a  = (*(buf+3)) * 5;
		r += (*(buf+0)) * a;
		g += (*(buf+1)) * a;
		b += (*(buf+2)) * a;
		sa += a;

		buf = tex + sl + ps;
		a  = (*(buf+3)) * 3;
		r += (*(buf+0)) * a;
		g += (*(buf+1)) * a;
		b += (*(buf+2)) * a;
		sa += a;

		if( sa > 0 ) {
			buf = tex;
			*(buf+0) = r / sa;
			*(buf+1) = g / sa;
			*(buf+2) = b / sa;
		}
	}
}
inline static void FixAlphaZeroPixelGray(unsigned char *tex,int ps,int sl) {
	if( 0==*(tex+1) ) {
		unsigned int g,a,sa;
		unsigned char *buf;

		buf = tex - sl - ps;
		a = (*(buf+1)) * 3;
		g = (*(buf+0)) * a;
		sa = a;

		buf = tex - sl;
		a  = (*(buf+1)) * 5;
		g += (*(buf+0)) * a;
		sa += a;

		buf = tex - sl + ps;
		a  = (*(buf+1)) * 3;
		g += (*(buf+0)) * a;
		sa += a;

		buf = tex - ps;
		a  = (*(buf+1)) * 5;
		g += (*(buf+0)) * a;
		sa += a;

		buf = tex + ps;
		a  = (*(buf+1)) * 5;
		g += (*(buf+0)) * a;
		sa += a;

		buf = tex + sl - ps;
		a  = (*(buf+1)) * 3;
		g += (*(buf+0)) * a;
		sa += a;

		buf = tex + sl;
		a  = (*(buf+1)) * 5;
		g += (*(buf+0)) * a;
		sa += a;

		buf = tex + sl + ps;
		a  = (*(buf+1)) * 3;
		g += (*(buf+0)) * a;
		sa += a;

		if( sa > 0 ) {
			buf = tex;
			*(buf+0) = g / sa;
		}
	}
}

void Pic::_reset(void) {
	w=0; h=0; data_mode=PDM_RGBA;
	buf=0; buf_owner=false;
	priv_data=0;
}
void Pic::_destroy(void) {
	_free_buf();
}
void Pic::_free_priv(void) {
	if( 0 != priv_data ) {
		SDL_Surface *s = (SDL_Surface*)priv_data;
		delete s;
		priv_data = 0;
	}
}
void Pic::_free_buf(void) {
	if( buf_owner ) {
		delete[] buf;
		buf = 0;
	}
}
void Pic::_alloc_buf(int bw,int bh,int dm) {
	bool do_alloc=true;

	data_mode = dm;				//to ustawiamy zawsze
	_free_priv();					//jezeli obrazek byl oparty o SDL_surface to juz nie bedzie

	if( buf_owner ) {
		//jezeli jestesmy wlascicielem bufora to moze nie trzeba go alokowac na nowo
		int cs,as;
		cs = buf_w * buf_h * data_mode_size(data_mode);
		as = bw * bh * data_mode_size(dm);
		if( cs >= as ) {
			do_alloc = false;	//bufor jest wystarczajaco duzy by pomiescic nowe dane
		} else {
			_free_buf();			//bufor jest za maly, wiec go zwalniamy
		}
	}
	if( do_alloc ) {
		buf_w = bw;
		buf_h = bh;
		buf = new unsigned char[buf_w * buf_h * data_mode_size(dm)];
		buf_owner = true;
	}
}
Pic::Pic(void) {
	_reset();
}
Pic::~Pic() {
	_destroy();
}
const unsigned char* Pic::GetBuffer(void) const {
	return buf;
}
unsigned char* Pic::GetBufferWR(void) {
	return buf;
}
int Pic::GetWidth(void) const {
	return w;
}
int Pic::GetHeight(void) const {
	return h;
}
int Pic::GetDataMode(void) const {
	return data_mode;
}
int Pic::GetScanlineSize(void) const {
	return w * GetPixelSize();
}
int Pic::GetPixelSize(void) const {
	return data_mode_size(data_mode);
}
void Pic::Set(int bw,int bh,int dm) {
	_alloc_buf(bw,bh,dm);
	w = bw;
	h = bh;
}
void Pic::Set(unsigned char* b,int bw,int bh,int dm) {
	_free_priv();
	_free_buf();
	w = bw;
	h = bh;
	data_mode = dm;
	buf = b;
	buf_w = bw;
	buf_h = bh;
	buf_owner = false;
}
void Pic::Set(const Pic& src,int dm) {
	_alloc_buf(src.w,src.h,dm);
	w = src.w;
	h = src.h;
	data_mode = dm;

	//do konwersji uzyjemy specjalnej klasy (klucz: wykorzystanie wskaznikow do metod)
	class Conv {
	public:
		unsigned int r,g,b,a;
		unsigned int gray;
		unsigned char *mc_src_buf, *mc_dst_buf;
		unsigned short *ms_src_buf, *ms_dst_buf;
		unsigned int *mi_src_buf, *mi_dst_buf;
		unsigned int rmul, gmul, bmul, div, mul8to32, mul16to32;
		void (Conv::*ReadFunc)(void);		//wskaznik na metode
		void (Conv::*WriteFunc)(void);	//wskaznik na metode
		Conv(void) { rmul=2125; gmul=7154; bmul=721; div=rmul+gmul+bmul; mul8to32=0x01010101; mul16to32=0x00010001; a=0xffffffff; }
		~Conv() {}
		void ReadGray8(void)			{ gray=*(mc_src_buf++); gray*=mul8to32;  r=gray; g=gray; b=gray; }
		void ReadGray16(void)			{ gray=*(ms_src_buf++); gray*=mul16to32; r=gray; g=gray; b=gray; }
		void ReadGray32(void)			{ gray=*(mi_src_buf++);                  r=gray; g=gray; b=gray; }
		void ReadGrayAlpha(void)	    { ReadGray8(); a=*(mc_src_buf++); a*=mul8to32; }
		void ReadRGB(void)				{ r=*(mc_src_buf++); r*=mul8to32; g=*(mc_src_buf++); g*=mul8to32; b=*(mc_src_buf++);  b*=mul8to32; }
		void ReadRGBA(void)				{ ReadRGB(); a=*(mc_src_buf++); a*=mul8to32; }
		void WriteGray8(void)			{ *(mc_dst_buf++) = (unsigned char) (( (r/mul8to32)*rmul + (g/mul8to32)*gmul + (b/mul8to32)*bmul )/div); }
		void WriteGray16(void)		    { *(ms_dst_buf++) = (unsigned short)(( (r/mul16to32)*rmul + (g/mul16to32)*gmul + (b/mul16to32)*bmul )/div); }
		void WriteGray32(void)		    { *(mi_dst_buf++) = (unsigned int)  (  (r/10)*2 + (g/10)*7 + (b/10)*1 ); }
		void WriteGrayAlpha(void)	    { WriteGray8(); *(mc_dst_buf++)=(unsigned char)(a/mul8to32); }
		void WriteRGB(void)				{ *(mc_dst_buf++)=(unsigned char)(r/mul8to32); *(mc_dst_buf++)=(unsigned char)(g/mul8to32); *(mc_dst_buf++)=(unsigned char)(b/mul8to32); }
		void WriteRGBA(void)			{ WriteRGB(); *(mc_dst_buf++)=(unsigned char)(a/mul8to32); }
		void Read(void)					{ (this->*ReadFunc)(); }
		void Write(void)				{ (this->*WriteFunc)(); }
	} conv;

	//inicjujemy obiekt konwertujacy
	switch( src.data_mode ) {
		case PDM_GRAY:
			conv.ReadFunc = &Conv::ReadGray8;
			conv.a = 0xffffffff;	//alpha stale
			conv.mc_src_buf = src.buf;
			break;
		case PDM_GRAY16:
			conv.ReadFunc = &Conv::ReadGray16;
			conv.a = 0xffffffff;	//alpha stale
			conv.ms_src_buf = (unsigned short*)src.buf;
			break;
		case PDM_GRAY32:
			conv.ReadFunc = &Conv::ReadGray32;
			conv.a = 0xffffffff;	//alpha stale
			conv.mi_src_buf = (unsigned int*)src.buf;
			break;
		case PDM_GRAY_ALPHA:
			conv.ReadFunc = &Conv::ReadGrayAlpha;
			conv.mc_src_buf = src.buf;
			break;
		case PDM_RGB:
			conv.ReadFunc = &Conv::ReadRGB;
			conv.a = 0xffffffff;	//alpha stale
			conv.mc_src_buf = src.buf;
			break;
		case PDM_RGBA:
			conv.ReadFunc = &Conv::ReadRGBA;
			conv.mc_src_buf = src.buf;
			break;
		default:
			ERROR("Nieobs³ugiwany zród³owy tryb danych rysunku");
			return;
	}

	switch( this->data_mode ) {
		case PDM_GRAY:
			conv.WriteFunc = &Conv::WriteGray8;
			conv.mc_dst_buf = this->buf;
			break;
		case PDM_GRAY16:
			conv.WriteFunc = &Conv::WriteGray16;
			conv.ms_dst_buf = (unsigned short*)this->buf;
			break;
		case PDM_GRAY32:
			conv.WriteFunc = &Conv::WriteGray32;
			conv.mi_dst_buf = (unsigned int*)this->buf;
			break;
		case PDM_GRAY_ALPHA:
			conv.WriteFunc = &Conv::WriteGrayAlpha;
			conv.mc_dst_buf = this->buf;
			break;
		case PDM_RGB:
			conv.WriteFunc = &Conv::WriteRGB;
			conv.mc_dst_buf = this->buf;
			break;
		case PDM_RGBA:
			conv.WriteFunc = &Conv::WriteRGBA;
			conv.mc_dst_buf = this->buf;
			break;
		default:
			ERROR("Nieobs³ugiwany docelowy tryb danych rysunku");
			return;
	}

	//konwertujemy
	for( int i=0, e=w*h; i<e; ++i ) {
		conv.Read();
		conv.Write();
	}

}
Pic* Pic::Convert(int dm) const {
	Pic *p = new Pic();
	p->Set(*this,dm);
	return p;
}
int Pic::Load(const std::string& filename) {

	//----------------
	//ladujemy obrazek
	SDL_Surface *image, *rgba_img;
	image = (SDL_Surface *) IMG_Load(filename.c_str());
	if( 0 == image ) {
		ERROR("Error while loading image file >"+filename+"<:");
		return -1;
	}

	//SDL_PixelFormat *pixf = image->format;

	//---------------------------------------------
	//konwersja wczytanego obrazka do bytemapy RGBA

	Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000; gmask = 0x00ff0000; bmask = 0x0000ff00;	amask = 0x000000ff;
#else
	rmask = 0x000000ff;	gmask = 0x0000ff00;	bmask = 0x00ff0000;	amask = 0xff000000;
#endif
	rgba_img = SDL_CreateRGBSurface(SDL_SWSURFACE, image->w, image->h, 32, rmask, gmask, bmask, amask);

	//na rysunku docelowym wszystko jest przezroczyste :-)
	Uint32 dkey;
	dkey = SDL_MapRGBA(rgba_img->format,	0, 0, 0, 255);
	SDL_FillRect(rgba_img, NULL, dkey);

	//na rysunku zrodlowym ustawiamy kolor przezroczysty
	SDL_SetAlpha(image,0,255);
	SDL_SetAlpha(rgba_img,0,255);

	//kopiujemy zrodlo do celu (przezroczystosc bedzie uwzgledniona)
	SDL_BlitSurface(image, 0, rgba_img, 0);

	//zwalniamy oryginalny obrazek
	SDL_FreeSurface(image);

	image = rgba_img;

	//------------------------------------------
	//ustawienie atrybutow obiektu Pic
	w = image->w;
	h = image->h;
	data_mode = PDM_RGBA;
	_free_buf();
	buf = (unsigned char*)image->pixels;
	buf_owner = false;	//nie alokowalismy sami bufora
	buf_w = image->w;
	buf_h = image->h;
	priv_data = image;

	return 1;
}
int Pic::SavePNG(const std::string& filename) const {
	return WritePNG(filename,buf,w,h,data_mode,ii_def_hint,ii_def_compression,iui_def_flags);
}
int Pic::SaveJPG(const std::string& filename) const {
	return WriteJPG(filename,buf,w,h,data_mode,ii_def_hint,ii_def_compression,iui_def_flags);
}
void Pic::FixAlphaZero(void) {
	int x,y,sl=GetScanlineSize(),ps=GetPixelSize();
	if( PDM_RGBA == data_mode ) {
		for(y=1;y<h-1;++y) {
			for(x=1;x<w-1;++x) {
				FixAlphaZeroPixel(buf+x*ps+y*sl,ps,sl);
			}
		}
	} else if( PDM_GRAY_ALPHA == data_mode ) {
		for(y=1;y<h-1;++y) {
			for(x=1;x<w-1;++x) {
				FixAlphaZeroPixelGray(buf+x*ps+y*sl,ps,sl);
			}
		}
	}
	return;
}
string Pic::Dump(void) const {
	string ret = "";
	ret += "Pic: w=" + toString(w) + " h=" + toString(h) + " data_mode=" + toString(data_mode);
	ret += " buf=" + toString((int)buf,"%8.8x") + " buf_owner=" + (buf_owner ? "TRUE" : "FALSE");
	ret += " priv_data=" + toString((int)priv_data,"%8.8x");
	return ret;
}

};
