/*
 * Production.cpp
 *
 *  Created on: Feb 7, 2019
 *      Author: Katie Lin & Connor Bruneau
 */

#include "Production.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Grid.h"
#include "Organism.h"
#include "Ant.h"
#include "Doodlebug.h"

using std::cout;
using std::endl;



//keep as global variables?

/**
 * Function is the default constructor for a production object that instantiates Production object,
 * and sets the timestepsleft to 100.
 * @param argc Number of words on the command line
 * @param argv Array of pointers to character strings representing the words on the command line.
 */
Production::Production(int argc, char* argv[]) {
	// TODO Auto-generated constructor stub

	char* endptr;

	if(argc<2){
		printf("No arguments entered, assuming defaults \n");
		timestepsLeft = 1000; //initialize available timesteps
	}
	else if(argc==2) {
		gridSize = strtol(argv[1], &endptr, 10);
		timestepsLeft = 1000; //initialize available timesteps

	}
	else if (argc == 3){
		gridSize = strtol(argv[1], &endptr, 10);
		doodlebugs = strtol(argv[2], &endptr, 10);
		timestepsLeft = 1000; //initialize available timesteps
	}

	else if(argc == 4){
		gridSize = strtol(argv[1], &endptr, 10);
		doodlebugs = strtol(argv[2], &endptr, 10);
		ants = strtol(argv[3], &endptr, 10);
		timestepsLeft = 1000; //initialize available timesteps
	}

	else if (argc == 5){
		gridSize = strtol(argv[1], &endptr, 10);
		doodlebugs = strtol(argv[2], &endptr, 10);
		ants = strtol(argv[3], &endptr, 10);
		timestepsLeft= strtol(argv[4], &endptr, 10); //initialize available timesteps
	}

	else if(argc == 6){
		gridSize = strtol(argv[1], &endptr, 10);
		doodlebugs = strtol(argv[2], &endptr, 10);
		ants = strtol(argv[3], &endptr, 10);
		timestepsLeft= strtol(argv[4], &endptr, 10);
		seed = strtol(argv[5], &endptr, 10);

	}

	else if (argc == 7){
		gridSize = strtol(argv[1], &endptr, 10);
		doodlebugs = strtol(argv[2], &endptr, 10);
		ants = strtol(argv[3], &endptr, 10);
		timestepsLeft= strtol(argv[4], &endptr, 10);
		seed = strtol(argv[5], &endptr, 10);
		pause = strtol(argv[6], &endptr, 10);

	}

	//Create Playing Board
	board = new Grid(gridSize);
	srand(seed);

	//set status to empty first, organism to null
	for(int r = 0; r<gridSize; r++){
		for(int c = 0; c<gridSize; c++){
			board->setCellOccupant(r, c, empty);
			board->setCellOrganism(r, c, NULL);
		}
	}

	//place all ants
	for(int i = 0; i<ants;i++){
		bool antPlaced = false;
		//place ant
		do{
			int r = rand()%(gridSize);
			int c = rand()%(gridSize);
			if(board->getCellOccupant(r, c)==empty){
				Ant* boardAnt = new Ant(r, c);
				board->setCellOccupant(r, c, ant);
				board->setCellOrganism(r,c,boardAnt);
				antPlaced = true;
			}
		}while(antPlaced == false);
	}

	//place all doodlebugs
	for(int i = 0; i<doodlebugs;i++){
		bool doodlePlaced = false;
		//place doodblebug
		do{
			int r = rand()%(gridSize);
			int c = rand()%(gridSize);
			if(board->getCellOccupant(r, c)==empty){
				Doodlebug* boardDoodle = new Doodlebug(r, c);
				board->setCellOccupant(r, c, doodlebug);
				board->setCellOrganism(r,c,boardDoodle);
				doodlePlaced = true;
			}
		}while(doodlePlaced == false);
	}

	//Print Grid with all Items
	printf("Initial Board \n");
	board->printGrid();


}
/**
 * Runs through one iteration of the game.
 */
void Production::playOne(){
	//process all Doodlebugs
	printf("\nProcess Doodlebugs:\n");
	for(int r = 0; r<gridSize; r++){
		for(int c = 0; c<gridSize; c++){
			//printf("hellooo %d %d %d",r, c, board->getCellOccupant(r,c));
			if((board->getCellOccupant(r,c)==doodlebug) && (board->getCellOrganism(r,c)->getProcessed()==false)){
				board->getCellOrganism(r,c)->setProcessed(true); //set the processed status
				printf("Doodle: (%d, %d)\n", r, c);
				Organism* org = board->getCellOrganism(r, c);
				org->move(board);
				// check for starve
				if(org->starve()==false){
					bool hadBred = org->breed(board); // If did not starve, will it breed?
					if(hadBred == true){
						newDoodlebugs++;
					}
				} else if (org->starve()==true){
					board->deleteOrganism(r, c); //if the doodlebug is starving, delete it!
				}
			}
		}
	}
	printf("\nProcess Ants:\n");
	// Process all Ants
	for(int r = 0; r<gridSize; r++){
		for(int c = 0; c<gridSize; c++){
			if((board->getCellOccupant(r,c)==ant) && (board->getCellOrganism(r,c)->getProcessed()==false)){
				board->getCellOrganism(r,c)->setProcessed(true); //set the processed status
				printf("Ant: (%d,%d)\n",r,c);
				Organism* org = board->getCellOrganism(r, c);
				org->move(board);
				bool hadBred = org->breed(board);
				if(hadBred == true){
					newAnts++;
				}
			}
		}
	}

	// Set the step counts for all, and resets all of the processed statuses to false
	for(int r = 0; r<gridSize; r++){
		for(int c = 0; c<gridSize; c++){
			if(board->getCellOccupant(r,c)==ant){
				board->getCellOrganism(r, c)->setStepCount((board->getCellOrganism(r, c)->getStepCount())+1);
				board->getCellOrganism(r,c)->setProcessed(false); //set the processed status
			}
			else if(board->getCellOccupant(r,c)==doodlebug){
				board->getCellOrganism(r, c)->setStepCount((board->getCellOrganism(r, c)->getStepCount())+1);
				board->getCellOrganism(r,c)->setProcessed(false); //set the processed status
			}
		}
	}

	timesRun++; //increment the timees run
}

/**
 * Function that runs the production while there are still time steps left.
 *
 * @return result A boolean value true if the production was able to run successfully, and false
 * 					if the production was not able to run successfully.
 */
bool Production::runProduction()
{
	bool result = true;
	while(timestepsLeft-- > 0)
	{
		if(pause!=0){
			if((timesRun)%pause == 0){
				printf(" \nCurrent Board: \n");
				board->printGrid();
				printf("Please enter a character to continue...");
				getchar();
			}
		}
		//printf("Rounds Left: %d\n", timestepsLeft);

		//dbs.step;
		//ants.step;

		//could call playOne
		playOne();

	}

	// count all the remaining ants and doodlebugs
	for(int r = 0; r<gridSize; r++){
		for(int c = 0; c<gridSize; c++){
			if(board->getCellOccupant(r,c)==ant){
				remainingAnts++;
			}
			else if(board->getCellOccupant(r,c)==doodlebug){
				remainingDoodlebugs++;
			}
		}
	}

	//simulation summary
	printf("Simulation Summary:\n\n");
	cout << "Command line: \n";
	cout << "  Grid size:" << gridSize << endl;
	cout << "  Doodlebugs:" << doodlebugs << endl;
	cout << "  Ants:" << ants << endl;
	cout << "  Time steps left:" << timestepsLeft << endl;
	cout << "  Seed:" << seed << endl;
	cout << "  Pause:" << pause << endl;

	cout << "Number of steps simulated:" << timesRun << endl;

	cout << "Total Ants: " << ants + newAnts << ", Remaining Ants: " << remainingAnts <<endl;
	cout << "Total Doodlebugs: " << doodlebugs + newDoodlebugs << ", Remaining Doodlebugs: " << remainingDoodlebugs <<endl;

	cout<< "Final Grid: \n";
	board->printGrid();


	return result;
}

/**
 * Function is a destructor that takes the production object and deletes it once the program is done using the
 * object.
 */
Production::~Production() {
	// TODO Auto-generated destructor stub
}

