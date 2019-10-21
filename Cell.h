/*
 * Cell.h
 *
 *  Created on: Feb 9, 2019
 *      Author: Katie Lin & Connor Bruneau
 */

#ifndef CELL_H_
#define CELL_H_

enum occupationStatus { empty, ant, doodlebug, unavailable };

class Organism;

class Cell {
private:
	Organism* occupant;
	occupationStatus guest  = empty;
public:
	Cell();
	bool setOccupant(occupationStatus g);
	occupationStatus getOccupant();
	void printCell();;
	Organism* getCurrentOrganism();
	Organism* setCurrentOrganism(Organism* newOccupant);
	virtual ~Cell();
};

#endif /* CELL_H_ */
