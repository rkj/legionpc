
#include <cmath>

#include "Amos.h"

#include "legion.h"
#include "lgn_akcja.h"
#include "lgn_diskacs.h"
#include "lgn_ekran1.h"
#include "lgn_przygoda.h"
#include "lgn_sceneria.h"
#include "lgn_sklep.h"
#include "lgn_util.h"
#include "main.h"
#include "utl_locale.h"


void SETUP(astr A_S,astr B_S,astr C_S) {
	//	Procedure SETUP[A$,B$,C$]

	aint X=0;
																		//	   'A$="--------"
																		//	   'B$="Bitwa"
																		//	   'C$="********"
	if( PREFS[3]==1 ) {								//	   If PREFS(3)=1 : _TRACK_FADE[1] : End If
		TrackFade(1);
	}
	EraseAll();												//	   Erase All
	Gfx::Color(0,0,0); _ClearRaster();
	//	   Hide On
	ScreenOpen(2,80,50,32,LOWRES);		//	   Screen Open 2,80,50,32,Lowres : Curs Off : Flash Off : Screen Display 2,252,140,80,50 : Cls 0
	ScreenDisplay(2,252,140,80,50);
	Gfx::Cls(0,0,0);
	SetFont(FON2);										//	   Set Font FON2
	Gfx::Color(1.0f,0.8f,0.1f);				//	   Ink 19,0
	X=40-(TextLength(A_S)/2); Text(X,15,A_S);	//	   X=40-(Text Length(A$)/2) : Text X,15,A$
	X=40-(TextLength(B_S)/2); Text(X,28,B_S);	//	   X=40-(Text Length(B$)/2) : Text X,28,B$
	X=40-(TextLength(C_S)/2); Text(X,40,C_S);	//	   X=40-(Text Length(C$)/2) : Text X,40,C$
	WaitVbl();
																		//	   View
																		//	   '---------------
																		//	   'Auto View Off
	ScreenOpen(0,640,512,32,LOWRES);	//	   Screen Open 0,640,512,32,Lowres : Screen Display 0,130,40,320,234 : Screen 0
	ScreenDisplay(0,130,40,320,234);
	Screen(0);
	Gfx::Cls(0,0,0);									//	   Curs Off : Flash Off : Cls 0
																		//	   Priority On : Priority Reverse Off
	BobUpdateOnOff(false);						//	   Double Buffer : Autoback 1 : Bob Update Off : Screen Hide
	ReserveZone(200);									//	   Reserve Zone 200
																		//	   '------------------
	ScreenOpen(1,320,160,32,LOWRES);	//	   Screen Open 1,320,160,32,Lowres : Screen Display 1,130,275,320,25 : Screen 1
	ScreenDisplay(1,130,275,320,25);
	Screen(1);
																		//	   Screen Hide 1
																		//	   Screen To Front 2
																		//	   Screen 1 : Curs Off : Flash Off : Cls 10
	ReserveZone(100);									//	   Reserve Zone 100
	_LOAD(KAT_S+"dane/gad","dane:gad","Dane",0);//	   _LOAD[KAT$+"dane/gad","dane:gad","Dane",0]
	USTAW_FONT("defender2",FONT_DEFENDER,8,1);			//	   USTAW_FONT["defender2",8]
																		//	   Get Bob Palette : Screen Show
																		//	   '------------------
	Screen(0);												//	   Screen 0 : Screen Show
	SamBank(4);												//	   Sam Bank 4
	_LOAD(KAT_S+"dane/sound","dane:sound","Dane",8);		//	   _LOAD[KAT$+"dane/sound","dane:sound","Dane",8]
	Mvolume(50);											//	   Mvolume 50
	_LOAD(KAT_S+"dane/glowny","dane:glowny","Dane",1);	//	   _LOAD[KAT$+"dane/glowny","dane:glowny","Dane",1]
	USTAW_FONT("defender2",FONT_DEFENDER,8,1);			//	   USTAW_FONT["defender2",8]
																		//	   Get Bob Palette
	GOBY=0;														//	   GOBY=0
	PIKIETY=50;												//	   PIKIETY=50
	BUBY=PIKIETY+18+10;								//	   BUBY=PIKIETY+18+10
	POTWORY=BUBY+131+32;							//	   POTWORY=BUBY+131+32
	BIBY=POTWORY+16;									//	   BIBY=POTWORY+16
	BSIBY=BIBY+12;										//	   BSIBY=BIBY+12
	CELOWNIK=52;											//	   CELOWNIK=52
	MSX=320; MSY=278;									//	   MSX=320 : MSY=278
	HotSpot(3+BUBY,0x00);							//	   Hot Spot 3+BUBY,$0
																		//	   Screen To Back 2
																		//	End Proc
}

void MAIN_ACTION(void) {
	//glowna petla akcji w terenie

																					//	Procedure MAIN_ACTION
	aint I=0, X1=0, Y1=0, HY=0, STREFA0=0, KLAW=0, STREFA=0, J=0,
	     WOJ1=0, WOJ2=0, SILA=0, SILA2=0, SPEED=0, SPEED2=0;
	astr A_S="";

	KONIEC_AKCJI=0;													//	   KONIEC_AKCJI=False
	WYNIK_AKCJI=0;													//	   WYNIK_AKCJI=0
																					//	   'przeîadowanie îuków
	for(I=1;I<=10;++I) STRZALY[I]=10;				//	   For I=1 To 10 : STRZALY(I)=10 : Next I
	Screen(2);															//	   Screen 2 : Get Palette 0
	Screen(0);															//	   Screen 0
	ChangeMouse(BUBY+6);										//	   Change Mouse BUBY+6 : Show On
	Screen(1);															//	   Screen 1 : USTAW_FONT["defender2",8] : Screen To Front 1
	USTAW_FONT("defender2",FONT_DEFENDER,8,1);
	NUMER=1;																//	   NUMER=1
	EKRAN1();																//	   EKRAN1
	Screen(0);															//	   Screen 0
	MARKERS();															//	   MARKERS
	SELECT(ARM,NUMER);											//	   SELECT[ARM,NUMER]
	X1=ARMIA[ARM][NUMER][TX];								//	   X1=ARMIA(ARM,NUMER,TX)
	Y1=ARMIA[ARM][NUMER][TY];								//	   Y1=ARMIA(ARM,NUMER,TY)
	CENTER(X1,Y1,0);												//	   CENTER[X1,Y1,0]
																					//
																					//	   'Auto View On :
																					//	   View
	BobUpdate(); WaitVbl();									//	   Bob Update : Wait Vbl
																					//
	do {																		//	   Do
		Screen(0);														//	      Screen 0
		rysuj();
		WaitVbl();
		HY=YMouse();													//	      HY=Y Mouse
		if( MouseClick() ) {									//	      If Mouse Click=1
			STREFA0=MouseZone();								//	         STREFA0=Mouse Zone
			if( STREFA0<11 && STREFA0>0 ) {			//	         If STREFA0<11 and STREFA0>0
				NUMER=STREFA0;										//	            NUMER=STREFA0
				SELECT(ARM,NUMER);								//	            SELECT[ARM,NUMER]
			}																		//	         End If
			if( STREFA0>10 && STREFA0<21 ) {		//	         If STREFA0>10 and STREFA0<21
				Screen(1);												//	            Screen 1
				WYKRESY(WRG,STREFA0-10);					//	            WYKRESY[WRG,STREFA0-10]
				do {
					ProcessEvents();
				} while( MouseKey()==LEWY );			//	            While Mouse Key=LEWY : Wend
				if( NUMER>0 ) WYKRESY(ARM,NUMER);	//	            If NUMER>0 : WYKRESY[ARM,NUMER] : End If
			}																		//	         End If
		}																			//	      End If
																					//
		A_S="";																//	      A$=""
		A_S=Inkey_S();												//	      A$=Inkey$
		KLAW=ScanCode();											//	      KLAW=Scancode
		if( MouseKey()==PRAWY ) SKROL(0);			//	      If Mouse Key=PRAWY : SKROL[0] : End If
		if( KLAW>75 && KLAW<80 ) {						//	      If KLAW>75 and KLAW<80
			KLAWSKROL(KLAW);										//	         KLAWSKROL[KLAW]
		}																			//	      End If
		if( KLAW>=80 && KLAW<90 ) {						//	      If KLAW>=80 and KLAW<90
			SELECT(ARM,KLAW-79);								//	         SELECT[ARM,KLAW-79]
			CENTER(ARMIA[ARM][NUMER][TX],ARMIA[ARM][NUMER][TY],2);//	         CENTER[ARMIA(ARM,NUMER,TX),ARMIA(ARM,NUMER,TY),2]
		}																			//	      End If
		if( A_S!="" ) {												//	      If A$<>""
			HY=300;															//	         HY=300
		}																			//	      End If
		if( KONIEC_AKCJI!=0 ) break;					//	      Exit If KONIEC_AKCJI
		while( HY>275 ) {											//	      While HY>275
			rysuj();
			WaitVbl();
			Screen(1);													//	         Screen 1
			if( A_S!="" || (MouseClick() && NUMER>0) ) {//	         If A$<>"" or Mouse Click=1 and NUMER>0
				GADUP(LAST_GAD);									//	            GADUP[LAST_GAD]
				STREFA=MouseZone();								//	            STREFA=Mouse Zone
				A_S=Upper_S(A_S);									//	            A$=Upper$(A$)
				if( A_S==GS("K_MOVE") ) STREFA=1;	//	            If A$="M" : STREFA=1 : End If
				if( A_S==GS("K_ATACK") ) STREFA=2;//	            If A$="A" : STREFA=2 : End If
				if( A_S==GS("K_SHOOT") ) STREFA=3;//	            If A$="S" : STREFA=3 : End If
				if( A_S==GS("K_TALK") ) STREFA=4;	//	            If A$="T" : STREFA=4 : End If
				if( A_S==GS("K_ACTION") ) STREFA=10;//	            If A$=" " : STREFA=10 : End If

				if( A_S=="P" ) {	//F12
					LOG("-------SNAPSHOT--------");
					aint scr = Screen();
					Screen(0);
					void *sb = StoreBuffer(0,0,320,256);
					WriteBuffer2File(sb,"snapshot.png");
					FreeBuffer(sb);
					Screen(scr);
				}

				if( (KeyState(69)!=0 && IMIONA_S[1]=="Marcin ®") || ARMIA[ARM][0][TE]==0 || KONIEC_AKCJI!=0 )							//	            If(Key State(69) and IMIONA$(1)="Marcin ®") or ARMIA(ARM,0,TE)=0 or KONIEC_AKCJI : Exit 2 : End If
					goto SKIP;

				if( STREFA==20 || STREFA==21 ) {	//	            If STREFA=20 or STREFA=21 : BRON_INFO[STREFA] : End If
					BRON_INFO(STREFA);
				}
				if( STREFA>0 && STREFA<11 ) {			//	            If STREFA>0 and STREFA<11
					GADDOWN(STREFA);								//	               GADDOWN[STREFA]
					LAST_GAD=STREFA;								//	               LAST_GAD=STREFA
					if( STREFA==1 ) {								//	               If STREFA=1
						RUCH();												//	                  RUCH
					}																//	               End If
					if( STREFA==2 ) {								//	               If STREFA=2
						_ATAK(2);											//	                  _ATAK[2]
					}																//	               End If
					if( STREFA==3 ) {								//	               If STREFA=3
						STRZAL();											//	                  STRZAL
					}																//	               End If
					if( STREFA==4 ) {								//	               If STREFA=4
						_ATAK(6);											//	                  _ATAK[6]
					}																//	               End If
					if( STREFA==10 ) {							//	               If STREFA=10
						AKCJA();											//	                  AKCJA
					}																//	               End If
					if( STREFA==5 ) {								//	               If STREFA=5
						GADGET(170,2,20,20,"bob9",2,0,19,5,0);//	                  GADGET[170,2,20,20,"bob9",2,0,19,5,0]
						WYBOR(0);											//	                  WYBOR[0]
					}																//	               End If
					if( STREFA==9 ) {								//	               If STREFA=9
						GADGET(147,2,20,20,"bob15",2,0,19,5,0);//	                  GADGET[147,2,20,20,"bob15",2,0,19,5,0]
						ROZKAZ();											//	                  ROZKAZ
						if( KONIEC_AKCJI!=0 ) {				//	                  If KONIEC_AKCJI
							goto SKIP;									//	                     Exit 2
						}															//	                  End If
					}																//	               End If
				}																	//	            End If
			}																		//	         End If
			A_S="";															//	         A$=""
			A_S=Inkey_S();											//	         A$=Inkey$

			//### - ulepszenie
			KLAW=ScanCode();
			if( KLAW>75 && KLAW<80 ) {
				KLAWSKROL(KLAW);
			}
			if( KLAW>=80 && KLAW<90 ) {
				SELECT(ARM,KLAW-79);
				CENTER(ARMIA[ARM][NUMER][TX],ARMIA[ARM][NUMER][TY],2);
			}

			ClearKey();													//	         Clear Key
			HY=YMouse();												//	         HY=Y Mouse
		}																			//	      Wend
	} while(true);													//	   Loop
	SKIP:

																					//	   '------------------
	Screen(0);															//	   Screen 0 :
//Fade 2
	Screen(1);															//	   Screen 1 :
	for(J=0;J<=25;++J) {										//	   For J=0 To 25 : Screen Display 1,130,275+J,320,25-J : Wait Vbl : View : Next
		ScreenDisplay(1,130,275+J,320,25-J);
		WaitVbl();
	}
	ScreenClose(1);													//	   Screen Close 1
	for(J=0;J<=110;++J) {										//	   For J=0 To 110
		for(I=0;I<=4;++I) {										//	      For I=0 To 4
			GLEBA[J][I]=0;											//	         GLEBA(J,I)=0
		}																			//	      Next I
	}																				//	   Next J
	WOJ1=0; WOJ2=0;													//	   WOJ1=0 : WOJ2=0
																					//	   'update------------
	for(I=1;I<=10;++I) {										//	   For I=1 To 10
		if( ARMIA[WRG][I][TE]>0 ) {						//	      If ARMIA(WRG,I,TE)>0
			WOJ2++;															//	         Inc WOJ2
			SILA2+=ARMIA[WRG][I][TSI];					//	         Add SILA2,ARMIA(WRG,I,TSI)
			SPEED2+=ARMIA[WRG][I][TSZ];					//	         Add SPEED2,ARMIA(WRG,I,TSZ)
		} else {															//	      Else
			ARMIA[WRG][I][TE]=0;								//	         ARMIA(WRG,I,TE)=0
		}																			//	      End If
		if( ARMIA[ARM][I][TE]>0 ) {						//	      If ARMIA(ARM,I,TE)>0
			WOJ1++;															//	         Inc WOJ1
			SILA+=ARMIA[ARM][I][TSI];						//	         Add SILA,ARMIA(ARM,I,TSI)
			SPEED+=ARMIA[ARM][I][TSZ];					//	         Add SPEED,ARMIA(ARM,I,TSZ)
		} else {															//	      Else
			ARMIA[ARM][I][TE]=0;								//	         ARMIA(ARM,I,TE)=0
		}																			//	      End If
		ARMIA[ARM][I][TTRYB]=0;								//	      ARMIA(ARM,I,TTRYB)=0
		ARMIA[WRG][I][TTRYB]=0;								//	      ARMIA(WRG,I,TTRYB)=0
	}																				//	   Next I
	if( WOJ1>0 ) SPEED=((SPEED/WOJ1)/5);		//	   If WOJ1>0 : SPEED=((SPEED/WOJ1)/5) : End If
	if( WOJ2>0 ) SPEED2=((SPEED2/WOJ2)/5);	//	   If WOJ2>0 : SPEED2=((SPEED2/WOJ2)/5) : End If
	ARMIA[ARM][0][TE]=WOJ1;									//	   ARMIA(ARM,0,TE)=WOJ1
	ARMIA[ARM][0][TSI]=SILA;								//	   ARMIA(ARM,0,TSI)=SILA
	ARMIA[ARM][0][TSZ]=SPEED;								//	   ARMIA(ARM,0,TSZ)=SPEED
	ARMIA[WRG][0][TE]=WOJ2;									//	   ARMIA(WRG,0,TE)=WOJ2
	ARMIA[WRG][0][TSI]=SILA2;								//	   ARMIA(WRG,0,TSI)=SILA2
	ARMIA[WRG][0][TSZ]=SPEED2;							//	   ARMIA(WRG,0,TSZ)=SPEED2
	KTO_ATAKUJE=-1;													//	   KTO_ATAKUJE=-1
	_M_FADE(1);															//	   _M_FADE[1]
	EraseAll();															//	   Erase All
	SamStop(-1);														//	   Sam Stop
	ScreenClose(2);													//	   Screen Close 2
	ScreenClose(0);													//	   Screen Close 0
																					//	End Proc
}
void AKCJA(void) {
																					//	Procedure AKCJA
	aint WOJ=0, KLAW=0, HALAS=0, I=0, TRYB=0, BAZA=0, BNR=0, STREFA0=0;
	astr A_S="";

	Screen(0);															//	   Screen 0
	BobOnOff(50,false);											//	   Bob Off 50
	BobOnOff(51,false);											//	   Bob Off 51
	MARKERS_OFF();													//	   MARKERS_OFF
	WOJ=0;																	//	   WOJ=0
	MUZYKA=-1;															//	   MUZYKA=True
	do {																		//	   Repeat
		if( MouseKey()==PRAWY ) {							//	      If Mouse Key=PRAWY
			Screen(0);													//	         Screen 0
			SKROL(0);														//	         SKROL[0]
		}																			//	      End If
		A_S="";																//	      A$=""
		A_S=Inkey_S();												//	      A$=Inkey$
		KLAW=ScanCode();											//	      KLAW=Scancode
		if( KLAW>75 && KLAW<80 ) {						//	      If KLAW>75 and KLAW<80
			KLAWSKROL(KLAW);										//	         KLAWSKROL[KLAW]
		}																			//	      End If
		HALAS=0;															//	      HALAS=0
		for(I=1;I<=10;++I) {									//	      For I=1 To 10
			if( ARMIA[ARM][I][TE]>0 ) {					//	         If ARMIA(ARM,I,TE)>0
				WOJ++;														//	            Inc WOJ
				TRYB=ARMIA[ARM][I][TTRYB];				//	            TRYB=ARMIA(ARM,I,TTRYB)
				if( TRYB==0 ) {										//	            If TRYB=0
					BAZA=ARMIA[ARM][I][TBOB];				//	               BAZA=ARMIA(ARM,I,TBOB)
					if( KTO_ATAKUJE==ARM ) {				//	               If KTO_ATAKUJE=ARM
						BNR=BAZA+1;										//	                  BNR=BAZA+1
					} else {												//	               Else
						BNR=BAZA+7;										//	                  BNR=BAZA+7
					}																//	               End If
					_Bob(I,NOPARI,NOPARI,BNR);			//	               Bob I,,,BNR
					goto SKIP1;											//	               Goto SKIP1
				}																	//	            End If
				if( TRYB==1 ) {										//	            If TRYB=1
					A_RUCH(ARM,I);									//	               A_RUCH[ARM,I]
					goto SKIP1;											//	               Goto SKIP1
				}																	//	            End If
				if( TRYB==2 ) {										//	            If TRYB=2
					A_ATAK(ARM,I);									//	               A_ATAK[ARM,I]
					HALAS++;												//	               Inc HALAS
					goto SKIP1;											//	               Goto SKIP1
				}																	//	            End If
				if( TRYB==3 ) {										//	            If TRYB=3
					A_STRZAL(ARM,I);								//	               A_STRZAL[ARM,I]
					goto SKIP1;											//	               Goto SKIP1
				}																	//	            End If
				if( TRYB==4 || TRYB==5 ) {				//	            If TRYB=4 or TRYB=5
					A_CZAR(ARM,I);									//	               A_CZAR[ARM,I]
					HALAS++;												//	               Inc HALAS
					goto SKIP1;											//	               Goto SKIP1
				}																	//	            End If
				if( TRYB==6 ) {										//	            If TRYB=6
					A_ROZMOWA(ARM,I);								//	               A_ROZMOWA[ARM,I]
					goto SKIP1;											//	               Goto SKIP1
				}																	//	            End If
				if( TRYB==7 || TRYB==8 ) {				//	            If TRYB=7 or TRYB=8
					A_LOT(ARM,I,TRYB);							//	               A_LOT[ARM,I,TRYB]
					goto SKIP1;											//	               Goto SKIP1
				}																	//	            End If
				SKIP1:														//	            SKIP1:
					;
			} else {														//	         Else
				//CZEKAJ();													//	            CZEKAJ
			}																		//	         End If
																					//
																					//
			if( ARMIA[WRG][I][TE]>0 ) {					//	         If ARMIA(WRG,I,TE)>0
				TRYB=ARMIA[WRG][I][TTRYB];				//	            TRYB=ARMIA(WRG,I,TTRYB)
				if( TRYB==0 ) {										//	            If TRYB=0
					WYDAJ_ROZKAZ(I);								//	               WYDAJ_ROZKAZ[I]
					goto SKIP2;											//	               Goto SKIP2
				}																	//	            End If
				if( TRYB==1 ) {										//	            If TRYB=1
					A_RUCH(WRG,I);									//	               A_RUCH[WRG,I]
					if( Rnd(20)==1) WYDAJ_ROZKAZ(I);//	               If Rnd(20)=1 : WYDAJ_ROZKAZ[I] : End If
					goto SKIP2;											//	               Goto SKIP2
				}																	//	            End If
				if( TRYB==2 ) {										//	            If TRYB=2
					A_ATAK(WRG,I);									//	               A_ATAK[WRG,I]
					HALAS++;												//	               Inc HALAS
					if( Rnd(10)==1 ) WYDAJ_ROZKAZ(I);//	               If Rnd(10)=1 : WYDAJ_ROZKAZ[I] : End If
					goto SKIP2;											//	               Goto SKIP2
				}																	//	            End If
				if( TRYB==3 ) {										//	            If TRYB=3
					A_STRZAL(WRG,I);								//	               A_STRZAL[WRG,I]
					goto SKIP2;											//	               Goto SKIP2
				}																	//	            End If
				if( TRYB==4 || TRYB==5 ) {				//	            If TRYB=4 or TRYB=5
					A_CZAR(WRG,I);									//	               A_CZAR[WRG,I]
					HALAS++;												//	               Inc HALAS
					goto SKIP2;											//	               Goto SKIP2
				}																	//	            End If
				if( TRYB==7 || TRYB==8 ) {				//	            If TRYB=7 or TRYB=8
					A_LOT(WRG,I,TRYB);							//	               A_LOT[WRG,I,TRYB]
					goto SKIP2;											//	               Goto SKIP2
				}																	//	            End If
				SKIP2:														//	            SKIP2:
					;
			} else {														//	         Else
				//CZEKAJ();													//	            CZEKAJ
			}																		//	         End If
																					//
		}																			//	      Next I

		//90 normalnie (jak na emulatorze Amigi)
		WaitMilisec(action_delay);

		rysuj();
		BobUpdate(); WaitVbl();								//	      Bob Update : Wait Vbl
		//!!! na PC wylaczam sterowanie muzyka, bo kanalow Ci u nas dostatek ;-)
		//		if( HALAS>3 && MUZYKA!=0 ) {					//	      If HALAS>3 and MUZYKA
		//			MusicStop();												//	         Music Stop
		//			MUZYKA=0;														//	         MUZYKA=False
		//		}																			//	      End If
		//																					//
		//		if( HALAS<=3 && MUZYKA==0 ) {					//	      If HALAS<=3 and MUZYKA=False
		//			MUZYKA=-1;													//	         MUZYKA=True
		//			Music(1);														//	         Music 1
		//		}																			//	      End If
																					//
	//### - ulepszenie
	//} while( !(MouseKey()==LEWY || Inkey_S()==" " || WOJ==0) );//	   Until Mouse Key=LEWY or Inkey$=" " or WOJ=0
	} while( !(MouseKey()==LEWY || A_S==" " || WOJ==0) );//	   Until Mouse Key=LEWY or Inkey$=" " or WOJ=0

	SamLoop(false);											//	   Sam Loop Off
	if( MUZYKA==0 ) {												//	   If Not MUZYKA : Sam Stop : Music 1 : End If
		SamStop(-1);
		Music(1);
	}
	MARKERS();															//	   MARKERS
	if( WOJ==0 ) {													//	   If WOJ=0 : ARMIA(ARM,0,TE)=0 : WYNIK_AKCJI=2 : End If
		ARMIA[ARM][0][TE]=0;
		WYNIK_AKCJI=2;
	}
	GADUP(10);															//	   GADUP[10]
	STREFA0=MouseZone();										//	   STREFA0=Mouse Zone
	if( STREFA0<11 && STREFA0>0 ) {					//	   If STREFA0<11 and STREFA0>0
		NUMER=STREFA0;												//	      NUMER=STREFA0
	}																				//	   End If
	SELECT(ARM,NUMER);											//	   SELECT[ARM,NUMER]
																					//	End Proc
}

class WyborVars {
public:
	aint X, Y, BB, BR, TYP, XM, YM, I, BR1, KONIEC, SEK, X2, Y2,
			 PLACE, BR2, WT, B, B1, BB1, B2, BB2, B3, BB3, XB, YB,
			 STREFA, RASA, BR_INFO;
	astr EN_S, MAG_S, GLOB_S;

	WyborVars(void) {
		X=0; Y=0; BB=0; BR=0; TYP=0; XM=0; YM=0; I=0; BR1=0; KONIEC=0; SEK=0; X2=0; Y2=0;
		PLACE=0; BR2=0; WT=0; B=0; B1=0; BB1=0; B2=0; BB2=0; B3=0; BB3=0; XB=0; YB=0;
		STREFA=0; RASA=0; BR_INFO=0;
		EN_S=""; MAG_S=""; GLOB_S="";
	}
	~WyborVars() {
	}
};
void _WYBOR_WYPISZ(WyborVars &v) {
																																		//	   'Wait Vbl
																																		//	   Gr Writing 1
	gad_back(1.0); _Bar(236,v.Y+1,236+73,v.Y+98);											//	   Ink 19,19 : Bar 236,Y+1 To 236+73,Y+98
	v.EN_S=Minus_S(Str_S(ARMIA[ARM][NUMER][TE])+"/"+Str_S(ARMIA[ARM][NUMER][TEM])," ");//	   EN$=Str$(ARMIA(ARM,NUMER,TE))+"/"+Str$(ARMIA(ARM,NUMER,TEM))-" "
	v.MAG_S=Minus_S(Str_S(ARMIA[ARM][NUMER][TMAG])+"/"+Str_S(ARMIA[ARM][NUMER][TMAGMA])," ");//	   MAG$=Str$(ARMIA(ARM,NUMER,TMAG))+"/"+Str$(ARMIA(ARM,NUMER,TMAGMA))-" "
	gad_text(1.0);																										//	   Ink 3,19
	Text(237,15,ARMIA_S[ARM][NUMER]);																	//	   Text 237,15,ARMIA$(ARM,NUMER)
	Text(237,25,RASY_S[ARMIA[ARM][NUMER][TRASA]]);										//	   Text 237,25,RASY$(ARMIA(ARM,NUMER,TRASA))
	Text(237,35,GS("008"));																						//	   Text 237,35,"Energy:"
	Text(237,45,GS("009"));																						//	   Text 237,45,"Strength:"
	Text(237,55,GS("010"));																						//	   Text 237,55,"Speed:"
	Text(237,65,GS("011"));																						//	   Text 237,65,"Resistance:"
	Text(237,75,GS("012"));																						//	   Text 237,75,"Magic:"
	Text(237,95,GS("013"));																						//	   Text 237,95,"Experience:"
	if( ARMIA[ARM][NUMER][TWAGA]>ARMIA[ARM][NUMER][TEM] ) {						//	   If ARMIA(ARM,NUMER,TWAGA)>ARMIA(ARM,NUMER,TEM)
		Gfx::Color(1.f,0.f,0.f);																				//	      Ink 20,19
	}																																	//	   End If
	Text(237,85,GS("014"));																						//	   Text 237,85,"Weight:"
																																		//
	gad_text(1.0);																										//	   Ink 16,19
	Text(270,35,v.EN_S);																							//	   Text 270,35,EN$
	Text(290,45,Str_S(ARMIA[ARM][NUMER][TSI]));												//	   Text 290,45,Str$(ARMIA(ARM,NUMER,TSI))
	Text(290,55,Str_S(ARMIA[ARM][NUMER][TSZ]));												//	   Text 290,55,Str$(ARMIA(ARM,NUMER,TSZ))
	Text(290,65,Str_S(ARMIA[ARM][NUMER][TP]));												//	   Text 290,65,Str$(ARMIA(ARM,NUMER,TP))
	Text(270,75,v.MAG_S);																							//	   Text 270,75,MAG$
	Text(290,85,Str_S(ARMIA[ARM][NUMER][TWAGA]));											//	   Text 290,85,Str$(ARMIA(ARM,NUMER,TWAGA))
	Text(295,95,Str_S(ARMIA[ARM][NUMER][TDOSW]));											//	   Text 295,95,Str$(ARMIA(ARM,NUMER,TDOSW))
	return;																														//	   Return
}
void	_WYBOR_PICK_2(WyborVars &v) {
																																		//	   Hide On
	v.BB=BRON[v.BR][B_BOB]+BROBY;																			//	   BB=BRON(BR,B_BOB)+BROBY
	HotSpot(v.BB,0x11);																								//	   Hot Spot BB,$11
	v.TYP=BRON[v.BR][B_TYP];																					//	   TYP=BRON(BR,B_TYP)
																																		//	   No Mask BB+GOBY
	gad_back(1.0); _Bar(v.X+6,71,v.X+98,88);													//	   Ink 19 : Bar X+6,71 To X+98,88
	gad_text(1.0);																										//	   Ink 3,19 : Text 130,78,BRON$(BR) : Text 192,78,"W:"+Str$(BRON(BR,B_WAGA))
	if( GetLang()=="PL" ) {
		Text(130,78,BRON2_S[v.TYP]);
		Text(192,78,GS("015")+Str_S(BRON[v.BR][B_WAGA]));
		Text(130,87,BRON_S[v.BR]);																			//	   Text 130,87,BRON2$(TYP)
	} else {
		Text(130,78,BRON_S[v.BR]);
		Text(192,78,GS("015")+Str_S(BRON[v.BR][B_WAGA]));
		Text(130,87,BRON2_S[v.TYP]);																			//	   Text 130,87,BRON2$(TYP)
	}
	return;																														//	   Return
}
void _WYBOR_SHOW_INFO(aint BR) {
	aint TYP=BRON[BR][B_TYP], XM, YM, DL;
	astr NAME;

	if( GetLang()=="PL" ) {
		NAME = BRON2_S[TYP] + " " + BRON_S[BR];
	} else {
		NAME = BRON_S[BR] + " " + BRON2_S[TYP];
	}
	XM=XScreen(XMouse())+8;
	YM=YScreen(YMouse())+4;
	DL=TextLength(NAME);
	if( XM+DL+4>330 ) {
		XM=330-DL-4;
	}
	gad_shadow(1.0);
	Text(XM-1,YM-1,NAME);
	Text(XM-1,YM+1,NAME);
	Text(XM+1,YM-1,NAME);
	Text(XM+1,YM+1,NAME);
	gad_text(1.0);
	Text(XM,YM,NAME);
}
void	_WYBOR_PICK(WyborVars &v) {
	_WYBOR_PICK_2(v);																									//	   Gosub PICK_2
	_store_ekran1_wybor();
	do {																															//	   Repeat
		v.XM=XScreen(XMouse());																					//	      XM=X Screen(X Mouse)
		v.YM=YScreen(YMouse());																					//	      YM=Y Screen(Y Mouse)
																																		//
		//!!! inny nr sprite
		Sprite(3,XMouse(),YMouse(),v.BB+GOBY);													//	      Sprite 53,X Mouse,Y Mouse,BB+GOBY : Wait Vbl
		rysuj(); WaitVbl();
		if( MouseClick()==1 ) {																					//	      If Mouse Click=1
			v.I=_Zone(v.XM,v.YM);																					//	         I=Zone(XM,YM)
			if( v.I!=0 ) {																								//	         If I<>0
				//!!! inny nr sprite
				SpriteOnOff(3,false);																				//	            Sprite Off 53 : Wait Vbl
				HotSpot(v.BB,0x00);																					//	            Hot Spot BB,$0
			}																															//	         End If
			//cos co jest w plecaku (gorny rzadek)
			if( v.I>0 && v.I<5 ) {																				//	         If I>0 and I<5
				_restore_ekran1();
				v.BR1=ARMIA[ARM][NUMER][TPLECAK+v.I-1];											//	            BR1=ARMIA(ARM,NUMER,TPLECAK+I-1)
				v.TYP=BRON[v.BR][B_TYP];																		//	            TYP=BRON(BR,B_TYP)
				if( v.TYP==17 ) {																						//	            If TYP=17
					ARMIA[ARM][NUMER][TPLECAK+v.I-1]=0;												//	               ARMIA(ARM,NUMER,TPLECAK+I-1)=0
					Add(ARMIA[ARM][0][TAMO],BRON[v.BR][B_DOSW],ARMIA[ARM][0][TAMO],320);//       Add ARMIA(ARM,0,TAMO),BRON(BR,B_DOSW),ARMIA(ARM,0,TAMO) To 320
				} else {																										//	            Else
					gad_back(1.0); _Bar(v.X+6+((v.I-1)*25),v.Y+6,v.X+6+((v.I-1)*25)+18,v.Y+6+18);
					PasteBob(v.X+7+((v.I-1)*25),v.Y+7,v.BB+GOBY);							//	               Paste Bob X+7+((I-1)*25),Y+7,BB+GOBY
					ARMIA[ARM][NUMER][TPLECAK+v.I-1]=v.BR;										//	               ARMIA(ARM,NUMER,TPLECAK+I-1)=BR
				}																														//	            End If
				if( v.BR1==0 ) { v.KONIEC=-1; } else { v.BR=v.BR1; _WYBOR_PICK_2(v); }//	         If BR1=0 : KONIEC=True : Else : BR=BR1 : Gosub PICK_2 : End If
				_store_ekran1_wybor();
			}																															//	         End If
			//cos co jest w plecaku (dolny rzadek)
			if( v.I>4 && v.I<9 ) {																				//	         If I>4 and I<9
				_restore_ekran1();
				v.BR1=ARMIA[ARM][NUMER][TPLECAK+v.I-1];											//	            BR1=ARMIA(ARM,NUMER,TPLECAK+I-1)
				v.TYP=BRON[v.BR][B_TYP];																		//	            TYP=BRON(BR,B_TYP)
				if( v.TYP==17 ) {																						//	            If TYP=17
					ARMIA[ARM][NUMER][TPLECAK+v.I-1]=0;												//	               ARMIA(ARM,NUMER,TPLECAK+I-1)=0
					Add(ARMIA[ARM][0][TAMO],BRON[v.BR][B_DOSW],ARMIA[ARM][0][TAMO],320);//	               Add ARMIA(ARM,0,TAMO),BRON(BR,B_DOSW),ARMIA(ARM,0,TAMO) To 320
				} else {																										//	            Else
					gad_back(1.0); _Bar(v.X+6+((v.I-5)*25),v.Y+31,v.X+6+((v.I-5)*25)+18,v.Y+31+18);
					PasteBob(v.X+7+((v.I-5)*25),v.Y+32,v.BB+GOBY);						//	               Paste Bob X+7+((I-5)*25),Y+32,BB+GOBY
					_store_ekran1_wybor();
					ARMIA[ARM][NUMER][TPLECAK+v.I-1]=v.BR;										//	               ARMIA(ARM,NUMER,TPLECAK+I-1)=BR
				}																														//	            End If
				if( v.BR1==0 ) { v.KONIEC=-1; } else { v.BR=v.BR1; _WYBOR_PICK_2(v); }//	         If BR1=0 : KONIEC=True : Else : BR=BR1 : Gosub PICK_2 : End If
				_store_ekran1_wybor();
			}																															//	         End If
			//cos co lezy na ziemi
			if( v.I>8 && v.I<13 ) {																				//	         If I>8 and I<13
				_restore_ekran1();
				v.BR1=GLEBA[v.SEK][v.I-9];																	//	            BR1=GLEBA(SEK,I-9)
				gad_back(1.0); _Bar(v.X2+6+((v.I-9)*25),v.Y2+6,v.X2+6+((v.I-9)*25)+18,v.Y2+6+18);
				PasteBob(v.X2+7+((v.I-9)*25),v.Y2+7,v.BB+GOBY);							//	            Paste Bob X2+7+((I-9)*25),Y2+7,BB+GOBY : Wait Vbl
				GLEBA[v.SEK][v.I-9]=v.BR;																		//	            GLEBA(SEK,I-9)=BR
				if( v.BR1==0 ) { v.KONIEC=-1; } else { v.BR=v.BR1; _WYBOR_PICK_2(v); }																																	//	         If BR1=0 : KONIEC=True : Else : BR=BR1 : Gosub PICK_2 : End If
				_store_ekran1_wybor();
			}																															//	         End If
			//glowa lub nogi
			if( v.I==13 || v.I==15 ) {																		//	         If I=13 or I=15
				_restore_ekran1();
				v.BR1=ARMIA[ARM][NUMER][TGLOWA+(v.I-13)];										//	            BR1=ARMIA(ARM,NUMER,TGLOWA+(I-13))
				v.PLACE=BRON[v.BR][B_PLACE];																//	            PLACE=BRON(BR,B_PLACE)
				v.TYP=BRON[v.BR][B_TYP];																		//	            TYP=BRON(BR,B_TYP)
				if( v.PLACE==v.I-12 && v.BR1==0 ) {													//	            If PLACE=I-12 and BR1=0
					ARMIA[ARM][NUMER][TGLOWA+(v.I-13)]=v.BR;									//	               ARMIA(ARM,NUMER,TGLOWA+(I-13))=BR
					PRZELICZ(v.I-13,1);																				//	               PRZELICZ[I-13,1]
					if( v.TYP==13 || v.TYP==18 ) {														//	               If TYP=13 or TYP=18
						ARMIA[ARM][NUMER][TGLOWA+(v.I-13)]=0;										//	                  ARMIA(ARM,NUMER,TGLOWA+(I-13))=0
					} else {																									//	               Else
																																		//	                  Make Mask BB+GOBY
						PasteBob(49,10+((v.I-13)*50),v.BB+GOBY);								//	                  Paste Bob 49,10+((I-13)*50),BB+GOBY
					}																													//	               End If
					v.KONIEC=-1;																							//	               KONIEC=True
				}																														//	            End If
				_store_ekran1_wybor();
			}																															//	         End If
			//korpus
			if( v.I==14 ) {																								//	         If I=14
				_restore_ekran1();
				v.BR1=ARMIA[ARM][NUMER][TGLOWA+(v.I-13)];										//	            BR1=ARMIA(ARM,NUMER,TGLOWA+(I-13))
				v.PLACE=BRON[v.BR][B_PLACE];																//	            PLACE=BRON(BR,B_PLACE)
				v.TYP=BRON[v.BR][B_TYP];																		//	            TYP=BRON(BR,B_TYP)
				if( v.PLACE==v.I-12 && v.BR1==0 ) {													//	            If PLACE=I-12 and BR1=0
					ARMIA[ARM][NUMER][TGLOWA+(v.I-13)]=v.BR;									//	               ARMIA(ARM,NUMER,TGLOWA+(I-13))=BR
					PRZELICZ(v.I-13,1);																				//	               PRZELICZ[I-13,1]
					if( v.TYP==13 ) {																					//	               If TYP=13
						ARMIA[ARM][NUMER][TGLOWA+(v.I-13)]=0;										//	                  ARMIA(ARM,NUMER,TGLOWA+(I-13))=0
					} else {																									//	               Else
						PasteBob(49,46,v.BB+GOBY);															//	                  Paste Bob 49,46,BB+GOBY
					}																													//	               End If
					v.KONIEC=-1;																							//	               KONIEC=True
				}																														//	            End If
				_store_ekran1_wybor();
			}																															//	         End If
																																		//
			//lewa reka
			if( v.I==16 ) {																								//	         If I=16
				_restore_ekran1();
				v.BR1=ARMIA[ARM][NUMER][TLEWA];															//	            BR1=ARMIA(ARM,NUMER,TLEWA)
				v.BR2=ARMIA[ARM][NUMER][TPRAWA];														//	            BR2=ARMIA(ARM,NUMER,TPRAWA)
				v.PLACE=BRON[v.BR][B_PLACE];																//	            PLACE=BRON(BR,B_PLACE)
				if( v.BR1==0 ) {																						//	            If BR1=0
					if( v.PLACE==4 || (v.PLACE==6 && v.BR2==0) ) {						//	               If PLACE=4 or(PLACE=6 and BR2=0)
						PasteBob(9,60,v.BB+GOBY);																//	                  Paste Bob 9,60,BB+GOBY
						ARMIA[ARM][NUMER][TLEWA]=v.BR;													//	                  ARMIA(ARM,NUMER,TLEWA)=BR
						PRZELICZ(3,1);																					//	                  PRZELICZ[3,1]
						v.KONIEC=-1;																						//	                  KONIEC=True
					}																													//	               End If
				}																														//	            End If
				_store_ekran1_wybor();
			}																															//	         End If
																																		//
			//prawa reka
			if( v.I==17 ) {																								//	         If I=17
				_restore_ekran1();
				v.BR1=ARMIA[ARM][NUMER][TPRAWA];														//	            BR1=ARMIA(ARM,NUMER,TPRAWA)
				v.BR2=ARMIA[ARM][NUMER][TLEWA];															//	            BR2=ARMIA(ARM,NUMER,TLEWA)
				v.PLACE=BRON[v.BR][B_PLACE];																//	            PLACE=BRON(BR,B_PLACE)
				if( v.BR1==0 ) {																						//	            If BR1=0
					if( v.PLACE==4 ||(v.PLACE==6 && v.BR2==0) ) {							//	               If PLACE=4 or(PLACE=6 and BR2=0)
						PasteBob(89,60,v.BB+GOBY);															//	                  Paste Bob 89,60,BB+GOBY
						ARMIA[ARM][NUMER][TPRAWA]=v.BR;													//	                  ARMIA(ARM,NUMER,TPRAWA)=BR
						v.KONIEC=-1;																						//	                  KONIEC=True
						PRZELICZ(4,1);																					//	                  PRZELICZ[4,1]
					}																													//	               End If
				}																														//	            End If
				_store_ekran1_wybor();
			}																															//	         End If
																																		//
		}																																//	      End If
	} while( v.KONIEC==0 );																						//	   Until KONIEC
	_restore_ekran1();
	WAGA(ARM,NUMER);																									//	   WAGA[ARM,NUMER]
	_WYBOR_WYPISZ(v);																									//	   Gosub WYPISZ
	v.KONIEC=0;																												//	   KONIEC=False
	_store_ekran1_wybor();
																																		//	   Show On
	return;																														//	   Return
}
void	_WYBOR_RYSUJ(WyborVars &v) {
	_restore_ekran1();
	if( v.WT==0 ) {																										//	   If WT=0
		SEKTOR(ARMIA[ARM][NUMER][TX],ARMIA[ARM][NUMER][TY]); v.SEK=Param;//	      SEKTOR[ARMIA(ARM,NUMER,TX),ARMIA(ARM,NUMER,TY)] : SEK=Param
	} else {																													//	   Else
		v.SEK=0;																												//	      SEK=0
	}																																	//	   End If

	GADGET(47,8,20,20,v.GLOB_S,5,5,15,15,13);													//	   GADGET[47,8,20,20,GLOB$,5,5,15,15,13]
	gad_light(1.0); _Box(47,8,67,28);																	//	   Ink 5 : Box 47,8 To 67,28

	v.B=ARMIA[ARM][NUMER][TGLOWA];																		//	   B=ARMIA(ARM,NUMER,TGLOWA)
	if( v.B>0 ) PasteBob(49,10,BRON[v.B][B_BOB]+BROBY+GOBY);					//	   If B>0 : Paste Bob 49,10,BRON(B,B_BOB)+BROBY+GOBY : End If
																																		//
	GADGET(47,44,20,20,"",5,5,0,16,14);																//	   GADGET[47,44,20,20,"",5,5,0,16,14]
	v.B=ARMIA[ARM][NUMER][TKORP];																			//	   B=ARMIA(ARM,NUMER,TKORP)
	if( v.B>0 ) PasteBob(49,46,BRON[v.B][B_BOB]+BROBY+GOBY);					//	   If B>0 : Paste Bob 49,46,BRON(B,B_BOB)+BROBY+GOBY : End If
																																		//
	GADGET(47,108,20,20,"",5,5,0,16,15);															//	   GADGET[47,108,20,20,"",5,5,0,16,15]
	v.B=ARMIA[ARM][NUMER][TNOGI];																			//	   B=ARMIA(ARM,NUMER,TNOGI)
	if( v.B>0 ) PasteBob(49,110,BRON[v.B][B_BOB]+BROBY+GOBY);					//	   If B>0 : Paste Bob 49,110,BRON(B,B_BOB)+BROBY+GOBY : End If
																																		//
	GADGET(7,58,20,20,"",5,5,0,16,16);																//	   GADGET[7,58,20,20,"",5,5,0,16,16]
	v.B=ARMIA[ARM][NUMER][TLEWA];																			//	   B=ARMIA(ARM,NUMER,TLEWA)
	if( v.B>0 ) PasteBob(9,60,BRON[v.B][B_BOB]+BROBY+GOBY);						//	   If B>0 : Paste Bob 9,60,BRON(B,B_BOB)+BROBY+GOBY : End If
																																		//
	GADGET(87,58,20,20,"",5,5,0,16,17);																//	   GADGET[87,58,20,20,"",5,5,0,16,17]
	v.B=ARMIA[ARM][NUMER][TPRAWA];																		//	   B=ARMIA(ARM,NUMER,TPRAWA)
	if( v.B>0 ) PasteBob(89,60,BRON[v.B][B_BOB]+BROBY+GOBY);					//	   If B>0 : Paste Bob 89,60,BRON(B,B_BOB)+BROBY+GOBY : End If
																																		//
	for( v.I=0; v.I<=3; ++v.I ) {																			//	   For I=0 To 3
		GADGET(5+v.X+(v.I*25),v.Y+5,20,20,"",0,5,0,16,1+v.I);						//	      GADGET[5+X+(I*25),Y+5,20,20,"",0,5,0,16,1+I]
		GADGET(5+v.X+(v.I*25),v.Y+30,20,20,"",0,5,0,16,5+v.I);					//	      GADGET[5+X+(I*25),Y+30,20,20,"",0,5,0,16,5+I]
		GADGET(5+v.X2+(v.I*25),v.Y2+5,20,20,"",0,5,0,16,9+v.I);					//	      GADGET[5+X2+(I*25),Y2+5,20,20,"",0,5,0,16,9+I]
																																		//
		v.B1=ARMIA[ARM][NUMER][TPLECAK+v.I];														//	      B1=ARMIA(ARM,NUMER,TPLECAK+I)
																																		//	      '      Print B1,BRON(B1,B_BOB)
		if( v.B1>0 ) {																									//	      If B1>0
			v.BB1=BRON[v.B1][B_BOB]+BROBY;																//	         BB1=BRON(B1,B_BOB)+BROBY
			PasteBob(v.X+7+(v.I*25),v.Y+7,v.BB1+GOBY);										//	         Paste Bob X+7+(I*25),Y+7,BB1+GOBY
		}																																//	      End If
		v.B2=ARMIA[ARM][NUMER][TPLECAK+v.I+4];													//	      B2=ARMIA(ARM,NUMER,TPLECAK+I+4)
		if( v.B2>0 ) {																									//	      If B2>0
			v.BB2=BRON[v.B2][B_BOB]+BROBY;																//	         BB2=BRON(B2,B_BOB)+BROBY
			PasteBob(v.X+7+(v.I*25),v.Y+32,v.BB2+GOBY);										//	         Paste Bob X+7+(I*25),Y+32,BB2+GOBY
		};																															//	      End If
		v.B3=GLEBA[v.SEK][v.I];																					//	      B3=GLEBA(SEK,I)
		if( v.B3>0 ) {																									//	      If B3>0
			v.BB3=BRON[v.B3][B_BOB]+BROBY;																//	         BB3=BRON(B3,B_BOB)+BROBY
			PasteBob(v.X2+7+(v.I*25),v.Y2+7,v.BB3+GOBY);									//	         Paste Bob X2+7+(I*25),Y2+7,BB3+GOBY
		}																																//	      End If
	}																																	//	   Next I
	_store_ekran1_wybor();
	return;																														//	   Return
}

void (*_rysuj_wybor_scenery)(void);
void _rysuj_wybor(void) {
	aint s = Screen();

	//ekran mruga na niektorych kartach graficznych, wiec czyscimy to co nie bedzie rysowane
	Gfx::Color(0.f,0.f,0.f);
	Screen(1);
	_ClearRaster(0,ScreenY()-5,640,525);

	if( _rysuj_wybor_scenery ) {
	  Screen(0);
    _rysuj_wybor_scenery();
	}
	Screen(1);
	_restore_ekran1();
	Screen(s);
}
void WYBOR(aint WT) {
	_rysuj_wybor_scenery = rysuj_ekran_ptr; //--zapamietujemy co bylo rysowane na ekranie

	WyborVars v;
	v.WT=WT;

																																		//	   Screen Hide : View
	ScreenDisplay(0,130,40,320,123);
	ScreenDisplay(1,130,162,320,140);																	//	   Screen Display 1,130,162,320,140

	Screen(1);																												//	   Screen 1
	Gfx::Color(0.f,0.f,0.f); _ClearRaster();

	for( v.I=0; v.I<=3; ++v.I ) {																			//	   For I=0 To 3
		PasteBob(0,v.I*50,GOBY+1);																			//	      Paste Bob 0,I*50,GOBY+1
	}																																	//	   Next I
																																		//	'   If Rnd(99)=1
																																		//	'      Reset Zone
																																		//	'      Screen Show : View : ZAB
																																		//	'      For I=0 To 3 : Paste Bob 0,I*50,GOBY+1 : Next I
																																		//	'   End If
																																		//	   Set Rainbow 1,15,512,"","","(8,1,1)"
																																		//	   Rainbow 1,1,165,160
																																		//	   Colour 0,$210
	v.X=120;																													//	   X=120
	v.Y=5;																														//	   Y=5
	v.X2=120;																													//	   X2=120
	v.Y2=100;																													//	   Y2=100
	if( v.WT==0 ) MSY=MSY+113;																				//	   If WT=0 : MSY=MSY+113 : End If
	v.XB=ARMIA[ARM][NUMER][TX]; v.YB=ARMIA[ARM][NUMER][TY];						//	   XB=ARMIA(ARM,NUMER,TX) : YB=ARMIA(ARM,NUMER,TY)
	GADGET(v.X,v.Y,105,55,"",5,0,8,8,-1);															//	   GADGET[X,Y,105,55,"",5,0,8,8,-1]
	GADGET(v.X2,v.Y2,105,30,"",5,0,8,8,-1);														//	   GADGET[X2,Y2,105,30,"",5,0,8,8,-1]
																																		//
	GADGET(v.X+5,70,95,20,"",0,5,19,19,-1);														//	   GADGET[X+5,70,95,20,"",0,5,19,19,-1]
	GADGET(235,v.Y,75,100,"",0,5,19,19,-1);														//	   GADGET[235,Y,75,100,"",0,5,19,19,-1]
	GADGET(235,v.Y2+15,30,15,"   <",5,0,8,1,21);											//	   GADGET[235,Y2+15,30,15,"   <",5,0,8,1,21]
	GADGET(280,v.Y2+15,30,15,"    >",5,0,8,1,22);											//	   GADGET[280,Y2+15,30,15,"    >",5,0,8,1,22]
	//strefy doswiadczenia;																						//	   '--------------strefy doôwiadczenia
	for( v.I=0; v.I<=4; ++v.I ) {																			//	   For I=0 To 4
		SetZone(25+v.I,237,28+v.I*10,277,37+v.I*10);										//	      Set Zone 25+I,237,28+I*10 To 277,37+I*10
	}																																	//	   Next I
	GADGET(5,5,105,125,"",0,5,15,15,-1);															//	   GADGET[5,5,105,125,"",0,5,15,15,-1]

	float rb[] = {   0.0, 0.0, 0.0, 0.0, 1.0,
							   100.0, 0.0, 0.0, 1.0, 1.0 };
	_Rainbow(6,6,109,129,rb,2);

	PasteBob(19,10,GOBY+38);																					//	   Paste Bob 19,10,GOBY+38
	GetSprite(GOBY+42,47,8,47+20,8+20);																//	   Get Sprite GOBY+42,47,8 To 47+15,28 : Wait Vbl
/*
	if( v.WT==1 ) {																										//	   If WT=1
		v.GLOB_S="bob86";																								//	      GLOB$="bob86"
	}else{																														//	   Else
		v.GLOB_S="bob42";																								//	      GLOB$="bob42"
	}																																	//	   End If
*/
  v.GLOB_S = "bob" + toString(GOBY+42);
	SetZone(20,235,5,310,18);																					//	   Set Zone 20,235,5 To 310,18

	_store_ekran1_wybor();
	_WYBOR_RYSUJ(v);																									//	   Gosub RYSUJ
	WAGA(ARM,NUMER);																									//	   WAGA[ARM,NUMER]
	_WYBOR_WYPISZ(v);																									//	   Gosub WYPISZ
																																		//	   Screen Show : View
	Screen(1);
	_store_ekran1_wybor();
	rysuj_ekran_ptr = _rysuj_wybor;

	do {																															//	   Do
		rysuj();
		if( v.BR_INFO > 0 ) {
			_WYBOR_SHOW_INFO(v.BR_INFO);
		}
		WaitVbl();
		if( MouseClick()==1 ) {																					//	      If Mouse Click=1
			v.STREFA=MouseZone();																					//	         STREFA=Mouse Zone
			if( v.STREFA>0 && v.STREFA<5 ) {															//	         If STREFA>0 and STREFA<5
				v.BR=ARMIA[ARM][NUMER][TPLECAK+v.STREFA-1];									//	            BR=ARMIA(ARM,NUMER,TPLECAK+STREFA-1)
				if( v.BR>0 ) {																							//	            If BR>0
					_restore_ekran1();
					GADGET(5+v.X+((v.STREFA-1)*25),v.Y+5,20,20,"",0,5,0,16,0);//	               GADGET[5+X+((STREFA-1)*25),Y+5,20,20,"",0,5,0,16,0]
					ARMIA[ARM][NUMER][TPLECAK+v.STREFA-1]=0;									//	               ARMIA(ARM,NUMER,TPLECAK+STREFA-1)=0
					_WYBOR_PICK(v);																						//	               Gosub PICK
				}																														//	            End If
			}																															//	         End If
			if( v.STREFA>4 && v.STREFA<9 ) {															//	         If STREFA>4 and STREFA<9
				v.BR=ARMIA[ARM][NUMER][TPLECAK+v.STREFA-1];									//	            BR=ARMIA(ARM,NUMER,TPLECAK+STREFA-1)
				if( v.BR>0 ) {																							//	            If BR>0
					_restore_ekran1();
					GADGET(5+v.X+((v.STREFA-5)*25),v.Y+30,20,20,"",0,5,0,16,0);//	               GADGET[5+X+((STREFA-5)*25),Y+30,20,20,"",0,5,0,16,0]
					ARMIA[ARM][NUMER][TPLECAK+v.STREFA-1]=0;									//	               ARMIA(ARM,NUMER,TPLECAK+STREFA-1)=0
					_WYBOR_PICK(v);																						//	               Gosub PICK
				}																														//	            End If
			}																															//	         End If
			if( v.STREFA>8 && v.STREFA<13 ) {															//	         If STREFA>8 and STREFA<13
				v.BR=GLEBA[v.SEK][v.STREFA-9];															//	            BR=GLEBA(SEK,STREFA-9)
				if( v.BR>0 ) {																							//	            If BR>0
					_restore_ekran1();
					GADGET(5+v.X2+((v.STREFA-9)*25),v.Y2+5,20,20,"",0,5,0,16,0);//	               GADGET[5+X2+((STREFA-9)*25),Y2+5,20,20,"",0,5,0,16,0]
					GLEBA[v.SEK][v.STREFA-9]=0;																//	               GLEBA(SEK,STREFA-9)=0
					_WYBOR_PICK(v);																						//	               Gosub PICK
				}																														//	            End If
			}																															//	         End If
			if( v.STREFA==13 ) {																					//	         If STREFA=13
				v.BR=ARMIA[ARM][NUMER][TGLOWA];															//	            BR=ARMIA(ARM,NUMER,TGLOWA)
				if( v.BR>0 ) {																							//	            If BR>0
					_restore_ekran1();
					GADGET(47,8,20,20,v.GLOB_S,5,5,15,15,0);									//	               GADGET[47,8,20,20,GLOB$,5,5,15,15,0]
					gad_light(1.0); _Box(47,8,67,28);											//	               Ink 5 : Box 47,8 To 67,28
					PRZELICZ(v.STREFA-13,-1);																	//	               PRZELICZ[STREFA-13,-1]
					_WYBOR_WYPISZ(v);																					//	               Gosub WYPISZ
					ARMIA[ARM][NUMER][TGLOWA+v.STREFA-13]=0;									//	               ARMIA(ARM,NUMER,TGLOWA+STREFA-13)=0
					_WYBOR_PICK(v);																						//	               Gosub PICK
				}																														//	            End If
			}																															//	         End If
			if( v.STREFA==14 ) {																					//	         If STREFA=14
				v.BR=ARMIA[ARM][NUMER][TGLOWA+v.STREFA-13];									//	            BR=ARMIA(ARM,NUMER,TGLOWA+STREFA-13)
				if( v.BR>0 ) {																							//	            If BR>0
					_restore_ekran1();
					GADGET(47,44,20,20,"",5,5,0,16,0);												//	               GADGET[47,44,20,20,"",5,5,0,16,0]
					PRZELICZ(v.STREFA-13,-1);																	//	               PRZELICZ[STREFA-13,-1]
					_WYBOR_WYPISZ(v);																					//	               Gosub WYPISZ
					ARMIA[ARM][NUMER][TGLOWA+v.STREFA-13]=0;									//	               ARMIA(ARM,NUMER,TGLOWA+STREFA-13)=0
					_WYBOR_PICK(v);																						//	               Gosub PICK
				}																														//	            End If
			}																															//	         End If
			if( v.STREFA==15 ) {																					//	         If STREFA=15
				v.BR=ARMIA[ARM][NUMER][TGLOWA+v.STREFA-13];									//	            BR=ARMIA(ARM,NUMER,TGLOWA+STREFA-13)
				if( v.BR>0 ) {																							//	            If BR>0
					_restore_ekran1();
					GADGET(47,8+((v.STREFA-13)*50),20,20,"",5,5,0,16,0);			//	               GADGET[47,8+((STREFA-13)*50),20,20,"",5,5,0,16,0]
					PRZELICZ(v.STREFA-13,-1);																	//	               PRZELICZ[STREFA-13,-1]
					_WYBOR_WYPISZ(v);																					//	               Gosub WYPISZ
					ARMIA[ARM][NUMER][TGLOWA+v.STREFA-13]=0;									//	               ARMIA(ARM,NUMER,TGLOWA+STREFA-13)=0
					_WYBOR_PICK(v);																						//	               Gosub PICK
				}																														//	            End If
			}																															//	         End If
			if( v.STREFA==16 ) {																					//	         If STREFA=16
				v.BR=ARMIA[ARM][NUMER][TLEWA];															//	            BR=ARMIA(ARM,NUMER,TLEWA)
				if( v.BR>0 ) {																							//	            If BR>0
					_restore_ekran1();
					GADGET(7,58,20,20,"",5,5,0,16,16);												//	               GADGET[7,58,20,20,"",5,5,0,16,16]
					PRZELICZ(3,-1);																						//	               PRZELICZ[3,-1]
					_WYBOR_WYPISZ(v);																					//	               Gosub WYPISZ
					ARMIA[ARM][NUMER][TLEWA]=0;																//	               ARMIA(ARM,NUMER,TLEWA)=0
					_WYBOR_PICK(v);																						//	               Gosub PICK
				}																														//	            End If
			}																															//	         End If
			if( v.STREFA==17 ) {																					//	         If STREFA=17
				v.BR=ARMIA[ARM][NUMER][TPRAWA];															//	            BR=ARMIA(ARM,NUMER,TPRAWA)
				if( v.BR>0 ) {																							//	            If BR>0
					_restore_ekran1();
					GADGET(87,58,20,20,"",5,5,0,16,17);												//	               GADGET[87,58,20,20,"",5,5,0,16,17]
					PRZELICZ(4,-1);																						//	               PRZELICZ[4,-1]
					_WYBOR_WYPISZ(v);																					//	               Gosub WYPISZ
					ARMIA[ARM][NUMER][TPRAWA]=0;															//	               ARMIA(ARM,NUMER,TPRAWA)=0
					_WYBOR_PICK(v);																						//	               Gosub PICK
				}																														//	            End If
			}																															//	         End If
			if( v.STREFA==20 ) {																					//	         If STREFA=20
				//WPISZ(237,15,3,19,11,0);																			//	            WPISZ[237,15,3,19,11]
				SET_BACKGROUND(119.0f/255.f,102.0f/255.f,85.0f/255.f,1.f);
				SET_FOREGROUND(210.0f/255.f,204.0f/255.f,203.0f/255.f,1.f);
				WPISZ_PC(237,15-TextBase(),70,10,11,ARMIA_S[ARM][NUMER],3);
				_store_ekran1_wybor();
				ARMIA_S[ARM][NUMER]=WPI_S;																	//	            ARMIA$(ARM,NUMER)=WPI$
			}																															//	         End If
			if( v.STREFA==25 && ARMIA[ARM][NUMER][TDOSW]>=1 && ARMIA[ARM][NUMER][TEM]<((20+RASY[v.RASA][0])*3)+20 ) {//	         If STREFA=25 and ARMIA(ARM,NUMER,TDOSW)>=1 and ARMIA(ARM,NUMER,TEM)<((20+RASY(RASA,0))*3)+20
				ARMIA[ARM][NUMER][TEM]++;																		//	            Inc ARMIA(ARM,NUMER,TEM)
				ARMIA[ARM][NUMER][TDOSW]--;																	//	            Dec ARMIA(ARM,NUMER,TDOSW)
				_restore_ekran1();
				gad_back(1.0);
				_Bar(270,28,306,35);
				_Bar(295,88,306,95);
				gad_text(1.0);					//	            Ink 19 : Bar 295,88 To 306,95 : Ink 16,19
				Text(270,35,Minus_S(Str_S(ARMIA[ARM][NUMER][TE])+"/"+Str_S(ARMIA[ARM][NUMER][TEM])," ")+" ");//	            Text 270,35,Str$(ARMIA(ARM,NUMER,TE))+"/"+Str$(ARMIA(ARM,NUMER,TEM))-" "+" "
				Text(295,95,Str_S(ARMIA[ARM][NUMER][TDOSW]));								//	            Text 295,95,Str$(ARMIA(ARM,NUMER,TDOSW))
				_store_ekran1_wybor();
			}																															//	         End If
			if( v.STREFA==26 && ARMIA[ARM][NUMER][TDOSW]>=3 && ARMIA[ARM][NUMER][TSI]<(RASY[v.RASA][1]/2)+40 ) {//	         If STREFA=26 and ARMIA(ARM,NUMER,TDOSW)>=3 and ARMIA(ARM,NUMER,TSI)<(RASY(RASA,1)/2)+40
				ARMIA[ARM][NUMER][TSI]++;																		//	            Inc ARMIA(ARM,NUMER,TSI)
				ARMIA[ARM][NUMER][TDOSW]-=3;																//	            Add ARMIA(ARM,NUMER,TDOSW),-3
				_restore_ekran1();
				gad_back(1.0);
				_Bar(290,38,306,45);
				_Bar(295,88,306,95);
				gad_text(1.0);					//	            Ink 19 : Bar 295,88 To 306,95 : Ink 16,19
				Text(290,45,Str_S(ARMIA[ARM][NUMER][TSI])+" ");							//	            Text 290,45,Str$(ARMIA(ARM,NUMER,TSI))+" "
				Text(295,95,Str_S(ARMIA[ARM][NUMER][TDOSW]));								//	            Text 295,95,Str$(ARMIA(ARM,NUMER,TDOSW))
				_store_ekran1_wybor();
			}																															//	         End If
			if( v.STREFA==27 && ARMIA[ARM][NUMER][TDOSW]>=4 && ARMIA[ARM][NUMER][TSZ]<RASY[v.RASA][2]+30 ) {//	         If STREFA=27 and ARMIA(ARM,NUMER,TDOSW)>=4 and ARMIA(ARM,NUMER,TSZ)<RASY(RASA,2)+30
				ARMIA[ARM][NUMER][TSZ]++;																		//	            Inc ARMIA(ARM,NUMER,TSZ)
				ARMIA[ARM][NUMER][TDOSW]-=3;																//	            Add ARMIA(ARM,NUMER,TDOSW),-3
				_restore_ekran1();
				gad_back(1.0);
				_Bar(290,48,306,55);
				_Bar(295,88,306,95);
				gad_text(1.0);					//	            Ink 19 : Bar 295,88 To 306,95 : Ink 16,19
				Text(290,55,Str_S(ARMIA[ARM][NUMER][TSZ])+" ");							//	            Text 290,55,Str$(ARMIA(ARM,NUMER,TSZ))+" "
				Text(295,95,Str_S(ARMIA[ARM][NUMER][TDOSW]));								//	            Text 295,95,Str$(ARMIA(ARM,NUMER,TDOSW))
				_store_ekran1_wybor();
			}																															//	         End If
			if( v.STREFA==28 && ARMIA[ARM][NUMER][TDOSW]>=3 ) {						//	         If STREFA=28 and ARMIA(ARM,NUMER,TDOSW)>=3
				ARMIA[ARM][NUMER][TP]++;																		//	            Inc ARMIA(ARM,NUMER,TP)
				ARMIA[ARM][NUMER][TDOSW]-=3;																//	            Add ARMIA(ARM,NUMER,TDOSW),-3
				_restore_ekran1();
				gad_back(1.0);
				_Bar(290,58,306,65);
				_Bar(295,88,306,95);
				gad_text(1.0);					//	            Ink 19 : Bar 295,88 To 306,95 : Ink 16,19
				Text(290,65,Str_S(ARMIA[ARM][NUMER][TP])+" ");							//	            Text 290,65,Str$(ARMIA(ARM,NUMER,TP))+" "
				Text(295,95,Str_S(ARMIA[ARM][NUMER][TDOSW]));								//	            Text 295,95,Str$(ARMIA(ARM,NUMER,TDOSW))
				_store_ekran1_wybor();
			}																															//	         End If
			if( v.STREFA==29 && ARMIA[ARM][NUMER][TDOSW]>=2 && ARMIA[ARM][NUMER][TMAGMA]<RASY[v.RASA][3]+30 ) {//	         If STREFA=29 and ARMIA(ARM,NUMER,TDOSW)>=2 and ARMIA(ARM,NUMER,TMAGMA)<RASY(RASA,3)+30
				ARMIA[ARM][NUMER][TMAGMA]++;																//	            Inc ARMIA(ARM,NUMER,TMAGMA)
				ARMIA[ARM][NUMER][TDOSW]-=2;																//	            Add ARMIA(ARM,NUMER,TDOSW),-2
				_restore_ekran1();
				gad_back(1.0);
				_Bar(270,68,306,75);
				_Bar(295,88,306,95);
				gad_text(1.0);					//	            Ink 19 : Bar 295,88 To 306,95 : Ink 16,19
				Text(270,75,Minus_S(Str_S(ARMIA[ARM][NUMER][TMAG])+"/"+Str_S(ARMIA[ARM][NUMER][TMAGMA])," ")+" ");//	            Text 270,75,Str$(ARMIA(ARM,NUMER,TMAG))+"/"+Str$(ARMIA(ARM,NUMER,TMAGMA))-" "+" "
				Text(295,95,Str_S(ARMIA[ARM][NUMER][TDOSW]));								//	            Text 295,95,Str$(ARMIA(ARM,NUMER,TDOSW))
				_store_ekran1_wybor();
			}																															//	         End If
																																		//
		}	else {																															//	      End If
			//### ulepszenie - prezentujemy info o przedmiocie po najechaniu go mycha
			v.BR_INFO = 0;
			v.STREFA=MouseZone();
			if( v.STREFA>=1 && v.STREFA<=8 ) {
				v.BR_INFO = ARMIA[ARM][NUMER][TPLECAK+v.STREFA-1];
			}
			if( v.STREFA>=9 && v.STREFA<=12 ) {
				v.BR_INFO=GLEBA[v.SEK][v.STREFA-9];
			}
			if( v.STREFA>=13 && v.STREFA<=15 ) {
				v.BR_INFO=ARMIA[ARM][NUMER][TGLOWA+v.STREFA-13];
			}
			if( v.STREFA==16 ) {
				v.BR_INFO=ARMIA[ARM][NUMER][TLEWA];
			}
			if( v.STREFA==17 ) {
				v.BR_INFO=ARMIA[ARM][NUMER][TPRAWA];
			}
		}
		if( MouseKey()==LEWY ) {																				//	      If Mouse Key=LEWY
			v.STREFA=MouseZone();																					//	         STREFA=Mouse Zone
			if( v.STREFA==21 ) {																					//	         If STREFA=21
				_restore_ekran1();
				GADGET(235,v.Y2+15,30,15,"   <",0,5,11,2,0);								//	            GADGET[235,Y2+15,30,15,"   <",0,5,11,2,0]
				GADGET(235,v.Y2+15,30,15,"   <",5,0,8,1,-1);								//	            GADGET[235,Y2+15,30,15,"   <",5,0,8,1,-1]
				AG1:																												//	            AG1:
				Add(NUMER,-1,1,10);																					//	            Add NUMER,-1,1 To 10
				if( ARMIA[ARM][NUMER][TE]<=0 ) goto AG1;										//	            If ARMIA(ARM,NUMER,TE)<=0 : Goto AG1 : End If
				if( v.WT==0 ) {																							//	            If WT=0
					Screen(0);																								//	               Screen 0
					v.XB=ARMIA[ARM][NUMER][TX]; v.YB=ARMIA[ARM][NUMER][TY];		//	               XB=ARMIA(ARM,NUMER,TX) : YB=ARMIA(ARM,NUMER,TY)
					CENTER(v.XB,v.YB,2);																			//	               CENTER[XB,YB,2]
					_Bob(50,v.XB,v.YB,1+BUBY); BobUpdate();										//	               Bob 50,XB,YB,1+BUBY : Bob Update
					Screen(1);																								//	               Screen 1
				}																														//	            End If
				v.RASA=ARMIA[ARM][NUMER][TRASA];														//	            RASA=ARMIA(ARM,NUMER,TRASA)
				WAGA(ARM,NUMER); WaitVbl(); _WYBOR_RYSUJ(v); _WYBOR_WYPISZ(v);//	            WAGA[ARM,NUMER] : Wait Vbl : Gosub RYSUJ : Gosub WYPISZ
				_store_ekran1_wybor();
			}																															//	         End If
			if( v.STREFA==22 ) {																					//	         If STREFA=22
				_restore_ekran1();
				GADGET(280,v.Y2+15,30,15,"    >",0,5,11,2,0);								//	            GADGET[280,Y2+15,30,15,"    >",0,5,11,2,0]
				GADGET(280,v.Y2+15,30,15,"    >",5,0,8,1,-1);								//	            GADGET[280,Y2+15,30,15,"    >",5,0,8,1,-1]
				AG2:																												//	            AG2:
				Add(NUMER,1,1,10);																					//	            Add NUMER,1,1 To 10
				if( ARMIA[ARM][NUMER][TE]<=0 ) goto AG2;										//	            If ARMIA(ARM,NUMER,TE)<=0 : Goto AG2 : End If
				if( v.WT==0 ) {																							//	            If WT=0
					Screen(0);																								//	               Screen 0
					v.XB=ARMIA[ARM][NUMER][TX]; v.YB=ARMIA[ARM][NUMER][TY];		//	               XB=ARMIA(ARM,NUMER,TX) : YB=ARMIA(ARM,NUMER,TY)
					CENTER(v.XB,v.YB,2);																			//	               CENTER[XB,YB,2]
					_Bob(50,v.XB,v.YB,1+BUBY); BobUpdate();										//	               Bob 50,XB,YB,1+BUBY : Bob Update
					Screen(1);																								//	               Screen 1
				}																														//	            End If
				v.RASA=ARMIA[ARM][NUMER][TRASA];														//	            RASA=ARMIA(ARM,NUMER,TRASA)
				WAGA(ARM,NUMER); WaitVbl(); _WYBOR_RYSUJ(v); _WYBOR_WYPISZ(v);//	            WAGA[ARM,NUMER] : Wait Vbl : Gosub RYSUJ : Gosub WYPISZ
				_store_ekran1_wybor();
			}																															//	         End If
		}																																//	      End If
		if( MouseKey()==PRAWY ) break;																	//	      Exit If Mouse Key=PRAWY
																																		//
	} while(true);																										//	   Loop
	//goto OVER;																											//	   Goto OVER

	//OVER:																															//	   OVER:
																																		//	   Rainbow Del 1
	rysuj_ekran_ptr = _rysuj_wybor_scenery;
	if( WT==0 ) {																											//	   If WT=0
    ScreenDisplay(0,130,40,320,234);

		MSY=278;																												//	      MSY=278
		Screen(0); CENTER(v.XB,v.YB,0); Screen(1);											//	      Screen 0 : CENTER[XB,YB,0] : Screen 1
		ScreenDisplay(1,130,275,320,25);																//	      Screen Display 1,130,275,320,25 : View
																																		//	      Colour 0,$0
		EKRAN1();																												//	      EKRAN1
		SELECT(ARM,NUMER);																							//	      SELECT[ARM,NUMER]
	} else {
	  ScreenDisplay(0,130,40,320,255);
	}																																	//	   End If

																																		//	End Proc
}
void ROZKAZ(void) {
																				//	Procedure ROZKAZ
	aint KONIEC=0, HY=0, KLAW=0, MYSZ=0, STREFA=0, I=0, X1=0, Y1=0,
			 STARAODL=0, WIDAC=0, J=0, X2=0, Y2=0, TARGET=0, CX=0, CY=0,
			 X=0, Y=0, ODL=0;
	astr A_S="";

	KONIEC=0;															//	   KONIEC=False
	Screen(1);														//	   Screen 1
	_restore_ekran1();
	PasteBob(0,0,1);											//	   Paste Bob 0,0,1
	ResetZone(-1);												//	   Reset Zone
	GADGET(8,4,70,15,GS("016"),26,24,25,30,1);//	   GADGET[8,4,70,15,"Guard",26,24,25,30,1]
	GADGET(82,4,70,15,GS("017"),26,24,25,30,2);//	   GADGET[82,4,70,15,"Attack",26,24,25,30,2]
	GADGET(156,4,70,15,GS("018"),26,24,25,30,3);//	   GADGET[156,4,70,15,"Retreat",26,24,25,30,3]
	GADGET(230,4,70,15,GS("019"),26,24,25,30,4);//	   GADGET[230,4,70,15,"END",26,24,25,30,4]
	_store_ekran1();

	while( MouseKey()==LEWY ) ProcessEvents();	//	   While Mouse Key=LEWY : Wend
	do {																	//	   Repeat
		rysuj(); WaitVbl();

		HY=YMouse();												//	      HY=Y Mouse
		if( HY>275 ) {											//	      If HY>275
			A_S=Inkey_S();										//	         A$=Inkey$
			KLAW=ScanCode();									//	         KLAW=Scancode
			if( KLAW>75 && KLAW<80 ) {				//	         If KLAW>75 and KLAW<80
				KLAWSKROL(KLAW);								//	            KLAWSKROL[KLAW]
			}																	//	         End If
			MYSZ=MouseKey();									//	         MYSZ=Mouse Key
			if( MYSZ==LEWY ) {								//	         If MYSZ=LEWY
				STREFA=MouseZone();							//	            STREFA=Mouse Zone
				if( STREFA==1 ) {								//	            If STREFA=1
					_restore_ekran1();
					GADGET(8,4,70,15,GS("016"),23,26,24,30,0);//	               GADGET[8,4,70,15,"Guard",23,26,24,30,0]
					GADGET(8,4,70,15,GS("016"),26,24,25,30,0);//	               GADGET[8,4,70,15,"Guard",26,24,25,30,0]
					_store_ekran1();
					KONIEC=-1;										//	               KONIEC=True
					for(I=1;I<=10;++I) {					//	               For I=1 To 10
						ARMIA[ARM][I][TTRYB]=0;			//	                  ARMIA(ARM,I,TTRYB)=0
					}															//	               Next
				}																//	            End If
				if( STREFA==2 ) {								//	            If STREFA=2
					KONIEC=-1;										//	               KONIEC=True
					_restore_ekran1();
					GADGET(82,4,70,15,GS("017"),23,26,24,30,0);//	               GADGET[82,4,70,15,"Attack",23,26,24,30,0]
					GADGET(82,4,70,15,GS("017"),26,24,25,30,0);//	               GADGET[82,4,70,15,"Attack",26,24,25,30,0]
					_store_ekran1();
					for(I=1;I<=10;++I) {					//	               For I=1 To 10
						if( ARMIA[ARM][I][TE]>0 ) {	//	                  If ARMIA(ARM,I,TE)>0
							X1=ARMIA[ARM][I][TX];			//	                     X1=ARMIA(ARM,I,TX)
							Y1=ARMIA[ARM][I][TY];			//	                     Y1=ARMIA(ARM,I,TY)
							STARAODL=WIDOCZNOSC;			//	                     STARAODL=WIDOCZNOSC
							WIDAC=0;									//	                     WIDAC=False
							for(J=1;J<=10;++J) {			//	                     For J=1 To 10
								if( ARMIA[WRG][J][TE]>0 ) {//	                        If ARMIA(WRG,J,TE)>0
									X2=ARMIA[WRG][J][TX];	//	                           X2=ARMIA(WRG,J,TX)
									Y2=ARMIA[WRG][J][TY];	//	                           Y2=ARMIA(WRG,J,TY)
									::ODL(X1,Y1,X2,Y2);		//	                           ODL[X1,Y1,X2,Y2]
																				//
									if( ODLEG<STARAODL ) {//	                           If ODLEG<STARAODL
										TARGET=J;						//	                              TARGET=J
										CX=X2; CY=Y2;				//	                              CX=X2 : CY=Y2
										STARAODL=ODLEG;			//	                              STARAODL=ODLEG
										WIDAC=-1;						//	                              WIDAC=True
									}											//	                           End If
								}												//	                        End If
							}													//	                     Next J
							if( WIDAC!=0 ) {					//	                     If WIDAC
								ARMIA[ARM][I][TTRYB]=2;	//	                        ARMIA(ARM,I,TTRYB)=2
								ARMIA[ARM][I][TCELX]=TARGET;//	                        ARMIA(ARM,I,TCELX)=TARGET
								ARMIA[ARM][I][TCELY]=WRG;//	                        ARMIA(ARM,I,TCELY)=WRG
							}													//	                     End If
						}														//	                  End If
					}															//	               Next
				}																//	            End If
																				//
				if( STREFA==4 ) {								//	            If STREFA=4
					KONIEC=-1;										//	               KONIEC=True
					KONIEC_AKCJI=-1;							//	               KONIEC_AKCJI=True
					WYNIK_AKCJI=0;								//	               WYNIK_AKCJI=0
					for(I=1;I<=10;++I) {					//	               For I=1 To 10
						if( ARMIA[ARM][I][TE]>0 ) {	//	                  If ARMIA(ARM,I,TE)>0
							X=ARMIA[ARM][I][TX];			//	                     X=ARMIA(ARM,I,TX)
							Y=ARMIA[ARM][I][TY];			//	                     Y=ARMIA(ARM,I,TY)
							if( X>22 && X<610 && Y>30 && Y<500 ) {//	                     If X>22 and X<610 and Y>30 and Y<500
								KONIEC=0;								//	                        KONIEC=False
								KONIEC_AKCJI=0;					//	                        KONIEC_AKCJI=False
							}													//	                     End If
						}														//	                  End If
					}															//	               Next I
					if( KONIEC==0 ) {							//	               If KONIEC=False
						WYNIK_AKCJI=1;							//	                  WYNIK_AKCJI=1
						KONIEC=-1; KONIEC_AKCJI=-1;	//	                  KONIEC=True : KONIEC_AKCJI=True
						for(I=1;I<=10;++I) {				//	                  For I=1 To 10
							if( ARMIA[WRG][I][TE]>0 && ARMIA[WRG][I][TKORP]>90 ) {//	                     If ARMIA(WRG,I,TE)>0 and ARMIA(WRG,I,TKORP)>90
								KONIEC=0;								//	                        KONIEC=False
								KONIEC_AKCJI=0; 				//	                        KONIEC_AKCJI=False : WYNIK_AKCJI=0
								WYNIK_AKCJI=0;
							}													//	                     End If
						}														//	                  Next
					}															//	               End If
					if( KONIEC_AKCJI!=0 ) {				//	               If KONIEC_AKCJI
						_restore_ekran1();
						GADGET(230,4,70,15,GS("019"),23,26,24,30,0);//	                  GADGET[230,4,70,15,"END",23,26,24,30,0]
						GADGET(230,4,70,15,GS("019"),26,24,25,30,0);//	                  GADGET[230,4,70,15,"END",26,24,25,30,0]
						_store_ekran1();
					}															//	               End If
				}																//	            End If
				if( STREFA==3 ) {								//	            If STREFA=3
					_restore_ekran1();
					GADGET(156,4,70,15,GS("018"),23,26,24,30,0);//	               GADGET[156,4,70,15,"Retreat",23,26,24,30,0]
					GADGET(156,4,70,15,GS("018"),26,24,25,30,0);//	               GADGET[156,4,70,15,"Retreat",26,24,25,30,0]
					_store_ekran1();
																				//
					for(I=1;I<=10;++I) {					//	               For I=1 To 10
						if( ARMIA[ARM][I][TE]>0 ) {	//	                  If ARMIA(ARM,I,TE)>0
							X=ARMIA[ARM][I][TX];			//	                     X=ARMIA(ARM,I,TX)
							Y=ARMIA[ARM][I][TY];			//	                     Y=ARMIA(ARM,I,TY)
							ODL=400;									//	                     ODL=400
							if( X<ODL ) {							//	                     If X<ODL : ODL=X : CY=Y : CX=17 : End If
								ODL=X; CY=Y; CX=17;
							}
							if( Y<ODL ) {							//	                     If Y<ODL : ODL=Y : CY=22 : CX=X : End If
								ODL=Y; CY=22; CX=X;
							}
							if( 640-X<ODL ) {					//	                     If 640-X<ODL : ODL=640-X : CY=Y : CX=623 : End If
								ODL=640-X;
								CY=Y;
								CX=623;
							}
							if( 512-Y<ODL ) {					//	                     If 512-Y<ODL : ODL=512-Y : CY=512 : CX=X : End If
								ODL=512-Y;
								//!!! BUG ? chyba 512-22
								CY=512;
								CX=X;
							}
							ARMIA[ARM][I][TTRYB]=1;		//	                     ARMIA(ARM,I,TTRYB)=1
							ARMIA[ARM][I][TCELX]=CX;	//	                     ARMIA(ARM,I,TCELX)=CX
							ARMIA[ARM][I][TCELY]=CY;	//	                     ARMIA(ARM,I,TCELY)=CY
						}														//	                  End If
					}															//	               Next I
					KONIEC=-1;										//	               KONIEC=True
				}																//	            End If
			}																	//	         End If
			if( MYSZ==PRAWY ) {								//	         If MYSZ=PRAWY
				KONIEC=-1;											//	            KONIEC=True
			}																	//	         End If
		} else {														//	      Else
			HY=YMouse();											//	         HY=Y Mouse
			A_S=Inkey_S();										//	         A$=Inkey$
			KLAW=ScanCode();									//	         KLAW=Scancode
			if( KLAW>75 && KLAW<80 ) {				//	         If KLAW>75 and KLAW<80
				KLAWSKROL(KLAW);								//	            KLAWSKROL[KLAW]
			}																	//	         End If
			if( MouseKey()==PRAWY ) {					//	         If Mouse Key=PRAWY : SKROL[0] : End If
				SKROL(0);
			}
		}																		//	      End If
	} while( KONIEC==0 );									//	   Until KONIEC
	while( MouseClick()!=0 ) {
		ProcessEvents();
	}
	ResetZone(-1);												//	   Reset Zone
	EKRAN1();															//	   EKRAN1
	SELECT(ARM,NUMER);										//	   SELECT[ARM,NUMER]
																				//	End Proc
}
void SELECT(aint A,aint NR) {
																			//	Procedure SELECT[A,NR]
	aint TRYB=0, JEST=0, I=0, GADE=0, X=0, Y=0, X2=0, Y2=0,
			 TARGET=0, B=0, Y22=0;

	Screen(1);													//	   Screen 1
	TRYB=ARMIA[A][NR][TTRYB];						//	   TRYB=ARMIA(A,NR,TTRYB)
	NUMER=NR;														//	   NUMER=NR
	if( ARMIA[A][NR][TE]<=0 ) {					//	   If ARMIA(A,NR,TE)<=0
		JEST=0;														//	      JEST=False
		for(I=1;I<=10;++I) {							//	      For I=1 To 10
			//!!! BUG ? powinno byc A zamiast ARM
			if( ARMIA[ARM][I][TE]>0 ) {			//	         If ARMIA(ARM,I,TE)>0 : NUMER=I : NR=I : I=10 : JEST=True : End If
				NUMER=I;
				NR=I;
				I=10;
				JEST=-1;
			}
		}																	//	      Next
	} else {														//	   Else
		JEST=-1;													//	      JEST=True
	}																		//	   End If
	if( JEST==0 ) {											//	   If Not JEST : KONIEC_AKCJI=True : Goto OVER : End If
		KONIEC_AKCJI=-1;
		goto OVER;
	}
	GADE=TRYB;													//	   GADE=TRYB
	if( TRYB==4 || TRYB==5 ) {					//	   If TRYB=4 or TRYB=5
		GADE=3;														//	      GADE=3
	}																		//	   End If
	if( TRYB==6 ) {											//	   If TRYB=6
		GADE=4;														//	      GADE=4
	}																		//	   End If
																			//	   'CHECK[LAST_GAD]
	GADUP(LAST_GAD);										//	   GADUP[LAST_GAD]
	GADDOWN(GADE);											//	   GADDOWN[GADE]
	LAST_GAD=GADE;											//	   LAST_GAD=GADE
	X=ARMIA[A][NR][TX];									//	   X=ARMIA(A,NR,TX)
	Y=ARMIA[A][NR][TY];									//	   Y=ARMIA(A,NR,TY)
	if( TRYB==1 || TRYB==3 || TRYB==4 ) {//	   If TRYB=1 or TRYB=3 or TRYB=4
		X2=ARMIA[ARM][NUMER][TCELX];			//	      X2=ARMIA(ARM,NUMER,TCELX)
		Y2=ARMIA[ARM][NUMER][TCELY];			//	      Y2=ARMIA(ARM,NUMER,TCELY)
	}																		//	   End If
	if( TRYB==2 || TRYB==5 || TRYB==6 ) {//	   If TRYB=2 or TRYB=5 or TRYB=6
		TARGET=ARMIA[ARM][NUMER][TCELX];	//	      TARGET=ARMIA(ARM,NUMER,TCELX)
		B=ARMIA[ARM][NUMER][TCELY];				//	      B=ARMIA(ARM,NUMER,TCELY)
		X2=ARMIA[B][TARGET][TX];					//	      X2=ARMIA(B,TARGET,TX)
		Y2=ARMIA[B][TARGET][TY];					//	      Y2=ARMIA(B,TARGET,TY)
	}																		//	   End If
	if( TRYB==3 || TRYB==4 ) {					//	   If TRYB=3 or TRYB=4
		Y22=12;														//	      Y22=12
	} else {														//	   Else
		Y22=0;														//	      Y22=0
	}																		//	   End If
	Screen(0);													//	   Screen 0
	_Bob(50,X,Y,1+BUBY);								//	   Bob 50,X,Y,1+BUBY
	if( TRYB!=0 ) {											//	   If TRYB<>0
		_Bob(51,X2,Y2+Y22,2+BUBY);				//	      Bob 51,X2,Y2+Y22,2+BUBY
	} else {														//	   Else
		BobOnOff(51,false);								//	      Bob Off 51 : Bob Update : Wait Vbl
	}																		//	   End If
	BobUpdate(); WaitVbl();							//	   Bob Update : Wait Vbl
	Screen(1); WYKRESY(A,NR);						//	   Screen 1 : WYKRESY[A,NR]
	OVER:																//	   OVER:
		;																	//	End Proc
}
void PRZELICZ(aint I,aint ZNAK) {
																					//	Procedure PRZELICZ[I,ZNAK]
	aint B=0, TYP=0, TYP2=0, RASA=0, SI=0, PAN=0, SZ=0, EN=0, MAG=0,
			 MAGIA=0, MAGMA=0, MXSI=0, MXSZ=0;
	B=ARMIA[ARM][NUMER][TGLOWA+I];					//	   B=ARMIA(ARM,NUMER,TGLOWA+I)
	TYP=BRON[B][B_TYP];											//	   TYP=BRON(B,B_TYP)
	TYP2=RASY[ARMIA[ARM][NUMER][TRASA]][4];	//	   TYP2=RASY(ARMIA(ARM,NUMER,TRASA),4)
	if( TYP!=4 && TYP!=5 && TYP!=12 && TYP!=15 && TYP!=16 ) {//	   If TYP<>4 and TYP<>5 and TYP<>12 and TYP<>15 and TYP<>16
		RASA=ARMIA[ARM][NUMER][TRASA];				//	      RASA=ARMIA(ARM,NUMER,TRASA)
		SI=BRON[B][B_SI];											//	      SI=BRON(B,B_SI)
		PAN=BRON[B][B_PAN];										//	      PAN=BRON(B,B_PAN)
		SZ=BRON[B][B_SZ];											//	      SZ=BRON(B,B_SZ)
		EN=BRON[B][B_EN];											//	      EN=BRON(B,B_EN)
		if( TYP==13 || TYP==18 ) {						//	      If TYP=13 or TYP=18
			MAG=BRON[B][B_MAG];									//	         MAG=BRON(B,B_MAG)
			MAGIA=ARMIA[ARM][NUMER][TMAG];			//	         MAGIA=ARMIA(ARM,NUMER,TMAG)
			MAGMA=ARMIA[ARM][NUMER][TMAGMA];		//	         MAGMA=ARMIA(ARM,NUMER,TMAGMA)
			MAGIA+=MAG;													//	         Add MAGIA,MAG
			if( MAGIA>MAGMA ) {									//	         If MAGIA>ARMIA(ARM,NUMER,TMAGMA)
				MAGIA=MAGMA;											//	            MAGIA=MAGMA
			}																		//	         End If
			ARMIA[ARM][NUMER][TMAG]=MAGIA;			//	         ARMIA(ARM,NUMER,TMAG)=MAGIA
			MXSI=(RASY[RASA][1]/2)+30;					//	         MXSI=(RASY(RASA,1)/2)+30
			MXSZ=RASY[RASA][2]+20;							//	         MXSZ=RASY(RASA,2)+20
			if( ARMIA[ARM][NUMER][TSI]+SI>MXSI ) {//	         If ARMIA(ARM,NUMER,TSI)+SI>MXSI : SI=MXSI-ARMIA(ARM,NUMER,TSI) : End If
				SI=MXSI-ARMIA[ARM][NUMER][TSI];
			}
			if( ARMIA[ARM][NUMER][TSZ]+SZ>MXSZ ) {//	         If ARMIA(ARM,NUMER,TSZ)+SZ>MXSZ : SZ=MXSZ-ARMIA(ARM,NUMER,TSZ) : End If
				SZ=MXSZ-ARMIA[ARM][NUMER][TSZ];
			}
		}																			//	      End If
		ARMIA[ARM][NUMER][TSI]+=SI*ZNAK;			//	      Add ARMIA(ARM,NUMER,TSI),SI*ZNAK
		ARMIA[ARM][NUMER][TP]+=PAN*ZNAK;			//	      Add ARMIA(ARM,NUMER,TP),PAN*ZNAK
		ARMIA[ARM][NUMER][TSZ]+=SZ*ZNAK;			//	      Add ARMIA(ARM,NUMER,TSZ),SZ*ZNAK
		ARMIA[ARM][NUMER][TAMO]+=SZ*ZNAK;			//	      Add ARMIA(ARM,NUMER,TAMO),SZ*ZNAK
		ARMIA[ARM][NUMER][TE]+=EN*ZNAK;				//	      Add ARMIA(ARM,NUMER,TE),EN*ZNAK
		if( TYP==TYP2 ) {											//	      If TYP=TYP2
			ARMIA[ARM][NUMER][TSI]+=4*ZNAK;			//	         Add ARMIA(ARM,NUMER,TSI),4*ZNAK
		}																			//	      End If
		clipu(ARMIA[ARM][NUMER][TSI],100);		//	      If ARMIA(ARM,NUMER,TSI)>100 : ARMIA(ARM,NUMER,TSI)=100 : End If
		clip(ARMIA[ARM][NUMER][TE],1,ARMIA[ARM][NUMER][TEM]);//	      If ARMIA(ARM,NUMER,TE)>ARMIA(ARM,NUMER,TEM) : ARMIA(ARM,NUMER,TE)=ARMIA(ARM,NUMER,TEM) : End If
																					//	      If ARMIA(ARM,NUMER,TE)<1 : ARMIA(ARM,NUMER,TE)=1 : End If
	}																				//	   End If
																					//	End Proc
}
void WAGA(aint A,aint NR) {
	//	Procedure WAGA[A,NR]

	aint I=0,WAGA=0,B=0,DW=0;
	WAGA=0;														//	   WAGA=0
	for(I=0;I<=12;++I) {							//	   For I=0 To 12
		B=ARMIA[A][NR][TGLOWA+I];				//	      B=ARMIA(A,NR,TGLOWA+I)
		if( B>0 ) {											//	      If B>0
			WAGA += BRON[B][B_WAGA];			//	         Add WAGA,BRON(B,B_WAGA)
		}																//	      End If
	}																	//	   Next I
	ARMIA[A][NR][TWAGA]=WAGA;					//	   ARMIA(A,NR,TWAGA)=WAGA
	DW=ARMIA[A][NR][TEM]-WAGA;				//	   DW=ARMIA(A,NR,TEM)-WAGA
	if( DW<0 ) {											//	   If DW<0
		ARMIA[A][NR][TSZ]=ARMIA[A][NR][TAMO]-20;	//	      ARMIA(A,NR,TSZ)=ARMIA(A,NR,TAMO)-20
		if( ARMIA[A][NR][TSZ]<=0 ) {		//	      If ARMIA(A,NR,TSZ)<=0 : ARMIA(A,NR,TSZ)=1 : End If
			ARMIA[A][NR][TSZ]=1;
		}
	}	else {													//	   Else
		ARMIA[A][NR][TSZ]=ARMIA[A][NR][TAMO];	//	      ARMIA(A,NR,TSZ)=ARMIA(A,NR,TAMO)
	}																	//	   End If
}																		//	End Proc
void SEKTOR(aint X,aint Y) {
											//	Procedure SEKTOR[X,Y]
	aint XSEK=0, YSEK=0, SEK=0;
	XSEK=X/64;					//	   XSEK=(X/64)
	YSEK=Y/50;					//	   YSEK=(Y/50)
	SEK=XSEK+(YSEK*10);	//	   SEK=XSEK+(YSEK*10)
	Param=SEK;					//	End Proc[SEK]
}

void GADUP(aint GN) {
																		//	Procedure GADUP[GN]
	aint SC=0;
	SC=Screen();											//	   SC=Screen
	Screen(1);												//	   Screen 1
_restore_ekran1();
	if( GN==1 || GN==-1 ) {						//	   If GN=1 or GN=-1
		GADGET(200,2,20,20,"bob3",2,0,19,5,-1);//	      GADGET[200,2,20,20,"bob3",2,0,19,5,-1]
	}																	//	   End If
	if( GN==2 || GN==-1 ) {						//	   If GN=2 or GN=-1
		GADGET(222,2,20,20,"bob4",2,0,19,5,-1);//	      GADGET[222,2,20,20,"bob4",2,0,19,5,-1]
	}																	//	   End If
	if( GN==3 || GN==-1 ) {						//	   If GN=3 or GN=-1
		GADGET(244,2,20,20,"bob5",2,0,19,5,-1);//	      GADGET[244,2,20,20,"bob5",2,0,19,5,-1]
	}																	//	   End If
	if( GN==4 || GN==-1 ) {						//	   If GN=4 or GN=-1
		GADGET(266,2,20,20,"bob6",2,0,19,5,-1);//	      GADGET[266,2,20,20,"bob6",2,0,19,5,-1]
	}																	//	   End If
	if( GN==10 || GN==-1 ) {					//	   If GN=10 or GN=-1
		GADGET(297,2,20,20,"bob7",2,0,19,5,-1);//	      GADGET[297,2,20,20,"bob7",2,0,19,5,-1]
	}																	//	   End If
_store_ekran1();
	Screen(SC);												//	   Screen SC
																		//	End Proc
}
void GADDOWN(aint GN) {
																		//	Procedure GADDOWN[GN]
	aint SC=0;
	SC=Screen();											//	   SC=Screen
	Screen(1);												//	   Screen 1
_restore_ekran1();
		//	   If GN=1
		//	      GADGET[200,2,20,20,"bob10",0,2,16,4,0]
		//	   End If
		//	   If GN=2
		//	      GADGET[222,2,20,20,"bob11",0,2,16,4,0]
		//	   End If
		//	   If GN=3
		//	      GADGET[244,2,20,20,"bob12",0,2,16,4,0]
		//	   End If
		//	   If GN=4
		//	      GADGET[266,2,20,20,"bob13",0,2,16,4,0]
		//	   End If
		//	   If GN=10
		//	      GADGET[297,2,20,20,"bob14",0,2,16,4,0]
		//	   End If
	switch( GN ) {
		case 1:		GADGET(200,2,20,20,"bob10",0,2,16,4,0); break;
		case 2:		GADGET(222,2,20,20,"bob11",0,2,16,4,0); break;
		case 3:		GADGET(244,2,20,20,"bob12",0,2,16,4,0); break;
		case 4:		GADGET(266,2,20,20,"bob13",0,2,16,4,0); break;
		case 10:	GADGET(297,2,20,20,"bob14",0,2,16,4,0); break;
		default:	break;
	}
_store_ekran1();
	Screen(SC);												//	   Screen SC
																		//	End Proc
}
void MARKERS(void) {
																			//	Procedure MARKERS
	aint I=0, X=0, Y=0;
	for(I=1;I<=10;++I) {								//	   For I=1 To 10
		if( ARMIA[ARM][I][TE]>0 ) {				//	      If ARMIA(ARM,I,TE)>0
			X=ARMIA[ARM][I][TX];						//	         X=ARMIA(ARM,I,TX)
			Y=ARMIA[ARM][I][TY]-45;					//	         Y=ARMIA(ARM,I,TY)-45
			_Bob(20+I,X,Y,PIKIETY+18+10);		//	         Bob 20+I,X,Y,PIKIETY+18+10
		}																	//	      End If
	}																		//	   Next I
	BobUpdate();												//	   Bob Update : Wait Vbl
	WaitVbl();
																			//	End Proc
}
void MARKERS_OFF(void) {
														//	Procedure MARKERS_OFF
	aint I=0;
	for(I=1;I<=10;++I) {			//	   For I=1 To 10
		BobOnOff(20+I,false);		//	      Bob Off 20+I
	}													//	   Next I
	BobUpdate(); WaitVbl();		//	   Bob Update : Wait Vbl
														//	End Proc
}
void RUCH(void) {
															//	Procedure RUCH
	aint STREFA=0;

	_GET_XY(0,0,0);							//	   _GET_XY[0,0,0]
	Screen(0);									//	   Screen 0
	BobOnOff(30+NUMER,false);		//	   Bob Off 30+NUMER
	OY+=8;											//	   Add OY,8
	if( OX>623 ) OX=623;				//	   If OX>623 Then OX=623
	if( OX<17 ) OX=17;					//	   If OX<17 Then OX=17
	if( OY>508 ) OY=508;				//	   If OY>508 Then OY=508
	if( OY<22 ) OY=22;					//	   If OY<22 Then OY=22
	STREFA=_Zone(OX,OY);				//	   STREFA=Zone(OX,OY)
	if( STREFA<21
		|| (STREFA>100 && STREFA<120)
		|| (STREFA>30 && STREFA<41) ) {//	   If STREFA<21 or STREFA>100 and STREFA<120 or STREFA>30 and STREFA<41
		ARMIA[ARM][NUMER][TCELX]=OX;//	      ARMIA(ARM,NUMER,TCELX)=OX
		ARMIA[ARM][NUMER][TCELY]=OY;//	      ARMIA(ARM,NUMER,TCELY)=OY
		ARMIA[ARM][NUMER][TTRYB]=1;	//	      ARMIA(ARM,NUMER,TTRYB)=1
		_Bob(51,OX,OY,2+BUBY);		//	      Bob 51,OX,OY,2+BUBY : Bob Update : Wait Vbl
		BobUpdate(); WaitVbl();
	}														//	   End If
	while( MouseKey()==LEWY ) {	//	   While Mouse Key=LEWY : Wend
		ProcessEvents();
	}
															//	End Proc
}

void A_RUCH(aint A,aint I) {
																				//	Procedure A_RUCH[A,I]
	aint I2=0, X1=0, Y1=0, X2=0, Y2=0, BAZA=0, KLATKA=0,
			 SPEED=0, SPEED2=0, BNR=0, ROZX=0, ROZY=0, STREFA=0,
			 STREFA2=0, RASA=0, KLIN=0, MIASTO=0, ZNX=0, ZNY=0, T=0,
			 B2=0, ST=0;


	Screen(0);														//	   Screen 0
	if( A==WRG ) {												//	   If A=WRG
		I2=I+10;														//	      I2=I+10
	} else {															//	   Else
		I2=I;																//	      I2=I
	}																			//	   End If
	X1=ARMIA[A][I][TX];										//	   X1=ARMIA(A,I,TX)
	Y1=ARMIA[A][I][TY];										//	   Y1=ARMIA(A,I,TY)
	X2=ARMIA[A][I][TCELX];								//	   X2=ARMIA(A,I,TCELX)
	Y2=ARMIA[A][I][TCELY];								//	   Y2=ARMIA(A,I,TCELY)
	BAZA=ARMIA[A][I][TBOB];								//	   BAZA=ARMIA(A,I,TBOB)
	KLATKA=ARMIA[A][I][TKLAT];						//	   KLATKA=ARMIA(A,I,TKLAT)
	SPEED=ARMIA[A][I][TSZ]/10;						//	   SPEED=ARMIA(A,I,TSZ)/10
	SPEED2=3-SPEED;												//	   SPEED2=3-SPEED
	if( SPEED2<=0 ) SPEED2=1;							//	   If SPEED2<=0 Then SPEED2=1
	if( SPEED<=0 ) SPEED=1;								//	   If SPEED<=0 Then SPEED=1
	if( SPEED>7 ) SPEED=7;								//	   If SPEED>7 Then SPEED=7
	Add(KLATKA,1,0,SPEED2*4-1);						//	   Add KLATKA,1,0 To(SPEED2*4)-1
	ARMIA[A][I][TKLAT]=KLATKA;						//	   ARMIA(A,I,TKLAT)=KLATKA
	KLATKA/=SPEED2;												//	   KLATKA=KLATKA/SPEED2
	KLATKA=AN[KLATKA];										//	   KLATKA=AN(KLATKA)
	BNR=BAZA+7;														//	   BNR=BAZA+7
	ROZX=X2-X1;														//	   ROZX=X2-X1
	ROZY=Y2-Y1;														//	   ROZY=Y2-Y1
	STREFA=_Zone(X1,Y1+1);								//	   STREFA=Zone(X1,Y1+1)
	STREFA2=_Zone(X1,Y1+30);							//	   STREFA2=Zone(X1,Y1+30)
	RASA=ARMIA[A][I][TRASA];							//	   RASA=ARMIA(A,I,TRASA)
	KLIN=2;																//	   KLIN=2
	if( RASA>9 && Rnd(40)==1 ) {					//	   If RASA>9 and Rnd(40)=1
		SamBank(5);													//	      Sam Bank 5
		FX(1);															//	      FX[1]
		SamBank(4);													//	      Sam Bank 4
	}																			//	   End If
	if( STREFA2>20 && STREFA2<31) {				//	   If STREFA2>20 and STREFA2<31
		LimitBob(I2,0,0,640,114);						//	      Limit Bob I2,0,0 To 640,114
	} else {															//	   Else
		LimitBob(I2,0,0,640,512);						//	      Limit Bob I2,0,0 To 640,512
	}																			//	   End If
	if( STREFA>100 && STREFA<120 && A==ARM ) {//	   If STREFA>100 and STREFA<120 and A=ARM
		MIASTO=ARMIA[A][0][TNOGI]-70;				//	      MIASTO=ARMIA(A,0,TNOGI)-70
		_SKLEP(MIASTO,STREFA-100,A,I);				//	      SKLEP[MIASTO,STREFA-100,A,I]
		Y1+=8;															//	      Add Y1,8
		goto SKIP;													//	      Goto SKIP
	}																			//	   End If
	if( STREFA>30 && STREFA<41 ) {				//	   If STREFA>30 and STREFA<41
		PLAPKA(STREFA-30,A,I,X1,Y1);				//	      PLAPKA[STREFA-30,A,I,X1,Y1]
		if( Param==1 ) {										//	      If Param=1
			goto OVER;												//	         Goto OVER
		}																		//	      End If
	}																			//	   End If
	if( Abs(ROZX)>4 ) {										//	   If Abs(ROZX)>4
		ZNX=Sgn(ROZX);											//	      ZNX=Sgn(ROZX)
		if( ZNX==-1 ) {											//	      If ZNX=-1 : BNR=BAZA+4+KLATKA : T=-17 : End If
			BNR=BAZA+4+KLATKA;
			T=-17;
		}
		if( ZNX==1 ) {											//	      If ZNX=1 : BNR=BAZA+10+KLATKA : T=17 : End If
			BNR=BAZA+10+KLATKA;
			T=17;
		}
		ST=_Zone(X1+T,Y1);									//	      ST=Zone(X1+T,Y1)
		if( ST==0 || (((ST>100 && ST<120) || (ST>30 && ST<41)) && ARM==A) ) {//	      If ST=0 or(ST>100 and ST<120 or ST>30 and ST<41) and A=ARM
			X1+=ZNX*SPEED;										//	         Add X1,ZNX*SPEED
			KLIN--;														//	         Dec KLIN
		}																		//	      End If
	}																			//	   End If
	if( Abs(ROZY)>4 ) {										//	   If Abs(ROZY)>4
		ZNY=Sgn(ROZY);											//	      ZNY=Sgn(ROZY)
		if( ZNY==-1 ) {											//	      If ZNY=-1 : B2=BAZA+1+KLATKA : T=-21 : End If
			B2=BAZA+1+KLATKA;
			T=-21;
		}
		if( ZNY==1 ) {											//	      If ZNY=1 : B2=BAZA+7+KLATKA : T=2 : End If
			B2=BAZA+7+KLATKA;
			//!@# blad - raczej T=21
			T=2;
		}
		ST=_Zone(X1,Y1+T);									//	      ST=Zone(X1,Y1+T)
		if( ST==0 || (((ST>100 && ST<120) || (ST>30 && ST<41)) && ARM==A) ) {//	      If ST=0 or(ST>100 and ST<120 or ST>30 and ST<41) and A=ARM
			Y1+=ZNY*SPEED;										//	         Add Y1,ZNY*SPEED
			BNR=B2;														//	         BNR=B2
			KLIN--;														//	         Dec KLIN
		}																		//	      End If
	}																			//	   End If
																				//
	if( Abs(ROZX)<=4 && Abs(ROZY)<=4 ) {	//	   If Abs(ROZX)<=4 and Abs(ROZY)<=4
		ARMIA[A][I][TTRYB]=0;								//	      ARMIA(A,I,TTRYB)=0
		KLIN=0;															//	      KLIN=0
	}																			//	   End If
																				//
SKIP:																		//	   SKIP:
	ARMIA[A][I][TX]=X1;										//	   ARMIA(A,I,TX)=X1
	ARMIA[A][I][TY]=Y1;										//	   ARMIA(A,I,TY)=Y1
																				//
	SetZone(I2,X1-15,Y1-15,X1+15,Y1);			//	   Set Zone I2,X1-15,Y1-15 To X1+15,Y1
	_Bob(I2,X1,Y1,BNR);										//	   Bob I2,X1,Y1,BNR
	if( KLIN==2 && A==WRG ) {							//	   If KLIN=2 and A=WRG
		X2=X1+Rnd(120)-60;									//	      X2=X1+Rnd(120)-60
		Y2=Y1+Rnd(100)-50;									//	      Y2=Y1+Rnd(100)-50
																				//	      If X2<20 : X2=20 : End If
																				//	      If X2>620 : X2=620 : End If
		clip(X2,20,620);
																				//	      If Y2<20 : Y2=20 : End If
																				//	      If Y2>510 : Y2=510 : End If
		clip(Y2,20,510);
		ARMIA[A][I][TCELX]=X2;							//	      ARMIA(A,I,TCELX)=X2
		ARMIA[A][I][TCELY]=Y2;							//	      ARMIA(A,I,TCELY)=Y2
		ARMIA[A][I][TTRYB]=1;								//	      ARMIA(A,I,TTRYB)=1
	}																			//	   End If
																				//
	OVER:																	//	   OVER:
		;
																				//	End Proc
}
void A_ATAK(aint A,aint I) {
																					//	Procedure A_ATAK[A,I]
	aint I2=0, X1=0, Y1=0, X2=0, Y2=0, BAZA=0, BNR=0, TARGET=0, B=0, ENP=0,
			 SPEED=0, KLATKA=0, SPEED2=0, STREFA=0, STREFA2=0, RASA=0, KLIN=0,
			 ROZX=0, ROZY=0, ZNX=0, T=0, ST=0, ZNY=0, B2=0, ODP=0,
			 SILA=0, MOC=0, MOC2=0, RASA2=0, OPOR=0, CIOS=0, PRZELOT=0,
			 CELX=0, CELY=0, MUDRY=0, SAM=0;

	if( A==WRG ) {													//	   If A=WRG
		I2=I+10;															//	      I2=I+10
	} else {																//	   Else
		I2=I;																	//	      I2=I
	}																				//	   End If
	X1=ARMIA[A][I][TX];											//	   X1=ARMIA(A,I,TX)
	Y1=ARMIA[A][I][TY];											//	   Y1=ARMIA(A,I,TY)
	BAZA=ARMIA[A][I][TBOB];									//	   BAZA=ARMIA(A,I,TBOB)
	BNR=BAZA+7;															//	   BNR=BAZA+7
	TARGET=ARMIA[A][I][TCELX];							//	   TARGET=ARMIA(A,I,TCELX)
	B=ARMIA[A][I][TCELY];										//	   B=ARMIA(A,I,TCELY)
	ENP=ARMIA[B][TARGET][TE];								//	   ENP=ARMIA(B,TARGET,TE)
	if( ENP<=0 ) {													//	   If ENP<=0
		ARMIA[A][I][TTRYB]=0;									//	      ARMIA(A,I,TTRYB)=0
		goto OVER;														//	      Goto OVER
	}																				//	   End If
	X2=ARMIA[B][TARGET][TX];								//	   X2=ARMIA(B,TARGET,TX)
	Y2=ARMIA[B][TARGET][TY];								//	   Y2=ARMIA(B,TARGET,TY)
	SPEED=ARMIA[A][I][TSZ]/10;							//	   SPEED=ARMIA(A,I,TSZ)/10
	KLATKA=ARMIA[A][I][TKLAT];							//	   KLATKA=ARMIA(A,I,TKLAT)
	SPEED2=3-SPEED;													//	   SPEED2=3-SPEED
	if(SPEED2<=0) SPEED2=1;									//	   If SPEED2<=0 Then SPEED2=1
	if(SPEED<=0) SPEED=1;										//	   If SPEED<=0 Then SPEED=1
	if(SPEED>7) SPEED=7;										//	   If SPEED>7 Then SPEED=7
	Add(KLATKA,1,0,SPEED2*4-1);							//	   Add KLATKA,1,0 To(SPEED2*4)-1
	ARMIA[A][I][TKLAT]=KLATKA;							//	   ARMIA(A,I,TKLAT)=KLATKA
	KLATKA/=SPEED2;													//	   KLATKA=KLATKA/SPEED2
	KLATKA=AN[KLATKA];											//	   KLATKA=AN(KLATKA)
	STREFA=_Zone(X1,Y1+1);									//	   STREFA=Zone(X1,Y1+1)
	STREFA2=_Zone(X1,Y1+30);								//	   STREFA2=Zone(X1,Y1+30)
	RASA=ARMIA[A][I][TRASA];								//	   RASA=ARMIA(A,I,TRASA)
	KLIN=2;																	//	   KLIN=2
	if( RASA>9 && Rnd(40)==1 ) {						//	   If RASA>9 and Rnd(40)=1
		SamBank(5);														//	      Sam Bank 5
		FX(1);																//	      FX[1]
		SamBank(4);														//	      Sam Bank 4
	}																				//	   End If
	if( STREFA>30 && STREFA<41 ) {					//	   If STREFA>30 and STREFA<41
		PLAPKA(STREFA-30,A,I,X1,Y1);					//	      PLAPKA[STREFA-30,A,I,X1,Y1]
		if( Param==1 ) {											//	      If Param=1
			goto OVER;													//	         Goto OVER
		}																			//	      End If
	}																				//	   End If
	if( STREFA2>20 && STREFA2<31 ) {				//	   If STREFA2>20 and STREFA2<31
		LimitBob(I2,0,0,640,114);							//	      Limit Bob I2,0,0 To 640,114
	} else {																//	   Else
		LimitBob(I2,0,0,640,512);							//	      Limit Bob I2,0,0 To 640,512
	}																				//	   End If
																					//
	ROZX=X2-X1;															//	   ROZX=X2-X1
	ROZY=Y2-Y1;															//	   ROZY=Y2-Y1
																					//
	if( Abs(ROZX)>33 ) {													//	   If Abs(ROZX)>33
		ZNX=Sgn(ROZX);															//	      ZNX=Sgn(ROZX)
		if( ZNX==-1 ) { BNR=BAZA+4+KLATKA; T=-17; }	//	      If ZNX=-1 : BNR=BAZA+4+KLATKA : T=-17 : End If
		if( ZNX==1 ) { BNR=BAZA+10+KLATKA; T=17; }	//	      If ZNX=1 : BNR=BAZA+10+KLATKA : T=17 : End If
		ST=_Zone(X1+T,Y1);													//	      ST=Zone(X1+T,Y1)
		if( ST==0 || (ST>30 && ST<41 && A==ARM) ) {	//	      If ST=0 or ST>30 and ST<41 and A=ARM
			X1+=ZNX*SPEED;														//	         Add X1,ZNX*SPEED
			KLIN--;																		//	         Dec KLIN
		}																						//	      End If
	}																							//	   End If
	if(	Abs(ROZY)>21 ) {													//	   If Abs(ROZY)>21
		ZNY=Sgn(ROZY);															//	      ZNY=Sgn(ROZY)
		if( ZNY==-1 ) { BNR=BAZA+1+KLATKA; T=-21; }	//	      If ZNY=-1 : BNR=BAZA+1+KLATKA : T=-21 : End If
		//!@# BLAD - chyba powinno byc T=21
		if( ZNY==1 ) { BNR=BAZA+7+KLATKA; T=2; }		//	      If ZNY=1 : BNR=BAZA+7+KLATKA : T=2 : End If
		ST=_Zone(X1,Y1+T);													//	      ST=Zone(X1,Y1+T)
		if( ST==0 || (ST>30 && ST<41 && A==ARM) ) {	//	      If ST=0 or ST>30 and ST<41 and A=ARM
			Y1+=ZNY*SPEED;														//	         Add Y1,ZNY*SPEED
			KLIN--;																		//	         Dec KLIN
		}																						//	      End If
	}																							//	   End If
																					//
	if( Abs(ROZX)<=33 && Abs(ROZY)<=21 ) {	//	   If Abs(ROZX)<=33 and Abs(ROZY)<=21
		KLIN=0;																//	      KLIN=0
		ZNX=Sgn(ROZX);												//	      ZNX=Sgn(ROZX)
		B2=BAZA+13+Rnd(2);										//	      B2=BAZA+13+Rnd(2)
		if( ZNX==-1 ) {												//	      If ZNX=-1
			BNR=BAZA+5+Rnd(1);									//	         BNR=BAZA+5+Rnd(1)
		} else {															//	      Else
			BNR=BAZA+11+Rnd(1);									//	         BNR=BAZA+11+Rnd(1) : B2=Hrev(B2)
			B2=Hrev(B2);
		}																			//	      End If
																					//
		if( B==WRG ) {												//	      If B=WRG : ARMIA(WRG,TARGET,TGLOWA)=1 : End If
			ARMIA[WRG][TARGET][TGLOWA]=1;
		}
		if( A==WRG ) {												//	      If A=WRG : ARMIA(WRG,I,TGLOWA)=1 : End If
			ARMIA[WRG][I][TGLOWA]=1;
		}
																					//	      'auto-defence system
		if(	ARMIA[B][TARGET][TTRYB]==0 || ARMIA[B][TARGET][TTRYB]==1 ) {	//	      If ARMIA(B,TARGET,TTRYB)=0 or(B=WRG and ARMIA(B,TARGET,TTRYB)=1)
			ARMIA[B][TARGET][TCELX]=I;					//	         ARMIA(B,TARGET,TCELX)=I
			ARMIA[B][TARGET][TCELY]=A;					//	         ARMIA(B,TARGET,TCELY)=A
			ARMIA[B][TARGET][TTRYB]=2;					//	         ARMIA(B,TARGET,TTRYB)=2
		}																			//	      End If
																					//	      '-------------------
		ODP=ARMIA[B][TARGET][TP];							//	      ODP=ARMIA(B,TARGET,TP)
		SILA=ARMIA[A][I][TSI];								//	      SILA=ARMIA(A,I,TSI)
		MOC=100-ARMIA[A][I][TDOSW];						//	      MOC=100-ARMIA(A,I,TDOSW)
		MOC2=100-ARMIA[B][TARGET][TDOSW];			//	      MOC2=100-ARMIA(B,TARGET,TDOSW)
																					//	      'BRO1=BRON(ARMIA(A,I,TLEWA),B_WAGA)
																					//	      'BRO2=BRON(ARMIA(A,I,TPRAWA),B_WAGA)
		SPEED=(100-ARMIA[A][I][TSI])/10;			//	      SPEED=(100-ARMIA(A,I,TSZ))/10
		if( SPEED<1 ) SPEED=1;								//	      If SPEED<1 : SPEED=1 : End If
		RASA2=ARMIA[B][TARGET][TRASA];				//	      RASA2=ARMIA(B,TARGET,TRASA)
		if( Rnd(SPEED) == 0 ) {								//	      If Rnd(SPEED)=0
//	         Ink 10 : Plot X2+Rnd(20)-10,Y2+Rnd(6)-2
			BNR=B2;															//	         BNR=B2
			OPOR=ODP-Rnd(((ODP*MOC2)/100)+1);		//	         OPOR=ODP-Rnd(((ODP*MOC2)/100)+1)
			CIOS=(SILA-Rnd((SILA*MOC)/100))-OPOR;//	         CIOS=(SILA-Rnd((SILA*MOC)/100))-OPOR
			CIOS/=2;														//	         CIOS=CIOS/2
																					//	         'CHECK[CIOS]
			if( CIOS<=0 ) CIOS=1;								//	         If CIOS<=0 : CIOS=1 : End If
			ENP-=CIOS;													//	         Add ENP,-CIOS
			if( RASA2<10 ) PRZELOT=Rnd(1);			//	         If RASA2<10 : PRZELOT=Rnd(1) : End If
			if( CIOS>13 && PRZELOT==1 ) {				//	         If CIOS>13 and PRZELOT=1
				ARMIA[B][TARGET][TTRYB]=7;				//	            ARMIA(B,TARGET,TTRYB)=7
				CELX=X2+ROZX;	clip(CELX,20,620);	//	            CELX=X2+ROZX : If CELX<20 : CELX=20 : End If : If CELX>620 : CELX=620 : End If
				CELY=Y2+ROZY;	clip(CELY,20,500);	//	            CELY=Y2+ROZY : If CELY<20 : CELY=20 : End If : If CELY>500 : CELY=500 : End If
				ARMIA[B][TARGET][TCELX]=CELX;			//	            ARMIA(B,TARGET,TCELX)=CELX
				ARMIA[B][TARGET][TCELY]=CELY;			//	            ARMIA(B,TARGET,TCELY)=CELY
			}																		//	         End If
																					//
			if( ENP<=0 ) {											//	         If ENP<=0
				if( CIOS>20 && PRZELOT==1 ) {			//	            If CIOS>20 and PRZELOT=1
					ARMIA[B][TARGET][TTRYB]=8;			//	               ARMIA(B,TARGET,TTRYB)=8
					ENP=5;													//	               ENP=5
				} else {													//	            Else
					ZABIJ(B,TARGET,0);							//	               ZABIJ[B,TARGET,0]
				}																	//	            End If
				MUDRY=RASY[RASA][6];							//	            MUNDRY=RASY(RASA,6)

				//!!! BLAD
				Add(ARMIA[A][I][TDOSW],Rnd(MUDRY),ARMIA[A][I][TDOSW],95);//	            Add ARMIA(A,I,TDOSW),Rnd(MUNDRY),ARMIA(A,I,TDOSW) To 95
				//!!! powinno byc
				//ARMIA[A][I][TDOSW] += Rnd(MUDRY);
				//clipu(ARMIA[A][I][TDOSW],95);

				ARMIA[A][I][TTRYB]=0;							//	            ARMIA(A,I,TTRYB)=0
				if( A==WRG ) ARMIA[A][I][TKORP]+=Rnd(20);	//	            If A=WRG : Add ARMIA(A,I,TKORP),Rnd(20) : End If
			}																		//	         End If
			ARMIA[B][TARGET][TE]=ENP;						//	         ARMIA(B,TARGET,TE)=ENP
			KANAL=Rnd(3);												//	         KANAL=Rnd(3)
			if( RASA<10 ) {											//	         If RASA<10
				SAM=Rnd(4)+1;											//	            SAM=Rnd(4)+1
			} else {														//	         Else
				SamBank(5);												//	            Sam Bank 5
				SAM=2;														//	            SAM=2
			}																		//	         End If
			FX(SAM);														//	         FX[SAM]
			SamBank(4);													//	         Sam Bank 4
		}																			//	      End If
	}																				//	   End If
	ARMIA[A][I][TX]=X1;											//	   ARMIA(A,I,TX)=X1
	ARMIA[A][I][TY]=Y1;											//	   ARMIA(A,I,TY)=Y1
	if( ARMIA[A][I][TE]>0 ) {								//	   If ARMIA(A,I,TE)>0 : Bob I2,X1,Y1,BNR : Set Zone I2,X1-15,Y1-15 To X1+15,Y1 : End If
		_Bob(I2,X1,Y1,BNR);
		SetZone(I2,X1-15,Y1-15,X1+15,Y1);
	}
	if( KLIN>1 && A==WRG ) {								//	   If KLIN>1 and A=WRG
		X2=X1+Rnd(120)-60;										//	      X2=X1+Rnd(120)-60
		Y2=Y1+Rnd(100)-50;										//	      Y2=Y1+Rnd(100)-50
		if(	X2<20 ) X2=20;										//	      If X2<20 : X2=20 : End If
		if( X2>620 ) X2=620;									//	      If X2>620 : X2=620 : End If
		if( Y2<20 ) Y2=20;										//	      If Y2<20 : Y2=20 : End If
		if( Y2>510 ) Y2=510;									//	      If Y2>510 : Y2=510 : End If
		ARMIA[A][I][TCELX]=X2;								//	      ARMIA(A,I,TCELX)=X2
		ARMIA[A][I][TCELY]=Y2;								//	      ARMIA(A,I,TCELY)=Y2
		ARMIA[A][I][TTRYB]=1;									//	      ARMIA(A,I,TTRYB)=1
	}																				//	   End If
	OVER:																		//	   OVER:
		;																			//	End Proc
}
void A_STRZAL(aint A,aint I) {
																								//	Procedure A_STRZAL[A,I]
	aint I2=0,SILA=0,ODLOT=0,SAM=0,STREFA=0,
			 BB=0,B=0,X1=0,Y1=0,ENP=0,ODP=0,RASA2=0,
			 OSZ=0,SEK=0,MOC=0,CIOS=0,CELX=0,CELY=0,
			 MUNDRY=0,X=0;
	aflt XP_F=0, YP_F=0, VX_F=0, VY_F=0;
	if( A==WRG ) {																//	   If A=WRG
		I2=I+10;																		//	      I2=I+10
	} else {																			//	   Else
		I2=I;																				//	      I2=I
	}																							//	   End If
	SILA=(aint)VEKTOR_F[I2][0];										//	   SILA=VEKTOR#(I2,0)
	XP_F=VEKTOR_F[I2][3];													//	   XP#=VEKTOR#(I2,3)
	YP_F=VEKTOR_F[I2][4];													//	   YP#=VEKTOR#(I2,4)
	VX_F=VEKTOR_F[I2][1];													//	   VX#=VEKTOR#(I2,1)
	VY_F=VEKTOR_F[I2][2];													//	   VY#=VEKTOR#(I2,2)
	XP_F += VX_F*2;																//	   XP#=XP#+(VX#*2)
	YP_F += VY_F*2;																//	   YP#=YP#+(VY#*2)
	VEKTOR_F[I2][3]=XP_F;													//	   VEKTOR#(I2,3)=XP#
	VEKTOR_F[I2][4]=YP_F;													//	   VEKTOR#(I2,4)=YP#
	if(SILA<0) {																	//	   If SILA<0
		BB=PIKIETY+21+Rnd(3);												//	      BB=PIKIETY+21+Rnd(3)
		SILA=-SILA;																	//	      SILA=-SILA
		ODLOT=Rnd(1);																//	      ODLOT=Rnd(1)
		SAM=14;																			//	      SAM=14
	} else {																			//	   Else
		SAM=11;																			//	      SAM=11
		ODLOT=0;																		//	      ODLOT=0
		BB=BSIBY+I2;																//	      BB=BSIBY+I2
	}																							//	   End If
	Screen(0);																		//	   Screen 0
	_Bob(I2+30,(aint)XP_F,(aint)YP_F,BB);					//	   Bob I2+30,XP#,YP#,BB
	STREFA=_Zone((aint)XP_F,(aint)YP_F);					//	   STREFA=Zone(XP#,YP#)
	//trafienie w goscia													//	   'trafienie w goôcia
	if( STREFA>0 && STREFA!=I2 && STREFA<21 ) {		//	   If STREFA>0 and STREFA<>I2 and STREFA<21
		if( STREFA>10 ) {														//	      If STREFA>10
			STREFA-=10;																//	         Add STREFA,-10
			B=WRG;																		//	         B=WRG
		} else {																		//	      Else
			B=ARM;																		//	         B=ARM
		}																						//	      End If
		BobOnOff(I2+30,false);											//	      Bob Off I2+30
		ARMIA[A][I][TTRYB]=0;												//	      ARMIA(A,I,TTRYB)=0
		X1=ARMIA[B][STREFA][TX];										//	      X1=ARMIA(B,STREFA,TX)
		Y1=ARMIA[B][STREFA][TY];										//	      Y1=ARMIA(B,STREFA,TY)
		ENP=ARMIA[B][STREFA][TE];										//	      ENP=ARMIA(B,STREFA,TE)
		ODP=ARMIA[B][STREFA][TP];										//	      ODP=ARMIA(B,STREFA,TP)
		RASA2=ARMIA[B][STREFA][TRASA];							//	      RASA2=ARMIA(B,STREFA,TRASA)
		if( RASA2>9 ) ODLOT=0;											//	      If RASA2>9 : ODLOT=0 : End If
		//oszczepy laduja na glebie									//	      'oszczepy lâdujâ na glebie
		OSZ=(aint)VEKTOR_F[I2][5];												//	      OSZ=VEKTOR#(I2,5)
		if( BRON[OSZ][B_TYP]==9 ) {									//	      If BRON(OSZ,B_TYP)=9
			SEKTOR(X1,Y1); SEK=Param;									//	         SEKTOR[X1,Y1] : SEK=Param
			for(I=0;I<=3;++I) {												//	         For I=0 To 3
				if( GLEBA[SEK][I]==0 ) {								//	            If GLEBA(SEK,I)=0
					GLEBA[SEK][I]=OSZ;										//	               GLEBA(SEK,I)=OSZ
					I=4;																	//	               I=4
				}																				//	            End If
			}																					//	         Next I
		}																						//	      End If
		//-------------------												//	      '-----------
		MOC=100-ARMIA[A][I][TDOSW];									//	      MOC=100-ARMIA(A,I,TDOSW)
		CIOS=SILA-Rnd((SILA*MOC)/100)-Rnd(ODP+2);		//	      CIOS=SILA-Rnd((SILA*MOC)/100)-Rnd(ODP+2)
																								//	      'CHECK[CIOS]
		if( CIOS<=0 ) CIOS=1;												//	      If CIOS<=0 : CIOS=1 : End If
																								//
		ENP-=CIOS;																	//	      Add ENP,-CIOS
		if( ODLOT==1 ) {														//	      If ODLOT=1
			ARMIA[B][STREFA][TTRYB]=7;								//	         ARMIA(B,STREFA,TTRYB)=7
			CELX=X1+(aint)VX_F*8;	clip(CELX,20,620);	//	         CELX=X1+VX#*8 : If CELX<20 : CELX=20 : End If : If CELX>620 : CELX=620 : End If
			CELY=X1+(aint)VY_F*8; clip(CELY,20,500);	//	         CELY=Y1+VY#*8 : If CELY<20 : CELY=20 : End If : If CELY>500 : CELY=500 : End If
			ARMIA[B][STREFA][TCELX]=CELX;							//	         ARMIA(B,STREFA,TCELX)=CELX
			ARMIA[B][STREFA][TCELY]=CELY;							//	         ARMIA(B,STREFA,TCELY)=CELY
		}																						//	      End If
		if( ENP<=0 ) {															//	      If ENP<=0
			MUNDRY=RASY[ARMIA[A][I][TRASA]][6];				//	         MUNDRY=RASY(ARMIA(A,I,TRASA),6)

			//!!! BLAD
			Add(ARMIA[A][I][TDOSW],Rnd(MUNDRY),ARMIA[A][I][TDOSW],95);//	         Add ARMIA(A,I,TDOSW),Rnd(MUNDRY),ARMIA(A,I,TDOSW) To 95
			//!!! powinno byc
			//ARMIA[A][I][TDOSW] += Rnd(MUNDRY);
			//clipu(ARMIA[A][I][TDOSW],95);

			if( A==WRG ) ARMIA[A][I][TKORP]+=Rnd(20);	//	         If A=WRG : Add ARMIA(A,I,TKORP),Rnd(20) : End If
			if( ODLOT==1 ) {													//	         If ODLOT=1
				ARMIA[B][STREFA][TTRYB]=8;							//	            ARMIA(B,STREFA,TTRYB)=8
				ENP=2;																	//	            ENP=2
			} else {																	//	         Else
				ZABIJ(B,STREFA,0);											//	            ZABIJ[B,STREFA,0]
			}																					//	         End If
		}																						//	      End If
		ARMIA[B][STREFA][TE]=ENP;										//	      ARMIA(B,STREFA,TE)=ENP
		FX(SAM);																		//	      FX[SAM]
	}																							//	   End If
	//trafienie w mur															//	   'trafienie w mur
	if( STREFA>20 && STREFA<31 && KTO_ATAKUJE==A ) {//	   If STREFA>20 and STREFA<31 and KTO_ATAKUJE=A
		BobOnOff(I2+30,false);															//	      Bob Off I2+30
		FX(14);																			//	      FX[14]
		ARMIA[A][I][TTRYB]=0;												//	      ARMIA(A,I,TTRYB)=0
		MUR[STREFA-21]-=SILA;												//	      Add MUR(STREFA-21),-SILA
		if( MUR[STREFA-21] <= 0 ) {									//	      If MUR(STREFA-21)<=0
			X=(STREFA-21)*64;													//	         X=(STREFA-21)*64
			ResetZone(STREFA);												//	         Reset Zone STREFA
			PBListOnoff(true);
			PasteBob(X,111,BIBY+12+2);								//	         Autoback 2 : Paste Bob X,111,BIBY+12+2 : Wait Vbl : Autoback 1
			PBListOnoff(false);
		}																						//	      End If
	}																							//	   End If
	if( XP_F>640 || XP_F<0 || YP_F>512 || YP_F<0 || STREFA>40 ) {//	   If XP#>640 or XP#<0 or YP#>512 or YP#<0 or STREFA>40
		BobOnOff(I2+30,false);															//	      Bob Off I2+30
		ARMIA[A][I][TTRYB]=0;												//	      ARMIA(A,I,TTRYB)=0
	}																							//	   End If
																								//	End Proc
}
void A_CZAR(aint A,aint I) {
																																//	Procedure A_CZAR[A,I]
	aint I2=0, BR=0, SILA=0, CZAR_TYP=0, MOC=0, BB=0, STREFA=0, B=0, X1=0, Y1=0,
			 ENP=0, CIOS=0, MUNDRY=0, X=0, SPEED=0, TARGET=0, X2=0, Y2=0, ODP=0,
			 ENM=0, J=0, ENERGIA=0, B3=0, B2=0, RASA=0, S=0, JEST=0, L=0, L2=0,
			 BAZA=0, Y=0, KLATKA=0, DX=0, DY=0, ODLOT=0, CELX=0, CELY=0;
	aflt XP_F=0, YP_F=0, VX_F=0, VY_F=0;

	if( A==WRG ) {																								//	   If A=WRG
		I2=I+10;																										//	      I2=I+10
	} else {																											//	   Else
		I2=I;																												//	      I2=I
	}																															//	   End If
	BR=(int)VEKTOR_F[I2][0];																			//	   BR=VEKTOR#(I2,0)
	SILA=BRON[BR][B_SI];																					//	   SILA=BRON(BR,B_SI)
	CZAR_TYP=BRON[BR][B_DOSW];																		//	   CZAR_TYP=BRON(BR,B_DOSW)
	MOC=100-ARMIA[A][I][TDOSW];																		//	   MOC=100-ARMIA(A,I,TDOSW)
																																//	   '------------------------
	if( CZAR_TYP==1 ) {																						//	   If CZAR_TYP=1
		XP_F=VEKTOR_F[I2][3];																				//	      XP#=VEKTOR#(I2,3)
		YP_F=VEKTOR_F[I2][4];																				//	      YP#=VEKTOR#(I2,4)
		VX_F=VEKTOR_F[I2][1];																				//	      VX#=VEKTOR#(I2,1)
		VY_F=VEKTOR_F[I2][2];																				//	      VY#=VEKTOR#(I2,2)
		BB=(int)VEKTOR_F[I2][5];																		//	      BB=VEKTOR#(I2,5)
		XP_F=XP_F+(VX_F*2);																					//	      XP#=XP#+(VX#*2)
		YP_F=YP_F+(VY_F*2);																					//	      YP#=YP#+(VY#*2)
		VEKTOR_F[I2][3]=XP_F;																				//	      VEKTOR#(I2,3)=XP#
		VEKTOR_F[I2][4]=YP_F;																				//	      VEKTOR#(I2,4)=YP#
		if( BR==42 ) { Add(BB,1,1,2); VEKTOR_F[I2][5]=BB; }					//	      If BR=42 : Add BB,1,1 To 2 : VEKTOR#(I2,5)=BB : End If
		if( BR==43 ) { BB=25+Rnd(2); }															//	      If BR=43 : BB=25+Rnd(2) : End If
		if( BR==44 ) { Add(BB,1,10,13); VEKTOR_F[I2][5]=BB; }				//	      If BR=44 : Add BB,1,10 To 13 : VEKTOR#(I2,5)=BB : End If
		_Bob(I2+30,(int)XP_F,(int)YP_F,PIKIETY+BB);									//	      Bob I2+30,XP#,YP#,PIKIETY+BB
		STREFA=_Zone((int)XP_F,(int)YP_F);													//	      STREFA=Zone(XP#,YP#)
		if( STREFA>0 && STREFA!=I2 && STREFA<21 ) {									//	      If STREFA>0 and STREFA<>I2 and STREFA<21
			if( STREFA>10 ) {																					//	         If STREFA>10
				STREFA-=10;																							//	            Add STREFA,-10
				B=WRG;																									//	            B=WRG
			} else {																									//	         Else
				B=ARM;																									//	            B=ARM
			}																													//	         End If
			X1=ARMIA[B][STREFA][TX];																	//	         X1=ARMIA(B,STREFA,TX)
			Y1=ARMIA[B][STREFA][TY];																	//	         Y1=ARMIA(B,STREFA,TY)
			ENP=ARMIA[B][STREFA][TE];																	//	         ENP=ARMIA(B,STREFA,TE)
			CIOS=SILA-Rnd((SILA*MOC)/100);														//	         CIOS=SILA-Rnd((SILA*MOC)/100)
			if( CIOS<=0 ) CIOS=1;																			//	         If CIOS<=0 : CIOS=1 : End If
			ENP-=CIOS;																								//	         Add ENP,-CIOS
			ARMIA[B][STREFA][TE]=ENP;																	//	         ARMIA(B,STREFA,TE)=ENP
			FX(12);																										//	         FX[12]
			if( ENP<=0 ) {																						//	         If ENP<=0
				MUNDRY=RASY[ARMIA[A][I][TRASA]][6];											//	            MUNDRY=RASY(ARMIA(A,I,TRASA),6)
				//!!! mozna lepiej
				Add(ARMIA[A][I][TDOSW],Rnd(MUNDRY),ARMIA[A][I][TDOSW],95);//	            Add ARMIA(A,I,TDOSW),Rnd(MUNDRY),ARMIA(A,I,TDOSW) To 95
				ZABIJ(B,STREFA,0);																			//	            ZABIJ[B,STREFA,0]
			}																													//	         End If
			if( BR!=44 ) {																						//	         If BR<>44
				BobOnOff(I2+30,false);																	//	            Bob Off I2+30
				ARMIA[A][I][TTRYB]=0;																		//	            ARMIA(A,I,TTRYB)=0
			}																													//	         End If
		}																														//	      End If
		if( STREFA>20 && STREFA<31 && KTO_ATAKUJE==A ) {						//	      If STREFA>20 and STREFA<31 and KTO_ATAKUJE=A
			BobOnOff(I2+30,false);																		//	         Bob Off I2+30
			ARMIA[A][I][TTRYB]=0;																			//	         ARMIA(A,I,TTRYB)=0
			MUR[STREFA-21]-=SILA;																			//	         Add MUR(STREFA-21),-SILA
			if( MUR[STREFA-21]<=0 ) {																	//	         If MUR(STREFA-21)<=0
				X=(STREFA-21)*64;																				//	            X=(STREFA-21)*64
				ResetZone(STREFA);																			//	            Reset Zone STREFA
				PBListOnoff(true);																			//	            Autoback 2 : Paste Bob X,111,BIBY+12+2 : Wait Vbl : Autoback 1
				PasteBob(X,111,BIBY+12+2);
				PBListOnoff(false);
			}																													//	         End If
		}																														//	      End If
																																//
		if( XP_F>640 || XP_F<0 || YP_F>512 || YP_F<0 || STREFA>40 ) {//	      If XP#>640 or XP#<0 or YP#>512 or YP#<0 or STREFA>40
			BobOnOff(I2+30,false);																		//	         Bob Off I2+30
			ARMIA[A][I][TTRYB]=0;																			//	         ARMIA(A,I,TTRYB)=0
		}																														//	      End If
	}																															//	   End If
																																//	   '-----------------
	if( CZAR_TYP==2 ) {																						//	   If CZAR_TYP=2
		SPEED=(100-ARMIA[A][I][TSZ])/10;														//	      SPEED=(100-ARMIA(A,I,TSZ))/10
		if( Rnd(SPEED)==0 ) {																				//	      If Rnd(SPEED)=0
																																//
			ARMIA[A][I][TMAG]-=BRON[BR][B_MAG];												//	         Add ARMIA(A,I,TMAG),-BRON(BR,B_MAG)
																																//
			TARGET=ARMIA[A][I][TCELX];																//	         TARGET=ARMIA(A,I,TCELX)
			B=ARMIA[A][I][TCELY];																			//	         B=ARMIA(A,I,TCELY)
			X2=ARMIA[B][TARGET][TX];																	//	         X2=ARMIA(B,TARGET,TX)
			Y2=ARMIA[B][TARGET][TY];																	//	         Y2=ARMIA(B,TARGET,TY)
			ENP=ARMIA[B][TARGET][TE];																	//	         ENP=ARMIA(B,TARGET,TE)
			ODP=ARMIA[B][TARGET][TP];																	//	         ODP=ARMIA(B,TARGET,TP)
			ENM=ARMIA[B][TARGET][TEM];																//	         ENM=ARMIA(B,TARGET,TEM)
			SILA=BRON[BR][B_SI];																			//	         SILA=BRON(BR,B_SI)
			if( BR==45 ) {																						//	         If BR=45
				CENTER(X2,Y2,1);																				//	            CENTER[X2,Y2,1]
				FX(9);																									//	            FX[9]
				for( J=1; J<=20; J++ ) {																//	            For J=1 To 20
					_Bob(I2+30,X2,Y2+8,PIKIETY+7+Rnd(2));									//	               Bob I2+30,X2,Y2+8,PIKIETY+7+Rnd(2)
					rysuj(); BobUpdate(); WaitVbl();											//	               Bob Update : Wait Vbl
				}																												//	            Next J
			}																													//	         End If
			if( BR==46 ) {																						//	         If BR=46
				CENTER(X2,Y2,1);																				//	            CENTER[X2,Y2,1]
//				Fade 5,$0,$25,$48,$16C,$19F,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$FFF,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0;																															//	            Fade 5,$0,$25,$48,$16C,$19F,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$FFF,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0
				FX(8);																									//	            FX[8]
				for( J=1; J<=20; J++ ) {																//	            For J=1 To 20
					_Bob(I2+30,X2,Y2+8,PIKIETY+3+Rnd(3));									//	               Bob I2+30,X2,Y2+8,PIKIETY+3+Rnd(3)
					rysuj(); BobUpdate(); WaitVbl();											//	               Bob Update : Wait Vbl
					if( J==14 ) {																					//	               If J=14 : Fade 4 To 2 : End If
//						Fade 4 To 2 ;
					}
				}																												//	            Next J
																																//
			}																													//	         End If
			if( SILA==0 ) {																						//	         If SILA=0
				FX(10);																									//	            FX[10]
				for( J=1; J<=15; J++ ) {																//	            For J=1 To 15
					_Bob(I2+30,X2,Y2+1,PIKIETY+14+Rnd(3));								//	               Bob I2+30,X2,Y2+1,PIKIETY+14+Rnd(3)
					rysuj(); BobUpdate(); WaitVbl();											//	               Bob Update : Wait Vbl
				}																												//	            Next J
			}																													//	         End If
			ARMIA[B][TARGET][TSZ]+=BRON[BR][B_SZ];										//	         Add ARMIA(B,TARGET,TSZ),BRON(BR,B_SZ)
			if( ARMIA[B][TARGET][TSZ]<1 ) ARMIA[B][TARGET][TSZ]=1;		//	         If ARMIA(B,TARGET,TSZ)<1 : ARMIA(B,TARGET,TSZ)=1 : End If
			ENERGIA=BRON[BR][B_EN];																		//	         ENERGIA=BRON(BR,B_EN)
			CIOS=SILA-Rnd((SILA*MOC)/100);														//	         CIOS=SILA-Rnd((SILA*MOC)/100)
																																//	         'CHECK[CIOS]
			ENP-=CIOS;																								//	         Add ENP,-CIOS
			ENP+=ENERGIA;																							//	         Add ENP,ENERGIA
			if( ENP>ENM ) {																						//	         If ENP>ENM
				ENP=ENM;																								//	            ENP=ENM
			}																													//	         End If
			if( ENP<=0 ) {																						//	         If ENP<=0
				MUNDRY=RASY[ARMIA[A][I][TRASA]][6];											//	            MUNDRY=RASY(ARMIA(A,I,TRASA),6)
				Add(ARMIA[A][I][TDOSW],Rnd(MUNDRY),ARMIA[A][I][TDOSW],95);//	            Add ARMIA(A,I,TDOSW),Rnd(MUNDRY),ARMIA(A,I,TDOSW) To 95
				ZABIJ(B,TARGET,0);																			//	            ZABIJ[B,TARGET,0]
			}																													//	         End If
			ARMIA[A][I][TTRYB]=0;																			//	         ARMIA(A,I,TTRYB)=0
			ARMIA[B][TARGET][TE]=ENP;																	//	         ARMIA(B,TARGET,TE)=ENP
			BobOnOff(I2+30,false);																		//	         Bob Off I2+30
		}																														//	      End If
	}																															//	   End If
																																//	   '------------------
																																//	   '   CHECK[CZAR_TYP]
	//---intuicja---
	if( CZAR_TYP==3 ) {																						//	   If CZAR_TYP=3
																																//	      'intuicja
		SPEED=(100-ARMIA[A][I][TSZ])/10;														//	      SPEED=(100-ARMIA(A,I,TSZ))/10
		if( Rnd(SPEED)==0 ) {																				//	      If Rnd(SPEED)=0
			FX(13);																										//	         FX[13]
			ARMIA[A][I][TMAG]-=BRON[BR][B_MAG];												//	         Add ARMIA(A,I,TMAG),-BRON(BR,B_MAG)
			TARGET=ARMIA[A][I][TCELX];																//	         TARGET=ARMIA(A,I,TCELX)
			B=ARMIA[A][I][TCELY];																			//	         B=ARMIA(A,I,TCELY)
			X2=ARMIA[B][TARGET][TX];																	//	         X2=ARMIA(B,TARGET,TX)
			Y2=ARMIA[B][TARGET][TY];																	//	         Y2=ARMIA(B,TARGET,TY)
			for( J=1; J<=20; ++J ) {																	//	         For J=1 To 20
				_Bob(I2+30,X2,Y2+1,PIKIETY+14+Rnd(3));									//	            Bob I2+30,X2,Y2+1,PIKIETY+14+Rnd(3)
				rysuj(); BobUpdate(); WaitVbl();												//	            Bob Update : Wait Vbl
			}																													//	         Next J
			ARMIA[A][I][TTRYB]=0;																			//	         ARMIA(A,I,TTRYB)=0
			if( B==WRG ) {																						//	         If B=WRG
				ARMIA[B][TARGET][TGLOWA]=1;															//	            ARMIA(B,TARGET,TGLOWA)=1
			}																													//	         End If
			BobOnOff(I2+30,false);																		//	         Bob Off I2+30
		}																														//	      End If
	}																															//	   End If
																																//	   '---------------------
	//---swiatlosc---
	if( CZAR_TYP==5 ) {																						//	   If CZAR_TYP=5
																																//	      'ôwiatîoôê
		SPEED=(100-ARMIA[A][I][TSZ])/10;														//	      SPEED=(100-ARMIA(A,I,TSZ))/10
		if( Rnd(SPEED)==0 ) {																				//	      If Rnd(SPEED)=0
//			Fade 2,,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF;																															//	         Fade 2,,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF
			ARMIA[A][I][TMAG]-=BRON[BR][B_MAG];												//	         Add ARMIA(A,I,TMAG),-BRON(BR,B_MAG)
			FX(13);																										//	         FX[13]
			for( J=1; J<=10; ++J ) {																	//	         For J=1 To 10
				if( ARMIA[WRG][J][TE]>0 ) {															//	            If ARMIA(WRG,J,TE)>0
					_Bob(J+10,ARMIA[WRG][J][TX],ARMIA[WRG][J][TY],ARMIA[WRG][J][TBOB]+2);//	               Bob J+10,ARMIA(WRG,J,TX),ARMIA(WRG,J,TY),ARMIA(WRG,J,TBOB)+2
				}																												//	            End If
			}																													//	         Next J
			rysuj(); BobUpdate(); WaitVbl();													//	         Bob Update : Wait Vbl
			ARMIA[A][I][TTRYB]=0;																			//	         ARMIA(A,I,TTRYB)=0
			Wait(30);																									//	         Wait 30
//			Fade 3 To 2;																						//	         Fade 3 To 2
		}																														//	      End If
	}																															//	   End If
																																//	   '-------------
	//---wszechwiedza---
	if( CZAR_TYP==6 ) {																						//	   If CZAR_TYP=6
																																//	      'wszechwiedza
		SPEED=(100-ARMIA[A][I][TSZ])/10;														//	      SPEED=(100-ARMIA(A,I,TSZ))/10
		if( Rnd(SPEED)==0 ) {																				//	      If Rnd(SPEED)=0
//			Fade 2,,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF;																															//	         Fade 2,,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF,$FFF
			ARMIA[A][I][TMAG]-=BRON[BR][B_MAG];												//	         Add ARMIA(A,I,TMAG),-BRON(BR,B_MAG)
			B=ARMIA[A][I][TCELY];																			//	         B=ARMIA(A,I,TCELY)
			FX(13);																										//	         FX[13]
			if( B==WRG ) {																						//	         If B=WRG
				for( J=1; J<=10; ++J ) {																//	            For J=1 To 10
					ARMIA[B][J][TGLOWA]=1;																//	               ARMIA(B,J,TGLOWA)=1
				}																												//	            Next J
			}																													//	         End If
			ARMIA[A][I][TTRYB]=0;																			//	         ARMIA(A,I,TTRYB)=0
			Wait(30);																									//	         Wait 30
//			Fade 3 To 2;																						//	         Fade 3 To 2
		}																														//	      End If
	}																															//	   End If
																																//	   '--------------
	//---gniew bozy---
	if( CZAR_TYP==7 ) {																						//	   If CZAR_TYP=7
																																//	      'Gniew Boûy
		if( MUZYKA!=0 ) MusicStop();																//	      If MUZYKA : Music Stop : End If
		rysuj(); BobUpdate(); WaitVbl(); FX(8);											//	      Wait Vbl : FX[8]
		ARMIA[A][I][TMAG]-=BRON[BR][B_MAG];													//	      Add ARMIA(A,I,TMAG),-BRON(BR,B_MAG)
		TARGET=ARMIA[A][I][TCELX];																	//	      TARGET=ARMIA(A,I,TCELX)
		B=ARMIA[A][I][TCELY];																				//	      B=ARMIA(A,I,TCELY)
		X2=ARMIA[B][TARGET][TX];																		//	      X2=ARMIA(B,TARGET,TX)
		Y2=ARMIA[B][TARGET][TY];																		//	      Y2=ARMIA(B,TARGET,TY)
//		Fade 2,$0,$25,$48,$16C,$19F,0,0,0,0,0,0,0,0,0,0,0,$FFF,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0;																															//	      Fade 2,$0,$25,$48,$16C,$19F,0,0,0,0,0,0,0,0,0,0,0,$FFF,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
																																//
		CENTER(X2,Y2,0);																						//	      CENTER[X2,Y2,0]
		for( J=1; J<=100; J++ ) {																		//	      For J=1 To 100
			_Bob(I2+30,NOPARI,NOPARI,PIKIETY+3+Rnd(3));								//	         Bob I2+30,,,PIKIETY+3+Rnd(3)
			_Bob(I2+50,NOPARI,NOPARI,PIKIETY+3+Rnd(3));								//	         Bob I2+50,,,PIKIETY+3+Rnd(3)
			Add(B3,1,PIKIETY+18,PIKIETY+20);													//	         Add B3,1,PIKIETY+18 To PIKIETY+20
			_Bob(I2+40,NOPARI,NOPARI,B3);															//	         Bob I2+40,,,B3
			rysuj(); BobUpdate(); WaitVbl();													//	         Bob Update : Wait Vbl
			S=Rnd(15);																								//	         S=Rnd(15)
			if( S<2 ) FX(9);																					//	         If S<2 : FX[9] : End If
			if( S==2 ) FX(8);																					//	         If S=2 : FX[8] : End If
			if( S==3 ) FX(12);																				//	         If S=3 : FX[12] : End If
			if( S==4 ) FX(14);																				//	         If S=4 : FX[14] : End If
			if( J % 2==0 ) {																					//	         If J mod 2=0 : Fade 5 To 2 : Bob I2+30,SX+Rnd(320),SY+Rnd(250),PIKIETY+3+Rnd(3) : End If
//				Fade 5 To 2;
					_Bob(I2+30,SX+Rnd(320),SY+Rnd(250),PIKIETY+3+Rnd(3));
			}
																																//
			if( J % 2==1 ) {																					//	         If J mod 2=1
				_Bob(I2+50,SX+Rnd(320),SY+Rnd(250),PIKIETY+3+Rnd(3));		//	            Bob I2+50,SX+Rnd(320),SY+Rnd(250),PIKIETY+3+Rnd(3)
//				Fade 5,$0,$25,$48,$16C,$19F,0,0,0,0,0,0,0,0,0,0,0,$FFF,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0;																															//	            Fade 5,$0,$25,$48,$16C,$19F,0,0,0,0,0,0,0,0,0,0,0,$FFF,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
			}																													//	         End If
			if( J % 3==0 ) {																					//	         If J mod 3=0 : Bob I2+40,SX+Rnd(320),SY+Rnd(250),B3 : End If
				_Bob(I2+40,SX+Rnd(320),SY+Rnd(250),B3);
			}
			CENTER(X2+Rnd(10)-5,Y2+Rnd(10)-5,0);											//	         CENTER[X2+Rnd(10)-5,Y2+Rnd(10)-5,0]
		}																														//	      Next J
		BobOnOff(I2+30,false); BobOnOff(I2+40,false); BobOnOff(I2+50,false);//	      Bob Off I2+30 : Bob Off I2+40 : Bob Off I2+50
		for( J=1; J<=10; ++J ) {																		//	      For J=1 To 10
			if( ARMIA[B][J][TE]>0 ) {																	//	         If ARMIA(B,J,TE)>0
				ARMIA[B][J][TE]-=Rnd(SILA);															//	            Add ARMIA(B,J,TE),-Rnd(SILA)
				if( ARMIA[B][J][TE]<=0 ) {															//	            If ARMIA(B,J,TE)<=0
					MUNDRY=RASY[ARMIA[A][I][TRASA]][6];										//	               MUNDRY=RASY(ARMIA(A,I,TRASA),6)
					Add(ARMIA[A][I][TDOSW],Rnd(MUNDRY),ARMIA[A][I][TDOSW],95);//	               Add ARMIA(A,I,TDOSW),Rnd(MUNDRY),ARMIA(A,I,TDOSW) To 95
					ZABIJ(B,J,0);																					//	               ZABIJ[B,J,0]
				}																												//	            End If
			}																													//	         End If
		}																														//	      Next J
		ARMIA[A][I][TTRYB]=0;																				//	      ARMIA(A,I,TTRYB)=0
//		Fade 2 To 2;																							//	      Fade 2 To 2
		if( MUZYKA!=0 ) Music(1);																		//	      If MUZYKA : Music 1 : End If
	}																															//	   End If
																																//	   '-----------------------
	//---nawrocenie---
	if( CZAR_TYP==8 ) {																						//	   If CZAR_TYP=8
																																//	      'nawrócenie
		SPEED=(100-ARMIA[A][I][TSZ])/10;														//	      SPEED=(100-ARMIA(A,I,TSZ))/10
		if( Rnd(SPEED)==0 ) {																				//	      If Rnd(SPEED)=0
			ARMIA[A][I][TMAG]-=BRON[BR][B_MAG];												//	         Add ARMIA(A,I,TMAG),-BRON(BR,B_MAG)
			B=ARMIA[A][I][TCELX];																			//	         B=ARMIA(A,I,TCELX)
			B2=ARMIA[A][I][TCELY];																		//	         B2=ARMIA(A,I,TCELY)
			X2=ARMIA[B2][B][TX];																			//	         X2=ARMIA(B2,B,TX)
			Y2=ARMIA[B2][B][TY];																			//	         Y2=ARMIA(B2,B,TY)
			RASA=ARMIA[B2][B][TRASA];																	//	         RASA=ARMIA(B2,B,TRASA)
			FX(15);																										//	         FX[15]
			for( J=1; J<=20; ++J ) {																	//	         For J=1 To 20
				_Bob(I2+30,X2,Y2+1,PIKIETY+14+Rnd(3));									//	            Bob I2+30,X2,Y2+1,PIKIETY+14+Rnd(3)
				rysuj(); BobUpdate(); WaitVbl();												//	            Bob Update : Wait Vbl
			}																													//	         Next J
			ARMIA[A][I][TTRYB]=0;																			//	         ARMIA(A,I,TTRYB)=0
																																//
			if( RASA<10 && B2==WRG ) {																//	         If RASA<10 and B2=WRG
				JEST=0;																									//	            JEST=False
				for( L=1; L<=10; ++L ) {																//	            For L=1 To 10
					if( ARMIA[ARM][L][TE]<=0 ) {													//	               If ARMIA(ARM,L,TE)<=0
						JEST=-1;																						//	                  JEST=True
						L2=L;																								//	                  L2=L
						L=10;																								//	                  L=10
					}																											//	               End If
				}																												//	            Next L
				if( JEST!=0 ) {																					//	            If JEST
					ARMIA[ARM][L2][TRASA]=ARMIA[WRG][B][TRASA];						//	               ARMIA(ARM,L2,TRASA)=ARMIA(WRG,B,TRASA)
					ARMIA[ARM][L2][TSI]=ARMIA[WRG][B][TSI];								//	               ARMIA(ARM,L2,TSI)=ARMIA(WRG,B,TSI)
					ARMIA[ARM][L2][TSZ]=ARMIA[WRG][B][TSZ];								//	               ARMIA(ARM,L2,TSZ)=ARMIA(WRG,B,TSZ)
					ARMIA[ARM][L2][TE]=ARMIA[WRG][B][TE];									//	               ARMIA(ARM,L2,TE)=ARMIA(WRG,B,TE)
					ARMIA[ARM][L2][TEM]=ARMIA[WRG][B][TEM];								//	               ARMIA(ARM,L2,TEM)=ARMIA(WRG,B,TEM)
					ARMIA[ARM][L2][TKLAT]=ARMIA[WRG][B][TKLAT];						//	               ARMIA(ARM,L2,TKLAT)=ARMIA(WRG,B,TKLAT)
					ARMIA[ARM][L2][TMAG]=ARMIA[WRG][B][TMAG];							//	               ARMIA(ARM,L2,TMAG)=ARMIA(WRG,B,TMAG)
					ARMIA[ARM][L2][TMAGMA]=ARMIA[WRG][B][TMAGMA];					//	               ARMIA(ARM,L2,TMAGMA)=ARMIA(WRG,B,TMAGMA)
					ARMIA[ARM][L2][TAMO]=ARMIA[WRG][B][TSZ];							//	               ARMIA(ARM,L2,TAMO)=ARMIA(WRG,B,TSZ)
					ARMIA[ARM][L2][TDOSW]=ARMIA[WRG][B][TDOSW];						//	               ARMIA(ARM,L2,TDOSW)=ARMIA(WRG,B,TDOSW)
					ARMIA[ARM][L2][TP]=0;																	//	               ARMIA(ARM,L2,TP)=0
					for( I=TGLOWA; I<=TPLECAK+7; ++I ) { ARMIA[ARM][L2][I]=0; }//	               For I=TGLOWA To TPLECAK+7 : ARMIA(ARM,L2,I)=0 : Next I
					ARMIA_S[ARM][L2]=ARMIA_S[WRG][B];											//	               ARMIA$(ARM,L2)=ARMIA$(WRG,B)
					ARMIA[WRG][B][TE]=0; BobOnOff(10+B,false); ResetZone(10+B); rysuj(); BobUpdate(); WaitVbl();//	               ARMIA(WRG,B,TE)=0 : Bob Off 10+B : Reset Zone 10+B : Bob Update : Wait Vbl
					ARMIA[WRG][B][TTRYB]=0;																//	               ARMIA(WRG,B,TTRYB)=0
					ARMIA[ARM][L2][TX]=ARMIA[WRG][B][TX];									//	               ARMIA(ARM,L2,TX)=ARMIA(WRG,B,TX)
					ARMIA[ARM][L2][TY]=ARMIA[WRG][B][TY];									//	               ARMIA(ARM,L2,TY)=ARMIA(WRG,B,TY)
					BAZA=RASY[ARMIA[ARM][L2][TRASA]][7];									//	               BAZA=RASY(ARMIA(ARM,L2,TRASA),7)
					X=ARMIA[ARM][L2][TX];																	//	               X=ARMIA(ARM,L2,TX)
					Y=ARMIA[ARM][L2][TY];																	//	               Y=ARMIA(ARM,L2,TY)
					ARMIA[ARM][L2][TBOB]=BAZA;														//	               ARMIA(ARM,L2,TBOB)=BAZA
					_Bob(L2,X,Y,BAZA+1); BobOnOff(B+10+30,false);					//	               Bob L2,X,Y,BAZA+1 : Bob Off B+10+30
					SetZone(L2,X-16,Y-20,X+16,Y);													//	               Set Zone L2,X-16,Y-20 To X+16,Y
				}																												//	            End If
			}																													//	         End If
			BobOnOff(I2+30,false); rysuj(); BobUpdate(); WaitVbl();		//	         Bob Off I2+30 : Bob Update : Wait Vbl
		}																														//	      End If
	}																															//	   End If
																																//
																																//
	//---wybuch---
	if( CZAR_TYP==9 ) {																						//	   If CZAR_TYP=9
																																//	      'wybuch
																																//	      '      KLATKA=VEKTOR#(I2,3)
		SPEED=(100-ARMIA[A][I][TSZ])/10;														//	      SPEED=(100-ARMIA(A,I,TSZ))/10
		if( Rnd(SPEED)==0 ) {																				//	      If Rnd(SPEED)=0
																																//
			X=ARMIA[A][I][TCELX];																			//	         X=ARMIA(A,I,TCELX)
			Y=ARMIA[A][I][TCELY];																			//	         Y=ARMIA(A,I,TCELY)
			CENTER(X,Y,1); FX(14);																		//	         CENTER[X,Y,1] : FX[14]
			for( J=0; J<=2; ++J ) {																		//	         For J=0 To 2
				_Bob(I2+30,X,Y,PIKIETY+18+J);														//	            Bob I2+30,X,Y,PIKIETY+18+J
				CENTER(X+Rnd(10)-5,Y+Rnd(10)-5,0);											//	            CENTER[X+Rnd(10)-5,Y+Rnd(10)-5,0]
				rysuj(); BobUpdate(); WaitVbl();												//	            Bob Update : Wait Vbl
			}																													//	         Next J
			BobOnOff(I2+30,false); ARMIA[A][I][TTRYB]=0;							//	         Bob Off I2+30 : ARMIA(A,I,TTRYB)=0
																																//
																																//	         'zliczanie odlegîoôci od epicentrum
			if( KLATKA==0 ) {																					//	         If KLATKA=0
				for( J=1; J<=10; ++J ) {																//	            For J=1 To 10
					if( ARMIA[WRG][J][TE]>0 ) {														//	               If ARMIA(WRG,J,TE)>0
						X2=ARMIA[WRG][J][TX];																//	                  X2=ARMIA(WRG,J,TX)
						Y2=ARMIA[WRG][J][TY];																//	                  Y2=ARMIA(WRG,J,TY)
						DX=X2-X;																						//	                  DX=X2-X
						DY=Y2-Y;																						//	                  DY=Y2-Y
						ODLEG=Abs(Sqr(DX*DX+DY*DY));												//	                  ODLEG=Abs(Sqr(DX*DX+DY*DY))
																																//
						if( ODLEG<60 ) {																		//	                  If ODLEG<60
							ODLOT=0;																					//	                     ODLOT=0
							if( I!=J ) ODLOT=Rnd(1);													//	                     If I<>J : ODLOT=Rnd(1) : End If
							if( ODLOT==1 ) {																	//	                     If ODLOT=1
								ARMIA[WRG][J][TTRYB]=7;													//	                        ARMIA(WRG,J,TTRYB)=7
								CELX=X2+DX; clip(CELX,20,620);									//	                        CELX=X2+DX : If CELX<20 : CELX=20 : End If : If CELX>620 : CELX=620 : End If
								CELY=Y2+DY; clip(CELY,20,500);									//	                        CELY=Y2+DY : If CELY<20 : CELY=20 : End If : If CELY>500 : CELY=500 : End If
								ARMIA[WRG][J][TCELX]=CELX;											//	                        ARMIA(WRG,J,TCELX)=CELX
								ARMIA[WRG][J][TCELY]=CELY;											//	                        ARMIA(WRG,J,TCELY)=CELY
							}																									//	                     End If
							ENP=ARMIA[WRG][J][TE];														//	                     ENP=ARMIA(WRG,J,TE)
							CIOS=SILA-(ODLEG/2);															//	                     CIOS=SILA-(ODLEG/2)
							ENP-=CIOS;																				//	                     Add ENP,-CIOS
																																//
							if( ENP<=0 ) {																		//	                     If ENP<=0
								MUNDRY=RASY[ARMIA[A][I][TRASA]][6];							//	                        MUNDRY=RASY(ARMIA(A,I,TRASA),6)
								//!!! da sie lepiej
								Add(ARMIA[A][I][TDOSW],Rnd(MUNDRY),ARMIA[A][I][TDOSW],95);//	                        Add ARMIA(A,I,TDOSW),Rnd(MUNDRY),ARMIA(A,I,TDOSW) To 95
								if( ODLOT==1 ) {																//	                        If ODLOT=1
									ARMIA[WRG][J][TTRYB]=8;												//	                           ARMIA(WRG,J,TTRYB)=8
									ENP=2;																				//	                           ENP=2
								} else {																				//	                        Else
									ZABIJ(WRG,J,0);																//	                           ZABIJ[WRG,J,0]
								}																								//	                        End If
							}																									//	                     End If
							ARMIA[WRG][J][TE]=ENP;														//	                     ARMIA(WRG,J,TE)=ENP
						}																										//	                  End If
					}																											//	               End If
					if( ARMIA[ARM][J][TE]>0 ) {														//	               If ARMIA(ARM,J,TE)>0
						X2=ARMIA[ARM][J][TX];																//	                  X2=ARMIA(ARM,J,TX)
						Y2=ARMIA[ARM][J][TY];																//	                  Y2=ARMIA(ARM,J,TY)
						DX=X2-X;																						//	                  DX=X2-X
						DY=Y2-Y;																						//	                  DY=Y2-Y
						ODLEG=Abs(Sqr(DX*DX+DY*DY));												//	                  ODLEG=Abs(Sqr(DX*DX+DY*DY))
						if( ODLEG<60 ) {																		//	                  If ODLEG<60
							ODLOT=0;																					//	                     ODLOT=0
							if( I!=J ) ODLOT=Rnd(1);													//	                     If I<>J : ODLOT=Rnd(1) : End If
							if( ODLOT==1 ) {																	//	                     If ODLOT=1
								ARMIA[ARM][J][TTRYB]=7;													//	                        ARMIA(ARM,J,TTRYB)=7
								CELX=X2+DX; clip(CELX,20,620);									//	                        CELX=X2+DX : If CELX<20 : CELX=20 : End If : If CELX>620 : CELX=620 : End If
								CELY=Y2+DY; clip(CELY,20,500);									//	                        CELY=Y2+DY : If CELY<20 : CELY=20 : End If : If CELY>500 : CELY=500 : End If
								ARMIA[ARM][J][TCELX]=CELX;											//	                        ARMIA(ARM,J,TCELX)=CELX
								ARMIA[ARM][J][TCELY]=CELY;											//	                        ARMIA(ARM,J,TCELY)=CELY
							}																									//	                     End If
																																//
							ENP=ARMIA[ARM][J][TE];														//	                     ENP=ARMIA(ARM,J,TE)
							CIOS=SILA-(ODLEG/2);															//	                     CIOS=SILA-(ODLEG/2)
							ENP-=CIOS;																				//	                     Add ENP,-CIOS
																																//
																																//
							if( ENP<=0 ) {																		//	                     If ENP<=0
								MUNDRY=RASY[ARMIA[A][I][TRASA]][6];							//	                        MUNDRY=RASY(ARMIA(A,I,TRASA),6)
								Add(ARMIA[A][I][TDOSW],Rnd(MUNDRY),ARMIA[A][I][TDOSW],95);//	                        Add ARMIA(A,I,TDOSW),Rnd(MUNDRY),ARMIA(A,I,TDOSW) To 95
								if( ODLOT==1 ) {																//	                        If ODLOT=1
									ARMIA[ARM][J][TTRYB]=8;												//	                           ARMIA(ARM,J,TTRYB)=8
									ENP=2;																				//	                           ENP=2
								} else {																				//	                        Else
									ZABIJ(ARM,J,0);																//	                           ZABIJ[ARM,J,0]
								}																								//	                        End If
							}																									//	                     End If
							ARMIA[ARM][J][TE]=ENP;														//	                     ARMIA(ARM,J,TE)=ENP
						}																										//	                  End If
					}																											//	               End If
				}																												//	            Next J
			}																													//	         End If
																																//	         '      VEKTOR#(I2,3)=VEKTOR#(I2,3)+1
		}																														//	      End If
	}																															//	   End If

	//---uspokojenie---
	if( CZAR_TYP==10 ) {																					//	   If CZAR_TYP=10
																																//	      'uspokojenie
		SPEED=(100-ARMIA[A][I][TSZ])/10;														//	      SPEED=(100-ARMIA(A,I,TSZ))/10
		if( Rnd(SPEED)==0 ) {																				//	      If Rnd(SPEED)=0
			FX(15);																										//	         FX[15]
			ARMIA[A][I][TMAG]-=BRON[BR][B_MAG];												//	         Add ARMIA(A,I,TMAG),-BRON(BR,B_MAG)
			TARGET=ARMIA[A][I][TCELX];																//	         TARGET=ARMIA(A,I,TCELX)
			B=ARMIA[A][I][TCELY];																			//	         B=ARMIA(A,I,TCELY)
			X2=ARMIA[B][TARGET][TX];																	//	         X2=ARMIA(B,TARGET,TX)
			Y2=ARMIA[B][TARGET][TY];																	//	         Y2=ARMIA(B,TARGET,TY)
			for( J=1; J<=20; ++J ) {																	//	         For J=1 To 20
				_Bob(I2+30,X2,Y2+1,PIKIETY+14+Rnd(3));									//	            Bob I2+30,X2,Y2+1,PIKIETY+14+Rnd(3)
				rysuj(); BobUpdate(); WaitVbl();												//	            Bob Update : Wait Vbl
			}																													//	         Next J
			ARMIA[A][I][TTRYB]=0;																			//	         ARMIA(A,I,TTRYB)=0
			if( B==WRG ) {																						//	         If B=WRG
				//!!! zdecydowanie mozna lepiej
				Add(ARMIA[B][TARGET][TKORP],-Rnd(SILA)-10-(ARMIA[A][I][TDOSW]/2),0,ARMIA[B][TARGET][TKORP]);//	            Add ARMIA(B,TARGET,TKORP),-Rnd(SILA)-10-(ARMIA(A,I,TDOSW)/2),0 To ARMIA(B,TARGET,TKORP)
			}																													//	         End If
			BobOnOff(I2+30,false);																		//	         Bob Off I2+30
		}																														//	      End If
	}																															//	   End If
																																//	End Proc
}
void A_LOT(aint A,aint I,aint TRYB) {
																																	//	Procedure A_LOT[A,I,TRYB]
	aint I2=0, X1=0, Y1=0, X2=0, Y2=0, BAZA=0, KLATKA=0, ROZX=0, ROZY,
			 BNR=0, STREFA=0, STREFA2=0, RASA=0, SPEED=0, KLIN=0, ZNX=0,
			 T=0, ST=0, ZNY=0;

	Screen(0);																											//	   Screen 0
	if( A==WRG ) {																									//	   If A=WRG
		I2=I+10;																											//	      I2=I+10
	} else {																												//	   Else
		I2=I;																													//	      I2=I
	}																																//	   End If
																																	//	   'CHECK[TRYB]
																																	//	   'If TRYB=8 : Bell : End If
																																	//	   'wyîâczam goôcia pikiete
	BobOnOff(I2+30,false);																					//	   Bob Off I2+30
																																	//
	X1=ARMIA[A][I][TX];																							//	   X1=ARMIA(A,I,TX)
	Y1=ARMIA[A][I][TY];																							//	   Y1=ARMIA(A,I,TY)
	X2=ARMIA[A][I][TCELX];																					//	   X2=ARMIA(A,I,TCELX)
	Y2=ARMIA[A][I][TCELY];																					//	   Y2=ARMIA(A,I,TCELY)
	BAZA=ARMIA[A][I][TBOB];																					//	   BAZA=ARMIA(A,I,TBOB)
	KLATKA=ARMIA[A][I][TKLAT];																			//	   KLATKA=ARMIA(A,I,TKLAT)
	Add(KLATKA,3,2,11);																							//	   Add KLATKA,3,2 To 11
	ARMIA[A][I][TKLAT]=KLATKA;																			//	   ARMIA(A,I,TKLAT)=KLATKA
	BNR=BAZA+KLATKA;																								//	   BNR=BAZA+KLATKA
	ROZX=X2-X1;																											//	   ROZX=X2-X1
	ROZY=Y2-Y1;																											//	   ROZY=Y2-Y1
	STREFA=_Zone(X1,Y1+1);																						//	   STREFA=Zone(X1,Y1+1)
	STREFA2=_Zone(X1,Y1+30);																					//	   STREFA2=Zone(X1,Y1+30)
	RASA=ARMIA[A][I][TRASA];																				//	   RASA=ARMIA(A,I,TRASA)
	SPEED=5;																												//	   SPEED=5
	KLIN=2;																													//	   KLIN=2
	if( STREFA2>20 && STREFA2<31 ) {																//	   If STREFA2>20 and STREFA2<31
		LimitBob(I2,0,0,640,114);																			//	      Limit Bob I2,0,0 To 640,114
	} else {																												//	   Else
		LimitBob(I2,0,0,640,512);																			//	      Limit Bob I2,0,0 To 640,512
	}																																//	   End If
	if( STREFA>30 && STREFA<41 ) {																	//	   If STREFA>30 and STREFA<41
		PLAPKA(STREFA-30,A,I,X1,Y1);																	//	      PLAPKA[STREFA-30,A,I,X1,Y1]
		if( Param==1 ) {																							//	      If Param=1
			goto OVER;																									//	         Goto OVER
		}																															//	      End If
	}																																//	   End If
	if( Abs(ROZX)>4 ) {																							//	   If Abs(ROZX)>4
		ZNX=Sgn(ROZX);																								//	      ZNX=Sgn(ROZX)
		if( ZNX==-1 ) T=-17;																					//	      If ZNX=-1 : T=-17 : End If
		if( ZNX==1 ) T=17;																						//	      If ZNX=1 : T=17 : End If
		ST=_Zone(X1+T,Y1);																						//	      ST=Zone(X1+T,Y1)
		if( (ST==0 || ((ST>100 && ST<120) || (ST>30 && ST<41))) && A==ARM ) {//	      If ST=0 or(ST>100 and ST<120 or ST>30 and ST<41) and A=ARM
			X1+=ZNX*SPEED;																							//	         Add X1,ZNX*SPEED
			KLIN--;																											//	         Dec KLIN
		}																															//	      End If
	}																																//	   End If
	if( Abs(ROZY)>4 ) {																							//	   If Abs(ROZY)>4
		ZNY=Sgn(ROZY);																								//	      ZNY=Sgn(ROZY)
		if( ZNY==-1 ) T=-21;																					//	      If ZNY=-1 : T=-21 : End If
		if( ZNY==1 ) T=2;																							//	      If ZNY=1 : T=2 : End If
		ST=_Zone(X1,Y1+T);																						//	      ST=Zone(X1,Y1+T)
		if( ST==0 || (ST>30 && ST<41) ) {															//	      If ST=0 or(ST>30 and ST<41)
			Y1+=ZNY*SPEED;																							//	         Add Y1,ZNY*SPEED
			KLIN--;																											//	         Dec KLIN
		}																															//	      End If
	}																																//	   End If
																																	//
	if( Abs(ROZX)<=4 && Abs(ROZY)<=4 ) {														//	   If Abs(ROZX)<=4 and Abs(ROZY)<=4
		KLIN=0;																												//	      KLIN=0
		if( TRYB==8 ) {																								//	      If TRYB=8
			ZABIJ(A,I,0);																								//	         ZABIJ[A,I,0]
			goto OVER;																									//	         Goto OVER
		}																															//	      End If
		ARMIA[A][I][TTRYB]=0;																					//	      ARMIA(A,I,TTRYB)=0
	}																																//	   End If

	//SKIP:																														//	   SKIP:
	ARMIA[A][I][TX]=X1;																							//	   ARMIA(A,I,TX)=X1
	ARMIA[A][I][TY]=Y1;																							//	   ARMIA(A,I,TY)=Y1
	SetZone(I2,X1-15,Y1-15,X1+15,Y1);																//	   Set Zone I2,X1-15,Y1-15 To X1+15,Y1
	_Bob(I2,X1,Y1,BNR);																							//	   Bob I2,X1,Y1,BNR
	if( KLIN==2 ) {																									//	   If KLIN=2
		if( TRYB==8 ) ZABIJ(A,I,0);																		//	      If TRYB=8 : ZABIJ[A,I,0] : End If
		ARMIA[A][I][TTRYB]=0;																					//	      ARMIA(A,I,TTRYB)=0
	}																																//	   End If
	OVER: 																													//	   OVER:
		;																															//	End Proc
}
void A_ROZMOWA(aint A,aint I) {
																								//	Procedure A_ROZMOWA[A,I]
	aint I2=0, X1=0, Y1=0, BAZA=0, BNR=0, TARGET=0, B=0, X2=0, Y2=0,
			 SPEED=0, SPEED2=0, KLATKA=0, STREFA=0, STREFA2=0, ROZX=0, ROZY=0,
			 ZNX=0, ST=0, T=0, ZNY=0, B2=0;
	Screen(0);																		//	   Screen 0
	if( A==WRG ) {																//	   If A=WRG
		I2=I+10;																		//	      I2=I+10
	} else {																			//	   Else
		I2=I;																				//	      I2=I
	}																							//	   End If
	X1=ARMIA[A][I][TX];														//	   X1=ARMIA(A,I,TX)
	Y1=ARMIA[A][I][TY];														//	   Y1=ARMIA(A,I,TY)
	BAZA=ARMIA[A][I][TBOB];												//	   BAZA=ARMIA(A,I,TBOB)
	BNR=BAZA+7;																		//	   BNR=BAZA+7
	TARGET=ARMIA[A][I][TCELX];										//	   TARGET=ARMIA(A,I,TCELX)
	B=ARMIA[A][I][TCELY];													//	   B=ARMIA(A,I,TCELY)
	X2=ARMIA[B][TARGET][TX];											//	   X2=ARMIA(B,TARGET,TX)
	Y2=ARMIA[B][TARGET][TY];											//	   Y2=ARMIA(B,TARGET,TY)
																								//
	SPEED=ARMIA[A][I][TSZ]/10;										//	   SPEED=ARMIA(A,I,TSZ)/10
	SPEED2=3-SPEED;																//	   SPEED2=3-SPEED
	clipl(SPEED2,1);															//	   If SPEED2<=0 Then SPEED2=1
																								//	   If SPEED<=0 Then SPEED=1
	clip(SPEED,1,7);															//	   If SPEED>7 Then SPEED=7
	KLATKA=ARMIA[A][I][TKLAT];										//	   KLATKA=ARMIA(A,I,TKLAT)
	Add(KLATKA,1,0,SPEED2*4-1);										//	   Add KLATKA,1,0 To(SPEED2*4)-1
	ARMIA[A][I][TKLAT]=KLATKA;										//	   ARMIA(A,I,TKLAT)=KLATKA
	KLATKA/=SPEED2;																//	   KLATKA=KLATKA/SPEED2
	KLATKA=AN[KLATKA];														//	   KLATKA=AN(KLATKA)
	STREFA2=_Zone(X1,Y1+30);											//	   STREFA2=Zone(X1,Y1+30)
	STREFA=_Zone(X1,Y1+1);												//	   STREFA=Zone(X1,Y1+1)
	if( STREFA>30 && STREFA<41 ) {								//	   If STREFA>30 and STREFA<41
		PLAPKA(STREFA-30,A,I,X1,Y1);								//	      PLAPKA[STREFA-30,A,I,X1,Y1]
		if( Param==1 ) {														//	      If Param=1
			goto OVER;																//	         Goto OVER
		}																						//	      End If
	}																							//	   End If
	if( STREFA2>20 && STREFA2<31 ) {							//	   If STREFA2>20 and STREFA2<31
		LimitBob(I2,0,0,640,114);										//	      Limit Bob I2,0,0 To 640,114
	} else {																			//	   Else
		LimitBob(I2,0,0,640,512);										//	      Limit Bob I2,0,0 To 640,512
	}																							//	   End If
																								//
	ROZX=X2-X1;																		//	   ROZX=X2-X1
	ROZY=Y2-Y1;																		//	   ROZY=Y2-Y1
	if( Abs(ROZX)>53 ) {													//	   If Abs(ROZX)>53
		ZNX=Sgn(ROZX);															//	      ZNX=Sgn(ROZX)
		if( ZNX==-1 ) { BNR=BAZA+4+KLATKA; T=-17; }	//	      If ZNX=-1 : BNR=BAZA+4+KLATKA : T=-17 : End If
		if( ZNX==1 ) { BNR=BAZA+10+KLATKA; T=17; }	//	      If ZNX=1 : BNR=BAZA+10+KLATKA : T=17 : End If
		ST=_Zone(X1+T,Y1);													//	      ST=Zone(X1+T,Y1)
		if( ST==0 || (ST>30 && ST<41 && A==ARM) ) {	//	      If ST=0 or ST>30 and ST<41 and A=ARM
			X1+=ZNX*SPEED;														//	         Add X1,ZNX*SPEED
		}																						//	      End If
	}																							//	   End If
	if( Abs(ROZY)>42 ) {													//	   If Abs(ROZY)>42
		ZNY=Sgn(ROZY);															//	      ZNY=Sgn(ROZY)
		if( ZNY==-1 ) { B2=BAZA+1+KLATKA; T=-21; }	//	      If ZNY=-1 : B2=BAZA+1+KLATKA : T=-21 : End If
		//!!! blad ? powinno byc T=21 ?
		if( ZNY==1 ) { B2=BAZA+7+KLATKA; T=2; } 		//	      If ZNY=1 : B2=BAZA+7+KLATKA : T=2 : End If
		ST=_Zone(X1,Y1+T);													//	      ST=Zone(X1,Y1+T)
		if( ST==0 || (ST>30 && ST<41 && A==ARM) ) {	//	      If ST=0 or ST>30 and ST<41 and A=ARM
			Y1+=ZNY*SPEED;														//	         Add Y1,ZNY*SPEED
			BNR=B2;																		//	         BNR=B2
		}																						//	      End If
	}																							//	   End If
	if( Abs(ROZX)<=53 && Abs(ROZY)<=42 ) {				//	   If Abs(ROZX)<=53 and Abs(ROZY)<=42
		ARMIA[A][I][TTRYB]=0;												//	      ARMIA(A,I,TTRYB)=0
		GADKA(I,TARGET);														//	      GADKA[I,TARGET]
	}																							//	   End If
	ARMIA[A][I][TX]=X1;														//	   ARMIA(A,I,TX)=X1
	ARMIA[A][I][TY]=Y1;														//	   ARMIA(A,I,TY)=Y1
	SetZone(I2,X1-15,Y1-15,X1+15,Y1);							//	   Set Zone I2,X1-15,Y1-15 To X1+15,Y1
	_Bob(I2,X1,Y1,BNR);														//	   Bob I2,X1,Y1,BNR
	OVER:	;																				//	   OVER:
																								//	End Proc
}
void PLAPKA(aint NR,aint A,aint I,aint X,aint Y) {
																																//	Procedure PLAPKA[NR,A,I,X,Y]
	aint _PLAPKA=0, I2=0, L=0, SKOK=0, CIOS=0;

	_PLAPKA=PLAPKI[NR][0];																															//	   PLAPKA=PLAPKI(NR,0)
	if( A==WRG ) {																															//	   If A=WRG
		I2=I+10;																															//	      I2=I+10
	} else {																															//	   Else
		I2=I;																															//	      I2=I
	}																															//	   End If
	//---przepasc---																															//	   'przepaôê
	if( _PLAPKA==1 ) {																															//	   If PLAPKA=1
		LimitBob(I2,0,0,640,Y+2);																															//	      Limit Bob I2,0,0 To 640,Y+2
		for( L=Y; L<=Y+60; L+=6 ) {																															//	      For L=Y To Y+60 Step 6
			_Bob(I2,NOPARI,L,NOPARI); rysuj(); BobUpdate(); WaitVbl();																															//	         Bob I2,,L, : Bob Update : Wait Vbl
		}																															//	      Next
		SKOK=1;																															//	      SKOK=1
		ZABIJ(A,I,1);																															//	      ZABIJ[A,I,1]
		Wait(20);																															//	      Wait 20
		FX(2);																															//	      FX[2]
	}																															//	   End If
	//---bagno---																															//	   'bagno
	if( _PLAPKA==2 ) {																															//	   If PLAPKA=2
		LimitBob(I2,0,0,640,Y+2);																															//	      Limit Bob I2,0,0 To 640,Y+2
		for( L=Y; L<=Y+35; L++ ) {																															//	      For L=Y To Y+35
			_Bob(I2,NOPARI,L,NOPARI); rysuj(); BobUpdate(); WaitVbl();																															//	         Bob I2,,L, : Bob Update : Wait Vbl
		}																															//	      Next
		ZABIJ(A,I,1);																															//	      ZABIJ[A,I,1]
		SKOK=1;																															//	      SKOK=1
	}																															//	   End If
	//---lodowate jeziorko---																															//	   'lodowate jeziorko
	if( _PLAPKA==3 ) {																															//	   If PLAPKA=3
		SKOK=0;																															//	      SKOK=0
		ARMIA[A][I][TE]-=2;																															//	      Add ARMIA(A,I,TE),-2
		if( ARMIA[A][I][TE]<=0 ) {																															//	      If ARMIA(A,I,TE)<=0
			SKOK=1;																															//	         SKOK=1
			ZABIJ(A,I,1);																															//	         ZABIJ[A,I,1]
		}																															//	      End If
	}																															//	   End If
	//---zapadnia---																															//	   'zapadnia
	if( _PLAPKA==4 ) {																															//	   If PLAPKA=4
		PBListOnoff(true);																															//	      Autoback 2
		PasteBob(PLAPKI[NR][1],PLAPKI[NR][2],BIBY+10);																															//	      Paste Bob PLAPKI(NR,1),PLAPKI(NR,2),BIBY+10
		PBListOnoff(false);																															//	      Autoback 1
		LimitBob(I2,0,0,640,PLAPKI[NR][4]);																															//	      Limit Bob I2,0,0 To 640,PLAPKI(NR,4)
		for( L=Y; L<=Y+80; L+=6 ) {																															//	      For L=Y To Y+80 Step 6
			_Bob(I2,NOPARI,L,NOPARI); rysuj(); BobUpdate(); WaitVbl();																															//	         Bob I2,,L, : Bob Update : Wait Vbl
		}																															//	      Next
		SKOK=1;																															//	      SKOK=1
		ZABIJ(A,I,1);																															//	      ZABIJ[A,I,1]
		Wait(20);																															//	      Wait 20
		FX(2);																															//	      FX[2]
	}																															//	   End If
	//---kolce---																															//	   'kolce
	if( _PLAPKA==5 ) {																															//	   If PLAPKA=5
		SKOK=0;																															//	      SKOK=0
		CIOS=Rnd(10)+5;																															//	      CIOS=Rnd(10)+5
		FX(11);																															//	      FX[11]
		ARMIA[A][I][TE]-=CIOS;																															//	      Add ARMIA(A,I,TE),-CIOS
		if( ARMIA[A][I][TE]<=0 ) { SKOK=1; ZABIJ(A,I,0); }																															//	      If ARMIA(A,I,TE)<=0 : SKOK=1 : ZABIJ[A,I,0] : End If
		PBListOnoff(true);																															//	      Autoback 2
		PasteBob(PLAPKI[NR][1],PLAPKI[NR][2],BIBY+7);																															//	      Paste Bob PLAPKI(NR,1),PLAPKI(NR,2),BIBY+7
		PBListOnoff(false);																															//	      Autoback 1
	}																															//	   End If
	//---przepasc gleboka---																															//	   'przepaôê gîëboka
	if( _PLAPKA==6 ) {																															//	   If PLAPKA=6
		LimitBob(I2,0,0,640,Y+PLAPKI[NR][4]);																															//	      Limit Bob I2,0,0 To 640,Y+PLAPKI(NR,4)
		for( L=Y; L<=Y+180; L+=6 ) {																															//	      For L=Y To Y+180 Step 6
			_Bob(I2,NOPARI,L,NOPARI); rysuj(); BobUpdate(); WaitVbl();																															//	         Bob I2,,L, : Bob Update : Wait Vbl
		}																															//	      Next
		SKOK=1;																															//	      SKOK=1
		ZABIJ(A,I,1);																															//	      ZABIJ[A,I,1]
		Wait(20);																															//	      Wait 20
		FX(2);																															//	      FX[2]
	}																															//	   End If
																																//
	Param=SKOK;																															//	End Proc[SKOK]
}

void _ATAK(aint TYP) {
																	//	Procedure _ATAK[TYP]
	aint WROG=0, STREFA=0, A=0, X=0, Y=0;

	_GET_XY(2,0,0);									//	   _GET_XY[2,0,0]
	if( TYP==6 ) {									//	If TYP=6 : WROG=False : Else : WROG=True : End If
		WROG=0;
	} else {
		WROG=-1;
	}
	Screen(0);											//	   Screen 0
	BobOnOff(30+NUMER,false);				//	   Bob Off 30+NUMER
	STREFA=_Zone(OX,OY);						//	   STREFA=Zone(OX,OY)
	if( STREFA>10 && STREFA<21 ) {	//	   If STREFA>10 and STREFA<21
		A=WRG;												//	      A=WRG
		STREFA-=10;										//	      Add STREFA,-10
																	//	      'ûeby nie gadali ze zwierzakami
		if( ARMIA[A][STREFA][TRASA]<10 ) {//	      If ARMIA(A,STREFA,TRASA)<10
			WROG=-1;										//	         WROG=True
		}															//	      End If
	} else {												//	   Else
		A=ARM;												//	      A=ARM
	}																//	   End If
	if( STREFA>0 && STREFA<11 && WROG!=0 ) {//	   If STREFA>0 and STREFA<11 and WROG
		ARMIA[ARM][NUMER][TCELX]=STREFA;//	      ARMIA(ARM,NUMER,TCELX)=STREFA
		ARMIA[ARM][NUMER][TCELY]=A;		//	      ARMIA(ARM,NUMER,TCELY)=A
		ARMIA[ARM][NUMER][TTRYB]=TYP;	//	      ARMIA(ARM,NUMER,TTRYB)=TYP
		X=ARMIA[A][STREFA][TX];				//	      X=ARMIA(A,STREFA,TX)
		Y=ARMIA[A][STREFA][TY];				//	      Y=ARMIA(A,STREFA,TY)
		_Bob(51,X,Y,2+BUBY);						//	      Bob 51,X,Y,2+BUBY : Bob Update : Wait Vbl
		BobUpdate();
		WaitVbl();
	}																//	   End If
	while( MouseKey()==LEWY ) {			//	   While Mouse Key=LEWY : Wend
		ProcessEvents();
	}
																	//	End Proc
}
void CZARY(aint BL,aint BP) {
																																		//	Procedure CZARY[BL,BP]
  aint B1=0, B2=0, CZAR_TYP=0, BR=0, MAG=0, MAG2=0, X1=0, Y1=0,
			 STREFA=0, A=0, X=0, Y=0;
  aflt DX_F=0, DY_F=0, L_F=0, VX_F=0, VY_F=0;

	B1=ARMIA[ARM][NUMER][TLEWA];																																	//	   B1=ARMIA(ARM,NUMER,TLEWA)
	B2=ARMIA[ARM][NUMER][TPRAWA];																																	//	   B2=ARMIA(ARM,NUMER,TPRAWA)
	if( BP==12 ) {																																	//	   If BP=12
		CZAR_TYP=BRON[B2][B_DOSW];																																	//	      CZAR_TYP=BRON(B2,B_DOSW)
		BR=B2;																																	//	      BR=B2
	}																																	//	   End If
	if( BL==12 ) {																																	//	   If BL=12
		CZAR_TYP=BRON[B1][B_DOSW];																																	//	      CZAR_TYP=BRON(B1,B_DOSW)
		BR=B1;																																	//	      BR=B1
	}																																	//	   End If
	MAG=BRON[BR][B_MAG];																																	//	   MAG=BRON(BR,B_MAG)
	MAG2=ARMIA[ARM][NUMER][TMAG];																																	//	   MAG2=ARMIA(ARM,NUMER,TMAG)
	if( MAG>MAG2 ) {																																	//	   If MAG>MAG2
		Screen(1);																																	//	      Screen 1
		GADUP(3);																																	//	      GADUP[3]
		goto OVER;																																	//	      Goto OVER
	}																																	//	   End If
																																		//
	if( CZAR_TYP==1 || CZAR_TYP==9 ) {																																	//	   If CZAR_TYP=1 or CZAR_TYP=9
		_GET_XY(0,0,0);																																	//	      _GET_XY[0,0,0]
		MAG2-=MAG;																																	//	      Add MAG2,-MAG
		ARMIA[ARM][NUMER][TMAG]=MAG2;																																	//	      ARMIA(ARM,NUMER,TMAG)=MAG2
		ARMIA[ARM][NUMER][TCELX]=OX;																																	//	      ARMIA(ARM,NUMER,TCELX)=OX
		ARMIA[ARM][NUMER][TCELY]=OY;																																	//	      ARMIA(ARM,NUMER,TCELY)=OY
		ARMIA[ARM][NUMER][TTRYB]=4;																																	//	      ARMIA(ARM,NUMER,TTRYB)=4
		Screen(0); _Bob(51,OX,OY+12,2+BUBY); rysuj(); BobUpdate(); WaitVbl();																																	//	      Screen 0 : Bob 51,OX,OY+12,2+BUBY : Bob Update : Wait Vbl
		X1=ARMIA[ARM][NUMER][TX];																																	//	      X1=ARMIA(ARM,NUMER,TX)
		Y1=ARMIA[ARM][NUMER][TY]-20;																																	//	      Y1=ARMIA(ARM,NUMER,TY)-20
		DX_F=OX-X1;																																	//	      DX#=OX-X1
		DY_F=OY-Y1;																																	//	      DY#=OY-Y1
		L_F=sqrt(DX_F*DX_F+DY_F*DY_F)+1;																																	//	      L#=Sqr(DX#*DX#+DY#*DY#)+1
		VX_F=DX_F/L_F;																																	//	      VX#=DX#/L#
		VY_F=DY_F/L_F;																																	//	      VY#=DY#/L#
		VEKTOR_F[NUMER][1]=VX_F*6;																																	//	      VEKTOR#(NUMER,1)=VX#*6
		VEKTOR_F[NUMER][2]=VY_F*6;																																	//	      VEKTOR#(NUMER,2)=VY#*6
		if( CZAR_TYP==1 ) {																																	//	      If CZAR_TYP=1
			VEKTOR_F[NUMER][3]=X1;																																	//	         VEKTOR#(NUMER,3)=X1
		} else {																																	//	      Else
			VEKTOR_F[NUMER][3]=0;																																	//	         VEKTOR#(NUMER,3)=0
		}																																	//	      End If
		VEKTOR_F[NUMER][4]=Y1;																																	//	      VEKTOR#(NUMER,4)=Y1
		VEKTOR_F[NUMER][0]=BR;																																	//	      VEKTOR#(NUMER,0)=BR
	} else {																																	//	   Else
		_GET_XY(2,0,0);																																	//	      _GET_XY[2,0,0]
		STREFA=_Zone(OX,OY);																																	//	      STREFA=Zone(OX,OY)
		if( STREFA>10 ) {																																	//	      If STREFA>10
			A=WRG;																																	//	         A=WRG
			STREFA-=10;																																	//	         Add STREFA,-10
		} else {																																	//	      Else
			A=ARM;																																	//	         A=ARM
		}																																	//	      End If
		if( STREFA>0 && STREFA<11 ) {																																	//	      If STREFA>0 and STREFA<11
			VEKTOR_F[NUMER][0]=BR;																																	//	         VEKTOR#(NUMER,0)=BR
			ARMIA[ARM][NUMER][TCELX]=STREFA;																																	//	         ARMIA(ARM,NUMER,TCELX)=STREFA
			ARMIA[ARM][NUMER][TCELY]=A;																																	//	         ARMIA(ARM,NUMER,TCELY)=A
			ARMIA[ARM][NUMER][TTRYB]=5;																																	//	         ARMIA(ARM,NUMER,TTRYB)=5
			X=ARMIA[A][STREFA][TX];																																	//	         X=ARMIA(A,STREFA,TX)
			Y=ARMIA[A][STREFA][TY];																																	//	         Y=ARMIA(A,STREFA,TY)
			_Bob(51,X,Y,2+BUBY); rysuj(); BobUpdate(); WaitVbl();																																	//	         Bob 51,X,Y,2+BUBY : Bob Update : Wait Vbl
		} else {																																	//	      Else
			GADUP(3);																																	//	         GADUP[3]
		}																																	//	      End If
		while( MouseKey()==LEWY ) ProcessEvents();																																	//	      While Mouse Key=LEWY : Wend
	}																																	//	   End If
	OVER: ;																																	//	   OVER:
																																		//	End Proc
}
void STRZAL(void) {
																						//	Procedure STRZAL
	aint B1=0, B2=0, BT1=0, BT2=0, BT3=0, CZAD=0, X1=0, Y1=0, I=0;
	aflt DX_F=0, DY_F=0, L_F=0, VX_F=0, VY_F=0, X_F=0, Y_F=0;

	B1=ARMIA[ARM][NUMER][TLEWA];							//	   B1=ARMIA(ARM,NUMER,TLEWA)
	B2=ARMIA[ARM][NUMER][TPRAWA];							//	   B2=ARMIA(ARM,NUMER,TPRAWA)
	BT1=BRON[B1][B_TYP];											//	   BT1=BRON(B1,B_TYP)
	BT2=BRON[B2][B_TYP];											//	   BT2=BRON(B2,B_TYP)
	BT3=RASY[ARMIA[ARM][NUMER][TRASA]][4];		//	   BT3=RASY(ARMIA(ARM,NUMER,TRASA),4)
																						//	   'szybkoôê lotu pocisku
	CZAD=4;																		//	   CZAD=4
	if((BT1==4 && BT2==5 && STRZALY[NUMER]>0) ||//	   If(BT1=4 and BT2=5 and STRZALY(NUMER)>0) or(BT1=5 and BT2=4 and STRZALY(NUMER)>0) or(BT1=15 and BT2=16) or(BT1=16 and BT2=15) or(BT1=9 and BT2<>12) or(BT2=9 and BT1<>12)
	   (BT1==5 && BT2==4 && STRZALY[NUMER]>0) ||
		 (BT1==15 && BT2==16) ||
		 (BT1==16 && BT2==15) ||
		 (BT1==9 && BT2!=12) ||
		 (BT2==9 && BT1!=12) ) {
		VEKTOR_F[NUMER][0]=BRON[B1][B_SI]+BRON[B2][B_SI];//	      VEKTOR#(NUMER,0)=BRON(B1,B_SI)+BRON(B2,B_SI)
		if( BT1==4 || BT2==4 ) {								//	      If BT1=4 or BT2=4
			STRZALY[NUMER]--;											//	         Dec STRZALY(NUMER)
		}																				//	      End If
		if( BT1==9 ) {													//	      If BT1=9
			VEKTOR_F[NUMER][0]=BRON[B1][B_SI]*3;	//	         VEKTOR#(NUMER,0)=BRON(B1,B_SI)*3
			PRZELICZ(3,-1);												//	         PRZELICZ[3,-1]
			ARMIA[ARM][NUMER][TLEWA]=0;						//	         ARMIA(ARM,NUMER,TLEWA)=0
			VEKTOR_F[NUMER][5]=B1;								//	         VEKTOR#(NUMER,5)=B1
			goto SKIP;														//	         Goto SKIP
		}																				//	      End If
		if( BT2==9 ) {													//	      If BT2=9
			VEKTOR_F[NUMER][0]=BRON[B2][B_SI]*3;	//	         VEKTOR#(NUMER,0)=BRON(B2,B_SI)*3
			PRZELICZ(4,-1);												//	         PRZELICZ[4,-1]
			ARMIA[ARM][NUMER][TPRAWA]=0;					//	         ARMIA(ARM,NUMER,TPRAWA)=0
			VEKTOR_F[NUMER][5]=B2;								//	         VEKTOR#(NUMER,5)=B2
			goto SKIP;														//	         Goto SKIP
		}																				//	      End If
		if( BT1==16 ) {													//	      If BT1=16
			VEKTOR_F[NUMER][0]=-VEKTOR_F[NUMER][0];//	         VEKTOR#(NUMER,0)=-VEKTOR#(NUMER,0)
			ARMIA[ARM][NUMER][TLEWA]=0;						//	         ARMIA(ARM,NUMER,TLEWA)=0
		}																				//	      End If
		if( BT2==16 ) {													//	      If BT2=16
			VEKTOR_F[NUMER][0]=-VEKTOR_F[NUMER][0];	//	         VEKTOR#(NUMER,0)=-VEKTOR#(NUMER,0)
			ARMIA[ARM][NUMER][TPRAWA]=0;					//	         ARMIA(ARM,NUMER,TPRAWA)=0
		}																				//	      End If
		SKIP:																		//	      SKIP:
		if( BT3==BT1 || BT3==BT2 ) {						//	      If BT3=BT1 or BT3=BT2
																						//	         'rasa bonus
			VEKTOR_F[NUMER][0]=VEKTOR_F[NUMER][0]+10;		//	         VEKTOR#(NUMER,0)=VEKTOR#(NUMER,0)+10
		}																				//	      End If
																						//
		_GET_XY(0,0,0);													//	      _GET_XY[0,0,0]
		ARMIA[ARM][NUMER][TCELX]=OX;						//	      ARMIA(ARM,NUMER,TCELX)=OX
		ARMIA[ARM][NUMER][TCELY]=OY;						//	      ARMIA(ARM,NUMER,TCELY)=OY
		ARMIA[ARM][NUMER][TTRYB]=3;							//	      ARMIA(ARM,NUMER,TTRYB)=3
		Screen(0); _Bob(51,OX,OY+12,2+BUBY); BobUpdate(); WaitVbl();	//	      Screen 0 : Bob 51,OX,OY+12,2+BUBY : Bob Update : Wait Vbl
		BobOnOff(30+NUMER,false);								//	      Bob Off 30+NUMER
		X1=ARMIA[ARM][NUMER][TX];								//	      X1=ARMIA(ARM,NUMER,TX)
		Y1=ARMIA[ARM][NUMER][TY]-20;						//	      Y1=ARMIA(ARM,NUMER,TY)-20
		DX_F=OX-X1;															//	      DX#=OX-X1
		DY_F=OY-Y1;															//	      DY#=OY-Y1
		L_F=sqrt(DX_F*DX_F+DY_F*DY_F)+1;				//	      L#=Sqr(DX#*DX#+DY#*DY#)+1
		VX_F=DX_F/L_F;													//	      VX#=DX#/L#
		VY_F=DY_F/L_F;													//	      VY#=DY#/L#
		//!!! BLAD ? ( BT1==4 || BT2==4 || BT1==9 || BT2==9 )
		if( BT1==4 || BT1==5 || BT1==9 || BT2==9 ) {//	      If BT1=4 or BT1=5 or BT1=9 or BT2=9


			unsigned char buf[32*32*4];
			_BufColor(0,0,0,0);
			_BufSet(buf,32,32);
																						//	         Screen 2
																						//	         Cls 0
			X_F=15; Y_F=15;												//	         X#=15 : Y#=15
			for(I=1;I<=20;++I) {									//	         For I=1 To 20
				X_F+=VX_F; Y_F+=VY_F;								//	            X#=X#+VX# : Y#=Y#+VY#
				_BufColor(0,0,0,0.75);							//	            Ink 19 : Plot X#,Y#+15
				_BufPlot(X_F,Y_F+15);
				_BufColor(1,1,1,1);									//	            Ink 15 : Plot X#,Y#
				_BufPlot(X_F,Y_F);
			}																			//	         Next I
			GetSprite(BSIBY+NUMER,buf,32,32);			//	         Get Sprite BSIBY+NUMER,0,0 To 31,31 : Wait Vbl
			HotSpot(BSIBY+NUMER,0x11);						//	         Hot Spot BSIBY+NUMER,$11
		}																				//	      End If
		VEKTOR_F[NUMER][1]=VX_F*6;							//	      VEKTOR#(NUMER,1)=VX#*6
		VEKTOR_F[NUMER][2]=VY_F*6;							//	      VEKTOR#(NUMER,2)=VY#*6
		VEKTOR_F[NUMER][3]=X1;									//	      VEKTOR#(NUMER,3)=X1
		VEKTOR_F[NUMER][4]=Y1;									//	      VEKTOR#(NUMER,4)=Y1
	} else {																	//	   Else
		if( BT1!=12 && BT2!=12 ) GADUP(3);			//	      If BT1<>12 and BT2<>12 : GADUP[3] : End If
	}																					//	   End If
	if( BT1==12 || BT2==12 ) CZARY(BT1,BT2);	//	   If BT1=12 or BT2=12 : CZARY[BT1,BT2] : End If
																						//	End Proc
}

void ZABIJ(aint A,aint NR,aint CICHO) {
																							//	Procedure ZABIJ[A,NR,CICHO]
	aint RASA=0, SAM=0, X=0, Y=0, SEK=0, I=0, BR=0, BAZA=0, KB=0, STREFA2;

	RASA=ARMIA[A][NR][TRASA];										//	   RASA=ARMIA(A,NR,TRASA)
	if( RASA>9 ) {															//	   If RASA>9
		SAM=3;																		//	      SAM=3
		SamBank(5);																//	      Sam Bank 5
	} else {																		//	   Else
		SAM=7;																		//	      SAM=7
	}																						//	   End If
	FX(SAM);																		//	   FX[SAM]
	SamBank(4);																	//	   Sam Bank 4
	ARMIA[A][NR][TE]=0;													//	   ARMIA(A,NR,TE)=0
	ARMIA[A][NR][TTRYB]=0;											//	   ARMIA(A,NR,TTRYB)=0
	X=ARMIA[A][NR][TX];													//	   X=ARMIA(A,NR,TX)
	Y=ARMIA[A][NR][TY];													//	   Y=ARMIA(A,NR,TY)
	SEKTOR(X,Y); SEK=Param;											//	   SEKTOR[X,Y] : SEK=Param
	for( I=0; I<=3; ++I ) {											//	   For I=0 To 3
		if( GLEBA[SEK][I]==0 ) {									//	      If GLEBA(SEK,I)=0
			if( A==ARM ) {													//	         If A=ARM
				GLEBA[SEK][I]=ARMIA[A][NR][TKORP+I];	//	            GLEBA(SEK,I)=ARMIA(A,NR,TKORP+I)
			} else {																//	         Else
				if( RASA>9 ) {												//	            If RASA>9
					BR=RASY[RASA][3+Rnd(1)];						//	               BR=RASY(RASA,3+Rnd(1))
					GLEBA[SEK][I]=BR;										//	               GLEBA(SEK,I)=BR
				} else {															//	            Else
					if( Rnd(2)==0 ) {										//	               If Rnd(2)=0
						LOSUJ:														//	                  LOSUJ:
						BR=Rnd(MX_WEAPON);								//	                  BR=Rnd(MX_WEAPON)
						if( BRON[BR][B_CENA]<(ARMIA[A][NR][TDOSW]*30)+ARMIA[A][NR][TSI] ) {//	                  If BRON(BR,B_CENA)<(ARMIA(A,NR,TDOSW)*30)+ARMIA(A,NR,TSI)
							GLEBA[SEK][I]=BR;								//	                     GLEBA(SEK,I)=BR
						} else {													//	                  Else
							goto LOSUJ;											//	                     Goto LOSUJ
						}																	//	                  End If
					}																		//	               End If
				}																			//	            End If
			}																				//	         End If
		}																					//	      End If
	}																						//	   Next I
	BAZA=ARMIA[A][NR][TBOB];										//	   BAZA=ARMIA(A,NR,TBOB)
	if( A==WRG ) {															//	   If A=WRG
		NR+=10;																		//	      Add NR,10
		for( I=1; I<=10; ++I ) {									//	      For I=1 To 10
			Add(ARMIA[A][I][TKORP],-Rnd(20),1,ARMIA[A][I][TKORP]);//	         Add ARMIA(A,I,TKORP),-Rnd(20),1 To ARMIA(A,I,TKORP)
		}																					//	      Next I
	}																						//	   End If
	BobOnOff(NR,false);													//	   Bob Off NR
	BobOnOff(30+NR,false);											//	   Bob Off 30+NR
	BobUpdate(); WaitVbl();											//	   Bob Update : Wait Vbl
	KB=BAZA+16;																	//	   KB=BAZA+16
	if( Rnd(1)==0 ) KB=Hrev(BAZA+16);						//	   If Rnd(1)=0 : KB=Hrev(BAZA+16) : End If
	STREFA2=_Zone(X,Y+30);											//	   STREFA2=Zone(X,Y+30)
	if( CICHO==0 && (STREFA2<20 || STREFA2>31) && SCENERIA!=7 && PREFS[4]==1 ) {	//	   If CICHO=0 and(STREFA2<20 or STREFA2>31) and SCENERIA<>7 and PREFS(4)=1
		PBListOnoff(true);
		//!!! inaczej
		//PasteBob(X-24,Y-20,KB);									//	      Autoback 2 : Paste Bob X-24,Y-20,KB : Wait 2 : Autoback 1
		PasteBob(X,Y,KB);													//	      Autoback 2 : Paste Bob X-24,Y-20,KB : Wait 2 : Autoback 1
		PBListOnoff(false);
	}																						//	   End If
	ResetZone(NR);															//	   Reset Zone NR
																							//	End Proc
}

void _GADKA_BULI(aint X, aint Y, aint &ILE, aint &TAK) {
	aint KONIEC2=0, STREFA=0;
	rysuj();
	KONIEC2=0;																									//	   KONIEC2=False
	gad_back(1.0); _Bar(X+141,Y+1,X+140+148,Y+82);							//	   Ink 25 : Bar X+141,Y+1 To X+140+148,Y+82
	gad_text(1.0);																							//	   Ink 30
	Text(X+144,Y+15,GS("020"));																	//	   Text X+144,Y+15,"It will cost you "
	Text(X+144,Y+25,Str_S(ILE)+GS("021"));											//	   Text X+144,Y+25,Str$(ILE)+" gold pieces"
	Text(X+144,Y+35,GS("022"));																	//	   Text X+144,Y+35,"Will you pay ?"
	GADGET(X+144,Y+60,25,15,GS("YES"),7,9,11,0,10);							//	   GADGET[X+144,Y+60,25,15,"Yes",7,9,11,0,10]
	GADGET(X+260,Y+60,25,15,GS("NO"),7,9,11,0,11);							//	   GADGET[X+260,Y+60,25,15,"No",7,9,11,0,11]
	WaitVbl();
	do {																												//	   Repeat
		ProcessEvents();
		if( MouseClick()==1 ) {																		//	      If Mouse Click=1
			STREFA=MouseZone();																			//	         STREFA=Mouse Zone
			if( STREFA==10 && GRACZE[1][1]-ILE>=0 ) {								//	         If STREFA=10 and GRACZE(1,1)-ILE>=0
				GRACZE[1][1]-=ILE;																		//	            Add GRACZE(1,1),-ILE
				TAK=-1;																								//	            TAK=True
				KONIEC2=-1;																						//	            KONIEC2=True
			}																												//	         End If
			if( STREFA==11 ) {																			//	         If STREFA=11
				TAK=0;																								//	            TAK=False
				KONIEC2=-1;																						//	            KONIEC2=True
			}																												//	         End If
		}																													//	      End If
	} while( KONIEC2==0 );																			//	   Until KONIEC2
	ResetZone(10); ResetZone(11);																//	   Reset Zone 10 : Reset Zone 11
	gad_back(1.0); _Bar(X+141,Y+1,X+140+148,Y+82);							//	   Ink 25 : Bar X+141,Y+1 To X+140+148,Y+82
	return;																											//	   Return
}
void _rysuj_gadka(void) {
	aint s = Screen();

	//ekran mruga na niektorych kartach graficznych, wiec czyscimy to co nie bedzie rysowane
	Gfx::Color(0.f,0.f,0.f);
	Screen(1);
	_ClearRaster(0,ScreenY()-5,640,525);

	Screen(0);
	rysuj_scenerie();
	Screen(1);
	_restore_ekran1();

	Screen(s);
}
void GADKA(aint NR,aint B) {
																															//	Procedure GADKA[NR,B]
	aint OSOBA=0, AGRESJA=0, AG2=0, CODP=0, GODP=0, JP=0, _MIASTO=0,
			 TAK=0, I=0, XA=0, YA=0, XB=0, YB=0, CELX=0, CELY=0, SRX=0, SRY=0,
			 X=0, Y=0, TYP=0, DL=0, ZN=0, KONIEC=0, STREFA=0, TYP2=0,
			 ODP=0, JEST=0, L=0, L2=0, ILE=0, MXSI=0, BAZA=0, GUL=0, F=0,
			 PX=0, PY=0, LEVEL=0, CENA=0;
	astr GTEX_S="", L_S="", R_S="", A_S="", B_S="";

	void (*rys)(void) = rysuj_ekran_ptr;

	OSOBA=B;																										//	   OSOBA=B
	AGRESJA=ARMIA[WRG][B][TKORP];																//	   AGRESJA=ARMIA(WRG,B,TKORP)
	AG2=AGRESJA/50;																							//	   AG2=AGRESJA/50
	CODP=ARMIA[WRG][B][TPRAWA];																	//	   CODP=ARMIA(WRG,B,TPRAWA)
	if( CODP!=-1 ) {																						//	   If CODP<>-1
		if( AG2>=3 ) CODP=Rnd(2);																	//	      If AG2>=3 : CODP=Rnd(2) : End If
		if( AG2==2 ) CODP=Rnd(2)+3;																//	      If AG2=2 : CODP=Rnd(2)+3 : End If
		if( AG2==1 ) CODP=Rnd(2)+6;																//	      If AG2=1 : CODP=Rnd(2)+6 : End If
		if( AG2==0 ) {																						//	      If AG2=0
			if( ARMIA[WRG][B][TPRAWA]==0 ) {												//	         If ARMIA(WRG,B,TPRAWA)=0
				if( Rnd(2)==1 ) {																			//	            If Rnd(2)=1
					CODP=Rnd(24)+9;																			//	               CODP=Rnd(24)+9
				} else {																							//	            Else
					CODP=9+Rnd(2);																			//	               CODP=9+Rnd(2)
				}																											//	            End If
				ARMIA[WRG][B][TPRAWA]=CODP;														//	            ARMIA(WRG,B,TPRAWA)=CODP
			} else {																								//	         Else
				CODP=ARMIA[WRG][B][TPRAWA];														//	            CODP=ARMIA(WRG,B,TPRAWA)
			}																												//	         End If
		}																													//	      End If
	}																														//	   End If
	ARMIA[WRG][B][TGLOWA]=1;																		//	   ARMIA(WRG,B,TGLOWA)=1
																															//	   'BOMBA1=False
	GODP=4-(AGRESJA/30);																				//	   GODP=4-(AGRESJA/30)
	if( GODP<0 ) GODP=0;																				//	   If GODP<0 Then GODP=0
	if( ARMIA[ARM][0][TNOGI]>69 && GODP>=3 && CODP>-1 && Rnd(7)==1 ) {//	   If ARMIA(ARM,0,TNOGI)>69 and GODP>=3 and CODP>-1 and Rnd(7)=1
		JP=1;																											//	      JP=1
	}																														//	   End If
	_MIASTO=ARMIA[ARM][0][TNOGI]-70;														//	   MIASTO=ARMIA(ARM,0,TNOGI)-70
	TAK=0;																											//	   TAK=False
	ScreenDisplay(0,130,40,320,123);
	Screen(1);																									//	   Screen 1
	Gfx::Color(0.f,0.f,0.f); Cls();
	ScreenDisplay(1,130,142,320,150);														//	   Screen Display 1,130,142,320,150 : View
	for(I=0;I<=3;++I) {																					//	   For I=0 To 3
		PasteBob(0,I*50,1);																				//	      Paste Bob 0,I*50,1
	}																														//	   Next I
	MSY=MSY+183;																								//	   MSY=MSY+183
	XA=ARMIA[ARM][0][TX]; YA=ARMIA[ARM][0][TY];									//	   XA=ARMIA(ARM,0,TX) : YA=ARMIA(ARM,0,TY)
	XB=ARMIA[ARM][NR][TX]; YB=ARMIA[ARM][NR][TY];								//	   XB=ARMIA(ARM,NR,TX) : YB=ARMIA(ARM,NR,TY)
																															//
	CELX=ARMIA[WRG][B][TX];																			//	   CELX=ARMIA(WRG,B,TX)
	CELY=ARMIA[WRG][B][TY];																			//	   CELY=ARMIA(WRG,B,TY)
	SRX=(XB+CELX)/2; SRY=(YB+CELY)/2;														//	   SRX=(XB+CELX)/2 : SRY=(YB+CELY)/2
	Screen(0);																									//	   Screen 0
	BobOnOff(50,false); BobOnOff(51,false);											//	   Bob Off 50 : Bob Off 51 : Bob Update
	_Bob(50,XB,YB,1+BUBY); _Bob(51,CELX,CELY,2+BUBY);						//	   Bob 50,XB,YB,1+BUBY : Bob 51,CELX,CELY,2+BUBY
																															//	   Bob Update : Wait Vbl
	CENTER_V=60;																								//	   CENTER_V=60
	CENTER(SRX,SRY,1);																					//	   CENTER[SRX,SRY,1]
	CENTER_V=100;																								//	   CENTER_V=100
	Screen(1);																									//	   Screen 1
	for( I=0; I<=2; ++I ) {																			//	   For I=0 To 2
		PasteBob(0,I*50,1);																				//	      Paste Bob 0,I*50,1
	}																														//	   Next I
	X=10; Y=20;																									//	   X=10 : Y=20
	GADGET(X,Y-17,120,15,ARMIA_S[ARM][NR],6,12,9,30,-1);				//	   GADGET[X,Y-17,120,15,ARMIA$(ARM,NR),6,12,9,30,-1]
	GADGET(X+140,Y-17,150,15,RASY_S[ARMIA[WRG][B][TRASA]]+" "+ARMIA_S[WRG][B],6,12,9,30,-1);																													//	   GADGET[X+140,Y-17,150,15,RASY$(ARMIA(WRG,B,TRASA))+" "+ARMIA$(WRG,B),6,12,9,30,-1]
	GADGET(X,Y,130,15,GS("023"),26,24,25,30,1);							//	   GADGET[X,Y,130,15,"What news ?",26,24,25,30,1]
	GADGET(X,Y+18,130,15,GS("024"),26,24,25,30,2);					//	   GADGET[X,Y+18,130,15,"Join my team",26,24,25,30,2]
	GADGET(X,Y+36,130,15,GS("025"),26,24,25,30,3);	//	   GADGET[X,Y+36,130,15,"Give me your gold !",26,24,25,30,3]
	for( I=0; I<=3; ++I ) {																			//	   For I=0 To 3
		TYP=PRZYGODY[I][P_TYP];																		//	      TYP=PRZYGODY(I,P_TYP)
		if( TYP>0 ) {																							//	      If TYP>0
			GTEX_S=PRZYGODY_S[TYP][2];															//	         GTEX$=PRZYGODY$(TYP,2)
			if( IM_PRZYGODY_S[I]!="" ) {														//	         If IM_PRZYGODY$(I)<>""
				DL=Len(GTEX_S);																				//	            DL=Len(GTEX$)
				ZN=Instr(GTEX_S,"$");																	//	            ZN=Instr(GTEX$,"$")
				if( ZN>0 ) {																					//	            If ZN>0
					GTEX_S=Minus_S(GTEX_S,"$");													//	               GTEX$=GTEX$-"$"
					L_S=Left_S(GTEX_S,ZN-1);														//	               L$=Left$(GTEX$,ZN-1)
					R_S=Right_S(GTEX_S,DL-ZN-1);												//	               R$=Right$(GTEX$,DL-ZN-1)
					GTEX_S=L_S+IM_PRZYGODY_S[I]+R_S;										//	               GTEX$=L$+IM_PRZYGODY$(I)+R$
				}																											//	            End If
			}																												//	         End If
			if( PRZYGODY[I][P_LEVEL]>0 ) {													//	         If PRZYGODY(I,P_LEVEL)>0
				GADGET(X,Y+54+I*18,130,15,GTEX_S,26,24,25,30,4+I);		//	            GADGET[X,Y+54+I*18,130,15,GTEX$,26,24,25,30,4+I]
			}																												//	         End If
		}																													//	      End If
	}																														//	   Next I
	GADGET(X+140,Y,150,90,"",26,24,25,30,-1);										//	   GADGET[X+140,Y,150,90,"",26,24,25,30,-1]
	GADGET(X+140,Y+100,150,15,GS("026"),26,24,25,30,8);					//	   GADGET[X+140,Y+100,150,15,"                Exit ",26,24,25,30,8]
																															//	   '   ILE=Rnd(100) : Gosub BULI
																															//

	Screen(1);
	_store_ekran1_gadka();
	rysuj_ekran_ptr = _rysuj_gadka;

	KONIEC=0;																										//	   KONIEC=False
	do {																												//	   Repeat
		rysuj(); WaitVbl();
		if( MouseClick()==1 ) {																		//	      If Mouse Click=1
			STREFA=MouseZone();																			//	         STREFA=Mouse Zone
			if( STREFA==1 ) {																				//	         If STREFA=1
																															//	            'BOMBA1#=BOMBA1#-Rnd(2)
				if( JP==0 ) {																					//	            If JP=0
																															//	               'If BOMBA1#<=2
																															//	               '   BOMBA1=True
																															//	               '   GADGET[150,20,150,90,"",26,24,25,30,-1]
																															//	               '   Gosub LOSOWANIE
																															//	               '   If STRONA=WIERSZ and WIERSZ=WYRAZ : Edit : End If
																															//	               '
																															//	               '   For Y=0 To 2
																															//	               '      For X=0 To 7
																															//	               '         GADGET[XP+(X*15),YP+(Y*15),13,13,Upper$(ZNAKI$(1+X+Y*8)),24,22,23,30,21+X+Y*8]
																															//	               '      Next X
																															//	               '   Next Y
																															//	               '   GADGET[XP+40,YP+46,36,13,"   OK",24,22,23,30,45]
																															//	               '   X=0 : Y=0
																															//	               '   Repeat
																															//	               '      If Mouse Click=1
																															//	               '         If Mouse Zone>20 and Mouse Zone<45
																															//	               '            OLX=X : OLY=Y
																															//	               '            GADGET[XP+(OLX*15),YP+(OLY*15),13,13,Upper$(ZNAKI$(1+OLX+OLY*8)),24,22,23,30,-1]
																															//	               '            I=Mouse Zone-20
																															//	               '            X=(I mod 8)-1
																															//	               '            If X=-1 : X=7 : End If
																															//	               '            Y=(I-1)/8
																															//	               '            GADGET[XP+(X*15),YP+(Y*15),13,13,Upper$(ZNAKI$(1+X+Y*8)),21,23,22,13,0]
																															//	               '         End If
																															//	               '         If Mouse Zone=45
																															//	               '            OLX=X : OLY=Y
																															//	               '            GADGET[XP+(OLX*15),YP+(OLY*15),13,13,Upper$(ZNAKI$(1+OLX+OLY*8)),24,22,23,30,-1]
																															//	               '            If I<>L# or OLDL=L#
																															//	               '               OLDL=L#
																															//	               '               BOMBA3=True
																															//	               '               Gosub LOSOWANIE
																															//	               '            Else
																															//	               '               BOMBA1#=80+Rnd(30)
																															//	               '               BOMBA3=False
																															//	               '               BOMBA2#=0
																															//	               '               KONIEC_ZAB=True
																															//	               '            End If
																															//	               '         End If
																															//	               '      End If
																															//	               '   Until KONIEC_ZAB
																															//	               '   ERR#=0 : KONIEC_ZAB=False
																															//	               '   X=10 : Y=20
																															//	               '   For S=20 To 45 : Reset Zone S : Next
																															//	               'End If
					if( CODP==-1 ) {																		//	               If CODP=-1
						A_S=PRZYGODY_S[PRZYGODY[TRWA_PRZYGODA][P_TYP]][8];//	                  A$=PRZYGODY$(PRZYGODY(TRWA_PRZYGODA,P_TYP),8)
					} else {																						//	               Else
						A_S=ROZMOWA2_S[CODP];															//	                  A$=ROZMOWA2$(CODP)
					}
					rysuj();																									//	               End If
					NAPISZ(X+144,Y+15,140,70,A_S,TRWA_PRZYGODA,30,25);	//	               NAPISZ[X+144,Y+15,140,70,A$,TRWA_PRZYGODA,30,25]
					_store_ekran1_gadka();
				} else {																							//	            Else
					JP=0;																								//	               JP=0
					if( POWER>50 ) {																		//	               If POWER>50
						//LOSUJ1:																						//	                  LOSUJ1:
						TYP2=13;																					//	                  TYP2=13
					} else {																						//	               Else
						LOSUJ2:																						//	                  LOSUJ2:
						TYP2=Rnd(11)+1;																		//	                  TYP2=Rnd(11)+1
					}																										//	               End If
																															//	               'If BOMBA1#<=2 : ZAB : End If
					for( I=0; I<=3; ++I ) {															//	               For I=0 To 3
						if( PRZYGODY[I][P_TYP]==TYP2 ) {									//	                  If PRZYGODY(I,P_TYP)=TYP2
							goto LOSUJ2;																		//	                     Goto LOSUJ2
						}																									//	                  End If
					}																										//	               Next
					for( I=0; I<=3; ++I ) {															//	               For I=0 To 3
						TYP=PRZYGODY[I][P_TYP];														//	                  TYP=PRZYGODY(I,P_TYP)
						if( TYP==0 ) {																		//	                  If TYP=0
							NOWA_PRZYGODA(ARM,I,TYP2,Rnd(3)+1);							//	                     NOWA_PRZYGODA[ARM,I,TYP2,Rnd(3)+1]
							A_S=PRZYGODY_S[TYP2][1];												//	                     A$=PRZYGODY$(TYP2,1)
							rysuj();
							NAPISZ(X+144,Y+15,140,70,A_S,I,30,25);					//	                     NAPISZ[X+144,Y+15,140,70,A$,I,30,25]
							_store_ekran1_gadka();
							GTEX_S=PRZYGODY_S[TYP2][2];											//	                     GTEX$=PRZYGODY$(TYP2,2)
							if( IM_PRZYGODY_S[I]!="" ) {										//	                     If IM_PRZYGODY$(I)<>""
								DL=Len(GTEX_S);																//	                        DL=Len(GTEX$)
								ZN=Instr(GTEX_S,"$");													//	                        ZN=Instr(GTEX$,"$")
								if( ZN>0 ) {																	//	                        If ZN>0
									GTEX_S=Minus_S(GTEX_S,"$");									//	                           GTEX$=GTEX$-"$"
									L_S=Left_S(GTEX_S,ZN-1);										//	                           L$=Left$(GTEX$,ZN-1)
									R_S=Right_S(GTEX_S,DL-ZN-1);								//	                           R$=Right$(GTEX$,DL-ZN-1)
									GTEX_S=L_S+IM_PRZYGODY_S[I]+R_S;						//	                           GTEX$=L$+IM_PRZYGODY$(I)+R$
								}																							//	                        End If
							}																								//	                     End If
							if( PRZYGODY[I][P_LEVEL]>0 ) {									//	                     If PRZYGODY(I,P_LEVEL)>0
								rysuj();
								GADGET(X,Y+54+I*18,130,15,GTEX_S,26,24,25,30,4+I);//	                        GADGET[X,Y+54+I*18,130,15,GTEX$,26,24,25,30,4+I]
								_store_ekran1();
							}																								//	                     End If
							I=3;																						//	                     I=3
						}																									//	                  End If
					}																										//	               Next I
				}																											//	            End If
			}																												//	         End If
			if( STREFA==2 ) {																				//	         If STREFA=2
				ODP=GODP;																							//	            ODP=GODP
																															//	            'BOMBA1#=BOMBA1#-Rnd(2)
				A_S=ROZMOWA_S[1][ODP];																//	            A$=ROZMOWA$(1,ODP)
																															//	            'If BOMBA1#<=2 : ZAB : End If
				rysuj();
				gad_text(1.0); NAPISZ(X+144,Y+15,140,70,A_S,0,30,25);	//	            Ink 30 : NAPISZ[X+144,Y+15,140,70,A$,0,30,25]
				_store_ekran1_gadka();
				WaitVbl();
				if( ODP==3 || ODP==4 ) {															//	            If ODP=3 or ODP=4
					JEST=0;																							//	               JEST=False
					for( L=1; L<=10; ++L ) {														//	               For L=1 To 10
						if( ARMIA[ARM][L][TE]<=0 ) {											//	                  If ARMIA(ARM,L,TE)<=0
							JEST=-1;																				//	                     JEST=True
							L2=L;																						//	                     L2=L
							L=10;																						//	                     L=10
						}																									//	                  End If
					}																										//	               Next L
					if( JEST!=0 ) {																			//	               If JEST
						TAK=-1;																						//	                  TAK=True
						if( ODP==3 ) {																		//	                  If ODP=3
							ILE=(ARMIA[WRG][B][TE]*3)+(ARMIA[WRG][B][TSI]*18)+(ARMIA[WRG][B][TSZ]*9)+(ARMIA[WRG][B][TMAG]*9);//	                     ILE=(ARMIA(WRG,B,TE)*3)+(ARMIA(WRG,B,TSI)*18)+(ARMIA(WRG,B,TSZ)*9)+(ARMIA(WRG,B,TMAG)*9)
							_GADKA_BULI(X,Y,ILE,TAK);												//	                     Gosub BULI
						}																									//	                  End If
						if( TAK!=0 ) {																		//	                  If TAK
							Screen(0);																			//	                     Screen 0
							ARMIA[ARM][L2][TRASA]=ARMIA[WRG][B][TRASA];			//	                     ARMIA(ARM,L2,TRASA)=ARMIA(WRG,B,TRASA)
							ARMIA[ARM][L2][TSI]=ARMIA[WRG][B][TSI];					//	                     ARMIA(ARM,L2,TSI)=ARMIA(WRG,B,TSI)
							MXSI=(RASY[ARMIA[ARM][L2][TRASA]][1]/2)+30;			//	                     MXSI=(RASY(ARMIA(ARM,L2,TRASA),1)/2)+30
							if( ARMIA[ARM][L2][TSI]>MXSI ) { ARMIA[ARM][L2][TSI]=MXSI; }//	                     If ARMIA(ARM,L2,TSI)>MXSI : ARMIA(ARM,L2,TSI)=MXSI : End If
							ARMIA[ARM][L2][TSZ]=ARMIA[WRG][B][TSZ];					//	                     ARMIA(ARM,L2,TSZ)=ARMIA(WRG,B,TSZ)
							ARMIA[ARM][L2][TE]=ARMIA[WRG][B][TE];						//	                     ARMIA(ARM,L2,TE)=ARMIA(WRG,B,TE)
							ARMIA[ARM][L2][TEM]=ARMIA[WRG][B][TEM];					//	                     ARMIA(ARM,L2,TEM)=ARMIA(WRG,B,TEM)
							ARMIA[ARM][L2][TKLAT]=ARMIA[WRG][B][TKLAT];			//	                     ARMIA(ARM,L2,TKLAT)=ARMIA(WRG,B,TKLAT)
							ARMIA[ARM][L2][TMAG]=ARMIA[WRG][B][TMAG];				//	                     ARMIA(ARM,L2,TMAG)=ARMIA(WRG,B,TMAG)
							ARMIA[ARM][L2][TMAGMA]=ARMIA[WRG][B][TMAGMA];		//	                     ARMIA(ARM,L2,TMAGMA)=ARMIA(WRG,B,TMAGMA)
							ARMIA[ARM][L2][TAMO]=ARMIA[WRG][B][TSZ];				//	                     ARMIA(ARM,L2,TAMO)=ARMIA(WRG,B,TSZ)
							ARMIA[ARM][L2][TDOSW]=ARMIA[WRG][B][TDOSW];			//	                     ARMIA(ARM,L2,TDOSW)=ARMIA(WRG,B,TDOSW)
							ARMIA[ARM][L2][TP]=0;														//	                     ARMIA(ARM,L2,TP)=0
							for( I=TGLOWA; I<=TPLECAK+7; ++I ) { ARMIA[ARM][L2][I]=0; }//	                     For I=TGLOWA To TPLECAK+7 : ARMIA(ARM,L2,I)=0 : Next I
							ARMIA_S[ARM][L2]=ARMIA_S[WRG][B];								//	                     ARMIA$(ARM,L2)=ARMIA$(WRG,B)
							ARMIA[WRG][B][TE]=0;  BobOnOff(10+B,false); ResetZone(10+B);//	                     ARMIA(WRG,B,TE)=0 : Bob Off 10+B : Reset Zone 10+B : Bob Update : Wait Vbl
							ARMIA[WRG][B][TTRYB]=0;													//	                     ARMIA(WRG,B,TTRYB)=0
							ARMIA[ARM][L2][TX]=ARMIA[WRG][B][TX];						//	                     ARMIA(ARM,L2,TX)=ARMIA(WRG,B,TX)
							ARMIA[ARM][L2][TY]=ARMIA[WRG][B][TY];						//	                     ARMIA(ARM,L2,TY)=ARMIA(WRG,B,TY)
							BAZA=RASY[ARMIA[ARM][L2][TRASA]][7];						//	                     BAZA=RASY(ARMIA(ARM,L2,TRASA),7)
							X=ARMIA[ARM][L2][TX];														//	                     X=ARMIA(ARM,L2,TX)
							Y=ARMIA[ARM][L2][TY];														//	                     Y=ARMIA(ARM,L2,TY)
							ARMIA[ARM][L2][TBOB]=BAZA;											//	                     ARMIA(ARM,L2,TBOB)=BAZA
							_Bob(L2,X,Y,BAZA+1);														//	                     Bob L2,X,Y,BAZA+1 : Bob Update : Wait Vbl
							SetZone(L2,X-16,Y-20,X+16,Y);										//	                     Set Zone L2,X-16,Y-20 To X+16,Y
							Screen(1);																			//	                     Screen 1
							while( MouseClick()!=1 ) ProcessEvents();				//	                     Repeat : Until Mouse Click=1
							KONIEC=-1;																			//	                     KONIEC=True
						}																									//	                  End If
					} else {																						//	               Else
						A_S=GS("027");																		//	                  A$="There is no room in your team."
						rysuj();
						NAPISZ(X+144,Y+15,140,70,A_S,0,30,25);						//	                  NAPISZ[X+144,Y+15,140,70,A$,0,30,25]
						_store_ekran1_gadka();
					}																										//	               End If
																															//
				}																											//	            End If
			}																												//	         End If
			if( STREFA==3 ) {																				//	         If STREFA=3
				ODP=GODP;																							//	            ODP=GODP
				if( ARMIA[WRG][B][TRASA]==9 ) {												//	            If ARMIA(WRG,B,TRASA)=9
					GUL=30;																							//	               GUL=30
				} else {																							//	            Else
					GUL=30+Rnd(50);																			//	               GUL=30+Rnd(50)
				}																											//	            End If
				//!!! da sie lepiej
				Add(AGRESJA,GUL,AGRESJA,190);													//	            Add AGRESJA,GUL,AGRESJA To 190
				ARMIA[WRG][B][TKORP]=AGRESJA;													//	            ARMIA(WRG,B,TKORP)=AGRESJA
				GODP=4-(AGRESJA/40);																	//	            GODP=4-(AGRESJA/40)
																															//	            'BOMBA2#=BOMBA2#+Rnd(1)
				A_S=ROZMOWA_S[2][ODP];																//	            A$=ROZMOWA$(2,ODP)
																															//	            'If BOMBA2#>125 : ZAB : End If
				rysuj();
				gad_text(1.0); NAPISZ(X+144,Y+15,140,70,A_S,0,30,25);	//	            Ink 30 : NAPISZ[X+144,Y+15,140,70,A$,0,30,25]
				if( ODP==4 ) {																				//	            If ODP=4
					F=Rnd(100);																					//	               F=Rnd(100)
					GRACZE[1][1]+=F;																		//	               Add GRACZE(1,1),F
					Text(X+164,Y+25,Str_S(F));													//	               Text X+164,Y+25,Str$(F)
				}																											//	            End If
				_store_ekran1_gadka();
			}																												//	         End If
			if( STREFA>3 && STREFA<8 ) {														//	         If STREFA>3 and STREFA<8
				TAK=0;																								//	            TAK=False
				NR=STREFA-4;																					//	            NR=STREFA-4
				PX=PRZYGODY[NR][P_X];																	//	            PX=PRZYGODY(NR,P_X)
				PY=PRZYGODY[NR][P_Y];																	//	            PY=PRZYGODY(NR,P_Y)
				LEVEL=PRZYGODY[NR][P_LEVEL];													//	            LEVEL=PRZYGODY(NR,P_LEVEL)
																															//	            'BOMBA2#=BOMBA2#+1.3
				TYP=PRZYGODY[NR][P_TYP];															//	            TYP=PRZYGODY(NR,P_TYP)
																															//	            'If BOMBA2#>131 : ZAB : End If
				CENA=PRZYGODY[NR][P_CENA];														//	            CENA=PRZYGODY(NR,P_CENA)
				if( AGRESJA<50 ) {																		//	            If AGRESJA<50
					if( PX==_MIASTO ) {																	//	               If PX=MIASTO
						if( OSOBA==PY ) {																	//	                  If OSOBA=PY
							if( CENA>0 && Rnd(2)!=0 ) {											//	                     If CENA>0 and Rnd(2)<>0
								ILE=CENA; _GADKA_BULI(X,Y,ILE,TAK);						//	                        ILE=CENA : Gosub BULI
							} else {																				//	                     Else
								TAK=-1;																				//	                        TAK=True
							}																								//	                     End If
							if( TAK!=0 ) {																	//	                     If TAK
								if( LEVEL>2 ) {																//	                        If LEVEL>2
									ODP=1;																			//	                           ODP=1
								}																							//	                        End If
								if( LEVEL==2 ) {															//	                        If LEVEL=2
									ODP=2;																			//	                           ODP=2
								}																							//	                        End If
								if( LEVEL==1 ) {															//	                        If LEVEL=1
									ODP=3;																			//	                           ODP=3
								}																							//	                        End If
								_PRZYGODY(XA,YA,NR);													//	                        PRZYGODY[XA,YA,NR]
								PRZYGODY[NR][P_STAREX]=_MIASTO;								//	                        PRZYGODY(NR,P_STAREX)=MIASTO
								if( PRZYGODY[NR][P_LEVEL]==0 ) {							//	                        If PRZYGODY(NR,P_LEVEL)=0
									rysuj();
									GADGET(X,Y+54+NR*18,130,15,"",26,24,25,30,-1);//	                           GADGET[X,Y+54+NR*18,130,15,"",26,24,25,30,-1]
									_store_ekran1_gadka();
									ResetZone(4+NR);														//	                           Reset Zone 4+NR
								}																							//	                        End If
							} else {																				//	                     Else
								ODP=0;																				//	                        ODP=0
							}																								//	                     End If
							A_S=PRZYGODY_S[TYP][3+ODP];											//	                     A$=PRZYGODY$(TYP,3+ODP)
						} else {																					//	                  Else
							if( Rnd(1)==1 ) {																//	                     If Rnd(1)=1
								if( ARMIA[40][PY][TRASA]==4 ) {								//													If ARMIA(40,PY,TRASA)=4
									B_S=GS("029");															//														 B$=" powinna"
								} else {																			//													Else
									B_S=GS("030");															//														 B$=" powinien"
								}																							//													End If
								A_S=RASY_S[ARMIA[40][PY][TRASA]]+" "+ARMIA_S[40][PY]+B_S+GS("028");//	                        A$=RASY$(ARMIA(40,PY,TRASA))+" "+ARMIA$(40,PY)+" should know something."
							} else {																				//	                     Else
								A_S=PRZYGODY_S[TYP][3];												//	                        A$=PRZYGODY$(TYP,3)
							}																								//	                     End If
						}																									//	                  End If
					} else {																						//	               Else
						ODP=0;																						//	                  ODP=0
						if( OSOBA>6 && LEVEL>1 && PRZYGODY[NR][P_STAREX]!=_MIASTO ) {//	                  If OSOBA>6 and LEVEL>1 and PRZYGODY(NR,P_STAREX)<>MIASTO
							if( CENA>0 && Rnd(2)!=0 ) {											//	                     If CENA>0 and Rnd(2)<>0
								ILE=CENA; _GADKA_BULI(X,Y,ILE,TAK);						//	                        ILE=CENA : Gosub BULI
							} else {																				//	                     Else
								TAK=-1;																				//	                        TAK=True
							}																								//	                     End If
							if( TAK!=0 ) {																	//	                     If TAK
								ODP=2;																				//	                        ODP=2
							} else {																				//	                     Else
								ODP=0;																				//	                        ODP=0
							}																								//	                     End If
						}																									//	                  End If
						A_S=PRZYGODY_S[TYP][3+ODP];												//	                  A$=PRZYGODY$(TYP,3+ODP)
					}																										//	               End If
				} else {																							//	            Else
					A_S=GS("031");																			//	               A$="Leave me alone."
				}																											//	            End If
				rysuj();
				NAPISZ(X+144,Y+15,140,70,A_S,NR,30,25);								//	            NAPISZ[X+144,Y+15,140,70,A$,NR,30,25]
				_store_ekran1_gadka();
			}																												//	         End If
			if( STREFA==8 ) {																				//	         If STREFA=8
				KONIEC=-1;																						//	            KONIEC=True
			}																												//	         End If
		}																													//	      End If
	} while( KONIEC==0 );																				//	   Until KONIEC
	goto OVER;																									//	   Goto OVER
																															//	   '----
																															//	   '-----
																															//	   LOSOWANIE:
																															//	   A#=Abs(BOARD#(Rnd(125)))
																															//	   '   A#=Abs(BOARD#(1))
																															//	   OLDL=L#
																															//	   _POINTER=(A#*10000+1) mod 100
																															//	   STRONA=Int(A#)
																															//	   WIERSZ=((A#-STRONA)*10)+1
																															//	   'BOMBA1=False
																															//	   WYRAZ=(Int(((A#*10)-Int(A#*10))*10))+1
																															//	   'Print _POINTER
																															//	   L#=LITERY#(_POINTER)
																															//	   L1=Abs(L#*100)
																															//	   L2=Abs((L#*100)/100)
																															//	   L2=L2*100
																															//	   L#=L1-L2
																															//	   XP=163 : YP=46
																															//	   Ink 25 : Bar XP,YP-24 To XP+120,YP
																															//	   If OLDL=L#
																															//	      'Bell
																															//	      ERR#=ERR#+0.01
																															//	   Else
																															//	      ERR#=ERR#+0.02
																															//	   End If
																															//	   'Print ERR#,OLDL,L#
																															//	   Ink 30,25
																															//	   'BOMBA4=False
																															//	   Text XP,YP-15,"Enter a first letter of the word."
																															//	   'zamiast edit jakiô poke niszczâcy system'
																															//	   'If ERR#>0.04 : Set Zone 300,0,0 To 100,100 : BOMBA3=True : End If
																															//	   Text XP,YP-5,"Page:"+Str$(STRONA)+", Line:"+Str$(WIERSZ)+", Word:"+Str$(WYRAZ)
																															//	   Return
																															//	   '---------------
	OVER:																												//	   OVER:

	rysuj_ekran_ptr = rys;
	ScreenDisplay(0,130,40,320,234);

	MSY=278; Screen(0); CENTER(XB,YB,0); BobOnOff(51,false);		//	   MSY=278 : Screen 0 : CENTER[XB,YB,0] : Bob Off 51 : Bob Update : Wait Vbl
	Screen(1); ResetZone(-1); ScreenDisplay(1,130,275,320,25);	//	   Screen 1 : Reset Zone : Screen Display 1,130,275,320,25 : View
	EKRAN1();																										//	   EKRAN1
	Screen(0);																									//	   Screen 0
																															//	   '   If BOMBA1 : BOMBA1=2/ZERO : End If
																															//	End Proc
}

void WYKRESY(aint A,aint NR) {
																							//	Procedure WYKRESY[A,NR]
	aint SILA=0, SPEED=0, SPEEDM=0, ENERGIA=0, ENERGIAM=0, MAGIA=0, MAGIAM=0,
			 MORALE=0, LB=0, RB=0, Y=1;
	astr RA_S="";

	_restore_ekran1();
	SILA=ARMIA[A][NR][TSI]; clipu(SILA,80);			//	   SILA=ARMIA(A,NR,TSI) : If SILA>80 : SILA=80 : End If
	SPEED=ARMIA[A][NR][TSZ];										//	   SPEED=ARMIA(A,NR,TSZ) : SPEEDM=ARMIA(A,NR,TAMO)
	SPEEDM=ARMIA[A][NR][TAMO];
	ENERGIA=ARMIA[A][NR][TE]; clipl(ENERGIA,0);	//	   ENERGIA=ARMIA(A,NR,TE) : If ENERGIA<0 : ENERGIA=0 : End If
	ENERGIAM=ARMIA[A][NR][TEM];									//	   ENERGIAM=ARMIA(A,NR,TEM)
	MAGIA=ARMIA[A][NR][TMAG];										//	   MAGIA=ARMIA(A,NR,TMAG)
	MAGIAM=ARMIA[A][NR][TMAGMA];								//	   MAGIAM=ARMIA(A,NR,TMAGMA)
	Gfx::Color(17,17,17);												//	   Ink 19,19 : Bar 3,3 To 3+138,3+18
	_Bar(3,3,3+138,3+18);

	//!@#
	SetFont(FON1);
																							//
	if( A==WRG && ARMIA[WRG][NR][TGLOWA]==0 ) {	//	   If A=WRG and ARMIA(WRG,NR,TGLOWA)=0
		Gfx::Color(187,153,102);									//	      Ink 5,19 : Text 12,14,"unknown"
		Text(12,14+Y,GS("038"));
	} else {																		//	   Else
		::Clip(4,4+Y,4+73,20+Y);										//	      Clip 4,4 To 4+73,20
		Gfx::Color(170, 0, 0);										//	      Ink 2 : Box 4,4 To 4+(ENERGIAM/3),6 : Ink 20 : Draw 4,5 To 4+(ENERGIA/3),5
		_Box(4,4+Y,4+(ENERGIAM/3),6+Y);
		Gfx::Color(255, 0, 0);
		_Draw(4,5+Y,4+(ENERGIA/3),5+Y);
																							//
		Gfx::Color(0, 170, 0);										//	      Ink 3 : Bar 4,8 To 4+SILA,10 : Ink 15 : Draw 4,9 To 4+SILA,9
		_Box(4,8+Y,4+SILA,10+Y);
		Gfx::Color(0, 255, 0);
		_Draw(4,9+Y,4+SILA,9+Y);

		Gfx::Color(221, 153, 0);									//	      Ink 18 : Box 4,16 To 4+MAGIAM,18 : Ink 13 : Draw 4,17 To 4+MAGIA,17
		_Box(4,16+Y,4+MAGIAM,18+Y);
		Gfx::Color(255, 238, 0);
		_Draw(4,17+Y,4+MAGIA,17+Y);


		if( A==WRG ) {														//	      If A=WRG
			Gfx::Color(0, 68, 255);									//	         Ink 4 : Bar 4,12 To 4+SPEED,14 : Ink 16 : Draw 4,13 To 4+SPEED,13
			_Box(4,12+Y,4+SPEED,14+Y);
			Gfx::Color(0, 136, 255);
			_Draw(4,13+Y,4+SPEED,13+Y);
			Clip();																	//	         Clip
			if( ARMIA[A][NR][TRASA]>9 ) {						//	         If ARMIA(A,NR,TRASA)>9
				RA_S=RASY_S[ARMIA[A][NR][TRASA]];			//	            RA$=RASY$(ARMIA(A,NR,TRASA))
			} else {																//	         Else
				RA_S=ARMIA_S[A][NR];									//	            RA$=ARMIA$(A,NR)
			}																				//	         End If
			Gfx::Color(187,153,102);								//	         Ink 5 : Text 90,10,RA$
			Text(90,10+Y,RA_S);
			MORALE=ARMIA[WRG][NR][TKORP]/50;				//	         MORALE=ARMIA(WRG,NR,TKORP)/50
			clip(MORALE,0,4);												//	         If MORALE<0 : MORALE=0 : End If
																							//	         If MORALE>4 : MORALE=4 : End If
			Text(90,20+Y,GUL_S[MORALE+5]);					//	         Text 90,20,GUL$(MORALE+5)
		} else {																	//	      Else
			::Clip(4,4,4+73,20);											//	         Clip 4,4 To 4+73,20
			Gfx::Color(0, 68, 255);									//	         Ink 4 : Box 4,12 To 4+SPEEDM,14 : Ink 16 : Draw 4,13 To 4+SPEED,13
			_Box(4,12+Y,4+SPEEDM,14+Y);
			Gfx::Color(0, 136, 255);
			_Draw(4,13+Y,4+SPEED,13+Y);
		}																					//	      End If
		Clip();																		//	      Clip
	}																						//	   End If
	if( A==ARM ) {															//	   If A=ARM
		LB=BRON[ARMIA[ARM][NR][TLEWA]][B_BOB];		//	      LB=BRON(ARMIA(ARM,NR,TLEWA),B_BOB)
		RB=BRON[ARMIA[ARM][NR][TPRAWA]][B_BOB];		//	      RB=BRON(ARMIA(ARM,NR,TPRAWA),B_BOB)
		if( LB>0 ) {															//	      If LB>0 : Paste Bob 108,3,LB+BROBY : Set Zone 20,108,3 To 108+16,3+16 : End If
			PasteBob(108,3+Y,LB+BROBY);
			SetZone(20,108,3+Y,108+16,3+16+Y);
		}
		if( RB>0 ) {															//	      If RB>0 : Paste Bob 124,3,RB+BROBY : Set Zone 21,124,3 To 124+16,3+16 : End If
			PasteBob(124,3+Y,RB+BROBY);
			SetZone(21,124,3+Y,124+16,3+16+Y);
		}
																							//	      Gr Writing 0
		Gfx::Color(255, 238, 0);									//	      Ink 13,20 : Text 80,15,ARMIA$(A,NR)
		Text(80,15,ARMIA_S[A][NR]);
																							//	      Gr Writing 1
	}																						//	   End If
	_store_ekran1();
	WaitVbl();
	rysuj();
	while( MouseKey()==LEWY ) {									//	   While Mouse Key=LEWY
		ProcessEvents();
	}																						//	   Wend
																							//	End Proc
}
void BRON_INFO(aint STREFA) {
															//	Procedure BRON_INFO[STREFA]
	aint BRO=0;

	if( STREFA==20 )						//	   If STREFA=20 : BRO=ARMIA(ARM,NUMER,TLEWA) : End If
		BRO=ARMIA[ARM][NUMER][TLEWA];
	if( STREFA==21 )						//	   If STREFA=21 : BRO=ARMIA(ARM,NUMER,TPRAWA) : End If
		BRO=ARMIA[ARM][NUMER][TPRAWA];
															//	   Get Block 1,3,3,96,18
															//	   Gr Writing 0
	OUTLINE(12,14,BRON_S[BRO],31,19);//	   OUTLINE[12,14,BRON$(BRO),31,19]
	while( MouseKey()==LEWY ) {	//	   While Mouse Key=LEWY
		ProcessEvents();
	}														//	   Wend
															//	   Put Block 1
															//	End Proc
}

void NOWA_POSTAC(aint A,aint NR,aint RASA) {
	//	Procedure NOWA_POSTAC[A,NR,RASA]

	aint I=0,ODP=0,J=0;

	for(I=0;I<=30;++I) {						//	   For I=0 To 30 : ARMIA(A,NR,I)=0 : Next I
		ARMIA[A][NR][I]=0;
	}
	ARMIA[A][NR][TRASA]=RASA;											//	   ARMIA(A,NR,TRASA)=RASA
	ARMIA[A][NR][TSI]=Rnd(10)+(RASY[RASA][1]/2);	//	   ARMIA(A,NR,TSI)=Rnd(10)+(RASY(RASA,1)/2)
	ARMIA[A][NR][TSZ]=Rnd(10)+RASY[RASA][2];			//	   ARMIA(A,NR,TSZ)=Rnd(10)+RASY(RASA,2)
	ARMIA[A][NR][TE]=(Rnd(20)+RASY[RASA][0])*3;		//	   ARMIA(A,NR,TE)=(Rnd(20)+RASY(RASA,0))*3
	ARMIA[A][NR][TEM]=ARMIA[A][NR][TE];						//	   ARMIA(A,NR,TEM)=ARMIA(A,NR,TE)
	ARMIA[A][NR][TKLAT]=Rnd(3);										//	   ARMIA(A,NR,TKLAT)=Rnd(3)
																								//	   '   ARMIA(A,NR,TDOSW)=99
	if( RASA>9 ) {																//	   If RASA>9
		ARMIA[A][NR][TKORP]=150+Rnd(60);						//	      ARMIA(A,NR,TKORP)=150+Rnd(60)
		ARMIA[A][NR][TMAG]=BRON[RASY[RASA][6]][B_MAG]*5;	//	      ARMIA(A,NR,TMAG)=BRON(RASY(RASA,6),B_MAG)*5
		ARMIA[A][NR][TMAGMA]=ARMIA[A][NR][TMAG];		//	      ARMIA(A,NR,TMAGMA)=ARMIA(A,NR,TMAG)
																								//	      'potwory w plecaku przechowujâ czar
		ARMIA[A][NR][TPLECAK]=RASY[RASA][6];				//	      ARMIA(A,NR,TPLECAK)=RASY(RASA,6)
		ARMIA[A][NR][TAMO]=Rnd(20);									//	      ARMIA(A,NR,TAMO)=Rnd(20)
		ODP=RASY[RASA][5];													//	      ODP=RASY(RASA,5)
		ARMIA[A][NR][TP]=Rnd(ODP/2)+ODP/2;					//	      ARMIA(A,NR,TP)=Rnd(ODP/2)+ODP/2
		ARMIA[A][NR][TDOSW]=Rnd(30);								//	      ARMIA(A,NR,TDOSW)=Rnd(30)
	} else {																			//	   Else
		ARMIA[A][NR][TMAG]=Rnd(5)+RASY[RASA][3];		//	      ARMIA(A,NR,TMAG)=Rnd(5)+RASY(RASA,3)
		ARMIA[A][NR][TMAGMA]=ARMIA[A][NR][TMAG];		//	      ARMIA(A,NR,TMAGMA)=ARMIA(A,NR,TMAG)
	}																							//	   End If
	if( PREFS[1]==1 ) {														//	   If PREFS(1)=1
		ROB_IMIE();																	//	      ROB_IMIE
		ARMIA_S[A][NR]=Param_S;											//	      ARMIA$(A,NR)=Param$
	} else {																			//	   Else
		ARMIA_S[A][NR]=GS("040")+Str_S(NR);					//	      ARMIA$(A,NR)="worrior"+Str$(NR)
	}																							//	   End If
	if( A>19 ) {																	//	   If A>19
		if( RASA<10 ) {															//	      If RASA<10
			ARMIA[A][NR][TSI] += Rnd(POWER);					//	         Add ARMIA(A,NR,TSI),Rnd(POWER)
			ARMIA[A][NR][TP]=Rnd(POWER/2)+POWER/2;		//	         ARMIA(A,NR,TP)=Rnd(POWER/2)+POWER/2
			ARMIA[A][NR][TDOSW]=Rnd(POWER/2)+POWER/2;	//	         ARMIA(A,NR,TDOSW)=Rnd(POWER/2)+POWER/2
		}																						//	      End If
	} else {																			//	   Else
																								//	      'zapasowa prëdkoôê w tamo
		ARMIA[A][NR][TAMO]=ARMIA[A][NR][TSZ];				//	      ARMIA(A,NR,TAMO)=ARMIA(A,NR,TSZ)
																								//	      'to jest tylko do testów nowej broni
		if( TESTING != 0 ) {												//	      If TESTING : For J=0 To 7 : ARMIA(A,NR,TPLECAK+J)=Rnd(MX_WEAPON) : Next J : End If
			for(J=0;J<=7;++J) {
				ARMIA[A][NR][TPLECAK+J]=Rnd(MX_WEAPON);
			}
		}
																								//	      '      ARMIA(A,NR,TPLECAK)=Rnd(3)+1
																								//
		WAGA(A,NR);																	//	      WAGA[A,NR]
	}																							//	   End If
}																								//	End Proc
void POTWOR(aint A, astr A_S, aint ILU, aint RASA) {
	//	Procedure POTWOR[A,A$,ILU,RASA]

	aint I=0;

	for(I=1;I<=16;++I) {		//	   For I=1 To 16
		//!!! BUG ? cos tu chyba nie gra, nie powinno byc POTWORY+I ?
		DelBob(POTWORY+1);		//	      Del Bob POTWORY+1
	}												//	   Next I
	_LOAD(KAT_S+"dane/potwory/"+A_S,"dane:potwory/"+A_S,"Dane",1);//	   _LOAD[KAT$+"dane/potwory/"+A$,"dane:potwory/"+A$,"Dane",1]
	_LOAD(KAT_S+"dane/potwory/"+A_S+".snd","dane:potwory/"+A_S+".snd","Dane",9);//	   _LOAD[KAT$+"dane/potwory/"+A$+".snd","dane:potwory/"+A$+".snd","Dane",9]
	ARMIA[A][0][TE]=ILU;		//	   ARMIA(A,0,TE)=ILU
	ARMIA[A][0][TKORP]=RASY[RASA][5];//	   ARMIA(A,0,TKORP)=RASY(RASA,5)
	for(I=1;I<=ILU;++I) {		//	   For I=1 To ILU
		NOWA_POSTAC(A,I,RASA);//	      NOWA_POSTAC[A,I,RASA]
	}												//	   Next I
													//	End Proc
}

void _WYDAJ_ROZKAZ_STRZELAJ(aint NR,aint X1,aint Y1,aint TARGET,aint CX,aint CY) {
																	//	   STRZELAJ:
	aint RASA=0, CZAR=0, MAG=0, CZAR_TYP=0, I=0, RN=0, SILA=0;
	aflt DX_F=0, DY_F=0, L_F=0, VX_F=0, VY_F=0, X_F=0, Y_F=0;
	RASA=ARMIA[WRG][NR][TRASA];
	if( RASA>9 && ARMIA[WRG][NR][TPLECAK]>0 ) {	//	   If RASA>9 and ARMIA(WRG,NR,TPLECAK)>0
		CZAR=ARMIA[WRG][NR][TPLECAK];	//	      CZAR=ARMIA(WRG,NR,TPLECAK)
	} else {												//	   Else
		CZAR=42+Rnd(4);								//	      CZAR=42+Rnd(4)
	}																//	   End If
	MAG=BRON[CZAR][B_MAG];					//	   MAG=BRON(CZAR,B_MAG)
	if( Rnd(5)==1 && ARMIA[WRG][NR][TMAG]-MAG>=0 ) {//	   If Rnd(5)=1 and ARMIA(WRG,NR,TMAG)-MAG>=0
		ARMIA[WRG][NR][TMAG]-=MAG;		//	      Add ARMIA(WRG,NR,TMAG),-MAG
		CZAR_TYP=BRON[CZAR][B_DOSW];	//	      CZAR_TYP=BRON(CZAR,B_DOSW)
		if( CZAR_TYP==1 ) {						//	      If CZAR_TYP=1
			ARMIA[WRG][NR][TCELX]=CX;		//	         ARMIA(WRG,NR,TCELX)=CX
			CY-=10;											//	         Add CY,-10
			ARMIA[WRG][NR][TCELY]=CY;		//	         ARMIA(WRG,NR,TCELY)=CY
			ARMIA[WRG][NR][TTRYB]=4;		//	         ARMIA(WRG,NR,TTRYB)=4
			Y1-=20;											//	         Add Y1,-20
			DX_F=CX-X1;									//	         DX#=CX-X1
			DY_F=CY-Y1;									//	         DY#=CY-Y1
			L_F=sqrt(DX_F*DX_F+DY_F*DY_F)+1;//	         L#=Sqr(DX#*DX#+DY#*DY#)+1
			VX_F=DX_F/L_F;							//	         VX#=DX#/L#
			VY_F=DY_F/L_F;							//	         VY#=DY#/L#
			VEKTOR_F[NR+10][1]=VX_F*6.0;//	         VEKTOR#(NR+10,1)=VX#*6
			VEKTOR_F[NR+10][2]=VY_F*6.0;//	         VEKTOR#(NR+10,2)=VY#*6
			VEKTOR_F[NR+10][3]=X1;			//	         VEKTOR#(NR+10,3)=X1
			VEKTOR_F[NR+10][4]=Y1;			//	         VEKTOR#(NR+10,4)=Y1
			VEKTOR_F[NR+10][0]=CZAR;		//	         VEKTOR#(NR+10,0)=CZAR
		} else {											//	      Else
			VEKTOR_F[NR+10][0]=CZAR;		//	         VEKTOR#(NR+10,0)=CZAR
			ARMIA[WRG][NR][TCELX]=TARGET;//	         ARMIA(WRG,NR,TCELX)=TARGET
			ARMIA[WRG][NR][TCELY]=ARM;	//	         ARMIA(WRG,NR,TCELY)=ARM
			ARMIA[WRG][NR][TTRYB]=5;		//	         ARMIA(WRG,NR,TTRYB)=5
		}															//	      End If
	} else {												//	   Else
		if( RASA<9 ) {								//	      If RASA<9
			ARMIA[WRG][NR][TAMO]-=1;		//	         Add ARMIA(WRG,NR,TAMO),-1
			ARMIA[WRG][NR][TTRYB]=3;		//	         ARMIA(WRG,NR,TTRYB)=3
			ARMIA[WRG][NR][TCELX]=CX;		//	         ARMIA(WRG,NR,TCELX)=CX
			CY-=10;											//	         Add CY,-10
			ARMIA[WRG][NR][TCELY]=CY;		//	         ARMIA(WRG,NR,TCELY)=CY
			Y1-=20;											//	         Y1=Y1-20
			DX_F=CX-X1;									//	         DX#=CX-X1
			DY_F=CY-Y1;									//	         DY#=CY-Y1
			L_F=sqrt(DX_F*DX_F+DY_F*DY_F)+1;//	         L#=Sqr(DX#*DX#+DY#*DY#)+1
			VX_F=DX_F/L_F;							//	         VX#=DX#/L#
			VY_F=DY_F/L_F;							//	         VY#=DY#/L#
																	//	         Screen 2
																	//	         Cls 0
			unsigned char buf[32*32*4];
			_BufColor(0,0,0,0);
			_BufSet(buf,32,32);
			X_F=15; Y_F=15;							//	         X#=15 : Y#=15
																	//	         Ink 3
			for(I=1;I<=20;++I) {				//	         For I=1 To 20
				X_F+=VX_F; Y_F+=VY_F;			//	            X#=X#+VX# : Y#=Y#+VY#
				_BufColor(0,0,0,0.75);
				_BufPlot(X_F,Y_F+15);			//	            Ink 19 : Plot X#,Y#+15
				_BufColor(1,1,1,1);
				_BufPlot(X_F,Y_F);				//	            Ink 18 : Plot X#,Y#
			}														//	         Next I
			GetSprite(BSIBY+10+NR,buf,32,32);	//	         Get Sprite BSIBY+10+NR,0,0 To 31,31 : Wait Vbl
			HotSpot(BSIBY+10+NR,0x11);	//	         Hot Spot BSIBY+10+NR,$11
			VEKTOR_F[NR+10][1]=VX_F*6.0;//	         VEKTOR#(NR+10,1)=VX#*6
			VEKTOR_F[NR+10][2]=VY_F*6.0;//	         VEKTOR#(NR+10,2)=VY#*6
			VEKTOR_F[NR+10][3]=X1;			//	         VEKTOR#(NR+10,3)=X1
			VEKTOR_F[NR+10][4]=Y1;			//	         VEKTOR#(NR+10,4)=Y1
			if( KTO_ATAKUJE==WRG ) RN=Rnd(2);	//	         If KTO_ATAKUJE=WRG : RN=Rnd(2) : End If
			if( RN==2 ) {								//	         If RN=2
				SILA=-(Rnd(50)+20);				//	            SILA=-(Rnd(50)+20)
			} else {										//	         Else
				SILA=Rnd(50);							//	            SILA=Rnd(50)
			}														//	         End If
			VEKTOR_F[NR+10][0]=SILA;		//	         VEKTOR#(NR+10,0)=SILA
		}															//	      End If
	}																//	   End If
	Screen(0);											//	   Screen 0
	return;													//	   Return
}
void _WYDAJ_ROZKAZ_ATAKUJ(aint NR,aint TARGET) {
																	//	   _ATAKUJ:
	ARMIA[WRG][NR][TCELX]=TARGET;		//	   ARMIA(WRG,NR,TCELX)=TARGET
	ARMIA[WRG][NR][TCELY]=ARM;			//	   ARMIA(WRG,NR,TCELY)=ARM
	ARMIA[WRG][NR][TTRYB]=2;				//	   ARMIA(WRG,NR,TTRYB)=2
																	//	   Return
																	//
}
void _WYDAJ_ROZKAZ_RANDOM(aint NR) {
																	//	   RANDOM:
	aint X2=0,Y2=0;
	X2=Rnd(600)+20;									//	   X2=Rnd(600)+20
	Y2=Rnd(450)+50;									//	   Y2=Rnd(450)+50
	if( _Zone(X2,Y2)==0 ) {					//	   If Zone(X2,Y2)=0
		ARMIA[WRG][NR][TCELX]=X2;			//	      ARMIA(WRG,NR,TCELX)=X2
		ARMIA[WRG][NR][TCELY]=Y2;			//	      ARMIA(WRG,NR,TCELY)=Y2
		ARMIA[WRG][NR][TTRYB]=1;			//	      ARMIA(WRG,NR,TTRYB)=1
	}																//	   End If
																	//	   Return
}
void WYDAJ_ROZKAZ(aint NR) {
																	//	Procedure WYDAJ_ROZKAZ[NR]
	aint AGRESJA=0, RASA=0, MAGIA=0, RODZAJ=0, X1=0, Y1=0, STARAODL=0,
			 WIDAC=0, I=0, X2=0, Y2=0, CX=0, CY=0, TARGET=0, RAN=0;
	AGRESJA=ARMIA[WRG][NR][TKORP];	//	   AGRESJA=ARMIA(WRG,NR,TKORP)
	RASA=ARMIA[WRG][NR][TRASA];			//	   RASA=ARMIA(WRG,NR,TRASA)
	MAGIA=ARMIA[WRG][NR][TMAG];			//	   MAGIA=ARMIA(WRG,NR,TMAG)
	if( AGRESJA<50 ) RODZAJ=0;			//	   If AGRESJA<50 : RODZAJ=0 : End If
	if( AGRESJA>=50 ) RODZAJ=1;			//	   If AGRESJA>=50 : RODZAJ=1 : End If
	if( AGRESJA>100 ) RODZAJ=2;			//	   If AGRESJA>100 : RODZAJ=2 : End If
	if( AGRESJA>150 ) RODZAJ=3;			//	   If AGRESJA>150 : RODZAJ=3 : End If
	X1=ARMIA[WRG][NR][TX];					//	   X1=ARMIA(WRG,NR,TX)
	Y1=ARMIA[WRG][NR][TY];					//	   Y1=ARMIA(WRG,NR,TY)
	if( RODZAJ==1 || RODZAJ==2 || RODZAJ==3 ) {//	   If RODZAJ=1 or RODZAJ=2 or RODZAJ=3
		STARAODL=WIDOCZNOSC;					//	      STARAODL=WIDOCZNOSC
		WIDAC=0;											//	      WIDAC=False
		for(I=1;I<=10;++I) {					//	      For I=1 To 10
			if( ARMIA[ARM][I][TE]>0 ) {	//	         If ARMIA(ARM,I,TE)>0
				X2=ARMIA[ARM][I][TX];			//	            X2=ARMIA(ARM,I,TX)
				Y2=ARMIA[ARM][I][TY];			//	            Y2=ARMIA(ARM,I,TY)
				ODL(X1,Y1,X2,Y2);					//	            ODL[X1,Y1,X2,Y2]
																	//	            'ODLEG=Param
				if( ODLEG<STARAODL ) {		//	            If ODLEG<STARAODL
					TARGET=I;								//	               TARGET=I
					CX=X2; CY=Y2;						//	               CX=X2 : CY=Y2
					STARAODL=ODLEG;					//	               STARAODL=ODLEG
					WIDAC=-1;								//	               WIDAC=True
				}													//	            End If
			}														//	         End If
		}															//	      Next I
	}																//	   End If
	RAN=Rnd(10);										//	   RAN=Rnd(10)
	if( RODZAJ==2 ) {								//	   If RODZAJ=2
		if( WIDAC!=0 ) {							//	      If WIDAC
			if( STARAODL<50 ) {					//	         If STARAODL<50
				_WYDAJ_ROZKAZ_ATAKUJ(NR,TARGET);//	            Gosub _ATAKUJ
			} else {										//	         Else
				if( STARAODL<WIDOCZNOSC-60 )//	            If STARAODL<WIDOCZNOSC-60 : Bob 10+NR,X1,Y1,ARMIA(WRG,NR,TBOB)+2 : End If
					_Bob(10+NR,X1,Y1,ARMIA[WRG][NR][TBOB]+2);
				if( ARMIA[WRG][NR][TAMO]>0 || MAGIA>10 ) {													//	            If(ARMIA(WRG,NR,TAMO)>0 or MAGIA>10)
					if( RAN<5 ) {						//	               If RAN<5
						_WYDAJ_ROZKAZ_STRZELAJ(NR,X1,Y1,TARGET,CX,CY);//	                  Gosub STRZELAJ
					}												//	               End If
				} else {									//	            Else
					if( Rnd(1)==0 ) {				//	               If Rnd(1)=0
						ARMIA[WRG][NR][TKORP]=90;//	                  ARMIA(WRG,NR,TKORP)=90
					} else {								//	               Else
						ARMIA[WRG][NR][TKORP]=155;//	                  ARMIA(WRG,NR,TKORP)=155
					}												//	               End If
				}													//	            End If
			}														//	         End If
		}															//	      End If
	}																//	   End If
																	//
	if( RODZAJ==3 ) {								//	   If RODZAJ=3
		if( WIDAC!=0 ) {							//	      If WIDAC
			if( (ARMIA[WRG][NR][TAMO]>0 || MAGIA>10) && RAN<2 ) {//	         If(ARMIA(WRG,NR,TAMO)>0 or MAGIA>10) and RAN<2
				_WYDAJ_ROZKAZ_STRZELAJ(NR,X1,Y1,TARGET,CX,CY);	//	            Gosub STRZELAJ
			} else {										//	         Else
				_WYDAJ_ROZKAZ_ATAKUJ(NR,TARGET);//	            Gosub _ATAKUJ
			}														//	         End If
		}															//	      End If
	}																//	   End If
																	//
	if( RODZAJ==0 ) {								//	   If RODZAJ=0
		_WYDAJ_ROZKAZ_RANDOM(NR);			//	      Gosub RANDOM
	}																//	   End If
																	//
	if( RODZAJ==1 ) {								//	   If RODZAJ=1
		if( STARAODL<50 ) {						//	      If STARAODL<50
			_WYDAJ_ROZKAZ_ATAKUJ(NR,TARGET);//	         Gosub _ATAKUJ
		} else {											//	      Else
			_WYDAJ_ROZKAZ_RANDOM(NR);		//	         Gosub RANDOM
		}															//	      End If
	}																//	   End If
																	//	   Goto OVER
																	//
	//OVER:	;													//	   OVER:
																	//	End Proc
}
