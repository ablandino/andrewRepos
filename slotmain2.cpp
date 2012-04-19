/*/////////////////////////////////
 Program: slotsmain2.cpp

 Author: Andrew Blandino

 Date: 3-272-12

 Revisions: 8th (3-27-12)

 Purpose: use of classes to load symbols data file into array of class symbols.  Then
	  displays the class symbols to the screen.

*////////////////////////////////////
#include <ctime>
#include "symbol.h"
#include "string.h"

/*
 Function: getfilename

 Purpose: asks for file name, sets to char pointer.
*/
void getfilename( char* );

/*
 Function: readinsymbol

 Purpose: reads in a symbol name, value, and bonus.  Then sets the values
	  to the symbol class with the class member functions.
*/
void readinsymbol( symbol&, ifstream& );

/*
 Function: readrow

 Purpose: reads in a row of symbols in a file, storing them into an array of.
*/
void readrow( symbol*, ifstream&, int );

/*
 Function: menu

 Purpose: displays the menu asks for char input.
*/
void menu( char& );

int main()
{
 reel * reel_ptr = NULL;
 symbol * sym_ptr = NULL;
 char* fptr = new char[30];
 ifstream fin;
 ofstream fout;
 int num_sym, num_reel, num_reel_sym=10, i,j, offset, temp;
 bool good = true;
 char choice = 'a';
 srand(time(NULL));

 // ask for symbols file name
 getfilename(fptr);
 fin.clear();
 fin.open(fptr);
 fin >> num_sym;

 // allocate memory to list of symbols
 sym_ptr = new symbol[num_sym];
 for( i=0; i < num_sym; i++ )
   readinsymbol( sym_ptr[i], fin );

 fin.close();
 // loop for menu
 while( choice != 'Q' && choice != 'q' )
 {
  menu(choice);
  switch(choice)
   {
    // new machine case
    case 'N':
    case 'n':
	// if machine loaded, deallocate
	if( reel_ptr != NULL )
	{
	delete[] reel_ptr;
	reel_ptr = NULL;
	}
	
	// loop to get number of reels
	while(good)
	{
	cout<<"Enter number of reels (3,5,7): ";
        cin>> num_reel;
	if( !( num_reel == 3 || num_reel == 5 || num_reel == 7 ) )
	 cout<<"Enter 3, 5, or 7 for number of reels."<<endl;	  
	else
	  good= false;
	}
	good= true;
	
	// allocate memory to reels
	reel_ptr = new reel[num_reel];
	// randomly populate reels	
	for(  i=0; i< num_reel; i++ )
	  reel_ptr[i].setreel( sym_ptr,num_sym,true,0,0 );
	
	getfilename(fptr);
	fout.open(fptr);
	fout << num_reel << ' ';
	fout << num_reel_sym << endl;

	// display reels to screen, and write to file
	for( i=0; i<num_reel_sym; i++ )
	{
	 for( j =0; j<num_reel; j++ )
	 {
	 reel_ptr[j].print(i);
	 reel_ptr[j].fprint(i,fout);
	 }
	cout<< endl;
	fout<<endl;
	}
	fout.close();
      break;

    // previous machine case
    case 'P':
    case 'p':
	// deallocate machine if one loaded
	if( reel_ptr != NULL )
	{
	delete[] reel_ptr;
	reel_ptr = NULL;
	}
	
	getfilename(fptr);
	fin.open( fptr );

	// if file open good, then load previous machine
	if( fin.good() )
	{
	 fin >> num_reel;
	 fin >> num_reel_sym;

	 // allocate memory to reels.
	 reel_ptr = new reel[num_reel];
	 symbol * list = NULL;

	 // loop to read in symbols, then copy to reels
	 for( i=0; i< num_reel_sym; i++ )
	 {
	 list = new symbol[num_reel];
	 readrow( list, fin, num_reel );
	  for( j=0; j< num_reel; j++ )
	  {
	  reel_ptr[j].setreel( list,num_sym,false, i, j );
	  }
	 delete[] list;
	 list = NULL;
	 }

	fin.close();

	// loop to display reels
	 for( i=0; i<num_reel_sym; i++ )
	 {
	  for( j =0; j<num_reel; j++ )
	  {
	  reel_ptr[j].print(i);
	  }
	 cout<< endl;
	 } 
	
	}

	// if bad file open, error msg
	else
	  cout << "Not valid file" << endl;
      break;

    // spin reels
    case 'S':
    case 's':

	// spin reels only if machine loaded
	if( reel_ptr != NULL )
	{
 	  cout<< "Reel paylines displayed horizontally" << endl;
	  // loop to display main paylines
	  for( i=0; i< num_reel; i++ )
	  {
	   reel_ptr[i].spinreel( num_reel );
	  }
	cout << endl;

 	cout << "Diagonal Paylines" << endl;
	
	// loop twice to display both diagonal paylines
	offset = -(num_reel / 2 );
	temp = offset;
	for( i=0; i<num_reel; i++ )
	{
	 reel_ptr[i].printdiagonal(offset);
	 offset++;
	}
	cout << endl;
	offset = temp;

	for( i=num_reel-1; i>-1; i-- )
	{
	 reel_ptr[i].printdiagonal(offset);
	 offset++;
	}
	cout << endl;

	}

	// otherwise error if no machine loaded.
	else
	  cout << "Must load machine first."<<endl<<endl;
      break;

    // display list of symbols in use
    case 'L':
    case 'l':
	for( i=0; i<num_sym; i++ )
	{
	 sym_ptr[i].sprint();
	 cout << endl;
	}
      break;
   }
 }

 return 0;
}

void getfilename( char* c_ptr )
{
 cout << "enter file name:" << endl;
 cin >> c_ptr;
}

void readrow( symbol* s_ptr, ifstream& fin, int num_reel)
{
 for( int i=0; i<num_reel; i++ )
   readinsymbol(s_ptr[i], fin );

}

void readinsymbol( symbol& s_ptr, ifstream& fin )
{
 char * tmp = new char[30];
 int len, val; 
 bool status;
 bool v_bonus;

 fin >> tmp;
 len = strlen( tmp );
 s_ptr.setname(tmp, len);

 fin >> val;
 s_ptr.setvalue( val );

 if( val == 0 )
   v_bonus = false;
 else
   v_bonus = true;

 s_ptr.setbonus( v_bonus );
 delete[] tmp;
}

void menu( char& choice )
{
 cout<<"--- Menu ---"<<endl;
 cout<<"[N]ew Machine"<<endl;
 cout<<"[P]revious Machine "<<endl;
 cout<<"[S]pin Reels "<<endl;
 cout<<"[L]ist Reels "<<endl;
 cout<<"[Q]uit "<<endl;
 cout<<"------------"<<endl;

 cin >> choice;
}

