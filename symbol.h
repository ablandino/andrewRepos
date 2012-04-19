/*
 File:  symbol.h

 Purpose: lists member functions and data members for the symbol and reel class.

*/
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include "string.h"
using namespace std;

class symbol{
 public:
   symbol();
   ~symbol();
   bool setname( char*,int );
   bool setvalue( int );
   bool setbonus( bool );
   char* getname() const;
   int getvalue() const;   
   bool getbonus() const;
   void sprint() const;

 private:
   char* s_name;
   int value;
   bool bonus;

};

class reel{
 public:
  reel(int=10 );
  ~reel();
  reel( const reel& );
  bool setreel(symbol*,int,bool,int,int);
  void print(int)const;
  void fprint(int, ofstream&);  
  void spinreel(int);
  void printdiagonal( int )const;

 private:
  symbol * sym_ptr;
  int payline;
  int num_reel_sym; 
};
