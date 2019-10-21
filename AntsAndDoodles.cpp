//============================================================================
// Name        : Ants.cpp
// Author      : Katie Lin & Connor Bruneau building on Therese building on Ciaraldi
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Tests2.h"
#include "Production.h"
class Tests;
class Production;

/**
 *The main function that calls production and checks to see if it is working properly.
 *
 *@param argc Number of words on the command line
 *@param argv Array of pointers to character strings representing the words on the command line.
 * @return true if Program was able to play ants and doodle bugs
 *         false if something went wrong in the tests.
 */
int main(int argc, char* argv[])
{//gridSize #doodlebugs #ants #time_steps seed pause
	std::cout << "!!!Hello the classmates, it's time for fun with C++!!!" << std::endl;
    Tests2 ts = Tests2();//see page 291
    if(ts.doTests())
	{
		Production ps = Production(argc, argv);
		bool ok = ps.runProduction();
		if(ok)
		{
			puts("Production worked.");
		}
		else
		{
			puts("Production did not work.");
		}
		ps.~Production(); //done with production
	}
    ts.~Tests2(); //done with tests


	return 0;
}
