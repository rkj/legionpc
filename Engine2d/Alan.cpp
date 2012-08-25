
#include <iostream>
#include <fstream>
#include <sstream>

#include "Alan.h"
#include "Bob.h"

#include "alan_parser.hh"

using namespace cppcc;
using namespace Alan;


namespace Gfx {

class AlanChannel {
protected:
	AlanCode				*code;
	AlanVM					*vm;
	AlanControlable *obj;
	TextureManager  *tex_mgr;
	bool						ib_onoff;

	AlanCode* _parseCode(const string& src);
public:
	AlanChannel(void);
	~AlanChannel();

	int setCode(const string& src_code);

	int initVM(void);
	void onoff(bool o);

	void calc_move(float dt,float &dx, float &dr, float &dy );
	void calc_anim(float dt,LTex* &ltex, string &img );
	void calc_scale(float dt,float &sx, float &sy );
	int run(float dt);
	int debug_run(float dt);

	void bindObject(AlanControlable* obj);
	void setTextureMgr(TextureManager *p_tex_mgr);

	string DumpCode(void);
	string DumpVars(void);

	friend class AlanControlable;
};


bool AlanControlable::AlanGetVarB(const std::string& name) {
	ASSERT( channel != 0, "Obiekt nie jest powi¹zany z kana³em ALANa" );
	ASSERT( channel->code, "Kana³ ALANa ma niezdefiniowany kod" );
	return channel->code->GetVarValB(name);
}
int AlanControlable::AlanGetVarI(const std::string& name) {
	ASSERT( channel != 0, "Obiekt nie jest powi¹zany z kana³em ALANa" );
	ASSERT( channel->code, "Kana³ ALANa ma niezdefiniowany kod" );
	return channel->code->GetVarValI(name);
}
float AlanControlable::AlanGetVarF(const std::string& name) {
	ASSERT( channel != 0, "Obiekt nie jest powi¹zany z kana³em ALANa" );
	ASSERT( channel->code, "Kana³ ALANa ma niezdefiniowany kod" );
	return channel->code->GetVarValF(name);
}
std::string AlanControlable::AlanGetVarS(const std::string& name) {
	ASSERT( channel != 0, "Obiekt nie jest powi¹zany z kana³em ALANa" );
	ASSERT( channel->code, "Kana³ ALANa ma niezdefiniowany kod" );
	return channel->code->GetVarValS(name);
}
void AlanControlable::AlanSetVar(const std::string& name,bool v) {
	ASSERT( channel != 0, "Obiekt nie jest powi¹zany z kana³em ALANa" );
	ASSERT( channel->code, "Kana³ ALANa ma niezdefiniowany kod" );
	channel->code->SetVarVal(name,v);
}
void AlanControlable::AlanSetVar(const std::string& name,int v) {
	ASSERT( channel != 0, "Obiekt nie jest powi¹zany z kana³em ALANa" );
	ASSERT( channel->code, "Kana³ ALANa ma niezdefiniowany kod" );
	channel->code->SetVarVal(name,v);
}
void AlanControlable::AlanSetVar(const std::string& name,float v) {
	ASSERT( channel != 0, "Obiekt nie jest powi¹zany z kana³em ALANa" );
	ASSERT( channel->code, "Kana³ ALANa ma niezdefiniowany kod" );
	channel->code->SetVarVal(name,v);
}
void AlanControlable::AlanSetVar(const std::string& name,std::string v) {
	ASSERT( channel != 0, "Obiekt nie jest powi¹zany z kana³em ALANa" );
	ASSERT( channel->code, "Kana³ ALANa ma niezdefiniowany kod" );
	channel->code->SetVarVal(name,v);
}


AlanCode* AlanChannel :: _parseCode(const string& src) {

	//otwieramy strumien
	istringstream *ifs;
	try {
		ifs = new istringstream(src);
	} catch(...) {
		ERROR("B³¹d otwierania strumienia na buforze");
		return 0;
	}

	//tworzymy parser
	AlanParser parser(ifs);

	//parsujemy plik
	AlanCode *cd = 0;
	try {
		cd = parser.parse();
	} catch(ScanException &scex) {
		ERROR((string)scex);
		return 0;
	} catch(ParseException &pex) {
		ERROR( (string) pex + "( before: " + parser.scanner.la(0)->image()
							+ " " + parser.scanner.la(1)->image() + ")" );
		return 0;
	} catch(AlanException &aex) {
		ERROR(aex.Msg());
		return 0;
	}

	return cd;
}

AlanChannel :: AlanChannel(void) {
	code = 0;
	vm = 0;
	obj = 0;
	tex_mgr = 0;
	ib_onoff = false;
}
AlanChannel :: ~AlanChannel() {
	if( 0 != vm ) delete vm;
	if( 0 != code ) delete code;
	//boba nie usuwamy
	//managera tesktur tez nie usuwamy
}

int AlanChannel :: setCode(const string& src_code) {
	if( 0 != code ) delete code;
	code = _parseCode(src_code);
	if( 0 == code)
		return -1;
	return 1;
}

int AlanChannel :: initVM(void) {
	vm = new AlanVM();
	vm->SetCode(code);
	vm->Reset();
	ib_onoff = true;	//moze dzialac
	return 1;
}
void AlanChannel :: onoff(bool o) {
	ib_onoff = o;
}

void AlanChannel :: calc_move(float dt,float &dx, float &dy, float &dr ) {


	AlanState *st = vm->GetState();

	dx = 0.0;
	dy = 0.0;
	dr = 0.0;

	if( 0 == st->move_cnt )	//koniec trasy
		return;

	int step;
	float time, step_time, ot;

	while( dt > 0.000001 ) {
		step = st->move_step;
		step_time = st->move_dt[step];
		time = st->move_time + dt;

		ot = time - step_time;
		if( ot < 0.0 ) {
			//idziemy dalej w ramach tego samego kroku
			dx += st->move_dx[step] * dt;
			dy += st->move_dy[step] * dt;
			dr += st->move_dr[step] * dt;
			st->move_time = time;
			return;
		}

		//doszlismy do konca kroku, albo jeszcze dalej
		//1) Konczymy biezacy krok
		if( step_time > 0.000001 ) {
			dt = step_time - st->move_time;		//tyle pozostalo z biezacego kroku
			dx += st->move_dx[step] * dt;
			dy += st->move_dy[step] * dt;
			dr += st->move_dr[step] * dt;
		} else {
			dx += st->move_dx[step];
			dy += st->move_dy[step];
			dr += st->move_dr[step];
		}
		//2) Rozpoczynamy nowy krok
		step++;
		if( step >= (int)(st->move_dt.size()) )	{	//koniec krokow
			if( st->move_cnt > 0 ) (st->move_cnt)--;
			if( 0 == st->move_cnt ) {					//koniec trasy
				return;
			}
			//idziemy dalej zaczynajac od pierwszego kroku
			step = 0;
		}
		st->move_step = step;
		st->move_time = 0.0;
		dt = ot;
	}

}

void AlanChannel :: calc_anim(float dt,LTex* &ltex,string &img ) {


	AlanState *st = vm->GetState();

	ltex = 0;

	if( 0 == st->anim_cnt )	//koniec animacji
		return;

	int step;
	float time, step_time, ot;
	ltex = 0;
	img = "";

	while( dt > 0.000001 ) {
		step = st->anim_step;
		step_time = st->anim_dt[step];
		time = st->anim_time + dt;

		ot = time - step_time;
		if( ot < 0.0 ) {
			//ciagle trwa ta sama ramka
			img = st->anim_img[step];
			if( 0 != st->tex_mgr ) {
				ltex = st->tex_mgr->GetLTex(img);
			}
			st->anim_time = time;
			return;
		}

		//doszlismy do konca ramki, albo jeszcze dalej
		//1) Konczymy biezacy krok
		dt = step_time - st->anim_time;		//tyle pozostalo z biezacego kroku
		//2) Rozpoczynamy nowy krok
		step++;
		if( step >= (int)(st->anim_dt.size()) )	{	//koniec krokow
			if( st->anim_cnt > 0 ) (st->anim_cnt)--;
			if( 0 == st->anim_cnt ) {					//koniec trasy
				return;
			}
			//idziemy dalej zaczynajac od pierwszego kroku
			step = 0;
		}
		st->anim_step = step;
		st->anim_time = 0.0;
		dt = ot;
	}

}

void AlanChannel :: calc_scale(float dt,float &sx, float &sy ) {

	AlanState *st = vm->GetState();

	sx = 1.0;
	sy = 1.0;

	if( 0 == st->scale_cnt )	//koniec animacji
		return;

	int step;
	float time, step_time, ot;

	if( dt <= 0.000001 ) {
		sx = st->scale_prev_sx;
		sy = st->scale_prev_sy;
		return;
	}

	while( dt > 0.000001 ) {
		step = st->scale_step;
		step_time = st->scale_dt[step];
		time = st->scale_time + dt;

		ot = time - step_time;
		if( ot < 0.0 ) {
			//ciagle trwa ta sama ramka
			float psx,psy;
			if( step > 0 ) {
				psx = st->scale_sx[step-1];
				psy = st->scale_sy[step-1];
			} else {
				psx = 1.0;
				psy = 1.0;
			}
			sx = psx * (1.0 - time / step_time) + st->scale_sx[step] * time / step_time;
			sy = psy * (1.0 - time / step_time) + st->scale_sy[step] * time / step_time;
			st->scale_time = time;
			return;
		}

		//doszlismy do konca kroku, albo jeszcze dalej
		//1) Konczymy biezacy krok
		dt = step_time - st->scale_time;		//tyle pozostalo z biezacego kroku
		if( step_time < 0.000001 ) {
			//dla zerowych czasow kroku przyjmujemy jako skale wartosc zdefiniowana dla kroku
			sx = st->scale_sx[step];
			sy = st->scale_sy[step];
		}
		//2) Rozpoczynamy nowy krok
		step++;
		if( step >= (int)(st->scale_dt.size()) )	{	//koniec krokow
			if( st->scale_cnt > 0 ) (st->scale_cnt)--;
			if( 0 == st->scale_cnt ) {					//koniec trasy
				return;
			}
			//idziemy dalej zaczynajac od pierwszego kroku
			step = 0;
		}
		st->scale_step = step;
		st->scale_time = 0.0;
		dt = ot;
	}
}

int AlanChannel :: run(float dt) {

	if( ! ib_onoff ) return 0;	//kanal wylaczony

	if( obj ) dt *= obj->AlanGetTimeFactor(dt);

//	bool scaling;
	float dx,dy,dr,sx,sy;
	LTex *ltex;
	float obj_sx, obj_sy;
	string img;

	AlanState *st = vm->GetState();

	calc_move(dt,dx,dy,dr);
	calc_anim(dt,ltex,img);
	calc_scale(dt,sx,sy);

	if( obj ) {
		vm->SetVarVal("X",obj->AlanGetX() + dx);
		vm->SetVarVal("Y",obj->AlanGetY() + dy);
		vm->SetVarVal("ROT",obj->AlanGetRot() + dr);
		vm->SetVarVal("DT",dt);

		obj_sx = obj->AlanGetScaleX();
		obj_sy = obj->AlanGetScaleY();
		obj_sx *= sx / st->scale_prev_sx;
		obj_sy *= sy / st->scale_prev_sy;
		st->scale_prev_sx = sx;
		st->scale_prev_sy = sy;
		vm->SetVarVal("SX",obj_sx);
		vm->SetVarVal("SY",obj_sy);

		vm->Continue();

		obj->AlanSetPos(vm->GetVarValF("X"),vm->GetVarValF("Y"));
		obj->AlanSetRot(vm->GetVarValF("ROT"));
		if( 0 != ltex ) obj->AlanSetTex(ltex);
		if( "" != img ) obj->AlanSetImg(img);
		obj->AlanSetScale(vm->GetVarValF("SX"),vm->GetVarValF("SY"));
	} else {
		vm->SetVarVal("X",vm->GetVarValF("X") + dx);
		vm->SetVarVal("Y",vm->GetVarValF("Y") + dy);
		vm->SetVarVal("ROT",vm->GetVarValF("ROT") + dr);
		vm->SetVarVal("DT",dt);

		obj_sx = vm->GetVarValF("SX");
		obj_sy = vm->GetVarValF("SY");
		obj_sx *= sx / st->scale_prev_sx;
		obj_sy *= sy / st->scale_prev_sy;
		st->scale_prev_sx = sx;
		st->scale_prev_sy = sy;
		vm->SetVarVal("SX",obj_sx);
		vm->SetVarVal("SY",obj_sy);

		vm->Continue();
	}

	return 1;
}

int AlanChannel :: debug_run(float dt) {

	if( ! ib_onoff ) return 0;	//kanal wylaczony

	if( obj ) dt *= obj->AlanGetTimeFactor(dt);

//	bool scaling;
	float dx,dy,dr,sx,sy;
	LTex *ltex;
	float obj_sx, obj_sy;
	string img;

	AlanState *st = vm->GetState();

	calc_move(dt,dx,dy,dr);
	calc_anim(dt,ltex,img);
	calc_scale(dt,sx,sy);

	if( obj ) {
		vm->SetVarVal("X",obj->AlanGetX() + dx);
		vm->SetVarVal("Y",obj->AlanGetY() + dy);
		vm->SetVarVal("ROT",obj->AlanGetRot() + dr);
		vm->SetVarVal("DT",dt);

		obj_sx = obj->AlanGetScaleX();
		obj_sy = obj->AlanGetScaleY();
		obj_sx *= sx / st->scale_prev_sx;
		obj_sy *= sy / st->scale_prev_sy;
		st->scale_prev_sx = sx;
		st->scale_prev_sy = sy;
		vm->SetVarVal("SX",obj_sx);
		vm->SetVarVal("SY",obj_sy);

		vm->DebugContinue();

		obj->AlanSetPos(vm->GetVarValF("X"),vm->GetVarValF("Y"));
		obj->AlanSetRot(vm->GetVarValF("ROT"));
		if( 0 != ltex ) obj->AlanSetTex(ltex);
		if( "" != img ) obj->AlanSetImg(img);
		obj->AlanSetScale(vm->GetVarValF("SX"),vm->GetVarValF("SY"));
	} else {
		vm->SetVarVal("X",vm->GetVarValF("X") + dx);
		vm->SetVarVal("Y",vm->GetVarValF("Y") + dy);
		vm->SetVarVal("ROT",vm->GetVarValF("ROT") + dr);
		vm->SetVarVal("DT",dt);

		obj_sx = vm->GetVarValF("SX");
		obj_sy = vm->GetVarValF("SY");
		obj_sx *= sx / st->scale_prev_sx;
		obj_sy *= sy / st->scale_prev_sy;
		st->scale_prev_sx = sx;
		st->scale_prev_sy = sy;
		vm->SetVarVal("SX",obj_sx);
		vm->SetVarVal("SY",obj_sy);

		vm->DebugContinue();
	}

	return 1;
}


void AlanChannel :: bindObject(AlanControlable* ob) {
	obj = ob;
	obj->channel = this;
}
void AlanChannel :: setTextureMgr(TextureManager *p_tex_mgr) {
	tex_mgr = p_tex_mgr;
	if( 0 != vm ) {
		AlanState *st = vm->GetState();
		if( 0 != st ) {
			st->tex_mgr = p_tex_mgr;
		}
	}
}

string AlanChannel :: DumpCode(void) {
	if( code ) return code->DumpCode();
	return "!NO_CODE!";
}

string AlanChannel :: DumpVars(void) {
	if( code ) return code->DumpVars("");
	return "!NO_VARS!";
}



Alan :: Alan(void) {
	tex_mgr = 0;
	debug = false;
	lmp_channels.clear();
}

Alan :: ~Alan() {
	AlanChannel *lo_ac;
	tit_channels lit;
	for( lit = lmp_channels.begin(); lit != lmp_channels.end(); ++lit ) {
		lo_ac = (AlanChannel*)(lit->second);
		if( lo_ac ) delete lo_ac;
	}
}

void* Alan :: _findChannel(const string& name) {
	tit_channels lit;
	lit = lmp_channels.find(name);
	if( lit == lmp_channels.end() )
		return 0;
	return lit->second;
}

int Alan :: openChannel( const string& name, const string& src_code ) {
	int li_ret;

	AlanChannel *lo_ac = (AlanChannel*)_findChannel(name);
	if( 0 != lo_ac ) {
		//return -1;			//juz taki kanal jest
		closeChannel(name);
	}

	lo_ac = new AlanChannel();

	li_ret = lo_ac->setCode(src_code);
	if( li_ret <  0 ) {
		return -2;
	}

	li_ret = lo_ac->initVM();
	if( li_ret < 0 ) {
		return -3;
	}

	lo_ac->setTextureMgr(tex_mgr);

	lmp_channels.insert( make_pair(name,(void*)lo_ac) );

	return 1;
}

int Alan :: bindObject( const string& name, AlanControlable *obj ) {
	AlanChannel *lo_ac = (AlanChannel*)_findChannel(name);
	if( 0 == lo_ac ) {
		return -1;			//nie ma takiego kanalu
	}

	lo_ac->bindObject(obj);

	return 1;
}

int Alan :: closeChannel( const string& name ) {

	tit_channels lit;
	lit = lmp_channels.find(name);
	if( lit == lmp_channels.end() ) {
		return -1;		//nie ma takiego kanalu
	}

	AlanChannel *lo_ac = (AlanChannel*)lit->second;
	if( 0 != lo_ac ) {
		delete lo_ac;
	}

	lmp_channels.erase(lit);

	return 1;
}

int Alan :: stopChannel(const string& name) {
	AlanChannel *lo_ac = (AlanChannel*)_findChannel(name);
	if( 0 == lo_ac ) {
		return -1;
	}

	lo_ac->onoff(false);

	return 1;
}
int Alan :: startChannel(const string& name) {
	AlanChannel *lo_ac = (AlanChannel*)_findChannel(name);
	if( 0 == lo_ac ) {
		return -1;
	}

	lo_ac->onoff(true);

	return 1;
}


int Alan :: setTextureMgr(TextureManager* p_tex_mgr) {
	tex_mgr = p_tex_mgr;
	return 1;
}

int Alan :: setTextureMgr(const string& name, TextureManager* p_tex_mgr) {
	AlanChannel *lo_ac = (AlanChannel*)_findChannel(name);
	if( 0 == lo_ac ) {
		return -1;			//nie ma takiego kanalu
	}

	lo_ac->setTextureMgr(p_tex_mgr);

	return 1;
}

void Alan :: _precalc_buildins(void) {
	int x,y;
	unsigned int k;
	k = SDL_GetMouseState(&x,&y);
	AlanState :: mouse_x = (float)x;
	AlanState :: mouse_y = (float)y;
	AlanState :: mouse_key = k;
}


int Alan :: process( const string& name, float dt ) {
	//if( debug ) return debug_process(name,dt);

	AlanChannel *lo_ac = (AlanChannel*)_findChannel(name);
	if( 0 == lo_ac ) {
		return -1;			//nie ma takiego kanalu
	}
	_precalc_buildins();
	lo_ac->run(dt);
	return 1;
}
int Alan :: debug_process( const string& name, float dt ) {
	AlanChannel *lo_ac = (AlanChannel*)_findChannel(name);
	if( 0 == lo_ac ) {
		return -1;			//nie ma takiego kanalu
	}
	_precalc_buildins();
	lo_ac->debug_run(dt);
	return 1;
}
int Alan :: process(float dt) {
	//if( debug ) return debug_process(dt);

	_precalc_buildins();
	AlanChannel *lo_ac;
	tit_channels lit;
	for( lit = lmp_channels.begin(); lit != lmp_channels.end(); ++lit ) {
		lo_ac = (AlanChannel*)(lit->second);
		lo_ac->run(dt);
	}
	return 1;
}
int Alan :: debug_process(float dt) {
	_precalc_buildins();
	AlanChannel *lo_ac;
	tit_channels lit;
	for( lit = lmp_channels.begin(); lit != lmp_channels.end(); ++lit ) {
		lo_ac = (AlanChannel*)(lit->second);
		lo_ac->debug_run(dt);
	}
	return 1;
}

}		//namespace Gfx
