
#include <cmath>

#include "Amos.h"

#include "legion.h"
#include "lgn_util.h"
#include "lgn_intro.h"
#include "utl_locale.h"

void (*rysuj_ekran_ptr)(void) = 0;	//wskaznik na funkcje, ktora rysuje mape,level,etc.
void rysuj(void) {
	if( 0 != rysuj_ekran_ptr ) {
		rysuj_ekran_ptr();
	}
}


void gad_back(float wsp) {
	wsp/=255.0f;
	Gfx::Color(119.0f*wsp,102.0f*wsp,85.0f*wsp);
}
void gad_back_sklep(float wsp) {
	wsp/=255.0f;
	Gfx::Color(51.0f*wsp,17.0f*wsp,0.0f*wsp);
}
void gad_light(float wsp) {
	wsp/=255.0f;
	Gfx::Color(140.0f*wsp,123.0f*wsp,106.0f*wsp);
}
void gad_dark(float wsp) {
	wsp/=255.0f;
	Gfx::Color(46.0f*wsp,29.0f*wsp,12.0f*wsp);
}
void gad_shadow(float wsp) {
	wsp/=255.0f;
	Gfx::Color(46.0f*wsp,29.0f*wsp,12.0f*wsp);
}
void gad_text(float wsp) {
	wsp/=255.0f;
	Gfx::Color(210.0f*wsp,204.0f*wsp,203.0f*wsp);
}
void gad_forsa(float wsp) {
	wsp/=255.0f;
	Gfx::Color(255.0f*wsp,230.0f*wsp,64.0f*wsp);
}
void GADGET(aint X,aint Y,aint SZER,aint WYS,astr TX_S,aint K1,aint K2,aint K3,aint K4,aint STREFA) {
	//	Procedure GADGET[X,Y,SZER,WYS,TX$,K1,K2,K3,K4,STREFA]

	aint DEEPX=0,DEEPY=0,DLUGTX=0,X1=0,Y1=0,BNR=0,CIENIE=0;

	DEEPX=1; DEEPY=1;								//	   DEEPX=1 : DEEPY=1
	DLUGTX=Len(TX_S);								//	   DLUGTX=Len(TX$)
	X1=X+SZER;											//	   X1=X+SZER
	Y1=Y+WYS;												//	   Y1=Y+WYS
	if( STREFA>0 ) {								//	   If STREFA>0
		SetZone(STREFA,X,Y,X1,Y1);		//	      Set Zone STREFA,X,Y To X1,Y1
	}																//	   End If
	float wsp;
	if( K3==4 ) {
		wsp=0.8;
	} else {
		wsp=1.0;
	}
	gad_light(wsp);									//	   Ink K1
	_Bar(X,Y,X1,Y1);								//	   Bar X,Y To X1,Y1
	if( K3==1000 )
	  gad_back_sklep(wsp);
	else
	  gad_back(wsp);									//	   Ink K3
	_Bar(X+DEEPX,Y+DEEPY,X1-DEEPX,Y1-DEEPY);//	   Bar X+DEEPX,Y+DEEPY To X1-DEEPX,Y1-DEEPY
	gad_dark(wsp);									//	   Ink K2
	_Line(X,Y1,X1,Y1);							//	   Polyline X,Y1 To X1,Y1 To X1,Y
	_Line(X1,Y1,X1,Y);
	if( TX_S != "" ) {							//	   If TX$<>""
		if( Upper_S(Left_S(TX_S,3))=="BOB" ) {		//	      If Upper$(Left$(TX$,3))="BOB"
			BNR=Val(Mid_S(TX_S,4,2));		//	         BNR=Val(Mid$(TX$,4,2))
			PasteBob(X,Y,BNR);					//	         Paste Bob X,Y,BNR
		} else {											//	      Else
			if( CIENIE>0 && CIENIE<4 ) {//	         If CIENIE>0 and CIENIE<4
				gad_shadow(wsp);							//	            Ink K2,K3
//!!!				Text(X+FONT/2,Y+FONT+FONT/3,TX_S);//	            Text X+FONT/2,Y+FONT+FONT/3,TX$
				Text(X+FONT/2,Y+FONT-FONT/8,TX_S);//	            Text X+FONT/2,Y+FONT+FONT/3,TX$
				gad_text(wsp);						//	            Ink K4,K3
//!!!				Text((X+FONT/2)+CIENIE,(Y+FONT+FONT/3)+CIENIE,TX_S);//	            Text(X+FONT/2)+CIENIE,(Y+FONT+FONT/3)+CIENIE,TX$
				Text((X+FONT/2)+CIENIE,(Y+FONT-FONT/8)+CIENIE,TX_S);//	            Text(X+FONT/2)+CIENIE,(Y+FONT+FONT/3)+CIENIE,TX$
			} else {										//	         Else
				gad_text(wsp);						//	            Ink K4,K3
//!!!				Text(X+FONT/2,Y+FONT+FONT/3,TX_S);//	            Text X+FONT/2,Y+FONT+FONT/3,TX$
				Text(X+FONT/2,Y+FONT-FONT/8,TX_S);//	            Text X+FONT/2,Y+FONT+FONT/3,TX$
			}														//	         End If
		}															//	      End If
	}																//	   End If
	if( STREFA==0 ) {								//	   If STREFA=0
																	//	      '      If mouse key=lewy
																	//	      '         Talk Stop
																	//	      '         Sam Play 2,10
																	//	      '       End If
		while( MouseKey()==LEWY )	{		//	      While Mouse Key=LEWY
			ProcessEvents();
		}															//	      Wend
	}																//	   End If
}	//	End Proc

aflt bg_r=0.0f, bg_g=0.0f, bg_b=0.0f, bg_a=1.0f;
aflt fg_r=1.0f, fg_g=1.0f, fg_b=1.0f, fg_a=1.0f;
void SET_BACKGROUND(aflt r,aflt g,aflt b,aflt a) {
	bg_r = r;
	bg_g = g;
	bg_b = b;
	bg_a = a;
}
void SET_FOREGROUND(aflt r,aflt g,aflt b,aflt a) {
	fg_r = r;
	fg_g = g;
	fg_b = b;
	fg_a = a;
}
void WPISZ_PC(aint X,aint Y,aint W,aint H,aint ILE,astr &REF_TXT_S,aint RYSUJ) {
	//X,Y - pozycja lewego,gornego rogu prostokata
	//W,H - rozmiar prostokata
	//ILE - ile maksymalnie znako moze miec wpisany napis
	//REF_TXT_S - referencja do zmiennej, w ktorej beda na biezaco odkladane wpisywane znaki
	//RYSUJ = 0 - nie rysuj, 1 - rysuj tylko ekran, 2 - rysuj dodatkowo kursor, 3 - rysuj dodatkowo wprowadzany tekst

	astr TXT_S=REF_TXT_S
			,K_S;
	aint SC, DL, CPOS, XC;
	aflt A_F=0.75f, DA_F=-0.02f;

	CPOS=Len(TXT_S);
	ClearKey();
	do {

		XC=X+TextLength(Left_S(TXT_S,CPOS));

		//mryganie kursora
		A_F+=DA_F;
		if( A_F<0.40f && DA_F<0.0f ) {
			A_F=0.40f;
			DA_F=-DA_F;
		}
		if( A_F>0.90f && DA_F>0.0f ) {
			A_F=0.90f;
			DA_F=-DA_F;
		}

		if( RYSUJ>=1 ) {
			//caly ekran
			rysuj();
		}
		if( RYSUJ>=3 ) {
			//tlo
			Gfx::Color(bg_r,bg_g,bg_b,bg_a);
			_Bar(X,Y,X+W,Y+H);
			//text
			Gfx::Color(fg_r,fg_g,fg_b,fg_a);
			Text(X,Y+TextBase(),TXT_S);
		}
		if( RYSUJ>=2 ) {
			//cursor
			Gfx::Color(A_F,A_F/3.0f,0.f);
			_Draw(XC,Y,XC,Y+H);
			_Draw(XC-1,Y,XC+1,Y);
			_Draw(XC-1,Y+H,XC+1,Y+H);
		}

		WaitVbl();

		K_S=Inkey_S();
		SC=ScanCode();
		if(SC>0 || Len(K_S)>0 ) {
			if( SC!=65 && SC!=68 && Asc(K_S)!=127 && Len(TXT_S)<ILE && Len(K_S)>0 ) {
				DL=Len(TXT_S);
				TXT_S = Left_S(TXT_S,CPOS) + K_S + Right_S(TXT_S,DL-CPOS);
				CPOS++;
			}
			if( SC==65 && Len(TXT_S)>0 && CPOS>0 ) {		//backspace
				DL=Len(TXT_S);
				TXT_S=Left_S(TXT_S,CPOS-1) + Right_S(TXT_S,DL-CPOS);
				CPOS--;
			}
			if( Asc(K_S)==127 && Len(TXT_S)>0 && CPOS<Len(TXT_S) ) {		//del
				DL=Len(TXT_S);
				TXT_S=Left_S(TXT_S,CPOS) + Right_S(TXT_S,DL-CPOS-1);
			}
			if( SC==78 && CPOS<Len(TXT_S) ) {		//cursor right
				CPOS++;
			}
			if( SC==79 && CPOS>0 ) {						//cursor left
				CPOS--;
			}
		}

		REF_TXT_S = TXT_S;

	} while( !( SC==68 || SC==67 || MouseClick()==2 ) );
	WPI=Val(TXT_S);
	WPI_F=Val(TXT_S);
	WPI_S=TXT_S;

	//rysujemy bez kursora aby mozna bylo zapamietac ekran z nowym napisem
	if( RYSUJ>=1 ) {
		//caly ekran
		rysuj();
	}
	if( RYSUJ>=3 ) {
		//tlo
		Gfx::Color(bg_r,bg_g,bg_b,bg_a);
		_Bar(X,Y,X+W,Y+H);
		//text
		Gfx::Color(fg_r,fg_g,fg_b,fg_a);
		Text(X,Y+TextBase(),TXT_S);
	}

}
void WPISZ_OLD(aint X,aint Y,aint K1,aint K2,aint ILE,aint RYSUJ) {
																															//	Procedure WPISZ[X,Y,K1,K2,ILE]
	aint NX=0, NY=0, DLT=0, DZ=0, DL=0, SC=0, XP=0, YP=0;
	astr K_S="", SUMA_S="";
																															//	   Ink K2,K1
	Gfx::Color(0.f,0.f,0.f);	//!@#
	Bar(X,Y-TextBase(),X+(ILE*FONTSZ),Y+(FONT/3));																														//	   Bar X,Y-Text Base To X+(ILE*FONTSZ),Y+(FONT/3)

	XP=X; YP=Y;
	ClearKey();																														//	   Clear Key
	if( Screen()==0 ) {																														//	   If Screen=0
		NX=SX; NY=SY;																														//	      NX=SX : NY=SY
	} else {																														//	   Else
		NX=0; NY=0;																														//	      NX=0 : NY=0
	}																														//	   End If
	do {																														//	   Repeat
		K_S=Inkey_S();																														//	      K$=Inkey$
		if( KeyState(65)==0 && Len(SUMA_S)<ILE && KeyState(68)==0 && DLT<100 ) {																														//	      If Key State(65)=0 and Len(SUMA$)<ILE and Key State(68)=0 and DLT<100
																								//	         Ink K1,K2
																																	//	         Text X,Y,K$
			SUMA_S=SUMA_S+K_S;																														//	         SUMA$=SUMA$+K$
			DZ=TextLength(K_S);																														//	         DZ=Text Length(K$)
			DLT=TextLength(SUMA_S);																														//	         DLT=Text Length(SUMA$)
			X=X+DZ;																														//	         X=X+DZ
			if( Len(SUMA_S)<ILE ) {																														//	         If Len(SUMA$)<ILE
				SetXMouse(XHard(X)-NX);																														//	            X Mouse=X Hard(X)-NX
				SetYMouse(YHard(Y)-NY);																														//	            Y Mouse=Y Hard(Y)-NY
			}																														//	         End If
		}																														//	      End If
		if( Len(SUMA_S)>0 && KeyState(65) ) {																														//	      If Len(SUMA$)>=0 and Key State(65)
			K_S=Right_S(SUMA_S,1);																														//	         K$=Right$(SUMA$,1)
			DZ=TextLength(K_S);																														//	         DZ=Text Length(K$)
			X=X-DZ;																														//	         X=X-DZ
			SetXMouse(XHard(X)-NX);																														//	         X Mouse=X Hard(X)-NX
			SetYMouse(YHard(Y)-NY);																														//	         Y Mouse=Y Hard(Y)-NY
																																	//	         Ink K2 : Text X,Y,K$
			DL=Len(SUMA_S)-1;																														//	         DL=Len(SUMA$)-1
			SUMA_S=Left_S(SUMA_S,DL);																														//	         SUMA$=Left$(SUMA$,DL)
			DLT=TextLength(SUMA_S);																														//	         DLT=Text Length(SUMA$)
			while( KeyState(65) ) {																														//	         While Key State(65)
				ProcessEvents();
			}																														//	         Wend
			ClearKey();																														//	         Clear Key
		}																													//	      End If
		SC=ScanCode();																														//	      SC=Scancode
		if( 0 != RYSUJ ) rysuj();
		Gfx::Color(0.f,0.f,0.f);
		_Bar(XP-FONTSZ,YP-TextBase(),XP+(ILE*FONTSZ)*2,YP+FONT);
		Gfx::Color(1.f,1.f,1.f);
		Text(XP,YP,SUMA_S);
		WaitVbl();
	} while( !( SC==68 || SC==67 || MouseClick()==2 ) );																														//	   Until SC=68 or SC=67 or Mouse Click=2
	WPI=Val(SUMA_S);																														//	   WPI=Val(SUMA$)
	WPI_F=Val(SUMA_S);																														//	   WPI#=Val(SUMA$)
	WPI_S=SUMA_S;																														//	   WPI$=SUMA$

/*
	aint SC=0;
	astr SUMA_S="";
	ClearKey();
	SUMA_S = "";
	do {
		SC = ScanCode();
		//cerr << "SCANCODE: " << toString(SC) << endl;
		if( SC != 0 ) {
			if( SC == SDLK_DELETE || SC == SDLK_BACKSPACE ) {
				SUMA_S = SUMA_S.substr(0,SUMA_S.size()-1);
			} else if( SC == SDLK_RETURN ) {
				break;
			}	else {
				if( SC >= 32 && (aint)SUMA_S.size() < ILE )
					SUMA_S += Chr_S(SC);
			}
		}
		Gfx::Color(0.f,0.f,0.f); _Bar(X-FONTSZ*2,Y-FONT*2,X+(ILE*FONTSZ)*2,Y+FONT);
		Gfx::Color(1.f,1.f,1.f);
		Text(X,Y,SUMA_S);
		ClearKey();
		WaitVbl();
	} while( true );
	WaitVbl();

	WPI=atoi(SUMA_S.c_str());
	WPI_F=atof(SUMA_S.c_str());
	WPI_S=SUMA_S;
*/
	//	End Proc
}


void USTAW_FONT( astr FONTNAME_S, astr FILENAME_S, aint WIEL, aint ANTIA) {
	//	Procedure USTAW_FONT[FONTNAME$,WIEL]
	//	   FONT=8
	//	   Repeat
	//	      Inc I
	//	      FON$=Left$(Font$(I),Len(FONTNAME$))
	//	      WIEL$=Mid$(Font$(I),28,6)
	//	      If Upper$(FON$)=Upper$(FONTNAME$) and Val(WIEL$)=WIEL
	//	         Set Font I
	//	         FONR=I
	//	         FONT=Val(WIEL$)
	//	      End If
	//	   Until Font$(I)=""
	//	End Proc

	FONT = 8;
	aint I=0;
	I = SetFont(FONTNAME_S,FILENAME_S,WIEL,0!=ANTIA);
	if( I >= 0 ) {
		FONR = I;
		FONT = WIEL;
		INFO("Pomyœlnie za³adowano font: " + FILENAME_S + ", " + toString(WIEL));
	} else {
		ERROR("B³¹d ³adowania fontu: " + FILENAME_S + ", " + toString(WIEL));
	}
}
void _GET_XY(aint TRYB,aint X1,aint Y1) {
																					//	Procedure _GET_XY[TRYB,X1,Y1]
	astr B_S="",A_S="";
	aint HY=0, KLAW=0;
																					//
																					//	   If TRYB=1
																					//	      Gr Writing 2
																					//	   End If
	if( TRYB==2 ) {													//	   If TRYB=2
		Sprite(0,XMouse(),YMouse(),49);				//	      Sprite 0,X Mouse,Y Mouse,49
																					//	      Hide
																					//	      A$="S: Move XM-X,YM-Y,1 ; Jump S"
																					//	      B$="Anim 0,(49,4)(46,4)(41,4)(46,4)"
		B_S="FLOAT F; F=4.0/50.0; ANIM -1,('49',F)('46',F)('41',F)('46',F); PAUSE while IS ANIMATING;";
		Amal(0,B_S);													//	      Amal 0,B$
		ChannelToSprite(0,0);
	} else {																//	   Else
		ChangeMouse(CELOWNIK);								//	      Change Mouse CELOWNIK
	}																				//	   End If
	Screen(0);															//	   Screen 0
	aint frame=0;
	do {																		//	   Repeat
		if( frame==0 ) frame=1; else frame=0;
		WaitVbl();
		rysuj();
		HY=YMouse();													//	      HY=Y Mouse
		OX=XScreen(XMouse());									//	      OX=X Screen(X Mouse)
		OY=YScreen(YMouse());									//	      OY=Y Screen(Y Mouse)
		if( TRYB==1 ) {												//	      If TRYB=1
			if( frame==0 )
				Gfx::Color(1.f,1.f,1.f);
			else
				Gfx::Color(0.f,0.f,0.f);
			_Draw(X1,Y1,OX,OY);									//	         Draw X1,Y1 To OX,OY
																					//	         Wait Vbl
																					//	         Draw X1,Y1 To OX,OY
		}																			//	      End If
		if(	TRYB==2 ) {												//	      If TRYB=2
			if( MouseZone()>0	&& MouseZone()<21 ) {//	         If Mouse Zone>0 and Mouse Zone<21
				AmalOnOff(0,true);								//	            Amal On 0 : Sprite 0,X Mouse,Y Mouse, : Wait Vbl
				Sprite(0,XMouse(),YMouse(),NOPARI);
			} else {														//	         Else
				AmalFreeze(-1);										//	            Amal Freeze
				Sprite(0,XMouse(),YMouse(),49);		//	            Sprite 0,X Mouse,Y Mouse,49 : Wait Vbl
			}																		//	         End If
		}																			//	      End If
		if( MouseKey() == PRAWY ) {						//	      If Mouse Key=PRAWY
			if( TRYB==2 ) {											//	         If TRYB=2 : Sprite Off 0 : Amal Freeze : End If
				SpriteOnOff(0,false);
				AmalFreeze(-1);
			}
			SKROL(1);														//	         SKROL[1]
			if( TRYB==2 ) {											//	         If TRYB=2 : Amal 0,B$ : Hide On : Sprite 0,X Mouse,Y Mouse,49 : End If
				Sprite(0,XMouse(),YMouse(),49);
				Amal(0,B_S);
				ChannelToSprite(0,0);
			}
		}																			//	      End If
		A_S=Inkey_S();												//	      A$=Inkey$
		KLAW=ScanCode();											//	      KLAW=Scancode
		if( KLAW>75 && KLAW<80 ) {						//	      If KLAW>75 and KLAW<80
			KLAWSKROL(KLAW);										//	         KLAWSKROL[KLAW]
		}																			//	      End If
	} while( ! MouseClick() );							//	   Until Mouse Click=1
	if( TRYB==2 ) {													//	   If TRYB=2
		AmalOnOff(0,false);										//	      Amal Off 0
																					//	      Show On
	}																				//	   End If
																					//	   If TRYB=1
																					//	      Gr Writing 0
																					//	   End If
	SpriteOnOff(0,false);
	ChangeMouse(BUBY+6);										//	   Change Mouse BUBY+6
																					//	End Proc
}

void OKNO(aint OKX,aint OKY,aint SZER,aint WYS) {
	//	Procedure OKNO[OKX,OKY,SZER,WYS]

	OKX += SX;							//	   Add OKX,SX
	OKY += SY;							//	   Add OKY,SY
	::OKX = OKX;
	::OKY = OKY;
													//	   Get Block 100,OKX,OKY,SZER+16,WYS+16,1
	Gfx::Color(0.f,1.f,1.f);//	   Ink 17 : Box OKX,OKY To OKX+SZER,OKY+WYS
	_Box(OKX,OKY,OKX+SZER,OKY+WYS);
}	//	End Proc
void ZOKNO(void) {
	//	Procedure ZOKNO

	aint I=0;
												//	   Put Block 100,OKX,OKY
	for(I=1;I<=19;++I) {	//	   For I=1 To 19
		ResetZone(I);				//	      Reset Zone I
	}											//	   Next I
}	//	End Proc
void WJAZD(aint XS,aint YS,aint X1,aint Y1,aint SZER,aint WYS,aint _WAIT) {
																																//	Procedure WJAZD[XS,YS,X1,Y1,SZER,WYS,_WAIT]
	aint I=0, SPEED=0, DX1=0, DX2=0, DY1=0, DY2=0, XB1=0, YB1=0, XB2=0, YB2=0;

																																//	   Gr Writing 3 : Ink 20
	for( I=1; I<=_WAIT; ++I ) {																		//	   For I=1 To _WAIT
		rysuj();
		_Box(XS-4,YS-4,XS+4,YS+4);																	//	      Box XS-4,YS-4 To XS+4,YS+4
		WaitVbl();
		Wait(2-1);																									//	      Wait 2
	}																															//	   Next I
	X1+=SX;																												//	   Add X1,SX
	Y1+=SY;																												//	   Add Y1,SY
	SPEED=15;																											//	   SPEED=15
	DX1=((X1-XS)/SPEED);																					//	   DX1=((X1-XS)/SPEED)
	DX2=((X1+SZER-XS)/SPEED);																			//	   DX2=((X1+SZER-XS)/SPEED)
	DY1=((Y1-YS)/SPEED);																					//	   DY1=((Y1-YS)/SPEED)
	DY2=((Y1+WYS-YS)/SPEED);																			//	   DY2=((Y1+WYS-YS)/SPEED)
																																//
	XB1=XS; YB1=YS; XB2=XS; YB2=YS;																//	   XB1=XS : YB1=YS : XB2=XS : YB2=YS
	do {																													//	   Repeat
		XB1+=DX1;																										//	      Add XB1,DX1
		XB2+=DX2;																										//	      Add XB2,DX2
		YB1+=DY1;																										//	      Add YB1,DY1
		YB2+=DY2;																										//	      Add YB2,DY2
		if( Abs(X1-XB1)<SPEED ) { XB1=X1; }													//	      If Abs(X1-XB1)<SPEED : XB1=X1 : End If
		if( Abs(Y1-YB1)<SPEED ) { YB1=Y1; }													//	      If Abs(Y1-YB1)<SPEED : YB1=Y1 : End If
		if( Abs(X1+SZER-XB2)<SPEED ) { XB2=X1+SZER; }								//	      If Abs(X1+SZER-XB2)<SPEED : XB2=X1+SZER : End If
		if( Abs(Y1+WYS-YB2)<SPEED ) { YB2=Y1+WYS; }									//	      If Abs(Y1+WYS-YB2)<SPEED : YB2=Y1+WYS : End If
		rysuj();
		_Box( XB1,YB1,XB2,YB2 );																		//	      Box XB1,YB1 To XB2,YB2
		WaitVbl();																									//	      Wait Vbl
																																//	      Box XB1,YB1 To XB2,YB2
	} while( !( XB1==X1 && YB1==Y1 && XB2==X1+SZER && YB2==Y1+WYS) );//	   Until XB1=X1 and YB1=Y1 and XB2=X1+SZER and YB2=Y1+WYS
																																//	   Gr Writing 0
																																//	End Proc
}

void WAIT_NO_MOUSE(void) {
	while( MouseKey()!=0 ) {
		MouseClick();	//jako efekt uboczny czysci bufor klikniec
		ProcessEvents();
	}
}
void _WAIT(aint ILE) {
	//	Procedure _WAIT[ILE]

	aint I=0;
	do {										//	   Repeat
		I++;									//	      Inc I
		if( MouseClick() ) {	//	      If Mouse Click
			KONIEC_INTRA++;			//	         Inc KONIEC_INTRA
			I = ILE;						//	         I=ILE
		}											//	      End If

		Inkey_S();
		if( ScanCode() == 69 ) {  //--ESC
		  ib_skip_intro = true;
		  return;
		}

		//tak najszybciej uporam sie z czyszczenie poprzedniej animacji klatki miecza
		if( ib_czysc_miecz ) {
			Gfx::Color(0,0,0);
			Gfx::Bar(450,0,639,511);
		}

		rysuj();

		WaitVbl();						//	      Wait Vbl
	} while( !(I>=ILE) );		//	   Until I=ILE
								//	End Proc
}
void BLAD(void) {
	//	Procedure BLAD
	//	   Resume
	//	End Proc
}
void BLAD2(void) {
	//	Procedure BLAD2
	//	   Resume Label
	//	End Proc
}

void BUSY_ANIM(void) {
																	//	Procedure BUSY_ANIM
	astr A_S="";
																	//	   Hide On
	Sprite(0,XMouse(),YMouse(),36);	//	   Sprite 0,X Mouse,Y Mouse,36
	//	   A$="Anim 0,(42,4)(43,4)(44,4)(43,4) ; S: Move XM-X,YM-Y,1 ; Jump S"

	A_S="FLOAT S S=4.0/50.0\
			 ANIM -1,('42',S)('43',S)('44',S)('43',S)\
			 LOOP:\
			   X=MOUSE X; Y=MOUSE Y\
			   PAUSE\
			 GOTO LOOP";


	Amal(0,A_S);										//	   Amal 0,A$
	ChannelToSprite(0,0);
	AmalOnOff(0,true);							//	   Amal On 0
	//_ShowCursor(false);
																	//	End Proc
}

void MESSAGE(aint A,astr A_S,aint P,aint M) {
	//	Procedure MESSAGE[A,A$,P,M]

	astr NA_S="";
	aint BB=0,AX=0,AY=0,MUR=0,PL=0;
	if( M>0 ) {												//	   If M>0
		NA_S=MIASTA_S[A];								//	      NA$=MIASTA$(A)
		MUR=MIASTA[A][0][M_MUR];				//	      MUR=MIASTA(A,0,M_MUR)
		BB=20+MUR;											//	      BB=20+MUR
		AX=MIASTA[A][0][M_X];						//	      AX=MIASTA(A,0,M_X)
		AY=MIASTA[A][0][M_Y];						//	      AY=MIASTA(A,0,M_Y)
	} else {													//	   Else
		AX=ARMIA[A][0][TX];							//	      AX=ARMIA(A,0,TX)
		AY=ARMIA[A][0][TY];							//	      AY=ARMIA(A,0,TY)
		NA_S=ARMIA_S[A][0];							//	      NA$=ARMIA$(A,0)
		PL=ARMIA[A][0][TMAG];						//	      PL=ARMIA(A,0,TMAG)
		BB=23+PL;												//	      BB=23+PL
	}																	//	   End If
	WJAZD(AX,AY,80,80,150,100,10);		//	   WJAZD[AX,AY,80,80,150,100,10]
	rysuj();
	OKNO(80,80,150,100);							//	   OKNO[80,80,150,100]
	GADGET(OKX+4,OKY+4,142,74,"",31,2,30,1,-1);//	   GADGET[OKX+4,OKY+4,142,74,"",31,2,30,1,-1]
	GADGET(OKX+50,OKY+80,50,15,GS("215"),8,2,6,31,1);//	   GADGET[OKX+50,OKY+80,50,15,"     Ok  ",8,2,6,31,1]
	PasteBob(OKX+8,OKY+8,BB);					//	   No Mask BB : Paste Bob OKX+8,OKY+8,BB
	gad_text(1.0); Text(OKX+50,OKY+15,NA_S);//	   Ink 1,30 : Text OKX+50,OKY+15,NA$
	NAPISZ(OKX+46,OKY+30,98,40,A_S,P,1,30);//	   NAPISZ[OKX+46,OKY+30,98,40,A$,P,1,30]
	void *sb=StoreBuffer(OKX-1,OKY-1,150+2,100+2);
	WaitVbl();
	WAIT_NO_MOUSE();
	do {															//	   Repeat
		rysuj();
		RestoreBuffer(sb);
		WaitVbl();
	} while( !(MouseClick() && MouseZone()==1) );//	   Until Mouse Click and Mouse Zone=1
	ZOKNO();													//	   ZOKNO
	FreeBuffer(sb);
																		//	End Proc
}
void MESSAGE2(aint A,astr A_S,aint B,aint M,aint WLOT) {
	//	Procedure MESSAGE2[A,A$,B,M,WLOT]

	astr NA_S="";
	aint X=0,Y=0,MUR=0,P=0;
	if( M>0 ) {														//	   If M>0
		NA_S=MIASTA_S[A];										//	      NA$=MIASTA$(A)
		MUR=MIASTA[A][0][M_MUR];						//	      MUR=MIASTA(A,0,M_MUR)
																				//
		X=MIASTA[A][0][M_X];								//	      X=MIASTA(A,0,M_X)
		Y=MIASTA[A][0][M_Y];								//	      Y=MIASTA(A,0,M_Y)
	} else {															//	   Else
		NA_S=ARMIA_S[A][0];									//	      NA$=ARMIA$(A,0)
		X=ARMIA[A][0][TX];									//	      X=ARMIA(A,0,TX)
		Y=ARMIA[A][0][TY];									//	      Y=ARMIA(A,0,TY)
	}																			//	   End If
	if( WLOT==1 ) {												//	   If WLOT=1 : WJAZD[X,Y,100,80,112,120,10] : End If
		WJAZD(X,Y,100,80,112,120,10);
	}
	rysuj();
	OKNO(100,80,112,120);									//	   OKNO[100,80,112,120]
	GADGET(OKX+4,OKY+4,105,114,"",31,2,30,1,1);//	   GADGET[OKX+4,OKY+4,105,114,"",31,2,30,1,1]
																				//
	if( Rnd(1)==1 ) {											//	   If Rnd(1)=1 : B=Hrev(B) : End If
		B=Hrev(B);
	}
	PasteBob(OKX+8,OKY+8,B);							//	   Paste Bob OKX+8,OKY+8,B
	gad_text(1.0); Text(OKX+12,OKY+80,NA_S);	//	   Ink 1,30 : Text OKX+12,OKY+80,NA$
	// !!! BUG ? P nie jest zdefiniowane
	NAPISZ(OKX+10,OKY+90,88,20,A_S,P,1,30);//	   NAPISZ[OKX+10,OKY+90,88,20,A$,P,1,30]
	void *sb=StoreBuffer(OKX-1,OKY-1,112+2,120+2);
	WaitVbl();
	WAIT_NO_MOUSE();
	do {																	//	   Repeat
		rysuj();
		RestoreBuffer(sb);
		WaitVbl();
	} while( !( MouseClick() && MouseZone() == 1) );//	   Until Mouse Click and Mouse Zone=1
	ZOKNO();															//	   ZOKNO
	FreeBuffer(sb);
																				//	End Proc
}

void OUTLINE(aint X,aint Y,astr A_S,aint K1,aint K2) {
		//	Procedure OUTLINE[X,Y,A$,K1,K2]
		//	   Gr Writing 0
		//	   Ink K2 : Text X,Y+1,A$ : Text X+1,Y,A$ : Text X-1,Y,A$ : Text X,Y-1,A$
		//	   Ink K1 : Text X,Y,A$
		//	End Proc
	Gfx::Color(0.2f,0.2f,0.2f);
	Text(X,Y+1,A_S); Text(X+1,Y,A_S); Text(X-1,Y,A_S); Text(X,Y-1,A_S);
	Gfx::Color(1.f,1.f,1.f);
	Text(X,Y,A_S);
}
void _M_FADE(aint SPEED) {
												//	Procedure _M_FADE[SPEED]
	aint SPEED2=0, I=0;

	SPEED2=SPEED;					//	   SPEED2=SPEED
	I=43;									//	   I=43
												//	'   If BOMBA3 : A=ARMIA(50,1,1) : End If
	do {									//	   Repeat
		I--;								//	      Dec I
		Mvolume(I);					//	      Mvolume I
		Wait(SPEED);				//	      Wait SPEED
	} while(I>0);					//	   Until I=0
	MusicStop();					//	   Music Stop
	Mvolume(50);					//	   Mvolume 50
												//	End Proc
}
void _TRACK_FADE(aint SPEED) {
	//	Procedure _TRACK_FADE[SPEED]
	//	   SPEED2=SPEED
	//	   I=63
	//	   A=Vumeter(0) : Add A,-1
	//	   B=Vumeter(1) : Add B,-1
	//	   C=Vumeter(2) : Add C,-1
	//	   D=Vumeter(3) : Add D,-1
	//	   Repeat
	//	      Dec SPEED2
	//	      If SPEED2=0
	//	         Add A,-1,0 To A
	//	         Add B,-1,0 To B
	//	         Add C,-1,0 To C
	//	         Add D,-1,0 To D
	//	         Dec I
	//	         SPEED2=SPEED
	//	      End If
	//	      Wait Vbl
	//	      Doke $DFF0A8,A
	//	      Doke $DFF0B8,B
	//	      Doke $DFF0C8,C
	//	      Doke $DFF0D8,D
	//	   Until I=5
	//	   Track Stop
	//	End Proc

	aint SPEED2=0, I=0;

	SPEED2=SPEED;
	I=63;
	do {
		I--;
		Mvolume(I);
		Wait(SPEED);
	} while(I>5);
	MusicStop();
	Mvolume(50);
}
void FX(aint SAM) {
										//	Procedure FX[SAM]
										//	   Add KANAL,1,1 To 3
										//	   If KANAL=1 : KAN=%10 : End If
										//	   If KANAL=2 : KAN=%100 : End If
										//	   If KANAL=3 : KAN=%1000 : End If
										//	   Sam Play KAN,SAM
	SamPlay(SAM);
										//	End Proc
}
void CHECK(aint A) {
		//	Procedure CHECK[A]
		//	   SK=Screen
		//	   Screen 1 : Print At(1,1);"        " : Print At(1,1);A : Screen SK
		//	   'Wait Key
		//	End Proc
}
void CZEKAJ(void) {
	//!!! no tu to sie Puchcik nie postaral, czekanie w ten sposob to skandal
	//!!! mogl np. badac ile lini ekranu sie wyrysowalo czytajac odpowiedni rejestr
	//!!! a tak to mimo testu predkosci na kazdej Amidze gra moze dzialac nieco inaczej...
	//	Procedure CZEKAJ
	//	   For CZ=1 To AMIGA : Next CZ
	//	End Proc
	SDL_Delay(AMIGA);
}
void SPEED_CHECK(void) {
	//	Procedure SPEED_CHECK
	//	   T=Timer
	//	   For I=1 To 100000 : Next I
	//	   T2=Timer
	//	   AMIGA=20000/(T2-T)
	//	   '   Print "your power:";AMIGA,T2-T
	//	   '   Wait Key
	//	End Proc
	//!!!
	AMIGA = 1;
}

void CENTER(aint X,aint Y,aint FLOOD) {
	//	Procedure CENTER[X,Y,FLOOD]
	aint ZX=0,ZY=0,DX=0,DY=0;

	X += -160;													//	   Add X,-160
	Y += -CENTER_V;											//	   Add Y,-CENTER_V
	if( X<0 ) X=0;											//	   If X<0 : X=0 : End If
	if( X>MSX ) X=MSX;									//	   If X>MSX : X=MSX : End If
	if( Y<0 ) Y=0;											//	   If Y<0 : Y=0 : End If
	if( Y>MSY ) Y=MSY;									//	   If Y>MSY : Y=MSY : End If
	if( FLOOD > 0 ) {										//	   If FLOOD>0
		ZX=Sgn(X-SX)*8*FLOOD;							//	      ZX=Sgn(X-SX)*8*FLOOD
		ZY=Sgn(Y-SY)*8*FLOOD;							//	      ZY=Sgn(Y-SY)*8*FLOOD
		do {															//	      Repeat
			if(	Abs(DX)>Abs(ZX) ) SX+=ZX;		//	         If Abs(DX)>Abs(ZX) : Add SX,ZX : End If
			if( Abs(DY)>Abs(ZY) ) SY+=ZY;		//	         If Abs(DY)>Abs(ZY) : Add SY,ZY : End If
			DX=SX-X;												//	         DX=(SX-X)
			DY=SY-Y;												//	         DY=(SY-Y)
			WaitVbl();											//	         Wait Vbl
			ScreenOffset(0,SX,SY);					//	         Screen Offset 0,SX,SY : View
		} while( !(Abs(DX)<=Abs(ZX) && Abs(DY)<=Abs(ZY)) );	//	      Until Abs(DX)<=Abs(ZX) and Abs(DY)<=Abs(ZY)
	} else {														//	   Else
		SX=X; SY=Y;												//	      SX=X : SY=Y
		ScreenOffset(0,SX,SY);						//	      Screen Offset 0,SX,SY : View
	}																		//	   End If
																			//
}	//	End Proc
void SKROL(aint A) {
	//	Procedure SKROL[A]

	aint X=0,Y=0,XO=0,YO=0,XF=0,YF=0,X2=0,Y2=0,DX=0,DY=0;
									//	   Auto View On
	X=XMouse();			//	   X=X Mouse
	Y=YMouse();			//	   Y=Y Mouse
	XO=X; YO=Y;			//	   XO=X : YO=Y
	XF=XScreen(X);	//	   XF=X Screen(X)
	YF=YScreen(Y);	//	   YF=Y Screen(Y)
	if( PREFS[2]==0 ) {						//	   If PREFS(2)=0
																//	      '      Change Mouse 33
	} else {											//	   Else
		LimitMouse(0,0,600,600);		//	      Limit Mouse 0,0 To 600,600
																//	      Hide On
	}															//	   End If
	while( MouseKey()==PRAWY ) {	//	   While Mouse Key=PRAWY
		rysuj();
		WaitVbl();									//	      Wait Vbl
		if( PREFS[2]==0 ) {					//	      If PREFS(2)=0
			X2=XScreen(XMouse());			//	         X2=X Screen(X Mouse)
			Y2=YScreen(YMouse());			//	         Y2=Y Screen(Y Mouse)
			DX=XF-X2;									//	         DX=XF-X2
			DY=YF-Y2;									//	         DY=YF-Y2
			SX=SX+DX; SY=SY+DY;				//	         SX=SX+DX : SY=SY+DY
		} else {										//	      Else
			DX=(X-XMouse())*2;				//	         DX=(X-X Mouse)*2
			DY=(Y-YMouse())*2;				//	         DY=(Y-Y Mouse)*2
			SX=SX-DX; SY=SY-DY;				//	         SX=SX-DX : SY=SY-DY
			X=XMouse(); Y=YMouse();		//	         X=X Mouse : Y=Y Mouse
		}														//	      End If
		if( SX<0 ) SX = 0;					//	      If SX<0
																//	         SX=0
																//	      End If
		if( SY<0 ) SY = 0;					//	      If SY<0
																//	         SY=0
																//	      End If
		if( SX>MSX ) SX=MSX;				//	      If SX>MSX
																//	         SX=MSX
																//	      End If
		if( SY>MSY ) SY=MSY;				//	      If SY>MSY
																//	         SY=MSY
																//	      End If
		ScreenOffset(0,SX,SY);			//	      Screen Offset 0,SX,SY
	}															//	   Wend
	if( PREFS[2]==1 ) {						//	   If PREFS(2)=1
		LimitMouse(128,40,447,298);	//	      Limit Mouse 128,40 To 447,298
//	      X Mouse=XO
//	      Y Mouse=YO
	}															//	   End If
																//	   Auto View Off
	if( A==1 ) ChangeMouse(CELOWNIK);//	   If A=1 : Change Mouse CELOWNIK : End If
																//	   ': Else : Change Mouse BUBY+6 : End If
																//	End Proc
}
void KLAWSKROL(aint KLAW) {
															//	Procedure KLAWSKROL[KLAW]
															//	   Auto View On
	//LOG(toString(KLAW));
	do {												//	   Repeat
		//### - ulepszenie
		//if( KLAW==76 ) SY-=4;			//	      If KLAW=76 Then Add SY,-4
		//if( KLAW==77 ) SY+=4;			//	      If KLAW=77 Then Add SY,4
		//if( KLAW==78 ) SX+=4;			//	      If KLAW=78 Then Add SX,4
		//if( KLAW==79 ) SX-=4;			//	      If KLAW=79 Then Add SX,-4

		if( KeyState(76) ) SY-=4;		//	      If KLAW=76 Then Add SY,-4
		if( KeyState(77) ) SY+=4;		//	      If KLAW=77 Then Add SY,4
		if( KeyState(78) ) SX+=4;		//	      If KLAW=78 Then Add SX,4
		if( KeyState(79) ) SX-=4;		//	      If KLAW=79 Then Add SX,-4

		if( SX<0 ) SX=0;					//	      If SX<0 : SX=0 : End If
		if( SY<0 ) SY=0;					//	      If SY<0 : SY=0 : End If
		if( SX>MSX ) SX=MSX;			//	      If SX>MSX : SX=MSX : End If
		if( SY>MSY ) SY=MSY;			//	      If SY>MSY : SY=MSY : End If
		ScreenOffset(0,SX,SY);		//	      Screen Offset 0,SX,SY
		rysuj();
		WaitVbl();								//	      Wait Vbl

	// } while( KeyState(KLAW)!=0 );//	   Until Key State(KLAW)=False
	//### - ulepszenie
	} while( KeyState(76) || KeyState(77) || KeyState(78) || KeyState(79) );//	   Until Key State(KLAW)=False

															//	   '   Clear Key
															//	   Auto View Off
															//	End Proc
}
void ODL(aint X1,aint Y1,aint X2,aint Y2) {
	//	Procedure ODL[X1,Y1,X2,Y2]

	aint DX=0,DY=0;
	DX=X2-X1;					//	   DX=X2-X1
	DY=Y2-Y1;					//	   DY=Y2-Y1
	ODLEG=Abs((aint)sqrt(DX*DX+DY*DY));	//	   ODLEG=Abs(Sqr(DX*DX+DY*DY))
										//	End Proc
}

void ROB_IMIE(void) {
		//	Procedure ROB_IMIE
		//	   IM$=""
		//	   Dim SAMOGL$(10)
		//	   Dim DZW$(30)
		//	   Restore DANE
		//	   For I=0 To 9
		//	      Read A$
		//	      SAMOGL$(I)=A$
		//	   Next I
	aint I=0,DL=0,A=0;
	astr IM_S="";
	astr SAMOGL_S[10+1];
	astr DZW_S[30+1];
	astr SAM_S="",SPD_S="",L_S="",R_S="",F_S="";
		//	   DANE:
		//	   Data "a","e","i","o","u","i","a","a","e","o"
	const char *dane[] = {"a","e","i","o","u","i","a","a","e","o"};
	for(I=0;I<=9;++I)
		SAMOGL_S[I]=dane[I];

		//	   For I=0 To 30
		//	      Read A$
		//	      DZW$(I)=A$
		//	   Next I
		//	   SP:
		//	   Data "c","f","h","k","p","s","t","p","j","s","s","k","t","p","t","f"
		//	   Data "b","d","g","l","m","n","r","w","z","r","r","r","d","z","b","g"
	const char *sp[] = {
		"c","f","h","k","p","s","t","p","j","s","s","k","t","p","t","f",
		"b","d","g","l","m","n","r","w","z","r","r","r","d","z","b","g"
	};
	for(I=0;I<=30;++I)
		DZW_S[I]=sp[I];

														//
	DL=Rnd(2)+1;							//	   DL=Rnd(2)+1
	for(I=0;I<DL;++I) {				//	   For I=0 To DL
		SAM_S=SAMOGL_S[Rnd(9)];	//	      SAM$=SAMOGL$(Rnd(9))
		SPD_S=DZW_S[Rnd(30)];		//	      SPD$=DZW$(Rnd(30))
		A=Rnd(2);								//	      A=Rnd(2)
		if(A==0) {							//	      If A=0
			IM_S+=SAM_S;					//	         IM$=IM$+SAM$
			IM_S+=SPD_S;					//	         IM$=IM$+SPD$
		}												//	      End If
		if(A==1) {							//	      If A=1
			IM_S+=SPD_S;					//	         IM$=IM$+SPD$
			IM_S+=SAM_S;					//	         IM$=IM$+SAM$
		}												//	      End If
		if(A==2) {							//	      If A=2
			IM_S+=SAM_S;					//	         IM$=IM$+SAM$
		}												//	      End If
	}													//	   Next I

	L_S=Upper_S(Left_S(IM_S,1));				//	   L$=Left$(IM$,1) : L$=Upper$(L$)
	R_S=Right_S(IM_S,Len(IM_S)-1);			//	   R$=Right$(IM$,Len(IM$)-1)
	F_S=L_S+R_S;												//	   F$=L$+R$
	Param_S = F_S;											//	End Proc[F$]
}

void NAPISZ(aint X,aint Y,aint SZER,aint WYS,astr A_S,aint P,aint K1,aint K2) {
																									//	Procedure NAPISZ[X,Y,SZER,WYS,A$,P,K1,K2]
	aint DL=0, I=0, BRO=0, DLUG=0;
	astr ZDANIE_S="", Z_S="", WYRA_S="";

	gad_back(1.0); _Bar(X-2,Y-10,X+SZER,Y+WYS);		//	   Ink K2 : Bar X-2,Y-10 To X+SZER,Y+WYS
	gad_text(1.0);																//	   Ink K1,K2
																									//	   '   SZPALTA=SZER/5
	DL=Len(A_S);																		//	   DL=Len(A$)
	ZDANIE_S="";																		//	   ZDANIE$=""
	for(I=1;I<=DL;++I) {														//	   For I=1 To DL
		Z_S=Mid_S(A_S,I,1);														//	      Z$=Mid$(A$,I,1)
		if(Z_S=="@") {																//	      If Z$="@"
			if( PRZYGODY[P][P_KIERUNEK]==0 ) { Z_S=GS("216"); }	//	         If PRZYGODY(P,P_KIERUNEK)=0 : Z$="north" : End If
			if( PRZYGODY[P][P_KIERUNEK]==1 ) { Z_S=GS("217");	}//	         If PRZYGODY(P,P_KIERUNEK)=1 : Z$="south" : End If
			if( PRZYGODY[P][P_KIERUNEK]==2 ) { Z_S=GS("218");	}//	         If PRZYGODY(P,P_KIERUNEK)=2 : Z$="east" : End If
			if( PRZYGODY[P][P_KIERUNEK]==3 ) { Z_S=GS("219");	}//	         If PRZYGODY(P,P_KIERUNEK)=3 : Z$="west" : End If
		}																							//	      End If
		if(Z_S=="#") {																//	      If Z$="@"
			if( PRZYGODY[P][P_KIERUNEK]==0 ) { Z_S=GS("220");	}//	         If PRZYGODY(P,P_KIERUNEK)=0 : Z$="north" : End If
			if( PRZYGODY[P][P_KIERUNEK]==1 ) { Z_S=GS("221");	}//	         If PRZYGODY(P,P_KIERUNEK)=1 : Z$="south" : End If
			if( PRZYGODY[P][P_KIERUNEK]==2 ) { Z_S=GS("222");	}//	         If PRZYGODY(P,P_KIERUNEK)=2 : Z$="east" : End If
			if( PRZYGODY[P][P_KIERUNEK]==3 ) { Z_S=GS("223");	}//	         If PRZYGODY(P,P_KIERUNEK)=3 : Z$="west" : End If
		}																							//	      End If

																									//
		if(Z_S=="*") {ROB_IMIE(); Z_S=Param_S;}				//	      If Z$="*" : ROB_IMIE : Z$=Param$ : End If
		if(Z_S=="§") {Z_S=MIASTA_S[PRZYGODY[P][P_X]];}//	      If Z$="#" : Z$=MIASTA$(PRZYGODY(P,P_X)) : End If
		if(Z_S=="&") {Z_S=MIASTA_S[PRZYGODY[P][P_NAGRODA]];}//	      If Z$="&" : Z$=MIASTA$(PRZYGODY(P,P_NAGRODA)) : End If
		if(Z_S=="$") {Z_S=IM_PRZYGODY_S[P];}					//	      If Z$="$" : Z$=IM_PRZYGODY$(P) : End If
		if(Z_S=="%") {BRO=PRZYGODY[P][P_BRON]; Z_S=BRON2_S[BRON[BRO][B_TYP]]+" "+BRON_S[BRO];}//	      If Z$="%" : BRO=PRZYGODY(P,P_BRON) : Z$=BRON2$(BRON(BRO,B_TYP))+" "+BRON$(BRO) : End If
		if(Z_S=="°") {Z_S=RASY_S[PRZYGODY[P][P_BRON]];}//	      If Z$="¹" : Z$=RASY$(PRZYGODY(P,P_BRON)) : End If
		WYRA_S=WYRA_S+Z_S;														//	      WYRA$=WYRA$+Z$
																									//
		if( Z_S==" " || Z_S=="." || Z_S=="?" ) {			//	      If Z$=" " or Z$="." or Z$="?"
			DLUG=TextLength(ZDANIE_S+WYRA_S);						//	         DLUG=Text Length(ZDANIE$+WYRA$)
			if( DLUG<SZER ) {														//	         If DLUG<SZER
				ZDANIE_S+=WYRA_S;													//	            ZDANIE$=ZDANIE$+WYRA$
				WYRA_S="";																//	            WYRA$=""
			} else {																		//	         Else
				Text(X,Y,ZDANIE_S);												//	            Text X,Y,ZDANIE$
				Y+=10;																		//	            Add Y,10
				ZDANIE_S=WYRA_S;													//	            ZDANIE$=WYRA$
				WYRA_S="";																//	            WYRA$=""
			}																						//	         End If
		}																							//	      End If
		if( I==DL ) Text(X,Y,ZDANIE_S+WYRA_S);				//	      If I=DL : Text X,Y,ZDANIE$+WYRA$ : End If
	}																								//	   Next I
																									//
																									//	End Proc
}
