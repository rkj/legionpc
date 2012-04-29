#ifndef D_AMOSMUSIC_H_D
#define D_AMOSMUSIC_H_D

#include <SDL/SDL_mixer.h>

unsigned char* convert_abk2mod(unsigned char *abk,long len,long &mod_len);

Mix_Chunk* convert_sam2mixchunk(unsigned char *sam_buf,long sam_len,int freq);

#endif
