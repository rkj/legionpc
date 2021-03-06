/******************************************************************
 * File: alan_token.hh
 *
 * This file was automatically generated by CppCC Version 0.0.8
 * DO NOT EDIT MANUALLY
 ******************************************************************/


#ifndef __ALAN_TOKEN_HH__
#define __ALAN_TOKEN_HH__

#include <string>
#include <sstream>

namespace cppcc
{

class Position
{
  public:
    Position () : ln(0), col(0) {}
    Position (int ln_, int col_) : ln(ln_), col(col_) {}
    Position (const Position &o) : ln(o.ln), col(o.col) {}
    
    operator std::string () const
    {
      std::ostringstream oss;
      oss << ln << ":" << col;
      return oss.str();
    }
    
    int ln, col;
};

class AlanToken
{
  friend class AlanScanner;
  public:
    
    AlanToken () : _img_valid(true) {}
    AlanToken (int id_, const std::string &_str_img_, 
              const Position &bPos_, const Position &ePos_) :
      id(id_), bPos(bPos_), ePos(ePos_), _img_valid(true), _str_img(_str_img_)
    {}
    AlanToken (int id_, const Position &bPos_, const Position &ePos_) :
      id(id_), bPos(bPos_), ePos(ePos_), _img_valid(true)
    {}
    AlanToken (int id_) : 
      id(id_), _img_valid(true)
    {}
    AlanToken (const std::string &_str_img_) : 
      _img_valid(true), _str_img(_str_img_)
    { length = _str_img.length(); }
    AlanToken (int id_, const Position &bPos_) :
      id(id_), bPos(bPos_), ePos(bPos_), _img_valid(true)
    {}
  
  public:
    int id;
    Position bPos, ePos;
    int length;
    std::string& image()
    {
      _cacheImg();
      return _str_img;
    }
  
  private:
    const char *_img_start; //points into the scanner's buffer
    bool _img_valid; //true if the string image is in sync with the buffer
    std::string _str_img; //caches the image as a string
    
    void _set (int id_, const Position &bPos_, const Position &ePos_,
               const char *_img_start_, int length_)
    {
      id = id_; bPos = bPos_; ePos = ePos_;
      _img_start = _img_start_; length = length_;
      _img_valid = false;
    }
    
    void _set (const char *_img_start_, int length_)
    {
      _img_start = _img_start_; length = length_;
      _img_valid = false;
    }
    void _cacheImg()
    {
      if (!_img_valid) {
        _str_img.assign(_img_start, length);
        _img_valid = true;
      }
    }
    
  private: // user code
  
#line 13 "ALan.cg"

#line 99 "alan_token.hh"

  
   /* Token id constants: */
  public:
  
    static const int eof;
    static const int ws;
    static const int eol;
    static const int EOL_COMMENT;
    static const int COMMA;
    static const int SEMICOLON;
    static const int LPAR;
    static const int RPAR;
    static const int ASSIGN;
    static const int PLUS;
    static const int MINUS;
    static const int MUL;
    static const int DIV;
    static const int MOD;
    static const int NOT;
    static const int AND;
    static const int OR;
    static const int TRUE;
    static const int FALSE;
    static const int LT;
    static const int GT;
    static const int LE;
    static const int GE;
    static const int NE;
    static const int BOOL;
    static const int INT;
    static const int FLOAT;
    static const int STRING;
    static const int MOVE;
    static const int ANIM;
    static const int SCALE;
    static const int GOTO;
    static const int GOSUB;
    static const int RETURN;
    static const int FOR;
    static const int TO;
    static const int STEP;
    static const int NEXT;
    static const int WHILE;
    static const int WEND;
    static const int IF;
    static const int ELSE;
    static const int EIF;
    static const int PAUSE;
    static const int IS;
    static const int MOVING;
    static const int ANIMATING;
    static const int SCALING;
    static const int MOUSE;
    static const int KEY;
    static const int STRLEN;
    static const int SUBSTR;
    static const int INSTR;
    static const int RAND;
    static const int RANDF;
    static const int SIN;
    static const int COS;
    static const int TAN;
    static const int EXP;
    static const int LOG;
    static const int POW;
    static const int SQRT;
    static const int ABS;
    static const int SGN;
    static const int FLOOR;
    static const int CEIL;
    static const int MIN;
    static const int MAX;
    static const int MAGICCODE;
    static const int DEC_CONSTANT;
    static const int FLOAT_CONSTANT;
    static const int STRING_LITERAL;
    static const int IDENT;
    
}; // end of AlanToken class


} // end namespace cppcc
#endif // ifndef __ALAN_TOKEN_HH__


/* End of file. */
