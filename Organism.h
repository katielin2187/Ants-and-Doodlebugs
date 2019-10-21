/*
 * Organism.h
 *
 *  Created on: Feb 7, 2019
 *      Author: Katie Lin & Connor Bruneau
 */

#ifndef ORGANISM_H_
#define ORGANISM_H_

#include "Grid.h"

class Organism {
protected:
	int row = 0;
	int col = 0;
	int stepCount = 0;
	bool amAnt = false;
	bool processed = false;
public:
	Organism();
	Organism(int r, int c);
	Organism(bool b);
	bool isPrey();
	virtual bool move(Grid* current);
	virtual bool breed(Grid* current)=0;
	virtual bool eat(Grid* current);
	virtual bool starve();
	void setAmAnt(bool b);
	int getStepCount();
	void setStepCount(int s);
	void setColumn(int c);
	void setRow(int r);
	int getRow();
	int getColumn();
	bool getProcessed();
	void setProcessed(bool setProcessed);
	virtual ~Organism();
};

#endif /* ORGANISM_H_ */
