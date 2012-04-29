
#include "Amos.h"

#include "legion.h"
#include "lgn_akcja.h"
#include "lgn_armia.h"
#include "lgn_diskacs.h"
#include "lgn_intro.h"
#include "lgn_mapa.h"
#include "lgn_miasto.h"
#include "lgn_opcje.h"
#include "lgn_przygoda.h"
#include "lgn_sceneria.h"
#include "lgn_util.h"
#include "utl_locale.h"
#include <cmath>

void SETUP0(void) {
	//	Procedure SETUP0

	EraseAll();	//	   Erase All
	//	   'Auto View Off
	//	   _LOAD[KAT$+"mapa2.org","Legion:mapa2.org","Legion",3]
	ScreenOpen(0,640,512,32,LOWRES);
	_LOAD(KAT_S+"mapa2.org",KAT_S+"mapa2.org.iff","Legion",3);
	ScreenDisplay(0,130,40,320,255);		//	   Screen Display 0,130,40,320,255
	ReserveZone(130);										//	   Reserve Zone 130
	LimitMouse(128,40,447,298);					//	   Limit Mouse 128,40 To 447,298
	BobUpdateOnOff(true);								//	   Bob Update On
	SpriteUpdateOnOff(true);						//		 Sprite Update On
																			//	   Flash Off
	USTAW_FONT("garnet",FONT_GARNET,16,1);//	   USTAW_FONT["garnet",16]
	FON2=FONR;													//	   FON2=FONR
	//!!! inny rozmiar niz oryginalnie
	USTAW_FONT("defender2",FONT_DEFENDER,12,1);			//	   USTAW_FONT["defender2",8]
	FON1=FONR;													//	   FON1=FONR

	_LOAD(KAT_S+GS("FILE001"),KAT_S+"mapa_eng.abk_sp","Legion",0);//	   _LOAD[KAT$+"mapa_eng","Legion:mapa_eng","Legion",0]
	ChangeMouse(5);											//	   Change Mouse 5
	CELOWNIK=43;												//	   CELOWNIK=43
																			//	   Show On
	BUBY=-1;														//	   BUBY=-1
	SPX=425; SPY=270;										//	   SPX=425 : SPY=270
	MSX=320; MSY=256;										//	   MSX=320 : MSY=256
	Sprite(2,SPX,SPY,1);								//	   Sprite 2,SPX,SPY,1
	SpriteOnOff(2,true);
																			//	   '   View
	//	   If PREFS(3)=1 : _LOAD[KAT$+"mod.legion","legion:mod.legion","Legion",6] : Track Play : Track Loop On : End If
  if( PREFS[3]==1 ) {
		_LOAD(KAT_S+"mod.legion",KAT_S+"mod.legion.mod","Legion",6);
		TrackLoop(true);
		TrackPlay(3);
	}

	rysuj_ekran_ptr = rysuj_mape;
	//	End Proc
}

void MAIN(void) {
	//glowna petla mapy
																			//	MAIN:
	aint X=0,Y=0,STREFA=0,KLAW=0;
	astr A_S="";

	GAME_OVER=0;												//	GAME_OVER=False
	REAL_KONIEC=0;											//	REAL_KONIEC=False
	rysuj_ekran_ptr = rysuj_mape;
	do {																//	Do
		A_S=Inkey_S();										//	   A$=Inkey$
		KLAW=ScanCode();									//	   KLAW=Scancode
		if( KLAW>75 && KLAW<80 ) {				//	   If KLAW>75 and KLAW<80
			KLAWSKROL(KLAW);								//	      KLAWSKROL[KLAW]
		}																	//	   End If
																			//	   '   If BOMBA1#<=0 : BOMBA1#=MIASTA(52,0,0) : End If
		ClearKey();												//	   Clear Key
		X=XMouse(); Y=YMouse();						//	   X=X Mouse : Y=Y Mouse
		rysuj();
		WaitVbl();												//	   Wait Vbl
		if( MouseKey() == PRAWY ) {				//	   If Mouse Key=PRAWY
			//	      If X>SPX-16 and Y>SPY-16 and X<SPX+16 and Y<SPY+16
			if( X>SPX-16 && Y>SPY-16 && X<SPX+16 && Y<SPY+16 ) {
																			//	         While Mouse Key=PRAWY
				while( MouseKey() == PRAWY ) {
					SPX=XMouse();								//	            SPX=X Mouse
					SPY=YMouse();								//	            SPY=Y Mouse
					Sprite(2,SPX,SPY,1);				//	            Sprite 2,SPX,SPY,1
					rysuj();
					WaitVbl();									//	            Wait Vbl
				}															//	         Wend
			} else {												//	      Else
				SKROL(0);											//	         SKROL[0]
			}																//	      End If
		}																	//	   End If
																			//
																			//	   '   If A$="p" : For I=1 To 4 : OBLICZ_POWER[I] : Pen GRACZE(I,3)+1 : Print Param : Next : End If
																			//
		STREFA=MouseZone();								//	   STREFA=Mouse Zone
		if( PREFS[5]==1 ) {								//	   If PREFS(5)=1
			if( STREFA>69 && STREFA<121 ) {	//	      If STREFA>69 and STREFA<121
																			//	         Gr Writing 3
				X=MIASTA[STREFA-70][0][M_X];	//	         X=MIASTA(STREFA-70,0,M_X)
				Y=MIASTA[STREFA-70][0][M_Y];	//	         Y=MIASTA(STREFA-70,0,M_Y)
				//	         Box X-8,Y-8 To X+8,Y+8 : Wait 2 : Box X-8,Y-8 To X+8,Y+8
				//	         Box X-7,Y-7 To X+7,Y+7 : Wait 2 : Box X-7,Y-7 To X+7,Y+7
				//	         Gr Writing 0
				rysuj();
				Gfx::Color(1.0f,1.0f,1.0f,0.5f);
				_Box(X-8,Y-8,X+8,Y+8);
				WaitVbl(); Wait(2);
				rysuj();
				Gfx::Color(1.0f,1.0f,1.0f,0.5f);
				_Box(X-7,Y-7,X+7,Y+7);
				WaitVbl(); Wait(2);
			}																//	      End If
			if( STREFA>19 && STREFA <61 ) {	//	      If STREFA>19 and STREFA<61
																			//	         Gr Writing 3
				X=ARMIA[STREFA-20][0][TX];		//	         X=ARMIA(STREFA-20,0,TX)
				Y=ARMIA[STREFA-20][0][TY];		//	         Y=ARMIA(STREFA-20,0,TY)
																			//	         Box X-4,Y-7 To X+4,Y : Wait 2 : Box X-4,Y-7 To X+4,Y
																			//	         Gr Writing 0
        rysuj();
				Gfx::Color(1.0f,1.0f,1.0f,0.5f);
				_Box(X-4,Y-7,X+4,Y);
				WaitVbl(); Wait(2);
				rysuj();
				WaitVbl(); Wait(2);
			}																//	      End If
		}																	//	   End If

		if( MouseClick() ) {							//	   If Mouse Click=1
			STREFA=MouseZone();							//	      STREFA=Mouse Zone
			//	      If X>SPX-14 and Y>SPY-14 and X<SPX+14 and Y<SPY-1
			if( X>SPX-14 && Y>SPY-14 && X<SPX+14 && Y<SPY-1 ) {
				MAPA_AKCJA();									//	         MAPA_AKCJA
				STREFA=0;											//	         STREFA=0
			}																//	      End If
			//	      If X>SPX-14 and Y>SPY+1 and X<SPX+14 and Y<SPY+15
			if( X>SPX-14 && Y>SPY+1 && X<SPX+14 && Y<SPY+15 ) {
				OPCJE();											//	         OPCJE
				STREFA=0;											//	         STREFA=0
			}																//	      End If
			if( STREFA>19 and STREFA<61 ) {	//	      If STREFA>19 and STREFA<61
				_ARMIA(STREFA-20);						//	         ARMIA[STREFA-20]
			}																//	      End If
			if( STREFA>69 && STREFA<121 ) {	//	      If STREFA>69 and STREFA<121
				MIASTO(STREFA-70);						//	         MIASTO[STREFA-70]
			}																//	      End If
			if( STREFA>120 && STREFA<125 ) {//	      If STREFA>120 and STREFA<125
				PRZYGODA_INFO(STREFA-121);		//	         PRZYGODA_INFO[STREFA-121]
			}																//	      End If
		}																	//	   End If
																			//	   Exit If REAL_KONIEC or GAME_OVER
		if( REAL_KONIEC!=0 || GAME_OVER!=0 ) break;
	} while(true);											//	Loop
																			//	Fade 2
	if( PREFS[3]==1 ) {									//	If PREFS(3)=1
		_TRACK_FADE(1);										//	   _TRACK_FADE[1]
	}																		//	End If
																			//	'   Wait 25
																			//	'End If
																			//	'sprzâtamy po sobie
	CLEAR_TABLES();											//	CLEAR_TABLES
	EraseAll();													//	Erase All
	SamStop(-1);												//	Sam Stop
	SpriteOnOff(-1,false);							//	Sprite Off
	if( GAME_OVER!=0 ) EXTRO();					//	If GAME_OVER : EXTRO : End If
	return;															//	Return
																			//	'-----------------------------
}

aint _nie_rysuj_tej_armii=-1;
void rysuj_mape(void) {
	_DrawIff(-1,0,0);

	//aint bob;
	aint B1=0, X=0, Y=0, I=0, A=0, CZYJE=0, LUD=0;

	//miasta
	//	for(int i=0;i<=49;++i) {
	//		bob = MIASTA[i][0][M_BOB];
	//		if( bob >= 0 )
	//			PasteBob( MIASTA[i][0][M_X]-8, MIASTA[i][0][M_Y]-8, bob );
	//	}

	//Armie
	//	for(int i=0;i<40;++i ) {
	//		bob = ARMIA[i][0][TBOB];
	//		if( bob >= 0 )
	//			PasteBob( ARMIA[i][0][TX]-1, ARMIA[i][0][TY], bob );
	//	}


	//miasta
	for( I=0; I<=49; ++I ) {														//	   For I=0 To 49
		CZYJE=MIASTA[I][0][M_CZYJE];											//	      CZYJE=MIASTA(I,0,M_CZYJE)
		B1=8+CZYJE*2;																			//	      B1=8+CZYJE*2
		LUD=MIASTA[I][0][M_LUDZIE];												//	      LUD=MIASTA(I,0,M_LUDZIE)
		if( LUD>700 ) {																		//	      If LUD>700
			B1++;																						//	         Inc B1
		}																									//	      End If
		X=MIASTA[I][0][M_X];															//	      X=MIASTA(I,0,M_X)
		Y=MIASTA[I][0][M_Y];															//	      Y=MIASTA(I,0,M_Y)
		PasteBob(X-8,Y-8,B1);															//	      Paste Bob X-8,Y-8,B1
	}																										//	   Next I

	//armie
	for( A=0; A<=39; ++A ) {														//	   For A=0 To 39
		if( A!=_nie_rysuj_tej_armii ) {
			if( ARMIA[A][0][TE]>0 ) {													//	      If ARMIA(A,0,TE)>0
				X=ARMIA[A][0][TX];															//	         X=ARMIA(A,0,TX)
				Y=ARMIA[A][0][TY];															//	         Y=ARMIA(A,0,TY)
				B1=ARMIA[A][0][TBOB];														//	         B1=ARMIA(A,0,TBOB)
				PasteBob(X,Y,B1);
			}																									//	      End If
		}
	}																										//	   Next A

	//przygody																										//
	for( I=0; I<=3; ++I ) {															//	   For I=0 To 3
		if( PRZYGODY[I][P_TYP]>0 && PRZYGODY[I][P_LEVEL]==0 ) {//	      If PRZYGODY(I,P_TYP)>0 and PRZYGODY(I,P_LEVEL)=0
			X=PRZYGODY[I][P_X]; Y=PRZYGODY[I][P_Y];					//	         X=PRZYGODY(I,P_X) : Y=PRZYGODY(I,P_Y)
			PasteBob(X,Y,18);																//	         Paste Bob X2,Y2,18
		}																									//	      End If
	}																										//	   Next I

	Gfx::Color(0.f,0.f,0.f);
	_ClearRaster(0,510,640,525);

}

void B_CLEAR(aint NR) {
	//	Procedure B_CLEAR[NR]

	//	   X=ARMIA(NR,0,TX)
	//	   Y=ARMIA(NR,0,TY)
	ResetZone(NR+20);	//	   Reset Zone NR+20
	//	   Put Block NR+1,X-4,Y-7
	//	   Z1=Zone(X-4,Y-7)
	//	   Z2=Zone(X+4,Y-7)
	//	   Z3=Zone(X-4,Y)
	//	   Z4=Zone(X+4,Y)
	//	   If Z1>=20 and Z1<60 : B_UPDATE[Z1-20] : End If
	//	   If Z2>=20 and Z2<60 : B_UPDATE[Z2-20] : End If
	//	   If Z3>=20 and Z3<60 : B_UPDATE[Z3-20] : End If
	//	   If Z4>=20 and Z4<60 : B_UPDATE[Z4-20] : End If
	//	End Proc
}
void B_DRAW(aint NR,aint X,aint Y,aint O) {
	//	Procedure B_DRAW[NR,X,Y,O]

	ResetZone(NR+20);							//	   Reset Zone NR+20
																//	   Z1=Zone(X-4,Y-7)
																//	   Z2=Zone(X+4,Y-7)
																//	   Z3=Zone(X-4,Y)
																//	   Z4=Zone(X+4,Y)
																//	   If Z1>=20 and Z1<60 : B_OFF[Z1-20] : End If
																//	   If Z2>=20 and Z2<60 : B_OFF[Z2-20] : End If
																//	   If Z3>=20 and Z3<60 : B_OFF[Z3-20] : End If
																//	   If Z4>=20 and Z4<60 : B_OFF[Z4-20] : End If
																//	   Get Block NR+1,X-4,Y-7,8,8,1
																//	   If Z1>=20 and Z1<60 : B_UPDATE[Z1-20] : End If
																//	   If Z2>=20 and Z2<60 : B_UPDATE[Z2-20] : End If
																//	   If Z3>=20 and Z3<60 : B_UPDATE[Z3-20] : End If
																//	   If Z4>=20 and Z4<60 : B_UPDATE[Z4-20] : End If
																//	   Paste Bob X-4,Y-7,O
	SetZone(NR+20,X-4,Y-7,X+4,Y);	//	   Set Zone NR+20,X-4,Y-7 To X+4,Y
																//	End Proc
}
void B_UPDATE(aint NR) {
	//	Procedure B_UPDATE[NR]

	//inaczej podchodze do kwesti rysowania armi na mapie
	;
	//	   X=ARMIA(NR,0,TX)
	//	   Y=ARMIA(NR,0,TY)
	//	   O=ARMIA(NR,0,TBOB)
	//	   Paste Bob X-4,Y-7,O
	//	End Proc
}
void B_OFF(aint NR) {
	//	Procedure B_OFF[NR]

	//inaczej podchodze do kwesti rysowania armi na mapie
	;
	//	   X=ARMIA(NR,0,TX)
	//	   Y=ARMIA(NR,0,TY)
	//	   Put Block NR+1,X-4,Y-7
	//	End Proc
}

void MAPA_AKCJA(void) {
	//	Procedure MAPA_AKCJA
	aint I=0,J=0,SR=0,PL=0,OLDSI=0,SI=0,P=0,X=0,Y=0,
	     MUNDRY=0,TRYB=0,A=0,RASA=0,ZARCIE=0,DNI=0,
	     M=0,LUDZIE=0,CZYJE=0,SPI=0,MORALE=0,SZAJBA=0,
	     PODATEK=0,JEST=0,_ATAK=0,_TEREN=0,LWOJ=0,MB=0;
	astr A_S="", KON_S="";

	DZIEN++;																			//	   Inc DZIEN
	BUSY_ANIM();																	//	   BUSY_ANIM
																								//	   'wygaszanie konfliktów zbrojnych przez NATO
	for(I=0;I<=5;++I) {														//	   For I=0 To 5
		for(J=0;J<=5;++J) {													//	      For J=0 To 5
			//!!! BLAD
			Add(WOJNA[I][J],-1,0,WOJNA[I][J]);				//	         Add WOJNA(I,J),-1,0 To WOJNA(I,J)
			//!!! powinno byc
			//WOJNA[I][J] -=1;
			//clipl(WOJNA[I][J],0);
		}																						//	      Next
	}																							//	   Next
																								//	   'wszczynanie duûych wojen
	SR=0;																					//	   SR=0
	for(PL=1;PL<=4;++PL) {												//	   For PL=1 To 4 : OBLICZ_POWER[PL] : SR=SR+Param : Next
		OBLICZ_POWER(PL); SR=SR+Param;
	}
	POWER=(GRACZE[1][2]/900)+7;										//	   POWER=(GRACZE(1,2)/900)+7 : If POWER>99 : POWER=99 : End If
	if( POWER>99 ) POWER=99;
	SR/=4;																				//	   SR=SR/4
																								//	   '   Pen 21 : Print At(1,0);"power:",POWER,GRACZE(1,2),SR
	OLDSI=0;																			//	   OLDSI=0
	for(I=1;I<=4;++I) {														//	   For I=1 To 4
		SI=GRACZE[I][2];														//	      SI=GRACZE(I,2)
																								//	      '      Pen GRACZE(I,3)+1 : Print At(1,I);SI
		if( SI>SR+((40*SR)/100) && SI>OLDSI ) {			//	      If SI>SR+((40*SR)/100) and SI>OLDSI
			OLDSI=SI;																	//	         OLDSI=SI
																								//	         '         Print At(10,I);"lider:"
			for(J=2;J<=4;++J) WOJNA[J][I]=Rnd(15)+10;	//	         For J=2 To 4 : WOJNA(J,I)=Rnd(15)+10 : Next
		}																						//	      End If
	}																							//	   Next I
																								//
																								//	   'nowe legiony chaosu
	P=50-POWER;																		//	   P=50-POWER
	if(P<2) P=2;																	//	   If P<2 : P=2 : End If
	if( Rnd(P)==1 ) {															//	   If Rnd(P)=1
		for(I=20;I<=39;++I) {												//	      For I=20 To 39
			if( ARMIA[I][0][TE]==0 ) {								//	         If ARMIA(I,0,TE)=0
				ARMIA_S[I][0]=GS("041");								//	            ARMIA$(I,0)="Chaos Worriors"
				MESSAGE2(I,GS("042"),38,0,0);						//	            MESSAGE2[I,"are comming from hell to play havoc",38,0,0]
				NOWA_ARMIA(I,10,11);										//	            NOWA_ARMIA[I,10,11]
				ARMIA[I][0][TMAG]=5;										//	            ARMIA(I,0,TMAG)=5
				X=Rnd(600)+20;													//	            X=Rnd(600)+20
				Y=Rnd(490)+10;													//	            Y=Rnd(490)+10
				ARMIA[I][0][TX]=X;											//	            ARMIA(I,0,TX)=X
				ARMIA[I][0][TY]=Y;											//	            ARMIA(I,0,TY)=Y
				ARMIA[I][0][TBOB]=7;										//	            ARMIA(I,0,TBOB)=7
				TEREN(X,Y);															//	            TEREN[X,Y]
				ARMIA[I][0][TNOGI]=LOK;									//	            ARMIA(I,0,TNOGI)=LOK
				B_DRAW(I,X,Y,7);												//	            B_DRAW[I,X,Y,7]
				I=39;																		//	            I=39
			}																					//	         End If
		}																						//	      Next I
	}																							//	   End If
																								//
																								//	   'obsîuga moich armii
	for(A=0;A<=19;++A) {													//	   For A=0 To 19
		if( GAME_OVER != 0 ) break;									//	      Exit If GAME_OVER
		if( ARMIA[A][0][TE] > 0 ) {									//	      If ARMIA(A,0,TE)>0
																								//	         'comiesiëczne douczanki
			if( DZIEN % 30 == 0 ) {										//	         If DZIEN mod 30=0
				for(I=1;I<=10;++I) {										//	            For I=1 To 10
					if( ARMIA[A][I][TE] > 0 ) {						//	               If ARMIA(A,I,TE)>0
						RASA=ARMIA[A][I][TRASA];						// !!! BUG ? tego orginalnie nie bylo
						MUNDRY=RASY[RASA][6];								//	                  MUNDRY=RASY(RASA,6)

						//!!! BLAD
						Add(ARMIA[A][I][TDOSW],Rnd(MUNDRY),ARMIA[A][I][TDOSW],95);//	                  Add ARMIA(A,I,TDOSW),Rnd(MUNDRY),ARMIA(A,I,TDOSW) To 95
						//!!! powinno byc
						//ARMIA[A][I][TDOSW] += Rnd(MUNDRY);
						//clipu(ARMIA[A][I][TDOSW],95);

					}																			//	               End If
				}																				//	            Next I
			}																					//	         End If
			ARMIA[A][0][TWAGA]=0;											//	         ARMIA(A,0,TWAGA)=0
			TRYB=ARMIA[A][0][TTRYB];									//	         TRYB=ARMIA(A,0,TTRYB)
			ZARCIE=ARMIA[A][0][TAMO];									//	         ZARCIE=ARMIA(A,0,TAMO)
			DNI=ZARCIE/ARMIA[A][0][TE];								//	         DNI=ZARCIE/ARMIA(A,0,TE)
			if( DNI<5 && DNI>0 ) {										//	         If DNI<5 and DNI>0
				MESSAGE(A,GS("043"),0,0);								//	            MESSAGE[A,"We have not enough food.",0,0]
			}																					//	         End If
			if( ZARCIE<=0 ) {													//	         If ZARCIE<=0
				MESSAGE(A,GS("044"),0,0);								//	            MESSAGE[A,"Unit disbanded",0,0]
				ZABIJ_ARMIE(A);													//	            ZABIJ_ARMIE[A]
				B_CLEAR(A);															//	            B_CLEAR[A]
				goto OVER_NEXT;													//	            Goto OVER_NEXT
			}																					//	         End If
			if( TRYB>0 && TRYB<4 ) {									//	         If TRYB>0 and TRYB<4
				MA_RUCH(A,TRYB);												//	            MA_RUCH[A,TRYB]
			}																					//	         End If
			if( TRYB==0 ) {														//	         If TRYB=0
				MA_OBOZ(A);															//	            MA_OBOZ[A]
			}																					//	         End If
			if( TRYB==4 ) {														//	         If TRYB=4
				MA_POLOWANIE(A);												//	            MA_POLOWANIE[A]
			}																					//	         End If
		}																						//	      End If
		OVER_NEXT:																	//	      OVER_NEXT:
			;
	}																							//	   Next A
	if( GAME_OVER ) goto OVER;										//	   If GAME_OVER : Goto OVER : End If
																								//	   'obsîuga cudzych armii
	for(A=20;A<=39;++A) {													//	   For A=20 To 39
		if( ARMIA[A][0][TE] > 0 ) {									//	      If ARMIA(A,0,TE)>0
			PL=ARMIA[A][0][TMAG];											//	         PL=ARMIA(A,0,TMAG)
			if( ARMIA[A][0][TMAGMA]<28 && ARMIA[A][0][TMAGMA]>0 ) {//	         If ARMIA(A,0,TMAGMA)<28 and ARMIA(A,0,TMAGMA)>0
				ARMIA[A][0][TMAGMA] -= 1;								//	            Dec ARMIA(A,0,TMAGMA)
			}																					//	         End If
			TRYB=ARMIA[A][0][TTRYB];									//	         TRYB=ARMIA(A,0,TTRYB)
			if( TRYB>0 && TRYB<4 ) {									//	         If TRYB>0 and TRYB<4
				if( Rnd(6)==1 ) {												//	            If Rnd(6)=1
					MA_WYDAJ_ROZKAZ(PL,A);								//	               MA_WYDAJ_ROZKAZ[PL,A]
				} else {																//	            Else
					MA_RUCH(A,TRYB);											//	               MA_RUCH[A,TRYB]
				}																				//	            End If
			}																					//	         End If
			if( TRYB==0 ) {														//	         If TRYB=0
				MA_OBOZ(A);															//	            MA_OBOZ[A]
				MA_WYDAJ_ROZKAZ(PL,A);									//	            MA_WYDAJ_ROZKAZ[PL,A]
			}																					//	         End If
			if( TRYB==4 ) {														//	         If TRYB=4
				MA_POLOWANIE(A);												//	            MA_POLOWANIE[A]
			}																					//	         End If
		}																						//	      End If
	}																							//	   Next
																								//	   'MIASTA
																								//	   '   If DZIEN mod 96=0 : ZAB2 : End If
	for(M=0;M<=49;++M) {													//	   For M=0 To 49
		LUDZIE=MIASTA[M][0][M_LUDZIE];							//	      LUDZIE=MIASTA(M,0,M_LUDZIE)
		if( Rnd(50)==1 && LUDZIE>800 ) {						//	      If Rnd(50)=1 and LUDZIE>800 : PLAGA[M,Rnd(2)] : End If
			PLAGA(M,Rnd(2));
		}
		CZYJE=MIASTA[M][0][M_CZYJE];								//	      CZYJE=MIASTA(M,0,M_CZYJE)
																								//	      'szajba & podatek modification
		if( Rnd(5)==1 ) {														//	      If Rnd(5)=1 : Add MIASTA(M,1,M_MORALE),Rnd(2)-1,0 To 25 : End If
			//!!! BLAD
			Add(MIASTA[M][1][M_MORALE],Rnd(2)-1,0,25);
			//!!! powinno byc
			//MIASTA[M][1][M_MORALE] += Rnd(2)-1;
			//clipu(MIASTA[M][1][M_MORALE],25);
		}
		PODATEK=MIASTA[M][0][M_PODATEK];						//	      PODATEK=MIASTA(M,0,M_PODATEK)
		GRACZE[CZYJE][1] += PODATEK*MIASTA[M][0][M_LUDZIE]/25;//	      Add GRACZE(CZYJE,1),PODATEK*MIASTA(M,0,M_LUDZIE)/25
																								//	      'obsîuga spichlerzy
		SPI=0;																			//	      SPI=0
		for(I=2;I<=20;++I) {												//	      For I=2 To 20
			if( MIASTA[M][I][M_LUDZIE]==9 ) SPI++;		//	         If MIASTA(M,I,M_LUDZIE)=9 : Inc SPI : End If
		}																						//	      Next I
		if( SPI>0 ) {																//	      If SPI>0 : Add MIASTA(M,1,M_LUDZIE),LUDZIE/15,MIASTA(M,1,M_LUDZIE) To SPI*200 : End If
			//!!! BLAD
			Add(MIASTA[M][1][M_LUDZIE],LUDZIE/15,MIASTA[M][1][M_LUDZIE],SPI*200);
			//!!! powinno byc
			//MIASTA[M][1][M_LUDZIE] += LUDZIE/15;
			//clipu(MIASTA[M][1][M_LUDZIE],SPI*200);
		}
																								//
																								//	'      If BOMBA2#>175 : C=2/ZERO : End If
		if( CZYJE>1 ) {															//	      If CZYJE>1
			MIASTA[M][0][M_LUDZIE] += Rnd(10)-2;			//	         Add MIASTA(M,0,M_LUDZIE),Rnd(10)-2
			if( GRACZE[CZYJE][1]>10000 && Rnd(3)==1 && MIASTA[M][1][M_PODATEK]==0 ) {//	         If GRACZE(CZYJE,1)>10000 and Rnd(3)=1 and MIASTA(M,1,M_PODATEK)=0
				for(I=20;I<=39;++I) {										//	            For I=20 To 39
					if( ARMIA[I][0][TE]<=0 ) {						//	               If ARMIA(I,0,TE)<=0
						GRACZE[CZYJE][1] -= 10000;					//	                  Add GRACZE(CZYJE,1),-10000
						MIASTA[M][1][M_PODATEK]=20+Rnd(10);	//	                  MIASTA(M,1,M_PODATEK)=20+Rnd(10)
						NOWA_ARMIA(I,10,-1);								//	                  NOWA_ARMIA[I,10,-1]
						ARMIA[I][0][TMAG]=CZYJE;						//	                  ARMIA(I,0,TMAG)=CZYJE
						X=MIASTA[M][0][M_X];								//	                  X=MIASTA(M,0,M_X)
						Y=MIASTA[M][0][M_Y];								//	                  Y=MIASTA(M,0,M_Y)
						ARMIA[I][0][TX]=X;									//	                  ARMIA(I,0,TX)=X
						ARMIA[I][0][TY]=Y;									//	                  ARMIA(I,0,TY)=Y
						ARMIA[I][0][TBOB]=2+CZYJE;					//	                  ARMIA(I,0,TBOB)=2+CZYJE
						ARMIA[I][0][TNOGI]=MIASTA[M][1][M_X];//	                  ARMIA(I,0,TNOGI)=MIASTA(M,1,M_X)
						if( Upper_S(Right_S(IMIONA_S[CZYJE],1))=="I") {																		//										If Upper$(Right$(IMIONA$(CZYJE),1))="I"
							KON_S=GS("046");									//											 KON$="ego"
						} else {														//										Else
							KON_S=GS("047");									//											 KON$="a"
						}																		//										End If
						ARMIA_S[I][0]=Str_S(I)+GS("045")+IMIONA_S[CZYJE]+KON_S;//	                  ARMIA$(I,0)=Str$(I)+" Legion of "+IMIONA$(CZYJE)
						B_DRAW(I,X,Y,2+CZYJE);							//	                  B_DRAW[I,X,Y,2+CZYJE]
						I=39;																//	                  I=39
					}																			//	               End If
				}																				//	            Next I
			}																					//	         End If
		}																						//	      End If
		if( CZYJE==1 ) {														//	      If CZYJE=1
			MORALE=MIASTA[M][0][M_MORALE];						//	         MORALE=MIASTA(M,0,M_MORALE)
			SZAJBA=MIASTA[M][1][M_MORALE];						//	         SZAJBA=MIASTA(M,1,M_MORALE)
			LUDZIE=MIASTA[M][0][M_LUDZIE];						//	         LUDZIE=MIASTA(M,0,M_LUDZIE)
			LUDZIE += SZAJBA-PODATEK;									//	         Add LUDZIE,SZAJBA-PODATEK
			MORALE += SZAJBA-PODATEK;									//	         Add MORALE,SZAJBA-PODATEK
			if( MORALE>150 ) MORALE=150;							//	         If MORALE>150 : MORALE=150 : End If
			if( MORALE<=0 ) {													//	         If MORALE<=0
				A_S=GS("048");													//	            A$="The Revolt has begun in the town."
				JEST=0;																	//	            JEST=False
				for(I=0;I<=19;++I) {										//	            For I=0 To 19
					if( ARMIA[I][0][TE]>0 && ARMIA[I][0][TNOGI]-70==M) {//	               If ARMIA(I,0,TE)>0 and ARMIA(I,0,TNOGI)-70=M
						JEST=-1;														//	                  JEST=True
						_ATAK=I;														//	                  _ATAK=I
						I=19;																//	                  I=19
					}																			//	               End If
				}																				//	            Next I
																								//
				if( JEST ) {														//	            If JEST
					A_S=A_S+ARMIA_S[_ATAK][0]+GS("049");	//	               A$=A$+ARMIA$(_ATAK,0)+" will fight against rebels."
					_TEREN=MIASTA[M][1][M_X];							//	               TEREN=MIASTA(M,1,M_X)
					LWOJ=(LUDZIE/70)+1;										//	               LWOJ=(LUDZIE/70)+1 : If LWOJ>10 : LWOJ=10 : End If
					if( LWOJ>10 ) LWOJ=10;
					NOWA_ARMIA(40,LWOJ,-1);								//	               NOWA_ARMIA[40,LWOJ,-1]
																								//	               'wieôniacy wôród buntowników
					aint k=2+Rnd(2);
					for(I=1;I<=k;++I) {										//	               For I=1 To 2+Rnd(2) : NOWA_POSTAC[40,I,9] : Next I
						NOWA_POSTAC(40,I,9);
					}
					AmalOnOff(0,false);										//	               Amal Off 0
																								//	               Show On
					CENTER(MIASTA[M][0][M_X],MIASTA[M][0][M_Y],1);//	               CENTER[MIASTA(M,0,M_X),MIASTA(M,0,M_Y),1]
					MESSAGE(M,A_S,0,1);										//	               MESSAGE[M,A$,0,1]
					BITWA(_ATAK,40,1,1,0,1,1,1,_TEREN,M);	//	               BITWA[_ATAK,40,1,1,0,1,1,1,TEREN,M]
					LUDZIE += -(LUDZIE/4);								//	               Add LUDZIE,-(LUDZIE/4)
					CENTER(MIASTA[M][0][M_X],MIASTA[M][0][M_Y],0);//	               CENTER[MIASTA(M,0,M_X),MIASTA(M,0,M_Y),0]
																								//	               'Hide On
																								//	               'Amal On 0
					if( ARMIA[_ATAK][0][TE]==0 ) {				//	               If ARMIA(_ATAK,0,TE)=0
						JEST=0;															//	                  JEST=False
						A_S=GS("050");											//	                  A$="Rebels are controling the town."
					} else {															//	               Else
						MORALE=50;													//	                  MORALE=50
						MIASTA[M][1][M_MORALE] += Rnd(3)+5;	//	                  Add MIASTA(M,1,M_MORALE),Rnd(3)+5
					}																			//	               End If
				}																				//	            End If
																								//
				if( JEST==0 ) {													//	            If Not JEST
					CENTER(MIASTA[M][0][M_X],MIASTA[M][0][M_Y],1);//	               CENTER[MIASTA(M,0,M_X),MIASTA(M,0,M_Y),1]
					MESSAGE(M,A_S,0,1);										//	               MESSAGE[M,A$,0,1]
					MIASTA[M][0][M_CZYJE]=0;							//	               MIASTA(M,0,M_CZYJE)=0
					MB=8;																	//	               MB=8
					if( LUDZIE>700 ) MB++;								//	               If LUDZIE>700 : Inc MB : End If
					PasteBob(MIASTA[M][0][M_X]-8,MIASTA[M][0][M_Y]-8,MB);//	               Paste Bob MIASTA(M,0,M_X)-8,MIASTA(M,0,M_Y)-8,MB
					MORALE=30;														//	               MORALE=30
				}																				//	            End If
			}																					//	         End If
			if( LUDZIE<30 ) LUDZIE=30;								//	         If LUDZIE<30 : LUDZIE=30 : End If
			MIASTA[M][0][M_LUDZIE]=LUDZIE;						//	         MIASTA(M,0,M_LUDZIE)=LUDZIE
			MIASTA[M][0][M_MORALE]=MORALE;						//	         MIASTA(M,0,M_MORALE)=MORALE
		}																						//	      End If
		if( MIASTA[M][1][M_Y]<25 && MIASTA[M][1][M_Y]>0 ) {//	      If MIASTA(M,1,M_Y)<25 and MIASTA(M,1,M_Y)>0 : Dec MIASTA(M,1,M_Y) : End If
			MIASTA[M][1][M_Y] -= 1;
		}
		if( MIASTA[M][1][M_PODATEK]>0 ) {						//	      If MIASTA(M,1,M_PODATEK)>0 : Dec MIASTA(M,1,M_PODATEK) : End If
			MIASTA[M][1][M_PODATEK] -= 1;
		}
	}																							//	   Next
	OBLICZ_POWER(1);															//	   OBLICZ_POWER[1]
	OVER:																					//	   OVER:
	AmalOnOff(-1,false);													//	   Amal Off
																								//	   Show On
	SpriteOnOff(0,false);
	//_ShowCursor(true);
																								//	   'If DZIEN mod _MODULO=0 : ZAB2 : End If
}	//	End Proc
void MA_RUCH(aint A,aint TRYB) {
	//	Procedure MA_RUCH[A,TRYB]

	aint PL=0,X1=0,Y1=0,WOJ=0,ZARCIE=0,SPEED=0,BB=0
			,X2=0,Y2=0,ILE_ZRE=0,B=0,C=0,PL2=0
	    ,SYMULACJA=0,DX=0,DY=0,LTRYB=0,LOAX=0,LOAX2=0
	    ,LOAY=0,LOAY2=0,I=0,NR=0,SKIP=0,_TEREN=0
	    ,MT=0,ILEDNI=0,LOSER=0,_MUR=0,MORALE=0
	    ,LUDZIE=0,LWOJ=0,MB=0,OLDPOWER=0,OBRONA=0,J=0,P=0;
	astr A_S="", KON_S="";
	aflt L_F=0,VX_F=0,VY_F=0,X_F=0,Y_F=0;

	PL=ARMIA[A][0][TMAG];								//	   PL=ARMIA(A,0,TMAG)
	X1=ARMIA[A][0][TX];									//	   X1=ARMIA(A,0,TX)
	Y1=ARMIA[A][0][TY];									//	   Y1=ARMIA(A,0,TY)
	if( ARMIA[A][0][TMAGMA]==100 ) 	{		//	   If ARMIA(A,0,TMAGMA)=100 : CENTER[X1,Y1,1] : End If
		CENTER(X1,Y1,1);
	}
	WOJ=ARMIA[A][0][TE];								//	   WOJ=ARMIA(A,0,TE)
	ZARCIE=ARMIA[A][0][TAMO];						//	   ZARCIE=ARMIA(A,0,TAMO)
	SPEED=ARMIA[A][0][TSZ];							//	   SPEED=ARMIA(A,0,TSZ)
	BB=ARMIA[A][0][TBOB];								//	   BB=ARMIA(A,0,TBOB)
	if( TRYB==1 ) {											//	   If TRYB=1
		X2=ARMIA[A][0][TCELX];						//	      X2=ARMIA(A,0,TCELX)
		Y2=ARMIA[A][0][TCELY];						//	      Y2=ARMIA(A,0,TCELY)
		ILE_ZRE=1;												//	      ILE_ZRE=1
	}																		//	   End If
	if( TRYB==2 ) {											//	   If TRYB=2
		X2=ARMIA[A][0][TCELX];						//	      X2=ARMIA(A,0,TCELX)
		Y2=ARMIA[A][0][TCELY];						//	      Y2=ARMIA(A,0,TCELY)
		ILE_ZRE=3;												//	      ILE_ZRE=3
		SPEED=ARMIA[A][0][TSZ]*2;					//	      SPEED=ARMIA(A,0,TSZ)*2
	}																		//	   End If
	if( TRYB==3 ) {											//	   If TRYB=3
		C=ARMIA[A][0][TCELY];							//	      C=ARMIA(A,0,TCELY)
		B=ARMIA[A][0][TCELX];							//	      B=ARMIA(A,0,TCELX)
		if( C==0 ) {											//	      If C=0
			X2=ARMIA[B][0][TX];							//	         X2=ARMIA(B,0,TX)
			Y2=ARMIA[B][0][TY];							//	         Y2=ARMIA(B,0,TY)
			A_S=ARMIA_S[B][0];							//	         A$=ARMIA$(B,0)
			PL2=ARMIA[B][0][TMAG];					//	         PL2=ARMIA(B,0,TMAG)
			if( ARMIA[B][0][TE]<=0 ) {			//	         If ARMIA(B,0,TE)<=0 : ARMIA(A,0,TTRYB)=0 : Goto OVER : End If
				ARMIA[A][0][TTRYB]=0;
				goto OVER;
			}
		} else {													//	      Else
			X2=MIASTA[B][0][M_X];						//	         X2=MIASTA(B,0,M_X)
			Y2=MIASTA[B][0][M_Y];						//	         Y2=MIASTA(B,0,M_Y)
			A_S=MIASTA_S[B];								//	         A$=MIASTA$(B)
			PL2=MIASTA[B][0][M_CZYJE];			//	         PL2=MIASTA(B,0,M_CZYJE)
			if( PL==PL2 ) {									//	         If PL=PL2 : ARMIA(A,0,TTRYB)=0 : Goto OVER : End If
				ARMIA[A][0][TTRYB]=0;
				goto OVER;
			}
		}																	//	      End If
		ILE_ZRE=1;												//	      ILE_ZRE=1
																			//
		if( PL!=1 && PL2!=1 ) {						//	      If PL<>1 and PL2<>1 : SYMULACJA=True : End If
			SYMULACJA=-1;
		}
	}																		//	   End If
	if( A<20 ) {												//	   If A<20
		ZARCIE -= WOJ*ILE_ZRE;						//	      Add ZARCIE,-WOJ*ILE_ZRE
		if( ZARCIE<0 ) ZARCIE=0;					//	      If ZARCIE<0 : ZARCIE=0 : End If
		ARMIA[A][0][TAMO]=ZARCIE;					//	      ARMIA(A,0,TAMO)=ZARCIE
	}																		//	   End If
	DX=X2-X1; DY=Y2-Y1;									//	   DX=X2-X1 : DY=Y2-Y1
																			//	   '   LOX=1 : LOY=1
																			//	   '   If DX>4 : LOX=0 : End If
																			//	   '   If DX<-4 : LOX=2 : End If
																			//	   '   If DY>4 : LOY=0 : End If
																			//	   '   If DY<-4 : LOY=2 : End If
																			//	   '   ARMIA(A,0,TLEWA)=LOX
																			//	   '   ARMIA(A,0,TPRAWA)=LOY
	if( Abs(DX)>Abs(DY) ) {							//	   If Abs(DX)>Abs(DY)
		LTRYB=3;													//	      LTRYB=3
		if( DX>=0 ) {											//	      If DX>=0
			LOAX=0; LOAX2=2;								//	         LOAX=0 : LOAX2=2
		} else {													//	      Else
			LOAX=2; LOAX2=0;								//	         LOAX=2 : LOAX2=0
		}																	//	      End If
	} else {														//	   Else
		LTRYB=2;													//	      LTRYB=2
		if( DY>=0 ) {											//	      If DY>=0
			LOAY=0; LOAY2=2;								//	         LOAY=0 : LOAY2=2
		} else {													//	      Else
			LOAY=2; LOAY2=0;								//	         LOAY=2 : LOAY2=0
		}																	//	      End If
	}																		//	   End If
	L_F=sqrt(DX*DX+DY*DY)+0.2;					//	   L#=Sqr(DX*DX+DY*DY)+0.2
	VX_F=DX/L_F; VY_F=DY/L_F;						//	   VX#=DX/L# : VY#=DY/L#
	X_F=X1; Y_F=Y1;											//	   X#=X1 : Y#=Y1
	B_CLEAR(A);													//	   B_CLEAR[A]
	_nie_rysuj_tej_armii = A;
	for(I=0;I<=SPEED;++I) {							//	   For I=0 To SPEED
		X_F += VX_F;											//	      X#=X#+VX#
		Y_F += VY_F;											//	      Y#=Y#+VY#
		X1=(aint)X_F; Y1=(aint)Y_F;				//	      X1=X# : Y1=Y#
		rysuj();
		_Bob(1,X1,Y1,BB);
		WaitVbl();												//	      Bob 1,X1,Y1,BB : Wait Vbl
		DX=X2-X1; DY=Y2-Y1;								//	      DX=X2-X1 : DY=Y2-Y1
		if( Abs(DX)<3 && Abs(DY)<3 ) {		//	      If Abs(DX)<3 and Abs(DY)<3
			break;													//	         Exit
		}																	//	      End If
	}																		//	   Next I
	BobOnOff(1,false); WaitVbl();				//	   Bob Off 1 : Wait Vbl
	_nie_rysuj_tej_armii = -1;
	TEREN(X1,Y1);												//	   TEREN[X1,Y1]
	if( LOK>69 && LOK<120 && A<20 ) {		//	   If LOK>69 and LOK<120 and A<20 : MIASTA(LOK-70,1,M_Y)=0 : End If
		MIASTA[LOK-70][1][M_Y]=0;
	}
	DX=X2-X1; DY=Y2-Y1;									//	   DX=X2-X1 : DY=Y2-Y1
	ARMIA[A][0][TX]=X1;									//	   ARMIA(A,0,TX)=X1
	ARMIA[A][0][TY]=Y1;									//	   ARMIA(A,0,TY)=Y1
	B_DRAW(A,X1,Y1,BB);									//	   B_DRAW[A,X1,Y1,BB]
	if( LOK>120 && A<20 ) {							//	   If LOK>120 and A<20
		NR=LOK-121;												//	      NR=LOK-121
		LOK=PRZYGODY[NR][P_TEREN];				//	      LOK=PRZYGODY(NR,P_TEREN)
		CENTER(X1,Y1,1);									//	      CENTER[X1,Y1,1]
		MA_PRZYGODA(A,NR);								//	      MA_PRZYGODA[A,NR]
																			//	      'nie chcë juû wiëcej przygód
		SKIP=1;														//	      SKIP=1
	}																		//	   End If
	ARMIA[A][0][TNOGI]=LOK;							//	   ARMIA(A,0,TNOGI)=LOK
	if( Abs(DX)<3 && Abs(DY)<3 ) {			//	   If Abs(DX)<3 and Abs(DY)<3
		AmalOnOff(-1,false);							//	      Amal Off 0
																			//	      Show On
		if( TRYB==3 && C==0 ) {						//	      If TRYB=3 and C=0
			_TEREN=ARMIA[B][0][TNOGI];			//	         TEREN=ARMIA(B,0,TNOGI)
			ARMIA[A][0][TNOGI]=_TEREN;			//	         ARMIA(A,0,TNOGI)=TEREN
			if( _TEREN>69 && _TEREN<121 ) {	//	         If TEREN>69 and TEREN<121
				MT=_TEREN-70;									//	            MT=TEREN-70
				_TEREN=MIASTA[MT][1][M_X];		//	            TEREN=MIASTA(TEREN-70,1,M_X)
			} else {												//	         Else
				MT=-1;												//	            MT=-1
			}																//	         End If
			if( SYMULACJA!=0 ) {						//	         If SYMULACJA
				BITWA_SYMULOWANA(A,B);				//	            BITWA_SYMULOWANA[A,B]
				LOSER=Param;									//	            LOSER=Param
				if( ARMIA[LOSER][0][TMAGMA]==100 ) {//	            If ARMIA(LOSER,0,TMAGMA)=100
					MESSAGE2(LOSER,GS("051"),33,0,0);//	               MESSAGE2[LOSER," has been defeat.",33,0,0]
				}															//	            End If
			} else {												//	         Else
																			//	            'LOX=ARMIA(B,0,TLEWA)
																			//	            'LOY=ARMIA(B,0,TPRAWA)
				if( A>19 ) {									//	            If A>19
					CENTER(X1,Y1,1);						//	               CENTER[X1,Y1,1]
					MESSAGE(A,GS("052")+A_S+" ",0,0);//	               MESSAGE[A,"is attacking our unit "+A$+" ",0,0]
					BITWA(B,A,LOAX2,LOAY2,LTRYB,LOAX,LOAY,LTRYB,_TEREN,MT);//	               BITWA[B,A,LOAX2,LOAY2,LTRYB,LOAX,LOAY,LTRYB,TEREN,MT]
					ARMIA[A][0][TMAGMA]=0;			//	               ARMIA(A,0,TMAGMA)=0
				} else {											//	            Else
					CENTER(X1,Y1,1);						//	               CENTER[X1,Y1,1]
					MESSAGE(A,GS("053")+A_S+" ",0,0);//	               MESSAGE[A,"We are begining to attack "+A$+" ",0,0]
					ILEDNI=Rnd(30)+10;					//	               ILEDNI=Rnd(30)+10
					WOJNA[PL][PL2]=ILEDNI;			//	               WOJNA(PL,PL2)=ILEDNI
					WOJNA[PL2][PL]=ILEDNI;			//	               WOJNA(PL2,PL)=ILEDNI
					ARMIA[B][0][TMAGMA]=0;			//	               ARMIA(B,0,TMAGMA)=0
					BITWA(A,B,LOAX,LOAY,LTRYB,LOAX2,LOAY2,LTRYB,_TEREN,MT);//	               BITWA[A,B,LOAX,LOAY,LTRYB,LOAX2,LOAY2,LTRYB,TEREN,MT]
				}															//	            End If
				CENTER(X1,Y1,0);							//	            CENTER[X1,Y1,0]
				if( ARMIA[B][0][TE]==0 )			//	            If ARMIA(B,0,TE)=0 : MESSAGE2[B,"has been defeat",33,0,0] : End If
					MESSAGE2(B,GS("054"),33,0,0);
				if( ARMIA[A][0][TE]==0 ) 			//	            If ARMIA(A,0,TE)=0 : MESSAGE2[A,"has been defeat",33,0,0] : End If
					MESSAGE2(A,GS("054"),33,0,0);
			}																//	         End If
		}																	//	      End If
		if( TRYB==3 && C==1 ) {						//	      If TRYB=3 and C=1
			_TEREN=MIASTA[B][1][M_X];				//	         TEREN=MIASTA(B,1,M_X)
			_MUR=MIASTA[B][0][M_MUR];				//	         MUR=MIASTA(B,0,M_MUR)
			if( _MUR==0 || PL==5 ) {				//	         If MUR=0 or PL=5
				_MUR=B;												//	            MUR=B
			} else {												//	         Else
				_MUR=-_MUR-1;									//	            MUR=-MUR-1
			}																//	         End If
			MORALE=MIASTA[B][0][M_MORALE];	//	         MORALE=MIASTA(B,0,M_MORALE)
			LUDZIE=MIASTA[B][0][M_LUDZIE];	//	         LUDZIE=MIASTA(B,0,M_LUDZIE)
			LWOJ=(LUDZIE/70)+1;							//	         LWOJ=(LUDZIE/70)+1 : If LWOJ>10 : LWOJ=10 : End If
			if( LWOJ>10 ) LWOJ=10;
			MB=8+PL*2;											//	         MB=8+PL*2
			if( LUDZIE>700 ) MB++;					//	         If LUDZIE>700 : Inc MB : End If
			KTO_ATAKUJE=A;									//	         KTO_ATAKUJE=A
			if( SYMULACJA != 0 ) {					//	         If SYMULACJA
				OLDPOWER=POWER;								//	            OLDPOWER=POWER
				POWER=(MORALE/3)+10;					//	            POWER=(MORALE/3)+10
				NOWA_ARMIA(40,LWOJ,-1);				//	            NOWA_ARMIA[40,LWOJ,-1]
																			//	            'wiëkszy ostrzaî
				ARMIA[40][0][TKORP]=150+POWER;//	            ARMIA(40,0,TKORP)=150+POWER
				BITWA_SYMULOWANA(A,40);				//	            BITWA_SYMULOWANA[A,40]

				//!!! BLAD
				Add(MIASTA[B][0][M_LUDZIE],-(LUDZIE/4),20,MIASTA[B][0][M_LUDZIE]);//	            Add MIASTA(B,0,M_LUDZIE),-(LUDZIE/4),20 To MIASTA(B,0,M_LUDZIE)
				//!!! powinno byc
				//MIASTA[B][0][M_LUDZIE] -= (LUDZIE/4);
				//clipl(MIASTA[B][0][M_LUDZIE],20);

				POWER=OLDPOWER;								//	            POWER=OLDPOWER
				if( ARMIA[40][0][TE]==0 ) {		//	            If ARMIA(40,0,TE)=0
					if( PL==5 ) {								//	               If PL=5
						MIASTA[B][0][M_CZYJE]=0;	//	                  MIASTA(B,0,M_CZYJE)=0

						//!!! BLAD
						Add(MIASTA[B][0][M_LUDZIE],-(LUDZIE/2),20,MIASTA[B][0][M_LUDZIE]);//	                  Add MIASTA(B,0,M_LUDZIE),-(LUDZIE/2),20 To MIASTA(B,0,M_LUDZIE)
						//!!! powinno byc
						//MIASTA[B][0][M_LUDZIE] -= (LUDZIE/2);
						//clipl(MIASTA[B][0][M_LUDZIE],20);

						for(I=2;I<=10;++I) {			//	                  For I=2 To 10 : If Rnd(1)=1 : MIASTA(B,I,M_LUDZIE)=0 : End If : Next I
							if( Rnd(1)==1 ) MIASTA[B][I][M_LUDZIE]=0;
						}
						MESSAGE2(B,GS("055"),32,1,0);//	                  MESSAGE2[B,"Chaos Warriors have burned the town.",32,1,0]
						MB=8;											//	                  MB=8
					} else {										//	               Else
						MIASTA[B][0][M_CZYJE]=PL;	//	                  MIASTA(B,0,M_CZYJE)=PL
					}														//	               End If
					B_OFF(A);										//	               B_OFF[A] : Paste Bob MIASTA(B,0,M_X)-8,MIASTA(B,0,M_Y)-8,MB : Wait Vbl : B_DRAW[A,X1,Y1,BB]
					PasteBob( MIASTA[B][0][M_X]-8,MIASTA[B][0][M_Y]-8,MB );
					WaitVbl();
					B_DRAW(A,X1,Y1,BB);
					if( ARMIA[A][0][TMAGMA]==100 ) {//	               If ARMIA(A,0,TMAGMA)=100
						CENTER(X1,Y1,1);					//	                  CENTER[X1,Y1,1]
						MESSAGE2(A,GS("056")+A_S+" ",32,0,0);//	                  MESSAGE2[A,"has conquered "+A$+" ",32,0,0]
					}														//	               End If
				}															//	            End If
				if( ARMIA[A][0][TMAGMA]==100 ) {//	            If ARMIA(A,0,TMAGMA)=100
					if( ARMIA[A][0][TE]==0 ) {	//	               If ARMIA(A,0,TE)=0
						CENTER(X1,Y1,1);					//	                  CENTER[X1,Y1,1]
						MESSAGE2(A,GS("057")+A_S+" ",33,0,0);//	                  MESSAGE2[A,"was defeat when storming "+A$+" ",33,0,0]
					}														//	               End If
				}															//	            End If
			}	else {												//	         Else
				if( A>19 && PL2==1 ) {				//	            If A>19 and PL2=1
					OBRONA=-1;									//	               OBRONA=-1
					for(I=0;I<=19;++I) {				//	               For I=0 To 19
						if( ARMIA[I][0][TE]>0 && ARMIA[I][0][TNOGI]==70+B ) {//	                  If ARMIA(I,0,TE)>0 and ARMIA(I,0,TNOGI)=70+B
							OBRONA=I;								//	                     OBRONA=I
							I=19;										//	                     I=19
						}													//	                  End If
					}														//	               Next
					if( OBRONA>-1 ) {						//	               If OBRONA>-1
						CENTER(X1,Y1,1);					//	                  CENTER[X1,Y1,1]
						if( PL==5 )
							KON_S=GS("058");
						else
							KON_S=GS("059");
						MESSAGE(A,KON_S+GS("060")+A_S+" ",0,0);//	                  MESSAGE[A,"is attacking our town "+A$+" ",0,0]
						for(I=1;I<=10;++I) {			//	                  For I=1 To 10 : ARMIA(A,I,TAMO)=30 : Next I
							ARMIA[A][I][TAMO]=30;
						}
						BITWA(OBRONA,A,0,0,2,0,2,2,_TEREN,_MUR);//	                  BITWA[OBRONA,A,0,0,2,0,2,2,TEREN,MUR]

						//!!! BLAD
						Add(MIASTA[B][0][M_LUDZIE],-(LUDZIE/4),20,MIASTA[B][0][M_LUDZIE]);//	                  Add MIASTA(B,0,M_LUDZIE),-(LUDZIE/4),20 To MIASTA(B,0,M_LUDZIE)
						//!!! powinno byc
						//MIASTA[B][0][M_LUDZIE] -= (LUDZIE/4);
						//clipl(MIASTA[B][0][M_LUDZIE],20);

						CENTER(X1,Y1,0);					//	                  CENTER[X1,Y1,0]
						if( WYNIK_AKCJI!=1 ) {		//	                  If WYNIK_AKCJI<>1
							if( PL==5 ) {						//	                     If PL=5
								MIASTA[B][0][M_CZYJE]=0;//	                        MIASTA(B,0,M_CZYJE)=0

								//!!! BLAD
								Add(MIASTA[B][0][M_LUDZIE],-(LUDZIE/2),20,MIASTA[B][0][M_LUDZIE]);//	                        Add MIASTA(B,0,M_LUDZIE),-(LUDZIE/2),20 To MIASTA(B,0,M_LUDZIE)
								//!!! powinno byc
								//MIASTA[B][0][M_LUDZIE] -= (LUDZIE/2);
								//clipl(MIASTA[B][0][M_LUDZIE],20);

								for(I=2;I<=20;++I) {	//	                        For I=2 To 20 : If Rnd(2)=1 : MIASTA(B,I,M_LUDZIE)=0 : End If : Next I
									MIASTA[B][I][M_LUDZIE]=0;
								}
								MESSAGE2(B,GS("061"),32,1,0);//	                        MESSAGE2[B,"Chaos Warriors have conquered and burned the town.",32,1,0]
								MB=8;									//	                        MB=8
							} else {								//	                     Else
								MIASTA[B][0][M_CZYJE]=PL;//	                        MIASTA(B,0,M_CZYJE)=PL
								MESSAGE2(A,GS("062")+A_S+" ",30,0,0);//	                        MESSAGE2[A,"has conquered our town "+A$+" ",30,0,0]
							}												//	                     End If
							B_OFF(A);								//	                     B_OFF[A] : Paste Bob MIASTA(B,0,M_X)-8,MIASTA(B,0,M_Y)-8,MB : Wait Vbl : B_DRAW[A,X1,Y1,BB]
							PasteBob( MIASTA[B][0][M_X]-8,MIASTA[B][0][M_Y]-8,MB);
							WaitVbl();
							B_DRAW(A,X1,Y1,BB);
						}													//	                  End If
					} else {										//	               Else
						if( PL==5 ) {							//	                  If PL=5
							MIASTA[B][0][M_CZYJE]=0;//	                     MIASTA(B,0,M_CZYJE)=0

							//!!! BLAD
							Add(MIASTA[B][0][M_LUDZIE],-(LUDZIE/2),20,MIASTA[B][0][M_LUDZIE]);//	                        Add MIASTA(B,0,M_LUDZIE),-(LUDZIE/2),20 To MIASTA(B,0,M_LUDZIE)
							//!!! powinno byc
							//MIASTA[B][0][M_LUDZIE] -= (LUDZIE/2);
							//clipl(MIASTA[B][0][M_LUDZIE],20);

							for(I=2;I<=20;++I) {	//	                        For I=2 To 20 : If Rnd(2)=1 : MIASTA(B,I,M_LUDZIE)=0 : End If : Next I
								MIASTA[B][I][M_LUDZIE]=0;
							}
							MESSAGE2(B,GS("063"),32,1,0);//	                     MESSAGE2[B,"town has been burned ",32,1,0]
							MB=8;										//	                     MB=8
						} else {									//	                  Else
							MIASTA[B][0][M_CZYJE]=PL;//	                     MIASTA(B,0,M_CZYJE)=PL
							CENTER(X1,Y1,1);				//	                     CENTER[X1,Y1,1]
							MESSAGE(A,GS("064")+A_S+" ",0,0);//	                     MESSAGE[A,"has taken over our town "+A$+" ",0,0]
						}													//	                  End If
						B_OFF(A);									//	                  B_OFF[A] : Paste Bob MIASTA(B,0,M_X)-8,MIASTA(B,0,M_Y)-8,MB : Wait Vbl : B_DRAW[A,X1,Y1,BB]
						PasteBob( MIASTA[B][0][M_X]-8,MIASTA[B][0][M_Y]-8,MB );
						WaitVbl();
						B_DRAW(A,X1,Y1,BB);
					}														//	               End If
				} else {											//	            Else
					CENTER(X1,Y1,1);						//	               CENTER[X1,Y1,1]
					MESSAGE(A,GS("065")+A_S,0,0);//	               MESSAGE[A,"We're attacking "+A$,0,0]
					ILEDNI=Rnd(30)+10;					//	               ILEDNI=Rnd(30)+10
					WOJNA[PL][PL2]=ILEDNI;			//	               WOJNA(PL,PL2)=ILEDNI
					WOJNA[PL2][PL]=ILEDNI;			//	               WOJNA(PL2,PL)=ILEDNI
					OLDPOWER=POWER;							//	               OLDPOWER=POWER
					POWER=(MORALE/3)+10;				//	               POWER=(MORALE/3)+10
					NOWA_ARMIA(40,LWOJ,-1);			//	               NOWA_ARMIA[40,LWOJ,-1]
					for(I=1;I<=10;++I) {				//	               For I=1 To 10 : ARMIA(40,I,TAMO)=30 : Next I
						ARMIA[40][I][TAMO]=30;
					}
					BITWA(A,40,0,2,2,0,0,2,_TEREN,_MUR);//	               BITWA[A,40,0,2,2,0,0,2,TEREN,MUR]

					//!!! BLAD
					Add(MIASTA[B][0][M_LUDZIE],-(LUDZIE/4),20,MIASTA[B][0][M_LUDZIE]);//	               Add MIASTA(B,0,M_LUDZIE),-(LUDZIE/4),20 To MIASTA(B,0,M_LUDZIE)
					//!!! powinno byc
					//MIASTA[B][0][M_LUDZIE] -= (LUDZIE/4);
					//clipl(MIASTA[B][0][M_LUDZIE],20);

					POWER=OLDPOWER;							//	               POWER=OLDPOWER
					CENTER(X1,Y1,0);						//	               CENTER[X1,Y1,0]
					if( ARMIA[40][0][TE]==0 ) {	//	               If ARMIA(40,0,TE)=0
						MIASTA[B][0][M_CZYJE]=PL;	//	                  MIASTA(B,0,M_CZYJE)=PL
						B_OFF(A);									//	                  B_OFF[A] : Paste Bob MIASTA(B,0,M_X)-8,MIASTA(B,0,M_Y)-8,MB : Wait Vbl : B_DRAW[A,X1,Y1,BB]
						PasteBob( MIASTA[B][0][M_X]-8,MIASTA[B][0][M_Y]-8,MB );
						WaitVbl();
						B_DRAW(A,X1,Y1,BB);
						for(J=1;J<=19;++J) {			//	                  For J=1 To 19 : MIASTA(B,J,M_MUR)=Rnd(20) : Next J
							MIASTA[B][J][M_MUR]=Rnd(20);
						}
						MESSAGE2(A,GS("066")+A_S+" ",30,0,0);	//	                  MESSAGE2[A,"We've conquered the "+A$+" ",30,0,0]
					}														//	               End If
					if( ARMIA[A][0][TE]==0 ) {	//	               If ARMIA(A,0,TE)=0
						MESSAGE2(A,GS("067")+A_S+" ",33,0,0);//	                  MESSAGE2[A,"was defeat when storming "+A$+" ",33,0,0]
					}														//	               End If
				}															//	            End If
			}																//	         End If
		}																	//	      End If
		ARMIA[A][0][TTRYB]=0;							//	      ARMIA(A,0,TTRYB)=0
		BUSY_ANIM();											//	      BUSY_ANIM
																			//
	} else {														//	   Else
																			//	      '      MA_WYPADEK[A,7] : Goto OVER
		if( A<20 && SKIP==0 ) {						//	      If A<20 and SKIP=0
			if( LOK==7 ) {									//	         If LOK=7
				if( Rnd(3)==1 ) MA_WYPADEK(A,3);//	            If Rnd(3)=1 : MA_WYPADEK[A,3] : End If
			}																//	         End If
			if( LOK==5 ) {									//	         If LOK=5
				if( Rnd(6)==1 ) MA_WYPADEK(A,1);//	            If Rnd(6)=1 : MA_WYPADEK[A,1] : End If
			}																//	         End If
			if( LOK==1 ) {									//	         If LOK=1
				P=Rnd(45);										//	            P=Rnd(45)
				if( P<4 ) MA_WYPADEK(A,4+P);	//	            If P<4 : MA_WYPADEK[A,4+P] : End If
				if( P==5 ) MA_WYPADEK(A,2);		//	            If P=5 : MA_WYPADEK[A,2] : End If
			}																//	         End If
			if( LOK==2 ) {									//	         If LOK=2
				P=Rnd(45);										//	            P=Rnd(45)
				if( P==1 ) MA_WYPADEK(A,2);		//	            If P=1 : MA_WYPADEK[A,2] : End If
				if( P==2 ) MA_WYPADEK(A,6);		//	            If P=2 : MA_WYPADEK[A,6] : End If
			}																//	         End If
			if( LOK==3 ) {									//	         If LOK=3
				P=Rnd(45);										//	            P=Rnd(45)
				if( P==1 ) MA_WYPADEK(A,2);		//	            If P=1 : MA_WYPADEK[A,2] : End If
			}																//	         End If
			if( LOK==4 ) {									//	         If LOK=4
				P=Rnd(45);										//	            P=Rnd(45)
				if( P==1 ) MA_WYPADEK(A,2);		//	            If P=1 : MA_WYPADEK[A,2] : End If
				if( P==5 ) MA_WYPADEK(A,7);		//	            If P=5 : MA_WYPADEK[A,7] : End If
			}																//	         End If
																			//
		}																	//	      End If
	}																		//	   End If
	OVER:																//	   OVER:
		;																	//	End Proc
}
void MA_POLOWANIE(aint A) {
	//	Procedure MA_POLOWANIE[A]

	aint _TEREN=0,WOJ=0,R=0,ILE=0,RSA=0,LOS=0,X=0,Y=0,I=0;
	astr PO_S="";

	_TEREN=ARMIA[A][0][TNOGI];				//	   TEREN=ARMIA(A,0,TNOGI)
	ARMIA[A][0][TLEWA]=1;							//	   ARMIA(A,0,TLEWA)=1
	ARMIA[A][0][TPRAWA]=1;						//	   ARMIA(A,0,TPRAWA)=1
	WOJ=ARMIA[A][0][TE];							//	   WOJ=ARMIA(A,0,TE)
	if( _TEREN<70 && A<20 ) {					//	   If TEREN<70 and A<20
		ARMIA[A][0][TAMO] -= WOJ;				//	      Add ARMIA(A,0,TAMO),-WOJ
	}																	//	   End If
	R=Rnd(13);												//	   R=Rnd(13)
	ILE=Rnd(9)+1;											//	   ILE=Rnd(9)+1
	if( R<5 ) {												//	   If R<5 : PO$="dzik" : RSA=13 : End If
		PO_S="dzik"; RSA=13;
	}
	if( R>4 && R<8 ) {								//	   If R>4 and R<8 : PO$="wilk" : RSA=12 : End If
		PO_S="wilk"; RSA=12;
	}
	if( R==8 || R==9 ) {							//	   If R=8 or R=9 : PO$="gargoil" : RSA=10 : ILE=Rnd(3)+1 : End If
		PO_S="gargoil"; RSA=10;
		ILE=Rnd(3)+1;
	}
	if( R==10 ) {											//	   If R=10 : PO$="skirial" : RSA=16 : ILE=Rnd(5)+1 : End If
		PO_S="skirial"; RSA=16;
		ILE=Rnd(5)+1;
	}
	if( R>10 ) {											//	   If R>10 : PO$="warpun" : RSA=15 : End If
		PO_S="warpun"; RSA=15;
	}
																		//	   If TEREN=1 : LOS=1 : End If
																		//	   If TEREN=2 : LOS=2 : End If
																		//	   If TEREN=3 : LOS=6 : End If
																		//	   If TEREN=4 : LOS=5 : End If
																		//	   If TEREN=5 : LOS=4 : End If
																		//	   If TEREN=7 : LOS=3 : PO$="gloom" : RSA=14 : End If
	LOS=32000;
	switch( _TEREN ) {
		case 1:	LOS=1; break;
		case 2: LOS=2; break;
		case 3: LOS=6; break;
		case 4: LOS=5; break;
		case 5: LOS=4; break;
		case 7: LOS=3; PO_S="gloom"; RSA=14; break;
	}
	if( Rnd(LOS)==1 ) {								//	   If Rnd(LOS)=1
		AmalOnOff(0,false);							//	      Amal Off 0
																		//	      Show On
		X=ARMIA[A][0][TX];							//	      X=ARMIA(A,0,TX)
		Y=ARMIA[A][0][TY];							//	      Y=ARMIA(A,0,TY)
		CENTER(X,Y,1);									//	      CENTER[X,Y,1]
		MESSAGE(A,GS("068"),0,0);//	      MESSAGE[A,"We have tracked down a beast !",0,0]
		ARM=A; WRG=40;									//	      ARM=A : WRG=40
		SpriteOnOff(2,false);						//	      Sprite Off 2
		SETUP("",GS("069"),"");					//	      SETUP["","Hunting",""]
		for(I=1;I<=10;++I) {						//	      For I=1 To 10 : ARMIA(40,I,TE)=0 : Next
			ARMIA[40][I][TE]=0;
		}
		POTWOR(40,PO_S,ILE,RSA);				//	      POTWOR[40,PO$,ILE,RSA]
		RYSUJ_SCENERIE(_TEREN,-1);			//	      RYSUJ_SCENERIE[TEREN,-1]
		X=Rnd(2); Y=Rnd(2);							//	      X=Rnd(2) : Y=Rnd(2)
		USTAW_WOJSKO(ARM,X,Y,0);				//	      USTAW_WOJSKO[ARM,X,Y,0]
		USTAW_WOJSKO(WRG,X,Y,1);				//	      USTAW_WOJSKO[WRG,X,Y,1]
		MAIN_ACTION();									//	      MAIN_ACTION
		for(I=1;I<=10;++I) {						//	      For I=1 To 10 : ARMIA(40,I,TE)=0 : Next
			ARMIA[40][I][TE]=0;
		}
		ARMIA[A][0][TTRYB]=0;						//	      ARMIA(A,0,TTRYB)=0
		SETUP0();												//	      SETUP0
		VISUAL_OBJECTS();								//	      VISUAL_OBJECTS
		Sprite(2,SPX,SPY,1);						//	      Sprite 2,SPX,SPY,1
		CENTER(ARMIA[A][0][TX],ARMIA[A][0][TY],0);//	      CENTER[ARMIA(A,0,TX),ARMIA(A,0,TY),0]
		BUSY_ANIM();										//	      BUSY_ANIM
																		//
	}																	//	   End If
																		//	End Proc
}
void MA_OBOZ(aint A) {
	//	Procedure MA_OBOZ[A]

	aint WOJ=0,_TEREN=0,I=0,MAGIA=0,M_MAX=0,EN=0,ENM=0;

	WOJ=ARMIA[A][0][TE];			//	   WOJ=ARMIA(A,0,TE)
	_TEREN=ARMIA[A][0][TNOGI];//	   TEREN=ARMIA(A,0,TNOGI)
	ARMIA[A][0][TLEWA]=1;			//	   ARMIA(A,0,TLEWA)=1
	ARMIA[A][0][TPRAWA]=1;		//	   ARMIA(A,0,TPRAWA)=1
	if( _TEREN<70 && A<20 ) {	//	   If TEREN<70 and A<20
		ARMIA[A][0][TAMO] -= WOJ;	//	      Add ARMIA(A,0,TAMO),-WOJ
	}													//	   End If
	for(I=1;I<=10;++I) {			//	   For I=1 To 10
		MAGIA=ARMIA[A][I][TMAG];//	      MAGIA=ARMIA(A,I,TMAG)
		M_MAX=ARMIA[A][I][TMAGMA];//	      M_MAX=ARMIA(A,I,TMAGMA)

		//!!! BLAD
		Add(MAGIA,Rnd(5)+5,MAGIA,M_MAX);//	      Add MAGIA,Rnd(5)+5,MAGIA To M_MAX
		//!!! powinno byc
		//MAGIA+=Rnd(5)+5;
		//clipu(MAGIA,M_MAX);

		ARMIA[A][I][TMAG]=MAGIA;//	      ARMIA(A,I,TMAG)=MAGIA
		EN=ARMIA[A][I][TE];			//	      EN=ARMIA(A,I,TE)
		ENM=ARMIA[A][I][TEM];		//	      ENM=ARMIA(A,I,TEM)
		if( EN>0 && EN<ENM ) {	//	      If EN>0 and EN<ENM

			//!!! BLAD
			Add(EN,Rnd(20)+10,EN,ENM);//	         Add EN,Rnd(20)+10,EN To ENM
			//!!! powinno byc
			//EN+=Rnd(20)+10;
			//clipu(EN,ENM);

			ARMIA[A][I][TE]=EN;		//	         ARMIA(A,I,TE)=EN
		}												//	      End If
	}													//	   Next
														//	End Proc
}
void MA_PRZYGODA(aint A,aint NR) {
																																		//	Procedure MA_PRZYGODA[A,NR]
  aint _TEREN=0, TYP=0, M=0, POT=0, ILE=0, I=0, IMAX=0, X=0, Y=0,
			 BB=0, CO=0, XB=0, YB=0, B=0, POS=0, MAGIA=0, ENERGIA=0,
			 SILA=0, SZYBKOSC=0, _DOS=0, SZBKOSC=0;
  astr A_S="", PO_S="";

	AmalOnOff(0,false);																								//	   Amal Off 0
																																		//	   Show On
	_TEREN=PRZYGODY[NR][P_TEREN];																			//	   TEREN=PRZYGODY(NR,P_TEREN)
	TYP=PRZYGODY[NR][P_TYP];																					//	   TYP=PRZYGODY(NR,P_TYP)
	A_S=PRZYGODY_S[TYP][7];																						//	   A$=PRZYGODY$(TYP,7)
	if( TESTING==0 ) {																								//	   If Not TESTING
		MESSAGE(A,A_S,NR,0); SpriteOnOff(2,false);											//	      MESSAGE[A,A$,NR,0] : Sprite Off 2
	}																																	//	   End If
																																		//	   'ûadnych komunikatów po akcji 0 armie lub 1 miasta
	M=-1;																															//	   M=-1
	ARM=A; WRG=40;																										//	   ARM=A : WRG=40
	TRWA_PRZYGODA=NR;																									//	   TRWA_PRZYGODA=NR
	SETUP(GS("70"),GS("071"),GS("072"));																						//	   SETUP["","Action",""]
	if( TYP==1 ) {																										//	   If TYP=1
		//---kopalnia koboldy---																				//	      'kopalnia koboldy
		if( Rnd(1)==0 ) {																								//	      If Rnd(1)=0
			POT=16; ILE=3; PO_S="skirial";																//	         POT=16 : ILE=3 : PO$="skirial"
		} else {																												//	      Else
			POT=18; ILE=5; PO_S="pajâk";																	//	         POT=18 : ILE=5 : PO$="pajâk"
		}																																//	      End If
		POTWOR(40,PO_S,ILE,POT);																				//	      POTWOR[40,PO$,ILE,POT]
		for( I=ILE+1; I<=10; ++I ) { NOWA_POSTAC(40,I,3); }							//	      For I=ILE+1 To 10 : NOWA_POSTAC[40,I,3] : Next I
		for( I=1; I<=10; ++I ) { ARMIA[WRG][I][TPRAWA]=-1; }						//	      For I=1 To 10 : ARMIA(WRG,I,TPRAWA)=-1 : Next I
		RYSUJ_SCENERIE(_TEREN,-1);																			//	      RYSUJ_SCENERIE[TEREN,-1]
			//dosypujemy skarbow																					//	      'dosypujemy trochë skarbów
		IMAX=Rnd(8)+8;
		for( I=1; I<=IMAX; ++I ) {																			//	      For I=1 To Rnd(8)+8
			X=Rnd(29)+70; Y=Rnd(3);																				//	         X=Rnd(29)+70 : Y=Rnd(3)
			BB=BIBY+12;																										//	         BB=BIBY+12
			CO=Rnd(3)+80;																									//	         CO=Rnd(3)+80
			if( Rnd(3)==1 ) {																							//	         If Rnd(3)=1
				CO=Rnd(MX_WEAPON);																					//	            CO=Rnd(MX_WEAPON)
				BB=BIBY+11;																									//	            BB=BIBY+11
			}																															//	         End If
			GLEBA[X][Y]=CO;																								//	         GLEBA(X,Y)=CO
			XB=(X%10)*64+Rnd(30);																					//	         XB=(X mod 10)*64+Rnd(30)
			YB=(X/10)*50+Rnd(20);																					//	         YB=(X/10)*50+Rnd(20)
			PBListOnoff(true);
			PasteBob(XB,YB,BB);																						//	         Paste Bob XB,YB,BB
			PBListOnoff(false);
		};																															//	      Next I
		for( I=1; I<=10; ++I) { ARMIA[WRG][I][TKORP]=180; }							//	      For I=1 To 10 : ARMIA(WRG,I,TKORP)=180 : Next I
		USTAW_WOJSKO(ARM,1,0,0);																				//	      USTAW_WOJSKO[ARM,1,0,0]
		USTAW_WOJSKO(WRG,1,2,2);																				//	      USTAW_WOJSKO[WRG,1,2,2]
		MAIN_ACTION();																									//	      MAIN_ACTION
	}																																	//	   End If
	if( TYP==2 || TYP==8 ) {																					//	   If TYP=2 or TYP=8
		//---grobowiec upiory---																				//	      'grobowiec upiory
		if( Rnd(1)==0 ) {																								//	      If Rnd(1)=0
			POT=17; ILE=9; PO_S="humanoid";																//	         POT=17 : ILE=9 : PO$="humanoid"
		} else {																												//	      Else
			POT=18; ILE=9; PO_S="pajâk";																	//	         POT=18 : ILE=9 : PO$="pajâk"
		}																																//	      End If
		POTWOR(40,PO_S,ILE,POT);																				//	      POTWOR[40,PO$,ILE,POT]
		for( I=1; I<=10; ++I) { ARMIA[WRG][I][TKORP]=180; }							//	      For I=1 To 10 : ARMIA(WRG,I,TKORP)=180 : Next I
		NOWA_POSTAC(WRG,10,9);																					//	      NOWA_POSTAC[WRG,10,9]
		ARMIA[WRG][10][TKORP]=40;																				//	      ARMIA(WRG,10,TKORP)=40
		ARMIA[WRG][10][TPRAWA]=-1;																			//	      ARMIA(WRG,10,TPRAWA)=-1
		RYSUJ_SCENERIE(_TEREN,-1);																			//	      RYSUJ_SCENERIE[TEREN,-1]
																																		//	      'umieszczenie skarbu
																																		//
		SEKTOR(460+12,28+22);																						//	      SEKTOR[460+12,28+22]
		GLEBA[Param][0]=PRZYGODY[NR][P_BRON];														//	      GLEBA(Param,0)=PRZYGODY(NR,P_BRON)
		for( I=1; I<=3; ++I ) { GLEBA[Param][I]=80; }										//	      For I=1 To 3 : GLEBA(Param,I)=80 : Next I
		PBListOnoff(true);
		PasteBob(460,28,BIBY+11);																				//	      Paste Bob 460,28,BIBY+11
		PBListOnoff(false);
																																		//
		USTAW_WOJSKO(ARM,0,2,0);																				//	      USTAW_WOJSKO[ARM,0,2,0]
		USTAW_WOJSKO(WRG,0,2,1);																				//	      USTAW_WOJSKO[WRG,0,2,1]
		MAIN_ACTION();																									//	      MAIN_ACTION
	}																																	//	   End If
	if( TYP==3 ) {																										//	   If TYP=3
		//---bandyci---																									//	      'bandyci
		POT=-1; ILE=Rnd(5)+5;																						//	      POT=-1 : ILE=Rnd(5)+5
		NOWA_ARMIA(40,ILE,POT);																					//	      NOWA_ARMIA[40,ILE,POT]
		for( I=1; I<=ILE; ++I ) { ARMIA[WRG][I][TPRAWA]=-1; }						//	      For I=1 To ILE : ARMIA(WRG,I,TPRAWA)=-1 : Next I
		RYSUJ_SCENERIE(_TEREN,-1);																			//	      RYSUJ_SCENERIE[TEREN,-1]
																																		//	      'silna i doôwiadczona zaîoga show no mercy and kill them all
		for( I=1; I<=10; ++I ) { ARMIA[WRG][I][TKORP]=250; }						//	      For I=1 To 10 : ARMIA(WRG,I,TKORP)=250 : Next I
		for( I=1; I<=10; ++I ) { ARMIA[WRG][I][TDOSW]=Rnd(25); }				//	      For I=1 To 10 : ARMIA(WRG,I,TDOSW)=Rnd(25) : Next I
		USTAW_WOJSKO(ARM,1,1,1);																				//	      USTAW_WOJSKO[ARM,1,1,1]
		USTAW_WOJSKO(WRG,1,1,0);																				//	      USTAW_WOJSKO[WRG,1,1,0]
		MAIN_ACTION();																									//	      MAIN_ACTION
		if( WYNIK_AKCJI==1 ) {																					//	      If WYNIK_AKCJI=1
			M=0;																													//	         M=0
			CO=ARM;																												//	         CO=ARM
			A_S=GS("073")+Str_S(PRZYGODY[NR][P_NAGRODA])+GS("074");				//	         A$="You're getting "+Str$(PRZYGODY(NR,P_NAGRODA))+" gold pieces as a reward."
			B=41;																													//	         B=41
			GRACZE[1][1]+=PRZYGODY[NR][P_NAGRODA];												//	         Add GRACZE(1,1),PRZYGODY(NR,P_NAGRODA)
		}																																//	      End If
	}																																	//	   End If
	if( TYP==4 ) {																										//	   If TYP=4
		//---córka króla---																							//	      'córka króla
		POT=-1; ILE=9;																									//	      POT=-1 : ILE=9
		POS=4;																													//	      POS=4
		NOWA_ARMIA(40,ILE,POT);																					//	      NOWA_ARMIA[40,ILE,POT]
		RYSUJ_SCENERIE(_TEREN,-1);																			//	      RYSUJ_SCENERIE[TEREN,-1]
		for( I=1; I<=10; ++I ) { ARMIA[WRG][I][TKORP]=170; }						//	      For I=1 To 10 : ARMIA(WRG,I,TKORP)=170 : Next I
		NOWA_POSTAC(WRG,10,POS);																				//	      NOWA_POSTAC[WRG,10,POS]
		ARMIA[WRG][10][TKORP]=40;																				//	      ARMIA(WRG,10,TKORP)=40
		ARMIA[WRG][10][TPRAWA]=-1;																			//	      ARMIA(WRG,10,TPRAWA)=-1
		USTAW_WOJSKO(ARM,1,2,0);																				//	      USTAW_WOJSKO[ARM,1,2,0]
		USTAW_WOJSKO(WRG,1,0,0);																				//	      USTAW_WOJSKO[WRG,1,0,0]
		MAIN_ACTION();																									//	      MAIN_ACTION
		if( WYNIK_AKCJI==1 && ARMIA[WRG][10][TE]>0 ) {									//	      If WYNIK_AKCJI=1 and ARMIA(WRG,10,TE)>0
			CO=PRZYGODY[NR][P_NAGRODA]; M=1; B=30;												//	         CO=PRZYGODY(NR,P_NAGRODA) : M=1 : B=30
			A_S=GS("075");																								//	         A$="is yours as a reward."
			MIASTA[CO][0][M_CZYJE]=1;																			//	         MIASTA(CO,0,M_CZYJE)=1
		}																																//	      End If
	}																																	//	   End If
	if( TYP==5 ) {																										//	   If TYP=5
		//---góra szczerbiec---																					//	      'góra szczerbiec
		POTWOR(WRG,"skirial",5,16);																			//	      POTWOR[WRG,"skirial",5,16]
		RYSUJ_SCENERIE(_TEREN,-1);																			//	      RYSUJ_SCENERIE[TEREN,-1]
		GLEBA[5][Rnd(3)]=7;																							//	      GLEBA(5,Rnd(3))=7
		PBListOnoff(true);
		PasteBob(330,12,BIBY+11);																				//	      Paste Bob 330,12,BIBY+11
		PBListOnoff(false);
		for( I=1; I<=10; ++I ) { ARMIA[WRG][I][TKORP]=170; }						//	      For I=1 To 10 : ARMIA(WRG,I,TKORP)=170 : Next I
		USTAW_WOJSKO(ARM,1,2,0);																				//	      USTAW_WOJSKO[ARM,1,2,0]
		USTAW_WOJSKO(WRG,1,0,2);																				//	      USTAW_WOJSKO[WRG,1,0,2]
		MAIN_ACTION();																									//	      MAIN_ACTION
	}																																	//	   End If
	if( TYP==6 ) {																										//	   If TYP=6
		//---super mag i wilki---																				//	      'super mag i wilki
		POTWOR(WRG,"wilk",9,12);																				//	      POTWOR[WRG,"wilk",9,12]
		NOWA_POSTAC(WRG,10,8);																					//	      NOWA_POSTAC[WRG,10,8]
		MAGIA=50+Rnd(50); ENERGIA=30+Rnd(40); SILA=20+Rnd(10); SZYBKOSC=10+Rnd(10); _DOS=50;																																	//	      MAGIA=50+Rnd(50) : ENERGIA=30+Rnd(40) : SILA=20+Rnd(10) : SZYBKOSC=10+Rnd(10) : _DOS=50
		RYSUJ_SCENERIE(_TEREN,-1);																			//	      RYSUJ_SCENERIE[TEREN,-1]
		for( I=1; I<=10; ++I ) { ARMIA[WRG][I][TKORP]=170; }						//	      For I=1 To 10 : ARMIA(WRG,I,TKORP)=170 : Next I
		ARMIA_S[WRG][10]=IM_PRZYGODY_S[NR];															//	      ARMIA$(WRG,10)=IM_PRZYGODY$(NR)
		ARMIA[WRG][10][TGLOWA]=1;																				//	      ARMIA(WRG,10,TGLOWA)=1
		ARMIA[WRG][10][TKORP]=40;																				//	      ARMIA(WRG,10,TKORP)=40
		ARMIA[WRG][10][TEM]+=ENERGIA;																		//	      Add ARMIA(WRG,10,TEM),ENERGIA
		ARMIA[WRG][10][TSI]+=SILA;																			//	      Add ARMIA(WRG,10,TSI),SILA
		//!!! blad - literowka w nazwie zmiennej
		ARMIA[WRG][10][TSZ]+=SZBKOSC;																		//	      Add ARMIA(WRG,10,TSZ),SZBKOSC
		ARMIA[WRG][10][TMAGMA]+=MAGIA;																	//	      Add ARMIA(WRG,10,TMAGMA),MAGIA
		ARMIA[WRG][10][TDOSW]+=_DOS;																		//	      Add ARMIA(WRG,10,TDOSW),_DOS
																																		//	      'bëdzie gadaî
		ARMIA[WRG][10][TPRAWA]=-1;																			//	      ARMIA(WRG,10,TPRAWA)=-1
		USTAW_WOJSKO(ARM,0,1,0);																				//	      USTAW_WOJSKO[ARM,0,1,0]
		USTAW_WOJSKO(WRG,2,1,0);																				//	      USTAW_WOJSKO[WRG,2,1,0]
		MAIN_ACTION();																									//	      MAIN_ACTION
	}																																	//	   End If
	if( TYP==7 ) {																										//	   If TYP=7
		//---super paladyn i szkielety---																//	      'super paladyn i szkielety
		POTWOR(WRG,"szkielet",9,11);																		//	      POTWOR[WRG,"szkielet",9,11]
		NOWA_POSTAC(WRG,10,7);																					//	      NOWA_POSTAC[WRG,10,7]
		RYSUJ_SCENERIE(_TEREN,-1);																			//	      RYSUJ_SCENERIE[TEREN,-1]
		for( I=1; I<=10; ++I ) { ARMIA[WRG][I][TKORP]=240; }						//	      For I=1 To 10 : ARMIA(WRG,I,TKORP)=240 : Next I
		MAGIA=20+Rnd(20); ENERGIA=60+Rnd(50); SILA=20+Rnd(20); SZYBKOSC=20+Rnd(20); _DOS=80;//	      MAGIA=20+Rnd(20) : ENERGIA=60+Rnd(50) : SILA=20+Rnd(20) : SZYBKOSC=20+Rnd(20) : _DOS=80
		ARMIA[WRG][10][TKORP]=35;																				//	      ARMIA(WRG,10,TKORP)=35
		ARMIA_S[WRG][10]=IM_PRZYGODY_S[NR];															//	      ARMIA$(WRG,10)=IM_PRZYGODY$(NR)
		ARMIA[WRG][10][TEM]+=ENERGIA;																		//	      Add ARMIA(WRG,10,TEM),ENERGIA
		ARMIA[WRG][10][TSI]+=SILA;																			//	      Add ARMIA(WRG,10,TSI),SILA
		//!!! blad - literowka w nazwie zmiennej
		ARMIA[WRG][10][TSZ]+=SZBKOSC;																		//	      Add ARMIA(WRG,10,TSZ),SZBKOSC
		ARMIA[WRG][10][TMAGMA]+=MAGIA;																	//	      Add ARMIA(WRG,10,TMAGMA),MAGIA
		ARMIA[WRG][10][TDOSW]+=_DOS;																		//	      Add ARMIA(WRG,10,TDOSW),_DOS
		ARMIA[WRG][10][TPRAWA]=-1;																			//	      ARMIA(WRG,10,TPRAWA)=-1
		USTAW_WOJSKO(ARM,1,0,0);																				//	      USTAW_WOJSKO[ARM,1,0,0]
		USTAW_WOJSKO(WRG,1,2,2);																				//	      USTAW_WOJSKO[WRG,1,2,2]
		MAIN_ACTION();																									//	      MAIN_ACTION
	}																																	//	   End If
																																		//
	if( TYP==9 ) {																										//	   If TYP=9
		//---swiatynia orkow---																					//	      'ôwiâtynia orków
		NOWA_ARMIA(40,10,1);																						//	      NOWA_ARMIA[40,10,1]
		for( I=1; I<=10; ++I ) { ARMIA[WRG][I][TPRAWA]=-1; }						//	      For I=1 To 10 : ARMIA(WRG,I,TPRAWA)=-1 : Next I
		for( I=1; I<=10; ++I ) { ARMIA[WRG][I][TKORP]=180; }						//	      For I=1 To 10 : ARMIA(WRG,I,TKORP)=180 : Next I
		RYSUJ_SCENERIE(_TEREN,-1);																			//	      RYSUJ_SCENERIE[TEREN,-1]
		WIDOCZNOSC=250;																									//	      WIDOCZNOSC=250
																																		//	      'umieszczenie trupów
		PBListOnoff(true);
		for( Y=0; Y<=20; ++Y ) {																				//	      For Y=0 To 20
			for( X=0; X<=10; ++X ) {																			//	         For X=O To 10
				XB=X*60; YB=Y*25;																						//	            XB=X*60 : YB=Y*25
				if( Rnd(8)==1 && _Zone(XB+10,YB+10)==0 ) {									//	            If Rnd(8)=1 and Zone(XB+10,YB+10)=0
					BB=Rnd(9)*16+18+63+16;																		//	               BB=Rnd(9)*16+18+63+16
					PasteBob(XB+10,YB+10,BB);																	//	               Paste Bob XB+10,YB+10,BB
				}																														//	            End If
			}																															//	         Next X
		}																																//	      Next Y
		PBListOnoff(false);
		USTAW_WOJSKO(ARM,1,2,0);																				//	      USTAW_WOJSKO[ARM,1,2,0]
		USTAW_WOJSKO(WRG,1,2,1);																				//	      USTAW_WOJSKO[WRG,1,2,1]
		MAIN_ACTION();																									//	      MAIN_ACTION
	}																																	//	   End If
																																		//
	if( TYP==10 ) {																										//	   If TYP=10
		//---barbarzyïca na bagnach---																	//	      'barbarzyïca na bagnach
		MAGIA=10+Rnd(20); ENERGIA=40+Rnd(40); SILA=20+Rnd(20); SZYBKOSC=10+Rnd(10); _DOS=60;//	      MAGIA=10+Rnd(20) : ENERGIA=40+Rnd(40) : SILA=20+Rnd(20) : SZYBKOSC=10+Rnd(10) : _DOS=60
		POTWOR(40,"gloom",9,14);																				//	      POTWOR[40,"gloom",9,14]
		RYSUJ_SCENERIE(_TEREN,-1);																			//	      RYSUJ_SCENERIE[TEREN,-1]
		for( I=1; I<=10; ++I ) { ARMIA[WRG][I][TKORP]=170; }						//	      For I=1 To 10 : ARMIA(WRG,I,TKORP)=170 : Next I
		NOWA_POSTAC(WRG,10,0);																					//	      NOWA_POSTAC[WRG,10,0]
		ARMIA_S[WRG][10]=IM_PRZYGODY_S[NR];															//	      ARMIA$(WRG,10)=IM_PRZYGODY$(NR)
		ARMIA[WRG][10][TGLOWA]=1;																				//	      ARMIA(WRG,10,TGLOWA)=1
		ARMIA[WRG][10][TKORP]=40;																				//	      ARMIA(WRG,10,TKORP)=40
		ARMIA[WRG][10][TEM]+=ENERGIA;																		//	      Add ARMIA(WRG,10,TEM),ENERGIA
		ARMIA[WRG][10][TSI]+=SILA;																			//	      Add ARMIA(WRG,10,TSI),SILA
		//!!! blad - literowka w nazwie zmiennej
		ARMIA[WRG][10][TSZ]+=SZBKOSC;																		//	      Add ARMIA(WRG,10,TSZ),SZBKOSC
		ARMIA[WRG][10][TMAGMA]+=MAGIA;																	//	      Add ARMIA(WRG,10,TMAGMA),MAGIA
		ARMIA[WRG][10][TDOSW]+=_DOS;																		//	      Add ARMIA(WRG,10,TDOSW),_DOS
																																		//	      'bëdzie gadaî
		ARMIA[WRG][10][TPRAWA]=-1;																			//	      ARMIA(WRG,10,TPRAWA)=-1
		USTAW_WOJSKO(ARM,0,1,0);																				//	      USTAW_WOJSKO[ARM,0,1,0]
		USTAW_WOJSKO(WRG,2,1,0);																				//	      USTAW_WOJSKO[WRG,2,1,0]
		MAIN_ACTION();																									//	      MAIN_ACTION
	}																																	//	   End If
																																		//
	if( TYP==11 ) {																										//	   If TYP=11
		//---wataha z gargoilami---																			//	      'wataha z gargoilami
		POTWOR(WRG,"gargoil",2,10);																			//	      POTWOR[WRG,"gargoil",2,10]
		IMAX=5+Rnd(4);
		for( I=3; I<=IMAX; ++I ) { NOWA_POSTAC(WRG,I,Rnd(8)); }					//	      For I=3 To 5+Rnd(4) : NOWA_POSTAC[WRG,I,Rnd(8)] : Next I
		RYSUJ_SCENERIE(_TEREN,-1);																			//	      RYSUJ_SCENERIE[TEREN,-1]
																																		//	      'umieszczenie trupów
		PBListOnoff(true);
		for( Y=0; Y<=20; ++Y ) {																				//	      For Y=0 To 20
			for( X=0; X<=10; ++X ) {																			//	         For X=O To 10
				XB=X*60; YB=Y*25;																						//	            XB=X*60 : YB=Y*25
				if( Rnd(8)==1 && _Zone(XB+10,YB+10)==0 ) {									//	            If Rnd(8)=1 and Zone(XB+10,YB+10)=0
					BB=Rnd(9)*16+18+63+16;																		//	               BB=Rnd(9)*16+18+63+16
					PasteBob(XB+10,YB+10,BB);																	//	               Paste Bob XB+10,YB+10,BB
				}																														//	            End If
			}																															//	         Next X
		}																																//	      Next Y
		PBListOnoff(true);
																																		//	      'silna i doôwiadczona zaîoga show no mercy and kill them all
		for( I=1; I<=10; ++I ) { ARMIA[WRG][I][TKORP]=250; }						//	      For I=1 To 10 : ARMIA(WRG,I,TKORP)=250 : Next I
		for( I=1; I<=10; ++I ) { ARMIA[WRG][I][TDOSW]=Rnd(25); }				//	      For I=1 To 10 : ARMIA(WRG,I,TDOSW)=Rnd(25) : Next I
																																		//	      'tworzenie bossa
		MAGIA=10+Rnd(20); ENERGIA=40+Rnd(40); SILA=20+Rnd(20); SZYBKOSC=10+Rnd(10); _DOS=60;//	      MAGIA=10+Rnd(20) : ENERGIA=40+Rnd(40) : SILA=20+Rnd(20) : SZYBKOSC=10+Rnd(10) : _DOS=60
		NOWA_POSTAC(WRG,10,PRZYGODY[NR][P_BRON]);												//	      NOWA_POSTAC[WRG,10,PRZYGODY(NR,P_BRON)]
		ARMIA_S[WRG][10]=IM_PRZYGODY_S[NR];															//	      ARMIA$(WRG,10)=IM_PRZYGODY$(NR)
		ARMIA[WRG][10][TGLOWA]=1;																				//	      ARMIA(WRG,10,TGLOWA)=1
		ARMIA[WRG][10][TKORP]=170;																			//	      ARMIA(WRG,10,TKORP)=170
		ARMIA[WRG][10][TEM]+=ENERGIA;																		//	      Add ARMIA(WRG,10,TEM),ENERGIA
		ARMIA[WRG][10][TE]+=ENERGIA;																		//	      Add ARMIA(WRG,10,TE),ENERGIA
		ARMIA[WRG][10][TSI]+=SILA;																			//	      Add ARMIA(WRG,10,TSI),SILA
		//!!! blad - literowka w nazwie zmiennej
		ARMIA[WRG][10][TSZ]+=SZBKOSC;																		//	      Add ARMIA(WRG,10,TSZ),SZBKOSC
		ARMIA[WRG][10][TMAG]+=MAGIA;																		//	      Add ARMIA(WRG,10,TMAG),MAGIA
		ARMIA[WRG][10][TDOSW]+=_DOS;																		//	      Add ARMIA(WRG,10,TDOSW),_DOS
																																		//	      'bëdzie gadaî
		ARMIA[WRG][10][TPRAWA]=-1;																			//	      ARMIA(WRG,10,TPRAWA)=-1
		USTAW_WOJSKO(ARM,1,2,0);																				//	      USTAW_WOJSKO[ARM,1,2,0]
		USTAW_WOJSKO(WRG,1,0,0);																				//	      USTAW_WOJSKO[WRG,1,0,0]
		MAIN_ACTION();																									//	      MAIN_ACTION
		if( ARMIA[WRG][10][TE]<=0 ) {																		//	      If ARMIA(WRG,10,TE)<=0
			M=0; CO=ARM;																									//	         M=0 : CO=ARM
			A_S=GS("076")+Str_S(PRZYGODY[NR][P_NAGRODA])+GS("077");				//	         A$="You're getting "+Str$(PRZYGODY(NR,P_NAGRODA))+" gold pieces reward for ruffian's head."
			B=41;																													//	         B=41
			GRACZE[1][1]+=PRZYGODY[NR][P_NAGRODA];												//	         Add GRACZE(1,1),PRZYGODY(NR,P_NAGRODA)
		}																																//	      End If
	}																																	//	   End If
																																		//
	if( TYP==12 ) {																										//	   If TYP=12
		//---jaskinia wiedzy---																					//	      'jaskinia wiedzy
		NOWA_POSTAC(WRG,10,8);																					//	      NOWA_POSTAC[WRG,10,8]
		RYSUJ_SCENERIE(_TEREN,-1);																			//	      RYSUJ_SCENERIE[TEREN,-1]
		ARMIA[WRG][10][TGLOWA]=1;																				//	      ARMIA(WRG,10,TGLOWA)=1
		ARMIA[WRG][10][TKORP]=40;																				//	      ARMIA(WRG,10,TKORP)=40
		ARMIA[WRG][10][TDOSW]=60+Rnd(40);																//	      ARMIA(WRG,10,TDOSW)=60+Rnd(40)
		ARMIA[WRG][10][TPRAWA]=-1;																			//	      ARMIA(WRG,10,TPRAWA)=-1
		USTAW_WOJSKO(ARM,1,0,0);																				//	      USTAW_WOJSKO[ARM,1,0,0]
		USTAW_WOJSKO(WRG,1,2,0);																				//	      USTAW_WOJSKO[WRG,1,2,0]
		for( I=1; I<=10; ++I ) {																				//	      For I=1 To 10
			ARMIA[ARM][I][TDOSW]+=40+Rnd(40);															//	         Add ARMIA(ARM,I,TDOSW),40+Rnd(40)
			clipu(ARMIA[ARM][I][TDOSW],95);																//	         If ARMIA(ARM,I,TDOSW)>95 : ARMIA(ARM,I,TDOSW)=95 : End If
		}																																//	      Next I
		MAIN_ACTION();																									//	      MAIN_ACTION
	}																																	//	   End If
	if( TYP==13 ) {																										//	   If TYP=13
																																		//	      'Goto SKIP2
		//---sparing koïcowy---																					//	      'sparing koïcowy
		//---obrona bagien---																						//	      'obrona bagien
		POTWOR(WRG,"szkielet",10,11);																		//	      POTWOR[WRG,"szkielet",10,11]
		RYSUJ_SCENERIE(7,-3);																						//	      RYSUJ_SCENERIE[7,-3]
		KTO_ATAKUJE=ARM;																								//	      KTO_ATAKUJE=ARM
		USTAW_WOJSKO(ARM,0,2,2);																				//	      USTAW_WOJSKO[ARM,0,2,2]
		USTAW_WOJSKO(WRG,0,0,2);																				//	      USTAW_WOJSKO[WRG,0,0,2]
		MAIN_ACTION();																									//	      MAIN_ACTION
		if( WYNIK_AKCJI==1 || IMIONA_S[1]=="Marcin ®" ) {								//	      If WYNIK_AKCJI=1 or IMIONA$(1)="Marcin ®"
			for( I=0; I<=10; ++I ) { ARMIA[40][I][TE]=0; }								//	         For I=0 To 10 : ARMIA(40,I,TE)=0 : Next I
																																		//	         Hide On
			_LOAD(KAT_S+"grob.hb","legion:grob.hb","Legion",3);						//	         _LOAD[KAT$+"grob.hb","legion:grob.hb","Legion",3]
			_LOAD(KAT_S+"mod.end2","legion:mod.end2","Legion",6);					//	         _LOAD[KAT$+"mod.end2","legion:mod.end2","Legion",6]
			TrackLoop(true); TrackPlay(3);																//	         Track Loop On : Track Play 3
			USTAW_FONT("defender2",FONT_DEFENDER,8,1);										//	         USTAW_FONT["defender2",8]

			if( GS("078")!="" ) OUTLINE(10,200,GS("078"),1,0);
			if( GS("079")!="" ) OUTLINE(10,210,GS("079"),1,0);
			if( GS("080")!="" )	OUTLINE(10,220,GS("080"),1,0);						//	         OUTLINE[10,220,"The Chaos Master lies",1,0]
			if( GS("081")!="" )	OUTLINE(10,230,GS("081"),1,0);						//	         OUTLINE[10,230,"in his underground tomb",1,0]
			if( GS("082")!="" ) OUTLINE(10,240,GS("082"),1,0);

																																		//	         'OUTLINE[10,220,"krypcie grobowej,",1,0]
																																		//	         'OUTLINE[10,230,"z której zatruwa caîe",1,0]
																																		//	         'OUTLINE[10,240,"królestwo.",1,0]
																																		//	         View
			_WAIT(1500);																									//	         _WAIT[1500]
//			Fade 2;																											//	         Fade 2
			_TRACK_FADE(1);																								//	         _TRACK_FADE[1]
			Erase(3);																											//	         Erase 3
			SETUP(GS("083"),GS("084"),GS("085"));												//	         SETUP["Battle","with","Chaos Master"]
																																		//	         'sparing z bossem
			POTWOR(WRG,"boss",1,19);																			//	         POTWOR[WRG,"boss",1,19]
			RYSUJ_SCENERIE(_TEREN,-1);																		//	         RYSUJ_SCENERIE[TEREN,-1]
			for( I=1; I<=10; ++I ) { ARMIA[WRG][I][TKORP]=180; }					//	         For I=1 To 10 : ARMIA(WRG,I,TKORP)=180 : Next I
			USTAW_WOJSKO(ARM,1,1,0);																			//	         USTAW_WOJSKO[ARM,1,1,0]
			USTAW_WOJSKO(WRG,1,1,0);																			//	         USTAW_WOJSKO[WRG,1,1,0]
			MAIN_ACTION();																								//	         MAIN_ACTION
			if( WYNIK_AKCJI==1 || IMIONA_S[1]=="Marcin ®" ) {							//	         If WYNIK_AKCJI=1 or IMIONA$(1)="Marcin ®"
				//SKIP2:																											//	            SKIP2:
				PRZYGODY[NR][P_TYP]=0;																			//	            PRZYGODY(NR,P_TYP)=0
				GAME_OVER=-1;																								//	            GAME_OVER=True
																																		//	            Hide On
				_LOAD(KAT_S+"pobieda.hb","legion:pobieda.hb","Legion",3);		//	            _LOAD[KAT$+"pobieda.hb","legion:pobieda.hb","Legion",3]
				_LOAD(KAT_S+"mod.2sample+","legion:mod.2sample+","Legion",6);//	            _LOAD[KAT$+"mod.2sample+","legion:mod.2sample+","Legion",6]
				TrackLoop(true); TrackPlay(3);															//	            Track Loop On : Track Play 3
				USTAW_FONT("defender2",FONT_DEFENDER,8,1);									//	            USTAW_FONT["defender2",8]
				OUTLINE(10,200,GS("086"),1,0);															//	            OUTLINE[10,200,"Oto ten, który niszczyî",1,0]
				OUTLINE(10,210,GS("087"),1,0);															//	            OUTLINE[10,210,"wszelkie ûycie ",1,0]
				OUTLINE(10,220,GS("088"),1,0);															//	            OUTLINE[10,220,"leûy teraz martwy",1,0]
				OUTLINE(10,230,GS("089"),1,0);															//	            OUTLINE[10,230,"u twych stóp",1,0]
				OUTLINE(10,240,GS("090"),1,0);															//	            OUTLINE[10,240,"",1,0]
				A_S=GS("091");																							//	            A$="Your adventure is ending."
				M=0; CO=ARM; B=34;																					//	            M=0 : CO=ARM : B=34
																																		//	            View
				_WAIT(3500);																								//	            _WAIT[3500]
//				Fade 2;																										//	            Fade 2
				_TRACK_FADE(1);																							//	            _TRACK_FADE[1]
				Erase(3);																										//	            Erase 3
			}																															//	         End If
		}																																//	      End If
	}																																	//	   End If
																																		//
	//OVER:																															//	   OVER:
	if( TESTING==0 ) {																								//	   If Not TESTING
		TRWA_PRZYGODA=-1;																								//	      TRWA_PRZYGODA=-1
		for( I=0; I<=10; ++I ) { ARMIA[40][I][TE]=0; }									//	      For I=0 To 10 : ARMIA(40,I,TE)=0 : Next I
		ARMIA[A][0][TTRYB]=0;																						//	      ARMIA(A,0,TTRYB)=0
		if( TYP!=13 ) { PRZYGODY[NR][P_TYP]=0; }												//	      If TYP<>13 : PRZYGODY(NR,P_TYP)=0 : End If
		SETUP0();																												//	      SETUP0
		VISUAL_OBJECTS();																								//	      VISUAL_OBJECTS
		Sprite(2,SPX,SPY,1);																						//	      Sprite 2,SPX,SPY,1
		CENTER(ARMIA[A][0][TX],ARMIA[A][0][TY],0);											//	      CENTER[ARMIA(A,0,TX),ARMIA(A,0,TY),0]
		if( M>-1 ) {																										//	      If M>-1
			MESSAGE2(CO,A_S,B,M,0);																				//	         MESSAGE2[CO,A$,B,M,0]
		}																																//	      End If
		BUSY_ANIM();																										//	      BUSY_ANIM
	}																																	//	   End If
																																		//	End Proc
}
void MA_WYPADEK(aint A,aint TYP) {
																														//	Procedure MA_WYPADEK[A,TYP]
	aint _TEREN=0, XT=0, YT=0, POT=0, ILE=0, BB=0, X=0, Y=0, I=0, AGRESJA=0;
	astr A_S="", PO_S="";

	_TEREN=ARMIA[A][0][TNOGI];																//	   TEREN=ARMIA(A,0,TNOGI)
	if( TYP==1 ) {																						//	   If TYP=1
		A_S=GS("092");																					//	      A$="Rabid wolves has encircled us !"
		PO_S="wilk";																						//	      PO$="wilk"
		XT=1; YT=1;																							//	      XT=1 : YT=1
		POT=12;																									//	      POT=12
		ILE=Rnd(5)+5;																						//	      ILE=Rnd(5)+5
		BB=34;																									//	      BB=34
	}																													//	   End If
	if( TYP==2 ) {																						//	   If TYP=2
		A_S=GS("093");																					//	      A$="We're attacked by robbers."
		POT=-1; ILE=Rnd(5)+5;																		//	      POT=-1 : ILE=Rnd(5)+5
		XT=Rnd(2); YT=Rnd(2);																		//	      XT=Rnd(2) : YT=Rnd(2)
		BB=31;																									//	      BB=31
	}																													//	   End If
	if( TYP==3 ) {																						//	   If TYP=3
		A_S=GS("094");																					//	      A$="We've stalled in the swaps."
		PO_S="gloom";																						//	      PO$="gloom"
		POT=14; ILE=Rnd(5);																			//	      POT=14 : ILE=Rnd(5)
		XT=1; YT=1;																							//	      XT=1 : YT=1
		BB=34;																									//	      BB=34
	}																													//	   End If
	if( TYP==4 ) {																						//	   If TYP=4
		A_S=GS("095");																					//	      A$="We're encircled by forest trolls."
		POT=6; ILE=Rnd(5)+5;																		//	      POT=6 : ILE=Rnd(5)+5
		XT=1; YT=1;																							//	      XT=1 : YT=1
		BB=31;																									//	      BB=31
	}																													//	   End If
	if( TYP==5 ) {																						//	   If TYP=5
		A_S=GS("096");																					//	      A$="Gargoyl !!!"
		PO_S="gargoil";																					//	      PO$="gargoil"
		POT=10; ILE=Rnd(1)+1;																		//	      POT=10 : ILE=Rnd(1)+1
		XT=1; YT=1;																							//	      XT=1 : YT=1
		BB=34;																									//	      BB=34
	}																													//	   End If
	if( TYP==6 ) {																						//	   If TYP=6
		A_S=GS("097");																					//	      A$="We meet a solitary knight."
		POT=-1; ILE=1;																					//	      POT=-1 : ILE=1
		XT=Rnd(2); YT=Rnd(2);																		//	      XT=Rnd(2) : YT=Rnd(2)
		BB=34;																									//	      BB=34
	}																													//	   End If
	if( TYP==7 ) {																						//	   If TYP=7
		A_S=GS("098");																					//	      A$="We've found an entrance to cavern."
		POT=18; ILE=5; XT=1; YT=0;															//	      POT=18 : ILE=5 : XT=1 : YT=0
		PO_S="pajâk";																						//	      PO$="pajâk"
		_TEREN=8;																								//	      TEREN=8
		BB=34;																									//	      BB=34
	}																													//	   End If
	AmalOnOff(-1,false);																			//	   Amal Off
																														//	   Show On
	X=ARMIA[A][0][TX];																				//	   X=ARMIA(A,0,TX)
	Y=ARMIA[A][0][TY];																				//	   Y=ARMIA(A,0,TY)
	CENTER(X,Y,1);																						//	   CENTER[X,Y,1]
	MESSAGE2(A,A_S,BB,0,1);																		//	   MESSAGE2[A,A$,BB,0,1]
	ARM=A; WRG=40;																						//	   ARM=A : WRG=40
	SpriteOnOff(2,false);																			//	   Sprite Off 2
	SETUP(GS("070"),GS("71"),GS("72"));												//	   SETUP["","Action",""]
	for( I=0; I<=10; ++I ) ARMIA[40][I][TE]=0;								//	   For I=0 To 10 : ARMIA(40,I,TE)=0 : Next I
	if( POT>9 ) {																							//	   If POT>9
		POTWOR(40,PO_S,ILE,POT);																//	      POTWOR[40,PO$,ILE,POT]
		if( TYP==7 ) {																					//	      If TYP=7
			for( I=6; I<=10; ++I ) {															//	         For I=6 To 10 : NOWA_POSTAC[40,I,Rnd(8)] : ARMIA(40,I,TKORP)=150+Rnd(50) : Next I
				NOWA_POSTAC(40,I,Rnd(8));
				ARMIA[40][I][TKORP]=150+Rnd(50);
			}
		}																												//	      End If
	} else {																									//	   Else
		NOWA_ARMIA(40,ILE,POT);																	//	      NOWA_ARMIA[40,ILE,POT]
		AGRESJA=ARMIA[WRG][0][TKORP];														//	      AGRESJA=ARMIA(WRG,0,TKORP)
		if( TYP==6 ) { ARMIA[WRG][1][TDOSW]=Rnd(30)+20; AGRESJA=40; }//	      If TYP=6 : ARMIA(WRG,1,TDOSW)=Rnd(30)+20 : AGRESJA=40 : End If
		for( I=1; I<=10; ++I ) { ARMIA[WRG][I][TKORP]=AGRESJA; }//	      For I=1 To 10 : ARMIA(WRG,I,TKORP)=AGRESJA : Next I
	}																													//	   End If
	RYSUJ_SCENERIE(_TEREN,-1);																//	   RYSUJ_SCENERIE[TEREN,-1]
	USTAW_WOJSKO(ARM,XT,YT,0);																//	   USTAW_WOJSKO[ARM,XT,YT,0]
	USTAW_WOJSKO(WRG,XT,YT,1);																//	   USTAW_WOJSKO[WRG,XT,YT,1]
	MAIN_ACTION();																						//	   MAIN_ACTION
	for( I=0; I<=10; ++I ) { ARMIA[40][I][TE]=0; }						//	   For I=0 To 10 : ARMIA(40,I,TE)=0 : Next I
	SETUP0();																									//	   SETUP0
	VISUAL_OBJECTS();																					//	   VISUAL_OBJECTS
	Sprite(2,SPX,SPY,1);																			//	   Sprite 2,SPX,SPY,1
	CENTER(ARMIA[A][0][TX],ARMIA[A][0][TY],0);								//	   CENTER[ARMIA(A,0,TX),ARMIA(A,0,TY),0]
	BUSY_ANIM();																							//	   BUSY_ANIM
																														//	End Proc
}
void PLAGA(aint MIASTO,aint PLAGA) {
																			//	Procedure PLAGA[MIASTO,PLAGA]
	astr M_S="", A_S="";
	aint LUDZIE=0, BB=0, I=0;

	M_S=MIASTA_S[MIASTO];								//	   M$=MIASTA$(MIASTO)
	LUDZIE=MIASTA[MIASTO][0][M_LUDZIE];	//	   LUDZIE=MIASTA(MIASTO,0,M_LUDZIE)
	if( PLAGA==0 ) {										//	   If PLAGA=0
		BB=32;														//	      BB=32
		A_S=GS("099");										//	      A$="The flames took a lot of inhabitants and their houses."

		//!!! BLAD
		Add(LUDZIE,-(LUDZIE/4),50,LUDZIE);//	      Add LUDZIE,-(LUDZIE/4),50 To LUDZIE
		//!!! powinno byc
		//LUDZIE-=LUDZIE/4;
		//clipl(LUDZIE,50);

		for(I=2;I<=20;++I) {							//	      For I=2 To 20 : If Rnd(1)=1 : MIASTA(MIASTO,I,M_LUDZIE)=0 : End If : Next I
			if( Rnd(1)==1 ) {
				MIASTA[MIASTO][I][M_LUDZIE]=0;
			}
		}
	}																		//	   End If
	if( PLAGA==1 ) {										//	   If PLAGA=1
		BB=29;														//	      BB=29

		//!!! BLAD
		Add(LUDZIE,-(LUDZIE/2),50,LUDZIE);//	      Add LUDZIE,-(LUDZIE/2),50 To LUDZIE
		//!!! powinno byc
		//LUDZIE-=LUDZIE/2;
		//clipl(LUDZIE,50);

		A_S=GS("100");										//	      A$="Epidemic has killed many people ! "
	}																		//	   End If
	if( PLAGA==2 ) {										//	   If PLAGA=2
		BB=30;														//	      BB=30
		A_S=GS("101");										//	      A$="Rats ate all grain reserves."
		MIASTA[MIASTO][1][M_LUDZIE]=0;		//	      MIASTA(MIASTO,1,M_LUDZIE)=0
	}																		//	   End If
	MIASTA[MIASTO][0][M_LUDZIE]=LUDZIE;	//	   MIASTA(MIASTO,0,M_LUDZIE)=LUDZIE
	MESSAGE2(MIASTO,A_S,BB,1,0);				//	   MESSAGE2[MIASTO,A$,BB,1,0]
																			//	End Proc
}
void MA_WYDAJ_ROZKAZ(aint PL,aint A) {
	//	Procedure MA_WYDAJ_ROZKAZ[PL,A]

	aint XA=0,YA=0,RODZAJ=0,STARAODL=0,WIDAC=0,I=0,LUDZIE=0,PL2=0,SZAJBA=0,
	     XB=0,YB=0,TARGET=0,CX=0,CY=0,M=0;

	XA=ARMIA[A][0][TX];								//	   XA=ARMIA(A,0,TX)
	YA=ARMIA[A][0][TY];								//	   YA=ARMIA(A,0,TY)
																		//	   '   RODZAJ=ARMIA(A,0,TKORP)
	RODZAJ=3;													//	   RODZAJ=3
	if( RODZAJ==1 || RODZAJ==2 || RODZAJ==3 ) {//	   If RODZAJ=1 or RODZAJ=2 or RODZAJ=3
		STARAODL=120;										//	      STARAODL=120
		WIDAC=0;												//	      WIDAC=False
		for(I=0;I<49;++I) {							//	      For I=0 To 49
			PL2=MIASTA[I][0][M_CZYJE];		//	         PL2=MIASTA(I,0,M_CZYJE)
			LUDZIE=MIASTA[I][0][M_LUDZIE];//	         LUDZIE=MIASTA(I,0,M_LUDZIE)
																		//	         'wszczynaie drobnych konfliktów
			if( PL2==0 || PL2==1 ) {			//	         If PL2=0 or PL2=1
				SZAJBA=300-POWER;						//	            SZAJBA=300-POWER
			} else {											//	         Else
				SZAJBA=2200+POWER;					//	            SZAJBA=2200+POWER
			}															//	         End If
			if( PL==5 ) SZAJBA=1;					//	         If PL=5 : SZAJBA=1 : End If
			if( Rnd(SZAJBA)==1 ) {				//	         If Rnd(SZAJBA)=1
				//!!! BUG ? CZY NIE POWINNO BYC TYLE SAMO, A NIE DWA RAZY LOSOWANE
				WOJNA[PL][PL2]=Rnd(20)+8;		//	            WOJNA(PL,PL2)=Rnd(20)+8
				WOJNA[PL2][PL]=Rnd(20)+8;		//	            WOJNA(PL2,PL)=Rnd(20)+8
			}															//	         End If
			if( WOJNA[PL][PL2]>0 && PL2!=PL ) {//	         If WOJNA(PL,PL2)>0 and PL2<>PL
																		//	            'litoôci !!!
				if( PL==5 && LUDZIE<200 ) {	//	            If PL=5 and LUDZIE<200
					goto SKIP;								//	               Goto SKIP
				}														//	            End If
				XB=MIASTA[I][0][M_X];				//	            XB=MIASTA(I,0,M_X)
				YB=MIASTA[I][0][M_Y];				//	            YB=MIASTA(I,0,M_Y)
				ODL(XA,YA,XB,YB);						//	            ODL[XA,YA,XB,YB]
				if( ODLEG<STARAODL ) {			//	            If ODLEG<STARAODL
					TARGET=I;									//	               TARGET=I
					CX=XB; CY=1;							//	               CX=XB : CY=1
					STARAODL=ODLEG;						//	               STARAODL=ODLEG
					WIDAC=-1;									//	               WIDAC=True
				}														//	            End If
			}															//	         End If
			SKIP:													//	         SKIP:
				;
		}																//	      Next I
																		//
		for(I=0;I<=39;++I) {						//	      For I=0 To 39
			PL2=ARMIA[I][0][TMAG];				//	         PL2=ARMIA(I,0,TMAG)
			if( ARMIA[I][0][TE]>0 && WOJNA[PL][PL2]>0 && PL2!=PL ) {//	         If ARMIA(I,0,TE)>0 and WOJNA(PL,PL2)>0 and PL2<>PL																	//	            M=ARMIA(I,0,TNOGI)
				//!!! BUG - M nie jest okreslone nigdzie, a wiec zawsze == 0
				if( M>69 ) {								//	            If M>69
					if( MIASTA[M-70][0][M_CZYJE]==PL2 ) {//	               If MIASTA(M-70,0,M_CZYJE)=PL2
						XB=MIASTA[M-70][0][M_X];//	                  XB=MIASTA(M-70,0,M_X)
						YB=MIASTA[M-70][0][M_Y];//	                  YB=MIASTA(M-70,0,M_Y)
						ODL(XA,YA,XB,YB);				//	                  ODL[XA,YA,XB,YB]
						if( ODLEG<STARAODL) {		//	                  If ODLEG<STARAODL
							TARGET=M-70;					//	                     TARGET=M-70
							CX=XB; CY=1;					//	                     CX=XB : CY=1
							STARAODL=ODLEG;				//	                     STARAODL=ODLEG
							WIDAC=-1;							//	                     WIDAC=True
						}												//	                  End If
					} else {									//	               Else
						goto DALEJ;							//	                  Goto DALEJ
					}													//	               End If
				} else {										//	            Else
					DALEJ:										//	               DALEJ:
					XB=ARMIA[I][0][TX];				//	               XB=ARMIA(I,0,TX)
					YB=ARMIA[I][0][TY];				//	               YB=ARMIA(I,0,TY)
					ODL(XA,YA,XB,YB);					//	               ODL[XA,YA,XB,YB]
					if( ODLEG<STARAODL ) {		//	               If ODLEG<STARAODL
						TARGET=I;								//	                  TARGET=I
						CX=XB; CY=0;						//	                  CX=XB : CY=0
						STARAODL=ODLEG;					//	                  STARAODL=ODLEG
						WIDAC=-1;								//	                  WIDAC=True
					}													//	               End If
				}														//	            End If
			}															//	         End If
		}																//	      Next I
	}																	//	   End If
																		//
	if( RODZAJ==3 && WIDAC!=0 ) {			//	   If RODZAJ=3 and WIDAC
																		//	      Gosub _ATAK
		ARMIA[A][0][TTRYB]=3;
		ARMIA[A][0][TCELX]=TARGET;
		ARMIA[A][0][TCELY]=CY;
		return;
	}																	//	   End If
																		//	   Goto OVER
																		//
																		//	   RUCH:
																		//	   Return
																		//
																		//	   _ATAK:
																		//	   ARMIA(A,0,TTRYB)=3
																		//	   ARMIA(A,0,TCELX)=TARGET
																		//	   ARMIA(A,0,TCELY)=CY
																		//	   Return
																		//
																		//	   OBOZ:
																		//	   Return
																		//
																		//	   OVER:
																		//	End Proc
}

void VISUAL_OBJECTS(void) {
																											//	Procedure VISUAL_OBJECTS
	aint I=0, CZYJE=0, B1=0, LUD=0, X=0, Y=0, A=0, X2=0, Y2=0;

	for( I=0; I<=49; ++I ) {														//	   For I=0 To 49
		CZYJE=MIASTA[I][0][M_CZYJE];											//	      CZYJE=MIASTA(I,0,M_CZYJE)
		B1=8+CZYJE*2;																			//	      B1=8+CZYJE*2
		LUD=MIASTA[I][0][M_LUDZIE];												//	      LUD=MIASTA(I,0,M_LUDZIE)
		if( LUD>700 ) {																		//	      If LUD>700
			B1++;																						//	         Inc B1
																											//	         '         MIASTA(I,2,M_MUR)=6
		} else {																					//	      Else
																											//	         '         TEREN[X+8,Y+8]
																											//	         '         MIASTA(I,2,M_MUR)=LOK
		}																									//	      End If
		X=MIASTA[I][0][M_X];															//	      X=MIASTA(I,0,M_X)
		Y=MIASTA[I][0][M_Y];															//	      Y=MIASTA(I,0,M_Y)
																											//	      'to moûna potem wywaliê
																											//	      '  TEREN[X+4,Y+4]
																											//	      '  If LOK=7 : LOK=1 : End If
																											//	      '  MIASTA(I,1,M_X)=LOK
		PasteBob(X-8,Y-8,B1);															//	      Paste Bob X-8,Y-8,B1
		SetZone(70+I,X-8,Y-8,X+8,Y+8);										//	      Set Zone 70+I,X-8,Y-8 To X+8,Y+8
	}																										//	   Next I
																											//
	for( A=0; A<=39; ++A ) {														//	   For A=0 To 39
		if( ARMIA[A][0][TE]>0 ) {													//	      If ARMIA(A,0,TE)>0
			X=ARMIA[A][0][TX];															//	         X=ARMIA(A,0,TX)
			Y=ARMIA[A][0][TY];															//	         Y=ARMIA(A,0,TY)
			B1=ARMIA[A][0][TBOB];														//	         B1=ARMIA(A,0,TBOB)
			B_DRAW(A,X,Y,B1);																//	         B_DRAW[A,X,Y,B1]
		}																									//	      End If
	}																										//	   Next A
																											//
	for( I=0; I<=3; ++I ) {															//	   For I=0 To 3
		if( PRZYGODY[I][P_TYP]>0 && PRZYGODY[I][P_LEVEL]==0 ) {//	      If PRZYGODY(I,P_TYP)>0 and PRZYGODY(I,P_LEVEL)=0
			X=PRZYGODY[I][P_X]; Y=PRZYGODY[I][P_Y];					//	         X=PRZYGODY(I,P_X) : Y=PRZYGODY(I,P_Y)
			X2=X; Y2=Y;																			//	         X2=X : Y2=Y
			LOSUJ:																					//	         LOSUJ:
			if( _Zone(X2,Y2)!=0 || X2<8 || X2>630 || Y2<10 || Y2>500 ) {//	         If Zone(X2,Y2)<>0 or X2<8 or X2>630 or Y2<10 or Y2>500
				X2=X+Rnd(60)-30; Y2=Y+Rnd(60)-30;							//	            X2=X+Rnd(60)-30 : Y2=Y+Rnd(60)-30
				goto LOSUJ;																		//	            Goto LOSUJ
			}																								//	         End If
			PRZYGODY[I][P_X]=X2; PRZYGODY[I][P_Y]=Y2;				//	         PRZYGODY(I,P_X)=X2 : PRZYGODY(I,P_Y)=Y2
			if( PRZYGODY[I][P_TEREN]==0 ) {									//	         If PRZYGODY(I,P_TEREN)=0
				TEREN(X2,Y2);																	//	            TEREN[X2,Y2]
				PRZYGODY[I][P_TEREN]=LOK;											//	            PRZYGODY(I,P_TEREN)=LOK
			}																								//	         End If
			PasteBob(X2,Y2,18);															//	         Paste Bob X2,Y2,18
			SetZone(121+I,X2,Y2,X2+6,Y2+6);									//	         Set Zone 121+I,X2,Y2 To X2+6,Y2+6
																											//	         '         Ink 17 : Box X2,Y2 To X2+6,Y2+6
		}																									//	      End If
	}																										//	   Next I
	rysuj(); WaitVbl();																	//	   View : Wait Vbl
																											//	End Proc
}

void _SZPIEGUJ_WYPISZ(aint CENA,aint DNI) {
	astr A_S="",B_S="";
																				//	   WYPISZ:
	if( CENA<=100 ) {											//	   If CENA<=100
		A_S=GS("169");											//	      A$="Nice weather "
		B_S=GS("170");											//	      B$=""
		if( CENA==0 ) {											//	      If CENA=0
			A_S=GS("171");										//	         A$="You have to pay for"
			B_S=GS("172");										//	         B$="informations."
		}																		//	      End If
	} else {															//	   Else
		A_S=GS("173");											//	      A$="I'll know something"
		B_S=GS("174")+Str_S(DNI)+GS("175");	//	      B$="during "+Str$(DNI)+" days"
	}																			//	   End If
	gad_back(1.0);												//	   Ink 30 : Bar OKX+5,OKY+68 To OKX+102,OKY+92
	_Bar(OKX+5,OKY+68,OKX+102,OKY+92);
	gad_text(1.0);												//	   Ink 1,30 : Text OKX+12,OKY+80,A$
	Text(OKX+12,OKY+80,A_S);
	Text(OKX+12,OKY+90,B_S);							//	   Text OKX+12,OKY+90,B$

	gad_back(1.0);									//	            Ink 30 : Bar OKX+113,OKY+25 To OKX+150,OKY+38
	_Bar(OKX+113,OKY+25,OKX+150,OKY+38);
	gad_text(1.0);									//	            Ink 1,30 : Text OKX+120,OKY+34,Str$(CENA)
	Text(OKX+120,OKY+34,Str_S(CENA));

}
void SZPIEGUJ(aint NR,aint CO) {
	//	Procedure SZPIEGUJ[NR,CO]

	rysuj();
	OKNO(80,90,156,100);									//	   OKNO[80,90,156,100]
	GADGET(OKX+4,OKY+4,104,92,"",31,2,30,1,-1);		//	   GADGET[OKX+4,OKY+4,104,92,"",31,2,30,1,-1]
	GADGET(OKX+112,OKY+4,18,15,"<<",8,2,6,31,1);	//	   GADGET[OKX+112,OKY+4,18,15," «",8,2,6,31,1]
	GADGET(OKX+133,OKY+4,18,15,">>",8,2,6,31,2);	//	   GADGET[OKX+133,OKY+4,18,15," »",8,2,6,31,2]
	GADGET(OKX+112,OKY+24,40,15,"",31,2,30,1,-1);	//	   GADGET[OKX+112,OKY+24,40,15,"",31,2,30,1,-1]
	GADGET(OKX+112,OKY+61,40,15,GS("176"),8,2,6,31,3);//	   GADGET[OKX+112,OKY+61,40,15," Cancel",8,2,6,31,3]
	GADGET(OKX+112,OKY+81,40,15,GS("177"),8,2,6,31,4);	//	   GADGET[OKX+112,OKY+81,40,15,"    Ok",8,2,6,31,4]
	PasteBob(OKX+8,OKY+8,35);													//	   Paste Bob OKX+8,OKY+8,35

	void *sb=StoreBuffer(OKX-1,OKY-1,156+2,100+2);
	aint CENA=0,DNI=0,ZN=0,STREFA=0,KONIEC=0;
	CENA=0;																//	   CENA=0
	DNI=22;																//	   DNI=22
	//_SZPIEGUJ_WYPISZ(CENA,DNI);					//	   Gosub WYPISZ
	do {																	//	   Repeat
		rysuj();
		RestoreBuffer(sb);
		_SZPIEGUJ_WYPISZ(CENA,DNI);
		WaitVbl();
		if( MouseClick() ) {								//	      If Mouse Click=1
			STREFA=MouseZone();								//	         STREFA=Mouse Zone
			if( STREFA==1 || STREFA==2 ) {		//	         If STREFA=1 or STREFA=2
				if( STREFA==1 ) {								//	         		If STREFA=1 : ZN=1 : Else ZN=-1 : End If
					ZN=1;
				} else {
					ZN=-1;
				}

				//!!! BLAD
				Add(CENA,ZN*50,0,1000);					//	            Add CENA,ZN*50,0 To 1000
				//!!! powinno raczej byc
				//CENA+=ZN*50; clip(CENA,0,1000);

				//!!! BLAD
				Add(DNI,-ZN,2,22);							//	            Add DNI,-ZN,2 To 22
				//!!! powinno raczej byc
				//DNI+=-ZN;	clip(DNI,2,22);

				//gad_back(1.0);									//	            Ink 30 : Bar OKX+113,OKY+25 To OKX+150,OKY+38
				//_Bar(OKX+113,OKY+25,OKX+150,OKY+38);
				//gad_text(1.0);									//	            Ink 1,30 : Text OKX+120,OKY+34,Str$(CENA)
				//Text(OKX+120,OKY+34,Str_S(CENA));
				//_SZPIEGUJ_WYPISZ(CENA,DNI);			//	            Gosub WYPISZ
			}																	//	         End If
			if( STREFA==4 ) {									//	         If STREFA=4
				if( GRACZE[1][1]-CENA>=0 ) {		//	            If GRACZE(1,1)-CENA>=0
					if( CENA>100 ) {							//	               If CENA>100
						if( CO==0 ) {								//	                  If CO=0
							MIASTA[NR][1][M_Y]=DNI;		//	                     MIASTA(NR,1,M_Y)=DNI
						}														//	                  End If
						if( CO==1 ) {								//	                  If CO=1
							ARMIA[NR][0][TMAGMA]=DNI;	//	                     ARMIA(NR,0,TMAGMA)=DNI
						}														//	                  End If
						GRACZE[1][1]-=CENA;					//	                  Add GRACZE(1,1),-CENA
					}															//	               End If
					KONIEC=-1;										//	               KONIEC=True
				}																//	            End If
			}																	//	         End If
			if( STREFA==3 ) {									//	         If STREFA=3 : KONIEC=True : End If
				KONIEC=-1;
			}
		}																		//	      End If
	} while( KONIEC==0 );									//	   Until KONIEC
																				//	   Goto OVER
																				//	   WYPISZ:
																				//	   If CENA<=100
																				//	      A$="Nice weather "
																				//	      B$=""
																				//	      If CENA=0
																				//	         A$="You have to pay for"
																				//	         B$="informations."
																				//	      End If
																				//	   Else
																				//	      A$="I'll know something"
																				//	      B$="during "+Str$(DNI)+" days"
																				//	   End If
																				//	   Ink 30 : Bar OKX+5,OKY+68 To OKX+102,OKY+92
																				//	   Ink 1,30 : Text OKX+12,OKY+80,A$
																				//	   Text OKX+12,OKY+90,B$
																				//	   Return
																				//	   OVER:
	ZOKNO();															//	   ZOKNO
	FreeBuffer(sb);
	rysuj();
																				//	End Proc
}

void TEREN(aint X1,aint Y1) {
	//	Procedure TEREN[X1,Y1]
	aint STREFA=0,X=0,Y=0,KOL=0,KOLOR=0,I=0,FINAL=0;

	STREFA=_Zone(X1,Y1);							//	   STREFA=Zone(X1,Y1)
	if(STREFA>69 && STREFA<125) {		//	   If STREFA>69 and STREFA<125
		LOK=STREFA;										//	      LOK=STREFA
		goto OVER;										//	      Goto OVER
	}																//	   End If
	if( STREFA>19 && STREFA<40 ) {	//	   If STREFA>19 and STREFA<40
		LOK=ARMIA[STREFA-20][0][TNOGI];	//	      LOK=ARMIA(STREFA-20,0,TNOGI)
		goto OVER;										//	      Goto OVER
	}																//	   End If
	aint KOLORY[31+1];							//	   Dim KOLORY(31)
	for(I=0;I<=31;++I) {
		KOLORY[I]=0;
	}
	for(Y=Y1-4;Y<=Y1+4;++Y) {				//	   For Y=Y1-4 To Y1+4
		for(X=X1-4;X<=X1+4;++X) {			//	      For X=X1-4 To X1+4
			KOL=_PointIff(X,Y);					//	         KOL=Point(X,Y)
			if( KOL>-1 ) KOLORY[KOL]++;	//	         If KOL>-1 : Add KOLORY(KOL),1 : End If
		}															//	      Next X
	}																//	   Next Y
	KOLOR=0;												//	   KOLOR=0
	for(I=0;I<=31;++I) {						//	   For I=0 To 31
		if(KOLORY[I]>KOLOR) {					//	      If KOLORY(I)>KOLOR
			KOLOR=KOLORY[I];						//	         KOLOR=KOLORY(I)
			FINAL=I;										//	         FINAL=I
		}															//	      End If
		KOLORY[I]=0;									//	      KOLORY(I)=0
	}																//	   Next I
																	//	   Pen 23
	LOK=0;													//	   LOK=0
	if( FINAL>8 && FINAL<11 ) {			//	   If FINAL>8 and FINAL<11
																	//	      'bagno
		LOK=7;												//	      LOK=7
	}																//	   End If
	if( FINAL>12 && FINAL<16 ) {		//	   If FINAL>12 and FINAL<16
																	//	      'îâka
		LOK=2;												//	      LOK=2
	}																//	   End If
	if( FINAL>10 && FINAL<13 ) {		//	   If FINAL>10 and FINAL<13
																	//	      'las
		LOK=1;												//	      LOK=1
	}																//	   End If
	if( FINAL>6 && FINAL<9 ) {			//	   If FINAL>6 and FINAL<9
																	//	      'pustynia
		LOK=3;												//	      LOK=3
	}																//	   End If
	if( FINAL>0 && FINAL<4 ) {			//	   If FINAL>0 and FINAL<4
																	//	      'las
		LOK=1;												//	      LOK=1
	}																//	   End If
	if( FINAL>28 ) {								//	   If FINAL>28
																	//	      'lodowiec
		LOK=5;												//	      LOK=5
	}																//	   End If
	if( FINAL>3 && FINAL<7 ) {			//	   If FINAL>3 and FINAL<7
																	//	      'skaîy
		LOK=4;												//	      LOK=4
	}																//	   End If
	if( FINAL>23 && FINAL<29 ) {		//	   If FINAL>23 and FINAL<29
																	//	      'skaîy
		LOK=4;												//	      LOK=4
	}																//	   End If
	OVER:														//	   OVER:
	if(LOK<=0) LOK=2;								//	   If LOK<=0 : LOK=2 : End If
																	//	End Proc
}

void BITWA(aint A,aint B,aint X1,aint Y1,aint T1,aint X2,aint Y2,aint T2,aint SCENERIA,aint WIES) {
	//	Procedure BITWA[A,B,X1,Y1,T1,X2,Y2,T2,SCENERIA,WIES]
	aint PL2=0,I=0,AGRESJA=0;

	ARM=A; WRG=B;										//	   ARM=A : WRG=B
	PL2=ARMIA[B][0][TMAG];					//	   PL2=ARMIA(B,0,TMAG)
	SpriteOnOff(2,false);						//	   Sprite Off 2
	SETUP("",GS("007"),"");					//	   SETUP["","Battle",""]
	if( ARMIA[B][0][TMAG]==5 ) {		//	   If ARMIA(B,0,TMAG)=5
		for(I=1;I<=16;++I) {					//	      For I=1 To 16
			DelBob(POTWORY+1);					//	         Del Bob POTWORY+1
		}															//	      Next I
		_LOAD(KAT_S+"dane/potwory/szkielet","dane:potwory/szkielet","Dane",1);//	      _LOAD[KAT$+"dane/potwory/szkielet","dane:potwory/szkielet","Dane",1]
		_LOAD(KAT_S+"dane/potwory/szkielet.snd","dane:potwory/szkielet.snd","Dane",9);//	      _LOAD[KAT$+"dane/potwory/szkielet.snd","dane:potwory/szkielet.snd","Dane",9]
	}																//	   End If
	RYSUJ_SCENERIE(SCENERIA,WIES);	//	   RYSUJ_SCENERIE[SCENERIA,WIES]
	AGRESJA=ARMIA[B][0][TKORP];			//	   AGRESJA=ARMIA(B,0,TKORP)
	for(I=1;I<=10;++I) {						//	   For I=1 To 10 : ARMIA(WRG,I,TKORP)=AGRESJA : Next I
		ARMIA[WRG][I][TKORP]=AGRESJA;
	}
	USTAW_WOJSKO(A,X1,Y1,T1);				//	   USTAW_WOJSKO[A,X1,Y1,T1]
	USTAW_WOJSKO(B,X2,Y2,T2);				//	   USTAW_WOJSKO[B,X2,Y2,T2]
	MAIN_ACTION();									//	   MAIN_ACTION
	if( TESTING!=0 ) return;				//	   If TESTING Then Pop Proc
	SETUP0();												//	   SETUP0
	VISUAL_OBJECTS();								//	   VISUAL_OBJECTS
	Sprite(2,SPX,SPY,1);						//	   Sprite 2,SPX,SPY,1
																	//
																	//	End Proc
}
void BITWA_SYMULOWANA(aint A,aint B) {
	//	Procedure BITWA_SYMULOWANA[A,B]

	aint S1=0,S2=0,S3=0,DS=0,I=0,WINNER=0,LOSER=0,WOJ=0,SILA=0,SPEED=0;
	S1=ARMIA[A][0][TSI]+Rnd(100);				//	   S1=ARMIA(A,0,TSI)+Rnd(100)
	S2=ARMIA[B][0][TSI]+Rnd(100);				//	   S2=ARMIA(B,0,TSI)+Rnd(100)
	DS=S1-S2;														//	   DS=S1-S2
	if( DS>=0 ) {												//	   If DS>=0
		WINNER=A; LOSER=B;								//	      WINNER=A : LOSER=B
		S3=S2/15;													//	      S3=S2/15
	} else {														//	   Else
		WINNER=B; LOSER=A;								//	      WINNER=B : LOSER=A
		//!!! BUG tu pewnie powinno byc S3=S1/15;
		S3=S2/15;													//	      S3=S2/15
	}																		//	   End If
	ZABIJ_ARMIE(LOSER);									//	   ZABIJ_ARMIE[LOSER]
	if( LOSER<40 ) B_CLEAR(LOSER);			//	   If LOSER<40 : B_CLEAR[LOSER] : End If
	for(I=1;I<=10;++I) {								//	   For I=1 To 10
		ARMIA[WINNER][I][TE] -= S3;				//	      Add ARMIA(WINNER,I,TE),-S3
		if( ARMIA[WINNER][I][TE]<0 )			//	      If ARMIA(WINNER,I,TE)<0 : ARMIA(WINNER,I,TE)=0 : End If
			ARMIA[WINNER][I][TE] = 0;
		if( ARMIA[WINNER][I][TE]>0 ) {		//	      If ARMIA(WINNER,I,TE)>0
			WOJ++;													//	         Inc WOJ
			SILA += ARMIA[WINNER][I][TSI];	//	         Add SILA,ARMIA(WINNER,I,TSI)
			SILA += ARMIA[WINNER][I][TE];		//	         Add SILA,ARMIA(WINNER,I,TE)
			SPEED += ARMIA[WINNER][I][TSZ];	//	         Add SPEED,ARMIA(WINNER,I,TSZ)
		}																	//	      End If
	}																		//	   Next I
	if( WOJ==0 ) WOJ=1;	//!!! niestandardowe
	SPEED=((SPEED/WOJ)/5);							//	   SPEED=((SPEED/WOJ)/5)
	ARMIA[WINNER][0][TSZ]=SPEED;				//	   ARMIA(WINNER,0,TSZ)=SPEED
	ARMIA[WINNER][0][TSI]=SILA;					//	   ARMIA(WINNER,0,TSI)=SILA
	ARMIA[WINNER][0][TE]=WOJ;						//	   ARMIA(WINNER,0,TE)=WOJ
	Param=LOSER;												//	End Proc[LOSER]
}

void USTAW_WOJSKO(aint A,aint XW,aint YW,aint TYP) {
	//	Procedure USTAW_WOJSKO[A,XW,YW,TYP]

	aint I=0,I2=0,X1=0,Y1=0,XW2=0,YW2=0,X=0,Y=0,BAZA=0,BNR=0,STREFA2=0;
	X1=XW*200;														//	   X1=XW*200
	Y1=YW*160;														//	   Y1=YW*160
	for(I=1;I<=10;++I) {									//	   For I=1 To 10
		if( ARMIA[A][I][TE]>0 ) {						//	      If ARMIA(A,I,TE)>0
			if( A==WRG ) {										//	         If A=WRG
				I2=I+10;												//	            I2=I+10
			}																	//	         End If
			if( A==ARM ) {										//	         If A=ARM
				I2=I;														//	            I2=I
			}																	//	         End If
																				//
			if( TYP==1 ) {										//	         If TYP=1
				AGAIN2:													//	            AGAIN2:
				XW2=Rnd(2);											//	            XW2=Rnd(2)
				YW2=Rnd(2);											//	            YW2=Rnd(2)
				if( XW2==XW && YW2==YW ) {			//	            If XW2=XW and YW2=YW
					goto AGAIN2;									//	               Goto AGAIN2
				}																//	            End If
				X1=XW2*200;											//	            X1=XW2*200
				Y1=YW2*160;											//	            Y1=YW2*160
			}																	//	         End If
			if( TYP==2 ) {										//	         If TYP=2
				X1=Rnd(2)*200;									//	            X1=Rnd(2)*200
			}																	//	         End If
			if( TYP==3 ) {										//	         If TYP=3
				Y1=Rnd(2)*160;									//	            Y1=Rnd(2)*160
			}																	//	         End If
			AGAIN:														//	         AGAIN:
			X=Rnd(200)+X1+16;									//	         X=Rnd(200)+X1+16
			Y=Rnd(160)+Y1+20;									//	         Y=Rnd(160)+Y1+20
			if( _Zone(X,Y)==0 ) {							//	         If Zone(X,Y)=0
				ARMIA[A][I][TX]=X;							//	            ARMIA(A,I,TX)=X
				ARMIA[A][I][TY]=Y;							//	            ARMIA(A,I,TY)=Y
				BAZA=RASY[ARMIA[A][I][TRASA]][7];//	            BAZA=RASY(ARMIA(A,I,TRASA),7)
				ARMIA[A][I][TBOB]=BAZA;					//	            ARMIA(A,I,TBOB)=BAZA
				if( A==ARM ) {									//	            If A=ARM
					if( KTO_ATAKUJE==ARM ) {			//	               If KTO_ATAKUJE=ARM
						BNR=BAZA+1;									//	                  BNR=BAZA+1
					} else {											//	               Else
						BNR=BAZA+7;									//	                  BNR=BAZA+7
					}															//	               End If
					_Bob(I2,X,Y,BNR);							//	               Bob I2,X,Y,BNR
					STREFA2=_Zone(X,Y+30);				//	               STREFA2=Zone(X,Y+30)
					if( STREFA2>20 && STREFA2<31 ) {//	               If STREFA2>20 and STREFA2<31
						LimitBob(I2,0,0,640,114);		//	                  Limit Bob I2,0,0 To 640,114
					} else {											//	               Else
						LimitBob(I2,0,0,640,512);		//	                  Limit Bob I2,0,0 To 640,512
					}															//	               End If
				}																//	            End If
				SetZone(I2,X-16,Y-20,X+16,Y);		//	            Set Zone I2,X-16,Y-20 To X+16,Y
			} else {													//	         Else
				goto AGAIN;											//	            Goto AGAIN
			}																	//	         End If
		}																		//	      End If
	}																			//	   Next I
																				//	End Proc
}

void OBLICZ_POWER(aint PL) {
	//	Procedure OBLICZ_POWER[PL]

	aint I=0,OPOWER=0;
	OPOWER=0;												//	   OPOWER=0
	if( GAME_OVER==0 ) {						//	   If Not GAME_OVER
		if( PL==1 ) GAME_OVER=-1;			//	      If PL=1 : GAME_OVER=True : End If
		for(I=0;I<=40;++I) {					//	      For I=0 To 40
			if( ARMIA[I][0][TMAG]==PL ) {//	         If ARMIA(I,0,TMAG)=PL
				if( ARMIA[I][0][TE]>0 ) {	//	            If ARMIA(I,0,TE)>0
					if( PL==1 ) GAME_OVER=0;//	               If PL=1 : GAME_OVER=False : End If
					OPOWER += ARMIA[I][0][TSI];//	               Add OPOWER,ARMIA(I,0,TSI)
				}													//	            End If
			}														//	         End If
		}															//	      Next
		for(I=0;I<=49;++I) {					//	      For I=0 To 49
			if( MIASTA[I][0][M_CZYJE]==PL ) {//	         If MIASTA(I,0,M_CZYJE)=PL
				if( PL==1 ) GAME_OVER=0;	//	            If PL=1 : GAME_OVER=False : End If
				OPOWER +=	MIASTA[I][0][M_LUDZIE]*2;//	            Add OPOWER,MIASTA(I,0,M_LUDZIE)*2
			}														//	         End If
		}															//	      Next
		OPOWER += DZIEN*20;						//	      Add OPOWER,DZIEN*20
		OPOWER += GRACZE[PL][1]/10;		//	      Add OPOWER,GRACZE(PL,1)/10
		GRACZE[PL][2]=OPOWER;					//	      GRACZE(PL,2)=OPOWER
	}																//	   End If
	Param=OPOWER;										//	End Proc[OPOWER]
}
