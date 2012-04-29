
#include "_alan_interials.h"

using namespace std;

namespace Alan {

float AlanState :: mouse_x = 0.0;
float AlanState :: mouse_y = 0.0;
unsigned int AlanState :: mouse_key = 0;


enum SpecialPC {
  SPC_IS_SPECIAL				= 1000000000
, SPC_PAUSE_INSTR 			= 1000000000
, SPC_PAUSE_WHILE_INSTR = 1000000001
, SPC_EMPTY_CALL_STACK 	= 1000000002
};

AlanInstr :: AlanInstr(void) {}
AlanInstr :: ~AlanInstr() {}

AlanInstrMove :: AlanInstrMove( AlanExpr* p_cnt
															, vector<AlanExpr*> &p_dx
															, vector<AlanExpr*> &p_dy
															, vector<AlanExpr*> &p_dr
															, vector<AlanExpr*> &p_dt ) {
	cnt = p_cnt;
	dx = p_dx;
	dy = p_dy;
	dr = p_dr;
	dt = p_dt;
}
AlanInstrMove :: ~AlanInstrMove() {}
int AlanInstrMove :: Execute(AlanState* stat) {

	stat->move_cnt = cnt->Eval(0).Cast2Int();
	stat->move_step = 0;
	stat->move_time = 0;

	stat->move_dx.clear();
	stat->move_dy.clear();
	stat->move_dr.clear();
	stat->move_dt.clear();

	vector<AlanExpr*>::iterator itx, ity, itr, itt;
	float t;
	for( itx = dx.begin(), ity = dy.begin(), itr = dr.begin(), itt = dt.begin()
		 ; itx != dx.end() && ity != dy.end() && itr != dr.end() && itt != dt.end()
		 ; ++itx, ++ity, ++itr, ++itt ) {
		t = (*itt)->Eval(0).Cast2Float();
		if( t != 0 ) {
			stat->move_dx.push_back( ((*itx)->Eval(0).Cast2Float()) / t );
			stat->move_dy.push_back( ((*ity)->Eval(0).Cast2Float()) / t );
			stat->move_dr.push_back( ((*itr)->Eval(0).Cast2Float()) / t );
			stat->move_dt.push_back( Abs(t) );
		} else {
			stat->move_dx.push_back( (*itx)->Eval(0).Cast2Float() );
			stat->move_dy.push_back( (*ity)->Eval(0).Cast2Float() );
			stat->move_dr.push_back( (*itr)->Eval(0).Cast2Float() );
			stat->move_dt.push_back( 0.0 );
		}
	}

	return 1;
}
bool AlanInstrMove :: Relocate(int pc,AlanCode *code,string& error) {
	return true;
}
string AlanInstrMove :: Dump(int pc) {
	string ret = "MOVE ";
	ret += cnt->Dump() + ",";

	for( int i=0; i < (int)(dx.size()) && i < (int)(dy.size()) && i < (int)(dr.size()) && i < (int)(dt.size()); ++i ) {
		ret += "(" + dx[i]->Dump() + ", ";
		ret +=       dy[i]->Dump() + ", ";
		ret +=       dr[i]->Dump() + ", ";
		ret +=       dt[i]->Dump() + ")";
	}

	return ret;
}


AlanInstrAnim :: AlanInstrAnim( AlanExpr* p_cnt, vector<AlanExpr*> &p_img, vector<AlanExpr*> &p_dt ) {
	cnt = p_cnt;
	img = p_img;
	dt  = p_dt;
}
AlanInstrAnim :: ~AlanInstrAnim() {}
int AlanInstrAnim :: Execute(AlanState* stat) {

	vector<AlanExpr*>::iterator iti, itt;

	stat->anim_cnt = cnt->Eval(stat).Cast2Int();
	stat->anim_step = 0;
	stat->anim_time = 0;

	stat->anim_img.clear();
	stat->anim_dt.clear();
	string s;
	float t;
	for( iti = img.begin(), itt = dt.begin()
		 ; iti != img.end() && itt != dt.end()
		 ; ++iti, ++itt ) {
		s = (*iti)->Eval(stat).Cast2String();
		t = (*itt)->Eval(stat).Cast2Float();
		stat->anim_img.push_back(s);
		stat->anim_dt.push_back(t);
	}

	return 1;
}
bool AlanInstrAnim :: Relocate(int pc,AlanCode *code,string& error) {
	return true;
}
string AlanInstrAnim :: Dump(int pc) {

	string ret = "ANIM ";
	ret += cnt->Dump() + ",";

	for( int i=0; i < (int)(img.size()) && i < (int)(dt.size()); ++i ) {
		ret += "(" + img[i]->Dump() + ", ";
		ret += dt[i]->Dump() + ")";
	}

	return ret;
}


AlanInstrScale :: AlanInstrScale( AlanExpr* p_cnt
																, vector<AlanExpr*> &p_sx
																, vector<AlanExpr*> &p_sy
																, vector<AlanExpr*> &p_dt ) {
	cnt = p_cnt;
	sx = p_sx;
	sy = p_sy;
	dt = p_dt;
}
AlanInstrScale :: ~AlanInstrScale() {}
int AlanInstrScale :: Execute(AlanState* stat) {

	stat->scale_cnt = cnt->Eval(0).Cast2Int();
	stat->scale_step = 0;
	stat->scale_time = 0;

	stat->scale_sx.clear();
	stat->scale_sy.clear();
	stat->scale_dt.clear();

	vector<AlanExpr*>::iterator itx, ity, itt;
	float t;
	for( itx = sx.begin(), ity = sy.begin(), itt = dt.begin()
		 ; itx != sx.end() && ity != sy.end() && itt != dt.end()
		 ; ++itx, ++ity, ++itt ) {
		t = (*itt)->Eval(0).Cast2Float();
		stat->scale_sx.push_back( ((*itx)->Eval(0).Cast2Float()) );
		stat->scale_sy.push_back( ((*ity)->Eval(0).Cast2Float()) );
		stat->scale_dt.push_back( Abs(t) );
	}

	return 1;
}
bool AlanInstrScale :: Relocate(int pc,AlanCode *code,string& error) {
	return true;
}
string AlanInstrScale :: Dump(int pc) {
	string ret = "SCALE ";
	ret += cnt->Dump() + ",";

	for( int i=0; i < (int)(sx.size()) && i < (int)(sy.size()) && i < (int)(dt.size()); ++i ) {
		ret += "(" + sx[i]->Dump() + ", ";
		ret += "(" + sy[i]->Dump() + ", ";
		ret +=       dt[i]->Dump() + ")";
	}

	return ret;
}


AlanInstrGoto :: AlanInstrGoto( const string& lab ) {
	dpc = 0;
	label = lab;
}
AlanInstrGoto :: ~AlanInstrGoto() {}
void AlanInstrGoto :: SetLabel(const string& lab) {
	label = lab;
}
int AlanInstrGoto :: Execute(AlanState* stat) {
	return dpc;
}
bool AlanInstrGoto :: Relocate(int pc,AlanCode *code,string& error) {
	int refpc = code->GetLabelPC(label);
	if( refpc < 0 ) {
		error = "Odwo³anie do nieistniej¹cej etykiety o nazwie " + label;
		return false;
	}
	dpc = refpc - pc;
	return true;
}
string AlanInstrGoto :: Dump(int pc) {
	return "GOTO " + label + " [dpc=" + toString(dpc) + ", ref_pc=" + toString(pc+dpc) + "]";
}


AlanInstrGosub :: AlanInstrGosub( const string& lab ) {
	dpc = 0;
	label = lab;
}
AlanInstrGosub :: ~AlanInstrGosub() {}
void AlanInstrGosub :: SetLabel(const string& lab) {
	label = lab;
}
int AlanInstrGosub :: Execute(AlanState* stat) {
	stat->call_stack.push( stat->pc + 1 );	//zapamietujemy na stosie PC nastepnej po gosub instrukcji
	return dpc;															//i skaczemy do etykiety
}
bool AlanInstrGosub :: Relocate(int pc,AlanCode *code,string& error) {
	int refpc = code->GetLabelPC(label);
	if( refpc < 0 ) {
		error = "Odwo³anie do nieistniej¹cej etykiety o nazwie " + label;
		return false;
	}
	dpc = refpc - pc;
	return true;
}
string AlanInstrGosub :: Dump(int pc) {
	return "GOSUB " + label + " [dpc=" + toString(dpc) + ", ref_pc=" + toString(pc+dpc) + "]";
}


AlanInstrReturn :: AlanInstrReturn(void) {}
AlanInstrReturn :: ~AlanInstrReturn() {}
int AlanInstrReturn :: Execute(AlanState* stat) {
	if( stat->call_stack.size() <= 0 ) {
		return SPC_EMPTY_CALL_STACK;
	}
	int ret_pc;
	ret_pc = stat->call_stack.top();
	stat->call_stack.pop();
	return ret_pc - stat->pc;							//skaczemy o tyle instrukcji ile dzieli return od gosub
}
bool AlanInstrReturn :: Relocate(int pc,AlanCode *code,string& error) {
	return true;
}
string AlanInstrReturn :: Dump(int pc) {
	return "RETURN";
}


AlanInstrLet :: AlanInstrLet(AlanVariable* p_var,AlanExpr* p_value) : var(p_var), val(p_value) {}
AlanInstrLet :: ~AlanInstrLet() {}
int AlanInstrLet :: Execute(AlanState* stat) {
	var->SetValue( val->Eval(stat) );
	return 1;
}
bool AlanInstrLet :: Relocate(int pc,AlanCode *code,string& error) {
	return true;
}
string AlanInstrLet :: Dump(int pc) {
	return "LET " + (var!=0 ? var->Dump() : "!ADR!") + " = " + (val!=0 ? val->Dump() : "!ADR!");
}


AlanInstrFor :: AlanInstrFor(AlanVariable* p_var,AlanExpr* p_beg,AlanExpr* p_end,AlanExpr* p_step,const string& p_lab) : var(p_var), beg(p_beg), end(p_end), step(p_step), label(p_lab) {
	dpc = 0;
}
AlanInstrFor :: ~AlanInstrFor() {}
int AlanInstrFor :: Execute(AlanState* stat) {
	if( var->type == TP_INT ) {
		var->SetValue( var->Eval(stat).GetInt()+ step->Eval(stat).GetInt() );
		if( var->Eval(stat).GetInt() > end->Eval(stat).GetInt() )
			return dpc;
		return 1;
	} else {
		var->SetValue( var->Eval(stat).GetFloat()+ step->Eval(stat).GetFloat() );
		if( var->Eval(stat).GetFloat() > end->Eval(stat).GetFloat() )
			return dpc;
		return 1;
	}
	return 1;
}
bool AlanInstrFor :: Relocate(int pc,AlanCode *code,string& error) {
	int refpc = code->GetLabelPC(label);
	if( refpc < 0 ) {
		error = "Odwo³anie do nieistniej¹cej etykiety o nazwie " + label;
		return false;
	}
	dpc = refpc - pc;
	return true;
}
string AlanInstrFor :: Dump(int pc) {
	return "FOR " + (var!=0 ? var->Dump() : "!ADR!") + " = " + (beg!=0 ? beg->Dump() : "!ADR!") + " TO " + (end!=0 ? end->Dump() : "!ADR!") + " STEP " + (step!=0 ? step->Dump() : "!ADR!") + " [label=" + label + ", dpc=" + toString(dpc) + ", ref_pc=" + toString(pc+dpc) + "]";
}


AlanInstrWhile :: AlanInstrWhile(AlanExpr* p_value,const string& p_lab) : val(p_value), label(p_lab) {
	dpc = 0;
}
AlanInstrWhile :: ~AlanInstrWhile() {}
int AlanInstrWhile :: Execute(AlanState* stat) {
	AlanValue v;
	v = val->Eval(stat);
	ASSERT( v.type == TP_BOOL, "ALAN: Wartoœæ warunku instrukcji WHILE nie jest typu BOOL" );
	if( v.GetBool() )
		return 1;
	else
		return dpc;
}
bool AlanInstrWhile :: Relocate(int pc,AlanCode *code,string& error) {
	int refpc = code->GetLabelPC(label);
	if( refpc < 0 ) {
		error = "Odwo³anie do nieistniej¹cej etykiety o nazwie " + label;
		return false;
	}
	dpc = refpc - pc;
	return true;
}
string AlanInstrWhile :: Dump(int pc) {
	return "WHILE " + (val!=0 ? val->Dump() : "!ADR!") + " [label=" + label + ", dpc=" + toString(dpc) + ", ref_pc=" + toString(pc+dpc) + "]";
}


AlanInstrIf :: AlanInstrIf(AlanExpr* p_value,const string& p_lab) : val(p_value), label(p_lab) {
	dpc = 0;
}
AlanInstrIf :: ~AlanInstrIf() {}
int AlanInstrIf :: Execute(AlanState* stat) {
	AlanValue v;
	v = val->Eval(stat);
	ASSERT( v.type == TP_BOOL, "ALAN: Wartoœæ warunku instrukcji IF nie jest typu BOOL" );
	if( v.GetBool() )
		return 1;
	return dpc;
}
bool AlanInstrIf :: Relocate(int pc,AlanCode *code,string& error) {
	int refpc = code->GetLabelPC(label);
	if( refpc < 0 ) {
		error = "Odwo³anie do nieistniej¹cej etykiety o nazwie " + label;
		return false;
	}
	dpc = refpc - pc;
	return true;
}
string AlanInstrIf :: Dump(int pc) {
	return "IF " + (val!=0 ? val->Dump() : "!ADR!") + " [label=" + label + ", dpc=" + toString(dpc) + ", ref_pc=" + toString(pc+dpc) + "]";
}


AlanInstrPause :: AlanInstrPause(void) {}
AlanInstrPause :: ~AlanInstrPause() {}
int AlanInstrPause :: Execute(AlanState* stat) {
	return SPC_PAUSE_INSTR;
}
bool AlanInstrPause :: Relocate(int pc,AlanCode *code,string& error) {
	return true;
}
string AlanInstrPause :: Dump(int pc) {
	return "PAUSE";
}


AlanInstrPauseWhile :: AlanInstrPauseWhile(AlanExpr* p_value) : val(p_value) {}
AlanInstrPauseWhile :: ~AlanInstrPauseWhile() {}
int AlanInstrPauseWhile :: Execute(AlanState* stat) {
	AlanValue v;
	v = val->Eval(stat);
	ASSERT( v.type == TP_BOOL, "ALAN: Wartoœæ warunku instrukcji PAUSE WHILE nie jest typu BOOL" );
	if( v.GetBool() )
		return SPC_PAUSE_WHILE_INSTR;		//warunek spelniony, a wiec czekamy
	return 1;
}
bool AlanInstrPauseWhile :: Relocate(int pc,AlanCode *code,string& error) {
	return true;
}
string AlanInstrPauseWhile :: Dump(int pc) {
	return "PAUSE while " + (val!=0 ? val->Dump() : "!ADR!");
}


AlanCode :: AlanCode(void) {
	relocated = false;
	AddBuildins();
}
AlanCode :: ~AlanCode() {}
void AlanCode :: AddBuildins(void) {
	AddVar("X",TP_FLOAT);
	AddVar("Y",TP_FLOAT);
	AddVar("ROT",TP_FLOAT);
	AddVar("IMG",TP_STRING);
	AddVar("SX",TP_FLOAT);
	AddVar("SY",TP_FLOAT);
	AddVar("DT",TP_FLOAT);
}
void AlanCode :: Reset(void) {
	//inicjuje zmienne
	t_variables_iter vit;
	for( vit = vars.begin(); vit != vars.end(); ++vit )
		vit->second->Reset();

	//oprozniam stos wywolan
	while( speclabs.size() > 0 ) speclabs.pop();

	//relokuje kod jezeli trzeba
	if( ! relocated ) {
		string error = "";
		if( ! Relocate(error) ) {
			ERROR("B³¹d podczas relokowania kodu: " + error );
		}
	}
}
bool AlanCode :: Relocate(string& error) {
	bool lb_ret;
	for( int pc = 0; pc < (int)(code.size()); ++pc ) {
		if( 0 == code[pc] ) {
			error = "Pusta instrukcja pod adresem " + toString(pc);
			return false;
		}
		lb_ret = code[pc]->Relocate(pc,this,error);
		if( ! lb_ret ) return false;
	}
	relocated = true;
	return true;
}
int AlanCode :: Len(void) {
	return code.size();
}
int AlanCode :: Execute(int pc,AlanState *state) {
	return code.at(pc)->Execute(state);
}
string AlanCode :: DumpVars(const string& varid) {
	//zrzuca wartosci zmiennych
	string ret = "";
	t_variables_iter vit;
	if( varid != "" ) {
		vit = vars.find(varid);
		if( vit != vars.end() )
			ret += vit->second->DumpV() + "\n";
	} else {
		for( vit = vars.begin(); vit != vars.end(); ++vit )
			ret += vit->second->DumpV() + "\n";
	}
	return ret;
}
string AlanCode :: DumpLabel(int pc) {
	string ret = "";
	t_labels_iter lib;
	for( lib = labs.begin(); lib != labs.end(); ++lib )
		if( lib->second == pc ) {
			ret += lib->first + " ";
		}
	return ret;
}
string AlanCode :: DumpCode(void) {
	//zrzuca kod
	string ret = "", labs;
	for( int pc = 0; pc <= (int)(code.size()); ++pc ) {
		ret += DumpCode(pc);
	}
	return ret;
}
string AlanCode :: DumpCode(int pc) {
	//zrzuca kod
	string ret = "", labs;
	labs = DumpLabel(pc);
	if( labs != "" ) labs = ">>> " + labs + "\n      ";
	if( pc < (int)(code.size()) )
		ret += toString(pc,"%4d") + ": " + labs + (code[pc] != 0 ? code[pc]->Dump(pc) : "!NULL!") + "\n";
	else
		ret += toString(pc,"%4d") + ": " + labs + "\n";
	return ret;
}
void AlanCode :: AddLabel(const string& id) {
	t_labels_iter it;
	it = labs.find(id);
	if( it == labs.end() ) {
		labs.insert( make_pair(id,code.size()) );
	} else {
		ERROR("Label " + id + " already defined" );
	}
}
int AlanCode :: GetLabelPC(const string& id) {
	t_labels_iter it;
	it = labs.find(id);
	if( it == labs.end() ) return -1;
	return it->second;
}
int AlanCode :: AddSpecLabel(char type,string& error) {
	//dodaje specjalna etykiete (do realizacji IF, FOR, WHILE)
	if( SpecialLabel::SLT_IF == type ) {
		//IF mozna dodac zawsze
		SpecialLabel sl;
		sl.type = SpecialLabel::SLT_IF;
		sl.pc = code.size();
		sl.refpc = sl.pc;
		speclabs.push(sl);
		AddLabel("@IF@"+toString(sl.refpc));
		return sl.refpc;
	}
	if( SpecialLabel::SLT_ELSE == type ) {
		//ELSE mozna dodac tylko, gdy na stosie jest IF (w takim przypadku zastepujemy IF ELSEm)
		if( speclabs.size() <= 0 ) {
			error = "Jest ELSE, a nie ma pasuj¹cego IF";
			return -1;
		}
		SpecialLabel &sl = speclabs.top();
		if( SpecialLabel::SLT_IF != sl.type ) {
			error = "Jest ELSE, a nie ma pasuj¹cego IF";
			return -1;
		}
		sl.type = SpecialLabel::SLT_ELSE;
		sl.pc = code.size();
		//refpc zostaje takie samo jak przy IF
		AddLabel("@ELSE@"+toString(sl.refpc));
		return sl.refpc;
	}
	if( SpecialLabel::SLT_EIF == type ) {
		//EIF mozna dodac tylko, gdy na stosie jest IF lub ELSE(w takim przypadku zastepujemy IF lub ELSE EIFem)
		if( speclabs.size() <= 0 ) {
			error = "Jest EIF, a nie ma pasuj¹cego IF lub ELSE";
			return -1;
		}
		SpecialLabel &sl = speclabs.top();
		if( SpecialLabel::SLT_IF != sl.type && SpecialLabel::SLT_ELSE != sl.type) {
			error = "Jest ELSE, a nie ma pasuj¹cego IF lub ELSE";
			return -1;
		}
		int refpc = sl.refpc;
		if( SpecialLabel::SLT_ELSE != sl.type )
			AddLabel("@ELSE@"+toString(refpc));
		AddLabel("@EIF@"+toString(refpc));
		speclabs.pop();
		return refpc;
	}
	if( SpecialLabel::SLT_FOR == type ) {
		//FOR mozna dodac zawsze
		SpecialLabel sl;
		sl.type = SpecialLabel::SLT_FOR;
		sl.pc = code.size();
		sl.refpc = sl.pc;
		speclabs.push(sl);
		AddLabel("@FOR@"+toString(sl.refpc));
		return sl.refpc;
	}
	if( SpecialLabel::SLT_NEXT == type ) {
		//NEXT mozna dodac tylko, gdy na stosie jest FOR (w takim przypadku zastepujemy zdejmujemy FOR ze stosu)
		if( speclabs.size() <= 0 ) {
			error = "Jest NEXT, a nie ma pasuj¹cego FOR";
			return -1;
		}
		SpecialLabel &sl = speclabs.top();
		if( SpecialLabel::SLT_FOR != sl.type ) {
			error = "Jest NEXT, a nie ma pasuj¹cego FOR";
			return -1;
		}
		int refpc = sl.refpc;
		AddLabel("@NEXT@"+toString(refpc));
		speclabs.pop();
		return refpc;
	}
	if( SpecialLabel::SLT_WHILE == type ) {
		//WHILE mozna dodac zawsze
		SpecialLabel sl;
		sl.type = SpecialLabel::SLT_WHILE;
		sl.pc = code.size();
		sl.refpc = sl.pc;
		speclabs.push(sl);
		AddLabel("@WHILE@"+toString(sl.refpc));
		return sl.refpc;
	}
	if( SpecialLabel::SLT_WEND == type ) {
		//WEND mozna dodac tylko, gdy na stosie jest WHILE (w takim przypadku zastepujemy zdejmujemy WHILE ze stosu)
		if( speclabs.size() <= 0 ) {
			error = "Jest WEND, a nie ma pasuj¹cego WHILE";
			return -1;
		}
		SpecialLabel &sl = speclabs.top();
		if( SpecialLabel::SLT_WHILE != sl.type ) {
			error = "Jest WEND, a nie ma pasuj¹cego WHILE";
			return -1;
		}
		int refpc = sl.refpc;
		AddLabel("@WEND@"+toString(refpc));
		speclabs.pop();
		return refpc;
	}

	error = "Nieznany tryb etykiety specjalnej";
	return -1;
}
AlanVariable* AlanCode :: GetVar(const string& id ) {
	t_variables_iter it;
	it = vars.find(id);
	if( it == vars.end() ) {
		return 0;
	} else {
		return (it->second);
	}
}
AlanVariable* AlanCode :: AddVar(const string& id,char type) {
	t_variables_iter it;
	it = vars.find(id);
	if( it == vars.end() ) {
		switch( type ) {
			case TP_BOOL:
				{
					AlanBoolVar* var = new AlanBoolVar(id);
					vars.insert( make_pair(id,var) );
					return var;
				}
			case TP_INT:
				{
					AlanIntVar* var = new AlanIntVar(id);
					vars.insert( make_pair(id,var) );
					return var;
				}
			case TP_FLOAT:
				{
					AlanFloatVar* var = new AlanFloatVar(id);
					vars.insert( make_pair(id,var) );
					return var;
				}
			case TP_STRING:
				{
					AlanStringVar* var = new AlanStringVar(id);
					vars.insert( make_pair(id,var) );
					return var;
				}
			default:
				ERROR("ALAN: Nieznany typ deklarowanej zmiennej");
				return 0;	//nieznany typ
		}
	} else {
		return 0;	//juz taka zmienna jest
	}
}
void AlanCode :: AddInstrMove(AlanExpr *cnt, vector<AlanExpr*> &dx,vector<AlanExpr*> &dy,vector<AlanExpr*> &dr, vector<AlanExpr*> &dt) {
	code.push_back( new AlanInstrMove(cnt,dx,dy,dr,dt) );
}
void AlanCode :: AddInstrAnim(AlanExpr *cnt, vector<AlanExpr*> &img, vector<AlanExpr*> &dt) {
	code.push_back( new AlanInstrAnim(cnt,img,dt) );
}
void AlanCode :: AddInstrScale(AlanExpr *cnt, vector<AlanExpr*> &sx,vector<AlanExpr*> &sy,vector<AlanExpr*> &dt) {
	code.push_back( new AlanInstrScale(cnt,sx,sy,dt) );
}
void AlanCode :: AddInstrGoto(const string& label) {
	code.push_back( new AlanInstrGoto(label) );
}
void AlanCode :: AddInstrGosub(const string& label) {
	code.push_back( new AlanInstrGosub(label) );
}
void AlanCode :: AddInstrReturn(void) {
	code.push_back( new AlanInstrReturn() );
}
void AlanCode :: AddInstrLet(AlanVariable* var,AlanExpr* value) {
	code.push_back( new AlanInstrLet(var,value) );
}
bool AlanCode :: AddInstrFor(AlanVariable* var,AlanExpr* beg,AlanExpr* end,AlanExpr* step,string& error) {
	code.push_back( new AlanInstrLet(var,beg) );
	AlanInstrGoto* gt = new AlanInstrGoto("");
	code.push_back(gt);
	int refpc = AddSpecLabel(SpecialLabel::SLT_FOR,error);
	if( refpc < 0 ) return false;
	code.push_back( new AlanInstrFor(var,beg,end,step,"@NEXT@"+toString(refpc)) );
	AddLabel("@FOR_ASTEP@"+toString(refpc));
	gt->SetLabel("@FOR_ASTEP@"+toString(refpc));
	return true;
}
bool AlanCode :: AddInstrNext(string& error) {
	AlanInstrGoto* gt = new AlanInstrGoto("");
	code.push_back(gt);
	int refpc = AddSpecLabel(SpecialLabel::SLT_NEXT,error);
	if( refpc < 0 ) return false;
	gt->SetLabel("@FOR@"+toString(refpc));
	return true;
}
bool AlanCode :: AddInstrWhile(AlanExpr* value,string& error) {
	int refpc = AddSpecLabel(SpecialLabel::SLT_WHILE,error);
	if( refpc < 0 ) return false;
	code.push_back( new AlanInstrWhile(value,"@WEND@"+toString(refpc)) );
	return true;
}
bool AlanCode :: AddInstrWend(string& error) {
	AlanInstrGoto* gt = new AlanInstrGoto("");
	code.push_back(gt);
	int refpc = AddSpecLabel(SpecialLabel::SLT_WEND,error);
	if( refpc < 0 ) return false;
	gt->SetLabel("@WHILE@"+toString(refpc));
	return true;
}
bool AlanCode :: AddInstrIf(AlanExpr* value,string& error) {
	int refpc = AddSpecLabel(SpecialLabel::SLT_IF,error);
	if( refpc < 0 ) return false;
	code.push_back( new AlanInstrIf(value,"@ELSE@"+toString(refpc)) );
	return true;
}
bool AlanCode :: AddInstrElse(string& error) {
	AlanInstrGoto* gt = new AlanInstrGoto("");
	code.push_back(gt);
	int refpc = AddSpecLabel(SpecialLabel::SLT_ELSE,error);
	if( refpc < 0 ) return false;
	gt->SetLabel("@EIF@"+toString(refpc));
	return true;
}
bool AlanCode :: AddInstrEif(string& error) {
	int refpc = AddSpecLabel(SpecialLabel::SLT_EIF,error);
	if( refpc < 0 ) return false;
	return true;
}
bool AlanCode :: AddInstrPause(string& error) {
	code.push_back( new AlanInstrPause() );
	return true;
}
bool AlanCode :: AddInstrPauseWhile(AlanExpr* value,string& error) {
	code.push_back( new AlanInstrPauseWhile(value) );
	return true;
}
void AlanCode :: SetVarVal(const string& varname,bool v) {
	AlanVariable *var = GetVar(varname);
	ASSERT( 0 != var, "ALAN: Zmienna " + varname + " nieistnieje" );
	ASSERT( TP_BOOL == var->type, "ALAN: Proba przypisania zmiennej typu " + TypeName(var->type) + " wartoœci typu BOOL");
	var->SetValue(v);
}
void AlanCode :: SetVarVal(const string& varname,int v) {
	AlanVariable *var = GetVar(varname);
	ASSERT( 0 != var, "ALAN: Zmienna " + varname + " nieistnieje" );
	ASSERT( TP_INT == var->type, "ALAN: Proba przypisania zmiennej typu " + TypeName(var->type) + " wartoœci typu INT");
	var->SetValue(v);
}
void AlanCode :: SetVarVal(const string& varname,float v) {
	AlanVariable *var = GetVar(varname);
	ASSERT( 0 != var, "ALAN: Zmienna " + varname + " nieistnieje" );
	ASSERT( TP_FLOAT == var->type, "ALAN: Proba przypisania zmiennej typu " + TypeName(var->type) + " wartoœci typu FLOAT");
	var->SetValue(v);
}
void AlanCode :: SetVarVal(const string& varname,const string& v) {
	AlanVariable *var = GetVar(varname);
	ASSERT( 0 != var, "ALAN: Zmienna " + varname + " nieistnieje" );
	ASSERT( TP_STRING == var->type, "ALAN: Proba przypisania zmiennej typu " + TypeName(var->type) + " wartoœci typu STRING");
	var->SetValue(v);
}
bool AlanCode :: GetVarValB(const string& varname) {
	AlanVariable *var = GetVar(varname);
	ASSERT( 0 != var, "ALAN: Zmienna " + varname + " nieistnieje" );
	return var->Eval(0).GetBool();
}
int AlanCode :: GetVarValI(const string& varname) {
	AlanVariable *var = GetVar(varname);
	ASSERT( 0 != var, "ALAN: Zmienna " + varname + " nieistnieje" );
	return var->Eval(0).GetInt();
}
float AlanCode :: GetVarValF(const string& varname) {
	AlanVariable *var = GetVar(varname);
	ASSERT( 0 != var, "ALAN: Zmienna " + varname + " nieistnieje" );
	return var->Eval(0).GetFloat();
}
string AlanCode :: GetVarValS(const string& varname) {
	AlanVariable *var = GetVar(varname);
	ASSERT( 0 != var, "ALAN: Zmienna " + varname + " nieistnieje" );
	return var->Eval(0).GetString();
}


AlanVM :: AlanVM(void) {
	code = 0;
	state = 0;
	code_finished = true;
}
AlanVM :: ~AlanVM() {}
void AlanVM :: SetCode( AlanCode* c ) {
	code = c;
	state = new AlanState();
}
AlanState* AlanVM :: GetState(void) {
	return state;
}
void AlanVM :: Reset(void) {
	if( 0 == code ) {
		ERROR("ALAN_VM: Brak kodu");
		return;
	}
	code->Reset();
	state->Reset();
	code_finished = false;
}
void AlanVM :: Continue(void) {

	if( code_finished ) return;

	int inc_pc;
	while( state->pc < code->Len() ) {
		inc_pc = code->Execute(state->pc,state);
		if( inc_pc >= SPC_IS_SPECIAL ) {
			switch( inc_pc ) {
				case SPC_PAUSE_INSTR:
					state->pc += 1;
					return;
				case SPC_PAUSE_WHILE_INSTR:
					//nie zmieniamy PC - pause czeka, az przestanie zachodzic warunek, i wtedy zwroci 1 a nie SPC_PAUSE_WHILE_INSTR
					return;
				case SPC_EMPTY_CALL_STACK:
					//blad - RETURN kiedy nie bylo GOSUB
					goto finish;
				default:
					state->pc += 1;
					break;
			}
		} else {
			state->pc += inc_pc;
		}
	}

	finish:
	code_finished = true;
}
void AlanVM :: DebugContinue(void) {

	if( code_finished ) {
		ERROR("ALANVM_DBG: Code finished");
		return;
	}

	int inc_pc;
	while( state->pc < code->Len() ) {
		inc_pc = code->Execute(state->pc,state);
		ERROR("ALANVM_DBG: " + code->DumpCode(state->pc));
		if( inc_pc >= SPC_IS_SPECIAL ) {
			switch( inc_pc ) {
				case SPC_PAUSE_INSTR:
					state->pc += 1;
					return;
				case SPC_PAUSE_WHILE_INSTR:
					//nie zmieniamy PC - pause czeka, az przestanie zachodzic warunek, i wtedy zwroci 1 a nie SPC_PAUSE_WHILE_INSTR
					return;
				case SPC_EMPTY_CALL_STACK:
					//blad - RETURN kiedy nie bylo GOSUB
					ERROR("ALANVM_DBG: ERROR - RETURN without GOSUB - call stack is empty");
					goto finish;
				default:
					state->pc += 1;
					break;
			}
		} else {
			state->pc += inc_pc;
		}
	}

	finish:
	code_finished = true;
	ERROR("ALANVM_DBG: end");
}
string AlanVM :: DumpVars(void) {
	if( 0 == code ) return "NO CODE!!!";
	return code->DumpVars("");
}
void AlanVM :: SetVarVal(const string& varname,float v) {
	ASSERT( 0 != code, "ALAN: Brak kodu" );
	code->SetVarVal(varname,v);
}
float AlanVM :: GetVarValF(const string& varname) {
	ASSERT( 0 != code, "ALAN: Brak kodu" );
	return code->GetVarValF(varname);
}



}		//namespace
