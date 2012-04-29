
#include "Amos.h"

#include "legion.h"
#include "lgn_akcja.h"
#include "lgn_diskacs.h"
#include "lgn_ekran1.h"
#include "lgn_mapa.h"
#include "lgn_miasto.h"
#include "lgn_przygoda.h"
#include "lgn_sceneria.h"
#include "lgn_util.h"
#include "utl_locale.h"

void _MIASTO_RYSUJ_ROZKAZY(void) {
	OKNO(110,90,90,110);															//	   OKNO[110,90,90,110]
	GADGET(OKX+8,OKY+8, 72,15,GS("102"),8,2,6,31,1);	//	   GADGET[OKX+8,OKY+8,72,15,"Taxes",8,2,6,31,1]
	GADGET(OKX+8,OKY+28,72,15,GS("103"),8,2,6,31,2);	//	   GADGET[OKX+8,OKY+28,72,15,"New Legion",8,2,6,31,2]
	GADGET(OKX+8,OKY+48,72,15,GS("104"),8,2,6,31,3);	//	   GADGET[OKX+8,OKY+48,72,15,"New Buildings",8,2,6,31,3]
	GADGET(OKX+8,OKY+68,72,15,GS("105"),8,2,6,31,4);	//	   GADGET[OKX+8,OKY+68,72,15,"Build Walls",8,2,6,31,4]
	GADGET(OKX+8,OKY+88,72,15,GS("106"),8,2,6,31,5);	//	   GADGET[OKX+8,OKY+88,72,15,"Exit",8,2,6,31,5]
}
void _MIASTO_RYSUJ_INFO(aint NR) {
	aint CZYJE=0, DANE=0, DNI=0, GDX=0, LUDZIE=0,
			 PODATEK=0, MORALE=0, MORALE2=0, _MUR=0, TYP=0, I=0;
	astr RO_S="", D_S="", DN_S="", M_S="", C_S="";

	CZYJE=MIASTA[NR][0][M_CZYJE];								//	   CZYJE=MIASTA(NR,0,M_CZYJE)

	if(CZYJE==1) {															//	   If CZYJE=1
		RO_S=GS("107"); DANE=-1;									//	      RO$="Commands" : DANE=True
	} else {																		//	   Else
		RO_S=GS("108");														//	      RO$="Inquiry"
		if( MIASTA[NR][1][M_Y]>25 ) {							//	      If MIASTA(NR,1,M_Y)>25
			DANE=0; D_S=GS("109");									//	         DANE=False : D$="No informations."
		} else {																	//	      Else
			DNI=MIASTA[NR][1][M_Y];									//	         DNI=MIASTA(NR,1,M_Y)
			if( DNI==1 ) {													//	         If DNI=1 : DN$=" day."
				DN_S=GS("110");
			} else {																//	         Else
				DN_S=GS("111");												//	            DN$=" days."
			}																				//	         End If
			DANE=0;	D_S=GS("112")+Str_S(DNI)+DN_S;	//	         DANE=False : D$="Informations during "+Str$(DNI)+DN$
		}																					//	      End If
		if( MIASTA[NR][1][M_Y]==0 ) {							//	      If MIASTA(NR,1,M_Y)=0
			RO_S="";																//	         RO$=""
			D_S="";																	//	         D$=""
			DANE=-1;																//	         DANE=True
		}																					//	      End If
	}																						//	   End If

	OKNO(80,80,150,100);												//	   OKNO[80,80,150,100]
	GDX=OKX+106;																//	   GDX=OKX+106
	GADGET(OKX+4,OKY+4,142,74,"",31,2,30,1,-1);	//	   GADGET[OKX+4,OKY+4,142,74,"",31,2,30,1,-1]
	if( RO_S!="" ) {														//	   If RO$<>""
		GADGET(OKX+4,OKY+80,50,15,RO_S,8,2,6,31,1);//	      GADGET[OKX+4,OKY+80,50,15,RO$,8,2,6,31,1]
	} else {																		//	   Else
		GDX=OKX+55;																//	      GDX=OKX+55
	}																						//	   End If
	GADGET(GDX,OKY+80,40,15,GS("113"),8,2,6,31,2);//	   GADGET[GDX,OKY+80,40,15,"   Ok  ",8,2,6,31,2]
	LUDZIE=MIASTA[NR][0][M_LUDZIE];							//	   LUDZIE=MIASTA(NR,0,M_LUDZIE)
	PODATEK=MIASTA[NR][0][M_PODATEK];						//	   PODATEK=MIASTA(NR,0,M_PODATEK)
	MORALE=MIASTA[NR][0][M_MORALE];							//	   MORALE=MIASTA(NR,0,M_MORALE)
	MORALE2=MORALE/20;													//	   MORALE2=MORALE/20
	if( MORALE2>4 ) MORALE2=4;									//	   If MORALE2>4 Then MORALE2=4
	_MUR=MIASTA[NR][0][M_MUR];									//	   MUR=MIASTA(NR,0,M_MUR)
	PasteBob(OKX+8,OKY+8,20+_MUR);							//	   Paste Bob OKX+8,OKY+8,20+MUR
	if( LUDZIE>700 ) {													//	   If LUDZIE>700
		M_S=GS("114");														//	      M$="Town   : "
	} else {																		//	   Else
		M_S=GS("115");														//	      M$="Village: "
	}																						//	   End If
	gad_text(1.0);															//	   Ink 1,30 : Text OKX+50,OKY+15,M$+MIASTA$(NR)
	Text(OKX+50,OKY+15,M_S+MIASTA_S[NR]);
	SetZone(3,OKX+85,OKY+5,OKX+145,OKY+16);			//	   Set Zone 3,OKX+85,OKY+5 To OKX+145,OKY+16
	if( DANE!=0 ) {															//	   If DANE
		Text(OKX+50,OKY+25,Str_S(LUDZIE)+GS("116"));//	      Text OKX+50,OKY+25,Str$(LUDZIE)+" inhabitants"
		Text(OKX+50,OKY+35,GS("117")+Str_S(PODATEK));//	      Text OKX+50,OKY+35,"Taxes  : "+Str$(PODATEK)
		Text(OKX+50,OKY+45,GS("118")+GUL_S[MORALE2]);//	      Text OKX+50,OKY+45,"Morale :"+GUL$(MORALE2)
		for( I=2; I<=10; ++I ) {									//	      For I=2 To 10
			TYP=MIASTA[NR][I][M_LUDZIE];						//	         TYP=MIASTA(NR,I,M_LUDZIE)
			if( TYP>3 ) {														//	         If TYP>3 : C$=BUDYNKI$(TYP) : D$=D$-C$ : D$=D$+C$+" " : End If
				C_S=BUDYNKI_S[TYP]; D_S=Minus_S(D_S,C_S); D_S=D_S+C_S+" ";
			}
		}																					//	      Next
		NAPISZ(OKX+8,OKY+57,134,20,D_S,0,1,30);		//	      NAPISZ[OKX+8,OKY+57,134,20,D$,0,1,30]
	} else {																		//	   Else
		Text(OKX+12,OKY+60,D_S);									//	      Text OKX+12,OKY+60,D$
	}																						//	   End If
}
void (*_rysuj_tlo_miasto)(void) = 0;
aint _rysuj_miasto_nr = -1;
void _rysuj_miasto(void) {
	if( _rysuj_tlo_miasto ) _rysuj_tlo_miasto();
	if( _rysuj_miasto_nr>= 0 ) _MIASTO_RYSUJ_INFO(_rysuj_miasto_nr);
}
void MIASTO(aint NR) {
																							//	Procedure MIASTO[NR]
	aint KONIEC=0, KONIEC2=0, KONIEC3=0, CZYJE=0,
			 STREFA=0, STREFA2=0, STREFA3=0;
	astr M_S;

	_rysuj_miasto_nr = NR;

	KONIEC=0; KONIEC2=0; KONIEC3=0;							//	   KONIEC=False : KONIEC2=False : KONIEC3=False
	CZYJE=MIASTA[NR][0][M_CZYJE];								//	   CZYJE=MIASTA(NR,0,M_CZYJE)

	if( PREFS[5]==1 ) {													//	   If PREFS(5)=1 : WJAZD[MIASTA(NR,0,M_X),MIASTA(NR,0,M_Y),80,80,150,100,4] : End If
		WJAZD(MIASTA[NR][0][M_X],MIASTA[NR][0][M_Y],80,80,150,100,4);
	}

	_MIASTO_RYSUJ_INFO(NR);

	void *sb=0, *sb2=0, *sb3=0;
	sb = StoreBuffer(OKX-1,OKY-1,150+2,100+2);
	do {																				//	   Repeat
		rysuj(); RestoreBuffer(sb); WaitVbl();
		if( MouseClick()==1 ) {										//	      If Mouse Click=1
			STREFA=MouseZone();											//	         STREFA=Mouse Zone
			if( STREFA==2 || STREFA==0 ) {					//	         If STREFA=2 or STREFA=0
				KONIEC=-1;														//	            KONIEC=True
				ZOKNO();															//	            ZOKNO
			}																				//	         End If
			if( STREFA==3 ) {												//	         If STREFA=3
				//WPISZ(OKX+84,OKY+15,1,30,12,0);				//	            WPISZ[OKX+84,OKY+15,1,30,12]

				if( MIASTA[NR][0][M_LUDZIE]>700 ) {
					M_S=GS("114");
				} else {
					M_S=GS("115");
				}

				_rysuj_tlo_miasto = rysuj_ekran_ptr;
				rysuj_ekran_ptr = _rysuj_miasto;
				WPISZ_PC(OKX+50+TextLength(M_S),OKY+15-TextBase(),100,10,12,MIASTA_S[NR],2);	//rysuj tylko tlo i kursor
				rysuj_ekran_ptr = _rysuj_tlo_miasto;
				sb = StoreBuffer(OKX-1,OKY-1,150+2,100+2);
				MIASTA_S[NR]=WPI_S;										//	            MIASTA$(NR)=WPI$
			}																				//	         End If
			if( STREFA==1 && CZYJE!=1 ) {						//	         If STREFA=1 and CZYJE<>1
				ZOKNO();															//	            ZOKNO
				KONIEC=-1;														//	            KONIEC=True
				SZPIEGUJ(NR,0);												//	            SZPIEGUJ[NR,0]
			}																				//	         End If
			if( STREFA==1 && CZYJE==1 ) {						//	         If STREFA=1 and CZYJE=1
				ZOKNO();															//	            ZOKNO
				KONIEC=-1;														//	            KONIEC=True
				rysuj();
				_MIASTO_RYSUJ_ROZKAZY();							//	            Gosub RYSUJ_ROZKAZY
				KONIEC2=0;														//	            KONIEC2=False
				sb2 = StoreBuffer(OKX-1,OKY-1,90+2,110+2);
				do {																	//	            Repeat
					rysuj(); RestoreBuffer(sb2); WaitVbl();
					if( MouseClick()==1 ) {							//	               If Mouse Click=1
						STREFA2=MouseZone();							//	                  STREFA2=Mouse Zone
						if( STREFA2==2 ) {								//	                  If STREFA2=2
							ZOKNO();												//	                     ZOKNO
							REKRUTACJA(Rnd(20),NR,-1);			//	                     REKRUTACJA[Rnd(20),NR,-1]
							rysuj();
							_MIASTO_RYSUJ_ROZKAZY();				//	                     Gosub RYSUJ_ROZKAZY
							sb2 = StoreBuffer(OKX-1,OKY-1,90+2,110+2);
						}																	//	                  End If
						if( STREFA2==4 && MIASTA[NR][0][M_MUR]<3 ) {//	                  If STREFA2=4 and MIASTA(NR,0,M_MUR)<3
							ZOKNO();												//	                     ZOKNO
							BUDOWA_MURU(NR);								//	                     BUDOWA_MURU[NR]
							rysuj();
							_MIASTO_RYSUJ_ROZKAZY();				//	                     Gosub RYSUJ_ROZKAZY
							sb2 = StoreBuffer(OKX-1,OKY-1,90+2,110+2);
						}																	//	                  End If
						if( STREFA2==3 ) {								//	                  If STREFA2=3
							ZOKNO();												//	                     ZOKNO
							ROZBUDOWA(NR);									//	                     ROZBUDOWA[NR]
							KONIEC=-1; KONIEC2=-1;					//	                     KONIEC=True : KONIEC2=True
																							//	                     'Gosub RYSUJ_ROZKAZY
						}																	//	                  End If
						if( STREFA2==5 ) {								//	                  If STREFA2=5
							KONIEC2=-1;											//	                     KONIEC2=True
							ZOKNO();												//	                     ZOKNO
						}																	//	                  End If
						if( STREFA2==1 ) {								//	                  If STREFA2=1
							ZOKNO();												//	                     ZOKNO
							rysuj();
							OKNO(90,90,135,70);							//	                     OKNO[90,90,135,70]
							GADGET(OKX+4,OKY+4,100,64,"",31,2,30,1,0);//	                     GADGET[OKX+4,OKY+4,100,64,"",31,2,30,1,0]
							PasteBob(OKX+6,OKY+6,41);				//	                     Paste Bob OKX+6,OKY+6,41
							//!!! inaczej
							//							GADGET(OKX+110,OKY+4,20,15," « ",8,2,6,31,1);//	                     GADGET[OKX+110,OKY+4,20,15," « ",8,2,6,31,1]
							//							GADGET(OKX+110,OKY+24,20,15," » ",8,2,6,31,2);//	                     GADGET[OKX+110,OKY+24,20,15," » ",8,2,6,31,2]
							GADGET(OKX+110,OKY+4,20,15," + ",8,2,6,31,1);//	                     GADGET[OKX+110,OKY+4,20,15," « ",8,2,6,31,1]
							GADGET(OKX+110,OKY+24,20,15," - ",8,2,6,31,2);//	                     GADGET[OKX+110,OKY+24,20,15," » ",8,2,6,31,2]

							GADGET(OKX+110,OKY+52,20,15,GS("OK"),8,2,6,31,3);//	                     GADGET[OKX+110,OKY+52,20,15,"Ok",8,2,6,31,3]
																							//	                     Set Font FON2 : Get Block 120,OKX+6,OKY+6,32,32 : Gr Writing 0
							sb3 = StoreBuffer(OKX-1,OKY-1,135+2,70+2);
																							//	                     Ink 23 : Text OKX+8,OKY+20,Str$(MIASTA(NR,0,M_PODATEK))-" "
							KONIEC3=0;											//	                     KONIEC3=False
							do {														//	                     Repeat
								rysuj(); RestoreBuffer(sb3);
								gad_forsa(1.0);
								Text(OKX+8,OKY+20,Str_S(MIASTA[NR][0][M_PODATEK]));
								WaitVbl();
								if( MouseKey()==LEWY ) {			//	                        If Mouse Key=LEWY
									STREFA3=MouseZone();				//	                           STREFA3=Mouse Zone
									if( STREFA3==1 ) {					//	                           If STREFA3=1
										Add(MIASTA[NR][0][M_PODATEK],1,0,25);//	                              Add MIASTA(NR,0,M_PODATEK),1,0 To 25
																							//	                              Put Block 120 : Text OKX+8,OKY+20,Str$(MIASTA(NR,0,M_PODATEK))-" "
										Wait(5);									//	                              Wait 5
									}														//	                           End If
																							//
									if( STREFA3==2 ) {					//	                           If STREFA3=2
										Add(MIASTA[NR][0][M_PODATEK],-1,0,25);//	                              Add MIASTA(NR,0,M_PODATEK),-1,0 To 25
																							//	                              Put Block 120 : Text OKX+8,OKY+20,Str$(MIASTA(NR,0,M_PODATEK))-" "
										Wait(5);									//	                              Wait 5
									}														//	                           End If
																							//
									if( STREFA3==3 ) {					//	                           If STREFA3=3
										KONIEC3=-1;								//	                              KONIEC3=True
										SetFont(FON1);						//	                              Set Font FON1
										ZOKNO();									//	                              ZOKNO
										rysuj();
										_MIASTO_RYSUJ_ROZKAZY();	//	                              Gosub RYSUJ_ROZKAZY
										sb2 = StoreBuffer(OKX-1,OKY-1,90+2,110+2);
									}														//	                           End If
								}															//	                        End If
																							//
							} while( KONIEC3==0 );					//	                     Until KONIEC3
																							//
						}																	//	                  End If
					}																		//	               End If
				} while( KONIEC2==0 );								//	            Until KONIEC2
			}																				//	         End If
		}																					//	      End If
	} while( KONIEC==0 );												//	   Until KONIEC
	FreeBuffer(sb3);
	FreeBuffer(sb2);
	FreeBuffer(sb);
																							//	   Goto OVER
																							//	   RYSUJ_ROZKAZY:
																							//	   OKNO[110,90,90,110]
																							//	   GADGET[OKX+8,OKY+8,72,15,"Taxes",8,2,6,31,1]
																							//	   GADGET[OKX+8,OKY+28,72,15,"New Legion",8,2,6,31,2]
																							//	   GADGET[OKX+8,OKY+48,72,15,"New Buildings",8,2,6,31,3]
																							//	   GADGET[OKX+8,OKY+68,72,15,"Build Walls",8,2,6,31,4]
																							//	   GADGET[OKX+8,OKY+88,72,15,"Exit",8,2,6,31,5]
																							//	   Return
																							//	   OVER:
																							//	End Proc
}

void ZROB_MIASTA() {
	//	Procedure ZROB_MIASTA

	aint I=0,J=0,X=0,Y=0,LUD=0,CZYJE=0,B1=0,BUD=0
			,SZER=0,SZER2=0,MUR=0,POD=0,MORALE=0,WYS=0,WAHANIA=0;
	for(I=0;I<=49;++I) {		//	   For I=0 To 49
	AGAIN:									//	      AGAIN:
		X=Rnd(590)+20;				//	      X=Rnd(590)+20
		Y=Rnd(460)+20;				//	      Y=Rnd(460)+20
		//	      If Zone(X,Y)=0 and Zone(X+8,Y+8)=0 and Zone(X+4,Y+4)=0
		if( _Zone(X,Y)==0 && _Zone(X+8,Y+8)==0 && _Zone(X+4,Y+4)==0 ) {
			LUD=Rnd(900)+10;			//	         LUD=Rnd(900)+10
			CZYJE=0;							//	         CZYJE=0
			//	         If I=43 or I=44 : CZYJE=2 : End If
			//	         If I=45 or I=46 : CZYJE=3 : End If
			//	         If I=47 or I=48 : CZYJE=4 : End If
			switch(I) {
				case 43: case 44:	CZYJE=2; break;
				case 45: case 46:	CZYJE=3; break;
				case 47: case 48:	CZYJE=4; break;
			}
			if( IMIONA_S[1]=="Lechu" ) {	//	         If IMIONA$(1)="Lechu"
				CZYJE=1;										//	            CZYJE=1
				GRACZE[1][1]=100000;				//	            GRACZE(1,1)=100000
			}															//	         End If
			B1=8+CZYJE*2;									//	         B1=8+CZYJE*2
			if( LUD>700 ) {								//	         If LUD>700
				B1++;												//	            Inc B1
				MUR=Rnd(2)+1;								//	            MUR=Rnd(2)+1
																		//	            '            MIASTA(I,2,M_MUR)=6
			} else {											//	         Else
				MUR=Rnd(1);									//	            MUR=Rnd(1)
																		//	            '            TEREN[X+8,Y+8]
																		//	            '            MIASTA(I,2,M_MUR)=LOK
			}															//	         End If
			POD=Rnd(25);									//	         POD=Rnd(25)
			MORALE=Rnd(100);							//	         MORALE=Rnd(100)
			TEREN(X+4,Y+4);								//	         TEREN[X+4,Y+4]
			if(LOK==7) LOK=1;							//	         If LOK=7 : LOK=1 : End If
			MIASTA[I][1][M_X]=LOK;				//	         MIASTA(I,1,M_X)=LOK
			MIASTA[I][0][M_BOB]=B1;				//	         Paste Bob X,Y,B1
			SetZone(70+I,X-20,Y-20,X+30,Y+30);	//	         Set Zone 70+I,X-20,Y-20 To X+30,Y+30
			MIASTA[I][0][M_X]=X+8;				//	         MIASTA(I,0,M_X)=X+8
			MIASTA[I][0][M_Y]=Y+8;				//	         MIASTA(I,0,M_Y)=Y+8
			MIASTA[I][0][M_LUDZIE]=LUD;		//	         MIASTA(I,0,M_LUDZIE)=LUD
			MIASTA[I][0][M_PODATEK]=POD;	//	         MIASTA(I,0,M_PODATEK)=POD
			MIASTA[I][0][M_MORALE]=MORALE;//	         MIASTA(I,0,M_MORALE)=MORALE
			MIASTA[I][1][M_MORALE]=Rnd(10)+5;//	         MIASTA(I,1,M_MORALE)=Rnd(10)+5
			MIASTA[I][0][M_CZYJE]=CZYJE;	//	         MIASTA(I,0,M_CZYJE)=CZYJE
			MIASTA[I][0][M_MUR]=MUR;			//	         MIASTA(I,0,M_MUR)=MUR
			MIASTA[I][1][M_Y]=30;					//	         MIASTA(I,1,M_Y)=30
			ROB_IMIE();										//	         ROB_IMIE
			MIASTA_S[I]=Param_S;					//	         MIASTA$(I)=Param$
			X=50; Y=50;										//	         X=50 : Y=50
			for(J=2;J<=9;++J)	{						//	         For J=2 To 9
				BUD=Rnd(9);									//	            BUD=Rnd(9)
																		//	            'BUD=8
				SZER=BUDYNKI[BUD][0];				//	            SZER=BUDYNKI(BUD,0) : SZER2=SZER/2
				SZER2=SZER/2;
				WYS=BUDYNKI[BUD][1];				//	            WYS=BUDYNKI(BUD,1)
				X+=Rnd(50);									//	            Add X,Rnd(50)
				if(X>580) {									//	            If X>580 : X=50 : Add Y,130+Rnd(30) : End If
					X=50;
					Y+=130+Rnd(30);
				}
				MIASTA[I][J][M_X]=X;					//	            MIASTA(I,J,M_X)=X
				MIASTA[I][J][M_Y]=Y;					//	            MIASTA(I,J,M_Y)=Y
				MIASTA[I][J][M_LUDZIE]=BUD;		//	            MIASTA(I,J,M_LUDZIE)=BUD
				X+=SZER;											//	            Add X,SZER
																			//	            'za co nieúle zapîaci
				MIASTA[I][J][M_PODATEK]=Rnd(18)+1;	//	            MIASTA(I,J,M_PODATEK)=Rnd(18)+1
			}																//	         Next J
			//	         'modyfikatory cenowe w %
			if( CZYJE==1 ) {								//	         If CZYJE=1
				WAHANIA=20;										//	            WAHANIA=20
			} else {												//	         Else
				WAHANIA=50;										//	            WAHANIA=50
			}																//	         End If
			for(J=1;J<=19;++J) {						//	         For J=1 To 19
				MIASTA[I][J][M_MUR]=Rnd(WAHANIA);	//	            MIASTA(I,J,M_MUR)=Rnd(WAHANIA)
			}																//	         Next J
		} else {													//	      Else
			goto AGAIN;											//	         Goto AGAIN
		}																	//	      End If
	}																		//	   Next I
	for(I=0;I<=49;++I) {								//	   For I=0 To 49
		X=MIASTA[I][0][M_X]-8;						//	      X=MIASTA(I,0,M_X)-8
		Y=MIASTA[I][0][M_Y]-8;						//	      Y=MIASTA(I,0,M_Y)-8
		SetZone(70+I,X,Y,X+16,Y+16);			//	      Set Zone 70+I,X,Y To X+16,Y+16
	}																		//	   Next I
																			//	   '   For I=0 To 3
																			//	   '   NOWA_PRZYGODA[0,I,I+1,0]
																			//	   '      PRZYGODY(I,P_LEVEL)=0
																			//
																			//	   '      PRZYGODY(I,P_X)=200+I*20
																			//	   '      PRZYGODY(I,P_Y)=200+I*20
																			//
																			//	   '      PRZYGODY(I,P_X)=Rnd(600)+20
																			//	   '      PRZYGODY(I,P_Y)=Rnd(490)+20
																			//	   '   Next I
																			//
																			//
																			//	End Proc
}

void BUDOWA_MURU(aint MIASTO) {
																								//	Procedure BUDOWA_MURU[MIASTO]
	aint MUR=0, STREFA=0, KONIEC=0;
	rysuj();
	OKNO(110,100,80,84);													//	   OKNO[110,100,80,84]
	MUR=MIASTA[MIASTO][0][M_MUR];									//	   MUR=MIASTA(MIASTO,0,M_MUR)
	GADGET(OKX+4,OKY+44,72,15,GS("163"),8,1,6,31,3);//	   GADGET[OKX+4,OKY+44,72,15,"Granite",8,1,6,31,3]
	gad_forsa(1.0);
	Text(OKX+52,OKY+54,"10000");									//	   Ink 23,6 : Text OKX+52,OKY+54,"10000"
	if(MUR<2) {																		//	   If MUR<2
		GADGET(OKX+4,OKY+24,72,15,GS("164"),8,1,6,31,2);//	      GADGET[OKX+4,OKY+24,72,15,"Stone ",8,1,6,31,2]
		gad_forsa(1.0);
		Text(OKX+52,OKY+34,"7000");									//	      Ink 23,6 : Text OKX+52,OKY+34,"7000"
	}																							//	   End If
	if(MUR<1) {																		//	   If MUR<1
		GADGET(OKX+4,OKY+4,72,15,GS("165"),8,1,6,31,1);//	      GADGET[OKX+4,OKY+4,72,15,"Palisade ",8,1,6,31,1]
		gad_forsa(1.0);
		Text(OKX+52,OKY+14,"4000");									//	      Ink 23,6 : Text OKX+52,OKY+14,"4000"
	}																							//	   End If
	GADGET(OKX+4,OKY+64,72,15,GS("166"),8,1,6,31,10);//	   GADGET[OKX+4,OKY+64,72,15,"       Exit",8,1,6,31,10]
	WaitVbl();
	do {																					//	   Repeat
		ProcessEvents();
		if( MouseClick()==1 ) {											//	      If Mouse Click=1
			STREFA=MouseZone();												//	         STREFA=Mouse Zone
			if( STREFA==10 ) {												//	         If STREFA=10
				KONIEC=-1;															//	            KONIEC=True
			}																					//	         End If
			if( STREFA>0 && STREFA<4 &&	GRACZE[1][1]-(4000+(STREFA-1)*3000)>=0 ) {//	         If STREFA>0 and STREFA<4 and GRACZE(1,1)-(4000+(STREFA-1)*3000)>=0
				KONIEC=-1;															//	            KONIEC=True
				GRACZE[1][1]-=(4000+(STREFA-1)*3000);		//	            Add GRACZE(1,1),-(4000+(STREFA-1)*3000)
				MIASTA[MIASTO][0][M_MUR]=STREFA;				//	            MIASTA(MIASTO,0,M_MUR)=STREFA
			}																					//	         End If
		}																						//	      End If
	} while( KONIEC==0 );																							//	   Until KONIEC
	ZOKNO();																			//	   ZOKNO
																								//	End Proc
}

aint _ROZBUDOWA_CHECK(aint X,aint Y,aint SZER,aint WYS,aint SZER2,aint WYS2) {
	aint MOZNA=0;																//	   MOZNA=False
	if( X>0 && X+SZER<640 && Y>0 && Y+WYS<512 ) {//	   If X>0 and X+SZER<640 and Y>0 and Y+WYS<512
		if( _Zone(X,Y)==0 && _Zone(X+SZER,Y)==0 && _Zone(X,Y+WYS)==0 && _Zone(X+SZER,Y+WYS)==0 && _Zone(X+SZER2,Y+WYS2)==0 ) {//	      If Zone(X,Y)=0 and Zone(X+SZER,Y)=0 and Zone(X,Y+WYS)=0 and Zone(X+SZER,Y+WYS)=0 and Zone(X+SZER2,Y+WYS2)=0
			MOZNA=-1;																//	         MOZNA=True
		}																					//	      End If
	}																						//	   End If
	return MOZNA;																//	   Return
}
void _ROZBUDOWA_WYPISZ(astr A_S,aint CENA) {
//!!!	gad_back(1.0); _Bar(167,3,167+105,3+28);		//	   Ink 22 : Bar 167,3 To 167+105,3+28
//!!!	gad_text(1.0); Text(172,15,A_S);						//	   Ink 1,22 : Text 172,15,A$
//!!!	Text(172,25,GS("167")+Str_S(CENA));					//	   Text 172,25,"cost :"+Str$(CENA)
	gad_back(1.0); _Bar(177,3,177+95,3+28);		//	   Ink 22 : Bar 167,3 To 167+105,3+28
	gad_text(1.0); Text(182,15,A_S);						//	   Ink 1,22 : Text 172,15,A$
	Text(182,25,GS("167")+Str_S(CENA));					//	   Text 172,25,"cost :"+Str$(CENA)
																							//	   '   Text 167,30,"budowa:"+Str$(CZAS)+" dni"
	//SetFont(FON2);															//	   Set Font FON2 : Text 210,12,Str$(GRACZE(1,1)) : Set Font FON1
	Text(240,15,Str_S(GRACZE[1][1]));
	SetFont(FON1);

	return;																			//	   Return
}
void _rysuj_rozbudowa(void) {
	aint s = Screen();

	//ekran mruga na niektorych kartach graficznych, wiec czyscimy to co nie bedzie rysowane
	Gfx::Color(0.f,0.f,0.f);
	Screen(1);
	_ClearRaster(0,ScreenY()-5,640,525);

	rysuj_scenerie();
	Screen(1);
	_restore_ekran1();
	Screen(s);
}
void ROZBUDOWA(aint MIASTO) {
																							//	Procedure ROZBUDOWA[MIASTO]
	aint _TEREN=0, I=0, HY=0, STREFA=0, SZER=0, SZER2=0, WYS=0, WYS2=0, CENA=0, CZAS=0,
			 B1=0, TYP=0, KONIEC=0, KLAW=0, X=0, Y=0, MOZNA=0, RAMKA=0, PREV_STREFA=0;
	astr MIA_S="", BB_S="", A_S="", B_S="";

	MIA_S=MIASTA_S[MIASTO];											//	   MIA$=MIASTA$(MIASTO)
	_TEREN=MIASTA[MIASTO][1][M_X];								//	   TEREN=MIASTA(MIASTO,1,M_X)
	if( PREFS[3]==1 ) _TRACK_FADE(1);						//	   If PREFS(3)=1 : _TRACK_FADE[1] : End If
	SpriteOnOff(2,false);												//	   Sprite Off 2
																							//	   '----
																							//	   Show On
	EraseAll();																	//	   Erase All
	ScreenOpen(2,80,50,32,LOWRES); ScreenDisplay(2,252,140,80,50); Gfx::Cls(0,0,0);	//	   Screen Open 2,80,50,32,Lowres : Curs Off : Flash Off : Screen Display 2,252,140,80,50 : Cls 0 : Screen Hide 2
	ScreenOpen(0,640,512,32,LOWRES); ScreenDisplay(0,130,40,320,234);//	   Screen Open 0,640,512,32,Lowres : Screen Display 0,130,40,320,234
																							//	   Curs Off : Flash Off : Cls 0 : Screen Hide
	ReserveZone(200);														//	   Reserve Zone 200
																							//	   '------------------
	ScreenOpen(1,320,160,32,LOWRES); ScreenDisplay(1,130,265,320,35);//	   Screen Open 1,320,160,32,Lowres : Screen Display 1,130,265,320,35
																							//	   Curs Off : Flash Off : Cls 10 : Screen Hide
	ReserveZone(30);														//	   Reserve Zone 30
	_LOAD(KAT_S+"dane/gad","dane:gad","Dane",0);//	   _LOAD[KAT$+"dane/gad","dane:gad","Dane",0] : Get Bob Palette
	_LOAD(KAT_S+"dane/gad3","dane:gad3","Dane",1);//	   _LOAD[KAT$+"dane/gad3","dane:gad3","Dane",1]
	USTAW_FONT("defender2",FONT_DEFENDER,12,1);	//	   USTAW_FONT["defender2",8]
	FON1=FONR;
	ChangeMouse(53);														//	   Change Mouse 53
	PasteBob(0,0,1);														//	   Paste Bob 0,0,1
	gad_shadow(1.0); Text(8,10,Upper_S(MIA_S));		//	   Gr Writing 0 : Ink 21 : Text 8,10,Upper$(MIA$)
	gad_text(1.0); Text(7,9,Upper_S(MIA_S));	//	   Ink 1 : Text 7,9,Upper$(MIA$)
	for(I=0;I<=5;++I) {													//	   For I=0 To 5
		BB_S=Minus_S("bob"+Str_S(51+I)," ");			//	      BB$="bob"+Str$(51+I)-" "
		GADGET(4+I*24,12,20,20,BB_S,5,12,9,1,I+1);//	      GADGET[4+I*24,12,20,20,BB$,5,12,9,1,I+1]
	}																						//	   Next I

		GADGET(4+I*24,12,20,20,"bu¿",5,12,9,1,I+1);	//buzenie

//!!!	GADGET(165,2,110,30,"",0,5,22,1,-1);				//	   GADGET[165,2,110,30,"",0,5,22,1,-1]
	GADGET(175,2,100,30,"",0,5,22,1,-1);				//	   GADGET[165,2,110,30,"",0,5,22,1,-1]

	GADGET(280,6,30,20,GS("168"),7,0,11,1,10);		//	   GADGET[280,6,30,20," exit",7,0,11,1,10]
																							//	   '------------------

	_store_ekran1_rozbudowa();
	rysuj_ekran_ptr = _rysuj_rozbudowa;

	Screen(0);																	//	   Screen 0
	USTAW_FONT("defender2",FONT_DEFENDER,8,1);	//	   USTAW_FONT["defender2",8]
	BIBY=62;																		//	   BIBY=62
	MSX=320; MSY=278;														//	   MSX=320 : MSY=278
																							//	   '-----
	RYSUJ_SCENERIE(_TEREN,MIASTO);							//	   RYSUJ_SCENERIE[TEREN,MIASTO]
																							//	   Screen Show 0 : Screen Show 1
																							//	   View
	TrackStop();																//	   Track Stop
	Screen(1);																	//	   Screen 1
	SetFont(FON1);
	do {																				//	   Repeat
		rysuj();
		HY=YMouse();															//	      HY=Y Mouse
		if( HY>263 ) {														//	      If HY>263
			Screen(1);															//	         Screen 1
			if( MouseClick()==1 ) {									//	         If Mouse Click=1
				STREFA=MouseZone();										//	            STREFA=Mouse Zone
				if( STREFA>0 and STREFA<8 ) {					//	            If STREFA>0 and STREFA<8
					I=STREFA+3;													//	               I=STREFA+3
					if( STREFA == 7 ) {
						//buzenie
						GADGET(4+(STREFA-1)*24,12,20,20,"BU¯",12,5,11,1,0);	//	               GADGET[4+(STREFA-1)*24,12,20,20,BB$,12,5,11,1,0]
						SZER=16;
						WYS=16;
						CENA=1500;
						CZAS=1;
						B1=-1;
						A_S="Wybu¿enie";
						TYP=I;
					} else {
						BB_S=Minus_S("bob"+Str_S(56+STREFA)," ");//	               BB$="bob"+Str$(56+STREFA)-" "
						GADGET(4+(STREFA-1)*24,12,20,20,BB_S,12,5,11,1,0);	//	               GADGET[4+(STREFA-1)*24,12,20,20,BB$,12,5,11,1,0]
						SZER=BUDYNKI[I][0]; SZER2=SZER/2;		//	               SZER=BUDYNKI(I,0) : SZER2=SZER/2
						WYS=BUDYNKI[I][1]; WYS2=WYS/2;			//	               WYS=BUDYNKI(I,1) : WYS2=WYS/2
						CENA=BUDYNKI[I][2];									//	               CENA=BUDYNKI(I,2)
						CZAS=BUDYNKI[I][3];									//	               CZAS=BUDYNKI(I,3)
						B1=BUDYNKI[I][4];										//	               B1=BUDYNKI(I,4)
						A_S=BUDYNKI_S[I];										//	               A$=BUDYNKI$(I)
						TYP=I;															//	               TYP=I
					}
					_ROZBUDOWA_WYPISZ(A_S,CENA);				//	               Gosub WYPISZ
					if( PREV_STREFA>0 && PREV_STREFA != STREFA) {
						if( PREV_STREFA==7 ) {
							GADGET(4+(PREV_STREFA-1)*24,12,20,20,"bu¿",5,12,9,1,-1);
						} else {
							BB_S=Minus_S("bob"+Str_S(50+PREV_STREFA)," ");	//	               BB$="bob"+Str$(50+STREFA)-" "
							GADGET(4+(PREV_STREFA-1)*24,12,20,20,BB_S,5,12,9,1,-1);//	               GADGET[4+(STREFA-1)*24,12,20,20,BB$,5,12,9,1,-1]
						}
					}
					PREV_STREFA=STREFA;
					_store_ekran1_rozbudowa();
				}																			//	            End If
				if( STREFA==10 ) {										//	            If STREFA=10
					GADGET(280,6,30,20,GS("168"),0,7,12,1,0);//	               GADGET[280,6,30,20," exit",0,7,12,1,0]
					KONIEC=-1;													//	               KONIEC=True
					GADGET(280,6,30,20,GS("168"),7,0,11,1,0);//	               GADGET[280,6,30,20," exit",7,0,11,1,0]
				}																			//	            End If
			}																				//	         End If
		} else {																	//	      Else
			HY=YMouse();														//	         HY=Y Mouse
			Screen(0);															//	         Screen 0
			B_S=Inkey_S();													//	         B$=Inkey$
			KLAW=ScanCode();												//	         KLAW=Scancode
			if( MouseKey()==PRAWY ) SKROL(0);				//	         If Mouse Key=PRAWY : SKROL[0] : End If
			if( KLAW>75 && KLAW<80 ) {							//	         If KLAW>75 and KLAW<80
				KLAWSKROL(KLAW);											//	            KLAWSKROL[KLAW]
			}																				//	         End If
			if( SZER>0 ) {													//	         If SZER>0
																							//	            Gr Writing 3
				X=XScreen(XMouse())-SZER2;						//	            X=X Screen(X Mouse)-SZER2
				Y=YScreen(YMouse())-WYS2;							//	            Y=Y Screen(Y Mouse)-WYS2
				PasteBob( X+47,Y+130,BIBY+12+B1 );
				if( RAMKA==0 ) {
					RAMKA=1;
					Gfx::Color(0,0,0);
					_Box(X,Y,X+SZER,Y+WYS);								//	            Box X,Y To X+SZER,Y+WYS : Wait Vbl
				} else {
					RAMKA=0;
					Gfx::Color(1.f,1.f,1.f);
					_Box(X,Y,X+SZER,Y+WYS);								//	            Box X,Y To X+SZER,Y+WYS
				}
			}																				//	         End If
			if( MouseClick()==1 && SZER>0 && GRACZE[1][1]-CENA>=0 ) {//	         If Mouse Click=1 and SZER>0 and GRACZE(1,1)-CENA>=0
				MOZNA=_ROZBUDOWA_CHECK(X,Y,SZER,WYS,SZER2,WYS2);//	            Gosub CHECK
				for(I=2;I<=20;++I) {									//	            For I=2 To 20
					if( MIASTA[MIASTO][I][M_LUDZIE]==0 && MOZNA!=0 ) {//	               If MIASTA(MIASTO,I,M_LUDZIE)=0 and MOZNA
						PBListOnoff(true);//dodajemy do listy rysowania
//!!!						PasteBob( X,Y,BIBY+12+B1 );				//	                  Paste Bob X,Y,BIBY+12+B1
						PasteBob( X+47,Y+130,BIBY+12+B1 );				//	                  Paste Bob X,Y,BIBY+12+B1
						PBListOnoff(false);
						MIASTA[MIASTO][I][M_X]=X;					//	                  MIASTA(MIASTO,I,M_X)=X
						MIASTA[MIASTO][I][M_Y]=Y;					//	                  MIASTA(MIASTO,I,M_Y)=Y
						MIASTA[MIASTO][I][M_LUDZIE]=TYP;	//	                  MIASTA(MIASTO,I,M_LUDZIE)=TYP
						MIASTA[MIASTO][1][M_MORALE]+=2;		//	                  Add MIASTA(MIASTO,1,M_MORALE),2
						MIASTA[MIASTO][0][M_MORALE]+=20;	//	                  Add MIASTA(MIASTO,0,M_MORALE),20
						SetZone(120+I,X,Y,X+SZER,Y+WYS);	//	                  Set Zone 120+I,X,Y To X+SZER,Y+WYS
						GRACZE[1][1]-=CENA;								//	                  Add GRACZE(1,1),-CENA
						Screen(1); _ROZBUDOWA_WYPISZ(A_S,CENA);
						_store_ekran1_rozbudowa();
						Screen(0);//	                  Screen 1 : Gosub WYPISZ : Screen 0
						break;														//	                  Exit
					}																		//	               End If
				}																			//	            Next I
			}																				//	         End If
		}																					//	      End If
		WaitVbl();
	} while( KONIEC==0 );												//	   Until KONIEC
	goto OVER;																	//	   Goto OVER
																							//	   '-----------
																							//	   CHECK:
																							//	   MOZNA=False
																							//	   If X>0 and X+SZER<640 and Y>0 and Y+WYS<512
																							//	      If Zone(X,Y)=0 and Zone(X+SZER,Y)=0 and Zone(X,Y+WYS)=0 and Zone(X+SZER,Y+WYS)=0 and Zone(X+SZER2,Y+WYS2)=0
																							//	         MOZNA=True
																							//	      End If
																							//	   End If
																							//	   Return
																							//	   '----------
																							//	   WYPISZ:
																							//	   Ink 22 : Bar 167,3 To 167+105,3+28
																							//	   Ink 1,22 : Text 172,15,A$
																							//	   Text 172,25,"cost :"+Str$(CENA)
																							//	   '   Text 167,30,"budowa:"+Str$(CZAS)+" dni"
																							//	   Set Font FON2 : Text 210,12,Str$(GRACZE(1,1)) : Set Font FON1
																							//
																							//	   Return
																							//	   '----------
	OVER:																				//	   OVER:
	EraseAll();																	//	   Erase All
	ScreenClose(2);															//	   Screen Close 2
	ScreenClose(1);															//	   Screen Close 1
	ScreenClose(0);															//	   Screen Close 0
	SETUP0();																		//	   SETUP0
	VISUAL_OBJECTS();														//	   VISUAL_OBJECTS
	Sprite(2,SPX,SPY,1);												//	   Sprite 2,SPX,SPY,1
	CENTER(MIASTA[MIASTO][0][M_X],MIASTA[MIASTO][0][M_Y],0);//	   CENTER[MIASTA(MIASTO,0,M_X),MIASTA(MIASTO,0,M_Y),0]
																							//	End Proc
}

void _REKRUTACJA_RYSUJ(aint &A, aint &A1,aint &A2, aint &JEST,aint *REKRUCI, aint MIASTO) {
  astr A_S="";
  aint I=0;

	A2=A;																																				//	   A2=A
	JEST=-1;																																		//	   JEST=True
	rysuj();
	OKNO(70,30,162,210);																												//	   OKNO[70,30,162,210]
	A_S=GS("154")+MIASTA_S[MIASTO]+GS("155");																		//	   A$="Recruits of "+MIASTA$(MIASTO)
	GADGET(OKX+4,OKY+4,154,15,A_S,31,2,30,1,-1);																//	   GADGET[OKX+4,OKY+4,154,15,A$,31,2,30,1,-1]
	if( A1==-1 ) {																															//	   If A1=-1
		A_S=GS("156")+Str_S(A+1);																									//	      A$="Legion "+Str$(A+1)
	} else {																																		//	   Else
		A_S=ARMIA_S[A][0];																												//	      A$=ARMIA$(A,0)
	}																																						//	   End If
	GADGET(OKX+4,OKY+22,70,13,A_S,7,0,4,31,11);																	//	   GADGET[OKX+4,OKY+22,70,13,A$,7,0,4,31,11]
	ARMIA_S[A2][0]=A_S;																													//	   ARMIA$(A2,0)=A$
	GADGET(OKX+77,OKY+22,70,13,GS("157"),7,0,4,31,-1);									//	   GADGET[OKX+77,OKY+22,70,13,"En  St  Sp  Mag",7,0,4,31,-1]
	GADGET(OKX+4,OKY+192,45,15,GS("158"),7,0,4,31,12);													//	   GADGET[OKX+4,OKY+192,45,15," Cancel",7,0,4,31,12]
	GADGET(OKX+113,OKY+192,45,15,GS("159"),7,0,4,31,13);													//	   GADGET[OKX+113,OKY+192,45,15,"   Ok",7,0,4,31,13]
	GADGET(OKX+55,OKY+192,50,15,"",8,1,6,31,-1);																//	   GADGET[OKX+55,OKY+192,50,15,"",8,1,6,31,-1]
	for( I=1; I<=10; ++I ) {																										//	   For I=1 To 10
		if( (A1>-1 && ARMIA[A][I][TE]<=0) || A1==-1 ) {														//	      If A1>-1 and ARMIA(A,I,TE)<=0 or A1=-1
			REKRUCI[I]=1;																														//	         REKRUCI(I)=1
			NOWA_POSTAC(A,I,Rnd(8));																								//	         NOWA_POSTAC[A,I,Rnd(8)]
			ARMIA[A][I][TE]=0;																											//	         ARMIA(A,I,TE)=0
			A_S=ARMIA_S[A][I]+" "+RASY_S[ARMIA[A][I][TRASA]];												//	         A$=ARMIA$(A,I)+" "+RASY$(ARMIA(A,I,TRASA))
			GADGET(OKX+4,OKY+24+I*15,138,13,A_S,8,1,6,31,-1);												//	         GADGET[OKX+4,OKY+24+I*15,138,13,A$,8,1,6,31,-1]
			GADGET(OKX+144,OKY+24+I*15,15,13,"",7,0,4,31,I);												//	         GADGET[OKX+144,OKY+24+I*15,15,13,"",7,0,4,31,I]
			gad_forsa(1.0);
			Text(OKX+77,OKY+34+I*15,Str_S(ARMIA[A][I][TEM]));												//	         Ink 23,6 : Text OKX+77,OKY+34+I*15,Str$(ARMIA(A,I,TEM))
			Text(OKX+95,OKY+34+I*15,Str_S(ARMIA[A][I][TSI]));												//	         Text OKX+95,OKY+34+I*15,Str$(ARMIA(A,I,TSI))
			Text(OKX+110,OKY+34+I*15,Str_S(ARMIA[A][I][TSZ]));											//	         Text OKX+110,OKY+34+I*15,Str$(ARMIA(A,I,TSZ))
			Text(OKX+125,OKY+34+I*15,Str_S(ARMIA[A][I][TMAG]));											//	         Text OKX+125,OKY+34+I*15,Str$(ARMIA(A,I,TMAG))
		}																																					//	      End If
	}																																						//	   Next I
	return;																																			//	   Return
}
void *_rekrutacja_buf = 0;
void (*_rysuj_tlo_rekrutacja)(void) = 0;
void _rekrutacja_rysuj(void) {
	if( _rysuj_tlo_rekrutacja ) _rysuj_tlo_rekrutacja();
	if( _rekrutacja_buf ) RestoreBuffer(_rekrutacja_buf);
}
void REKRUTACJA(aint ILU,aint MIASTO,aint A1) {
																																							//	Procedure REKRUTACJA[ILU,MIASTO,A1]
  aint JEST=0, KONIEC=0, CENA=0, A=0, A2=0, STREFA=0, I=0, WOJ=0, XA=0, YA=0, DNI=0;

	aint REKRUCI[10+1];																													//	   Dim REKRUCI(10)
	JEST=0;																																			//	   JEST=False
	KONIEC=0;																																		//	   KONIEC=False
	CENA=0;																																			//	   CENA=0
	ILU=0;																																			//	   ILU=0
																																							//
	if( MIASTA[MIASTO][1][M_PODATEK]==0 ) {																			//	   If MIASTA(MIASTO,1,M_PODATEK)=0
		if( A1==-1 ) {																														//	      If A1=-1
			for( A=0; A<=19; ++A ) {																								//	         For A=0 To 19
				if( ARMIA[A][0][TE]==0 ) {																						//	            If ARMIA(A,0,TE)=0
					_REKRUTACJA_RYSUJ(A,A1,A2,JEST,REKRUCI,MIASTO);											//	               Gosub RYSUJ
					break;																															//	               Exit
				}																																			//	            End If
			}																																				//	         Next A
		} else {																																	//	      Els
			A=A1;																																		//	         A=A1
			_REKRUTACJA_RYSUJ(A,A1,A2,JEST,REKRUCI,MIASTO);													//	         Gosub RYSUJ
		}																																					//	      End If
																																							//
		void *sb=StoreBuffer(OKX-1,OKY-1,162+2,210+2);
		if( JEST!=0 ) {																														//	      If JEST
			do {																																		//	         Repeat
				rysuj();
				RestoreBuffer(sb);
				if( MouseKey()==LEWY ) {																							//	            If Mouse Key=LEWY
					STREFA=MouseZone();																									//	               STREFA=Mouse Zone
					if( STREFA>0 && STREFA<11 ) {																				//	               If STREFA>0 and STREFA<11
						I=STREFA;																													//	                  I=STREFA
						if( ARMIA[A2][I][TE]>0 ) {																				//	                  If ARMIA(A2,I,TE)>0
							ARMIA[A2][I][TE]=0;																							//	                     ARMIA(A2,I,TE)=0
							gad_back(0.8); _Bar(OKX+145,OKY+26+I*15,OKX+155,OKY+36+I*15);		//	                     Ink 4 : Bar OKX+145,OKY+26+I*15 To OKX+155,OKY+36+I*15
							CENA-=1000; WOJ--;																							//	                     Add CENA,-1000 : Dec WOJ
							gad_back(1.0); _Bar(OKX+64,OKY+193,OKX+96,OKY+205);							//	                     Ink 6 : Bar OKX+64,OKY+193 To OKX+96,OKY+205 : Ink 31,6 : Text OKX+66,OKY+202,Str$(CENA)
							gad_text(1.0); Text(OKX+66,OKY+202,Str_S(CENA));
						} else {																													//	                  Else
							ARMIA[A2][I][TE]=ARMIA[A2][I][TEM];															//	                     ARMIA(A2,I,TE)=ARMIA(A2,I,TEM)
							gad_text(1.0); Text(OKX+149,OKY+33+I*15,"X");										//	                     Ink 31,4 : Text OKX+149,OKY+33+I*15,"@"
							CENA+=1000; WOJ++;																							//	                     Add CENA,1000 : Inc WOJ
							gad_back(1.0); _Bar(OKX+64,OKY+193,OKX+96,OKY+205);							//	                     Ink 6 : Bar OKX+64,OKY+193 To OKX+96,OKY+205 : Ink 31,6 : Text OKX+66,OKY+202,Str$(CENA)
							gad_text(1.0); Text(OKX+66,OKY+202,Str_S(CENA));
						}																																	//	                  End If
						StoreBuffer(sb,OKX-1,OKY-1,162+2,210+2);
					}																																		//	               End If
					if( STREFA==11 ) {																									//	               If STREFA=11
						//WPISZ(OKX+8,OKY+31,31,4,14,0);																			//	                  WPISZ[OKX+8,OKY+31,31,4,14]
						_rysuj_tlo_rekrutacja = rysuj_ekran_ptr;
						rysuj_ekran_ptr = _rekrutacja_rysuj;
						_rekrutacja_buf = sb;
						SET_BACKGROUND(119.0f/255.f*.8f,102.0f/255.f*.8f,85.0f/255.f*.8f,1.f);
						SET_FOREGROUND(210.0f/255.f,204.0f/255.f,203.0f/255.f,1.f);
						WPISZ_PC(OKX+10,OKY+33-TextBase(),64,10,14,ARMIA_S[A2][0],3);
						rysuj_ekran_ptr = _rysuj_tlo_rekrutacja;
						StoreBuffer(sb,OKX-1,OKY-1,162+2,210+2);
						ARMIA_S[A2][0]=WPI_S;																							//	                  ARMIA$(A2,0)=WPI$
					}																																		//	               End If
					if( STREFA==13 && WOJ>0 && GRACZE[1][1]-CENA>=0 ) {									//	               If STREFA=13 and WOJ>0 and GRACZE(1,1)-CENA>=0
						GRACZE[1][1]-=CENA;																								//	                  Add GRACZE(1,1),-CENA
						ARMIA[A2][0][TE]=WOJ;																							//	                  ARMIA(A2,0,TE)=WOJ
						MIASTA[MIASTO][1][M_PODATEK]=30;																	//	                  MIASTA(MIASTO,1,M_PODATEK)=30
						ZOKNO();																														//	                  ZOKNO
						if( A1==-1 ) {																										//	                  If A1=-1
							ARMIA[A2][0][TAMO]=100;																					//	                     ARMIA(A2,0,TAMO)=100
							ARMIA[A2][0][TMAG]=1;																						//	                     ARMIA(A2,0,TMAG)=1
							XA=MIASTA[MIASTO][0][M_X];																			//	                     XA=MIASTA(MIASTO,0,M_X)
							YA=MIASTA[MIASTO][0][M_Y];																			//	                     YA=MIASTA(MIASTO,0,M_Y)
							ARMIA[A2][0][TX]=XA;																						//	                     ARMIA(A2,0,TX)=XA
							ARMIA[A2][0][TY]=YA;																						//	                     ARMIA(A2,0,TY)=YA
							ARMIA[A2][0][TNOGI]=MIASTO+70;																	//	                     ARMIA(A2,0,TNOGI)=MIASTO+70
							ARMIA[A2][0][TBOB]=3;																						//	                     ARMIA(A2,0,TBOB)=3
							B_DRAW(A2,XA,YA,3);																							//	                     B_DRAW[A2,XA,YA,3]
						}																																	//	                  End If
						KONIEC=-1;																												//	                  KONIEC=True
					}																																		//	               End If
					if( STREFA==12 ) {																									//	               If STREFA=12
						for(I=1;I<=10;++I) { if( REKRUCI[I]==1 ) ARMIA[A2][I][TE]=0; }		//	                  For I=1 To 10 : If REKRUCI(I)=1 : ARMIA(A2,I,TE)=0 : End If : Next I
						ZOKNO();																													//	                  ZOKNO
						KONIEC=-1;																												//	                  KONIEC=True
					}																																		//	               End If
					while( MouseKey()==LEWY ) ProcessEvents();														//	               While Mouse Key=LEWY : Wend
				}																																			//	            End If
				WaitVbl();
																																							//
			} while( KONIEC==0 );																										//	         Until KONIEC
																																							//
		} else {																																	//	      Else
			MESSAGE(MIASTO,GS("160"),0,1);																					//	         MESSAGE[MIASTO,"You can't command more legions.",0,1]
		}
		FreeBuffer(sb);																														//	      End If
	} else {																																		//	   Else
		DNI=MIASTA[MIASTO][1][M_PODATEK];																					//	      DNI=MIASTA(MIASTO,1,M_PODATEK)
		MESSAGE(MIASTO,GS("161")+Str_S(DNI)+GS("162"),0,1);												//	      MESSAGE[MIASTO,"New worriors during "+Str$(DNI)+" days.",0,1]
	}																																						//	   End If
	goto OVER;																																	//	   Goto OVER
																																							//	   RYSUJ:
																																							//	   A2=A
																																							//	   JEST=True
																																							//	   OKNO[70,30,162,210]
																																							//	   A$="Recruits of "+MIASTA$(MIASTO)
																																							//	   GADGET[OKX+4,OKY+4,154,15,A$,31,2,30,1,-1]
																																							//	   If A1=-1
																																							//	      A$="Legion "+Str$(A+1)
																																							//	   Else
																																							//	      A$=ARMIA$(A,0)
																																							//	   End If
																																							//	   GADGET[OKX+4,OKY+22,70,13,A$,7,0,4,31,11]
																																							//	   ARMIA$(A2,0)=A$
																																							//	   GADGET[OKX+77,OKY+22,70,13,"En  St  Sp  Mag",7,0,4,31,-1]
																																							//	   GADGET[OKX+4,OKY+192,45,15," Cancel",7,0,4,31,12]
																																							//	   GADGET[OKX+113,OKY+192,45,15,"   Ok",7,0,4,31,13]
																																							//	   GADGET[OKX+55,OKY+192,50,15,"",8,1,6,31,-1]
																																							//	   For I=1 To 10
																																							//	      If A1>-1 and ARMIA(A,I,TE)<=0 or A1=-1
																																							//	         REKRUCI(I)=1
																																							//	         NOWA_POSTAC[A,I,Rnd(8)]
																																							//	         ARMIA(A,I,TE)=0
																																							//	         A$=ARMIA$(A,I)+" "+RASY$(ARMIA(A,I,TRASA))
																																							//	         GADGET[OKX+4,OKY+24+I*15,138,13,A$,8,1,6,31,-1]
																																							//	         GADGET[OKX+144,OKY+24+I*15,15,13,"",7,0,4,31,I]
																																							//	         Ink 23,6 : Text OKX+77,OKY+34+I*15,Str$(ARMIA(A,I,TEM))
																																							//	         Text OKX+95,OKY+34+I*15,Str$(ARMIA(A,I,TSI))
																																							//	         Text OKX+110,OKY+34+I*15,Str$(ARMIA(A,I,TSZ))
																																							//	         Text OKX+125,OKY+34+I*15,Str$(ARMIA(A,I,TMAG))
																																							//	      End If
																																							//	   Next I
																																							//	   Return
	OVER:	;																																			//	   OVER:
																																							//	End Proc
}

