

/*
 File: symbol.cpp

 Purpose: implementation file for the symbol class and reel class, for public member functions.

*/

#include "symbol.h"

// constructor
symbol::symbol()
{
 s_name = NULL;
 value = 0;
 bonus = false;
}

// destructor
symbol::~symbol()
{
 delete[] s_name;
 s_name = NULL;
 value = 0;
 bonus = false;
}

/*
 Function: setvalue
 
 Purpose: sets the value of the value private datamember, within the range of 0 - 10.
	  returns false if value input was out of bounds.
*/
bool symbol::setvalue( int x )
{
 if( x >= 0 && x <= 10 )
 {
  value = x;
  return true;
 }

 else
 {
  value = 0;
  return false;
 }

}

/*
 Function: setbonus

 Purpose: sets the bonus bool to the symbol class.
*/
bool symbol::setbonus( bool x )
{
  bonus = x;
  return true;
}

/*
 Function: getvalue

 Purpose: returns the int value from the symbol class.
*/
int symbol::getvalue() const
{
 return value;
}

/*
 Function: getbonus
  
 Purpose: returns the bool bonus from the symbol class.
*/
bool symbol::getbonus() const
{
 return bonus;
}

/*
 Function: getname

 Purpose: returns the char pointer s_name from the symbol class.
*/
char* symbol::getname() const
{
 char* tmp = s_name;
 return s_name;
}

/*
 Function: setname

 Purpose: sets the s_name to an array of characters dynamically, with exact sizing.
	  Must be sent the length of the string.
*/
bool symbol::setname( char* source, int len )
{
  int i =0;
  s_name = new char[len+1];

  while( source[i] != '\0' )
  {
   s_name[i]= source[i];
   i++;
  }
  s_name[i]= '\0';
  
  return true;
}

/*
 Function: sprint
i
 Purpose: prints the class symbol data members, excluding the bool bonus.
*/
void symbol::sprint() const
{
 cout<<setw(8)<<s_name <<' '<<setw(2)<< value;
}

// default constructor
reel::reel(int a)
{
 if( a >= 10 && a <= 15 )
   num_reel_sym = a;

 else
  num_reel_sym = 10;
 
 sym_ptr = new symbol[num_reel_sym];
  payline = 0;
}

// copy constructor
reel::reel( const reel &a )
{
 sym_ptr = a.sym_ptr;
 payline = a.payline; 
 num_reel_sym = a.num_reel_sym;
}

// destructor
reel::~reel()
{
 delete[] sym_ptr;
 sym_ptr = NULL;
 num_reel_sym = 0;
}

/*
 Function: setreel

 Purpose: sets a reel either vertically, or horizontally, determined by the bool nload.
	  true for vertically, false for horizontally. 
*/
bool reel::setreel( symbol* s_ptr, int num_sym, bool nload, int row, int col  )
{
 bool status;
 int rnum,len;
 char* tmp = NULL;

if( nload )
{
 for( int i=0; i < num_reel_sym; i++ )
 {
  rnum = rand() % num_sym;
  tmp = s_ptr[rnum].getname();
  len = strlen( tmp );
  status = sym_ptr[i].setname( tmp,len );
  status = sym_ptr[i].setvalue( s_ptr[rnum].getvalue() );
  status = sym_ptr[i].setbonus( s_ptr[rnum].getbonus() );
 }
}
 else
 {
  tmp = s_ptr[col].getname();
  len = strlen( tmp );
  sym_ptr[row].setname( tmp, len );
  sym_ptr[row].setvalue( s_ptr[col].getvalue() );
  sym_ptr[row].setbonus( s_ptr[col].getbonus() );
}


 return true;
}

/*
 Function: spinreel

 Purpose: spins the reel by displaying the paylines for a reel.
*/
void reel::spinreel( int num_reel )
{
 payline = rand() % num_reel_sym;
 int offset = -( num_reel / 2 );
 int offsetMax = num_reel - (num_reel / 2 );

 while( offset < offsetMax )
 {
  int shifted_payline = (payline + offset) % num_reel_sym;
 
  if( shifted_payline < 0 )
   shifted_payline += num_reel_sym;
  sym_ptr[shifted_payline].sprint();
  offset++;
 }
 cout << endl;
}

/*
 Function: printdiagonal

 Purpose: prints a diagonal payline for a reel at a given offset.
*/
void reel::printdiagonal(int offset ) const
{
 int shifted_payline = (payline + offset) % num_reel_sym;
 
 if( shifted_payline < 0 )
   shifted_payline += num_reel_sym;

 sym_ptr[shifted_payline].sprint();

}

/*
 Function: print
 
 Purpose: prints the symbol at the given index on the reel.
*/
void reel::print(int i) const
{
 sym_ptr[i].sprint();
}

/*
 Function: fprint

 Purpose: writes symbol at index to output file.
*/
void reel::fprint(int i, ofstream& fout )
{
 fout << setw(7) << left << sym_ptr[i].getname() << ' ';
 fout << setw(2) << left << sym_ptr[i].getvalue() << ' ';
}

