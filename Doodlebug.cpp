/*
 * Doodlebug.cpp
 *
 *  Created on: Feb 10, 2019
 *      Author: Katie Lin & Connor Bruneau
 */

#include "Doodlebug.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * Function is the default constructor for a Doodlebug object that instantiates a Doodlebug object.
 *
 * @param r The row that the doodlebug will be instantiated on.
 * @param c The column that the doodlebug will be instantiated on.
 */
Doodlebug::Doodlebug(int r, int c) {
	// TODO Auto-generated constructor stub

	row = r;
	col = c;
}

/**
 * Returns the Organism's current starveCount;
 */
int Doodlebug::getStarveCount()
{
	return this->starveCount;
}


/**
 * Sets the Organism's starveCount to the passed in parameter count;
 *
 * @param count The amount of plays that the doodlebug has been starving for.
 */
void Doodlebug::setStarveCount(int count)
{
	this->starveCount = count;
}

/**
 * Functions tells whether if the doodlebug will move or not.
 *
 * @param current A pointer to the current board that the game is being played on.
 * @return status A boolean value that indicates true if a doodlebug can move
 * 											 and false if the doodlebug cannot move.
 */
bool Doodlebug::move(Grid* current)
{
	bool status = true;
	//bool* foodOptions = current->findFood(this->row, this->col);

	status = eat(current);
	printf(" Eat status: %s\n", status ? "true" : "false");

	//if unable to eat, call Organism::move
	if(status == false){
		Organism::move(current);
		starveCount++;            //increment starve count cause doodlebug cannot eat ant
	} else{
		starveCount = 0;
	}

	return status;
}


/**
 * Functions tells whether if the doodlebug can breed or not.
 *
 * @param current A pointer to the current board that the game is being played on.
 * @return status A boolean value that indicates true if a doodlebug can breed
 * 											 and false if the doodlebug cannot breed.
 */
bool Doodlebug::breed(Grid* current)
{
	bool status = false;
	int r = this->row;
	int c = this->col;
	int optionCount = 0;
	int j= 0;


	if(this->stepCount>=8){
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

			printf(" Breed status: %s\n", status ? "true" : "false");

		}
		//if status == true call moveOrganism
		if(optionCount>0){
			status = true;
			int randomChoice = rand()%optionCount;  //randomly select an item in direction array to move in
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

			stepCount = 0; // Reset becuase  this Organism has bred.
		}


	}



	return status;
}

/**
 * Functions tells whether if the doodlebug can eat or not.
 *
 * @param current A pointer to the current board that the game is being played on.
 * @return status A boolean value that indicates true if a doodlebug can eat
 * 											 and false if the doodlebug cannot eat.
 */
bool Doodlebug::eat(Grid* current)
{
	bool status = false;
	int optionCount = 0;
	int j= 0;
	char* direction = new char[4];
	//char* beginDirection = direction; //point to first elt of direction
	int r = this->row;
	int c = this->col;

	bool* foodOptions = current->findFood(r, c);

	for(int i = 0; i<4; i++){
		if((foodOptions[i]) == true) {
			status = true;
			optionCount++;

			if(i==0){
				direction[j] = 'N';
			} else if(i==1){
				direction[j] = 'S';
			} else if(i==2){
				direction[j] = 'E';
			} else if (i==3){
				direction[j] = 'W';
			}

			j++;
		}
	}

	//if status == true call moveOrganism
	if(optionCount>0){
		//status = true;
		int randomChoice = rand()%optionCount;  //randomly select an item in direction array to move in
		char result = direction[randomChoice];

		if(result=='N'){
			current->deleteOrganism(r-1, c);
			current->moveOrganism(r, c, r-1, c); //North
		} else if(result=='S'){
			current->deleteOrganism(r+1, c);
			current->moveOrganism(r, c, r+1, c); //South
		} else if(result=='E'){
			current->deleteOrganism(r, c+1);
			current->moveOrganism(r, c, r, c+1); //East
		} else if (result=='W'){
			current->deleteOrganism(r, c-1);
			current->moveOrganism(r, c, r, c-1); //West
		}
	}


	return status;
}

/**
 * Returns whether or not the Doodlebug has starved.
 */
bool Doodlebug::starve()
{
	bool starved = false;
	//check to see if doodle starved
	if(starveCount == 3){
		starved = true;
	}
	return starved;
}

/**
 * Function is a destructor that takes the Doodlebug object and deletes it once the program is done using the
 * object.
 */
Doodlebug::~Doodlebug() {
	// TODO Auto-generated destructor stub
}

