#ifndef D_PICTURES_H_D
#define D_PICTURES_H_D

#include <string>

namespace Gfx {

enum PicDataModes {
	PDM_GRAY = 1
, PDM_GRAY_ALPHA = 2
, PDM_RGB = 3
, PDM_RGBA = 4
, PDM_GRAY8	= PDM_GRAY
, PDM_GRAY16 = 5
, PDM_GRAY32 = 6
};

enum PicHints {
	PICH_NONE = 0			//no hint at all
,	PICH_FAST = 1			//fast write
, PICH_SIZE = 2			//small size
, PICH_QUALITY = 4	//best quality
};

enum PicFlags {
	PICF_NONE = 0
, PICF_VREV = 1
};

class Pic {
protected:
	int w,h;
	int data_mode;
	unsigned char *buf;
	int buf_w, buf_h;
	bool buf_owner;
	void *priv_data;
	void _reset(void);
	void _destroy(void);
	void _free_priv(void);
	void _free_buf(void);
	void _alloc_buf(int bw,int bh,int dm);
public:
	Pic(void);
	~Pic();
	const unsigned char* GetBuffer(void) const;
	unsigned char* GetBufferWR(void);
	int GetWidth(void) const;
	int GetHeight(void) const;
	int GetDataMode(void) const;
	int GetScanlineSize(void) const;
	int GetPixelSize(void) const;
	void Set(int w,int h,int dm=PDM_RGBA);
	void Set(unsigned char* b,int w,int h,int dm=PDM_RGBA);
	void Set(const Pic& src,int dm=PDM_RGBA);
	Pic* Convert(int dm=PDM_RGBA) const;
	int Load(const std::string& filename);
	int SavePNG(const std::string& filename) const;
	int SaveJPG(const std::string& filename) const;
	void FixAlphaZero(void);
	std::string Dump(void) const;
};

int PicWriteHint(int hint);
int PicCompressionStrength(int str);
unsigned int PicWriteFlags(unsigned int flags);

};

#endif
