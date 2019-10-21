/*
 * Organism.cpp
 *
 *  Created on: Feb 7, 2019
 *      Author: Katie Lin & Connor Bruneau
 */

#include "Organism.h"
#include "Grid.h"
#include <stdlib.h>
#include <stdio.h>


/**
 * Function is the default constructor for an organism object that instantiates an
 * Organism object.
 */
Organism::Organism() {
	// TODO Auto-generated constructor stub

}

/**
 * Function is another constructor for an organism object that instantiates an Organism
 * object with r rows and c columns.
 *
 * @param r The row that the organism will be instantiated in.
 * @param c The column that the organism will be instantiated in.
 */
Organism::Organism(int r, int c) {
	// TODO Auto-generated constructor stub
	row = r;
	col = c;
	stepCount = 0;

}

/**
 * Function is another constructor for an organism object that instantiates an Organism object and
 * sets the boolean value amAnt to the passes in param b.
 *
 * @param b A boolean value indicating whether an organism is an ant or not.
 */
Organism::Organism(bool b) {
	amAnt = b;

}


/**
 * Functions tells whether if the organism can move or not, and then moves it accordingly.
 *
 * @param current A pointer to the current board that the game is being played on.
 * @return status A boolean value that indicates true if an ant can move
 * 											 and false if the ant cannot move.
 */
bool Organism::move(Grid* current)
{
	bool status = false;
	int optionCount = 0;
	int j= 0;
	char* direction = new char[4];
	//char* beginDirection = direction; //point to first elt of direction
	//row and column of organism to move
	int r = this->row;
	int c = this->col;
	//establish and array of booleans showing which directions are free to move
	bool* moveOptions = current->findMove(r, c);

	for(int i = 0; i<4; i++){
		//if there is an available space, status  is true
		if((moveOptions[i]) == true) {
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

	printf(" Move status: %s\n", status ? "true" : "false");

	//if status == true call moveOrganism
	if(optionCount>0){
		status = true;
		int randomChoice = rand()%optionCount;  //randomly select an item in direction array to move in
		char result = direction[randomChoice];
		//manually extract direction, move in that direction
		if(result=='N'){
			current->moveOrganism(r, c, r-1, c); //North
		} else if(result=='S'){
			current->moveOrganism(r, c, r+1, c); //South
		} else if(result=='E'){
			current->moveOrganism(r, c, r, c+1); //East
		} else if (result=='W'){
			current->moveOrganism(r, c, r, c-1); //West
		}

	}

	return status;
}


/**
 * Function tells whether an organism is a prey.
 *
 * @return status A boolean value that indicates true if an organism is prey
 * 											 and false if the organism is not prey.
 */
bool Organism::isPrey()
{
	return amAnt;
}


/**
 * Function returns the current stepCount of the organism.
 *
 * @return stepCount A number of steps that the organism has survived for.
 */
int Organism::getStepCount(){
	return stepCount;
}


/**
 * Function sets the current stepCount of the organism.
 *
 * @param s The given number of steps that the organism has survived for.
 */
void Organism::setStepCount(int s){
	stepCount = s;
}


/**
 * Function tells whether an organism is a prey.
 *
 * @return false This boolean value holds true for all organism unless ovverrided in child class.
 */
bool Organism::eat(Grid* current){
	return false;
}

/**
 * Returns whether or not the organism has starved.
 *
 * @return false This boolean value holds true for all organisms, unless overrided in child class.
 */
bool Organism::starve()
{
	return false;
}

/**
 * Function sets the organism as an ant.
 */
void Organism::setAmAnt(bool b)
{
	amAnt = b;
}


/**
 * Function returns the current row of the organism.
 *
 * @return row The current row that the organism is in.
 */
int Organism::getRow(){
	return row;
}


/**
 * Function sets the current row of the organism.
 *
 * @param r The given row that the organism will be in.
 */
void Organism::setRow(int r){
	row = r;
}

/**
 * Function returns the current row of the organism.
 *
 * @return row The current row that the organism is in.
 */
int Organism::getColumn(){
	return col;
}


/**
 * Function sets the current row of the organism.
 *
 * @param r The given row that the organism will be in.
 */
void Organism::setColumn(int c){
	col = c;
}


/**
 * Function returns the processed status of the organism.
 *
 * @return row The current processed status of the organism.
 */
bool Organism::getProcessed(){
	return processed;
}


/**
 * Function sets the current processed status of the organism.
 *
 * @param setProcessed A boolean value indicating what the processed status should be set to.
 */
void Organism::setProcessed(bool setProcessed){
	processed = setProcessed;
}



/**
 * Function is a destructor that takes the Organism object and deletes it once the program is done using the
 * object.
 */
Organism::~Organism() {
	// TODO Auto-generated destructor stub
}

