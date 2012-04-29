#ifndef D_LGN_DISKACS_H_D
#define D_LGN_DISKACS_H_D

void ODCZYT(unsigned char *MEM);
void CLEAR_TABLES(void);
void SDIR(astr A_S,aint K1,aint K2);
void REQUEST(astr A_S,astr NAPI_S);
void _LOAD( astr A_S, astr B_S, astr NAPI_S, aint TRYB);
void _SAVE_GAME(void);
void _LOAD_GAME(void);

#endif // D_LGN_DISKACS_H_D

