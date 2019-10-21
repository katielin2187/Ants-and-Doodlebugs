/*
 * Grid.h
 *
 *  Created on: Feb 9, 2019
 *      Author: Katie Lin & Connor Bruneau
 */

#ifndef GRID_H_
#define GRID_H_

#include "Cell.h"

class Grid {
private:
	int n=0; //this initial value will be changed when the program is invoked
	Cell** myGridCells_ptr_array = (Cell**)nullptr;
public:
	Grid();
	Grid(int nSquaresOnASide);
	bool setCellOccupant(int r, int c, occupationStatus g);
	occupationStatus getCellOccupant(int r, int c);
	occupationStatus* checkNeighbors(int r, int c);
	bool* findFood(int r, int c);
	bool* findMove(int r, int c);
	void moveOrganism(int r_old, int c_old, int r_new, int c_new);
	void setCellOrganism(int r, int c, Organism* g);
	Organism* getCellOrganism(int r, int c);
	Cell getCell(int r, int c);
	void printGrid();
	void deleteOrganism(int r, int c);
	bool createOrganism(int r, int c, Organism* mother);
	virtual ~Grid();
};

#endif /* GRID_H_ */
