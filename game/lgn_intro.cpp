
#include "Amos.h"

#include "legion.h"
#include "lgn_diskacs.h"
#include "lgn_intro.h"
#include "lgn_util.h"
#include "utl_locale.h"


bool ib_czysc_miecz = false,
     ib_skip_intro;
aflt _fade_factor=0.0;
aint _intro_x1, _intro_y1, _intro_x2, _intro_y2;
astr _intro_a, _intro_b;

void _intro_sub_fading_rysuj(void) {
  Gfx::Cls(0.f,0.f,0.f);
  Gfx::Color(1.f,1.f,1.f);
  Text(_intro_x1,_intro_y1,_intro_a);
  Text(_intro_x2,_intro_y2,_intro_b);
  Fade(_fade_factor);
}
void _INTRO_SUB_FADING(aint X1,aint Y1,astr A_S,aint X2,aint Y2,astr B_S) {
	//	   FADING:
	//	   Repeat : Until Timer mod 3=1
	//	   Text X1,Y1,A$ : Repeat : Until Timer mod 3=1 : Text X2,Y2,B$
	//	   Fade 2 To 2 : _WAIT[100]
	//	   Fade 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 : Wait 25 : Repeat : Until Timer mod 3=0 : Ink 0 : Bar 130,190 To 415,280
	//	   Return
	_intro_x1 = X1;
	_intro_y1 = Y1;
	_intro_x2 = X2;
	_intro_y2 = Y2;
	_intro_a = A_S;
	_intro_b = B_S;
	rysuj_ekran_ptr = _intro_sub_fading_rysuj;
	for( int f=30; f>=0; --f ) {
	  _fade_factor = f/30.0;
		_WAIT(1);
	}
  _fade_factor = 0.0;
	_WAIT(100-30);
	for( int f=0; f<=30; ++f ) {
	  _fade_factor = f/30.0;
		_WAIT(1);
	}
	rysuj_ekran_ptr = 0;
	return;
}
void _intro_rysuj_logo(void) {
  Gfx::Color(0,0,0);
  _ClearRaster();
  _DrawIff(-1,0,0);
  Fade(_fade_factor);
}
void _INTRO(void) {
	//	Procedure _INTRO

	aint X1=0,Y1=0,X2=0,Y2=0;
	astr A_S="",B_S="";

	if( ib_skip_intro) goto koniec;

	Gfx::Color(0,0,0);
	_ClearRaster();
//	SwapBuffers();
//	_ClearRaster();
	//	   Auto View Off
	//	   Set Sprite Buffer 300
	//	   Screen Open 2,64,10,32,L : Flash Off : Screen Hide
	ScreenOpen(2,64,10,32,LOWRES);
	//	   Screen Open 3,64,10,32,L : Flash Off : Screen Hide
	ScreenOpen(3,64,10,32,LOWRES);
	//	   Screen Open 0,640,512,16,-1 : Flash Off : Cls 0 : Screen Hide : Hide
	ScreenOpen(0,640,512,16,-1);

	//	   _LOAD[KAT$+"miecz","legion:miecz","Legion",0]
	_LOAD(KAT_S+"miecz",KAT_S+"miecz.abk_sp","Legion",0);
	//	   _LOAD[KAT$+"mod.intro","legion:mod.intro","Legion",6]
	_LOAD(KAT_S+"mod.intro",KAT_S+"mod.intro.mod","Legion",6);

	//	   Track Loop On : Led Off
	TrackLoop(true);


	USTAW_FONT("bodacious",FONT_BODACIOUS,42,1);			//	   USTAW_FONT["bodacious",42]
	//	   Gr Writing 0
	//	   Flash Off : Get Bob Palette
	//	   For I=0 To 15 : Colour I+16,Colour(I) : Next I
	//	   For I=0 To 15 : Colour I,D : Add D,$222 : Next I
	//	   Screen 2 : Get Palette 0
	//	   Screen Open 1,640,512,16,-1
	ScreenOpen(1,640,512,16,-1);
	//	   Cls 0 : Flash Off
	//	   Screen 1 : Get Palette 0 : Screen Hide : Hide
	//	   Screen Display 1,150,,,
	ScreenDisplay(1,150,NOPARI,NOPARI,NOPARI);
	//	   Auto View On

	//	   _LOAD[KAT$+"title2","legion:title2","Legion",2]
	_LOAD(KAT_S+"title2",KAT_S+"title2.iff","Legion",2);

	//	   For I=16 To 31 : Screen 0 : KOL=Colour(I) : Screen 1 : Colour I,KOL : Next I
	//	   Screen 3 : Get Palette 1
	//	   'BOMBA4=True

	//	   Screen 0 : _LOAD[KAT$+"gobilog.16","legion:gobilog.16","Legion",2] : Screen Show 0 : View
	Screen(0);
	_LOAD(KAT_S+"gobilog.16",KAT_S+"gobilog.16.iff","Legion",2);

	//	   Track Play 3
	TrackPlay(3);

  //rysujemy GOBI logo
  rysuj_ekran_ptr = _intro_rysuj_logo;

	for( int f=30; f>=0; --f ) {
		_fade_factor = f/30.0;
		_WAIT(1);
    if( ib_skip_intro) goto koniec;
	}

	//	   Amos To Front : View
	//	   _WAIT[150]
	_fade_factor = 0.0;
	_WAIT(150);
	if( ib_skip_intro) goto koniec;

	//	   Fade 2 : Wait 30 : Cls 0
	for( int f=0; f<=30; ++f ) {
		_fade_factor = f/30.0;
		_WAIT(1);
    if( ib_skip_intro) goto koniec;
	}

	//	   For I=0 To 16 : Colour I,0 : Next I
	X1=200; Y1=235; A_S=GS("I006");	//	   X1=200 : Y1=235 : A$="  presents"
	X2=130; Y2=270; B_S=GS("I007");						//	   X2=130 : Y2=270 : B$=""
	//	   Gosub FADING
	_INTRO_SUB_FADING(X1,Y1,A_S,X2,Y2,B_S);
	if( ib_skip_intro) goto koniec;

							//
							//	   Sprite 0,365,70,1
							//	   A$="Anim 0,(1,3)(2,3)(3,3)(4,3)(5,3)(6,3)(7,3)(8,3)(9,3)(10,3)(11,3)(12,3)(13,3)(14,3)(15,3)(16,3)(17,3)(18,3)(19,3);"
							//	   Amal 0,A$
							//	   Repeat : Until Timer mod 3=0
							//	   Amal On 0
	Screen(1);	//	   Screen 1
							//	   For I=0 To 16 : Colour I,0 : Next I
							//
	ib_czysc_miecz = true;
	Sprite(0,365,70,1);
	A_S = "FLOAT S; S=3.0/50;	\n\
				 ANIM -1,('1',S)('2',S)('3',S)('4',S)('5',S)('6',S)('7',S)('8',S)('9',S)('10',S)('11',S)('12',S)('13',S)('14',S)('15',S)('16',S)('17',S)('18',S)('19',S);	\n\
				 PAUSE IS ANIMATING; ";
	Amal(0,A_S);
	ChannelToSprite(0,0);
	AmalOnOff(0,true);

	KONIEC_INTRA = 0;

	//	   Repeat
	do {
		//	      Screen 1 : Screen To Front 1 : Screen Show 1 : Fade 2 To 3
		Screen(1);
    rysuj_ekran_ptr = _intro_rysuj_logo;
		for( int f=30; f>=0; --f ) {
			_fade_factor = f/30.0;
			_WAIT(1);
      if( ib_skip_intro) goto koniec;
		}

		//	      _WAIT[200] : Exit If KONIEC_INTRA>2
    _fade_factor = 0.0;
		_WAIT(200-30); if( KONIEC_INTRA>2 ) break;
    if( ib_skip_intro) goto koniec;
		//	      Fade 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		//	      _WAIT[30] : Exit If KONIEC_INTRA>2
		for( int f=0; f<=30; ++f ) {
			_fade_factor = f/30.0;
			_WAIT(1);
      if( ib_skip_intro) goto koniec;
		}

    rysuj_ekran_ptr = 0;

		Screen(0);																	//	      Screen 0
		ScreenDisplay(0,140,NOPARI,NOPARI,NOPARI);	//	      Screen Display 0,140,,,
																								//	      For I=0 To 16 : Colour I,0 : Next I
																								//
																								//	      Screen To Front 0 : Screen Show
		X1=130; Y1=220; A_S=GS("I014");
		X2=130; Y2=270; B_S="Marek Lech";
		_INTRO_SUB_FADING(X1,Y1,A_S,X2,Y2,B_S);
		if( KONIEC_INTRA>2 ) break;
    if( ib_skip_intro) goto koniec;

		X1=130; Y1=220; A_S=GS("I015");
		X2=130; Y2=270; B_S="Marcin Puchta";
		_INTRO_SUB_FADING(X1,Y1,A_S,X2,Y2,B_S);
		if( KONIEC_INTRA>2 ) break;
    if( ib_skip_intro) goto koniec;

//		X1=130; Y1=220; A_S=GS("I010");					//	      X1=130 : Y1=220 : A$="   program   "
		X1=115; Y1=220; A_S=GS("I010");					//	      X1=130 : Y1=220 : A$="   program   "
		X2=130; Y2=270; B_S="Marcin Puchta";		//	      X2=130 : Y2=270 : B$="Marcin Puchta"
		_INTRO_SUB_FADING(X1,Y1,A_S,X2,Y2,B_S);	//	      Gosub FADING : Exit If KONIEC_INTRA>2
		if( KONIEC_INTRA>2 ) break;
    if( ib_skip_intro) goto koniec;

		X1=135; Y1=220; A_S=GS("I011");					//	      X1=135 : Y1=220 : A$="   graphics "
		X2=130; Y2=270; B_S="Andrzej Puchta";		//	      X2=130 : Y2=270 : B$="Andrzej Puchta"
		_INTRO_SUB_FADING(X1,Y1,A_S,X2,Y2,B_S);	//	      Gosub FADING : Exit If KONIEC_INTRA>2
 		if( KONIEC_INTRA>2 ) break;
    if( ib_skip_intro) goto koniec;

		X1=135; Y1=220; A_S=GS("I012");					//	      X1=135 : Y1=220 : A$=" music & sfx"
		X2=130; Y2=270; B_S="Marcin Puchta";		//	      X2=130 : Y2=270 : B$="Marcin Puchta"
		_INTRO_SUB_FADING(X1,Y1,A_S,X2,Y2,B_S);	//	      Gosub FADING : Exit If KONIEC_INTRA>2
 		if( KONIEC_INTRA>2 ) break;
    if( ib_skip_intro) goto koniec;

//		X1=135; Y1=240; A_S=GS("I013");					//	      X1=135 : Y1=240 : A$="greetings to:"
//		X2=130; Y2=270; B_S="";								//	      X2=130 : Y2=270 : B$=""
		X1=135; Y1=220; A_S=GS("I013");					//	      X1=135 : Y1=240 : A$="greetings to:"
		X2=130; Y2=270; B_S="M.Malachowski";		//	      X2=130 : Y2=270 : B$=""
		_INTRO_SUB_FADING(X1,Y1,A_S,X2,Y2,B_S);	//	      Gosub FADING : Exit If KONIEC_INTRA>2
 		if( KONIEC_INTRA>2 ) break;
    if( ib_skip_intro) goto koniec;

//		X1=135; Y1=220; A_S="M.Malachowski";		//	      X1=135 : Y1=220 : A$="M.Malachowski"
//		X2=130; Y2=270; B_S=" Marek Lech";			//	      X2=130 : Y2=270 : B$=" Marek Lech"
//		_INTRO_SUB_FADING(X1,Y1,A_S,X2,Y2,B_S);	//	      Gosub FADING : Exit If KONIEC_INTRA>2
// 		if( KONIEC_INTRA>2 ) break;

		KONIEC_INTRA=2;										//	      KONIEC_INTRA=2
	} while( ! (KONIEC_INTRA>2) );			//	   Until KONIEC_INTRA>2

	//	   Goto OVER
	//	   FADING:
	//	   Repeat : Until Timer mod 3=1
	//	   Text X1,Y1,A$ : Repeat : Until Timer mod 3=1 : Text X2,Y2,B$
	//	   Fade 2 To 2 : _WAIT[100]
	//	   Fade 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 : Wait 25 : Repeat : Until Timer mod 3=0 : Ink 0 : Bar 130,190 To 415,280
	//	   Return
	//
	//	   OVER:
	//	   Fade 2
	//	   Wait 25
	for( int f=0; f<=30; ++f ){
		_fade_factor = f/30.0;
		_WAIT(1);
    if( ib_skip_intro) goto koniec;
	}

koniec:
  rysuj_ekran_ptr = 0;

	//	   Amal Off
	//	   Sprite Off
	AmalOnOff(-1,false);
	SpriteOnOff(-1,false);

	//	   Screen Close 2
	//	   Screen Close 3
	//	   If Screen=0
	//	      Screen Close 1 : Screen Close 0
	//	   Else
	//	      Screen Close 0 : Screen Close 1
	//	   End If
	ScreenClose(2);
	ScreenClose(3);
	if( Screen() == 0 ) {
		ScreenClose(1); ScreenClose(0);
	} else {
		ScreenClose(0); ScreenClose(1);
	}

	//Gfx::Color(0,0,0);
	//_ClearRaster();
	//SwapBuffers();
	//_ClearRaster();

	//	   Erase 1
	Erase(1);
	//	   Auto View Off
	//	End Proc
}
void EXTRO(void) {
																			//	Procedure EXTRO
																			//	   Hide On
	ScreenOpen(0,320,256,32,LOWRES);

	_LOAD(KAT_S+"czacha.32","legion:czacha.32","Legion",3);	//	   _LOAD[KAT$+"czacha.32","legion:czacha.32","Legion",3]
	_LOAD(KAT_S+"mod.end2","legion:mod.end2","Legion",6);		//	   _LOAD[KAT$+"mod.end2","legion:mod.end2","Legion",6]
	TrackLoop(true); TrackPlay(3);			//	   Track Loop On : Track Play 3
																			//	   View
	Screen(0);

	Gfx::Color(0,0,0);
	_ClearRaster();
	_DrawIff(-1,0,0);
	SwapBuffers();


	WAIT_NO_MOUSE();

	_WAIT(1500);												//	   _WAIT[1500]

	//	   Fade 2
	for(int f=0;f<=30;++f) {
	  Gfx::Color(0,0,0);
		_ClearRaster();
		_DrawIff(-1,0,0);
		Fade(f/30.0);
		_WAIT(1);
	}

	_TRACK_FADE(1);											//	   _TRACK_FADE[1]
																			//	End Proc
}

void _pcintro_rysuj_maksyme(void) {
  static int x=-999888, y;
  if( x == -999888 ) {
    if( GetLang()=="PL" ) {
      x=45;
      y=150;
    } else {
      x=70;
      y=150;
    }
  }

  Gfx::Color(0.f,0.f,0.f);
  _ClearRaster();
  Gfx::Color(1.f,1.f,1.f);
  Text(x,y+0,   GS("I000") );
  Text(x,y+40,  GS("I001") );
  Text(x,y+80,  GS("I002") );
  Text(x,y+120, GS("I003") );
  Text(x,y+160, GS("I004") );
  Fade(_fade_factor);
}
void _pcintro_rysuj_logo(void) {
  Gfx::Color(0,0,0);
  _ClearRaster();
  _DrawIff(-1,0,0);
  Fade(_fade_factor);
}
void pc_intro(void) {

  ib_skip_intro = false;

	ScreenOpen(0,640,512,16,HIRES|LACED);
	USTAW_FONT("bodacious",FONT_BODACIOUS,32,1);

	rysuj_ekran_ptr = _pcintro_rysuj_maksyme;

  //rozjasniamy tekst
	for( int f=30; f>=0; --f ) {
	  _fade_factor = f/30.0;
		_WAIT(1);
		if( ib_skip_intro) goto koniec;
	}

  //pokazujemy tekst przez pewien czas
  _fade_factor = 0;
	_WAIT(500);
	if( ib_skip_intro) goto koniec;

	//zciemniamy tekst
	for( int f=0; f<=30; ++f ) {
	  _fade_factor = f/30.0;
		_WAIT(1);
		if( ib_skip_intro) goto koniec;
	}

	_LOAD("smfk_logo","smfk_logo.png","Legion",2);

	rysuj_ekran_ptr = _pcintro_rysuj_logo;

	//rozjasniamy logo
	for(int f=30;f>=0;--f) {
	  _fade_factor = f/30.0;
		_WAIT(1);
		if( ib_skip_intro) goto koniec;
	}

	USTAW_FONT("bodacious",FONT_BODACIOUS,42,1);

  _fade_factor = 0;
	_WAIT(150);
	if( ib_skip_intro) goto koniec;

	//zciemniamy logo
	for(int f=0;f<=30;++f) {
		_fade_factor = f/30.0;
		_WAIT(1);
		if( ib_skip_intro) goto koniec;
	}

	_INTRO_SUB_FADING(285,235,GS("I005"),0,0,"");

koniec:
	rysuj_ekran_ptr = 0;
}

