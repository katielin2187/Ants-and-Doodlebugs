/*
 * Production.h
 *
 *  Created on: Feb 7, 2019
 *      Author: Katie Lin & Connor Bruneau
 */

#ifndef PRODUCTION_H_
#define PRODUCTION_H_
#include "Grid.h"

class Production {
private:
	int timestepsLeft=1000;
	int timesRun = 0;
	int gridSize = 20;
	int doodlebugs = 5;
	int ants = 100;
	int seed = 1;
	int pause = 0;
	Grid* board;
	int newAnts = 0;
	int newDoodlebugs = 0;
	int remainingAnts = 0;
	int remainingDoodlebugs = 0;

public:
	Production(int argc, char* argv[]);
	bool runProduction();
	virtual ~Production();
	void playOne();
};

#endif /* PRODUCTION_H_ */
