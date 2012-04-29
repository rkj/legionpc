#ifndef D_LGN_AKCJA_H_D
#define D_LGN_AKCJA_H_D

void SETUP(astr A_S,astr B_S,astr C_S);
void MAIN_ACTION(void);
void AKCJA(void);

void _WYBOR_SHOW_INFO(aint BR);

void WYBOR(aint WT);
void ROZKAZ(void);
void SELECT(aint A,aint NR);
void PRZELICZ(aint I,aint ZNAK);
void WAGA(aint A,aint NR);
void SEKTOR(aint X,aint U);

void GADUP(aint GN);
void GADDOWN(aint GN);
void MARKERS(void);
void MARKERS_OFF(void);
void RUCH(void);

void A_RUCH(aint A,aint I);
void A_ATAK(aint A,aint I);
void A_STRZAL(aint A,aint I);
void A_CZAR(aint A,aint I);
void A_LOT(aint A,aint I,aint TRYB);
void A_ROZMOWA(aint A,aint I);
void PLAPKA(aint NR,aint A,aint I,aint X,aint Y);

void _ATAK(aint TYP);
void CZARY(aint BL,aint BP);
void STRZAL(void);
void ZABIJ(aint A,aint NR,aint CICHO);
void GADKA(aint NR,aint B);
void WYKRESY(aint A,aint NR);
void BRON_INFO(aint STREFA);

void NOWA_POSTAC(aint A,aint NR,aint RASA);
void POTWOR(aint A, astr A_S, aint ILU, aint RASA);

void WYDAJ_ROZKAZ(aint NR);

#endif // D_LGN_AKCJA_H_D

