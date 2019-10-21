/*
 * Ant.cpp
 *
 *  Created on: Feb 10, 2019
 *      Author: Katie Lin & Connor Bruneau
 */

#include "Ant.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * Function is the default constructor for an Ant object that instantiates an Ant object.
 */
Ant::Ant()
//:Organism(true)
{
}

/**
 * Function is another constructor for an Ant object that instantiates an Ant object and
 * sets the rows to the given parameter r, and sets the columns to the given parameter c.
 *
 * @param r The row that the ant will be instantiated on.
 * @param c The column that the ant will be instantiated on.
 */
Ant::Ant(int r, int c)
:Organism(true)
{
	row = r;
	col = c;
}



/**
 * Function tells whether if an ant will breed or not.
 *
 * @param current A pointer to the current board that the game is being played on.
 * @return status A boolean value that indicates true if an ant can breed
 * 											 and false if the ant cannot breed.
 */
bool Ant::breed(Grid* current)
{
	bool status = false;
	int r = this->row;
	int c = this->col;

	int optionCount = 0;
	int j= 0;

	if(this->stepCount>=3){
		bool* breedOptions = current->findMove(this->row, this->col);
		char* direction = new char[4];
		for(int i = 0; i<4; i++){
			if((breedOptions[i]) == true){
				status = true;
				//for every available space increase optionCount
				optionCount++;
				//based on position of boolean in moveOptions, save which directions are free in direction array
				if(i==0){
					direction[j] = 'N';
				} else if(i==1){
					direction[j] = 'S';
				} else if(i==2){
					direction[j] = 'E';
				} else if (i==3){
					direction[j] = 'W';
				}
				//increment where we put direction
				j++;
			}

		}
		printf(" Breed status: %s\n", status ? "true" : "false");
		//if status == true call moveOrganism
		if(optionCount>0){
			status = true;
			int randomChoice = rand()%optionCount; //randomly select an item in direction array to move in
			char result = direction[randomChoice];
			//manually extract direction, move in that direction
			if(result=='N'){
				current->createOrganism(r-1, c, this); //North
			} else if(result=='S'){
				current->createOrganism(r+1, c, this); //South
			} else if(result=='E'){
				current->createOrganism(r, c+1, this); //East
			} else if (result=='W'){
				current->createOrganism(r, c-1, this); //West
			}

			stepCount = 0;
		}


	}
	return status;
}

/**
 * Function is a destructor that takes the Ant object and deletes it once the program is done using the
 * object.
 */
Ant::~Ant() {
	// TODO Auto-generated destructor stub

}

