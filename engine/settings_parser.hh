/******************************************************************
 * File: settings_parser.hh
 *
 * This file was automatically generated by CppCC Version 0.0.8
 * DO NOT EDIT MANUALLY
 ******************************************************************/


#ifndef __SETTINGS_PARSER_HH__
#define __SETTINGS_PARSER_HH__

#include <iostream>
#include <string>
#include <exception>

#include "settings_token.hh"
#include "settings_scanner.hh"
namespace cppcc
{

class ParseException : public std::exception
{
  public:
    
    ParseException (const std::string &message_ = "Parse exception") :
      message(message_)
    {}
    
    ParseException (const Position &pos_,
                   const std::string &message_ = "Parse exception") :
      pos(pos_), message(message_)
    {}
    
    ~ParseException () throw ()
    {}
    
    virtual operator std::string () const
    {
      return std::string(pos) + ": " + message;
    }
    
    virtual const char* what () throw ()
    {
      return message.c_str();
    }
    
    virtual Position& where () throw ()
    {
      return pos;
    }
    
  private:
  
    Position pos;
    std::string message;
}; // end class PasreException


class SettingsParser_base
{
  protected:
    bool onParseError (ParseException &pex) { return false; }
};


class SettingsParser : public SettingsParser_base
{
  public: // methods
    
    SettingsParser (std::istream *in_ = NULL) throw (ScanException, ParseException) :
       scanner(in_), _la(0)
    {}
    
    // productions entry points:
    
    
#line 113 "settings.cg"
Symbol*
#line 80 "settings_parser.hh"

     parse ()
       throw (ScanException, ParseException);
    void
     wezel_lub_lisc (
#line 120 "settings.cg"
Symbol* s)
#line 88 "settings_parser.hh"

       throw (ScanException, ParseException);
    
#line 129 "settings.cg"
Symbol*
#line 94 "settings_parser.hh"

     lisc ()
       throw (ScanException, ParseException);
    
#line 138 "settings.cg"
Symbol*
#line 101 "settings_parser.hh"

     wezel ()
       throw (ScanException, ParseException);
    
#line 148 "settings.cg"
ValueList*
#line 108 "settings_parser.hh"

     value ()
       throw (ScanException, ParseException);
    
#line 155 "settings.cg"
ValueList*
#line 115 "settings_parser.hh"

     simpleValue ()
       throw (ScanException, ParseException);
    
#line 164 "settings.cg"
ValueList*
#line 122 "settings_parser.hh"

     booleanConstant ()
       throw (ScanException, ParseException);
    
#line 174 "settings.cg"
ValueList*
#line 129 "settings_parser.hh"

     listValue ()
       throw (ScanException, ParseException);
    
#line 186 "settings.cg"
Symbol*
#line 136 "settings_parser.hh"

     scopedId (
#line 186 "settings.cg"
Symbol* &last)
#line 141 "settings_parser.hh"

       throw (ScanException, ParseException);
    
#line 196 "settings.cg"
Symbol*
#line 147 "settings_parser.hh"

     extract (
#line 196 "settings.cg"
Symbol* src)
#line 152 "settings_parser.hh"

       throw (ScanException, ParseException);
    
#line 224 "settings.cg"
Symbol::ChildList*
#line 158 "settings_parser.hh"

     find (
#line 224 "settings.cg"
Symbol* src, int &child_index)
#line 163 "settings_parser.hh"

       throw (ScanException, ParseException);
    
#line 274 "settings.cg"
Symbol::ChildList*
#line 169 "settings_parser.hh"

     oneStepOnPath (
#line 274 "settings.cg"
Symbol* src,int &idx)
#line 174 "settings_parser.hh"

       throw (ScanException, ParseException);
    
    // productions LA methods:
    
    bool __la_parse_ () throw (ScanException);
    bool __la_wezel_lub_lisc_ () throw (ScanException);
    bool __la_lisc_ () throw (ScanException);
    bool __la_wezel_ () throw (ScanException);
    bool __la_value_ () throw (ScanException);
    bool __la_simpleValue_ () throw (ScanException);
    bool __la_booleanConstant_ () throw (ScanException);
    bool __la_listValue_ () throw (ScanException);
    bool __la_scopedId_ () throw (ScanException);
    bool __la_extract_ () throw (ScanException);
    bool __la_find_ () throw (ScanException);
    bool __la_oneStepOnPath_ () throw (ScanException);
    
    // lookahead entry points:
    
    // LA entry points for parse
    
    // LA entry points for wezel_lub_lisc
    
    bool __la_0_ (int depth) throw (ScanException);
    // LA entry points for lisc
    
    // LA entry points for wezel
    
    // LA entry points for value
    
    // LA entry points for simpleValue
    
    // LA entry points for booleanConstant
    
    // LA entry points for listValue
    
    // LA entry points for scopedId
    
    // LA entry points for extract
    
    // LA entry points for find
    
    // LA entry points for oneStepOnPath
    
    
    
  private: // methods
    
    void consumeToken (int tId)  throw (ScanException, ParseException)
    {
      if ((token = scanner.la())->id != tId)
      {
        ParseException pex(scanner.la()->bPos, "Parse error.");
        if (!onParseError(pex)) throw pex;
      }
      scanner.unchecked_consume();
    }
    
    bool laConsumeToken (int tId)  throw (ScanException, ParseException)
    {
      if (scanner.la()->id != tId) return false;
      scanner.unchecked_consume();
      return true;
    }
    
  public: // data
    
    SettingsScanner scanner;
    int _la;
    SettingsToken *token;
    
}; //end class SettingsParser


} //end namespace cppcc


#endif // ifndef __SETTINGS_PARSER_HH__


/* End of file. */