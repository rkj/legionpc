
#include "Amos.h"

#include "legion.h"
#include "lgn_przygoda.h"
#include "lgn_util.h"
#include "locale.h"

void NOWA_PRZYGODA(aint A,aint NR,aint TYP,aint LEVEL) {
																														//	Procedure NOWA_PRZYGODA[A,NR,TYP,LEVEL]
  aint _BRON=0, BTYP=0, BCENA=0, _MIASTO=0, RSA=0;

	PRZYGODY[NR][P_TYP]=TYP;																	//	   PRZYGODY(NR,P_TYP)=TYP
	PRZYGODY[NR][P_X]=ARMIA[A][0][TNOGI]-70;									//	   PRZYGODY(NR,P_X)=ARMIA(A,0,TNOGI)-70
	PRZYGODY[NR][P_Y]=Rnd(9)+1;																//	   PRZYGODY(NR,P_Y)=Rnd(9)+1
	PRZYGODY[NR][P_KIERUNEK]=-1;															//	   PRZYGODY(NR,P_KIERUNEK)=-1
	PRZYGODY[NR][P_LEVEL]=LEVEL;															//	   PRZYGODY(NR,P_LEVEL)=LEVEL
	IM_PRZYGODY_S[NR]="";																			//	   IM_PRZYGODY$(NR)=""

	if( TYP==1 ) {																						//	   If TYP=1
		//---kopalnia---																				//	      'kopalnia
		PRZYGODY[NR][P_TERMIN]=100+Rnd(100);										//	      PRZYGODY(NR,P_TERMIN)=100+Rnd(100)
		PRZYGODY[NR][P_CENA]=20*LEVEL;													//	      PRZYGODY(NR,P_CENA)=20*LEVEL
		PRZYGODY[NR][P_NAGRODA]=LEVEL*10000;										//	      PRZYGODY(NR,P_NAGRODA)=LEVEL*10000
		PRZYGODY[NR][P_TEREN]=8;																//	      PRZYGODY(NR,P_TEREN)=8
		PRZYGODY[NR][P_BRON]=0;																	//	      PRZYGODY(NR,P_BRON)=0
	}																													//	   End If
	if( TYP==2 ) {																						//	   If TYP=2
		//---kurhan---																					//	      'kurhan
		PRZYGODY[NR][P_TERMIN]=100+Rnd(100);										//	      PRZYGODY(NR,P_TERMIN)=100+Rnd(100)
		PRZYGODY[NR][P_CENA]=Rnd(20*LEVEL);											//	      PRZYGODY(NR,P_CENA)=Rnd(20*LEVEL)
		PRZYGODY[NR][P_NAGRODA]=LEVEL*100;											//	      PRZYGODY(NR,P_NAGRODA)=LEVEL*100
		do {																										//	      Repeat
			_BRON=Rnd(MX_WEAPON);																	//	         BRON=Rnd(MX_WEAPON)
			BTYP=BRON[_BRON][B_TYP];															//	         BTYP=BRON(BRON,B_TYP)
		} while( !( BRON[_BRON][B_CENA]>=1000 && BRON[_BRON][BCENA]<100+LEVEL*1000 && BTYP!=5 && BTYP!=8 && BTYP!=13 && BTYP!=14 && BTYP<16) );																													//	      Until BRON(BRON,B_CENA)>=1000 and BRON(BRON,BCENA)<100+LEVEL*1000 and BTYP<>5 and BTYP<>8 and BTYP<>13 and BTYP<>14 and BTYP<16
		PRZYGODY[NR][P_BRON]=_BRON;															//	      PRZYGODY(NR,P_BRON)=BRON
		PRZYGODY[NR][P_TEREN]=9;																//	      PRZYGODY(NR,P_TEREN)=9
		ROB_IMIE();																							//	      ROB_IMIE
		IM_PRZYGODY_S[NR]=Param_S;															//	      IM_PRZYGODY$(NR)=Param$
	}																													//	   End If
	if( TYP==3 ) {																						//	   If TYP=3
		//---bandyci---																					//	      'bandyci
		PRZYGODY[NR][P_TERMIN]=100+Rnd(100);										//	      PRZYGODY(NR,P_TERMIN)=100+Rnd(100)
		PRZYGODY[NR][P_CENA]=0;																	//	      PRZYGODY(NR,P_CENA)=0
		PRZYGODY[NR][P_NAGRODA]=4000+Rnd(2000)+LEVEL*100;				//	      PRZYGODY(NR,P_NAGRODA)=4000+Rnd(2000)+LEVEL*100
		PRZYGODY[NR][P_TEREN]=0;																//	      PRZYGODY(NR,P_TEREN)=0
		PRZYGODY[NR][P_BRON]=0;																	//	      PRZYGODY(NR,P_BRON)=0
	}																													//	   End If
	if( TYP==4 ) {																						//	   If TYP=4
		//---cora---																						//	      'córa
		PRZYGODY[NR][P_TERMIN]=100+Rnd(100);										//	      PRZYGODY(NR,P_TERMIN)=100+Rnd(100)
		PRZYGODY[NR][P_CENA]=0;																	//	      PRZYGODY(NR,P_CENA)=0
		do { _MIASTO=Rnd(49); } while( MIASTA[_MIASTO][0][M_CZYJE]==1 );//	      Repeat : MIASTO=Rnd(49) : Until MIASTA(MIASTO,0,M_CZYJE)<>1
		PRZYGODY[NR][P_NAGRODA]=_MIASTO;												//	      PRZYGODY(NR,P_NAGRODA)=MIASTO
		PRZYGODY[NR][P_BRON]=0;																	//	      PRZYGODY(NR,P_BRON)=0
		PRZYGODY[NR][P_TEREN]=0;																//	      PRZYGODY(NR,P_TEREN)=0
		ROB_IMIE();																							//	      ROB_IMIE
		IM_PRZYGODY_S[NR]=Param_S;															//	      IM_PRZYGODY$(NR)=Param$
	}																													//	   End If
	if( TYP==5 ) {																						//	   If TYP=5
		//---gora jakas tam---																	//	      'góra jakaô tam
		PRZYGODY[NR][P_TERMIN]=100+Rnd(100);										//	      PRZYGODY(NR,P_TERMIN)=100+Rnd(100)
		PRZYGODY[NR][P_CENA]=Rnd(100)+30;												//	      PRZYGODY(NR,P_CENA)=Rnd(100)+30
																														//	      'jedno z miast rnd(m_czyje)
		PRZYGODY[NR][P_NAGRODA]=_MIASTO;												//	      PRZYGODY(NR,P_NAGRODA)=MIASTO
		PRZYGODY[NR][P_TEREN]=4;																//	      PRZYGODY(NR,P_TEREN)=4
		PRZYGODY[NR][P_BRON]=0;																	//	      PRZYGODY(NR,P_BRON)=0
		ROB_IMIE();																							//	      ROB_IMIE
		IM_PRZYGODY_S[NR]=Param_S;															//	      IM_PRZYGODY$(NR)=Param$
	}																													//	   End If
	if( TYP==6 ) {																						//	   If TYP=6
		//---super mag---																			//	      'super mag
		PRZYGODY[NR][P_TERMIN]=100+Rnd(100);										//	      PRZYGODY(NR,P_TERMIN)=100+Rnd(100)
		PRZYGODY[NR][P_CENA]=Rnd(100)+10;												//	      PRZYGODY(NR,P_CENA)=Rnd(100)+10
																														//	      'jedno z miast rnd(m_czyje)
		PRZYGODY[NR][P_NAGRODA]=_MIASTO;												//	      PRZYGODY(NR,P_NAGRODA)=MIASTO
		PRZYGODY[NR][P_TEREN]=0;																//	      PRZYGODY(NR,P_TEREN)=0
		PRZYGODY[NR][P_BRON]=0;																	//	      PRZYGODY(NR,P_BRON)=0
		ROB_IMIE();																							//	      ROB_IMIE
		IM_PRZYGODY_S[NR]=Param_S;															//	      IM_PRZYGODY$(NR)=Param$
	}																													//	   End If
	if( TYP==7 ) {																						//	   If TYP=7
		//---gora paladyna ufola---															//	      'grota paladyna ufola
		PRZYGODY[NR][P_TERMIN]=100+Rnd(100);										//	      PRZYGODY(NR,P_TERMIN)=100+Rnd(100)
		PRZYGODY[NR][P_CENA]=Rnd(100)+10;												//	      PRZYGODY(NR,P_CENA)=Rnd(100)+10
																														//	      'jedno z miast rnd(m_czyje)
		PRZYGODY[NR][P_NAGRODA]=_MIASTO;												//	      PRZYGODY(NR,P_NAGRODA)=MIASTO
		PRZYGODY[NR][P_TEREN]=8;																//	      PRZYGODY(NR,P_TEREN)=8
		PRZYGODY[NR][P_BRON]=0;																	//	      PRZYGODY(NR,P_BRON)=0
		ROB_IMIE();																							//	      ROB_IMIE
		IM_PRZYGODY_S[NR]=Param_S;															//	      IM_PRZYGODY$(NR)=Param$
	}																													//	   End If
																														//
	if( TYP==8 ) {																						//	   If TYP=8
		//---magiczna ksiega---																	//	      'magiczna ksiëga
		PRZYGODY[NR][P_LEVEL]=3;																//	      PRZYGODY(NR,P_LEVEL)=3
		PRZYGODY[NR][P_TERMIN]=100+Rnd(100);										//	      PRZYGODY(NR,P_TERMIN)=100+Rnd(100)
		PRZYGODY[NR][P_CENA]=100;																//	      PRZYGODY(NR,P_CENA)=100
		PRZYGODY[NR][P_TEREN]=9;																//	      PRZYGODY(NR,P_TEREN)=9
		if( Rnd(1)==0 ) {																				//	      If Rnd(1)=0
																														//	         'GB
			PRZYGODY[NR][P_BRON]=52;															//	         PRZYGODY(NR,P_BRON)=52
		} else {																								//	      Else
																														//	         'NAW
			PRZYGODY[NR][P_BRON]=88;															//	         PRZYGODY(NR,P_BRON)=88
		}																												//	      End If
	}																													//	   End If
																														//
	if( TYP==9 ) {																						//	   If TYP=9
		//---swiatynia orkow---																	//	      'ôwiâtynia orków
		PRZYGODY[NR][P_TERMIN]=100+Rnd(100);										//	      PRZYGODY(NR,P_TERMIN)=100+Rnd(100)
		PRZYGODY[NR][P_CENA]=Rnd(20);														//	      PRZYGODY(NR,P_CENA)=Rnd(20)
		PRZYGODY[NR][P_TEREN]=9;																//	      PRZYGODY(NR,P_TEREN)=9
		PRZYGODY[NR][P_BRON]=0;																	//	      PRZYGODY(NR,P_BRON)=0
	}																													//	   End If
																														//
	if( TYP==10 ) {																						//	   If TYP=10
		//---barbarzynca na bagnach															//	      'barbrayïca na bagnach
		PRZYGODY[NR][P_TERMIN]=100+Rnd(100);										//	      PRZYGODY(NR,P_TERMIN)=100+Rnd(100)
		PRZYGODY[NR][P_CENA]=Rnd(100)+30;												//	      PRZYGODY(NR,P_CENA)=Rnd(100)+30
		PRZYGODY[NR][P_TEREN]=7;																//	      PRZYGODY(NR,P_TEREN)=7
		PRZYGODY[NR][P_BRON]=0;																	//	      PRZYGODY(NR,P_BRON)=0
		ROB_IMIE();																							//	      ROB_IMIE
		IM_PRZYGODY_S[NR]=Param_S;															//	      IM_PRZYGODY$(NR)=Param$
	}																													//	   End If
																														//
	if( TYP==11 ) {																						//	   If TYP=11
		//---wataha---																					//	      'wataha
		PRZYGODY[NR][P_TERMIN]=100+Rnd(100);										//	      PRZYGODY(NR,P_TERMIN)=100+Rnd(100)
		PRZYGODY[NR][P_CENA]=0;																	//	      PRZYGODY(NR,P_CENA)=0
		PRZYGODY[NR][P_NAGRODA]=3000*LEVEL;											//	      PRZYGODY(NR,P_NAGRODA)=3000*LEVEL
		PRZYGODY[NR][P_TEREN]=0;																//	      PRZYGODY(NR,P_TEREN)=0
		AGAIN:																									//	      AGAIN:
		RSA=Rnd(8);																							//	      RSA=Rnd(8)
		if( RSA==4 ) {																					//	      If RSA=4
																														//	         ' bez amazonek
			goto AGAIN;																						//	         Goto AGAIN
		}																												//	      End If
		PRZYGODY[NR][P_BRON]=RSA;																//	      PRZYGODY(NR,P_BRON)=RSA
		ROB_IMIE();																							//	      ROB_IMIE
		IM_PRZYGODY_S[NR]=Param_S;															//	      IM_PRZYGODY$(NR)=Param$
	}																													//	   End If
																														//
	if( TYP==12 ) {																						//	   If TYP=12
		//---jaskinia wiedzy---																	//	      'jaskinia wiedzy
		PRZYGODY[NR][P_TERMIN]=100+Rnd(100);										//	      PRZYGODY(NR,P_TERMIN)=100+Rnd(100)
		PRZYGODY[NR][P_CENA]=Rnd(100)+20;												//	      PRZYGODY(NR,P_CENA)=Rnd(100)+20
		PRZYGODY[NR][P_TEREN]=8;																//	      PRZYGODY(NR,P_TEREN)=8
	}																													//	   End If
																														//
	if( TYP==13 ) {																						//	   If TYP=13
		//---wladca chaosu---																		//	      'wîadca chaosu
		PRZYGODY[NR][P_LEVEL]=4;																//	      PRZYGODY(NR,P_LEVEL)=4
		PRZYGODY[NR][P_TERMIN]=100+Rnd(100);										//	      PRZYGODY(NR,P_TERMIN)=100+Rnd(100)
		PRZYGODY[NR][P_CENA]=500+Rnd(100);											//	      PRZYGODY(NR,P_CENA)=500+Rnd(100)
																														//	      'jedno z miast rnd(m_czyje)
		PRZYGODY[NR][P_NAGRODA]=_MIASTO;												//	      PRZYGODY(NR,P_NAGRODA)=MIASTO
		PRZYGODY[NR][P_TEREN]=10;																//	      PRZYGODY(NR,P_TEREN)=10
		PRZYGODY[NR][P_BRON]=0;																	//	      PRZYGODY(NR,P_BRON)=0
	}																													//	   End If
																														//
																														//	End Proc
}
void _PRZYGODY(aint XA,aint YA,aint NR) {
																									//	Procedure PRZYGODY[XA,YA,NR]
	aint LEVEL=0, STARAODL=0, OLD_KIER=0, I=0, X2=0, Y2=0, DX=0, DY=0,
			 KIER=0, MIASTO=0, X=0, Y=0;
	LEVEL=PRZYGODY[NR][P_LEVEL];										//	   LEVEL=PRZYGODY(NR,P_LEVEL)
	LEVEL--;																				//	   Dec LEVEL
	PRZYGODY[NR][P_LEVEL]=LEVEL;										//	   PRZYGODY(NR,P_LEVEL)=LEVEL
																									//
	if( LEVEL>0 ) {																	//	   If LEVEL>0
																									//	      'wskaû konkretnâ osobë
																									//	      'miasto wybrane zgodnie z kierunkiem przygody
		STARAODL=600;																	//	      STARAODL=600
		OLD_KIER=PRZYGODY[NR][P_KIERUNEK];						//	      OLD_KIER=PRZYGODY(NR,P_KIERUNEK)
		for(I=0;I<=49;++I) {													//	      For I=0 To 49
			X2=MIASTA[I][0][M_X];												//	         X2=MIASTA(I,0,M_X)
			Y2=MIASTA[I][0][M_Y];												//	         Y2=MIASTA(I,0,M_Y)
			DX=XA-X2;																		//	         DX=XA-X2
			DY=YA-Y2;																		//	         DY=YA-Y2
			if( Abs(DX)>=Abs(DY) ) {										//	         If Abs(DX)>=Abs(DY)
				if( DX>=0 ) {															//	            If DX>=0
					KIER=2;																	//	               KIER=2
				} else {																	//	            Else
					KIER=3;																	//	               KIER=3
				}																					//	            End If
			} else {																		//	         Else
				if( DY>=0 ) {															//	            If DY>=0
					KIER=1;																	//	               KIER=1
				} else {																	//	            Else
					KIER=0;																	//	               KIER=0
				}																					//	            End If
			}																						//	         End If
			ODL(XA,YA,X2,Y2);														//	         ODL[XA,YA,X2,Y2]
			if( ODLEG<STARAODL && KIER!=OLD_KIER && ODLEG>30+Rnd(100) ) {		//	         If ODLEG<STARAODL and KIER<>OLD_KIER and ODLEG>30+Rnd(100)
				STARAODL=ODLEG;														//	            STARAODL=ODLEG
				MIASTO=I;																	//	            MIASTO=I
			}																						//	         End If
		}																							//	      Next I
		PRZYGODY[NR][P_X]=MIASTO;											//	      PRZYGODY(NR,P_X)=MIASTO
																									//	      'osoba
		PRZYGODY[NR][P_Y]=Rnd(9)+1;										//	      PRZYGODY(NR,P_Y)=Rnd(9)+1
		DX=XA-MIASTA[MIASTO][0][M_X];									//	      DX=XA-MIASTA(MIASTO,0,M_X)
		DY=YA-MIASTA[MIASTO][0][M_Y];									//	      DY=YA-MIASTA(MIASTO,0,M_Y)
		if( Abs(DX)>=Abs(DY) ) {											//	      If Abs(DX)>=Abs(DY)
			if( DX>=0 ) {																//	         If DX>=0
				KIER=3;																		//	            KIER=3
			} else {																		//	         Else
				KIER=2;																		//	            KIER=2
			}																						//	         End If
		} else {																			//	      Else
			if( DY>=0 ) {																//	         If DY>=0
				KIER=0;																		//	            KIER=0
			} else {																		//	         Else
				KIER=1;																		//	            KIER=1
			}																						//	         End If
		}																							//	      End If
		PRZYGODY[NR][P_KIERUNEK]=KIER;								//	      PRZYGODY(NR,P_KIERUNEK)=KIER
	}																								//	   End If
	if( LEVEL==0 ) {																//	   If LEVEL=0
		X=XA+Rnd(100)-50;															//	      X=XA+Rnd(100)-50
		Y=YA+Rnd(100)-50;															//	      Y=YA+Rnd(100)-50
		PRZYGODY[NR][P_X]=X;													//	      PRZYGODY(NR,P_X)=X
		PRZYGODY[NR][P_Y]=Y;													//	      PRZYGODY(NR,P_Y)=Y
																									//	      'wskaû miejsce na mapie
																									//	      'strefa o numerze przygody
	}																								//	   End If
																									//	End Proc
}
void PRZYGODA_INFO(aint NR) {
																	//	Procedure PRZYGODA_INFO[NR]
	aint TYP=0, DL=0, ZN=0;
	astr A_S="", L_S="", R_S="";
	OKNO(70,100,180,23);						//	   OKNO[70,100,180,23]
	TYP=PRZYGODY[NR][P_TYP];				//	   TYP=PRZYGODY(NR,P_TYP)
	A_S=PRZYGODY_S[TYP][0];					//	   A$=PRZYGODY$(TYP,0)
	if( IM_PRZYGODY_S[NR] != "" ) {	//	   If IM_PRZYGODY$(NR)<>""
		DL=Len(A_S);									//	      DL=Len(A$)
		ZN=Instr(A_S,"$");						//	      ZN=Instr(A$,"$")
		if( ZN>0 ) {									//	      If ZN>0
			A_S=Minus_S(A_S,"$");				//	         A$=A$-"$"
			L_S=Left_S(A_S,ZN-1);				//	         L$=Left$(A$,ZN-1)
			R_S=Right_S(A_S,DL-ZN-1);		//	         R$=Right$(A$,DL-ZN-1)
			A_S=L_S+IM_PRZYGODY_S[NR]+R_S;//	         A$=L$+IM_PRZYGODY$(NR)+R$
		}															//	      End If
	}																//	   End If
	GADGET(OKX+4,OKY+4,172,15,A_S,31,2,30,1,-1);//	   GADGET[OKX+4,OKY+4,172,15,A$,31,2,30,1,-1]
	do {														//	   Repeat
		rysuj();
		GADGET(OKX+4,OKY+4,172,15,A_S,31,2,30,1,-1);//	   GADGET[OKX+4,OKY+4,172,15,A$,31,2,30,1,-1]
		WaitVbl();
	} while( MouseClick()!=1 );			//	   Until Mouse Click=1
	ZOKNO();												//	   ZOKNO
																	//	End Proc
}

