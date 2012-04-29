#ifndef D_LGN_UTIL_H_D
#define D_LGN_UTIL_H_D

#include	"amos_types.h"

extern void (*rysuj_ekran_ptr)(void);	//wskaznik na funkcje, ktora rysuje mape,level,etc.
void rysuj(void);


void gad_back(float wsp);
void gad_back_sklep(float wsp);
void gad_light(float wsp);
void gad_dark(float wsp);
void gad_shadow(float wsp);
void gad_text(float wsp);
void gad_forsa(float wsp);
void GADGET(aint X,aint Y,aint SZER,aint WYS,astr TX_S,aint K1,aint K2,aint K3,aint K4,aint STREFA);

void SET_BACKGROUND(aflt r,aflt g,aflt b,aflt a);
void SET_FOREGROUND(aflt r,aflt g,aflt b,aflt a);
void WPISZ_PC(aint X,aint Y,aint W,aint H,aint ILE,astr &REF_TXT_S,aint RYSUJ);
void WPISZ_OLD(aint X,aint Y,aint K1,aint K2,aint ILE,aint RYSUJ);

void USTAW_FONT( astr FONTNAME_S, astr FILENAME_S, aint WIEL, aint ANTIA);
void _GET_XY(aint TRYB,aint X1,aint Y1);

void OKNO(aint OKX,aint OKY,aint SZER,aint WYS);
void ZOKNO(void);
void WJAZD(aint XS,aint YS,aint X1,aint Y1,aint SZER,aint WYS,aint _WAIT);

void _WAIT(aint ile);
void WAIT_NO_MOUSE(void);
void BLAD(void);
void BLAD2(void);
void BUSY_ANIM(void);
void MESSAGE(aint A,astr A_S,aint P,aint M);
void MESSAGE2(aint A,astr A_S,aint B,aint M,aint WLOT);

void OUTLINE(aint X,aint Y,astr A_S,aint K1,aint K2);
void _M_FADE(aint SPEED);
void _TRACK_FADE(aint SPEED);
void FX(aint SAM);
void CZEKAJ(void);
void SPEED_CHECK(void);
void CHECK(aint A);

void SKROL(aint A);
void KLAWSKROL(aint KLAW);
void ODL(aint X1,aint Y1,aint X2,aint Y2);
void CENTER(aint X,aint Y,aint FLOOD);
void ROB_IMIE(void);
void NAPISZ(aint X,aint Y,aint SZER,aint WYS,astr A_S,aint P,aint K1,aint K2);


#endif // D_LGN_UTIL_H_D

