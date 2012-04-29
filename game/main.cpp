
#include <Engine2d/Core.h>
#include <Engine2d/Gfx.h>

#include "main.h"
#include "Amos.h"
#include "AmosImage.h"
#include "legion.h"
#include "utl_locale.h"

#include <SDL_main.h>
#include <SDL.h>

using namespace Core;
using namespace Gfx;

Settings *setts = 0;
int action_delay = 90;

int main(int argc,char* argv[]) {

	int li_ret, li_filtering;

	setts = new Settings();
	li_ret = setts->ReadFile("Legion.config");
	if( li_ret < 0 ) {
		cerr << "Error loading configuration file" << endl;
	}

	bool lb_fullscreen = false;
	if( setts->Exists("Fullscreen") ) {
		lb_fullscreen = setts->GetValB("Fullscreen");
	}

	ib_full_screen = lb_fullscreen;
	ib_resizable = false;

	Settings s;
	if( lb_fullscreen ) {
		il_screen_width = 800;
		il_screen_height = 600;
		s = setts->Extract("Screen");
	} else {
		il_screen_width = DISPLAY_WIDTH;
		il_screen_height = DISPLAY_HEIGHT;
		s = setts->Extract("Window");
	}
	if( s.isValid() ) {
		long v;
		v = s.GetValI(".Width");
		if( v > 0 ) il_screen_width = v;
		v = s.GetValI(".Height");
		if( v > 0 ) il_screen_height = v;
	}

	is_screen_title = "Legion";

	if( argc >= 2 ) {
		gs_language = argv[1];
	} else {
		if( setts->Exists("Language") ) {
			gs_language = setts->GetValS("Language");
			if( gs_language == "" )
				gs_language = "PL";
		}
	}

	Init();	//inicjujemy tak szybko jak sie da co by nie zwlekac z otwarciem okna

	//na dobry poczatek czyscimy ekran na czarno
	Gfx::Color(0,0,0);
	Gfx::Cls();
	Core::SwapBuffers();

	//Tempo akcji w terenie
	if( setts->Exists("ActionTempo") ) {
		int tempo = setts->GetValI("ActionTempo");
		if( tempo < 1 ) tempo=1;
		if( tempo > 5 ) tempo=5;
		switch( tempo ) {
			case 1:	action_delay = 150; break;
			case 2:	action_delay = 120; break;
			case 3:	action_delay = 90; break;
			case 4:	action_delay = 50; break;
			case 5:	action_delay = 20; break;
			default: break;
		}
	}

	//Sposob filtrowania grafiki
	li_filtering = 1;	//linear
	if( setts->Exists("Filtering") ) {
		int f = setts->GetValI("Filtering");
		if( f < 0 ) f=0;
		if( f > 4 ) f=4;
		li_filtering = f;
	}
	switch( li_filtering ) {
		case 0:	//NEAREST
			PTex::SetDefaultFiltering(PTex::FM_NEAREST);
			HQScaleType = SCLT_NONE;
			break;
		case 1:	//LINEAR
			PTex::SetDefaultFiltering(PTex::FM_LINEAR);
			HQScaleType = SCLT_NONE;
			break;
		case 2:	//BILINEAR
			PTex::SetDefaultFiltering(PTex::FM_BILINEAR);
			HQScaleType = SCLT_NONE;
			break;
		case 3:	//Scale2x
			PTex::SetDefaultFiltering(PTex::FM_LINEAR);
			HQScaleType = SCLT_SCALE2X;
			break;
		case 4:	//hq2x
			PTex::SetDefaultFiltering(PTex::FM_LINEAR);
			HQScaleType = SCLT_HQ2X;
			break;
		default:
			PTex::SetDefaultFiltering(PTex::FM_NEAREST);
			HQScaleType = SCLT_NONE;
			break;
	}

	//Cienie wysokiej jakosci
	HQShadows = false;
	if( setts->Exists("HQShadows") ) {
		HQShadows = setts->GetValB("HQShadows");
	}

	//po wczytaniu ustawien przechodzimy do odpalenia srodowiska Amosa
	_AmosInit();

		ProjectionOrtho(0,DISPLAY_WIDTH,DISPLAY_HEIGHT,0);

		_resize(il_screen_width,il_screen_height,0);

		FrameTiming(FTM_NEW_FRAME);		//zaczynamy nowa ramke
		main_code();

	_AmosFinish();
	Finish();
	return 0;
}
