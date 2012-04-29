
#include "Amos.h"

#include "legion.h"
#include "lgn_sceneria.h"
#include "lgn_akcja.h"
#include "lgn_diskacs.h"
#include "lgn_ekran1.h"
#include "lgn_util.h"

PBList *pbl_sceneria = 0;
void rysuj_scenerie(void) {
	//rysujemy pole gry
	Screen(0);
	if( pbl_sceneria )
		pbl_sceneria->Draw();
	BobUpdate();
}
void rysuj_akcja(void) {
	aint scr = Screen();

	//ekran mruga na niektorych kartach graficznych, wiec czyscimy to co nie bedzie rysowane
	Gfx::Color(0.f,0.f,0.f);
	Screen(1);
	_ClearRaster(0,ScreenY()-5,640,525);

	//pole gry
	Screen(0);
	rysuj_scenerie();

	//rysujemy "patelnie"
	Screen(1);
	_restore_ekran1();

	if( IB_TEST_MODE ) {
		DbgDrawZones(0);
		DbgDrawZones(1);
	}

	Screen(scr);
}
void _RYSUJ_SCENERIE_LOSUJ2(aint &X, aint &Y, aint &LX, aint &LY, aint &LSZER, aint &WIES) {
	LOSUJ2:									//	   LOSUJ2:
	X=LX+Rnd(LSZER);				//	   X=LX+Rnd(LSZER)
	if( WIES<-1 ) {					//	   If WIES<-1
		Y=Rnd(300)+200;				//	      Y=Rnd(300)+200
	} else {								//	   Else
		Y=LY+Rnd(LSZER);			//	      Y=LY+Rnd(LSZER)
	}												//	   End If
	if( _Zone(X,Y)>120 )		//	   If Zone(X,Y)>120 : Goto LOSUJ2 : End If
		goto LOSUJ2;
	return;									//	   Return
}
aint _RYSUJ_SCENERIE_LOSUJ(aint &X, aint &Y, aint &LX, aint &LY, aint &LSZER, aint &WIES) {
													//	   LOSUJ:
	aint hrev=0;
	if( Rnd(1)==0 ) {				//	   If Rnd(1)=0
		hrev=-1;							//	      B=Hrev(B)
	}												//	   End If
	_RYSUJ_SCENERIE_LOSUJ2(X,Y,LX,LY,LSZER,WIES);
	return hrev;
}
void _RYSUJ_SCENERIE_OBCINANIE(void) {
													//   OBCINANIE:
	aint I;									//
													//   Screen Hide 1 : Screen Hide 2 : View
													//   Screen 2
	for(I=BUBY+4;I<=BUBY+163;++I) {	//   For I=BUBY+4 To BUBY+163
		//### - ulepszenie
		//TODO: mozna w ramach ulepszenia zrobic to ladniej
		//zamiast ustawiac na 32 od góry obciaæ np 12 od dolu
		//wtedy wyzsze postacie beda nadal wyzsze ;-)
		_ClipImage(-1,I,0,-12);
		//_ClipImage(-1,I,0,32);
													//      Cls 0
													//      Paste Bob 0,0,I
													//      Get Sprite I,0,0 To 32,32 : Wait Vbl
													//      Hot Spot I,$12
	}												//   Next
													//   Screen Show 1
													//   Screen 0
													//   Return
}
void RYSUJ_SCENERIE(aint TYP,aint WIES) {
	//	Procedure RYSUJ_SCENERIE[TYP,WIES]
	//scenerie nie rysujemy a zapamietujemy na liscie
	if( pbl_sceneria ) {
		delete pbl_sceneria;
	}
	pbl_sceneria = _NewPBList();
	PBListOnoff(true);
	rysuj_ekran_ptr = rysuj_akcja;

	aint LX=0, LY=0, LSZER=0, LWYS=0, D=0, I=0, X=0, Y=0, R=0, CO=0,
			 NR=0, B=0, J=0, X2=0, ZX1=0, ZY1=0, ZX2=0, ZY2=0, ZX3=0, ZX4=0, ZY3=0, ZY4=0,
			 BB=0, XB=0, YB=0, B2=0, RAN=0, LOS=0;

	SCENERIA=TYP;												//	   SCENERIA=TYP
	Screen(0);													//	   Screen 0
																			//	   Screen Hide 0
																			//	   'Auto View Off
	Gfx::Color(0,0,0);									//	   Cls 20
	Cls();
	LX=20; LY=20; LSZER=600; LWYS=490;	//	   LX=20 : LY=20 : LSZER=600 : LWYS=490
	if( WIES==-1 ) {										//	   If WIES=-1
		D=1;															//	      D=1
	} else {														//	   Else
		D=2;															//	      D=2
	}																		//	   End If
	if( WIES>-1 )												//	   If WIES>-1 : FUNDAMENTY[WIES] : End If
		FUNDAMENTY(WIES);

LOG("Sceneria typ="+toString(TYP));

	//---las---													//	   'las
	if( TYP==1 ) {											//	   If TYP=1
		_LOAD(KAT_S+"dane/scen-las","dane:scen-las","Dane",1);								//	      _LOAD[KAT$+"dane/scen-las","dane:scen-las","Dane",1] : Get Bob Palette
		_LOAD(KAT_S+"dane/muzyka/mus-las","dane:muzyka/mus-las","Dane",7);		//	      _LOAD[KAT$+"dane/muzyka/mus-las","dane:muzyka/mus-las","Dane",7]
		Music(1);													//	      Music 1
		aint e=Rnd(12)+1;
		for(I=0;I<=e;++I) {								//	      For I=1 To Rnd(12)+1
			X=Rnd(47); Y=Rnd(3);						//	         X=Rnd(47) : Y=Rnd(3)
			R=Rnd(10);											//	         R=Rnd(10)
			if( R<5 ) CO=37;								//	         If R<5 : CO=37 : End If
			if( R==5 ) CO=36;								//	         If R=5 : CO=36 : End If
			if( R==6 ) CO=36;								//	         If R=6 : CO=36 : End If
			if( R==7 ) CO=32;								//	         If R=7 : CO=32 : End If
			if( R==8 ) CO=32;								//	         If R=8 : CO=32 : End If
			if( R==9 ) CO=39;								//	         If R=9 : C0=39 : End If
			if( R==10 ) CO=0;								//	         If R=10 : CO=0 : End If
			GLEBA[X][Y]=CO;									//	         GLEBA(X,Y)=CO
		}																	//	      Next I
																			//
		for(Y=0;Y<=11;++Y) {							//	      For Y=0 To 11
			for(X=0;X<=15;++X) {						//	         For X=0 To 15
				PasteBob(X*50,Y*50,BIBY+1,1.005);		//	            Paste Bob X*50,Y*50,BIBY+1
			}																//	         Next X
		}																	//	      Next Y
																			//
		WIDOCZNOSC=150;										//	      WIDOCZNOSC=150
		for(I=0;I<=30;++I) {							//	      For I=0 To 30
			X=Rnd(620)+20;									//	         X=Rnd(620)+20
			Y=I*20;													//	         Y=(I*20)
			NR=Rnd(1)+5;										//	         NR=Rnd(1)+5
			PasteBob(X,Y,BIBY+NR);					//	         Paste Bob X,Y,BIBY+NR
		}																	//	      Next I
		for(I=0;I<=15/D;++I) {						//	      For I=0 To 15/D
			B=Rnd(2)+2;											//	         B=Rnd(2)+2
			_RYSUJ_SCENERIE_LOSUJ(X,Y,LX,LY,LSZER,WIES);//	         Gosub LOSUJ
			PasteBob(X,Y,BIBY+B);						//	         Paste Bob X,Y,BIBY+B
			SetZone(60+I,X+4,Y+4,X+28,Y+22);//	         Set Zone 60+I,X+4,Y+4 To X+28,Y+22
																			//	         '         Ink 10 : Box X+4,Y+4 To X+28,Y+22
		}																	//	      Next I
		if( WIES==-1 ) {									//	      If WIES=-1
			for(J=0;J<=3;++J) {							//	         For J=0 To 3
				X2=Rnd(640);									//	            X2=Rnd(640)
				for(I=0;I<=18;++I) {					//	            For I=0 To 18
					X=X2+Rnd(100)-50;						//	               X=X2+Rnd(100)-50
					Y=J*100+I*4-60;							//	               Y=(J*100)+(I*4)-60
					NR=Rnd(2)+7;								//	               NR=Rnd(2)+7
					PasteBob(X+40,Y+120,NR+BIBY);			//	               Paste Bob X,Y,NR+BIBY
				}															//	            Next I
				ZX1=X2-50; ZY1=J*100-60;			//	            ZX1=X2-50 : ZY1=(J*100)-60
				ZX2=ZX1+190; ZY2=ZY1+130;			//	            ZX2=ZX1+190 : ZY2=ZY1+130
				ZX3=ZX1+40; ZX4=ZX2-45;				//	            ZX3=ZX1+40 : ZX4=ZX2-45
				ZY3=ZY1+130; ZY4=ZY1+180;			//							ZY3=ZY1+130 : ZY4=ZY1+180
				if( ZX1<0 ) ZX1=0;						//	            If ZX1<0 : ZX1=0 : End If
				if( ZY1<0 ) ZY1=0;						//	            If ZY1<0 : ZY1=0 : End If
				if( ZX2>640 ) ZX2=640;				//	            If ZX2>640 : ZX2=640 : End If
				if( ZY2>512 ) ZY2=512;				//	            If ZY2>512 : ZY2=512 : End If
				if( ZX3<0 ) ZX3=0;						//	            If ZX3<0 : ZX3=0 : End If
				if( ZY3<0 ) ZY3=0;						//	            If ZY3<0 : ZY3=0 : End If
				if( ZX4>640 ) ZX4=640;				//	            If ZX4>640 : ZX4=640 : End If
				if( ZY4>512 ) ZY4=512;				//	            If ZY4>512 : ZY4=512 : End If
																			//
																			//	            '         Ink 10 : Box ZX3,ZY3 To ZX4,ZY4
																			//	            '         Ink 2 : Box ZX1,ZY1 To ZX2,ZY2
				SetZone(90+J,ZX1,ZY1,ZX2,ZY2);//	            Set Zone 90+J,ZX1,ZY1 To ZX2,ZY2
				SetZone(94+J,ZX3,ZY3,ZX4,ZY4);//	            Set Zone 94+J,ZX3,ZY3 To ZX4,ZY4
			}																//	         Next J
		}																	//	      End If
	}																		//	   End If

	//---step---												//	   'Step
	if( TYP==2 ) {											//	   If TYP=2
		WIDOCZNOSC=500;										//	      WIDOCZNOSC=500
		_LOAD(KAT_S+"dane/scen-step","dane:scen-step","Dane",1);							//	      _LOAD[KAT$+"dane/scen-step","dane:scen-step","Dane",1] : Get Bob Palette
		_LOAD(KAT_S+"dane/muzyka/mus-step","dane:muzyka/mus-step","Dane",7);		//	      _LOAD[KAT$+"dane/muzyka/mus-step","dane:muzyka/mus-step","Dane",7]
		Music(1);													//	      Music 1
		for(I=1;I<=Rnd(6)+1;I++) {				//	      For I=1 To Rnd(6)+1
			X=Rnd(47); Y=Rnd(3);						//	         X=Rnd(47) : Y=Rnd(3)
			R=Rnd(10);											//	         R=Rnd(10)
			if( R<5 ) CO=37;								//	         If R<5 : CO=37 : End If
			if( R==5 ) CO=36;								//	         If R=5 : CO=36 : End If
			if( R==6 ) CO=36;								//	         If R=6 : CO=36 : End If
			if( R==7 ) CO=32;								//	         If R=7 : CO=32 : End If
			if( R==8 ) CO=32;								//	         If R=8 : CO=32 : End If
			if( R==9 ) CO=39;								//	         If R=9 : C0=39 : End If
			if( R==10 ) CO=0;								//	         If R=10 : CO=0 : End If
			GLEBA[X][Y]=CO;									//	         GLEBA(X,Y)=CO
		}																	//	      Next I
																			//
		for( Y=0;Y<=11;++Y ) {						//	      For Y=0 To 11
			for( X=0;X<=15;++X ) {					//	         For X=0 To 15
				PasteBob(X*50,Y*50,BIBY+1,1.005);		//	            Paste Bob X*50,Y*50,BIBY+1
			}																//	         Next X
		}																	//	      Next Y
		for( I=1; I<=20; ++I ) {					//	      For I=1 To 20
			B=BIBY+2+Rnd(1);								//	         B=BIBY+2+Rnd(1)
			_RYSUJ_SCENERIE_LOSUJ(X,Y,LX,LY,LSZER,WIES);	//	         Gosub LOSUJ
			PasteBob(X,Y,B);								//	         Paste Bob X,Y,B
		}																	//	      Next
		for( I=1; I<=3; ++I ) {						//	      For I=1 To 3
			B=BIBY+4;												//	         B=BIBY+4
			_RYSUJ_SCENERIE_LOSUJ2(X,Y,LX,LY,LSZER,WIES);	//	         Gosub LOSUJ2
			PasteBob(X,Y,B);								//	         Paste Bob X,Y,B
			SetZone(60+I,X+4,Y,X+60,Y+36);	//	         Set Zone 60+I,X+4,Y To X+60,Y+36
		}																	//	      Next
																			//	      '      For I=1 To 2
																			//	      '         B=BIBY+5
																			//	      '         Gosub LOSUJ2
																			//	      '         Bob 60+I,X,Y,B
																			//	      '      Next
	}																		//	   End If

	//---skaly---												//	   'skaîy
	if(	TYP==4 ) {											//	   If TYP=4
		WIDOCZNOSC=250;										//	      WIDOCZNOSC=250
		_LOAD(KAT_S+"dane/scen-skaly","dane:scen-skaly","Dane",1);						//	      _LOAD[KAT$+"dane/scen-skaly","dane:scen-skaly","Dane",1] : Get Bob Palette
		_LOAD(KAT_S+"dane/muzyka/mus-gory","dane:muzyka/mus-gory","Dane",7);	//	      _LOAD[KAT$+"dane/muzyka/mus-gory","dane:muzyka/mus-gory","Dane",7]
		Music(1);													//	      Music 1
		for( I=1;I<=50;++I) {							//	      For I=1 To 50 : X=Rnd(47) : Y=Rnd(3) : GLEBA(X,Y)=64+Rnd(4) : Next I
			X=Rnd(47); Y=Rnd(3);
			GLEBA[X][Y]=64+Rnd(4);
		}
		for( Y=0;Y<=10;++Y ) {						//	      For Y=0 To 10
			for( X=0;X<=12;++X ) {					//	         For X=0 To 12
				PasteBob(X*50,Y*50,BIBY+1,1.005);		//	            Paste Bob X*50,Y*50,BIBY+1
			}																//	         Next X
		}																	//	      Next Y
		for( I=1;I<=6;++I ) {							//	      For I=1 To 6
			PasteBob(Rnd(600)+20,Rnd(490)+20,BIBY+10);	//	         Paste Bob Rnd(600)+20,Rnd(490)+20,BIBY+10
		}																	//	      Next I
		for( I=1;I<=50;++I ) {						//	      For I=1 To 50 : B=BIBY+2+Rnd(1) : Gosub LOSUJ : Paste Bob X,Y,B : Next I
			_RYSUJ_SCENERIE_LOSUJ(X,Y,LX,LY,LSZER,WIES);
			PasteBob(X,Y,B);
		}
		for( I=1;I<=5/D;++I ) {						//	      For I=1 To 5/D
			B=BIBY+7+Rnd(1);								//	         B=BIBY+7+Rnd(1)
			_RYSUJ_SCENERIE_LOSUJ(X,Y,LX,LY,LSZER,WIES);	//	         Gosub LOSUJ
			PasteBob(X,Y,B);								//	         Paste Bob X,Y,B
			SetZone(30+I,X+20,Y+12,X+90,Y+37);//	         Set Zone 30+I,X+20,Y+12 To X+90,Y+37
																			//	         '         Ink 3 : Box X+20,Y+12 To X+90,Y+37
			PLAPKI[I][0]=1;									//	         PLAPKI(I,0)=1
		}																	//	      Next I
		for( I=1;I<=5/D;++I ) {						//	      For I=1 To 5/D
			B=BIBY+6;												//	         B=BIBY+6
			_RYSUJ_SCENERIE_LOSUJ(X,Y,LX,LY,LSZER,WIES);	//	         Gosub LOSUJ
			PasteBob(X,Y,B);								//	         Paste Bob X,Y,B
			SetZone(35+I,X+16,Y+10,X+50,Y+25);//	         Set Zone 35+I,X+16,Y+10 To X+50,Y+25
																			//	         '         Ink 3 : Box X+16,Y+10 To X+50,Y+25
			PLAPKI[I+5][0]=1;								//	         PLAPKI(I+5,0)=1
		}																	//	      Next I
		for( I=1;I<=10/D;++I ) {					//	      For I=1 To 20/(D*2)
			B=BIBY+4+Rnd(1);								//	         B=BIBY+4+Rnd(1)
			_RYSUJ_SCENERIE_LOSUJ(X,Y,LX,LY,LSZER,WIES);//	         Gosub LOSUJ
			PasteBob(X,Y,B);								//	         Paste Bob X,Y,B
			SetZone(60+I,X,Y,X+48,Y+36);		//	         Set Zone 60+I,X,Y To X+48,Y+36
		}																	//	      Next I
		for( I=1;I<=5/D;++I ) {						//	      For I=1 To 5/D
			B=BIBY+9;												//	         B=BIBY+9
			_RYSUJ_SCENERIE_LOSUJ(X,Y,LX,LY,LSZER,WIES);//	         Gosub LOSUJ
			PasteBob(X,Y,B);								//	         Paste Bob X,Y,B
			SetZone(85+I,X+10,Y,X+86,Y+62);	//	         Set Zone 85+I,X+10,Y To X+86,Y+62
		}																	//	      Next I
	}																		//	   End If

	//---pustynia---										//	   'pustynia
	if( TYP==3 ) {											//	   If TYP=3
		WIDOCZNOSC=500;										//	      WIDOCZNOSC=500
		_LOAD(KAT_S+"dane/scen-pustynia","dane:scen-pustynia","Dane",1);																	//	      _LOAD[KAT$+"dane/scen-pustynia","dane:scen-pustynia","Dane",1] : Get Bob Palette
		_LOAD(KAT_S+"dane/muzyka/mus-pustnia","dane:muzyka/mus-pustnia","Dane",7);																	//	      _LOAD[KAT$+"dane/muzyka/mus-pustnia","dane:muzyka/mus-pustnia","Dane",7]
		for( I=1;I<=Rnd(2)+1;++I ) {			//	      For I=1 To Rnd(2)+1
			X=Rnd(47); Y=Rnd(3);						//	         X=Rnd(47) : Y=Rnd(3)
			//!!! blad - powinno byc 0 a nie 9
			//R=Rnd(2);												//	         R=Rnd(2)
			//if( R==1 ) CO=35;								//	         If R=1 : CO=35 : End If
			//if( R==9 ) CO=39;								//	         If R=9 : CO=39 : End If
			R=Rnd(1);												//	         R=Rnd(2)
			if( R==0 ) CO=35;								//	         If R=1 : CO=35 : End If
			if( R==1 ) CO=39;								//	         If R=9 : CO=39 : End If
			GLEBA[X][Y]=CO;									//	         GLEBA(X,Y)=CO
		}																	//	      Next I
																			//
		Music(1);													//	      Music 1
		for(Y=0;Y<=10;++Y) {							//	      For Y=0 To 10
			for(X=0;X<=12;++X) {						//	         For X=0 To 12
				PasteBob(X*50,Y*50,BIBY+1,1.005);		//	            Paste Bob X*50,Y*50,BIBY+1
			}																//	         Next X
		}																	//	      Next Y
		for( I=1; I<=40; ++I ) {					//	      For I=1 To 40
			B=BIBY+2+Rnd(3);								//	         B=BIBY+2+Rnd(3)
			_RYSUJ_SCENERIE_LOSUJ(X,Y,LX,LY,LSZER,WIES);//	         Gosub LOSUJ
			PasteBob(X,Y,B);								//	         Paste Bob X,Y,B
		}																	//	      Next I
		for( I=1; I<=10; ++I ) {					//	      For I=1 To 10
			B=BIBY+6;												//	         B=BIBY+6
			_RYSUJ_SCENERIE_LOSUJ(X,Y,LX,LY,LSZER,WIES);//	         Gosub LOSUJ
			PasteBob(X,Y,B);								//	         Paste Bob X,Y,B
		}																	//	      Next I
		for( I=1; I<=10/D; ++I ) {				//	      For I=1 To 10/D
			B=BIBY+7+Rnd(1);								//	         B=BIBY+7+Rnd(1)
			_RYSUJ_SCENERIE_LOSUJ(X,Y,LX,LY,LSZER,WIES);//	         Gosub LOSUJ
			PasteBob(X,Y,B);								//	         Paste Bob X,Y,B
			SetZone(60+I,X,Y,X+48,Y+35);		//	         Set Zone 60+I,X,Y To X+48,Y+35
		}																	//	      Next I
		for( I=1; I<=5/D; ++I ) {					//	      For I=1 To 5/D
			B=BIBY+9;												//	         B=BIBY+9
			LAB_AG1:												//	         AG1:
			_RYSUJ_SCENERIE_LOSUJ(X,Y,LX,LY,LSZER,WIES);//	         Gosub LOSUJ
			if( _Zone(X+60,Y+40)>0 ) goto LAB_AG1;//	         If Zone(X+60,Y+40)>0 : Goto AG1 : End If
			PasteBob(X,Y,B);								//	         Paste Bob X,Y,B
			SetZone(70+I,X,Y,X+64,Y+45);		//	         Set Zone 70+I,X,Y To X+64,Y+45
		}																	//	      Next I
																			//
	}																		//	   End If

	//---lodowiec---										//	   'lodowiec
	if( TYP==5 ) {											//	   If TYP=5
		WIDOCZNOSC=400;										//	      WIDOCZNOSC=400
		_LOAD(KAT_S+"dane/scen-lodowiec","dane:scen-lodowiec","Dane",1);																	//	      _LOAD[KAT$+"dane/scen-lodowiec","dane:scen-lodowiec","Dane",1] : Get Bob Palette
		_LOAD(KAT_S+"dane/muzyka/mus-zima","dane:muzyka/mus-zima","Dane",7);																	//	      _LOAD[KAT$+"dane/muzyka/mus-zima","dane:muzyka/mus-zima","Dane",7]
		Music(1);													//	      Music 1
																			//	      'zimno----------------
		for(I=1;I<=10;++I) {							//	      For I=1 To 10
			if(ARMIA[ARM][I][TE]>0) {				//	         If ARMIA(ARM,I,TE)>0
				if( ARMIA[ARM][I][TNOGI]==0	&& ARMIA[ARM][I][TKORP]==0 ) {//	            If ARMIA(ARM,I,TNOGI)=0 and ARMIA(ARM,I,TKORP)=0
					//!!! BLAD
					Add(ARMIA[ARM][I][TE],-Rnd(10)-10,5,ARMIA[ARM][I][TE]);//	               Add ARMIA(ARM,I,TE),-Rnd(10)-10,5 To ARMIA(ARM,I,TE)
					//!!! powinno byc
					//ARMIA[ARM][I][TE] -= Rnd(10)+10;
					//clipl(ARMIA[ARM][I][TE],5);
				}															//	            End If
			}																//	         End If
		}																	//	      Next
																			//	      '---------------------
		for(Y=0;Y<=10;++Y) {							//	      For Y=0 To 10
			for(X=0;X<=12;++X) {						//	         For X=0 To 12
				PasteBob(X*50,Y*50,BIBY+1,1.005);//	            Paste Bob X*50,Y*50,BIBY+1
			}																//	         Next X
		}																	//	      Next Y
		for(I=1;I<=30;++I) {							//	      For I=1 To 30
			B=BIBY+2;												//	         B=BIBY+2
			_RYSUJ_SCENERIE_LOSUJ(X,Y,LX,LY,LSZER,WIES);//	         Gosub LOSUJ
			PasteBob(X,Y,B);								//	         Paste Bob X,Y,B
		}																	//	      Next I
		for(I=1;I<=15;++I) {							//	      For I=1 To 15
			B=BIBY+3;												//	         B=BIBY+3
			_RYSUJ_SCENERIE_LOSUJ(X,Y,LX,LY,LSZER,WIES);//	         Gosub LOSUJ
			PasteBob(X,Y,B);								//	         Paste Bob X,Y,B
		}																	//	      Next I
		for(I=1;I<=5/D;++I) {							//	      For I=1 To 5/D
			B=BIBY+6;												//	         B=BIBY+6
			_RYSUJ_SCENERIE_LOSUJ(X,Y,LX,LY,LSZER,WIES);//	         Gosub LOSUJ
			PasteBob(X,Y,B);								//	         Paste Bob X,Y,B
			SetZone(30+I,X+8,Y,X+60,Y+40);	//	         Set Zone 30+I,X+8,Y To X+60,Y+40
			PLAPKI[I][0]=3;									//	         PLAPKI(I,0)=3
		}																	//	      Next I
		for(I=1;I<=10/D;++I) {						//	      For I=1 To 10/D
			B=BIBY+4;												//	         B=BIBY+4
			_RYSUJ_SCENERIE_LOSUJ2(X,Y,LX,LY,LSZER,WIES);//	         Gosub LOSUJ2
			PasteBob(X,Y,B);								//	         Paste Bob X,Y,B
			SetZone(65+I,X,Y,X+32,Y+40);		//	         Set Zone 65+I,X,Y To X+32,Y+40
		}																	//	      Next I
		B=BIBY+7;													//	      B=BIBY+7
		_RYSUJ_SCENERIE_LOSUJ2(X,Y,LX,LY,LSZER,WIES);//	         Gosub LOSUJ2
		PasteBob(X,Y,B);									//	      Paste Bob X,Y,B
		SetZone(65+I,X,Y,X+64,Y+82);			//	      Set Zone 65+I,X,Y To X+64,Y+82
		if( WIES==-1 ) {									//	      If WIES=-1
			for(J=0;J<=3;++J) {							//	         For J=0 To 3
				X2=Rnd(640);									//	            X2=Rnd(640)
				for(I=0;I<=10;++I) {					//	            For I=0 To 10
					X=X2+Rnd(80)-40;						//	               X=X2+Rnd(80)-40
					Y=(J*100)+(I*4)-60;					//	               Y=(J*100)+(I*4)-60
					B=BIBY+5;										//	               B=BIBY+5
					PasteBob(X,Y,B);						//	               Paste Bob X,Y,B
				}															//	            Next I
				ZX1=X2-30; ZY1=(J*100)-50;		//	            ZX1=X2-30 : ZY1=(J*100)-50
				ZX2=ZX1+100; ZY2=ZY1+100;			//	            ZX2=ZX1+100 : ZY2=ZY1+100
				if( ZX1<0 ) ZX1=0;						//	            If ZX1<0 : ZX1=0 : End If
				if( ZY1<0 ) ZY1=0;						//	            If ZY1<0 : ZY1=0 : End If
				if( ZX2>640 ) ZX2=640;				//	            If ZX2>640 : ZX2=640 : End If
				if( ZY2>512 ) ZY2=512;				//	            If ZY2>512 : ZY2=512 : End If
																			//	            'Ink 10 : Box ZX3,ZY3 To ZX4,ZY4
																			//	            'Ink 2 : Box ZX1,ZY1 To ZX2,ZY2
				SetZone(90+J,ZX1,ZY1,ZX2,ZY2);//	            Set Zone 90+J,ZX1,ZY1 To ZX2,ZY2
			}																//	         Next J
		}																	//	      End If
	}																		//	   End If

	//---bagna---												//	   'bagna
	if( TYP==7 ) {											//	   If TYP=7
		WIDOCZNOSC=250;										//	      WIDOCZNOSC=250
		_RYSUJ_SCENERIE_OBCINANIE();			//	      Gosub OBCINANIE
		_LOAD(KAT_S+"dane/scen-bagno","dane:scen-bagno","Dane",1);							//	      _LOAD[KAT$+"dane/scen-bagno","dane:scen-bagno","Dane",1] : Get Bob Palette
		_LOAD(KAT_S+"dane/muzyka/mus-bagna","dane:muzyka/mus-bagna","Dane",7);	//	      _LOAD[KAT$+"dane/muzyka/mus-bagna","dane:muzyka/mus-bagna","Dane",7]
		Music(1);													//	      Music 1
		aint r=Rnd(10)+1;
		for(I=1;I<=r;++I) {								//	      For I=1 To Rnd(10)+1
			X=Rnd(47); Y=Rnd(3);						//	         X=Rnd(47) : Y=Rnd(3)
			//!!! blad w losowaniu
			//R=Rnd(2);												//	         R=Rnd(2)
			//if( R==1 ) CO=34;								//	         If R=1 : CO=34 : End If
			//if( R==9 ) CO=33;								//	         If R=9 : CO=33 : End If
			R=Rnd(1);												//	         R=Rnd(2)
			if( R==1 ) CO=34;								//	         If R=1 : CO=34 : End If
			if( R==0 ) CO=33;								//	         If R=9 : CO=33 : End If
			GLEBA[X][Y]=CO;									//	         GLEBA(X,Y)=CO
		}																	//	      Next I
																			//
		for(Y=0;Y<=11;++Y) {							//	      For Y=0 To 11
			for(X=0;X<=15;++X) {						//	         For X=0 To 15
				PasteBob(X*50,Y*50,BIBY+1,1.005);		//	            Paste Bob X*50,Y*50,BIBY+1
			}																//	         Next X
		}																	//	      Next Y
		for(I=1;I<=15;++I) {							//	      For I=1 To 15
			B=BIBY+2+Rnd(1);								//	         B=BIBY+2+Rnd(1)
			_RYSUJ_SCENERIE_LOSUJ(X,Y,LX,LY,LSZER,WIES);//	         Gosub LOSUJ
			PasteBob(X,Y,B);								//	         Paste Bob X,Y,B
		}																	//	      Next
		for(I=1;I<=2;++I) {								//	      For I=1 To 2
			B=BIBY+4;												//	         B=BIBY+4
			_RYSUJ_SCENERIE_LOSUJ2(X,Y,LX,LY,LSZER,WIES);//	         Gosub LOSUJ2
			PasteBob(X,Y,B);								//	         Paste Bob X,Y,B
			SetZone(60+I,X+25,Y,X+54,Y+20);	//	         Set Zone 60+I,X+25,Y To X+54,Y+20
		}																	//	      Next
		for(I=1;I<=3;++I) {								//	      For I=1 To 3
			B=BIBY+5;												//	         B=BIBY+5
			_RYSUJ_SCENERIE_LOSUJ2(X,Y,LX,LY,LSZER,WIES);//	         Gosub LOSUJ2
			PasteBob(X,Y,B);								//	         Paste Bob X,Y,B
			SetZone(62+I,X+15,Y,X+35,Y+30);	//	         Set Zone 62+I,X+15,Y To X+35,Y+30
		}																	//	      Next
		for(I=1;I<=6;++I) {								//	      For I=1 To 6
			B=BIBY+6;												//	         B=BIBY+6
			_RYSUJ_SCENERIE_LOSUJ(X,Y,LX,LY,LSZER,WIES);//	         Gosub LOSUJ
			PasteBob(X,Y,B);								//	         Paste Bob X,Y,B
			SetZone(65+I,X+4,Y,X+44,Y+40);	//	         Set Zone 65+I,X+4,Y To X+44,Y+40
		}																	//	      Next
		for(I=1;I<=5;++I) {								//	      For I=1 To 5
			_RYSUJ_SCENERIE_LOSUJ2(X,Y,LX,LY,LSZER,WIES);//	         Gosub LOSUJ2
			SetZone(30+I,X,Y,X+64,Y+48);		//	         Set Zone 30+I,X,Y To X+64,Y+48
			PLAPKI[I][0]=2;									//	         PLAPKI(I,0)=2
																			//	         '         Ink 3 : Box X,Y To X+64,Y+48
		}																	//	      Next
	}																		//	   End If

																			//
	//---jaskinia---										//	   'jaskinia
	if( TYP==8 ) {											//	   If TYP=8
		WIDOCZNOSC=100;										//	      WIDOCZNOSC=100
		_LOAD(KAT_S+"dane/scen-jaskinia","dane:scen-jaskinia","Dane",1);							//	      _LOAD[KAT$+"dane/scen-jaskinia","dane:scen-jaskinia","Dane",1] : Get Bob Palette
		_LOAD(KAT_S+"dane/muzyka/mus-jaskinia","dane:muzyka/mus-jaskinia","Dane",7);	//	      _LOAD[KAT$+"dane/muzyka/mus-jaskinia","dane:muzyka/mus-jaskinia","Dane",7]
		LX=40; LSZER=530; LY=75; LWYS=470;//	      LX=40 : LSZER=530 : LY=75 : LWYS=470
		Music(1);													//	      Music 1
		for(Y=0;Y<=6;++Y) {								//	      For Y=0 To 6
			for(X=0;X<=4;++X) {							//	         For X=0 To 4
				PasteBob(X*144,Y*75,BIBY+1,1.005);//	            Paste Bob X*144,Y*75,BIBY+1
			}																//	         Next
		}																	//	      Next
																			//	      'rozrzucanie zîota
		for(I=1;I<=Rnd(8)+2;++I) {				//	      For I=1 To Rnd(8)+2
			X=Rnd(29)+70; Y=Rnd(3);					//	         X=Rnd(29)+70 : Y=Rnd(3)
			BB=BIBY+12;											//	         BB=BIBY+12
			CO=Rnd(3)+80;										//	         CO=Rnd(3)+80
			if( Rnd(3)==1 ) {								//	         If Rnd(3)=1
				CO=Rnd(MX_WEAPON);						//	            CO=Rnd(MX_WEAPON)
				BB=BIBY+11;										//	            BB=BIBY+11
			}																//	         End If
			GLEBA[X][Y]=CO;									//	         GLEBA(X,Y)=CO
			XB=(X%10)*64+Rnd(30);						//	         XB=(X mod 10)*64+Rnd(30)
			YB=(X/10)*50+Rnd(20);						//	         YB=(X/10)*50+Rnd(20)
			PasteBob(XB,YB,BB);							//	         Paste Bob XB,YB,BB
		}																	//	      Next I
		for(I=0;I<=1;++I) {								//	      For I=0 To 1 : Paste Bob I*112,0,BIBY+10 : Next : Paste Bob 200,-10,BIBY+9
			PasteBob(I*112,0,BIBY+10);
		}
		PasteBob(200,-10,BIBY+9);
		SetZone(60,0,0,230,70);						//	      Set Zone 60,0,0 To 230,70
		for(I=4;I<=5;++I) {								//	      For I=4 To 5 : Paste Bob I*112,0,BIBY+10 : Next : Paste Bob 420,-10,Hrev(BIBY+9)
			PasteBob(I*112,0,BIBY+10);
		}
		PasteBob(420,-10,Hrev(BIBY+9));
		SetZone(61,420,0,640,70);					//	      Set Zone 61,420,0 To 640,70
		for(I=0;I<=15;++I) {							//	      For I=0 To 15 : Paste Bob 0,(I*30)+Rnd(10),BIBY+9 : Next
			PasteBob(0,(I*30)+Rnd(10),BIBY+9);
		}
		SetZone(62,0,0,40,512);						//	      Set Zone 62,0,0 To 40,512
		B2=Hrev(BIBY+9);									//	      B2=Hrev(BIBY+9)
		for(I=0;I<=15;++I) {							//	      For I=0 To 15 : Paste Bob 600,(I*30)+Rnd(10),B2 : Next
			PasteBob(600,(I*30)+Rnd(10),B2);
		}
		SetZone(63,600,0,640,512);				//	      Set Zone 63,600,0 To 640,512
		for(I=1;I<=40;++I ) {							//	      For I=1 To 40
			_RYSUJ_SCENERIE_LOSUJ2(X,Y,LX,LY,LSZER,WIES);//	         Gosub LOSUJ2
			PasteBob(X,Y,BIBY+2+Rnd(3));		//	         Paste Bob X,Y,BIBY+2+Rnd(3)
		}																	//	      Next
		for(I=1;I<=10;++I) {							//	      For I=1 To 10
			_RYSUJ_SCENERIE_LOSUJ2(X,Y,LX,LY,LSZER,WIES);//	         Gosub LOSUJ2
			PasteBob(X,Y,BIBY+8);						//	         Paste Bob X,Y,BIBY+8
			SetZone(64+I,X,Y,X+32,Y+28);		//	         Set Zone 64+I,X,Y To X+32,Y+28
		}																	//	      Next
		for(J=1;J<=4;++J) {								//	      For J=1 To 4
			X2=Rnd(640);										//	         X2=Rnd(640)
			for(I=0;I<=30;++I) {						//	         For I=0 To 30
				X=X2+Rnd(60)-30;							//	            X=X2+Rnd(60)-30
				Y=(J*80)+(I*2)-60;						//	            Y=(J*80)+(I*2)-60
				B=BIBY+7;											//	            B=BIBY+7
				PasteBob(X,Y,B);							//	            Paste Bob X,Y,B
			}																//	         Next I
			ZX1=X2-15; ZY1=(J*80)-50;				//	         ZX1=X2-15 : ZY1=(J*80)-50
			ZX2=ZX1+65; ZY2=ZY1+80;					//	         ZX2=ZX1+65 : ZY2=ZY1+80
			clipl(ZX1,0);										//	         If ZX1<0 : ZX1=0 : End If
			clipl(ZY1,0);										//	         If ZY1<0 : ZY1=0 : End If
			clipu(ZX2,640);									//	         If ZX2>640 : ZX2=640 : End If
			clipu(ZY2,512);									//	         If ZY2>512 : ZY2=512 : End If
																			//	         'Ink 10 : Box ZX3,ZY3 To ZX4,ZY4
																			//	         '            Ink 2 : Box ZX1,ZY1 To ZX2,ZY2
			SetZone(80+J,ZX1,ZY1,ZX2,ZY2);	//	         Set Zone 80+J,ZX1,ZY1 To ZX2,ZY2
		}																	//	      Next J
																			//
	}																		//	   End If

	if( TYP==9 ) {											//	   If TYP=9
																			//	      'grobowiec
		WIDOCZNOSC=120;																	//	      WIDOCZNOSC=120
		_LOAD(KAT_S+"dane/scen-grobowiec","dane:scen-grobowiec","Dane",1);																	//	      _LOAD[KAT$+"dane/scen-grobowiec","dane:scen-grobowiec","Dane",1] : Get Bob Palette
		_LOAD(KAT_S+"dane/muzyka/mus-jaskinia","dane:muzyka/mus-jaskinia","Dane",7);																	//	      _LOAD[KAT$+"dane/muzyka/mus-jaskinia","dane:muzyka/mus-jaskinia","Dane",7]
		Music(1);																	//	      Music 1
		for(Y=0;Y<=10;++Y) {																	//	      For Y=0 To 10
			for(X=0;X<=10;++X) {																//	         For X=0 To 10
				PasteBob(X*60,Y*52,BIBY+1,1.005);															//	            Paste Bob X*60,Y*52,BIBY+1
			}																//	         Next
		}																	//	      Next
		for(I=1;I<=50;++I) {																	//	      For I=1 To 50 : Gosub LOSUJ2 : Paste Bob X,Y,BIBY+2 : Next
			_RYSUJ_SCENERIE_LOSUJ2(X,Y,LX,LY,LSZER,WIES);
			PasteBob(X,Y,BIBY+2);
		}
		for(I=1;I<=25;++I) {																	//	      For I=1 To 25 : Gosub LOSUJ2 : Paste Bob X,Y,BIBY+3 : Next
			_RYSUJ_SCENERIE_LOSUJ2(X,Y,LX,LY,LSZER,WIES);
			PasteBob(X,Y,BIBY+3);
		}
		for(I=1;I<=5;++I) {																	//	      For I=1 To 5 : Gosub LOSUJ2 : Paste Bob X,Y,BIBY+8 : Next
			_RYSUJ_SCENERIE_LOSUJ2(X,Y,LX,LY,LSZER,WIES);
			PasteBob(X,Y,BIBY+8);
		}
																			//	      'rozrzucanie zîota
		for(I=0;I<=Rnd(8)+2;++I) {																	//	      For I=1 To Rnd(8)+2
			X=Rnd(99); Y=Rnd(3);																//	         X=Rnd(99) : Y=Rnd(3)
			BB=BIBY+12;																//	         BB=BIBY+12
			CO=Rnd(3)+80;																//	         CO=Rnd(3)+80
			GLEBA[X][Y]=CO;																//	         GLEBA(X,Y)=CO
			XB=(X%10)*64+Rnd(30);																//	         XB=(X mod 10)*64+Rnd(30)
			YB=(X/10)*50+Rnd(20);																//	         YB=(X/10)*50+Rnd(20)
			PasteBob(XB,YB,BB);																//	         Paste Bob XB,YB,BB
		}																	//	      Next I
		if( PRZYGODY[TRWA_PRZYGODA][P_TYP]==9 ) {																	//	      If PRZYGODY(TRWA_PRZYGODA,P_TYP)=9
			RAN=55;																//	         RAN=55
			I=0;																//	         I=0
		} else {																	//	      Else
			PasteBob(6*60,0,BIBY+4); SetZone(61,6*60,0,6*60+78,80);						//	         Paste Bob 6*60,0,BIBY+4 : Set Zone 61,6*60,0 To 6*60+78,80
			PasteBob(9*60,0,BIBY+4); SetZone(62,9*60-18,0,9*60+60,80);																//	         Paste Bob 9*60,0,BIBY+4 : Set Zone 62,9*60-18,0 To 9*60+60,80
			PasteBob(6*60,0,BIBY+9);																//	         Paste Bob 6*60,0,BIBY+9
			PasteBob(9*60,0,BIBY+9);																//	         Paste Bob 9*60,0,BIBY+9
			PasteBob(7*60,0,BIBY+6);																//	         Paste Bob 7*60,0,BIBY+6
			PasteBob(520,0,BIBY+6);																//	         Paste Bob 520,0,BIBY+6
			PasteBob(7*60,40,BIBY+6);																//	         Paste Bob 7*60,40,BIBY+6
			PasteBob(520,40,BIBY+6);																//	         Paste Bob 520,40,BIBY+6
																			//
			PasteBob(452,30,BIBY+8);																//	         Paste Bob 452,30,BIBY+8
																			//	         '         Box 6*60,0 To 6*60+78,80
																			//	         '         Box 9*60-18,0 To 9*60+60,80
			SetZone(60,6*60,0,9*60+60,180);																//	         Set Zone 60,6*60,0 To 9*60+60,180
																			//	         '         Box 6*60,0 To 9*60+60,180
			I=3;																//	         I=3
			RAN=45;																//	         RAN=45
		}																	//	      End If
		J=0;																	//	      J=0
		for(Y=0;Y<=20;++Y) {																	//	      For Y=0 To 20
			for(X=0;X<=10;++X) {																//	         For X=0 To 10
				LOS=Rnd(RAN);															//	            LOS=Rnd(RAN)
				XB=X*60; YB=Y*25;															//	            XB=X*60 : YB=Y*25
				if( I<39 ) {															//	            If I<39
					if((LOS==1 || LOS==2) && _Zone(XB+4,YB+18)!=60 ) {//	               If(LOS=1 or LOS=2) and Zone(XB+4,YB+18)<>60
						++I;													//	                  Inc I
						PasteBob(XB,YB,BIBY+4);													//	                  Paste Bob XB,YB,BIBY+4
						SetZone(60+I,XB,YB,XB+60,YB+80);													//	                  Set Zone 60+I,XB,YB To XB+60,YB+80
					}														//	               End If
																			//
					if( LOS==0 && _Zone(XB+4,YB+18)!=60 ) {														//	               If LOS=0 and Zone(XB+4,YB+18)<>60
						++I;													//	                  Inc I
						PasteBob(XB,YB,BIBY+9);													//	                  Paste Bob XB,YB,BIBY+9
						SetZone(60+I,XB,YB,XB+60,YB+80);													//	                  Set Zone 60+I,XB,YB To XB+60,YB+80
					}														//	               End If
																			//
					if( LOS==3 && _Zone(XB+4,YB+18)!=60 ) {														//	               If LOS=3 and Zone(XB+4,YB+18)<>60
						++I;													//	                  Inc I
						PasteBob(XB,YB,BIBY+5);													//	                  Paste Bob XB,YB,BIBY+5
						SetZone(60+I,XB+5,YB,XB+35,YB+30);													//	                  Set Zone 60+I,XB+5,YB To XB+35,YB+30
																			//	                  'Box XB+5,YB To XB+34,YB+30
					}														//	               End If
					if( LOS==4 && _Zone(XB+4,YB+4)==0 ) {														//	               If LOS=4 and Zone(XB+4,YB+4)=0
						++I;													//	                  Inc I
						PasteBob(XB,YB,BIBY+6);													//	                  Paste Bob XB,YB,BIBY+6
						SetZone(60+I,XB+5,YB,XB+18,YB+38);													//	                  Set Zone 60+I,XB+5,YB To XB+18,YB+38
																			//	                  'Box XB+5,YB To XB+18,YB+38
					}														//	               End If
					if( LOS==5 && J<9 && _Zone(XB+4,YB+4)==0 ) {										//	               If LOS=5 and J<9 and Zone(XB+4,YB+4)=0
						++J;											//	                  Inc J
						SetZone(30+J,XB,YB+14,XB+34,YB+38);//	                  Set Zone 30+J,XB,YB+14 To XB+34,YB+38
						PLAPKI[J][0]=5;						//	                  PLAPKI(J,0)=5
						PLAPKI[J][1]=XB;					//	                  PLAPKI(J,1)=XB
						PLAPKI[J][2]=YB;					//	                  PLAPKI(J,2)=YB
						PLAPKI[J][3]=XB+34;				//	                  PLAPKI(J,3)=XB+34
						PLAPKI[J][4]=YB+38;				//	                  PLAPKI(J,4)=YB+38
																			//	                  'Paste Bob XB,YB,BIBY+7
																			//	                  'Box XB,YB+14 To XB+34,YB+38
					}														//	               End If
					if( LOS==7 && J<9 && _Zone(XB+4,YB+4)==0 ) {//	               If LOS=7 and J<9 and Zone(XB+4,YB+4)=0
						++J;											//	                  Inc J
						SetZone(30+J,XB+13,YB+8,XB+45,YB+35);//	                  Set Zone 30+J,XB+13,YB+8 To XB+45,YB+35
						PLAPKI[J][0]=4;						//	                  PLAPKI(J,0)=4
						PLAPKI[J][1]=XB+5;				//	                  PLAPKI(J,1)=XB+5
						PLAPKI[J][2]=YB+5;				//	                  PLAPKI(J,2)=YB+5
						PLAPKI[J][3]=XB+48+5;			//	                  PLAPKI(J,3)=XB+48+5
						PLAPKI[J][4]=YB+35;				//	                  PLAPKI(J,4)=YB+35
																			//	                  'Paste Bob XB+5,YB+5,BIBY+10
																			//	                  'Box XB+13,YB+8 To XB+45,YB+35
					}														//	               End If
					if( LOS==6 && _Zone(XB+4,YB+4)==0 && Rnd(2)==0 ) {//	               If LOS=6 and Zone(XB+4,YB+4)=0 and Rnd(2)=0
						SEKTOR(XB+15,YB+10);			//	                  SEKTOR[XB+15,YB+10]
						GLEBA[Param][Rnd(3)]=Rnd(MX_WEAPON);//	                  GLEBA(Param,Rnd(3))=Rnd(MX_WEAPON)
						PasteBob(XB,YB,BIBY+11);	//	                  Paste Bob XB,YB,BIBY+11
					}														//	               End If
				}															//	            End If
			}																//	         Next X
		}																	//	      Next Y
		ResetZone(60);										//	      Reset Zone 60
	}																		//	   End If
																			//
	//---grota wladcy---
	if( TYP==10 ) {												//	   If TYP=10
																				//	      'grota wîadcy
		WIDOCZNOSC=500;											//	      WIDOCZNOSC=500
		_LOAD(KAT_S+"dane/scen-grota","dane:scen-grota","Dane",1);//	      _LOAD[KAT$+"dane/scen-grota","dane:scen-grota","Dane",1] : Get Bob Palette
		_LOAD(KAT_S+"dane/muzyka/mus-grota","dane:muzyka/mus-grota","Dane",7);//	      _LOAD[KAT$+"dane/muzyka/mus-grota","dane:muzyka/mus-grota","Dane",7]
//	      Shift Down 3,20,23,1
		Music(1);														//	      Music 1
		for(Y=0;Y<=8;++Y) {									//	      For Y=0 To 8
			for(X=0;X<=9;++X) {								//	         For X=0 To 9
				PasteBob(X*64,Y*64,BIBY+1,1.005);//	            Paste Bob X*64,Y*64,BIBY+1
			}																	//	         Next
		}																		//	      Next
		for(Y=2;Y<=8;++Y) {									//	      For Y=2 To 8
			for(X=2;X<=7;++X) {								//	         For X=2 To 7
				PasteBob(X*64,Y*40,BIBY+2,1.005);//	            Paste Bob X*64,Y*40,BIBY+2
			}																	//	         Next
		}																		//	      Next
		for(Y=1;Y<=4;++Y) {									//	      For Y=1 To 4
			PasteBob(128,Y*64,BIBY+3,1.005);	//	         Paste Bob 128,Y*64,BIBY+3
			PasteBob(496,Y*64,Hrev(BIBY+3),1.005);//	         Paste Bob 496,Y*64,Hrev(BIBY+3)
		}																		//	      Next Y
		for(X=2;X<=7;++X) {									//	      For X=2 To 7
			PasteBob(X*64,64,BIBY+4,1.005);		//	         Paste Bob X*64,64,BIBY+4
			PasteBob(X*64,304,BIBY+5,1.005);	//	         Paste Bob X*64,304,BIBY+5
		}																		//	      Next
		for(Y=0;Y<=12;++Y) {								//	      For Y=0 To 12
			X=-Rnd(20);												//	         X=-Rnd(20)
			PasteBob(X,Rnd(10)+20+Y*40,BIBY+7);//	         Paste Bob X,Rnd(10)+20+Y*40,BIBY+7
			PasteBob(X,Y*40,BIBY+6);					//	         Paste Bob X,Y*40,BIBY+6
																				//
			X=Rnd(20);												//	         X=Rnd(20)
			PasteBob(X+560,Rnd(10)+20+Y*40,Hrev(BIBY+7));//	         Paste Bob X+560,Rnd(10)+20+Y*40,Hrev(BIBY+7)
			PasteBob(X+560,Y*40,Hrev(BIBY+6));//	         Paste Bob X+560,Y*40,Hrev(BIBY+6)
																				//
		}																		//	      Next Y
																				//
		XB=100; YB=322;											//	      XB=100 : YB=322
		SetZone(31,XB,YB,XB+420,YB+100);		//	      Set Zone 31,XB,YB To XB+420,YB+100
		PLAPKI[1][0]=6;											//	      PLAPKI(1,0)=6
		PLAPKI[1][1]=XB;										//	      PLAPKI(1,1)=XB
		PLAPKI[1][2]=YB;										//	      PLAPKI(1,2)=YB
		PLAPKI[1][3]=XB+34;									//	      PLAPKI(1,3)=XB+34
		PLAPKI[1][4]=115;										//	      PLAPKI(1,4)=115
																				//	      '      Ink 10
																				//	      '      Box XB,YB To XB+420,YB+100
																				//
		XB=100; YB=0;												//	      XB=100 : YB=0
		SetZone(32,XB,YB,XB+420,YB+63);			//	      Set Zone 32,XB,YB To XB+420,YB+63
		PLAPKI[2][0]=6;											//	      PLAPKI(2,0)=6
		PLAPKI[2][1]=XB;										//	      PLAPKI(2,1)=XB
		PLAPKI[2][2]=YB;										//	      PLAPKI(2,2)=YB
		PLAPKI[2][3]=XB+34;									//	      PLAPKI(2,3)=XB+34
		PLAPKI[2][4]=0;											//	      PLAPKI(2,4)=0
																				//	      '      Ink 10
																				//	      '      Box XB,YB To XB+420,YB+63
																				//
		XB=0; YB=0;													//	      XB=0 : YB=0
		SetZone(33,XB,YB,XB+118,YB+340);		//	      Set Zone 33,XB,YB To XB+118,YB+340
		PLAPKI[3][0]=6;											//	      PLAPKI(3,0)=6
		PLAPKI[3][1]=XB;										//	      PLAPKI(3,1)=XB
		PLAPKI[3][2]=YB;										//	      PLAPKI(3,2)=YB
		PLAPKI[3][3]=XB+34;									//	      PLAPKI(3,3)=XB+34
		PLAPKI[3][4]=85;										//	      PLAPKI(3,4)=85
																				//	      '      Ink 10
																				//	      '      Box XB,YB To XB+118,YB+340
																				//
		XB=522; YB=0;												//	      XB=522 : YB=0
		SetZone(34,XB,YB,XB+100,YB+340);		//	      Set Zone 34,XB,YB To XB+100,YB+340
		PLAPKI[4][0]=6;											//	      PLAPKI(4,0)=6
		PLAPKI[4][1]=XB;										//	      PLAPKI(4,1)=XB
		PLAPKI[4][2]=YB;										//	      PLAPKI(4,2)=YB
		PLAPKI[4][3]=XB+34;									//	      PLAPKI(4,3)=XB+34
		PLAPKI[4][4]=85;										//	      PLAPKI(4,4)=85
																				//	      '      Ink 10
																				//	      '      Box XB,YB To XB+100,YB+340
																				//
	}																			//	   End If
																				//
	if(WIES>=0) {													//	   If WIES>=0
		RYSUJ_WIES(WIES);										//	      RYSUJ_WIES[WIES]
																				//	      'dodaê domy (9)
		BSIBY=BIBY+12+9;										//	      BSIBY=BIBY+12+9
	}																			//	   End If
	if(WIES<-1) {													//	   If WIES<-1
		RYSUJ_MUR(WIES);										//	      RYSUJ_MUR[WIES]
																				//	      'dodaê mury (2)
		BSIBY=BIBY+12+2;										//	      BSIBY=BIBY+12+2
	}																			//	   End If
																				//	   'wytnij strzaîy
	//to nie ma znaczenia na PC
																				//	   Screen 2
																				//	   Cls 0
																				//	   For I=1 To 20
																				//	      Get Bob BSIBY+I,0,0 To 31,31
																				//	   Next I
																				//	   Screen 0
																				//
																				//	   Goto OVER
	//OVER:																	//	   OVER:
																				//	   Screen Show 0
																				//	End Proc
	PBListOnoff(false);
}

void FUNDAMENTY(aint NR) {
	aint I=0, TYP=0, X=0, Y=0, SZER=0, WYS=0;
																//	Procedure FUNDAMENTY[NR]
	for(I=2;I<=20;++I) {					//	   For I=2 To 20
		TYP=MIASTA[NR][I][M_LUDZIE];//	      TYP=MIASTA(NR,I,M_LUDZIE)
		if( TYP>0 ) {								//	      If TYP>0
			X=MIASTA[NR][I][M_X];			//	         X=MIASTA(NR,I,M_X)
			Y=MIASTA[NR][I][M_Y];			//	         Y=MIASTA(NR,I,M_Y)
			SZER=BUDYNKI[TYP][0];			//	         SZER=BUDYNKI(TYP,0)
			WYS=BUDYNKI[TYP][1];			//	         WYS=BUDYNKI(TYP,1)
			SetZone(120+I,X,Y,X+SZER,Y+WYS+40);	//	         Set Zone 120+I,X,Y To X+SZER,Y+WYS+40
		}														//	      End If
	}															//	   Next
																//	End Proc
}
void RYSUJ_WIES(aint NR) {
																							//	Procedure RYSUJ_WIES[NR]
	aint I=0, TYP=0, X=0, Y=0, SZER=0, WYS=0, B=0, DR=0, BR=0, RANGA=0, S=0;

	WIDOCZNOSC=250;															//	   WIDOCZNOSC=250
	aint SOR[6+1];															//	   Dim SOR(6)
	_LOAD(KAT_S+"dane/scen-domy","dane:scen-domy","Dane",1);//	   _LOAD[KAT$+"dane/scen-domy","dane:scen-domy","Dane",1]
	for( I=2; I<=20; I++ ) {										//	   For I=2 To 20
		TYP=MIASTA[NR][I][M_LUDZIE];							//	      TYP=MIASTA(NR,I,M_LUDZIE)
		if( TYP>0 ) {															//	      If TYP>0
			X=MIASTA[NR][I][M_X];										//	         X=MIASTA(NR,I,M_X)
			Y=MIASTA[NR][I][M_Y];										//	         Y=MIASTA(NR,I,M_Y)
																							//
			SZER=BUDYNKI[TYP][0];										//	         SZER=BUDYNKI(TYP,0)
			WYS=BUDYNKI[TYP][1];										//	         WYS=BUDYNKI(TYP,1)
			B=BUDYNKI[TYP][4];											//	         B=BUDYNKI(TYP,4)
			DR=BUDYNKI[TYP][6];											//	         DR=BUDYNKI(TYP,6)
//!@#			PasteBob(X,Y,BIBY+12+B);								//	         Paste Bob X,Y,BIBY+12+B
			PasteBob(X+47,Y+130,BIBY+12+B);								//	         Paste Bob X,Y,BIBY+12+B
			SetZone(120+I,X,Y,X+SZER,Y+WYS);				//	         Set Zone 120+I,X,Y To X+SZER,Y+WYS
			if( DR>0 ) {														//	         If DR>0
				SetZone(100+I,X+DR,Y+WYS-32,X+DR+32,Y+WYS);//	            Set Zone 100+I,X+DR,Y+WYS-32 To X+DR+32,Y+WYS
																							//	            '            Ink 3 : Box X+DR,Y+WYS-32 To X+DR+32,Y+WYS
																							//
				RANGA=MIASTA[NR][I][M_CZYJE];					//	            RANGA=MIASTA(NR,I,M_CZYJE)
				switch(TYP) {
					case 4:															//	            If TYP=4
						SOR[0]=1; SOR[1]=2; SOR[2]=3; SOR[3]=4; SOR[4]=5; SOR[5]=7; SOR[6]=13;//	               SOR(0)=1 : SOR(1)=2 : SOR(2)=3 : SOR(3)=4 : SOR(4)=5 : SOR(5)=7 : SOR(6)=13
						break;														//	            End If
					case 5:															//	            If TYP=5
						SOR[0]=1; SOR[1]=3; SOR[2]=2; SOR[3]=2; SOR[4]=11; SOR[5]=7; SOR[6]=6;//	               SOR(0)=1 : SOR(1)=3 : SOR(2)=2 : SOR(3)=2 : SOR(4)=11 : SOR(5)=7 : SOR(6)=6
						break;														//	            End If
					case 6:															//	            If TYP=6
						SOR[0]=12; SOR[1]=12; SOR[2]=12; SOR[3]=12; SOR[4]=12; SOR[5]=12; SOR[6]=12;																//	               SOR(0)=12 : SOR(1)=12 : SOR(2)=12 : SOR(3)=12 : SOR(4)=12 : SOR(5)=12 : SOR(6)=12
						break;														//	            End If
					case 7:															//	            If TYP=7
						SOR[0]=4; SOR[1]=5; SOR[2]=8; SOR[3]=9; SOR[4]=10; SOR[5]=15; SOR[6]=16;//	               SOR(0)=4 : SOR(1)=5 : SOR(2)=8 : SOR(3)=9 : SOR(4)=10 : SOR(5)=15 : SOR(6)=16
						break;														//	            End If
					case 8:															//	            If TYP=8
						SOR[0]=13; SOR[1]=13; SOR[2]=13; SOR[3]=18; SOR[4]=18; SOR[5]=18; SOR[6]=18;//	               SOR(0)=13 : SOR(1)=13 : SOR(2)=13 : SOR(3)=18 : SOR(4)=18 : SOR(5)=18 : SOR(6)=18
						break;														//	            End If
					case 9:															//	            If TYP=9
						SOR[0]=17; SOR[1]=17; SOR[2]=17; SOR[3]=17; SOR[4]=17; SOR[5]=17; SOR[6]=17;//	               SOR(0)=17 : SOR(1)=17 : SOR(2)=17 : SOR(3)=17 : SOR(4)=17 : SOR(5)=17 : SOR(6)=17
						break;										  			//	            End If
				}
				S=0;																	//	            S=0
				if( TYP<9 ) {													//	            If TYP<9
					for(Y=0;Y<=1;++Y) {									//	               For Y=0 To 1
						for(X=0;X<=9;++X) {								//	                  For X=0 To 9
							if( Rnd(3)==1 ) {								//	                     If Rnd(3)=1
								SKLEP[I][S]=0;								//	                        SKLEP(I,S)=0
							} else {												//	                     Else
								AGAIN:												//	                        AGAIN:
								BR=Rnd(MX_WEAPON);						//	                        BR=Rnd(MX_WEAPON)
								for(B=0;B<=6;B++) {						//	                        For B=0 To 6
									if( BRON[BR][B_TYP]==SOR[B] && BRON[BR][B_CENA]<1000) {//	                           If BRON(BR,B_TYP)=SOR(B) and BRON(BR,B_CENA)<1000
										goto JEST;								//	                              Goto JEST
									}														//	                           End If
								}															//	                        Next B
								goto AGAIN;										//	                        Goto AGAIN
								JEST:													//	                        JEST:
								SKLEP[I][S]=BR;								//	                        SKLEP(I,S)=BR
							}																//	                     End If
							S++;														//	                     Inc S
						}																	//	                  Next X
					}																		//	               Next Y
				}																			//	            End If
			}																				//	         End If
		}																					//	      End If
	}																						//	   Next I
																							//
																							//
																							//	End Proc
}
void RYSUJ_MUR(aint TYP) {
																					//	Procedure RYSUJ_MUR[TYP]
	aint SILA=0,I=0;
	WIDOCZNOSC=400;													//	   WIDOCZNOSC=400
	if( TYP==-2 ) {													//	   If TYP=-2
		_LOAD(KAT_S+"dane/mur2","dane:mur2","Dane",1);//	      _LOAD[KAT$+"dane/mur2","dane:mur2","Dane",1]
		SILA=220;															//	      SILA=220
	}																				//	   End If
	if( TYP==-3 ) {													//	   If TYP=-3
		_LOAD(KAT_S+"dane/mur1","dane:mur1","Dane",1);//	      _LOAD[KAT$+"dane/mur1","dane:mur1","Dane",1]
		SILA=300;															//	      SILA=300
	}																				//	   End If
	if( TYP==-4 ) {													//	   If TYP=-4
		_LOAD(KAT_S+"dane/mur3","dane:mur3","Dane",1);//	      _LOAD[KAT$+"dane/mur3","dane:mur3","Dane",1]
		SILA=400;															//	      SILA=400
	}																				//	   End If
																					//
	for(I=0;I<=9;++I) {											//	   For I=0 To 9
		PasteBob(I*64,10,BIBY+12+1);					//	      Paste Bob I*64,10,BIBY+12+1
		SetZone(21+I,I*64,140,(I*64)+64,200);	//	      Set Zone 21+I,I*64,140 To(I*64)+64,200
		MUR[I]=SILA;													//	      MUR(I)=SILA
	}																				//	   Next I
																					//	End Proc
}
