slot.out:	symbol.o slotmain2.o string.o
		g++ -o slot.out symbol.o slotmain2.o string.o

symbol.o:	symbol.cpp symbol.h
		g++ -c symbol.cpp

string.o:	string.cpp string.h
		g++ -c string.cpp

slotmain2.o:	slotmain2.cpp symbol.cpp symbol.h string.h string.cpp 
		g++ -c slotmain2.cpp

clean:
		rm *.o symbol.out
