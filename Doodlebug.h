/*
 * Doodlebug.h
 *
 *  Created on: Feb 10, 2019
 *      Author: Katie Lin & Connor Bruneau
 */

#ifndef DOODLEBUG_H_
#define DOODLEBUG_H_

#include "Organism.h"

class Doodlebug: public Organism {
private:
	int starveCount = 0;
public:
	Doodlebug(int r, int c);
	int getStarveCount();
	void setStarveCount(int count);
	bool move(Grid* current);
	bool breed(Grid* current);
	bool eat(Grid* current);
	bool starve();
	virtual ~Doodlebug();
};

#endif /* DOODLEBUG_H_ */
