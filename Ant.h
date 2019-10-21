/*
 * Ant.h
 *
 *  Created on: Feb 10, 2019
 *      Author: Katie Lin & Connor Bruneau
 */

#ifndef ANT_H_
#define ANT_H_

#include "Organism.h"

class Ant: public Organism {

public:
	Ant();
	Ant(int r=0, int c = 0);
	//bool move(Grid* current);
	bool breed(Grid* current);
	 ~Ant();
};

#endif /* ANT_H_ */
