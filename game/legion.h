#ifndef D_LEGION_H_D
#define D_LEGION_H_D

#include "amos_types.h"

//const astr DATA_DIR = "Data/";
const astr DATA_DIR = "legion/";
const astr FONT_BODACIOUS = "fonts/Bodacious-Normal.ttf";
const astr FONT_GARNET = "fonts/CAROBTN_.TTF";
const astr FONT_DEFENDER = "fonts/FUNDR___.TTF";
const bool IB_INTRO = true;
const bool IB_TEST_MODE = false;

extern astr gs_language;
extern astr gs_default_language;

extern astr KAT_S;
extern aint LEWY,PRAWY;
extern aint ARMIA[40+1][10+1][30+1]
		 , WOJNA[5+1][5+1]
		 , GRACZE[4+1][3+1];
extern astr ARMIA_S[40+1][10+1]
			,IMIONA_S[4+1];
extern aint AN[4+1];
extern aflt VEKTOR_F[20+1][5+1];
extern aint PREFS[10+1];
extern aint MIASTA[50+1][20+1][6+1+1], MUR[10+1], SKLEP[20+1][21+1], STRZALY[10+1];
extern astr MIASTA_S[50+1], ZNAKI_S[30+1];
extern aflt BOARD_F[125+1],LITERY_F[100+1];
extern aint M_X, M_Y, M_LUDZIE, M_PODATEK, M_CZYJE, M_MORALE, M_MUR, M_BOB;
extern aint OX,OY,NUMER,SX,SY,MSX,MSY,FONT,FONR,FONTSZ,LOK,DZIEN,FON1,FON2,FON3;
extern aint AMIGA,WPI,IMIONA,ODLEG,WIDOCZNOSC,BUBY,BIBY,PIKIETY,POTWORY;
extern astr WPI_S;
extern aflt WPI_F;
extern aint CENTER_V,SCENERIA,LAST_GAD,KANAL,POWER,REZULTAT,GOBY,MUZYKA,KONIEC_INTRA;
extern aflt BOMBA1_F;
extern aint BOMBA3,BOMBA4,BSIBY;
extern aint RASY[20+1][7+1];
extern astr RASY_S[20+1];
extern aint BRON[120+1][11+1];
extern astr BRON_S[120+1];
extern astr BRON2_S[25+1];
extern aint GLEBA[110+1][4+1], PLAPKI[10+1][4+1];
extern aint BUDYNKI[12+1][6+1];
extern astr BUDYNKI_S[12+1], GUL_S[10+1];
extern astr ROZMOWA_S[5+1][5+1], ROZMOWA2_S[50+1], PRZYGODY_S[20+1][10+1], IM_PRZYGODY_S[3+1];
extern aint PRZYGODY[3+1][10+1], TRWA_PRZYGODA;
extern aint P_TYP, P_X, P_Y, P_TERMIN, P_KIERUNEK, P_LEVEL, P_CENA, P_NAGRODA, P_BRON, P_TEREN, P_STAREX;
extern aint BROBY;
extern aint ARM, WRG;
extern aint B_SI, B_PAN, B_SZ, B_EN, B_TYP, B_WAGA, B_PLACE, B_DOSW, B_MAG, B_CENA, B_BOB;
extern aint OKX,OKY,SPX,SPY,REAL_KONIEC,KONIEC_AKCJI,WYNIK_AKCJI,KTO_ATAKUJE,TESTING,CELOWNIK;
extern aint GAME_OVER,_MODULO,SUPERVISOR,MX_WEAPON;
extern aflt BOMBA2_F;
extern aint TEM, TX, TY, TSI, TSZ, TCELX, TCELY, TTRYB, TE, TP, TBOB, TKLAT, TAMO, TLEWA, TPRAWA, TNOGI, TGLOWA
					, TPLECAK, TKORP, TMAG, TDOSW, TRASA, TWAGA, TMAGMA;

void main_code(void);


#endif
