#ifndef D_ALAN_INTERIALS_H_D
#define D_ALAN_INTERIALS_H_D

#include <string>
#include <vector>
#include <map>
#include <stack>
#include <cmath>

#include "Textures.h"
#include "Utils.h"
#include "Rand.h"

namespace Alan {


class AlanCode;

class AlanState {
public:
	int pc;
	std::stack<int>	call_stack;
	std::vector<float>	move_dx, move_dy, move_dr, move_dt, anim_dt, scale_sx, scale_sy, scale_dt;
	std::vector<std::string> anim_img;
	float move_time, anim_time, scale_time, scale_prev_sx, scale_prev_sy;
	int move_cnt, move_step, anim_cnt, anim_step, scale_cnt, scale_step;
	static float mouse_x, mouse_y;
	static unsigned int mouse_key;
	Gfx::TextureManager *tex_mgr;
	AlanState(void)	{}
	~AlanState() {}
	void Reset(void)	{
		pc = 0;
		while( call_stack.size() > 0 ) call_stack.pop();
		move_cnt = 0;
		move_time = 0;
		move_step = 0;
		move_dx.clear();
		move_dy.clear();
		move_dr.clear();
		move_dt.clear();
		anim_cnt = 0;
		anim_time = 0;
		anim_step = 0;
		anim_img.clear();
		anim_dt.clear();
		scale_cnt = 0;
		scale_time = 0;
		scale_step = 0;
		scale_sx.clear();
		scale_sy.clear();
		scale_dt.clear();
		scale_prev_sx = 1.0;
		scale_prev_sy = 1.0;
		tex_mgr = 0;
	}
};


class AlanException {
protected:
	int line, col;
	std::string msg;
public:
	AlanException(int line, int col,const std::string& msg) {
		this->line = line;
		this->col = col;
		this->msg = msg;
	}
	~AlanException() {
	}
	std::string Msg(void) {
		return "(" + toString(line) + ":" + toString(col) + ") " + msg;
	}
};

enum AlanTypes {
	TP_BOOL   = 0
, TP_INT	  = 1
, TP_FLOAT  = 2
, TP_STRING = 3
, TP_BAD		= 255
};

class AlanValue {
public:
	char	type;
	union Value {
		bool		v_bool;
		int			v_int;
		float		v_float;
	} val;
	std::string v_str;

	AlanValue(void)							{ type = TP_BAD; }
	AlanValue(bool v)  					{ type = TP_BAD; Set(v); }
	AlanValue(int v)   					{ type = TP_BAD; Set(v); }
	AlanValue(float v) 					{ type = TP_BAD; Set(v); }
	AlanValue(const std::string& v)	{ type = TP_BAD; Set(v); }

	~AlanValue() {}

	void Set(bool v)  					{ type = TP_BOOL;  val.v_bool = v; }
	void Set(int v)   					{ type = TP_INT;   val.v_int = v; }
	void Set(float v) 					{ type = TP_FLOAT; val.v_float = v; }
	void Set(const std::string& v) 	{ type = TP_STRING; v_str = v; }

	bool GetBool(void)	{
		ASSERT( type == TP_BOOL, "ALAN: Próba pobrania wartoœci typu BOOL, a wartoœæ jest innego typu" );
		return val.v_bool;
	}
	int GetInt(void)	{
		ASSERT( type == TP_INT, "ALAN: Próba pobrania wartoœci typu INT, a wartoœæ jest innego typu" );
		return val.v_int;
	}
	float GetFloat(void)	{
		ASSERT( type == TP_FLOAT, "ALAN: Próba pobrania wartoœci typu FLOAT, a wartoœæ jest innego typu" );
		return val.v_float;
	}
	const std::string& GetString(void)	{
		ASSERT( type == TP_STRING, "ALAN: Próba pobrania wartoœci typu STRING, a wartoœæ jest innego typu" );
		return v_str;
	}

	bool Cast2Bool(void)	{
		switch( type ) {
			case TP_BOOL:		return val.v_bool;
			case TP_INT:		if( val.v_int == 0 ) return false; return true;
			case TP_FLOAT:	if( val.v_float == 0 ) return false; return true;
			case TP_STRING:	if( v_str == "TRUE" ) return true; return false;
		}
		return false;
	}
	int Cast2Int(void)	{
		switch( type ) {
			case TP_INT:		return val.v_int;
			case TP_FLOAT:	return (int)(val.v_float);
			case TP_STRING:	return atol(v_str.c_str());
			case TP_BOOL:		if( val.v_bool ) return 1; return 0;
		}
		return 0;
	}
	float Cast2Float(void)	{
		switch( type ) {
			case TP_FLOAT:	return val.v_float;
			case TP_INT:		return (float)(val.v_int);
			case TP_STRING:	return atof(v_str.c_str());
			case TP_BOOL:		if( val.v_bool ) return 1.0; return 0.0;
		}
		return 0.0;
	}

	std::string Cast2String(void)	{
		switch( type ) {
			case TP_INT:		return toString(val.v_int);
			case TP_FLOAT:	return toString(val.v_float);
			case TP_STRING:	return v_str;
			case TP_BOOL:		if( val.v_bool ) return "true"; return "false";
		}
		return std::string("");
	}

	AlanValue& operator=( const AlanValue& v ) {
		type = v.type;
		switch( type ) {
			case TP_BOOL:		val.v_bool = v.val.v_bool; break;
			case TP_INT:		val.v_int = v.val.v_int; break;
			case TP_FLOAT:	val.v_float = v.val.v_float; break;
			case TP_STRING:	v_str = v.v_str; break;
		}
		return *this;
	}
};

class AlanExpr {
public:
	char type;
	AlanExpr(void) { type = TP_BAD; }
	virtual ~AlanExpr() {}
	virtual AlanValue Eval(AlanState *state) = 0;
	virtual std::string Dump(void) = 0;
};

class AlanFunc : public AlanExpr {
public:
	AlanFunc(void)	{}
	~AlanFunc()	{}
};

class AlanFuncIsMoving : public AlanFunc {
public:
	AlanFuncIsMoving(void)	{ type = TP_BOOL; }
	~AlanFuncIsMoving()	{}
	AlanValue Eval(AlanState *state) {
		if( 0 != state )
			return AlanValue((bool)(state->move_cnt != 0));
		return false;
	}
	std::string Dump(void) {
		return "IsMoving";
	}
};

class AlanFuncIsAnimating : public AlanFunc {
public:
	AlanFuncIsAnimating(void)	{ type = TP_BOOL; }
	~AlanFuncIsAnimating()	{}
	AlanValue Eval(AlanState *state) {
		if( 0 != state )
			return AlanValue((bool)(state->anim_cnt != 0));
		return false;
	}
	std::string Dump(void) {
		return "IsAnimating";
	}
};

class AlanFuncIsScaling : public AlanFunc {
public:
	AlanFuncIsScaling(void)	{ type = TP_BOOL; }
	~AlanFuncIsScaling()	{}
	AlanValue Eval(AlanState *state) {
		if( 0 != state )
			return AlanValue((bool)(state->scale_cnt != 0));
		return AlanValue(false);
	}
	std::string Dump(void) {
		return "IsSizing";
	}
};

class AlanFuncMouseX : public AlanFunc {
public:
	AlanFuncMouseX(void)	{ type = TP_FLOAT; }
	~AlanFuncMouseX()	{}
	AlanValue Eval(AlanState *state) {
		if( 0 != state )
			return AlanValue(state->mouse_x);
		return AlanValue((float)0);
	}
	std::string Dump(void) {
		return "MouseX";
	}
};

class AlanFuncMouseY : public AlanFunc {
public:
	AlanFuncMouseY(void)	{ type = TP_FLOAT; }
	~AlanFuncMouseY()	{}
	AlanValue Eval(AlanState *state) {
		if( 0 != state )
			return AlanValue(state->mouse_y);
		return AlanValue((float)0);
	}
	std::string Dump(void) {
		return "MouseY";
	}
};

class AlanFuncMouseKey : public AlanFunc {
public:
	AlanExpr *key;
	AlanFuncMouseKey(AlanExpr *p_key) : key(p_key) {
		type = TP_BOOL;
	}
	~AlanFuncMouseKey()	{}
	AlanValue Eval(AlanState *state) {
		int k;
		k = key->Eval(state).GetInt();
		if( k <= 0 || k > 32 )
			return AlanValue(false);
		if( 0 != state )
			return AlanValue( (bool)(0 != (state->mouse_key & 1<<(k-1))) );
		return AlanValue(false);
	}
	std::string Dump(void) {
		return "MouseKey" + key->Dump();
	}
};

class AlanFuncStrLen : public AlanFunc {
public:
	AlanExpr *str;
	AlanFuncStrLen(AlanExpr *p_str)	: str(p_str) {
		type = TP_INT;
	}
	~AlanFuncStrLen()	{}
	AlanValue Eval(AlanState *state) {
		ASSERT( str->type == TP_STRING, "ALAN: Parametr 'str' funkcji STRLEN jest innego typu ni¿ STRING" );
		return AlanValue( (int)str->Eval(state).GetString().size() );
	}
	std::string Dump(void) {
		return "StrLen(" + str->Dump() + ")";
	}
};

class AlanFuncSubStr : public AlanFunc {
public:
	AlanExpr *str, *beg, *cnt;
	AlanFuncSubStr(AlanExpr *p_str, AlanExpr *p_beg, AlanExpr *p_cnt) : str(p_str), beg(p_beg), cnt(p_cnt) {
		type = TP_STRING;
	}
	~AlanFuncSubStr()	{}
	AlanValue Eval(AlanState *state) {
		ASSERT( str->type == TP_STRING, "ALAN: Parametr 'str' funkcji SUBSTR jest innego typu ni¿ STRING" );
		ASSERT( beg->type == TP_INT, "ALAN: Parametr 'beg' funkcji SUBSTR jest innego typu ni¿ INT" );
		ASSERT( cnt->type == TP_INT, "ALAN: Parametr 'cnt' funkcji SUBSTR jest innego typu ni¿ INT" );
		int b,c;
		std::string s;
		b = beg->Eval(state).GetInt();
		c = cnt->Eval(state).GetInt();
		s = str->Eval(state).GetString();
		if( b < 0 ) {
			c += b;
			b = 0;
		}
		if( b >= (int)(s.size()) || c <= 0 )
			return AlanValue(std::string(""));
		return AlanValue( s.substr(b,c) );
	}
	std::string Dump(void) {
		return "SubStr(" + str->Dump() + ", " + beg->Dump() + "," + cnt->Dump() + ")";
	}
};

class AlanFuncInStr : public AlanFunc {
public:
	AlanExpr *str, *pat, *beg;
	AlanFuncInStr(AlanExpr *p_str, AlanExpr *p_pat, AlanExpr *p_beg) : str(p_str), pat(p_pat), beg(p_beg) {
		type = TP_INT;
	}
	~AlanFuncInStr()	{}
	AlanValue Eval(AlanState *state) {
		ASSERT( str->type == TP_STRING, "ALAN: Parametr 'str' funkcji INSTR jest innego typu ni¿ STRING" );
		ASSERT( pat->type == TP_STRING, "ALAN: Parametr 'pat' funkcji INSTR jest innego typu ni¿ STRING" );
		ASSERT( beg->type == TP_INT, "ALAN: Parametr 'beg' funkcji SUBSTR jest innego typu ni¿ INT" );
		int b,i;
		std::string s,p;
		s = str->Eval(state).GetString();
		p = pat->Eval(state).GetString();
		b = beg->Eval(state).GetInt();
		if( b < 0 || b >= (int)(s.size()) )
			return AlanValue( int(-1) );
		i = s.find(p,b);
		if( (int)(std::string::npos) == i ) i = -1;
		return AlanValue( i );
	}
	std::string Dump(void) {
		return "InStr(" + str->Dump() + ", " + pat->Dump() + "," + beg->Dump() + ")";
	}
};

class AlanFuncRandI : public AlanFunc {
public:
	AlanExpr *p1, *p2;
	AlanFuncRandI(AlanExpr *p_p1, AlanExpr *p_p2) : p1(p_p1), p2(p_p2)	{ type = TP_INT; }
	~AlanFuncRandI()	{}
	AlanValue Eval(AlanState *state) {
		ASSERT( p1->type == TP_INT, "ALAN: Parametr nr 1 funkcji RAND jest innego typu ni¿ INT" );
		ASSERT( p2->type == TP_INT, "ALAN: Parametr nr 2 funkcji RAND jest innego typu ni¿ INT" );
		int low,hi;
		low = p1->Eval(state).GetInt();
		hi  = p2->Eval(state).GetInt();
		return AlanValue((int)(Core::Randi(low,hi)));
	}
	std::string Dump(void) {
		return "Rand(" + p1->Dump() + ", " + p2->Dump() + ")";
	}
};

class AlanFuncRandF : public AlanFunc {
public:
	AlanExpr *p1, *p2;
	AlanFuncRandF(AlanExpr *p_p1, AlanExpr *p_p2) : p1(p_p1), p2(p_p2)	{ type = TP_FLOAT; }
	~AlanFuncRandF()	{}
	AlanValue Eval(AlanState *state) {
		ASSERT( p1->type == TP_FLOAT, "ALAN: Parametr nr 1 funkcji RANDF jest innego typu ni¿ FLOAT" );
		ASSERT( p2->type == TP_FLOAT, "ALAN: Parametr nr 2 funkcji RANDF jest innego typu ni¿ FLOAT" );
		float low,hi;
		low = p1->Eval(state).GetFloat();
		hi  = p2->Eval(state).GetFloat();
		return AlanValue(Core::Randf(low,hi));
	}
	std::string Dump(void) {
		return "RandF(" + p1->Dump() + ", " + p2->Dump() + ")";
	}
};

class AlanFuncSin : public AlanFunc {
public:
	AlanExpr *par;
	AlanFuncSin(AlanExpr *p_par) : par(p_par)	{ type = TP_FLOAT; }
	~AlanFuncSin()	{}
	AlanValue Eval(AlanState *state) {
		ASSERT( par->type == TP_FLOAT, "ALAN: Parametr funkcji SIN jest innego typu ni¿ FLOAT" );
		float p;
		p = par->Eval(state).GetFloat();
		return AlanValue((float)sin(p));
	}
	std::string Dump(void) {
		return "Sin(" + par->Dump() + ")";
	}
};

class AlanFuncCos : public AlanFunc {
public:
	AlanExpr *par;
	AlanFuncCos(AlanExpr *p_par) : par(p_par)	{ type = TP_FLOAT; }
	~AlanFuncCos()	{}
	AlanValue Eval(AlanState *state) {
		ASSERT( par->type == TP_FLOAT, "ALAN: Parametr funkcji COS jest innego typu ni¿ FLOAT" );
		float p;
		p = par->Eval(state).GetFloat();
		return AlanValue((float)cos(p));
	}
	std::string Dump(void) {
		return "Cos(" + par->Dump() + ")";
	}
};

class AlanFuncTan : public AlanFunc {
public:
	AlanExpr *par;
	AlanFuncTan(AlanExpr *p_par) : par(p_par)	{ type = TP_FLOAT; }
	~AlanFuncTan()	{}
	AlanValue Eval(AlanState *state) {
		ASSERT( par->type == TP_FLOAT, "ALAN: Parametr funkcji TAN jest innego typu ni¿ FLOAT" );
		float p;
		p = par->Eval(state).GetFloat();
		return AlanValue((float)tan(p));
	}
	std::string Dump(void) {
		return "Tan(" + par->Dump() + ")";
	}
};

class AlanFuncExp : public AlanFunc {
public:
	AlanExpr *par;
	AlanFuncExp(AlanExpr *p_par) : par(p_par)	{ type = TP_FLOAT; }
	~AlanFuncExp()	{}
	AlanValue Eval(AlanState *state) {
		ASSERT( par->type == TP_FLOAT, "ALAN: Parametr funkcji EXP jest innego typu ni¿ FLOAT" );
		float p;
		p = par->Eval(state).GetFloat();
		return AlanValue((float)exp(p));
	}
	std::string Dump(void) {
		return "Exp(" + par->Dump() + ")";
	}
};

class AlanFuncLog : public AlanFunc {
public:
	AlanExpr *par;
	AlanFuncLog(AlanExpr *p_par) : par(p_par)	{ type = TP_FLOAT; }
	~AlanFuncLog()	{}
	AlanValue Eval(AlanState *state) {
		ASSERT( par->type == TP_FLOAT, "ALAN: Parametr funkcji LOG jest innego typu ni¿ FLOAT" );
		float p;
		p = par->Eval(state).GetFloat();
		return AlanValue((float)log(p));
	}
	std::string Dump(void) {
		return "Log(" + par->Dump() + ")";
	}
};

class AlanFuncPow : public AlanFunc {
public:
	AlanExpr *p1, *p2;
	AlanFuncPow(AlanExpr *p_p1, AlanExpr *p_p2) : p1(p_p1), p2(p_p2)	{ type = TP_FLOAT; }
	~AlanFuncPow()	{}
	AlanValue Eval(AlanState *state) {
		ASSERT( p1->type == TP_FLOAT, "ALAN: Parametr nr 1 funkcji POW jest innego typu ni¿ FLOAT" );
		ASSERT( p2->type == TP_FLOAT, "ALAN: Parametr nr 2 funkcji POW jest innego typu ni¿ FLOAT" );
		float v1,v2;
		v1 = p1->Eval(state).GetFloat();
		v2 = p2->Eval(state).GetFloat();
		return AlanValue((float)pow(v1,v2));
	}
	std::string Dump(void) {
		return "Pow(" + p1->Dump() + ", " + p2->Dump() + ")";
	}
};

class AlanFuncSqrt : public AlanFunc {
public:
	AlanExpr *par;
	AlanFuncSqrt(AlanExpr *p_par) : par(p_par)	{ type = TP_FLOAT; }
	~AlanFuncSqrt()	{}
	AlanValue Eval(AlanState *state) {
		ASSERT( par->type == TP_FLOAT, "ALAN: Parametr funkcji SQRT jest innego typu ni¿ FLOAT" );
		float p;
		p = par->Eval(state).GetFloat();
		return AlanValue((float)sqrt(p));
	}
	std::string Dump(void) {
		return "Sqrt(" + par->Dump() + ")";
	}
};

class AlanFuncAbsI : public AlanFunc {
public:
	AlanExpr *par;
	AlanFuncAbsI(AlanExpr *p_par) : par(p_par)	{ type = TP_INT; }
	~AlanFuncAbsI()	{}
	AlanValue Eval(AlanState *state) {
		ASSERT( par->type == TP_INT, "ALAN: Parametr funkcji ABS_I jest innego typu ni¿ INT" );
		int p;
		p = par->Eval(state).GetInt();
		return AlanValue( (int)(p<0 ? -p : p) );
	}
	std::string Dump(void) {
		return "Abs_I(" + par->Dump() + ")";
	}
};

class AlanFuncAbsF : public AlanFunc {
public:
	AlanExpr *par;
	AlanFuncAbsF(AlanExpr *p_par) : par(p_par)	{ type = TP_FLOAT; }
	~AlanFuncAbsF()	{}
	AlanValue Eval(AlanState *state) {
		ASSERT( par->type == TP_INT, "ALAN: Parametr funkcji ABS_F jest innego typu ni¿ FLOAT" );
		float p;
		p = par->Eval(state).GetFloat();
		return AlanValue( (float)(p<0.0f ? -p : p) );
	}
	std::string Dump(void) {
		return "Abs_F(" + par->Dump() + ")";
	}
};

class AlanFuncSgnI : public AlanFunc {
public:
	AlanExpr *par;
	AlanFuncSgnI(AlanExpr *p_par) : par(p_par)	{ type = TP_INT; }
	~AlanFuncSgnI()	{}
	AlanValue Eval(AlanState *state) {
		ASSERT( par->type == TP_INT, "ALAN: Parametr funkcji SGN_I jest innego typu ni¿ INT" );
		int p;
		p = par->Eval(state).GetInt();
		return AlanValue( (int)(p==0 ? 0 : (p<0 ? -1 : 1)) );
	}
	std::string Dump(void) {
		return "Sgn_I(" + par->Dump() + ")";
	}
};

class AlanFuncSgnF : public AlanFunc {
public:
	AlanExpr *par;
	AlanFuncSgnF(AlanExpr *p_par) : par(p_par)	{ type = TP_FLOAT; }
	~AlanFuncSgnF()	{}
	AlanValue Eval(AlanState *state) {
		ASSERT( par->type == TP_INT, "ALAN: Parametr funkcji SGN_F jest innego typu ni¿ FLOAT" );
		float p;
		p = par->Eval(state).GetFloat();
		return AlanValue( (int)(p==0.0f ? 0.0f : (p<0.0f ? -1.0f : 1.0f)) );
	}
	std::string Dump(void) {
		return "Sgn_F(" + par->Dump() + ")";
	}
};

class AlanFuncFloor : public AlanFunc {
public:
	AlanExpr *par;
	AlanFuncFloor(AlanExpr *p_par) : par(p_par)	{ type = TP_INT; }
	~AlanFuncFloor()	{}
	AlanValue Eval(AlanState *state) {
		ASSERT( par->type == TP_FLOAT, "ALAN: Parametr funkcji FLOOR jest innego typu ni¿ FLOAT" );
		float p;
		p = par->Eval(state).GetFloat();
		return AlanValue( (int)floor(p) );
	}
	std::string Dump(void) {
		return "Floor(" + par->Dump() + ")";
	}
};

class AlanFuncCeil : public AlanFunc {
public:
	AlanExpr *par;
	AlanFuncCeil(AlanExpr *p_par) : par(p_par)	{ type = TP_INT; }
	~AlanFuncCeil()	{}
	AlanValue Eval(AlanState *state) {
		ASSERT( par->type == TP_FLOAT, "ALAN: Parametr funkcji CEIL jest innego typu ni¿ FLOAT" );
		float p;
		p = par->Eval(state).GetFloat();
		return AlanValue( (int)ceil(p) );
	}
	std::string Dump(void) {
		return "Ceil(" + par->Dump() + ")";
	}
};

class AlanFuncMinF : public AlanFunc {
public:
	AlanExpr *p1, *p2;
	AlanFuncMinF(AlanExpr *p_p1, AlanExpr *p_p2) : p1(p_p1), p2(p_p2)	{ type = TP_FLOAT; }
	~AlanFuncMinF()	{}
	AlanValue Eval(AlanState *state) {
		ASSERT( p1->type == TP_FLOAT, "ALAN: Parametr nr 1 funkcji MIN_F jest innego typu ni¿ FLOAT" );
		ASSERT( p2->type == TP_FLOAT, "ALAN: Parametr nr 2 funkcji MIN_F jest innego typu ni¿ FLOAT" );
		float v1,v2;
		v1 = p1->Eval(state).GetFloat();
		v2 = p2->Eval(state).GetFloat();
		return AlanValue( v1<v2 ? v1 : v2 );
	}
	std::string Dump(void) {
		return "Min_F(" + p1->Dump() + ", " + p2->Dump() + ")";
	}
};

class AlanFuncMinI : public AlanFunc {
public:
	AlanExpr *p1, *p2;
	AlanFuncMinI(AlanExpr *p_p1, AlanExpr *p_p2) : p1(p_p1), p2(p_p2)	{ type = TP_INT; }
	~AlanFuncMinI()	{}
	AlanValue Eval(AlanState *state) {
		ASSERT( p1->type == TP_INT, "ALAN: Parametr nr 1 funkcji MIN_I jest innego typu ni¿ INT" );
		ASSERT( p2->type == TP_INT, "ALAN: Parametr nr 2 funkcji MIN_I jest innego typu ni¿ INT" );
		int v1,v2;
		v1 = p1->Eval(state).GetInt();
		v2 = p2->Eval(state).GetInt();
		return AlanValue( v1<v2 ? v1 : v2 );
	}
	std::string Dump(void) {
		return "Min_I(" + p1->Dump() + ", " + p2->Dump() + ")";
	}
};

class AlanFuncMaxF : public AlanFunc {
public:
	AlanExpr *p1, *p2;
	AlanFuncMaxF(AlanExpr *p_p1, AlanExpr *p_p2) : p1(p_p1), p2(p_p2)	{ type = TP_FLOAT; }
	~AlanFuncMaxF()	{}
	AlanValue Eval(AlanState *state) {
		ASSERT( p1->type == TP_FLOAT, "ALAN: Parametr nr 1 funkcji MAX_F jest innego typu ni¿ FLOAT" );
		ASSERT( p2->type == TP_FLOAT, "ALAN: Parametr nr 2 funkcji MAX_F jest innego typu ni¿ FLOAT" );
		float v1,v2;
		v1 = p1->Eval(state).GetFloat();
		v2 = p2->Eval(state).GetFloat();
		return AlanValue( v1>v2 ? v1 : v2 );
	}
	std::string Dump(void) {
		return "Max_F(" + p1->Dump() + ", " + p2->Dump() + ")";
	}
};

class AlanFuncMaxI : public AlanFunc {
public:
	AlanExpr *p1, *p2;
	AlanFuncMaxI(AlanExpr *p_p1, AlanExpr *p_p2) : p1(p_p1), p2(p_p2)	{ type = TP_INT; }
	~AlanFuncMaxI()	{}
	AlanValue Eval(AlanState *state) {
		ASSERT( p1->type == TP_INT, "ALAN: Parametr nr 1 funkcji MAX_I jest innego typu ni¿ INT" );
		ASSERT( p2->type == TP_INT, "ALAN: Parametr nr 2 funkcji MAX_I jest innego typu ni¿ INT" );
		int v1,v2;
		v1 = p1->Eval(state).GetInt();
		v2 = p2->Eval(state).GetInt();
		return AlanValue( v1>v2 ? v1 : v2 );
	}
	std::string Dump(void) {
		return "Max_I(" + p1->Dump() + ", " + p2->Dump() + ")";
	}
};


class AlanVariable : public AlanExpr {
public:
	std::string id;
	AlanVariable(void) { id=""; }
	~AlanVariable() {}
	const std::string& GetID(void) { return id; }
	virtual std::string DumpV(void) = 0;
	virtual void Reset(void) = 0;
	virtual void SetValue( const AlanValue& val ) = 0;
	std::string Dump(void) {
		return id;
	}
};

class AlanBoolVar : public AlanVariable {
public:
	AlanValue val;
	AlanBoolVar(const std::string& id)	{ this->id=id; type = TP_BOOL; }
	~AlanBoolVar() {}
	std::string DumpV(void) {
		return "bool " + id + " = " + (val.GetBool() ? "true" : "false") ;
	}
	void Reset(void) {
		val.Set(false);
	}
	void SetValue( const AlanValue& v ) {
		ASSERT( type == v.type, "ALAN: Próba przypisania zmiennej wartoœci typu innego ni¿ BOOL" );
		val = v;
	}
	AlanValue Eval(AlanState *state) { return val; }
};

class AlanIntVar : public AlanVariable {
public:
	AlanValue val;
	AlanIntVar(const std::string& id)	{ this->id=id; type = TP_INT; }
	~AlanIntVar() {}
	std::string DumpV(void) {
		return "int " + id + " = " + toString(val.GetInt());
	}
	void Reset(void) {
		val.Set(0);
	}
	void SetValue( const AlanValue& v ) {
		ASSERT( type == v.type, "ALAN: Próba przypisania zmiennej wartoœci typu innego ni¿ INT " );
		val = v;
	}
	AlanValue Eval(AlanState *state) { return val; }
};

class AlanFloatVar : public AlanVariable {
public:
	AlanValue val;
	AlanFloatVar(const std::string& id)	{ this->id=id; type = TP_FLOAT; }
	~AlanFloatVar() {}
	std::string DumpV(void) {
		return "float " + id + " = " + toString(val.GetFloat());
	}
	void Reset(void) {
		val.Set(float(0));
	}
	void SetValue( const AlanValue& v ) {
		ASSERT( type == v.type, "ALAN: Próba przypisania zmiennej wartoœci typu innego ni¿ FLOAT" );
		val = v;
	}
	AlanValue Eval(AlanState *state) { return val; }
};

class AlanStringVar : public AlanVariable {
public:
	AlanValue val;
	AlanStringVar(const std::string& id)	{ this->id=id; type = TP_STRING; val.Set(std::string("")); }
	~AlanStringVar() {}
	std::string DumpV(void) {
		return "string " + id + " = '" + val.GetString() + "'";
	}
	void Reset(void) {
		val.Set(std::string(""));
	}
	void SetValue( const AlanValue& v ) {
		ASSERT( type == v.type, "ALAN: Próba przypisania zmiennej wartoœci typu innego ni¿ STRING" );
		val = v;
	}
	AlanValue Eval(AlanState *state) { return val; }
};

class AlanConstant : public AlanExpr {
public:
	AlanValue val;
	AlanConstant(bool v) { val.Set(v); type = TP_BOOL; }
	AlanConstant(int v) { val.Set(v); type = TP_INT; }
	AlanConstant(float v) { val.Set(v); type = TP_FLOAT; }
	AlanConstant(const std::string& v) { val.Set(v); type = TP_STRING; }
	~AlanConstant() {}
	AlanValue Eval(AlanState *state) { return val; }
	std::string Dump(void) {
		switch( val.type ) {
			case TP_BOOL:		return (val.GetBool() ? "true" : "false");
			case TP_INT:		return toString(val.GetInt());
			case TP_FLOAT:	return toString(val.GetFloat());
			case TP_STRING:	return "'" + val.GetString() + "'";
			default:				return "!TYPE!";
		}
	}
};

class AlanExpr2Arg : public AlanExpr {
public:
	AlanExpr *e1, *e2;
	AlanExpr2Arg( AlanExpr *p_e1, AlanExpr *p_e2 ) : e1(p_e1), e2(p_e2) {
		ASSERT( e1->type == e2->type, "ALAN: Typy parametrów operatora dwuargumentowego nie s¹ zgodne");
		type = e1->type;
	}
	~AlanExpr2Arg() { delete e1; delete e2; }
	virtual std::string Dump(void) {
		return "( " + (e1!=0 ? e1->Dump() : "!ADR!") + " , " + (e2!=0 ? e2->Dump() : "!ADR!") + " )";
	}
};

class AlanExprAdd : public AlanExpr2Arg {
public:
	AlanExprAdd( AlanExpr *p_e1, AlanExpr *p_e2 ) : AlanExpr2Arg(p_e1,p_e2) {}
	~AlanExprAdd() {}
	AlanValue Eval(AlanState *state) {
		AlanValue v1,v2;
		v1 = e1->Eval(state);
		v2 = e2->Eval(state);
		//typy powinny siê zgadzac
		ASSERT( v1.type == v2.type, "ALAN: Typy parametrów operatora + nie s¹ zgodne");
		switch( v1.type ) {
			case TP_INT:		return AlanValue( v1.GetInt() + v2.GetInt() );
			case TP_FLOAT:	return AlanValue( v1.GetFloat() + v2.GetFloat() );
			case TP_STRING:
				{
					AlanValue ret;
					std::string s1,s2,s3;
					s1 = v1.GetString();
					s2 = v2.GetString();
					s3 = s1 + s2;
					ret = AlanValue(s3);
					return ret;
					//return AlanValue( v1.GetString() + v2.GetString() );
				}
			case TP_BOOL:		ERROR("ALAN: Operator + jest niezdefiniowany dla typu boolean"); return AlanValue(false);
			default:				ERROR("ALAN: Nieznany typ parametrów operatora +"); return AlanValue();
		}
	}
	std::string Dump(void) {
		return "+" + AlanExpr2Arg::Dump();
	}
};

class AlanExprSub : public AlanExpr2Arg {
public:
	AlanExprSub( AlanExpr *e1, AlanExpr *e2 ) : AlanExpr2Arg(e1,e2) {}
	~AlanExprSub() {}
	AlanValue Eval(AlanState *state) {
		AlanValue v1,v2;
		v1 = e1->Eval(state);
		v2 = e2->Eval(state);
		//typy powinny siê zgadzac
		ASSERT( v1.type == v2.type, "ALAN: Typy parametrów operatora - nie s¹ zgodne");
		switch( v1.type ) {
			case TP_INT:		return AlanValue( v1.GetInt() - v2.GetInt() );
			case TP_FLOAT:	return AlanValue( v1.GetFloat() - v2.GetFloat() );
			case TP_STRING:	ERROR("ALAN: Operator - jest niezdefiniowany dla typu string"); return AlanValue(std::string(""));
			case TP_BOOL:		ERROR("ALAN: Operator - jest niezdefiniowany dla typu boolean"); return AlanValue(false);
			default:				ERROR("ALAN: Nieznany typ parametrów operatora -"); return AlanValue();
		}
	}
	std::string Dump(void) {
		return "-" + AlanExpr2Arg::Dump();
	}
};

class AlanExprMul : public AlanExpr2Arg {
public:
	AlanExprMul( AlanExpr *e1, AlanExpr *e2 ) : AlanExpr2Arg(e1,e2) {}
	~AlanExprMul() {}
	AlanValue Eval(AlanState *state) {
		AlanValue v1,v2;
		v1 = e1->Eval(state);
		v2 = e2->Eval(state);
		//typy powinny siê zgadzac
		ASSERT( v1.type == v2.type, "ALAN: Typy parametrów operatora * nie s¹ zgodne");
		switch( v1.type ) {
			case TP_INT:		return AlanValue( v1.GetInt() * v2.GetInt() );
			case TP_FLOAT:	return AlanValue( v1.GetFloat() * v2.GetFloat() );
			case TP_STRING:	ERROR("ALAN: Operator * jest niezdefiniowany dla typu string"); return AlanValue(std::string(""));
			case TP_BOOL:		ERROR("ALAN: Operator * jest niezdefiniowany dla typu boolean"); return AlanValue(false);
			default:				ERROR("ALAN: Nieznany typ parametrów operatora *"); return AlanValue();
		}
	}
	std::string Dump(void) {
		return "*" + AlanExpr2Arg::Dump();
	}
};

class AlanExprDiv : public AlanExpr2Arg {
public:
	AlanExprDiv( AlanExpr *e1, AlanExpr *e2 ) : AlanExpr2Arg(e1,e2) {}
	~AlanExprDiv() {}
	AlanValue Eval(AlanState *state) {
		AlanValue v1,v2;
		v1 = e1->Eval(state);
		v2 = e2->Eval(state);
		//typy powinny siê zgadzac
		ASSERT( v1.type == v2.type, "ALAN: Typy parametrów operatora / nie s¹ zgodne");
		switch( v1.type ) {
			case TP_INT:		return AlanValue( v1.GetInt() / v2.GetInt() );
			case TP_FLOAT:	return AlanValue( v1.GetFloat() / v2.GetFloat() );
			case TP_STRING:	ERROR("ALAN: Operator / jest niezdefiniowany dla typu string"); return AlanValue(std::string(""));
			case TP_BOOL:		ERROR("ALAN: Operator / jest niezdefiniowany dla typu boolean"); return AlanValue(false);
			default:				ERROR("ALAN: Nieznany typ parametrów operatora /"); return AlanValue();
		}
	}
	std::string Dump(void) {
		return "/" + AlanExpr2Arg::Dump();
	}
};

class AlanExprMod : public AlanExpr2Arg {
public:
	AlanExprMod( AlanExpr *e1, AlanExpr *e2 ) : AlanExpr2Arg(e1,e2) {}
	~AlanExprMod() {}
	AlanValue Eval(AlanState *state) {
		AlanValue v1,v2;
		v1 = e1->Eval(state);
		v2 = e2->Eval(state);
		//typy powinny siê zgadzac
		ASSERT( v1.type == v2.type, "ALAN: Typy parametrów operatora % nie s¹ zgodne");
		switch( v1.type ) {
			case TP_INT:		return AlanValue( v1.GetInt() % v2.GetInt() );
			case TP_FLOAT:	return AlanValue( (float)fmod(v1.GetFloat(),v2.GetFloat()) );
			case TP_STRING:	ERROR("ALAN: Operator % jest niezdefiniowany dla typu string"); return AlanValue(std::string(""));
			case TP_BOOL:		ERROR("ALAN: Operator % jest niezdefiniowany dla typu boolean"); return AlanValue(false);
			default:				ERROR("ALAN: Nieznany typ parametrów operatora %"); return AlanValue();
		}
	}
	std::string Dump(void) {
		return "%" + AlanExpr2Arg::Dump();
	}
};

class AlanExpr1Arg : public AlanExpr {
public:
	AlanExpr *e1;
	AlanExpr1Arg( AlanExpr *p_e1 ) : e1(p_e1) {
		type = e1->type;
	}
	~AlanExpr1Arg() { delete e1; }
	virtual std::string Dump(void) {
		return "( " + (e1!=0 ? e1->Dump() : "!ADR!") + " )";
	}
};

class AlanExprNeg : public AlanExpr1Arg {
public:
	AlanExprNeg( AlanExpr *e1 ) : AlanExpr1Arg(e1) {}
	~AlanExprNeg() {}
	AlanValue Eval(AlanState *state) {
		AlanValue v1;
		v1 = e1->Eval(state);
		switch( v1.type ) {
			case TP_INT:		return AlanValue( - v1.GetInt() );
			case TP_FLOAT:	return AlanValue( - v1.GetFloat() );
			case TP_STRING:	ERROR("ALAN: Operator jednoargumentowy - jest niezdefiniowany dla typu string"); return AlanValue("");
			case TP_BOOL:		ERROR("ALAN: Operator jednoargumentowy - jest niezdefiniowany dla typu boolean"); return AlanValue(false);
			default:				ERROR("ALAN: Nieznany typ parametru operatora jednoargumentowego -"); return AlanValue();
		}
	}
	std::string Dump(void) {
		return "-" + AlanExpr1Arg::Dump();
	}
};

class AlanExprCastBool : public AlanExpr1Arg {
public:
	AlanExprCastBool( AlanExpr *e1 ) : AlanExpr1Arg(e1) {
		type = TP_BOOL;
	}
	~AlanExprCastBool() {}
	AlanValue Eval(AlanState *state) {
		AlanValue v1;
		v1 = e1->Eval(state);
		return AlanValue( v1.Cast2Bool() );
	}
	std::string Dump(void) {
		return "BOOL" + AlanExpr1Arg::Dump();
	}
};

class AlanExprCastInt : public AlanExpr1Arg {
public:
	AlanExprCastInt( AlanExpr *e1 ) : AlanExpr1Arg(e1) {
		type = TP_INT;
	}
	~AlanExprCastInt() {}
	AlanValue Eval(AlanState *state) {
		AlanValue v1;
		v1 = e1->Eval(state);
		return AlanValue( v1.Cast2Int() );
	}
	std::string Dump(void) {
		return "INT" + AlanExpr1Arg::Dump();
	}
};

class AlanExprCastFloat : public AlanExpr1Arg {
public:
	AlanExprCastFloat( AlanExpr *e1 ) : AlanExpr1Arg(e1) {
		type = TP_FLOAT;
	}
	~AlanExprCastFloat() {}
	AlanValue Eval(AlanState *state) {
		AlanValue v1;
		v1 = e1->Eval(state);
		return AlanValue( v1.Cast2Float() );
	}
	std::string Dump(void) {
		return "FLOAT" + AlanExpr1Arg::Dump();
	}
};

class AlanExprCastString : public AlanExpr1Arg {
public:
	AlanExprCastString( AlanExpr *e1 ) : AlanExpr1Arg(e1) {
		type = TP_STRING;
	}
	~AlanExprCastString() {}
	AlanValue Eval(AlanState *state) {
		AlanValue v1;
		v1 = e1->Eval(state);
		return AlanValue( v1.Cast2String() );
	}
	std::string Dump(void) {
		return "STRING" + AlanExpr1Arg::Dump();
	}
};

class AlanExprEq : public AlanExpr2Arg {
public:
	AlanExprEq( AlanExpr *e1, AlanExpr *e2 ) : AlanExpr2Arg(e1,e2) {
		type = TP_BOOL;
	}
	~AlanExprEq() {}
	AlanValue Eval(AlanState *state) {
		AlanValue v1,v2;
		v1 = e1->Eval(state);
		v2 = e2->Eval(state);
		//typy powinny siê zgadzac
		ASSERT( v1.type == v2.type, "ALAN: Typy parametrów operatora = (==) nie s¹ zgodne");
		switch( v1.type ) {
			case TP_INT:		if( v1.GetInt() == v2.GetInt() ) return AlanValue(true); return AlanValue(false);
			case TP_FLOAT:	if( v1.GetFloat() == v2.GetFloat() ) return AlanValue(true); return AlanValue(false);
			case TP_STRING:	if( v1.GetString() == v1.GetString() )return AlanValue(true); return AlanValue(false);
			case TP_BOOL:		if( v1.GetBool() == v1.GetBool() )return AlanValue(true); return AlanValue(false);
			default:				ERROR("ALAN: Nieznany typ parametrów operatora = (==)"); return AlanValue();
		}
	}
	std::string Dump(void) {
		return "=" + AlanExpr2Arg::Dump();
	}
};

class AlanExprNe : public AlanExpr2Arg {
public:
	AlanExprNe( AlanExpr *e1, AlanExpr *e2 ) : AlanExpr2Arg(e1,e2) {
		type = TP_BOOL;
	}
	~AlanExprNe() {}
	AlanValue Eval(AlanState *state) {
		AlanValue v1,v2;
		v1 = e1->Eval(state);
		v2 = e2->Eval(state);
		//typy powinny siê zgadzac
		ASSERT( v1.type == v2.type, "ALAN: Typy parametrów operatora <> nie s¹ zgodne");
		switch( v1.type ) {
			case TP_INT:		if( v1.GetInt() != v2.GetInt() ) return AlanValue(true); return AlanValue(false);
			case TP_FLOAT:	if( v1.GetFloat() != v2.GetFloat() ) return AlanValue(true); return AlanValue(false);
			case TP_STRING:	if( v1.GetString() != v1.GetString() )return AlanValue(true); return AlanValue(false);
			case TP_BOOL:		if( v1.GetBool() != v1.GetBool() )return AlanValue(true); return AlanValue(false);
			default:				ERROR("ALAN: Nieznany typ parametrów operatora <>"); return AlanValue();
		}
	}
	std::string Dump(void) {
		return "<>" + AlanExpr2Arg::Dump();
	}
};

class AlanExprLt : public AlanExpr2Arg {
public:
	AlanExprLt( AlanExpr *e1, AlanExpr *e2 ) : AlanExpr2Arg(e1,e2) {
		type = TP_BOOL;
	}
	~AlanExprLt() {}
	AlanValue Eval(AlanState *state) {
		AlanValue v1,v2;
		v1 = e1->Eval(state);
		v2 = e2->Eval(state);
		//typy powinny siê zgadzac
		ASSERT( v1.type == v2.type, "ALAN: Typy parametrów operatora < nie s¹ zgodne");
		switch( v1.type ) {
			case TP_INT:		if( v1.GetInt() < v2.GetInt() ) return AlanValue(true); return AlanValue(false);
			case TP_FLOAT:	if( v1.GetFloat() < v2.GetFloat() ) return AlanValue(true); return AlanValue(false);
			case TP_STRING:	if( v1.GetString() < v1.GetString() )return AlanValue(true); return AlanValue(false);
			case TP_BOOL:		ERROR("ALAN: Operator < jest niezdefiniowany dla typu boolean"); return AlanValue(false);
			default:				ERROR("ALAN: Nieznany typ parametrów operatora <"); return AlanValue();
		}
	}
	std::string Dump(void) {
		return "<" + AlanExpr2Arg::Dump();
	}
};

class AlanExprGt : public AlanExpr2Arg {
public:
	AlanExprGt( AlanExpr *e1, AlanExpr *e2 ) : AlanExpr2Arg(e1,e2) {
		type = TP_BOOL;
	}
	~AlanExprGt() {}
	AlanValue Eval(AlanState *state) {
		AlanValue v1,v2;
		v1 = e1->Eval(state);
		v2 = e2->Eval(state);
		//typy powinny siê zgadzac
		ASSERT( v1.type == v2.type, "ALAN: Typy parametrów operatora > nie s¹ zgodne");
		switch( v1.type ) {
			case TP_INT:		if( v1.GetInt() > v2.GetInt() ) return AlanValue(true); return AlanValue(false);
			case TP_FLOAT:	if( v1.GetFloat() > v2.GetFloat() ) return AlanValue(true); return AlanValue(false);
			case TP_STRING:	if( v1.GetString() > v1.GetString() )return AlanValue(true); return AlanValue(false);
			case TP_BOOL:		ERROR("ALAN: Operator > jest niezdefiniowany dla typu boolean"); return AlanValue(false);
			default:				ERROR("ALAN: Nieznany typ parametrów operatora >"); return AlanValue();
		}
	}
	std::string Dump(void) {
		return ">" + AlanExpr2Arg::Dump();
	}
};

class AlanExprLe : public AlanExpr2Arg {
public:
	AlanExprLe( AlanExpr *e1, AlanExpr *e2 ) : AlanExpr2Arg(e1,e2) {
		type = TP_BOOL;
	}
	~AlanExprLe() {}
	AlanValue Eval(AlanState *state) {
		AlanValue v1,v2;
		v1 = e1->Eval(state);
		v2 = e2->Eval(state);
		//typy powinny siê zgadzac
		ASSERT( v1.type == v2.type, "ALAN: Typy parametrów operatora <= nie s¹ zgodne");
		switch( v1.type ) {
			case TP_INT:		if( v1.GetInt() <= v2.GetInt() ) return AlanValue(true); return AlanValue(false);
			case TP_FLOAT:	if( v1.GetFloat() <= v2.GetFloat() ) return AlanValue(true); return AlanValue(false);
			case TP_STRING:	if( v1.GetString() <= v1.GetString() )return AlanValue(true); return AlanValue(false);
			case TP_BOOL:		ERROR("ALAN: Operator <= jest niezdefiniowany dla typu boolean"); return AlanValue(false);
			default:				ERROR("ALAN: Nieznany typ parametrów operatora <="); return AlanValue();
		}
	}
	std::string Dump(void) {
		return "<=" + AlanExpr2Arg::Dump();
	}
};

class AlanExprGe : public AlanExpr2Arg {
public:
	AlanExprGe( AlanExpr *e1, AlanExpr *e2 ) : AlanExpr2Arg(e1,e2) {
		type = TP_BOOL;
	}
	~AlanExprGe() {}
	AlanValue Eval(AlanState *state) {
		AlanValue v1,v2;
		v1 = e1->Eval(state);
		v2 = e2->Eval(state);
		//typy powinny siê zgadzac
		ASSERT( v1.type == v2.type, "ALAN: Typy parametrów operatora >= nie s¹ zgodne");
		switch( v1.type ) {
			case TP_INT:		if( v1.GetInt() >= v2.GetInt() ) return AlanValue(true); return AlanValue(false);
			case TP_FLOAT:	if( v1.GetFloat() >= v2.GetFloat() ) return AlanValue(true); return AlanValue(false);
			case TP_STRING:	if( v1.GetString() >= v1.GetString() )return AlanValue(true); return AlanValue(false);
			case TP_BOOL:		ERROR("ALAN: Operator >= jest niezdefiniowany dla typu boolean"); return AlanValue(false);
			default:				ERROR("ALAN: Nieznany typ parametrów operatora >="); return AlanValue();
		}
	}
	std::string Dump(void) {
		return ">=" + AlanExpr2Arg::Dump();
	}
};

class AlanExprNot : public AlanExpr1Arg {
public:
	AlanExprNot( AlanExpr *e1 ) : AlanExpr1Arg(e1) {
		type = TP_BOOL;
	}
	~AlanExprNot() {}
	AlanValue Eval(AlanState *state) {
		AlanValue v1;
		v1 = e1->Eval(state);
		if( v1.type != TP_BOOL ) {
			ERROR("ALAN: Niepoprawnu typ parametru operatora jednoargumentowego NOT");
			return AlanValue(false);
		}
		return AlanValue( ! v1.GetBool() );
	}
	std::string Dump(void) {
		return "NOT" + AlanExpr1Arg::Dump();
	}
};

class AlanExprAnd : public AlanExpr2Arg {
public:
	AlanExprAnd( AlanExpr *e1, AlanExpr *e2 ) : AlanExpr2Arg(e1,e2) {
		type = TP_BOOL;
	}
	~AlanExprAnd() {}
	AlanValue Eval(AlanState *state) {
		AlanValue v1,v2;
		v1 = e1->Eval(state);
		v2 = e2->Eval(state);
		ASSERT( v1.type == TP_BOOL, "Lewy parametr operatora AND nie jest typu BOOL" );
		ASSERT( v1.type == TP_BOOL, "Prawy parametr operatora AND nie jest typu BOOL" );
		return AlanValue( v1.GetBool() && v2.GetBool() );
	}
	std::string Dump(void) {
		return "AND" + AlanExpr2Arg::Dump();
	}
};

class AlanExprOr : public AlanExpr2Arg {
public:
	AlanExprOr( AlanExpr *e1, AlanExpr *e2 ) : AlanExpr2Arg(e1,e2) {
		type = TP_BOOL;
	}
	~AlanExprOr() {}
	AlanValue Eval(AlanState *state) {
		AlanValue v1,v2;
		v1 = e1->Eval(state);
		v2 = e2->Eval(state);
		ASSERT( v1.type == TP_BOOL, "Lewy parametr operatora OR nie jest typu BOOL" );
		ASSERT( v1.type == TP_BOOL, "Prawy parametr operatora OR nie jest typu BOOL" );
		return AlanValue( v1.GetBool() || v2.GetBool() );
	}
	std::string Dump(void) {
		return "OR" + AlanExpr2Arg::Dump();
	}
};


class AlanInstr {
public:
	AlanInstr(void);
	virtual ~AlanInstr();
	virtual int Execute(AlanState *stat) = 0;
	virtual bool Relocate(int pc,AlanCode *code,std::string& error) = 0;
	virtual std::string Dump(int pc) = 0;
};

class AlanInstrMove : public AlanInstr {
public:
	std::vector<AlanExpr*> dx,dy,dr,dt;
	AlanExpr *cnt;
	AlanInstrMove( AlanExpr* cnt, std::vector<AlanExpr*> &dx, std::vector<AlanExpr*> &dy, std::vector<AlanExpr*> &dr, std::vector<AlanExpr*> &dt );
	~AlanInstrMove();
	int Execute(AlanState *stat);
	bool Relocate(int pc,AlanCode *code,std::string& error);
	std::string Dump(int pc);
};

class AlanInstrAnim : public AlanInstr {
public:
	std::vector<AlanExpr*> img, dt;
	AlanExpr *cnt;
	AlanInstrAnim( AlanExpr* cnt, std::vector<AlanExpr*> &img, std::vector<AlanExpr*> &dt );
	~AlanInstrAnim();
	int Execute(AlanState *stat);
	bool Relocate(int pc,AlanCode *code,std::string& error);
	std::string Dump(int pc);
};

class AlanInstrScale : public AlanInstr {
public:
	std::vector<AlanExpr*> sx,sy,dt;
	AlanExpr *cnt;
	AlanInstrScale( AlanExpr* cnt, std::vector<AlanExpr*> &sx, std::vector<AlanExpr*> &sy, std::vector<AlanExpr*> &dt );
	~AlanInstrScale();
	int Execute(AlanState *stat);
	bool Relocate(int pc,AlanCode *code,std::string& error);
	std::string Dump(int pc);
};

class AlanInstrGoto : public AlanInstr {
public:
	int dpc;
	std::string label;
	AlanInstrGoto( const std::string& lab );
	~AlanInstrGoto();
	void SetLabel(const std::string& lab);
	int Execute(AlanState *stat);
	bool Relocate(int pc,AlanCode *code,std::string& error);
	std::string Dump(int pc);
};

class AlanInstrGosub : public AlanInstr {
public:
	int dpc;
	std::string label;
	AlanInstrGosub( const std::string& lab );
	~AlanInstrGosub();
	void SetLabel(const std::string& lab);
	int Execute(AlanState *stat);
	bool Relocate(int pc,AlanCode *code,std::string& error);
	std::string Dump(int pc);
};

class AlanInstrReturn : public AlanInstr {
public:
	AlanInstrReturn(void);
	~AlanInstrReturn();
	int Execute(AlanState *stat);
	bool Relocate(int pc,AlanCode *code,std::string& error);
	std::string Dump(int pc);
};

class AlanInstrLet : public AlanInstr {
public:
	AlanVariable *var;
	AlanExpr *val;
	AlanInstrLet(AlanVariable* p_var,AlanExpr* p_value);
	~AlanInstrLet();
	int Execute(AlanState *stat);
	bool Relocate(int pc,AlanCode *code,std::string& error);
	std::string Dump(int pc);
};

class AlanInstrFor : public AlanInstr {
public:
	AlanVariable *var;
	AlanExpr *beg, *end, *step;
	std::string label;
	int dpc;
	AlanInstrFor(AlanVariable* p_var,AlanExpr* p_beg,AlanExpr* p_end,AlanExpr* p_step,const std::string& p_lab);
	~AlanInstrFor();
	int Execute(AlanState *stat);
	bool Relocate(int pc,AlanCode *code,std::string& error);
	std::string Dump(int pc);
};

class AlanInstrWhile : public AlanInstr {
public:
	AlanExpr *val;
	std::string label;
	int dpc;
	AlanInstrWhile(AlanExpr* p_value,const std::string& p_lab);
	~AlanInstrWhile();
	int Execute(AlanState *stat);
	bool Relocate(int pc,AlanCode *code,std::string& error);
	std::string Dump(int pc);
};

class AlanInstrIf : public AlanInstr {
public:
	AlanExpr *val;
	std::string label;
	int dpc;
	AlanInstrIf(AlanExpr* p_value,const std::string& p_lab);
	~AlanInstrIf();
	int Execute(AlanState *stat);
	bool Relocate(int pc,AlanCode *code,std::string& error);
	std::string Dump(int pc);
};

class AlanInstrPause : public AlanInstr {
public:
	AlanInstrPause(void);
	~AlanInstrPause();
	int Execute(AlanState *stat);
	bool Relocate(int pc,AlanCode *code,std::string& error);
	std::string Dump(int pc);
};

class AlanInstrPauseWhile : public AlanInstr {
public:
	AlanExpr *val;
	AlanInstrPauseWhile(AlanExpr* p_value);
	~AlanInstrPauseWhile();
	int Execute(AlanState *stat);
	bool Relocate(int pc,AlanCode *code,std::string& error);
	std::string Dump(int pc);
};


class AlanCode {
protected:
	typedef std::map<std::string,int> t_labels;
	typedef t_labels::iterator t_labels_iter;

	typedef std::map<std::string,AlanVariable*> t_variables;
	typedef t_variables::iterator t_variables_iter;

	typedef std::vector<AlanInstr*> t_instructions;

	t_labels				labs;
	t_variables			vars;
	t_instructions	code;

	class SpecialLabel {
	public:
		char type;
		int pc, refpc;
		enum Types {
			SLT_IF		= 0
		, SLT_ELSE	= 1
		, SLT_EIF		= 2
		, SLT_FOR		= 3
		, SLT_NEXT	= 4
		, SLT_WHILE	= 5
		, SLT_WEND	= 6
		, SLT_BAD		= 255
		};
		SpecialLabel(void) {
			type = SLT_BAD;
			pc = 0;
			refpc = 0;
		}
		~SpecialLabel() {
		}
	};
	typedef std::stack<SpecialLabel> t_speclab;
	t_speclab speclabs;

	//info o kodzie
	bool relocated;

public:
	AlanCode(void);
	~AlanCode();

	void AddBuildins(void);

	//inicjuje zmienne i relokuje kod jezeli trzeba
	void Reset(void);
	bool Relocate(std::string& error);

	int Len(void);
	int Execute(int pc,AlanState *state);

	std::string DumpVars(const std::string& varid);
	std::string DumpLabel(int pc);
	std::string DumpCode(void);
	std::string DumpCode(int pc);

	void AddLabel(const std::string& id);
	int AddSpecLabel(char type,std::string& error);
	int GetLabelPC(const std::string& id);

	AlanVariable* GetVar(const std::string& id );
	AlanVariable* AddVar(const std::string& id,char type);

	void AddInstrMove(AlanExpr *cnt, std::vector<AlanExpr*> &dx, std::vector<AlanExpr*> &dy, std::vector<AlanExpr*> &dr, std::vector<AlanExpr*> &dt);
	void AddInstrAnim(AlanExpr *cnt, std::vector<AlanExpr*> &img, std::vector<AlanExpr*> &dt);
	void AddInstrScale(AlanExpr *cnt, std::vector<AlanExpr*> &sx, std::vector<AlanExpr*> &sy, std::vector<AlanExpr*> &dt);
	void AddInstrGoto(const std::string& label);
	void AddInstrGosub(const std::string& label);
	void AddInstrReturn(void);
	void AddInstrLet(AlanVariable* var,AlanExpr* value);
	bool AddInstrFor(AlanVariable* var,AlanExpr* beg,AlanExpr* end,AlanExpr* step,std::string& error);
	bool AddInstrNext(std::string& error);
	bool AddInstrWhile(AlanExpr* value,std::string& error);
	bool AddInstrWend(std::string& error);
	bool AddInstrIf(AlanExpr* value,std::string& error);
	bool AddInstrElse(std::string& error);
	bool AddInstrEif(std::string& error);
	bool AddInstrPause(std::string& error);
	bool AddInstrPauseWhile(AlanExpr* value,std::string& error);

	void SetVarVal(const std::string& varname,bool v);
	void SetVarVal(const std::string& varname,int v);
	void SetVarVal(const std::string& varname,float v);
	void SetVarVal(const std::string& varname,const std::string& v);
	bool GetVarValB(const std::string& varname);
	int GetVarValI(const std::string& varname);
	float GetVarValF(const std::string& varname);
	std::string GetVarValS(const std::string& varname);
};

class AlanVM {
protected:
	AlanCode *code;
	AlanState *state;
	bool code_finished;
public:
	AlanVM(void);
	~AlanVM();
	void SetCode( AlanCode* c );
	AlanState* GetState(void);
	void Reset(void);
	void Continue(void);
	void DebugContinue(void);
	std::string DumpVars(void);
	void SetVarVal(const std::string& varname,float v);
	float GetVarValF(const std::string& varname);
};



inline std::string TypeName(char type) {
	switch( type ) {
		case TP_BOOL: return "BOOL";
		case TP_INT: return "INT";
		case TP_FLOAT: return "FLOAT";
		case TP_STRING: return "STRING";
		default:	return "BAD";
	}
}

inline bool IsNumType(char type) {
	switch( type ) {
		case TP_INT:
		case TP_FLOAT:	return true;
		default:				return false;
	}
}

inline bool IsRelType(char type) {
	switch( type ) {
		case TP_INT:
		case TP_FLOAT:
		case TP_STRING: return true;
		default:				return false;
	}
}

inline bool TypesMatch(char type1,char type2) {
	switch( type1 ) {
		case TP_BOOL:		if( type2 == TP_BOOL ) return true; else return false;
		case TP_INT:
		case TP_FLOAT:	if( type2 == TP_INT || type2 == TP_FLOAT ) return true; else return false;
		case TP_STRING:	if( type2 == TP_STRING ) return true; else return false;
		default:				return false;
	}
}

inline AlanExpr* Cast(char type,AlanExpr *e ) {
	if( e->type == type ) return e;
	switch( type ) {
		case TP_BOOL:		return new AlanExprCastBool(e);
		case TP_INT:		return new AlanExprCastInt(e);
		case TP_FLOAT:	return new AlanExprCastFloat(e);
		case TP_STRING:	return new AlanExprCastString(e);;
		default:				return 0;
	}
}

inline void Cast(AlanExpr* &e1,AlanExpr* &e2) {
	switch( e1->type ) {

		case TP_BOOL:		if( e2->type != TP_BOOL )
											e2 = new AlanExprCastBool(e2);
										return;

		case TP_INT:		if( e2->type == TP_FLOAT )
											e1 = new AlanExprCastFloat(e1);
										else if( e2->type == TP_INT )
											e2 = e2;	//nie trzeba rzutowac
										else
											e2 = new AlanExprCastInt(e2);
										return;

		case TP_FLOAT:	if( e2->type == TP_INT )
											e2 = new AlanExprCastFloat(e2);
										else if( e2->type == TP_FLOAT )
											e2 = e2;	//nie trzeba rzutowac
										else
											e2 = new AlanExprCastFloat(e2);
										return;

		case TP_STRING:	if( e2->type != TP_STRING )
											e2 = new AlanExprCastString(e2);
										return;

		default:				e1 = 0; e2 = 0;
										return;
	}
}


}

#endif
