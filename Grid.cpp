/*
 * Grid.cpp
 *
 *  Created on: Feb 9, 2019
 *      Author: Katie Lin & Connor Bruneau
 */

#include <iostream>
#include <iomanip>
#include "Grid.h"
#include "Cell.h"
#include "Organism.h"
#include "Ant.h"
#include "Doodlebug.h"

using std::cout;
using std::endl;

//int n=0; //this initial value will be changed when the program is invoked
//Cell** myGridCells_ptr_array = (Cell**)nullptr;

/**
 * Function is the default constructor for a Grid object that instantiates a Grid object with the
 *  default grid value set to 10..
 */
Grid::Grid() {
	// TODO Auto-generated constructor stub
	Grid(10); //calls general constructor with default value
}

/**
 * Function is another constructor for a Grid object that instantiates a grid object and
 * sets the size of the grid, n, to the given parameter nSquaresOnSide, and allocates
 * a array of pointers with n amount of row pointers and allocates memory for n amount
 * of columns in each row.
 *
 * @param nSquaresOnASide The number of rows and columns on each side of the newly created grid.
 */
Grid::Grid(int nSquaresOnASide)
{
	n = nSquaresOnASide; //initialize size of grid
	//we do not want automatic storage for the grid

	myGridCells_ptr_array = new Cell* [n];  //first allocate array of row pointers

	for(int i=0 ; i < n ; i++)
	{
		myGridCells_ptr_array[i] = new Cell[n]; // allocate memory for columns in each row
	}
}

/**
 * Function sets the occupant status in the given location of the passed in row and column.
 *
 * @param r The row that the occupant status must be changed.
 * @param c The column that the occupant status must be changed.
 * @param g The occupant status that the cell would be set to.
 * @return myGridCells_ptr_array[r][c].setOccupant(g) A boolean value that returns true if you
 * were able to set the occupant and false if you were unable to set the occupant.
 */
bool Grid::setCellOccupant(int r, int c, occupationStatus g)
{
	return myGridCells_ptr_array[r][c].setOccupant(g);
}

/**
 * Function retrieves the occupant status in the given location of the passed in row and column.
 *
 * @param r The row that the occupant status must be retrieved.
 * @param c The column that the occupant status must be retrieved.
 * @return myGridCells_ptr_array[r][c].getOccupant() An enum that indicates the current occupation
 * status of the cell. If cell is off the edge of the grid, returns unavailable.
 */
occupationStatus Grid::getCellOccupant(int r, int c)
{
	if (r < 0 || c < 0 || r >= n || c >= n) { // Outside the grid?
		return unavailable;
	}

	return myGridCells_ptr_array[r][c].getOccupant();
}

/////////////////////////

Cell Grid::getCell(int r, int c)
{
	return myGridCells_ptr_array[r][c];
}


///////////////////////////

/**
 * Function sets the current organism in the given location of the passed in row and column.
 *
 * @param r The row that the organism must be changed.
 * @param c The column that the organism must be changed.
 * @param g The pointer to the organism that needs to be set.
 * @return myGridCells_ptr_array[r][c].setOccupant(g) A boolean value that returns true if you
 * were able to set the occupant and false if you were unable to set the occupant.
 */
void Grid::setCellOrganism(int r, int c, Organism* g)
{
	myGridCells_ptr_array[r][c].setCurrentOrganism(g);
}

/**
 * Function retrieves the current organism in the given location of the passed in row and column.
 *
 * @param r The row that the occupant organism must be retrieved.
 * @param c The column that the occupant organism must be retrieved.
 * @return myGridCells_ptr_array[r][c].getCurrentOrganism() A Organism pointer value that indicates
 * the current organism in the cell.
 */
Organism* Grid::getCellOrganism(int r, int c)
{
	return myGridCells_ptr_array[r][c].getCurrentOrganism();
}


/**
 * Returns a pointer to an array of occupation statuses that represents the occupied status for the
 * positions North , South, East, West specifically in that order.
 *
 * @param r The row of the cell whose neighbors we check.
 * @param c The column of the cell whose neighbors we check.
 * @returns values An array of boolean values that determines if the cells north, south, east, and
 * west are occupied.
 */
occupationStatus* Grid::checkNeighbors(int r, int c)
{
	occupationStatus* neighbors = new occupationStatus[4];

	neighbors[0] = getCellOccupant(r-1, c); //North
	neighbors[1] = getCellOccupant(r+1, c); //South
	neighbors[2] = getCellOccupant(r, c+1); //East
	neighbors[3] = getCellOccupant(r, c-1); //West

	return neighbors;
}


/**
 * Returns a pointer to an array of boolean values that indicates whether or not the cell
 * occupant is and ant(food).
 *
 * @param r The row of the cell whose neighbors we check if they are ants(food).
 * @param c The column of the cell whose neighbors we check if they are ants(food).
 * @return isAnt A array of boolean values indicating if the neighbors is food. true i
 * s food, and false is not food.
 */
bool* Grid::findFood(int r, int c)
{
	occupationStatus* neighbors = checkNeighbors(r,c);
	bool* isAnt = new bool[4];

	for(int i=0; i<4; i++){
		if(neighbors[i] == ant){
			isAnt[i]= true;
		} else{
			isAnt[i]= false;
		}
	}

	return isAnt;
}

/**
 * Returns a pointer to an array of boolean values that indicates whether or not the cell
 * occupant is empty.
 *
 * @param r The row of the cell whose neighbors we check if they are empty.
 * @param c The column of the cell whose neighbors we check if they are empty.
 * @return isEmpty A array of boolean values indicating if the neighbors is empty. true
 * is empty, and false is not empty.
 */
bool* Grid::findMove(int r, int c)
{
	occupationStatus* neighbors = checkNeighbors(r,c);
	bool* isEmpty = new bool[4];

	for(int i=0; i<4; i++){
		if(neighbors[i] == empty){
			isEmpty[i]= true;
		} else{
			isEmpty[i]= false;
		}
	}

	return isEmpty;
}

/**
 * Functions moves the organism from one cell to another cell.
 *
 * @param r_old The current row of the cell that will be moved.
 * @param c_old The current column of the cell that will be moved.
 * @param r_new The new row of the cell that will move to.
 * @param c_new The new column of the cell that will move to.
 */
void Grid::moveOrganism(int r_old, int c_old, int r_new, int c_new)
{
	//set new status
	occupationStatus oldStatus = getCellOccupant(r_old, c_old);
	setCellOccupant(r_new, c_new, oldStatus);

	//set new occupant
	Organism* currentOccupant = myGridCells_ptr_array[r_old][c_old].getCurrentOrganism();
	currentOccupant->setColumn(c_new);  //set the new row and column
	currentOccupant->setRow(r_new);
	myGridCells_ptr_array[r_new][c_new].setCurrentOrganism(currentOccupant);

	//set old organism
	myGridCells_ptr_array[r_old][c_old].setCurrentOrganism(NULL);
	//set old status
	setCellOccupant(r_old, c_old, empty);

	//cout<< "Old Organism:" << myGridCells_ptr_array[r_old][c_old].getCurrentOrganism() <<endl;
	//cout << "Old status:" << getCellOccupant(r_old, c_old) << endl;

	//cout<< "New Organism:" << myGridCells_ptr_array[r_new][c_new].getCurrentOrganism() <<endl;
	//cout << "New status:" << getCellOccupant(r_new, c_new) << endl;
}

/**
 * Prints out the grid for one play.
 */
void Grid::printGrid()
{

	for(int r=0; r < n; r++)
	{
		for(int c=0; c < n; c++)
		{
			myGridCells_ptr_array[r][c].printCell(); // prints the cell occupant
		}
		printf("\n");
	}
}

/**
 * Function deletes the organism in the location of the passed in parameters, r, and c.
 *
 * @param r The row of the cell whose organism is to be deleted.
 * @param c The column of the cell whose organism is to be deleted.
 */
void Grid::deleteOrganism(int r, int c){
	occupationStatus status = getCellOccupant(r, c);
	if((status == empty) || (status == unavailable)){
		printf("Cannot delete organism.\n");
	} else{
		Organism* temp = myGridCells_ptr_array[r][c].getCurrentOrganism();
		//myGridCells_ptr_array[r][c].setCurrentOrganism(NULL);
		delete temp;
		myGridCells_ptr_array[r][c].setOccupant(empty);
		myGridCells_ptr_array[r][c].setCurrentOrganism(NULL);

		//setCellOccupant(r, c, empty);
	}


}


/**
 * Function creates a new organism, an ant or a doodlebug depending on the type of the
 * mother organism, in the place of the given row and column.
 *
 * @param r The row of the cell whose organism is to be deleted.
 * @param c The column of the cell whose organism is to be deleted.
 * @param mother The organism of the original cell that the new cell will take after of.
 */
bool Grid::createOrganism(int r, int c, Organism* mother){
	bool canCreate= true;

	if(this->getCellOccupant(r, c) == unavailable){
		canCreate = false;
	}
	if(mother->isPrey()==true){
		Ant* newAnt = new Ant(r, c);
		myGridCells_ptr_array[r][c].setCurrentOrganism(newAnt);
		myGridCells_ptr_array[r][c].setOccupant(ant);

	}
	else{
		Doodlebug* newDoodle = new Doodlebug(r, c);
		myGridCells_ptr_array[r][c].setCurrentOrganism(newDoodle);
		myGridCells_ptr_array[r][c].setOccupant(doodlebug);
	}
	return canCreate;
}


/**
 * Function is a destructor that takes the Grid object and deletes it once the program is done using the
 * object.
 */
Grid::~Grid() {

	for(int r=0; r < n; r++)
	{
		for(int c=0; c < n; c++)
		{
			//cout << "Before freeing" << r << c << endl;
			myGridCells_ptr_array[r][c].~Cell(); // free memory for columns in each row
		}
	}
	//myGridCells_ptr_array = (Cell**)nullptr;
}

