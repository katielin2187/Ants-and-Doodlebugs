/*
 * Cell.cpp
 *
 *  Created on: Feb 9, 2019
 *      Author: Katie Lin & Connor Bruneau
 */

#include "Cell.h"
#include <stdio.h>



/**
 * Function is the default constructor for a Cell object that instantiates a Cell object
 * with an empty guest.
 */
Cell::Cell() {
	occupant = NULL;
	guest = empty;
}

/**
 * Function is a constructor for a cell object that instantiates a cell object and sets the occupancy
 * status to the passed in parameter, g, and returns the result.
 * @return result A boolean value that indicates true if the occupant status has been set
 * 												and false if the status has not been set because the Cell was occupied.
 */
bool Cell::setOccupant(occupationStatus g)
{
	bool result = true;

	// Only allow setting an empty cell non-empty.
	// But set any cell empty when asked.
	if(guest==empty || g == empty)
	{
		guest = g;
	}
	else
	{
		result = false;
	}
	return result;
}

/**
 * Function that returns the Cell's occupancy status.
 *
 * @return guest A value that indicates the occupancy status of a cell.
 */
occupationStatus Cell::getOccupant()
{
	return guest;
}


/**
 * Function that returns the Cell's occupant.
 *
 * @return occupant The current occupant of a cell.
 */
Organism* Cell::getCurrentOrganism()
{
	return this->occupant;
}

/**
 * Function that sets the Cell's occupant.
 *
 * @param newOccupant A pointer to an organism object that the cell's organism will be set to.
 * @return occupant The new occupant of a cell.
 */
Organism* Cell::setCurrentOrganism(Organism* newOccupant)
{
	this->occupant = newOccupant;

	return occupant;
}

/**
 * Function that prints a character representing the current occupation status of the cell.
 * If the occupation status is ant, this function prints 'o'
 * If the occupation status is a doodlebug, this function prints 'x'
 * If the occupation status is empty, this function prints ' '
 */
void Cell::printCell()
{
	if(guest == empty){
		printf("%c", '-');
	}

	if(guest == ant){
		printf("%c", 'o');
	}

	if(guest == doodlebug){
		printf("%c", 'x');
	}

}

/**
 * Function is a destructor that takes the Cell object and deletes it once the program is done using the
 * object.
 */
Cell::~Cell() {
	// TODO Auto-generated destructor stub
}

