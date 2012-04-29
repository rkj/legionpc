
#include "Amos.h"

#include "legion.h"
#include "lgn_diskacs.h"
#include "lgn_util.h"
#include "utl_locale.h"

void _LOAD( astr A_S, astr B_S, astr NAPI_S, aint TRYB) {
	//	Procedure _LOAD[A$,B$,NAPI$,TRYB]
	//	   If Exist(A$)
	//	      Goto ODCZYT
	//	   Else
	//	      A$=B$
	//	      REQUEST[A$,NAPI$]
	//	   End If
	if( Exists(A_S) ) {
		goto ODCZYT;
	} else {
		A_S = B_S;
		//requesta nie robimy
	}

	ODCZYT:	//	   ODCZYT:
					//	   On Error Proc BLAD
					//	   If TRYB=0 : Load A$ : End If
					//	   If TRYB=1 : Load A$,1 : End If
					//	   If TRYB=2 : Load Iff A$ : End If
					//	   If TRYB=3 : Load Iff A$,0 : End If
					//	   If TRYB=4 : Load Iff A$,1 : End If
					//	   If TRYB=5 : Load Iff A$,2 : End If
					//	   If TRYB=6 : Track Load A$,3 : End If
					//	   If TRYB=7 : Load A$,3 : End If
					//	   If TRYB=8 : Load A$,4 : End If
					//	   If TRYB=9 : Load A$,5 : End If
					//
	int ret;
	switch( TRYB ) {
		case 0:	ret = LoadAbkSp(A_S,-1); break;
		case 1: ret = LoadAbkSp(A_S,1); break;
		case 2:	ret = LoadIff(A_S,-1); break;
		case 3:	ret = LoadIff(A_S,0); break;
		case 4:	ret = LoadIff(A_S,1); break;
		case 5:	ret = LoadIff(A_S,2); break;
		case 6:	ret = LoadTrack(A_S,3); break;
		case 7: ret = LoadAbkMus(A_S,3); break;
		case 8: ret = LoadAbkSnd(A_S,4); break;
		case 9: ret = LoadAbkSnd(A_S,5); break;
		default:	ret=-1;
	}
	if( ret < 0 ) {
		ERROR("B³¹d ³adowania pliku danych: " + A_S + ": " + toString(ret));
		BLAD();
	} else {
		INFO("Pomyœlnie za³adowano plik danych: " + A_S);
	}
	//	End Proc
}
void _WRITE_STRING(unsigned char* &MEM,astr DAT_S) {					//	   WRITE_STRING:
	aint DLUG=0;
	DLUG=Len(DAT_S);																						//	   DLUG=Len(DAT$)
	Poke(MEM,DLUG); MEM++;																			//	   Poke MEM,DLUG : Inc MEM
	Poke_S(MEM,DAT_S);																					//	   Poke$ MEM,DAT$
	MEM+=DLUG;																									//	   Add MEM,DLUG
	return;																											//	   Return
}
void _ZAPIS(astr NAME_S,aint NSAVE) {
																															//	   ZAPIS:
	aint I=0, J=0, K=0, DAT=0;
	astr DAT_S="";

	BUSY_ANIM();																								//	   BUSY_ANIM
	unsigned char bank[60000], *MEM;														//	   Reserve As Work 10,60000
	for(int i=0; i<60000; ++i ) {
		bank[i]=0;
	}

	Poke_S(bank,NAME_S);																				//	   Poke$ Start(10),NAME$
	MEM=bank+20;																								//	   MEM=Start(10)+20
																															//	   'armia(40,10,30)
	for( I=0; I<=40; ++I ) {																		//	   For I=0 To 40
		for( J=0; J<=10; ++J ) {																	//	      For J=0 To 10
			for( K=0; K<=30; ++K ) {																//	         For K=0 To 30
				DAT=ARMIA[I][J][K];																		//	            DAT=ARMIA(I,J,K)
				Doke(MEM,DAT);																				//	            Doke MEM,DAT
				MEM+=2;																								//	            Add MEM,2
			}																												//	         Next K
		}																													//	      Next J
	}																														//	   Next I
																															//	   'wojna(5,5)
	for( I=0; I<=5; ++I ) {																			//	   For I=0 To 5
		for( J=0; J<=5; ++J ) {																		//	      For J=0 To 5
			DAT=WOJNA[I][J];																				//	         DAT=WOJNA(I,J)
			Poke(MEM,DAT);																					//	         Poke MEM,DAT
			MEM++;																									//	         Inc MEM
		}																													//	      Next
	}																														//	   Next
																															//	   'gracze(4,3)
	for( I=0; I<=4; ++I ) {																			//	   For I=0 To 4
		for( J=0; J<=3; ++J ) {																		//	      For J=0 To 3
			DAT=GRACZE[I][J];																				//	         DAT=GRACZE(I,J)
			Loke(MEM,DAT);																					//	         Loke MEM,DAT
			MEM+=4;																									//	         Add MEM,4
		}																													//	      Next
	}																														//	   Next
																															//	   'armia$(40,10)
	for( I=0; I<=40; ++I ) {																		//	   For I=0 To 40
		for( J=0; J<=10; ++J ) {																	//	      For J=0 To 10
			DAT_S=ARMIA_S[I][J];																		//	         DAT$=ARMIA$(I,J)
			_WRITE_STRING(MEM,DAT_S);																//	         Gosub WRITE_STRING
		}																													//	      Next
	}																														//	   Next
																															//	   'imiona$(4)
	for( I=0; I<=4; ++I ) {																			//	   For I=0 To 4
		DAT_S=IMIONA_S[I];																				//	      DAT$=IMIONA$(I)
		_WRITE_STRING(MEM,DAT_S);																	//	      Gosub WRITE_STRING
	}																														//	   Next
																															//	   'prefs(10)
	for( I=0; I<=10; ++I ) {																		//	   For I=0 To 10
		DAT=PREFS[I];																							//	      DAT=PREFS(I)
		Poke(MEM,DAT);																						//	      Poke MEM,DAT
		MEM++;																										//	      Inc MEM
	}																														//	   Next
																															//	   'miasta(50,20,6)
	for( I=0; I<=50; ++I ) {																		//	   For I=0 To 50
		for( J=0; J<=20; ++J ) {																	//	      For J=0 To 20
			for( K=0; K<=6; ++K ) {																	//	         For K=0 To 6
				DAT=MIASTA[I][J][K];																	//	            DAT=MIASTA(I,J,K)
				Doke(MEM,DAT);																				//	            Doke MEM,DAT
				MEM+=2;																								//	            Add MEM,2
			}																												//	         Next K
		}																													//	      Next J
	}																														//	   Next I
																															//	   'miasta$(50)
	for( I=0; I<=50; ++I ) {																		//	   For I=0 To 50
		DAT_S=MIASTA_S[I];																				//	      DAT$=MIASTA$(I)
		_WRITE_STRING(MEM,DAT_S);																	//	      Gosub WRITE_STRING
	}																														//	   Next
	Doke(MEM,DZIEN); MEM+=2;																		//	   Doke MEM,DZIEN : Add MEM,2
	Doke(MEM,POWER); MEM+=2;																		//	   Doke MEM,POWER : Add MEM,2
																															//	   'przygody(3,10)
	for( I=0; I<=3; ++I ) {																			//	   For I=0 To 3
		for( J=0; J<=10; ++J ) {																	//	      For J=0 To 10
			DAT=PRZYGODY[I][J];																			//	         DAT=PRZYGODY(I,J)
			Doke(MEM,DAT);																					//	         Doke MEM,DAT
			MEM+=2;																									//	         Add MEM,2
		}																													//	      Next J
	}																														//	   Next I
																															//	   'im_przygody$(3)
	for( I=0; I<=3; ++I ) {																			//	   For I=0 To 3
		DAT_S=IM_PRZYGODY_S[I];																		//	      DAT$=IM_PRZYGODY$(I)
		_WRITE_STRING(MEM,DAT_S);																	//	      Gosub WRITE_STRING
	}																														//	   Next I
																															//
	ChangeMouse(42);																						//	   Change Mouse 42
	AmalOnOff(-1,false);																				//	   Amal Off
																															//	   Show
																															//	   On Error Proc BLAD2
																															//	   Resume Label SKIP
																															//	   If Exist(KAT$+"archiwum")
																															//	      Bsave KAT$+"archiwum/zapis"+Str$(NSAVE),Start(10) To MEM
	FILE *fout=fopen((KAT_S+"archiwum/zapis"+Str_S(NSAVE)).c_str(),"wb");
	if( fout!=0 ) {
		fwrite(bank,1,MEM-bank,fout);
		fclose(fout);																							//	   Else
	}																														//	      REQUEST["archiwum:","Archiwum"]
																															//	      Bsave "archiwum:zapis"+Str$(NSAVE),Start(10) To MEM
																															//	   End If
																															//	   SKIP:
																															//	   Erase 10
	ChangeMouse(5);																							//	   Change Mouse 5
	SpriteOnOff(0,false);
	return;																											//	   Return
																															//																															//
}

astr _sdir_get_file_name(aint I) {
	//FILE *fin=0;
	astr NAME_S="", PAT_S="";

	PAT_S=KAT_S+"archiwum/";											//	      PAT$=KAT$+"archiwum/"
	if( ! DirExists(PAT_S) ) {
		PAT_S="./";
	}

	if( Exists(PAT_S+"zapis"+Str_S(I+1)) ) {		//	      If Exist(PAT$+"zapis"+Str$(I+1))
		FILE *fin=fopen((PAT_S+"zapis"+Str_S(I+1)).c_str(),"rb");//	         Open In 1,PAT$+"zapis"+Str$(I+1)
		if( 0!=fin ) {
			char buf[21];														//	         NAME$=Input$(1,20)
			fread(buf,1,20,fin);
			buf[20]=0;
			NAME_S=buf;
																							//	         Close 1
			fclose(fin);
		}
	} else {																		//	      Else
		NAME_S=GS("005");													//	         NAME$="Empty Slot"
	}																						//	      End If

	return NAME_S;
}

void (*_rysuj_tlo_savegame)(void) = 0;
void _rysuj_savegame(void) {
	if( 0!=_rysuj_tlo_savegame ) _rysuj_tlo_savegame();
	SDIR(GS("224"),21,20);
}

void _SAVE_GAME(void) {
																															//	Procedure _SAVE_GAME
	aint STREFA=0, NSAVE=0, KONIEC=0;
	astr NAME_S="";


	rysuj();
	SDIR(GS("224"),21,20);																			//	   SDIR["Archives - Save Game",21,20]
	WaitVbl();
	do {																												//	   Repeat
		ProcessEvents();
		if( MouseClick()==1 ) {																		//	      If Mouse Click=1
			STREFA=MouseZone();																			//	         STREFA=Mouse Zone
			if( STREFA>0 && STREFA<6 ) {														//	         If STREFA>0 and STREFA<6
				NSAVE=STREFA;																					//	            NSAVE=STREFA

				//WPISZ(OKX+14,OKY+38+((STREFA-1)*20),31,6,20,0);					//	            WPISZ[OKX+14,OKY+38+((STREFA-1)*20),31,6,20]

				NAME_S=_sdir_get_file_name(STREFA-1);
				SET_BACKGROUND(119.0f/255.0f,102.0f/255.0f,85.0f/255.0f,1.0f);
				SET_FOREGROUND(255.0f/255.0f,255.0f/255.0f,255.0f/255.0f,1.0f);
				_rysuj_tlo_savegame = rysuj_ekran_ptr;
				rysuj_ekran_ptr = _rysuj_savegame;
				WPISZ_PC(OKX+16,OKY+39+((STREFA-1)*20)-TextBase(),100,10,20,NAME_S,3);
				rysuj_ekran_ptr = _rysuj_tlo_savegame;

				NAME_S=WPI_S;																					//	            NAME$=WPI$
				if( NAME_S=="" ) NAME_S="Zapis "+Str_S(STREFA);				//	            If NAME$="" : NAME$="Zapis "+Str$(STREFA) : End If
				_ZAPIS(NAME_S,NSAVE);																	//	            Gosub ZAPIS

				rysuj(); SDIR(GS("224"),21,20);	WaitVbl();
			}																												//	         End If
			if( STREFA==6 ) {																				//	         If STREFA=6
				KONIEC=-1;																						//	            KONIEC=True
			}																												//	         End If
																															//
		}																													//	      End If
																															//
	} while( KONIEC==0 );																				//	   Until KONIEC
	ZOKNO();																										//	   ZOKNO
																															//	   Goto OVER
																															//
																															//	   OVER:
																															//	End Proc
}
void _LOAD_GAME_ODCZYT(astr PAT_S,aint NSAVE) {
																														//	   ODCZYT:
	unsigned char bank[60000], *MEM;													//	   Reserve As Work 10,60000
	MEM=bank+20;																							//	   MEM=Start(10)+20
	ChangeMouse(42);																					//	   Change Mouse 42
	FILE *fin=fopen((PAT_S+"zapis"+Str_S(NSAVE)).c_str(),"rb");
	if( fin!=0 ) {
		fread(bank,1,60000,fin);
		fclose(fin);
	} else {
		return;
	}
																														//	   If Exist(KAT$+"archiwum/zapis"+Str$(NSAVE))
																														//	      Bload KAT$+"archiwum/zapis"+Str$(NSAVE),Start(10)
																														//	   Else
																														//	      REQUEST["archiwum:zapis"+Str$(NSAVE),"Archiwum"]
																														//	      Bload "archiwum:zapis"+Str$(NSAVE),Start(10)
																														//	   End If
	BUSY_ANIM();																							//	   BUSY_ANIM
	ODCZYT(MEM);																							//	   ODCZYT[MEM]
	AmalOnOff(-1,false);																			//	   Amal Off
																														//	   Show
																														//	   Return
}
void _LOAD_GAME(void) {
																															//	Procedure _LOAD_GAME
	aint STREFA=0, NSAVE=0, KONIEC=0, JEST=0;
	astr PAT_S="";

	rysuj();
	SDIR(GS("225"),17,16);													//	   SDIR["Archives - Load Game",17,16]
	WaitVbl();
	PAT_S=Param_S;																							//	   PAT$=Param$
	do {																												//	   Repeat
		ProcessEvents();
		if( MouseClick()==1 ) {																		//	      If Mouse Click=1
			STREFA=MouseZone();																			//	         STREFA=Mouse Zone
			if( STREFA>0 && STREFA<6 && Exists(PAT_S+"zapis"+Str_S(STREFA)) ) {//	         If STREFA>0 and STREFA<6 and Exist(PAT$+"zapis"+Str$(STREFA))
				NSAVE=STREFA;																					//	            NSAVE=STREFA
				KONIEC=-1;																						//	            KONIEC=True
				ZOKNO();																							//	            ZOKNO
				JEST=-1;																							//	            JEST=True
				_LOAD_GAME_ODCZYT(PAT_S,NSAVE);												//	            Gosub ODCZYT
			}																												//	         End If
			if( STREFA==6 ) {																				//	         If STREFA=6
				ZOKNO();																							//	            ZOKNO
				KONIEC=-1;																						//	            KONIEC=True
			}																												//	         End If
		}																													//	      End If
	} while( KONIEC==0 );																				//	   Until KONIEC
																															//	   Goto OVER
																															//	   OVER:
																															//	End Proc[JEST]
	Param = JEST;
}
void _READ_STRING(unsigned char* &MEM) {
	aint DLUG=0;
	astr DAT_S="";

	DLUG=Peek(MEM); MEM++;															//	   DLUG=Peek(MEM) : Inc MEM
	DAT_S=Peek_S(MEM,DLUG);															//	   DAT$=Peek$(MEM,DLUG)
	MEM+=DLUG;																					//	   Add MEM,DLUG
																											//	   Return
	Param_S=DAT_S;																			//
}
void ODCZYT(unsigned char *MEM) {
																											//	Procedure ODCZYT[MEM]
	aint I=0, J=0, K=0, DAT=0;
																											//	   'armia(40,10,30)
	for( I=0; I<=40; ++I ) {														//	   For I=0 To 40
		for( J=0; J<=10; ++J ) {													//	      For J=0 To 10
			for( K=0; K<=30; ++K ) {												//	         For K=0 To 30
				DAT=Deek(MEM);																//	            DAT=Deek(MEM)
				ARMIA[I][J][K]=DAT;														//	            ARMIA(I,J,K)=DAT
				MEM+=2;																				//	            Add MEM,2
			}																								//	         Next K
		}																									//	      Next J
	}																										//	   Next I
																											//	   'wojna(5,5)
	for( I=0; I<=5; ++I ) {															//	   For I=0 To 5
		for( J=0; J<=5; ++J ) {														//	      For J=0 To 5
			DAT=Peek(MEM);																	//	         DAT=Peek(MEM)
			WOJNA[I][J]=DAT;																//	         WOJNA(I,J)=DAT
			MEM++;																					//	         Inc MEM
		}																									//	      Next
	}																										//	   Next
																											//	   'gracze(4,3)
	for( I=0; I<=4; ++I ) {															//	   For I=0 To 4
		for( J=0; J<=3; ++J ) {														//	      For J=0 To 3
			DAT=Leek(MEM);																	//	         DAT=Leek(MEM)
			GRACZE[I][J]=DAT;																//	         GRACZE(I,J)=DAT
			MEM+=4;																					//	         Add MEM,4
		}																									//	      Next
	}																										//	   Next
																											//	   'armia$(40,10)
	for( I=0; I<=40; ++I ) {														//	   For I=0 To 40
		for( J=0; J<=10; ++J ) {													//	      For J=0 To 10
			_READ_STRING(MEM);															//	         Gosub _READ_STRING
			ARMIA_S[I][J]=Param_S;													//	         ARMIA$(I,J)=DAT$
		}																									//	      Next
	}																										//	   Next
																											//	   'imiona$(4)
	for( I=0; I<=4; ++I ) {															//	   For I=0 To 4
		_READ_STRING(MEM);																//	      Gosub _READ_STRING
		IMIONA_S[I]=Param_S;															//	      IMIONA$(I)=DAT$
	}																										//	   Next
																											//	   'prefs(10)
	for( I=0; I<=10; ++I ) {														//	   For I=0 To 10
		DAT=Peek(MEM);																		//	      DAT=Peek(MEM)
		PREFS[I]=DAT;																			//	      PREFS(I)=DAT
		MEM++;																						//	      Inc MEM
	}																										//	   Next
																											//	   'miasta(50,20,6)
	for( I=0; I<=50; ++I ) {														//	   For I=0 To 50
		for( J=0; J<=20; ++J ) {													//	      For J=0 To 20
			for( K=0; K<=6; ++K ) {													//	         For K=0 To 6
				DAT=Deek(MEM);																//	            DAT=Deek(MEM)
				MIASTA[I][J][K]=DAT;													//	            MIASTA(I,J,K)=DAT
				MEM+=2;																				//	            Add MEM,2
			}																								//	         Next K
		}																									//	      Next J
	}																										//	   Next I
																											//	   'miasta$(50)
	for( I=0; I<=50; ++I ) {														//	   For I=0 To 50
		_READ_STRING(MEM);																//	      Gosub _READ_STRING
		MIASTA_S[I]=Param_S;															//	      MIASTA$(I)=DAT$
	}																										//	   Next
	DZIEN=Deek(MEM); MEM+=2;														//	   DZIEN=Deek(MEM) : Add MEM,2
	POWER=Deek(MEM); MEM+=2;														//	   POWER=Deek(MEM) : Add MEM,2
																											//	   'przygody(3,10)
	for( I=0; I<=3; ++I ) {															//	   For I=0 To 3
		for( J=0; J<=10; ++J ) {													//	      For J=0 To 10
			DAT=Deek(MEM);																	//	         DAT=Deek(MEM)
			PRZYGODY[I][J]=DAT;															//	         PRZYGODY(I,J)=DAT
			MEM+=2;																					//	         Add MEM,2
		}																									//	      Next J
	}																										//	   Next I
																											//	   'im_przygody$(3)
	for( I=0; I<=3; ++I ) {															//	   For I=0 To 3
		_READ_STRING(MEM);																//	      Gosub _READ_STRING
		IM_PRZYGODY_S[I]=Param_S;													//	      IM_PRZYGODY$(I)=DAT$
	}																										//	   Next I
	;																										//	   Erase 10
																											//
																											//	   Goto OVER
																											//
																											//	   OVER:
																											//	End Proc
}
void CLEAR_TABLES(void) {
																	//	Procedure CLEAR_TABLES
	aint I=0, J=0, K=0;
																	//	   'armia(40,10,30)
	for(I=0;I<=40;++I) {						//	   For I=0 To 40
		for(J=0;J<=10;++J) {					//	      For J=0 To 10
			for(K=0;K<=30;++K) {				//	         For K=0 To 30
				ARMIA[I][J][K]=0;					//	            ARMIA(I,J,K)=0
			}														//	         Next K
		}															//	      Next J
	}																//	   Next I
																	//	   'wojna(5,5)
	for(I=0;I<=5;++I) {							//	   For I=0 To 5
		for(J=0;J<=5;++J) {						//	      For J=0 To 5
			WOJNA[I][J]=0;							//	         WOJNA(I,J)=0
		}															//	      Next
	}																//	   Next
																	//	   'gracze(4,3)
	for(I=0;I<=4;++I) {							//	   For I=0 To 4
		for(J=0;J<=3;++J) {						//	      For J=0 To 3
			GRACZE[I][J]=0;							//	         GRACZE(I,J)=0
		}															//	      Next
	}																//	   Next
																	//	   'armia$(40,10)
	for(I=0;I<=40;++I) {						//	   For I=0 To 40
		for(J=0;J<=10;++J) {					//	      For J=0 To 10
			ARMIA_S[I][J]="";						//	         ARMIA$(I,J)=""
		}															//	      Next
	}																//	   Next
																	//	   'imiona$(4)
	for(I=0;I<=4;++I) {							//	   For I=0 To 4
		IMIONA_S[I]="";								//	      IMIONA$(I)=""
	}																//	   Next
																	//	   'prefs(10)
	for(I=0;I<=10;++I) {						//	   For I=0 To 10
		PREFS[I]=0;										//	      PREFS(I)=0
	}																//	   Next
																	//	   'miasta(50,20,6)
	for(I=0;I<=50;++I) {						//	   For I=0 To 50
		for(J=0;J<=20;++J) {					//	      For J=0 To 20
			for(K=0;K<=6;++K) {					//	         For K=0 To 6
				MIASTA[I][J][K]=0;				//	            MIASTA(I,J,K)=0
			}														//	         Next K
		}															//	      Next J
	}																//	   Next I
																	//	   'miasta$(50)
	for(I=0;I<=50;++I) {						//	   For I=0 To 50
		MIASTA_S[I]="";								//	      MIASTA$(I)=""
	}																//	   Next
																	//	   'przygody(3,10)
	for(I=0;I<=3;++I) {							//	   For I=0 To 3
		for(J=0;J<=10;++J) {					//	      For J=0 To 10
			PRZYGODY[I][J]=0;						//	         PRZYGODY(I,J)=0
		}															//	      Next J
	}																//	   Next I
																	//	   'im_przygody$(3)
	for(I=0;I<=3;++I) {							//	   For I=0 To 3
		IM_PRZYGODY_S[I]="";					//	      IM_PRZYGODY$(I)=""
	}																//	   Next I
																	//
																	//	   OVER:
																	//	End Proc
}
void SDIR(astr A_S,aint K1,aint K2) {
																								//	Procedure SDIR[A$,K1,K2]
	aint I;
	astr PAT_S="", NAME_S="";
	OKNO(100,60,140,160);													//	   OKNO[100,60,140,160]
	GADGET(OKX+10,OKY+8,120,15,A_S,K1,0,K2,31,-1);//	   GADGET[OKX+10,OKY+8,120,15,A$,K1,0,K2,31,-1]
																								//	   If Exist(KAT$+"archiwum")
	PAT_S=KAT_S+"archiwum/";											//	      PAT$=KAT$+"archiwum/"
	if( ! DirExists(PAT_S) ) {
		PAT_S="./";
	}
																								//	   Else
																								//	      REQUEST["archiwum:","Archiwum"]
																								//	      PAT$="archiwum:"
																								//	   End If
																								//
	for( I=0; I<=4; ++I ) {												//	   For I=0 To 4
		NAME_S = _sdir_get_file_name(I);
		GADGET(OKX+10,OKY+28+(I*20),120,15,NAME_S,8,1,6,31,I+1);//	      GADGET[OKX+10,OKY+28+(I*20),120,15,NAME$,8,1,6,31,I+1]
	}																							//	   Next
	GADGET(OKX+10,OKY+128,120,15,GS("226"),8,1,6,31,6);//	   GADGET[OKX+10,OKY+128,120,15,"Exit",8,1,6,31,6]
	Param_S=PAT_S;																							//	End Proc[PAT$]
}
void REQUEST(astr A_S,astr NAPI_S) {
	//NONEEDTODO
	//	Procedure REQUEST[A$,NAPI$]
	//	   If Not Exist(A$)
	//	      'MLech
	//	      NAPI$=NAPI$+" "+A$
	//
	//	      SKRIN=Screen
	//	      Hide
	//	      Screen Open 4,320,17,4,Lowres
	//	      Screen Display 4,140,270,320,
	//	      Screen To Front 4 : Screen 4
	//	      Set Rainbow 0,1,64,"(1,1,1)","",""
	//	      Rainbow 0,0,138,16
	//	      Curs Off
	//	      Flash Off
	//	      Set Font FON2
	//	      If SKRIN>-1 and SKRIN<8 : Get Palette SKRIN : End If
	//	      Palette $0,$A00,$BF0,$840
	//	      Cls 1
	//	      '   Gr Writing 0 : Ink 2 : Text 120,10,NAPI$
	//	      X=160-(Text Length(NAPI$)/2)
	//	      OUTLINE[X,10,NAPI$,2,3]
	//	      Y=270
	//	      SPEED=12
	//	      Repeat
	//	         Add Y,-SPEED
	//	         Add SPEED,-1,1 To SPEED
	//	         Screen Display 4,140,Y,320,
	//	         Rainbow 0,0,Y-1,17
	//	         Wait Vbl : View
	//	      Until Y<200
	//	      Repeat
	//	         Wait Vbl
	//	      Until Exist(A$)
	//	      Repeat
	//	         Add Y,SPEED
	//	         Add SPEED,1,SPEED To 20
	//	         Screen Display 4,140,Y,320,
	//	         Rainbow 0,0,Y-2,16
	//	         Wait Vbl : View
	//	      Until Y>250
	//	      Rainbow Del 0
	//	      Screen Close 4
	//	      Show
	//	      If SKRIN>-1 and SKRIN<8 : Screen SKRIN : End If
	//	   End If
	//	End Proc
}

