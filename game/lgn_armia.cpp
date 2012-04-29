
#include "Amos.h"

#include "legion.h"
#include "lgn_akcja.h"
#include "lgn_armia.h"
#include "lgn_miasto.h"
#include "lgn_diskacs.h"
#include "lgn_mapa.h"
#include "lgn_sceneria.h"
#include "lgn_util.h"
#include "utl_locale.h"

void ZROB_ARMIE(void) {
	//	Procedure ZROB_ARMIE

	aint L=0,XG=0,YG=0,B1=0,K=0,AR=0,X=0,Y=0;
	astr KON_S="";

	IMIONA_S[0]="ufo";			//	   IMIONA$(0)="ufo"
	for(L=0;L<=2;++L) {			//	   For L=0 To 2
		XG=Rnd(410)+100;			//	      XG=Rnd(410)+100
		YG=Rnd(300)+100;			//	      YG=Rnd(300)+100
		B1=4+L;								//	      B1=4+L
		for(K=0;K<=2;++K) {		//	      For K=0 To 2
			AR=(L*5)+20+K;			//	         AR=(L*5)+20+K
			X=XG+Rnd(200)-100;	//	         X=XG+Rnd(200)-100
			Y=YG+Rnd(200)-100;	//	         Y=YG+Rnd(200)-100
			if( Upper_S(Right_S(IMIONA_S[L+2],1))=="I" ) {//					 If Upper$(Right$(IMIONA$(L+2),1))="I"
				KON_S=GS("120");	//							KON$="ego"
			} else {						//					 Else
				KON_S=GS("121");	//							KON$="a"
			}										//					 End If
			ARMIA_S[AR][0]=Str_S(K+1)+GS("119")+IMIONA_S[L+2]+KON_S;			//	         ARMIA$(AR,0)=Str$(K+1)+" Legion of "+IMIONA$(L+2)
			ARMIA[AR][0][TX]=X;	//	         ARMIA(AR,0,TX)=X
			ARMIA[AR][0][TY]=Y;	//	         ARMIA(AR,0,TY)=Y
			ARMIA[AR][0][TBOB]=B1;//	         ARMIA(AR,0,TBOB)=B1
			ARMIA[AR][0][TMAG]=L+2;//	         ARMIA(AR,0,TMAG)=L+2
			NOWA_ARMIA(AR,10,-1);//	         NOWA_ARMIA[AR,10,-1]
			TEREN(X,Y);					//	         TEREN[X,Y]
			ARMIA[AR][0][TNOGI]=LOK;//	         ARMIA(AR,0,TNOGI)=LOK
			B_DRAW(AR,X,Y,B1);	//	         B_DRAW[AR,X,Y,B1]
		}											//	      Next K
	}												//	   Next L
													//	   'ustawianie poczâtkowej zaîogi
													//
	X=Rnd(600)+20;					//	   X=Rnd(600)+20
	Y=Rnd(490)+10;					//	   Y=Rnd(490)+10
	if( TESTING != 0 ) {		//	   If TESTING
		X=190;								//	      X=190
		Y=190;								//	      Y=190
	}												//	   End If
	NOWA_ARMIA(0,5,-1);			//	   NOWA_ARMIA[0,5,-1]
	ARMIA[0][0][TX]=X;			//	   ARMIA(0,0,TX)=X
	ARMIA[0][0][TY]=Y;			//	   ARMIA(0,0,TY)=Y
	ARMIA[0][0][TBOB]=3;		//	   ARMIA(0,0,TBOB)=3
	ARMIA[0][0][TMAG]=1;		//	   ARMIA(0,0,TMAG)=1
	TEREN(X,Y);							//	   TEREN[X,Y]
	ARMIA[0][0][TNOGI]=LOK;	//	   ARMIA(0,0,TNOGI)=LOK
	ARMIA[0][0][TAMO]=100;	//	   ARMIA(0,0,TAMO)=100
	B_DRAW(0,X,Y,3);				//	   B_DRAW[0,X,Y,3]
													//
													//	End Proc
}

void _ARMIA_RYSUJ_ROZKAZY(aint A) {
	aint AWT=0,WYS=0,TRYB=0,TEREN=0;
	TEREN=ARMIA[A][0][TNOGI];
	AWT=ARMIA[A][0][TWAGA];									//	   AWT=ARMIA(A,0,TWAGA)
	if( AWT==1 ) {													//	   If AWT=1
		WYS=135;															//	      WYS=135
	} else {																//	   Else
		WYS=150;															//	      WYS=150
	}																				//	   End If
	OKNO(110,70,80,WYS);										//	   OKNO[110,70,80,WYS]
	GADGET(OKX+4,OKY+4,72,15,GS("178"),8,2,6,31,1);		//	   GADGET[OKX+4,OKY+4,72,15,"Move",8,2,6,31,1]
	GADGET(OKX+4,OKY+40,72,15,GS("179"),8,2,6,31,3);	//	   GADGET[OKX+4,OKY+40,72,15,"Attack",8,2,6,31,3]
	GADGET(OKX+4,OKY+2+20,72,15,GS("180"),8,2,6,31,2);//	   GADGET[OKX+4,OKY+2+20,72,15,"Fast Move",8,2,6,31,2]
	if( TEREN<70 ) {												//	   If TEREN<70
		GADGET(OKX+4,OKY+58,72,15,GS("181"),8,2,6,31,4); //	      GADGET[OKX+4,OKY+58,72,15,"Hunt",8,2,6,31,4]
	} else {																//	   Else
		GADGET(OKX+4,OKY+58,72,15,GS("182"),8,2,6,31,4); //	      GADGET[OKX+4,OKY+58,72,15,"Recruit",8,2,6,31,4]
	}																				//	   End If
	GADGET(OKX+4,OKY+76,72,15,GS("183"),8,2,6,31,5);				//	   GADGET[OKX+4,OKY+76,72,15,"Camp",8,2,6,31,5]
	GADGET(OKX+4,OKY+94,72,15,GS("184"),8,2,6,31,6);	//	   GADGET[OKX+4,OKY+94,72,15,"Equipment",8,2,6,31,6]
	if( AWT==0 ) {													//	   If AWT=0
		GADGET(OKX+4,OKY+112,72,15,GS("185"),8,2,6,31,8);	//	      GADGET[OKX+4,OKY+112,72,15,"Action",8,2,6,31,8]
		GADGET(OKX+4,OKY+130,72,15,GS("186"),8,2,6,31,7);		//	      GADGET[OKX+4,OKY+130,72,15,"Exit",8,2,6,31,7]
	} else {																//	   Else
		GADGET(OKX+4,OKY+112,72,15,GS("186"),8,2,6,31,7);		//	      GADGET[OKX+4,OKY+112,72,15,"Exit",8,2,6,31,7]
	}																				//	   End If
	TRYB=ARMIA[A][0][TTRYB];								//	   TRYB=ARMIA(A,0,TTRYB)
	Gfx::Color(1.f,1.f,1.f);								//	   Ink 23,6
	if( TRYB>0 ) {													//	   If TRYB>0
		Text(OKX+65,OKY-4+18*TRYB,"@");				//	      Text OKX+65,OKY-4+18*TRYB,"@"
	}																				//	   End If
	if( TRYB==0 ) {													//	   If TRYB=0
		Text(OKX+65,OKY-4+18*5,"@");					//	      Text OKX+65,OKY-4+18*5,"@"
	}																				//	   End If
}
void _ARMIA_RYSUJ_INFO(aint A) {
	aint AX=0,AY=0,PL=0,I=0;
	aint GD=0,DANE=0;//,KONIEC=0;
	aint WOJ=0,SILA=0,SPEED=0,TRYB=0,CELX=0,CELY=0,ROZ=0;
	aint TEREN=0,ZARCIE=0;
	astr RO_S="",D_S="",DNI_S="",WOJ_S="",R2_S="";

	AX=ARMIA[A][0][TX];											//	   AX=ARMIA(A,0,TX)
	AY=ARMIA[A][0][TY];											//	   AY=ARMIA(A,0,TY)
	PL=ARMIA[A][0][TMAG];										//	   PL=ARMIA(A,0,TMAG)

	OKNO(80,80,150,100);										//	   OKNO[80,80,150,100]
	GD=50;																	//	   GD=50
	if( A<20 ) {														//	   If A<20
		RO_S=GS("187");												//	      RO$="Commands"
		DANE=-1;															//	      DANE=True
	} else {																//	   Else
		RO_S=GS("188");												//	      RO$="Inquiry"
		if( ARMIA[A][0][TMAGMA]>28 && ARMIA[A][0][TMAGMA]<100 ) {	//	      If ARMIA(A,0,TMAGMA)>28 and ARMIA(A,0,TMAGMA)<100
			DANE=0; D_S=GS("189");							//	         DANE=False : D$="No informations."
		} else {															//	      Else
			if( ARMIA[A][0][TMAGMA]>1 ) {				//	         If ARMIA(A,0,TMAGMA)>1
				DNI_S=GS("190");									//	            DNI$=" days."
			} else {														//	         Else
				DNI_S=GS("191");									//	            DNI$=" day."
			}																		//	         End If
			DANE=0;															//	         DANE=False : D$="Informations during "+Str$(ARMIA(A,0,TMAGMA))+DNI$
			D_S=GS("192")+Str_S(ARMIA[A][0][TMAGMA])+DNI_S;
		}																			//	      End If
		if( ARMIA[A][0][TMAGMA]==0 || ARMIA[A][0][TMAGMA]==100 ) {//	      If ARMIA(A,0,TMAGMA)=0 or ARMIA(A,0,TMAGMA)=100
			RO_S=GS("193");											//	         RO$="Trace "
			GD=52;															//	         GD=52
			DANE=-1;														//	         DANE=True
		}																			//	      End If
	}																				//	   End If
	GADGET(OKX+4,OKY+4,142,74,"",31,2,30,1,-1);//	   GADGET[OKX+4,OKY+4,142,74,"",31,2,30,1,-1]
	GADGET(OKX+4,OKY+80,GD,15,RO_S,8,2,6,31,10);//	   GADGET[OKX+4,OKY+80,GD,15,RO$,8,2,6,31,10]
	GADGET(OKX+106,OKY+80,40,15,GS("194"),8,2,6,31,1);//	   GADGET[OKX+106,OKY+80,40,15,"   Ok  ",8,2,6,31,1]
	if( ARMIA[A][0][TMAGMA]==100 ) {				//	   If ARMIA(A,0,TMAGMA)=100 : Ink 31,6 : Text OKX+48,OKY+89,"@" : End If
		gad_text(1.0);
		Text(OKX+48,OKY+89,"@");
	}
	//!!!nieco inaczej											//	   No Mask 23+PL : Paste Bob OKX+8,OKY+8,23+PL
	Gfx::Color(0,0,0); _Bar(OKX+8,OKY+8,OKX+40,OKY+40);
	PasteBob(OKX+8,OKY+8,23+PL);
	SetZone(11,OKX+50,OKY+5,OKX+120,OKY+15);//	   Set Zone 11,OKX+50,OKY+5 To OKX+120,OKY+15
	gad_text(1.0);													//	   Ink 1,30 : Text OKX+50,OKY+15,ARMIA$(A,0)
	Text(OKX+50,OKY+15,ARMIA_S[A][0]);
	if( DANE !=0 ) {												//	   If DANE
		for(I=1;I<=10;++I) {									//	      For I=1 To 10
			if( ARMIA[A][I][TE]>0 ) {						//	         If ARMIA(A,I,TE)>0
				WOJ+=1;														//	            Add WOJ,1
				SILA+=ARMIA[A][I][TSI];						//	            Add SILA,ARMIA(A,I,TSI)
				SILA+=ARMIA[A][I][TE];						//	            Add SILA,ARMIA(A,I,TE)
				SPEED+=ARMIA[A][I][TSZ];					//	            Add SPEED,ARMIA(A,I,TSZ)
			}																		//	         End If
		}																			//	      Next I
		ARMIA[A][0][TE]=WOJ;									//	      ARMIA(A,0,TE)=WOJ
		SPEED=((SPEED/WOJ)/5);								//	      SPEED=((SPEED/WOJ)/5)
		ARMIA[A][0][TSZ]=SPEED;								//	      ARMIA(A,0,TSZ)=SPEED
		ARMIA[A][0][TSI]=SILA;								//	      ARMIA(A,0,TSI)=SILA
		AX=ARMIA[A][0][TX];										//	      AX=ARMIA(A,0,TX)
		AY=ARMIA[A][0][TY];										//	      AY=ARMIA(A,0,TY)
		TRYB=ARMIA[A][0][TTRYB];							//	      TRYB=ARMIA(A,0,TTRYB)
		CELX=ARMIA[A][0][TCELX];							//	      CELX=ARMIA(A,0,TCELX)
		CELY=ARMIA[A][0][TCELY];							//	      CELY=ARMIA(A,0,TCELY)
		ROZ=ARMIA[A][0][TTRYB];								//	      ROZ=ARMIA(A,0,TTRYB)
		TEREN=ARMIA[A][0][TNOGI];							//	      TEREN=ARMIA(A,0,TNOGI)
		WOJ_S=GS("195");											//	      WOJ$=" worriors"
		if( WOJ==1 ) WOJ_S=GS("196");					//	      If WOJ=1 : WOJ$=" worrior" : End If
		if(	ROZ==0 ) {												//	      If ROZ=0
			RO_S=GS("197");											//	         RO$="Unit is tenting"
			if( TEREN>69 ) {										//	         If TEREN>69
				RO_S+=GS("198")+MIASTA_S[TEREN-70];	//	            RO$=RO$+" in "+MIASTA$(TEREN-70)
			}																		//	         End If
		}																			//	      End If
		if( ROZ==1 || ROZ==2 ) {							//	      If ROZ=1 or ROZ=2 : RO$="Unit is moving." : End If
			RO_S=GS("199");
		}
		if( ROZ==3 ) {												//	      If ROZ=3
			if( CELY==0 ) {											//	         If CELY=0
				R2_S=ARMIA_S[CELX][0];						//	            R2$=ARMIA$(CELX,0)
			} else {														//	         Else
				R2_S=MIASTA_S[CELX];							//	            R2$=MIASTA$(CELX)
			}																		//	         End If
			RO_S=GS("200")+R2_S;				//	         RO$="We're attacking "+R2$
		}																			//	      End If
		if( ROZ==4 ) {												//	      If ROZ=4 : RO$="We're hunting" : End If
			RO_S=GS("201");
		}
		ZARCIE=ARMIA[A][0][TAMO]/WOJ;					//	      ZARCIE=ARMIA(A,0,TAMO)/WOJ
		DNI_S=GS("202")+Str_S(ZARCIE)+GS("203");//	      DNI$="Food for "+Str$(ZARCIE)+" days"
		if( ZARCIE==1 ) {											//	      If ZARCIE=1 : DNI$="Food for only 1 day" : End If
			DNI_S=GS("204");
		}
		if( ZARCIE<=0 ) {											//	      If ZARCIE<=0 : DNI$="We have no food !" : End If
			DNI_S=GS("205");
		}
		gad_text(1.0);																	//	      Ink 1,30
		Text(OKX+50,OKY+35,GS("206")+Str_S(SILA));	//	      Text OKX+50,OKY+35,"Strength  :"+Str$(SILA)
		Text(OKX+50,OKY+25,Str_S(WOJ)+WOJ_S);						//	      Text OKX+50,OKY+25,Str$(WOJ)+WOJ$
		Text(OKX+50,OKY+45,DNI_S);											//	      Text OKX+50,OKY+45,DNI$
		Text(OKX+50,OKY+55,GS("207")+Str_S(SPEED));	//	      Text OKX+50,OKY+55,"Speed     :"+Str$(SPEED)
		Text(OKX+12,OKY+65,RO_S);												//	      Text OKX+12,OKY+65,RO$
	} else {																//	   Else
		gad_text(1.0);
		Text(OKX+12,OKY+60,D_S);							//	      Text OKX+12,OKY+60,D$
	}																				//	   End If
}
void (*_rysuj_tlo_armia)(void) = 0;
aint _rysuj_armia_nr = -1;
void _rysuj_armia(void) {
	if( _rysuj_tlo_armia ) _rysuj_tlo_armia();
	if( _rysuj_armia_nr>= 0 ) _ARMIA_RYSUJ_INFO(_rysuj_armia_nr);
}
void _ARMIA(aint A) {
	//	Procedure ARMIA[A]

	aint AX=0,AY=0,PL=0,KONIEC=0,TEREN=0,I=0,DANE=0;
	aint STREFA=0,KONIEC2=0,STREFA2=0,TER2=0;

	_rysuj_armia_nr = A;

	AX=ARMIA[A][0][TX];											//	   AX=ARMIA(A,0,TX)
	AY=ARMIA[A][0][TY];											//	   AY=ARMIA(A,0,TY)
	PL=ARMIA[A][0][TMAG];										//	   PL=ARMIA(A,0,TMAG)
	if( PREFS[5]==1 ) {
		WJAZD(AX,AY,80,80,150,100,4);					//	   If PREFS(5)=1 : WJAZD[AX,AY,80,80,150,100,4] : End If
	}

	if( A<20 ) {
		DANE=-1;
	} else {
		if( ARMIA[A][0][TMAGMA]==0 || ARMIA[A][0][TMAGMA]==100 ) {
			DANE=-1;
		}
	}

	if( DANE!=0 ) {
		TEREN=ARMIA[A][0][TNOGI];
		AX=ARMIA[A][0][TX];
		AY=ARMIA[A][0][TY];
	}

	rysuj();
	_ARMIA_RYSUJ_INFO(A);

	void *sb=0, *sb2=0;
	sb = StoreBuffer(OKX-1,OKY-1,150+2,100+2);

	do {																		//	   Repeat
		rysuj();
		RestoreBuffer(sb);
		WaitVbl();
		if( MouseClick() ) {									//	      If Mouse Click=1
			STREFA=MouseZone();									//	         STREFA=Mouse Zone
			if( STREFA==1 || STREFA==0 ) {			//	         If STREFA=1 or STREFA=0
				KONIEC=-1;												//	            KONIEC=True
				ZOKNO();													//	            ZOKNO
			}																		//	         End If
			if( STREFA==11 ) {									//	         If STREFA=11
				//WPISZ(OKX+50,OKY+15,1,30,14,0);			//	            WPISZ[OKX+50,OKY+15,1,30,14]

				_rysuj_tlo_armia = rysuj_ekran_ptr;
				rysuj_ekran_ptr = _rysuj_armia;
				WPISZ_PC(OKX+50,OKY+15-TextBase(),100,10,14,ARMIA_S[A][0],2);	//rysuj tylko tlo i kursor
				rysuj_ekran_ptr = _rysuj_tlo_armia;
				sb = StoreBuffer(OKX-1,OKY-1,150+2,100+2);

				ARMIA_S[A][0]=WPI_S;							//	            ARMIA$(A,0)=WPI$
			}																		//	         End If
			if( STREFA==10 && A<20 ) {					//	         If STREFA=10 and A<20
				ZOKNO();													//	            ZOKNO
				KONIEC=-1;												//	            KONIEC=True
				rysuj();
				_ARMIA_RYSUJ_ROZKAZY(A);					//	            Gosub RYSUJ_ROZKAZY
				sb2 = StoreBuffer(OKX-1,OKY-1,80+2,150+2);
				KONIEC2=0;												//	            KONIEC2=False
				do {															//	            Repeat
					rysuj();
					RestoreBuffer(sb2);
					WaitVbl();
					if( MouseClick() ) {						//	               If Mouse Click=1
						STREFA2=MouseZone();					//	                  STREFA2=Mouse Zone
						if( STREFA2>0 && STREFA2<4 ) {//	                  If STREFA2>0 and STREFA2<4
							ZOKNO();										//	                     ZOKNO
							M_RUCH(A,STREFA2);					//	                     M_RUCH[A,STREFA2]
							KONIEC2=-1; KONIEC=-1;			//	                     KONIEC2=True : KONIEC=True
						}															//	                  End If
						if( STREFA2==4 && TEREN<70 ) {//	                  If STREFA2=4 and TEREN<70
							ZOKNO();										//	                     ZOKNO
							ARMIA[A][0][TTRYB]=4;				//	                     ARMIA(A,0,TTRYB)=4
							KONIEC2=-1; KONIEC=-1;			//	                     KONIEC=True : KONIEC2=True
						}															//	                  End If
						if( STREFA2==4 && TEREN>69 ) {//	                  If STREFA2=4 and TEREN>69
							if( MIASTA[TEREN-70][0][M_CZYJE]==1 ) {//	                     If MIASTA(TEREN-70,0,M_CZYJE)=1
								ZOKNO();									//	                        ZOKNO
								ARMIA[A][0][TTRYB]=0;			//	                        ARMIA(A,0,TTRYB)=0
								REKRUTACJA(10,TEREN-70,A);//	                        REKRUTACJA[10,TEREN-70,A]
								_ARMIA_RYSUJ_ROZKAZY(A);		//	                        Gosub RYSUJ_ROZKAZY
							}														//	                     End If
						}															//	                  End If
																					//
						if( STREFA2==6 ) {						//	                  If STREFA2=6
							ZOKNO();										//	                     ZOKNO
							SpriteOnOff(2,false);				//	                     Sprite Off 2
																					//	                     'Auto View Off
							_LOAD(KAT_S+"dane/gad","dane:gad","Dane",1);	//	                     _LOAD[KAT$+"dane/gad","dane:gad","Dane",1]
							ScreenOpen(1,320,160,32,LOWRES);//	                     Screen Open 1,320,160,32,Lowres
							Screen(1);									//	                     Screen 1
																					//	                     Curs Off : Flash Off
							ReserveZone(60);						//	                     Reserve Zone 60 : Get Bob Palette : Set Font FON1
							SetFont(FON1);
							GOBY=44;										//	                     GOBY=44
																					//	                     'Auto View On
							ARM=A;											//	                     ARM=A
							for(I=1;I<=10;++I) {				//	                     For I=1 To 10
								if( ARMIA[A][I][TE]>0 ) {	//	                        If ARMIA(A,I,TE)>0
									NUMER=I;								//	                           NUMER=I
									I=10;										//	                           I=10
								}													//	                        End If
							}														//	                     Next
							WYBOR(1);										//	                     WYBOR[1]
							ScreenClose(1);							//	                     Screen Close 1
							for(I=1;I<=50;++I) {				//	                     For I=1 To 50
								DelBob(GOBY+1);						//	                        Del Bob GOBY+1
							}														//	                     Next
							Screen(0);									//	                     Screen 0
							Sprite(2,SPX,SPY,1);				//	                     Sprite 2,SPX,SPY,1
							_ARMIA_RYSUJ_ROZKAZY(A);			//	                     Gosub RYSUJ_ROZKAZY
						}															//	                  End If
																					//
						if( STREFA2==8 ) {						//	                  If STREFA2=8
							KONIEC=-1;KONIEC2=-1;				//	                     KONIEC=True : KONIEC2=True
							ARMIA[A][0][TWAGA]=1;				//	                     ARMIA(A,0,TWAGA)=1
							ARM=A; WRG=40;							//	                     ARM=A : WRG=40
							SpriteOnOff(2,false);				//	                     Sprite Off 2
							SETUP(GS("070"),GS("071"),GS("072"));			//	                     SETUP["","Action",""]
							if( TEREN>69 ) {						//	                     If TEREN>69
								TER2=MIASTA[TEREN-70][1][M_X];//	                        TER2=MIASTA(TEREN-70,1,M_X)
								RYSUJ_SCENERIE(TER2,TEREN-70);//	                        RYSUJ_SCENERIE[TER2,TEREN-70]
								WRG=40;										//	                        WRG=40
																					//	                        'ustaw wieôniaków
								for(I=1;I<=7;++I) {				//	                        For I=1 To 7 : NOWA_POSTAC[40,I,9] : Next I
									NOWA_POSTAC(40,I,9);
								}
								for(I=8;I<=10;++I) {			//	                        For I=8 To 10 : NOWA_POSTAC[40,I,Rnd(8)] : Next I
									NOWA_POSTAC(40,I,Rnd(8));
								}
								for(I=1;I<=7;++I) {				//	                        For I=1 To 7 : ARMIA(40,I,TKORP)=20 : Next I
									ARMIA[40][I][TKORP]=20;
								}
								for(I=8;I<=10;++I) {			//	                        For I=8 To 10 : ARMIA(WRG,I,TKORP)=40 : Next I
									ARMIA[WRG][I][TKORP]=40;
								}
								ARMIA[40][0][TE]=10;			//	                        ARMIA(40,0,TE)=10
								USTAW_WOJSKO(WRG,1,1,1);	//	                        USTAW_WOJSKO[WRG,1,1,1]
							} else {										//	                     Else
								ARMIA[WRG][0][TE]=0;			//	                        ARMIA(WRG,0,TE)=0
								RYSUJ_SCENERIE(TEREN,-1);	//	                        RYSUJ_SCENERIE[TEREN,-1]
							}														//	                     End If
							USTAW_WOJSKO(ARM,1,1,0);		//	                     USTAW_WOJSKO[ARM,1,1,0]
							MAIN_ACTION();							//	                     MAIN_ACTION
																					//	                     'skasuj wieôniaków
							for(I=0;I<=10;++I) {				//	                     For I=0 To 10 : ARMIA(40,I,TE)=0 : Next I
								ARMIA[40][I][TE]=0;
							}
							SETUP0();										//	                     SETUP0
							VISUAL_OBJECTS();						//	                     VISUAL_OBJECTS
							CENTER(AX,AY,0);						//	                     CENTER[AX,AY,0]
							Sprite(2,SPX,SPY,1);				//	                     Sprite 2,SPX,SPY,1
						}															//	                  End If
																					//
						if( STREFA2==5 ) {						//	                  If STREFA2=5
							ZOKNO();										//	                     ZOKNO
							ARMIA[A][0][TTRYB]=0;				//	                     ARMIA(A,0,TTRYB)=0
							KONIEC=-1;KONIEC2=-1;				//	                     KONIEC=True : KONIEC2=True
						}															//	                  End If
						if( STREFA2==7 ) {						//	                  If STREFA2=7
							ZOKNO();										//	                     ZOKNO
							KONIEC2=-1;									//	                     KONIEC2=True
						}															//	                  End If
					}																//	               End If
				} while( 0==KONIEC2 );						//	            Until KONIEC2
			}																		//	         End If
			if( STREFA==10 && A>19 ) {					//	         If STREFA=10 and A>19
				if( ARMIA[A][0][TMAGMA]==0 ) {		//	            If ARMIA(A,0,TMAGMA)=0
					gad_text(1.0);									//	               Ink 31,6 : Text OKX+48,OKY+89,"@"
					Text(OKX+48,OKY+89,"@");
					ARMIA[A][0][TMAGMA]=100;				//	               ARMIA(A,0,TMAGMA)=100
					goto SKIP;											//	               Goto SKIP
				}																	//	            End If
				if( ARMIA[A][0][TMAGMA]==100 ) {	//	            If ARMIA(A,0,TMAGMA)=100
					gad_text(1.0);									//	               Gr Writing 1 : Ink 6,6
					Text(OKX+47,OKY+89,"  ");				//	               Text OKX+47,OKY+89,"  "
					ARMIA[A][0][TMAGMA]=0;					//	               ARMIA(A,0,TMAGMA)=0
				}																	//	            End If
				if( ARMIA[A][0][TMAGMA]>0 && ARMIA[A][0][TMAGMA]<100 ) {//	            If ARMIA(A,0,TMAGMA)>0 and ARMIA(A,0,TMAGMA)<100
					ZOKNO();												//	               ZOKNO
					KONIEC=-1;											//	               KONIEC=True
					SZPIEGUJ(A,1);									//	               SZPIEGUJ[A,1]
				}																	//	            End If
				SKIP:															//	            SKIP:
					;
			}																		//	         End If
		}																			//	      End If
	} while( KONIEC==0 );										//	   Until KONIEC

	FreeBuffer(sb);
	FreeBuffer(sb2);
																					//	   Goto OVER
																					//	   OVER:
																					//	End Proc
}

void _M_RUCH_INFO(astr A_S) {
	aint KONIEC=0;
	rysuj(); MouseClick();
																					//	   INFO:
	OKNO(90,100,158,22);										//	   OKNO[90,100,158,22]
	GADGET(OKX+4,OKY+4,150,15,"",31,2,30,1,0);//	   GADGET[OKX+4,OKY+4,150,15,"",31,2,30,1,0]
	gad_text(1.0); Text(OKX+8,OKY+15,A_S);	//	   Ink 1,30 : Text OKX+8,OKY+15,A$
	void *sb=StoreBuffer(OKX-1,OKY-1,158+2,22+2);
	do {																		//	   Repeat
		rysuj();
		RestoreBuffer(sb);
		WaitVbl();
		if( MouseClick() ) {									//	      If Mouse Click=1
			KONIEC=-1;													//	         KONIEC=True
		}																			//	      End If
	} while( KONIEC==0 );										//	   Until KONIEC
	ZOKNO();																//	   ZOKNO
	FreeBuffer(sb);
	rysuj();
	WaitVbl();
}
void M_RUCH(aint A,aint TYP) {
	//	Procedure M_RUCH[A,TYP]

	aint AX=0,AY=0,SPEED=0,CZAS=0,STREFA=0;
	astr DNI_S="",A_S="";

	AX=ARMIA[A][0][TX]; AY=ARMIA[A][0][TY];	//	   AX=ARMIA(A,0,TX) : AY=ARMIA(A,0,TY)
	_GET_XY(1,AX,AY);												//	   _GET_XY[1,AX,AY]
	STREFA=_Zone(OX,OY);											//	   STREFA=Zone(OX,OY)
	ODL(AX,AY,OX,OY);												//	   ODL[AX,AY,OX,OY]
	SPEED=ARMIA[A][0][TSZ];									//	   SPEED=ARMIA(A,0,TSZ)
	if( TYP==2 ) SPEED *= 2;								//	   If TYP=2 Then SPEED=SPEED*2
	CZAS=ODLEG/SPEED;												//	   CZAS=ODLEG/SPEED
	if( CZAS==0 || CZAS==1 ) {							//	   If CZAS=0 or CZAS=1
		DNI_S=GS("208"); CZAS=1;							//	      DNI$=" day" : CZAS=1
	} else {																//	   Else
		DNI_S=GS("209");											//	      DNI$=" days"
	}																				//	   End If
																					//	   'naprawa
	if( TYP==3 ) {													//	   If TYP=3
		if( STREFA>=20 && STREFA<120 ) {			//	      If STREFA>=20 and STREFA<120
			A_S=GS("210")+Str_S(CZAS)+DNI_S;		//	         A$="We'll reach target during "+Str$(CZAS)+DNI$
			ARMIA[A][0][TTRYB]=TYP;							//	         ARMIA(A,0,TTRYB)=TYP
			if(	STREFA<61 ) {										//	         If STREFA<61
				if( STREFA-20>19 ) {							//	            If STREFA-20>19
					ARMIA[A][0][TCELX]=STREFA-20;		//	               ARMIA(A,0,TCELX)=STREFA-20
					ARMIA[A][0][TCELY]=0;						//	               ARMIA(A,0,TCELY)=0
				} else {													//	            Else
					ARMIA[A][0][TTRYB]=0;						//	               ARMIA(A,0,TTRYB)=0
					A_S=GS("211");									//	               A$="This is our unit !"
				}																	//	            End If
			}	else {														//	         Else
				if( MIASTA[STREFA-70][0][M_CZYJE] != 1 ) {//	            If MIASTA(STREFA-70,0,M_CZYJE)<>1
					ARMIA[A][0][TCELX]=STREFA-70;		//	               ARMIA(A,0,TCELX)=STREFA-70
					ARMIA[A][0][TCELY]=1;						//	               ARMIA(A,0,TCELY)=1
				} else {													//	            Else
					ARMIA[A][0][TTRYB]=0;						//	               ARMIA(A,0,TTRYB)=0
					A_S=GS("212");									//	               A$="This is our town !"
				}																	//	            End If
			}																		//	         End If
			_M_RUCH_INFO(A_S);									//	         Gosub INFO
		} else {															//	      Else
			A_S=GS("213");											//	         A$="There is no target."
			_M_RUCH_INFO(A_S);									//	         Gosub INFO
			ARMIA[A][0][TTRYB]=0;								//	         ARMIA(A,0,TTRYB)=0
		}																			//	      End If
	} else {																//	   Else
		if( OY<8 ) OY=8;											//	      If OY<8 : OY=8 : End If
		if( OY>511 ) OY=511;									//	      If OY>511 : OY=511 : End If
		if( OX<4 ) OX=4;											//	      If OX<4 : OX=4 : End If
		if( OX>636 ) OX=636;									//	      If OX>636 : OX=636 : End If
																					//
		ARMIA[A][0][TCELX]=OX;								//	      ARMIA(A,0,TCELX)=OX
		ARMIA[A][0][TCELY]=OY;								//	      ARMIA(A,0,TCELY)=OY
		ARMIA[A][0][TTRYB]=TYP;								//	      ARMIA(A,0,TTRYB)=TYP
		A_S=GS("214")+Str_S(CZAS)+DNI_S;			//	      A$="We'll get there during "+Str$(CZAS)+DNI$
																					//
		_M_RUCH_INFO(A_S);										//	      Gosub INFO
	}																				//	   End If
																					//	   Goto OVER
																					//	   OVER:
																					//	End Proc
}

void ZABIJ_ARMIE(aint A) {
	//	Procedure ZABIJ_ARMIE[A]

	aint I=0;
	ARMIA[A][0][TE]=0;			//	   ARMIA(A,0,TE)=0
	ARMIA[A][0][TAMO]=0;		//	   ARMIA(A,0,TAMO)=0
	ARMIA[A][0][TSI]=0;			//	   ARMIA(A,0,TSI)=0
	ARMIA[A][0][TSZ]=0;			//	   ARMIA(A,0,TSZ)=0
	ARMIA[A][0][TTRYB]=0;		//	   ARMIA(A,0,TTRYB)=0
	for(I=1;I<=10;I++) {		//	   For I=1 To 10
		ARMIA[A][I][TE]=0;		//	      ARMIA(A,I,TE)=0
	}												//	   Next
													//	End Proc
}

void NOWA_ARMIA(aint A,aint ILU,aint RASA) {
	//	Procedure NOWA_ARMIA[A,ILU,RASA]

	astr A_S="";
	aint R=0,I=0,SILA=0,SPEED=0;

	if( A<20 ) {										//	   If A<20 : A$="Legion "+Str$(A+1)
		A_S=GS("039")+Str_S(A+1);
		ARMIA_S[A][0]=A_S;						//	      ARMIA$(A,0)=A$
	} else {												//	   Else
																	//	      'utajnianie
		ARMIA[A][0][TMAGMA]=30;				//	      ARMIA(A,0,TMAGMA)=30
		ARMIA[A][0][TKORP]=150+Rnd(50)+POWER;		//	      ARMIA(A,0,TKORP)=150+Rnd(50)+POWER
	}																//	   End If
	ARMIA[A][0][TAMO]=Rnd(200);			//	   ARMIA(A,0,TAMO)=Rnd(200)
	ARMIA[A][0][TE]=ILU;						//	   ARMIA(A,0,TE)=ILU
	R=RASA;													//	   R=RASA
	for(I=1;I<=ILU;++I) {						//	   For I=1 To ILU
		if(RASA==-1) R=Rnd(8);				//	      If RASA=-1 : R=Rnd(8) : End If
		NOWA_POSTAC(A,I,R);						//	      NOWA_POSTAC[A,I,R]
		SILA += ARMIA[A][I][TSI];			//	      Add SILA,ARMIA(A,I,TSI)
		SILA += ARMIA[A][I][TE];			//	      Add SILA,ARMIA(A,I,TE)
		SPEED += ARMIA[A][I][TSZ];		//	      Add SPEED,ARMIA(A,I,TSZ)
	}																//	   Next I
	//!!! niestandardowe
	if( ILU==0 ) ILU=1;
	SPEED=((SPEED/ILU)/5);					//	   SPEED=((SPEED/ILU)/5)
	ARMIA[A][0][TSZ]=SPEED;					//	   ARMIA(A,0,TSZ)=SPEED
	ARMIA[A][0][TSI]=SILA;					//	   ARMIA(A,0,TSI)=SILA
	ARMIA[A][0][TTRYB]=0;						//	   ARMIA(A,0,TTRYB)=0
}																	//	End Proc
