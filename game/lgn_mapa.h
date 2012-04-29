#ifndef D_LGN_MAPA_H_D
#define D_LGN_MAPA_H_D

void SETUP0(void);
void MAIN(void);
void rysuj_mape(void);

void B_CLEAR(aint NR);
void B_DRAW(aint NR,aint X,aint Y,aint O);
void B_UPDATE(aint NR);
void B_OFF(aint NR);

void MAPA_AKCJA(void);
void MA_RUCH(aint A,aint TRYB);
void MA_POLOWANIE(aint A);
void MA_OBOZ(aint A);
void MA_PRZYGODA(aint A,aint NR);
void MA_WYPADEK(aint A,aint TYP);
void MA_WYDAJ_ROZKAZ(aint PL,aint A);
void PLAGA(aint MIASTO,aint PLAGA);

void VISUAL_OBJECTS(void);

void SZPIEGUJ(aint NR,aint CO);

void TEREN(aint X,aint Y);

void BITWA(aint A,aint B,aint X1,aint Y1,aint T1,aint X2,aint Y2,aint T2,aint SCENERIA,aint WIES);
void BITWA_SYMULOWANA(aint A,aint B);
void USTAW_WOJSKO(aint A,aint XW,aint YW,aint TYP);

void OBLICZ_POWER(aint PL);


#endif // D_LGN_MAPA_H_D

