#include "string.h"

void strcpy( char* destination, const char* source )
{
 int i = 0;

 while( source[i] != '\0' )
 {
  destination[i] = source[i];
  i++;
 }
 destination[i] = source[i];
}

int strlen( const char* source )
{
 int i = 0;

 while( source[i] != '\0' )
   i++;

 return i;
}

bool strcmp( const char* destination, const char* source )
{
  int i =0;
  while( source[i] != '\0' && destination[i] != '\0' )
  {
   if( source[i] != destination[i] )
    return false;  
   i++;
  }
 
 if( source[i] == destination[i] )
  return true;
 else
  return false;
}
