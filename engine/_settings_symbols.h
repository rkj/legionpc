#ifndef D_SETTINGS_SYMBOLS_H_D
#define D_SETTINGS_SYMBOLS_H_D

#include <string>
#include <vector>
#include <map>
#include <cstdio>


class ValueList {
protected:
	char	type_id;

	union V {
		bool		bval;
		long		ival;
		double	fval;
		std::string	*sval;
	};

	std::vector<V> val;

	enum TYPE_IDS {
        TID_NONE		= 0
	,   TID_BOOL		= 1
	,	TID_INT			= 2
	,   TID_FLOAT		= 3
	,   TID_STRING	    = 4
	};
	enum Exceptions {
		EXCP_OK			= 0
	,	EXCP_BAD_TYPE		= 1
	};
public:
	ValueList(void) {
		type_id = TID_NONE;
	}
	ValueList(bool v) {
		type_id = TID_BOOL;
		Append(v);
	}
	ValueList(long v) {
		type_id = TID_INT;
		Append(v);
	}
	ValueList(double v) {
		type_id = TID_FLOAT;
		Append(v);
	}
	ValueList(const std::string& v) {
		type_id = TID_STRING;
		Append(v);
	}
	~ValueList() {
		if( TID_STRING == type_id ) {
			std::vector<V>::iterator it;
			for( it = val.begin(); it != val.end(); ++it )
				delete (*it).sval;
		}
	}

	bool IsB() const {
		return TID_BOOL == type_id;
	}
	bool IsI() const {
		return TID_INT == type_id;
	}
	bool IsF() const {
		return TID_FLOAT == type_id;
	}
	bool IsS() const {
		return TID_STRING == type_id;
	}

	void Append(bool v) {
		if( TID_NONE == type_id )
			type_id = TID_BOOL;
		else
			if( type_id != TID_BOOL ) throw EXCP_BAD_TYPE;
		V x;
		x.bval = v;
		val.push_back(x);
	}
	void Append(long v) {
		if( TID_NONE == type_id )
			type_id = TID_INT;
		else
			if( type_id != TID_INT ) throw EXCP_BAD_TYPE;
		V x;
		x.ival = v;
		val.push_back(x);
	}
	void Append(double v) {
		if( TID_NONE == type_id )
			type_id = TID_FLOAT;
		else
			if( type_id != TID_FLOAT ) throw EXCP_BAD_TYPE;
		V x;
		x.fval = v;
		val.push_back(x);
	}
	void Append(const std::string& v) {
		if( TID_NONE == type_id )
			type_id = TID_STRING;
		else
			if( type_id != TID_STRING ) throw EXCP_BAD_TYPE;
		V x;
		x.sval = new std::string(v);
		val.push_back(x);
	}
	void Append(ValueList* v) {
		if( TID_NONE == type_id )
			type_id = v->type_id;
		else
			if( type_id != v->type_id ) throw EXCP_BAD_TYPE;
		std::vector<V>::iterator it;
		for( it = v->val.begin(); it != v->val.end(); ++it )
			switch( v->type_id ) {
				case TID_BOOL:		Append( (*it).bval ); break;
				case TID_INT:		Append( (*it).ival ); break;
				case TID_FLOAT:		Append( (*it).fval ); break;
				case TID_STRING:	Append( *((*it).sval) ); break;
			}
	}

	bool GetB(int idx) const {
		if( type_id != TID_BOOL ) return false;
		return val.at(idx).bval;
	}

	long GetI(int idx) const {
		if( type_id != TID_INT ) return 0;
		return val.at(idx).ival;
	}

	double GetF(int idx) const {
		if( type_id != TID_FLOAT ) return 0;
		return val.at(idx).fval;
	}

	const std::string& GetS(int idx) const {
		static std::string ls_null = "";
		if( type_id != TID_STRING ) return ls_null;
		return *(val.at(idx).sval);
	}


	std::string dump(void) const {
		std::string str = "";
		char buf[256];
		std::vector<V>::const_iterator it;
		for( it = val.begin(); it != val.end(); ++it ) {
			switch( type_id ) {
				case TID_BOOL:
					sprintf(buf,"(B)%s, ",it->bval ? "TRUE" : "FALSE");
					str += buf;
					break;
				case TID_INT:
					sprintf(buf,"(I)%ld, ",it->ival);
					str += buf;
					break;
				case TID_FLOAT:
					sprintf(buf,"(F)%f, ",it->fval);
					str += buf;
					break;
				case TID_STRING:
					str += "(S)\"" + *(it->sval) + "\"\n";
					break;
			}
		}
		if( TID_STRING != type_id && "" != str )
			str += "\n";
		return str;
	}
};

class Symbol {
protected:
	std::string name;
	ValueList val;
public:
	typedef std::vector<Symbol*> ChildList;
	typedef ChildList::iterator ChildListIter;
	typedef ChildList::const_iterator ConstChildListIter;
	typedef ChildList::reverse_iterator ChildListRIter;
	typedef ChildList::const_reverse_iterator ConstChildListRIter;
protected:
	typedef std::map<std::string,ChildList*> Childs;
	typedef Childs::iterator ChildsIter;
	typedef Childs::const_iterator ConstChildsIter;
	typedef Childs::reverse_iterator ChildsRIter;
	typedef Childs::const_reverse_iterator ConstChildsRIter;

	Childs childs;

	bool ref_childs;	//jezeli TRUE to przy destruktorze nie niszczymy dzieciakow, bo mamy do nich jedynie wskazniki i moga byc uzywane w innych kontekstach

	std::string _indent(const std::string& block) const {
		if( block.length() <= 0 ) return "";
		std::string ret = "  ";
		int last = 0, curr;
		for( int i = 0; i < (int)(block.length()); ++i ) {
			curr = block.at(i);
			if( '\n' != curr && '\r' != curr && ('\n' == last || '\r' == last) )
				ret += "  ";
			ret += curr;
			last = curr;
		}
		return ret;
	}

	std::string _to_char(int i) const {
		char buf[128];
		sprintf(buf,"%d",i);
		return std::string(buf);
	}

	std::string _dump(int child_nr) const {
		std::string str = "", c = "";

		if( 0 != name.length() )
			str += "<" + name + "[" + _to_char(child_nr) + "]>\n";
		else
			str += "<ROOT>\n";

		str += _indent(val.dump());

		ConstChildsRIter it;
		ChildList *cl;
		ConstChildListIter cit;
		Symbol *child;
		int cnum;
		for( it = childs.rbegin(); it != childs.rend(); ++it ) {
			cl = it->second;
			cnum = 1;
			for( cit = cl->begin(); cit != cl->end(); ++cit ) {
				child = *cit;
				c = _indent( child->_dump(cnum) );
				str += c;
				++cnum;
			}
		}


		if( 0 != name.length() )
			str += "</" + name + ">\n";
		else
			str += "</ROOT>\n";

		return str;
	}

public:
	Symbol(bool ref_childs=false) {
		name = "";
		this->ref_childs = ref_childs;
		childs.clear();
	}
	Symbol(const std::string& name,bool ref_childs=false) {
		this->name = name;
		this->ref_childs = ref_childs;
		childs.clear();
	}
	~Symbol() {
		ChildsIter it;
		ChildList *cl;
		ChildListIter cit;
		for( it = childs.begin(); it != childs.end(); ++it ) {
			cl = it->second;
			if( ! ref_childs ) {
				//nie zwalniamy dzieciakow w trybie REF
				for( cit = cl->begin(); cit != cl->end(); ++cit )
					delete *(cit);
			}
			delete cl;
		}
	}

	void SetName(const std::string& name) {
		this->name = name;
	}
	const std::string& GetName(void) {
		return this->name;
	}

	template <typename TYP>
	void AppendVal(TYP v) {
		val.Append(v);
	}

	bool Exists(int cidx,int vidx) const {
		//w "childs" mamy mapê string->ChildList
		//obiekt Symbol, z którego pobieramy dane powinnien zawierac tylko
		//dzieciaki o jednakowej nazwie, a wiec mapa jest jednoelementowa
		ChildList *cl = childs.rbegin()->second;
		if( cl ) {
			Symbol* sym = cl->at(cidx);
			if( sym )
				return true;
		}
		return false;
	}

	bool IsValB(int cidx) const {
		ChildList *cl = childs.rbegin()->second;
		if( cl ) {
			Symbol* sym = cl->at(cidx);
			if( sym )
				return sym->val.IsB();
			return false;
		}
		return false;
	}
	bool IsValI(int cidx) const {
		ChildList *cl = childs.rbegin()->second;
		if( cl ) {
			Symbol* sym = cl->at(cidx);
			if( sym )
				return sym->val.IsI();
			return false;
		}
		return false;
	}
	bool IsValF(int cidx) const {
		ChildList *cl = childs.rbegin()->second;
		if( cl ) {
			Symbol* sym = cl->at(cidx);
			if( sym )
				return sym->val.IsF();
			return false;
		}
		return false;
	}
	bool IsValS(int cidx) const {
		ChildList *cl = childs.rbegin()->second;
		if( cl ) {
			Symbol* sym = cl->at(cidx);
			if( sym )
				return sym->val.IsS();
			return false;
		}
		return false;
	}


	bool GetValB(int cidx,int vidx) const {
		//w "childs" mamy mapê string->ChildList
		//obiekt Symbol, z którego pobieramy dane powinnien zawierac tylko
		//dzieciaki o jednakowej nazwie, a wiec mapa jest jednoelementowa
		ChildList *cl = childs.rbegin()->second;
		if( cl ) {
			Symbol* sym = cl->at(cidx);
			if( sym )
				return sym->val.GetB(vidx);
			return false;
		}
		return false;
	}

	long GetValI(int cidx,int vidx) const {
		//w "childs" mamy mapê string->ChildList
		//obiekt Symbol, z którego pobieramy dane powinnien zawierac tylko
		//dzieciaki o jednakowej nazwie, a wiec mapa jest jednoelementowa
		ChildList *cl = childs.rbegin()->second;
		if( cl ) {
			Symbol* sym = cl->at(cidx);
			if( sym )
				return sym->val.GetI(vidx);
			return 0;
		}
		return 0;
	}

	double GetValF(int cidx,int vidx) const {
		//w "childs" mamy mapê string->ChildList
		//obiekt Symbol, z którego pobieramy dane powinnien zawierac tylko
		//dzieciaki o jednakowej nazwie, a wiec mapa jest jednoelementowa
		ChildList *cl = childs.rbegin()->second;
		if( cl ) {
			Symbol* sym = cl->at(cidx);
			if( sym )
				return sym->val.GetF(vidx);
			return 0.0;
		}
		return 0.0;
	}

	const std::string& GetValS(int cidx,int vidx) const {
		//w "childs" mamy mapê string->ChildList
		//obiekt Symbol, z którego pobieramy dane powinnien zawierac tylko
		//dzieciaki o jednakowej nazwie, a wiec mapa jest jednoelementowa
		static std::string ls_null = std::string("");
		ChildList *cl = childs.rbegin()->second;
		if( cl ) {
			Symbol* sym = cl->at(cidx);
			if( sym )
				return sym->val.GetS(vidx);
			return ls_null;
		}
		return ls_null;
	}

	ChildList* GetChilds(const std::string& name) {
		ChildsIter it;
		it = childs.find(name);
		if( it == childs.end() )
			return 0;
		else
			return it->second;
	}

	ChildList* GetChilds(void) {
		ChildsIter it;
		it = childs.begin();
		if( it == childs.end() )
			return 0;
		else
			return it->second;
	}

	void AppendChild(Symbol* s) {
		if( 0 == s ) return;
		ChildList* cl = GetChilds(s->name);
		if( 0 == cl ) {
			//nie ma jeszcze takiej listy dzieciakow
			cl = new ChildList();
			childs.insert( make_pair(s->name,cl) );
		}
		cl->push_back(s);	//dorzucamy symbol do listy

	}

	std::string dump(void) const {
		return _dump(1);
	}

};


#endif
