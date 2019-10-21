/*
 * Tests2.cpp
 *
 *  Created on: Feb 7, 2019
 *      Author: Katie Lin & Connor Bruneau
 */

#include "Tests2.h"
#include "Grid.h"
#include "Ant.h"
#include "Doodlebug.h"
#include "Cell.h"
#include "Organism.h"
#include "Production.h"
#include <iostream>

/**
 * Function is the default constructor for a test object that instantiates an test object.
 */
Tests2::Tests2() {
	// TODO Auto-generated constructor stub
	//initialize the grid
}

/**
 * Function calls all of the test functions and returns a boolean value that indicates
 * whether or not all the tests passed or not.
 *
 * @return results A boolean value that reads true if all of the tests passed and false if
 * any of the tests fail.
 */
bool Tests2::doTests()
{
	bool results;
	//////////////////////////////////////////////////////////////////////
	//----------------grid & cell
	printf("////////////////////Grid & Cell tests: \n");
	//establish a grid --done
	bool ok1 = gridTest();

	//see if cell occupant can be returned
	//see if cell organism can be returned
	//see if organism can be created
	//see if organism can be deleted
	//see if cell occupant can be set
	//see if cell organism can be set
	bool ok14 = cellOccupantOrganismTests();

	//return occupant statuses of neighbors
	bool ok11 = checkNeighborsTest();
	//see if any neighbors are ants(food)
	bool ok12 = findFoodTest();
	//see if there is space to move
	bool ok13 = findMoveTest();

	//see if organism can be moved
	bool ok15 = moveOrganismTest();
	//see if grid is printed right
	bool ok16 = printGridAndCellTest();



	///////////////////////////////////////////////////////////////////////
	/*//-------------------organism
	printf("////////////////////Organism tests: \n");
	//test to see if an organism (ant or doodle) can eat
	bool ok17 = eatTest();
	//test to see if an organism (ant or doodle) can move
	bool ok18 = movetest();
	//test to see if an organism is an ant
	bool ok29 = setAmAntTest();
	//test to see if an organism can set the stepcount
	bool ok20 = setStepCountTest();*/


	///////////////////////////////////////////////////////////////////////
	//-------------------ant
	printf("////////////////////Ant tests: \n");
	//populate it with ants -- done
	bool ok2 = makeAntsTest();
	//see whether they move --
	bool ok3 = antsMoveTest();
	//see whether they breed --
	bool ok4 = antsBreedTest();
	//see whether they die?, maybe if they wander off? --
	bool ok5 = antsDieTest();


	///////////////////////////////////////////////////////////////////////
	//---------------doodlebug
	printf("////////////////////Doodlebug tests: \n");
	//populate with doodlebugs --
	bool ok6 = makeDoodlesTest();
	//see whether they move --
	bool ok7 = doodleMoveTest();
	//see whether they breed --
	bool ok8 = doodleBreedTest();
	//see whether they eat ants --
	bool ok9 = doodleEatTest();
	//see whether they die --
	bool ok10 = doodleDietest();

	/////////////////////////////////////////////////////

	results = ok1 && ok2 && ok3 && ok4 && ok5 && ok6 && ok7 && ok8 && ok9
			&& ok10 && ok11 && ok12 && ok13 && ok14;
	// && ok15 && ok16 && ok17 &&ok18 &&ok19 && ok20

	printf("Done with tests.\nResults: %s", results ? "All tests passed\n" : "Something went wrong.\n");

	return results;
}


/**
 * Function calls the grid object and checks whether the grid was instantiated correctly
 * and if the grid sets the occupancy statuses correctly.
 *
 * @return results A boolean value that reads true if the the grid was able to set the cell occupancy
 * statuses correctly.
 */
bool Tests2::gridTest()
{
	bool result = true;
	bool ok1 = true;
	bool ok2 = true;
	std::cout << "Running the grid test" << std::endl;

	Grid myGrid = Grid(8);
	if(myGrid.getCellOccupant(2, 3)!=empty)
	{
		std::cout << "Cell not initially empty" << std::endl;
		ok1 = false;
	}
	//std::cout << "second grid test" << std::endl;
	myGrid.setCellOccupant(2, 3, ant);
	if(myGrid.getCellOccupant(2, 3)!=ant)
	{
		std::cout << "Cell not set to ant" << std::endl;
		ok2 = false;
	}
	//std::cout << "third grid test" << std::endl;
	myGrid.~Grid();
	result = ok1 && ok2;
	printf("Result: %s", result ? "gridTest passed\n" : "gridTest failed.\n");
	return result;
}


bool Tests2::cellOccupantOrganismTests()
{
	bool result = true;
	std::cout << "Running the cellOccupantOrganism test------------------" << std::endl;

	Grid* myGrid_p = new Grid(9);

	//1)see if organism can be created
	//2)see if cell occupant can be returned
	//3)see if cell organism can be returned
	//4)see if cell occupant can be set
	//5)see if cell organism can be set
	bool ok1a = true; //createOrganismTest();
	bool ok1b = true;
	bool ok2a = true; //getCellOccupantTest();
	bool ok2b = true;
	bool ok3a = true; //getCellOrganismTest();
	bool ok3b = true;
	bool ok4a = true; //setCellOccupantTest();
	bool ok4b = true;
	bool ok5a = true; //setCellOrgansimTest();
	bool ok5b = true;

	myGrid_p->setCellOccupant(2, 2, ant);
	Organism* a1 = new Ant(2,2);                   //ant is an organism
	myGrid_p->setCellOrganism(2,2, a1);

	occupationStatus antOcc = myGrid_p->getCellOccupant(2,2);
	Organism* antOrg = myGrid_p->getCellOrganism(2,2);

	if((antOcc==ant)&&(antOrg == a1)){
		std::cout << "Original Ant:" << a1 << std::endl;
		std::cout << "Occupation Status:" << antOcc <<  std::endl;
		std::cout << "Organism:" << antOrg << std::endl;
		printf("Ant Organism was created\n");
	} else{
		ok1a = false;
		ok2a = false;
		ok3a = false;
		ok4a = false;
		ok5a = false;
	}

	myGrid_p->setCellOccupant(3, 2, doodlebug);
	Organism* d1 = new Doodlebug(3,2);                   //doodlebug is an organism
	myGrid_p->setCellOrganism(3,2, d1);

	occupationStatus doodleOcc = myGrid_p->getCellOccupant(3,2);
	Organism* doodleOrg = myGrid_p->getCellOrganism(3,2);

	if((doodleOcc==doodlebug)&&(doodleOrg== d1)){
		std::cout << "Original Doodlebug:" << d1 << std::endl;
		std::cout << "Occupation Status:" << doodleOcc <<  std::endl;
		std::cout << "Organism:" << doodleOrg << std::endl;
		printf("Doodlebug Organism was created\n");
	} else {
		ok1b = false;
		ok2b = false;
		ok3b = false;
		ok4b = false;
		ok5b = false;
	}


	printf("\nPrinting Occupant/Organism grid--before.\n");
	myGrid_p->printGrid();
	//6)see if organism can be deleted
	bool ok6a = true; //deleteOrganismTest();
	bool ok6b = true;

	std::cout << "Before:Ant Occ: " << antOcc << std::endl;
	std::cout << "Before:Ant Org: " << antOrg << std::endl;
	std::cout << "Before:Doodle Occ: " << doodleOcc << std::endl;
	std::cout << "Before:Doodle Org: " << doodleOrg << std::endl;

	printf("Calling to delete ant.\n");
	myGrid_p->deleteOrganism(2, 2);
	antOcc = myGrid_p->getCellOccupant(2,2);
	std::cout << "After:Ant Occ: " << antOcc << std::endl;
	std::cout << "After:Ant Org: " << antOrg << std::endl;
	if(antOcc == empty){
		printf("Test passed, ant organism was deleted.\n");
	} else {
		ok6a = false;
	}

	printf("Calling to delete doodlebug.\n");
	myGrid_p->deleteOrganism(3, 2);
	doodleOcc = myGrid_p->getCellOccupant(3,2);
	std::cout << "After:Doodle Occ: " << doodleOcc << std::endl;
	std::cout << "After:Doodle Org: " << doodleOrg << std::endl;
	if(doodleOcc == empty){
		printf("Test passed, doodlebug organism was deleted.\n");
	} else {
		ok6b = false;
	}

	printf("Printing Occupant/Organism grid--after.\n");
	myGrid_p->printGrid();

	myGrid_p->setCellOccupant(1, 2, empty);
	printf("Calling to delete empty cell.\n");
	myGrid_p->deleteOrganism(1, 2); //cannot delete, should return message saying cannot delete



	puts("\nEnd of testing cellOccupantOrganismTests\n");

	result = ok1a && ok1b && ok2a && ok2b && ok3a && ok3b
			&& ok4a && ok4b && ok5a && ok5b && ok6a;// && ok6b;
	printf("Result: %s", result ? "cellOccupantOrganismTests passed\n" : "cellOccupantOrganismTests failed.\n");
	return result;
}

/**
 * Function calls the findFoodTest and returns true if tests pass.
 *
 * @return result true if the tests were able to pass and false if they were not able to pass.
 */
bool Tests2::findFoodTest()
{
	bool result = true;
	bool ok1 = true;
	bool ok2 = true;
	bool ok3 = true;
	bool ok4 = true;
	bool ok5 = true;
	std::cout << "Running the findFood test------------------" << std::endl;

	Grid* myGrid_p = new Grid(9);

	myGrid_p->setCellOccupant(2, 2, ant);
	Ant* a2 = new Ant(2,2);                   //1 neighbor
	myGrid_p->setCellOrganism(2,2, a2);

	myGrid_p->setCellOccupant(3, 1, ant);
	Ant* a3 = new Ant(3,1);                   //1 neighbor
	myGrid_p->setCellOrganism(3,1, a3);

	myGrid_p->setCellOccupant(3, 2, doodlebug);
	Doodlebug* d2 = new Doodlebug(3,2);                   //4 neighbors
	myGrid_p->setCellOrganism(3,2, d2);

	myGrid_p->setCellOccupant(3, 3, ant);
	Ant* a5 = new Ant(3,3);                   //1 neighbor
	myGrid_p->setCellOrganism(3,3, a5);

	myGrid_p->setCellOccupant(4, 2, ant);
	Ant* a6 = new Ant(4,2);                   //1 neighbor
	myGrid_p->setCellOrganism(4,2, a6);

	//////////////////////

	myGrid_p->setCellOccupant(0, 8, doodlebug);
	Doodlebug* d3 = new Doodlebug(0,8); 					//2 neighbors
	myGrid_p->setCellOrganism(0,8,d3);

	myGrid_p->setCellOccupant(0, 7, ant);
	Ant* cornerBlock1 = new Ant(0,7);					//1 niehgbor
	myGrid_p->setCellOrganism(0,7,cornerBlock1);

	myGrid_p->setCellOccupant(1,8 , ant);
	Ant* cornerBlock2 = new Ant(1,8);					//1 neighbor
	myGrid_p->setCellOrganism(1,8,cornerBlock2);

	myGrid_p->setCellOccupant(2, 5 , doodlebug);
	Doodlebug* d1 = new Doodlebug(2,5);					//0 neighbors, doodlebug
	myGrid_p->setCellOrganism(2,5, d1);

	//print grid
	puts("Printing findFoodTest grid.");
	myGrid_p->printGrid();

	////////////////////////

	puts("\nTest 1: a2");
	bool* a2check = myGrid_p->findFood(2, 2);
	bool a2ans[4] = {false, false, false, false};

	for(int i=0 ; i<4; i++){
		if(a2check[i] == a2ans[i]){
			printf("--Same--i:%d\n", i);
			std::cout << "output: " << a2check[i] << ", expected:" << a2ans[i] << std::endl;
		} else{
			printf("--Failed--i:%d\n", i);
			std::cout << "output: " << a2check[i] << ", expected:" << a2ans[i] << std::endl;
			ok1 = false;
		}
	}

	///////////////////////

	puts("\nTest 2: a3");
	bool* a3check = myGrid_p->findFood(3, 1);
	bool a3ans[4] = {false, false, false, false};

	for(int i=0 ; i<4; i++){
		if(a3check[i] == a3ans[i]){
			printf("--Same--i:%d\n", i);
			std::cout << "output: " << a3check[i] << ", expected:" << a3ans[i] << std::endl;
		} else{
			printf("--Failed--i:%d\n", i);
			std::cout << "output: " << a3check[i] << ", expected:" << a3ans[i] << std::endl;
			ok2 = false;
		}
	}

	///////////////////////

	puts("\nTest 3: d2");
	bool* a4check = myGrid_p->findFood(3, 2);
	bool a4ans[4] = {true, true, true, true};

	for(int i=0 ; i<4; i++){
		if(a4check[i] == a4ans[i]){
			printf("--Same--i:%d\n", i);
			std::cout << "output: " << a4check[i] << ", expected:" << a4ans[i] << std::endl;
		} else{
			printf("--Failed--i:%d\n", i);
			std::cout << "output: " << a4check[i] << ", expected:" << a4ans[i] << std::endl;
			ok3 = false;
		}
	}

	///////////////////////

	puts("\nTest 4: a5");
	bool* a5check = myGrid_p->findFood(0, 8);
	bool a5ans[4] = {false, false, false, false};

	for(int i=0 ; i<4; i++){
		if(a4check[i] == a4ans[i]){
			printf("--Same--i:%d\n", i);
			std::cout << "output: " << a5check[i] << ", expected:" << a5ans[i] << std::endl;
		} else{
			printf("--Failed--i:%d\n", i);
			std::cout << "output: " << a5check[i] << ", expected:" << a5ans[i] << std::endl;
			ok4 = false;
		}
	}

	///////////////////////

	puts("\nTest 5: d1");
	bool* a6check = myGrid_p->findFood(2, 5);
	bool a6ans[4] = {false, false, false, false};

	for(int i=0 ; i<4; i++){
		if(a4check[i] == a4ans[i]){
			printf("--Same--i:%d\n", i);
			std::cout << "output: " << a6check[i] << ", expected:" << a6ans[i] << std::endl;
		} else{
			printf("--Failed--i:%d\n", i);
			std::cout << "output: " << a6check[i] << ", expected:" << a6ans[i] << std::endl;
			ok5 = false;
		}
	}

	puts("\nEnd of testing findFood\n");

	result = ok1 && ok2 && ok3 && ok4 && ok5;
	printf("Result: %s", result ? "findFood passed\n" : "findFood failed.\n");
	return result;
}

/**
 * Function calls the checkNeighborsTest and returns true if tests pass.
 *
 * @return result true if the tests were able to pass and false if they were not able to pass.
 */
bool Tests2::checkNeighborsTest()
{
	bool result = true;
	bool ok1 = true;
	bool ok2 = true;
	bool ok3 = true;
	bool ok4 = true;
	std::cout << "Running the checkNieghbors test------------------" << std::endl;

	Grid* myGrid_p = new Grid(9);

	myGrid_p->setCellOccupant(2, 2, ant);
	Ant* a2 = new Ant(2,2);                   //one neighbor
	myGrid_p->setCellOrganism(2,2, a2);

	myGrid_p->setCellOccupant(3, 1, ant);
	Ant* a3 = new Ant(3,1);                   //one neighbor
	myGrid_p->setCellOrganism(3,1, a3);

	myGrid_p->setCellOccupant(3, 2, ant);
	Ant* a4 = new Ant(3,2);                   //four neighbors
	myGrid_p->setCellOrganism(3,2, a4);

	myGrid_p->setCellOccupant(3, 3, ant);
	Ant* a5 = new Ant(3,3);                   //one neighbor
	myGrid_p->setCellOrganism(3,3, a5);

	myGrid_p->setCellOccupant(4, 2, ant);
	Ant* a6 = new Ant(4,2);                   //one neighbor
	myGrid_p->setCellOrganism(4,2, a6);

	//////////////////////

	myGrid_p->setCellOccupant(0, 8, ant);
	Ant* antNOTMOVING = new Ant(0,8); 					//two neighbors
	myGrid_p->setCellOrganism(0,8,antNOTMOVING);

	myGrid_p->setCellOccupant(0, 7, ant);
	Ant* cornerBlock1 = new Ant(0,7);					//one niehgbor
	myGrid_p->setCellOrganism(0,7,cornerBlock1);

	myGrid_p->setCellOccupant(1,8 , ant);
	Ant* cornerBlock2 = new Ant(1,8);					//one neighbor
	myGrid_p->setCellOrganism(1,8,cornerBlock2);


	//print grid
	puts("Printing checkNeighborsTest grid.");
	myGrid_p->printGrid();

	////////////////////////

	puts("\nTest 1: a2");
	occupationStatus* a2check = myGrid_p->checkNeighbors(2, 2);
	occupationStatus a2ans[4] = {empty, ant, empty, empty};

	for(int i=0 ; i<4; i++){
		if(a2check[i] == a2ans[i]){
			printf("--Same--i:%d\n", i);
			std::cout << "output: " << a2check[i] << ", expected:" << a2ans[i] << std::endl;
		} else{
			printf("--Failed--i:%d\n", i);
			std::cout << "output: " << a2check[i] << ", expected:" << a2ans[i] << std::endl;
			ok1 = false;
		}
	}

	///////////////////////

	puts("\nTest 2: a3");
	occupationStatus* a3check = myGrid_p->checkNeighbors(3, 1);
	occupationStatus a3ans[4] = {empty, empty, ant, empty};

	for(int i=0 ; i<4; i++){
		if(a3check[i] == a3ans[i]){
			printf("--Same--i:%d\n", i);
			std::cout << "output: " << a3check[i] << ", expected:" << a3ans[i] << std::endl;
		} else{
			printf("--Failed--i:%d\n", i);
			std::cout << "output: " << a3check[i] << ", expected:" << a3ans[i] << std::endl;
			ok2 = false;
		}
	}

	///////////////////////

	puts("\nTest 3: a4");
	occupationStatus* a4check = myGrid_p->checkNeighbors(3, 2);
	occupationStatus a4ans[4] = {ant, ant, ant, ant};

	for(int i=0 ; i<4; i++){
		if(a4check[i] == a4ans[i]){
			printf("--Same--i:%d\n", i);
			std::cout << "output: " << a4check[i] << ", expected:" << a4ans[i] << std::endl;
		} else{
			printf("--Failed--i:%d\n", i);
			std::cout << "output: " << a4check[i] << ", expected:" << a4ans[i] << std::endl;
			ok3 = false;
		}
	}

	///////////////////////

	puts("\nTest 4: a5");
	occupationStatus* a5check = myGrid_p->checkNeighbors(0, 8);
	occupationStatus a5ans[4] = {unavailable, ant, unavailable, ant};

	for(int i=0 ; i<4; i++){
		if(a4check[i] == a4ans[i]){
			printf("--Same--i:%d\n", i);
			std::cout << "output: " << a5check[i] << ", expected:" << a5ans[i] << std::endl;
		} else{
			printf("--Failed--i:%d\n", i);
			std::cout << "output: " << a5check[i] << ", expected:" << a5ans[i] << std::endl;
			ok4 = false;
		}
	}

	puts("\nEnd of testing neighbors\n");

	result = ok1 && ok2 && ok3 && ok4;
	printf("Result: %s", result ? "checkNeighbors passed\n" : "checkNeighbors failed.\n");
	return result;
}

/**
 * Function calls the findMoveTest and returns true if tests pass.
 *
 * @return result true if the tests were able to pass and false if they were not able to pass.
 */
bool Tests2::findMoveTest()
{
	bool result = true;
	bool ok1 = true;
	bool ok2 = true;
	bool ok3 = true;
	bool ok4 = true;
	bool ok5 = true;
	std::cout << "Running the findMove test------------------" << std::endl;

	Grid* myGrid_p = new Grid(9);

	myGrid_p->setCellOccupant(2, 2, ant);
	Ant* a2 = new Ant(2,2);                   //1 neighbor
	myGrid_p->setCellOrganism(2,2, a2);

	myGrid_p->setCellOccupant(3, 1, ant);
	Ant* a3 = new Ant(3,1);                   //1 neighbor
	myGrid_p->setCellOrganism(3,1, a3);

	myGrid_p->setCellOccupant(3, 2, ant);
	Ant* a4 = new Ant(3,2);                   //4 neighbors
	myGrid_p->setCellOrganism(3,2, a4);

	myGrid_p->setCellOccupant(3, 3, ant);
	Ant* a5 = new Ant(3,3);                   //1 neighbor
	myGrid_p->setCellOrganism(3,3, a5);

	myGrid_p->setCellOccupant(4, 2, ant);
	Ant* a6 = new Ant(4,2);                   //1 neighbor
	myGrid_p->setCellOrganism(4,2, a6);

	//////////////////////

	myGrid_p->setCellOccupant(0, 8, ant);
	Ant* antNOTMOVING = new Ant(0,8); 					//2 neighbors
	myGrid_p->setCellOrganism(0,8,antNOTMOVING);

	myGrid_p->setCellOccupant(0, 7, ant);
	Ant* cornerBlock1 = new Ant(0,7);					//1 niehgbor
	myGrid_p->setCellOrganism(0,7,cornerBlock1);

	myGrid_p->setCellOccupant(1,8 , ant);
	Ant* cornerBlock2 = new Ant(1,8);					//1 neighbor
	myGrid_p->setCellOrganism(1,8,cornerBlock2);

	myGrid_p->setCellOccupant(2, 5 , doodlebug);
	Doodlebug* d1 = new Doodlebug(2,5);					//0 neighbors, doodlebug
	myGrid_p->setCellOrganism(2,5, d1);

	//print grid
	puts("Printing findMoveTest grid.");
	myGrid_p->printGrid();

	////////////////////////

	puts("\nTest 1: a2");
	bool* a2check = myGrid_p->findMove(2, 2);
	bool a2ans[4] = {true, false, true, true};

	for(int i=0 ; i<4; i++){
		if(a2check[i] == a2ans[i]){
			printf("--Same--i:%d\n", i);
			std::cout << "output: " << a2check[i] << ", expected:" << a2ans[i] << std::endl;
		} else{
			printf("--Failed--i:%d\n", i);
			std::cout << "output: " << a2check[i] << ", expected:" << a2ans[i] << std::endl;
			ok1 = false;
		}
	}

	///////////////////////

	puts("\nTest 2: a3");
	bool* a3check = myGrid_p->findMove(3, 1);
	bool a3ans[4] = {true, true, false, true};

	for(int i=0 ; i<4; i++){
		if(a3check[i] == a3ans[i]){
			printf("--Same--i:%d\n", i);
			std::cout << "output: " << a3check[i] << ", expected:" << a3ans[i] << std::endl;
		} else{
			printf("--Failed--i:%d\n", i);
			std::cout << "output: " << a3check[i] << ", expected:" << a3ans[i] << std::endl;
			ok2 = false;
		}
	}

	///////////////////////

	puts("\nTest 3: a4");
	bool* a4check = myGrid_p->findMove(3, 2);
	bool a4ans[4] = {false, false, false, false};

	for(int i=0 ; i<4; i++){
		if(a4check[i] == a4ans[i]){
			printf("--Same--i:%d\n", i);
			std::cout << "output: " << a4check[i] << ", expected:" << a4ans[i] << std::endl;
		} else{
			printf("--Failed--i:%d\n", i);
			std::cout << "output: " << a4check[i] << ", expected:" << a4ans[i] << std::endl;
			ok3 = false;
		}
	}

	///////////////////////

	puts("\nTest 4: a5");
	bool* a5check = myGrid_p->findMove(0, 8);
	bool a5ans[4] = {false, false, false, false};

	for(int i=0 ; i<4; i++){
		if(a4check[i] == a4ans[i]){
			printf("--Same--i:%d\n", i);
			std::cout << "output: " << a5check[i] << ", expected:" << a5ans[i] << std::endl;
		} else{
			printf("--Failed--i:%d\n", i);
			std::cout << "output: " << a5check[i] << ", expected:" << a5ans[i] << std::endl;
			ok4 = false;
		}
	}

	///////////////////////

	puts("\nTest 5: d1");
	bool* a6check = myGrid_p->findMove(2, 5);
	bool a6ans[4] = {true, true, true, true};

	for(int i=0 ; i<4; i++){
		if(a4check[i] == a4ans[i]){
			printf("--Same--i:%d\n", i);
			std::cout << "output: " << a6check[i] << ", expected:" << a6ans[i] << std::endl;
		} else{
			printf("--Failed--i:%d\n", i);
			std::cout << "output: " << a6check[i] << ", expected:" << a6ans[i] << std::endl;
			ok5 = false;
		}
	}

	puts("\nEnd of testing findMove\n");

	result = ok1 && ok2 && ok3 && ok4 && ok5;

	printf("Result: %s", result ? "findMove passed\n" : "findMove failed.\n");

	return result;
}


/**
 * Function calls the moveOrganismTest and returns true if tests pass.
 *
 * @return result true if the tests were able to pass and false if they were not able to pass.
 */
bool Tests2::moveOrganismTest()
{
	bool result = true;
	bool ok1 = true;
	bool ok2 = true;
	std::cout << "Running the moveOrganism test------------------" << std::endl;

	Grid* myGrid_p = new Grid(9);

	myGrid_p->setCellOccupant(3, 1, ant);
	Ant* a1 = new Ant(3,1);                   //1 neighbor
	myGrid_p->setCellOrganism(3,1, a1);

	myGrid_p->setCellOccupant(3, 2, doodlebug);
	Doodlebug* d1 = new Doodlebug(3,2);                //4 neighbors
	myGrid_p->setCellOrganism(3,2, d1);


	//print grid
	puts("Printing moveOrganism grid.");
	myGrid_p->printGrid();


	//move ant 1
	puts("Call moveOrganism to move a1 from (3,1) to (2,1).\n");
	myGrid_p->moveOrganism(3,1,2,1);
	myGrid_p->printGrid();

	if((myGrid_p->getCellOccupant(2, 1) == ant)&&(myGrid_p->getCellOccupant(3, 1) == empty)){
		puts("Ant(a1) moved. Pass.\n");
	} else{
		ok1 = false;
		puts("Ant(a1) did not moved. Fail.\n");
	}

	//move doodlebug 1
	puts("Call moveOrganism to move d1 from (3,2) to (4,2).\n");
	myGrid_p->moveOrganism(3,2,4,2);
	myGrid_p->printGrid();

	if((myGrid_p->getCellOccupant(4, 2) == doodlebug)&&(myGrid_p->getCellOccupant(3,2) == empty)){
		puts("Doodlebug(d1) moved. Pass.\n");
	} else{
		ok2 = false;
		puts("Doodlebug(d1) did not move. Fail.\n");
	}

	puts("\nEnd of testing moveOrganism\n");

	result = ok1 && ok2;

	printf("Result: %s", result ? "moveOrganism passed\n" : "moveOrganism failed.\n");

	return result;
}

/**
 * Function calls the printGridTest and the printCellTest and returns true if tests pass.
 *
 * @return result true if the tests were able to pass and false if they were not able to pass.
 */
bool Tests2::printGridAndCellTest()
{
	bool result = true;

	std::cout << "Running the printGridAndCell test------------------" << std::endl;

	Grid* myGrid_p = new Grid(9);

	myGrid_p->setCellOccupant(2, 2, ant);
	Ant* a2 = new Ant(2,2);                   //1 neighbor
	myGrid_p->setCellOrganism(2,2, a2);

	myGrid_p->setCellOccupant(3, 1, ant);
	Ant* a3 = new Ant(3,1);                   //1 neighbor
	myGrid_p->setCellOrganism(3,1, a3);

	myGrid_p->setCellOccupant(3, 2, doodlebug);
	Doodlebug* d2 = new Doodlebug(3,2);                   //4 neighbors
	myGrid_p->setCellOrganism(3,2, d2);

	myGrid_p->setCellOccupant(3, 3, ant);
	Ant* a5 = new Ant(3,3);                   //1 neighbor
	myGrid_p->setCellOrganism(3,3, a5);

	myGrid_p->setCellOccupant(4, 2, ant);
	Ant* a6 = new Ant(4,2);                   //1 neighbor
	myGrid_p->setCellOrganism(4,2, a6);

	//////////////////////

	myGrid_p->setCellOccupant(0, 8, doodlebug);
	Doodlebug* d3 = new Doodlebug(0,8); 					//2 neighbors
	myGrid_p->setCellOrganism(0,8,d3);

	myGrid_p->setCellOccupant(0, 7, ant);
	Ant* cornerBlock1 = new Ant(0,7);					//1 niehgbor
	myGrid_p->setCellOrganism(0,7,cornerBlock1);

	myGrid_p->setCellOccupant(1,8 , ant);
	Ant* cornerBlock2 = new Ant(1,8);					//1 neighbor
	myGrid_p->setCellOrganism(1,8,cornerBlock2);

	myGrid_p->setCellOccupant(2, 5 , doodlebug);
	Doodlebug* d1 = new Doodlebug(2,5);					//0 neighbors, doodlebug
	myGrid_p->setCellOrganism(2,5, d1);

	//print grid
	puts("Printing printGrid grid.");
	myGrid_p->printGrid();

	//print single cell
	puts("Printing printCell for single cell from grid.\n");
	puts("Print doodlebug (0,8):\n");
	myGrid_p->getCell(0,8).printCell();
	puts("\nPrint ant (3,3):\n");
	myGrid_p->getCell(3,3).printCell();
	puts("\nPrint doodlebug (2,5):\n");
	myGrid_p->getCell(2,5).printCell();
	puts("\nPrint ant (0,7):\n");
	myGrid_p->getCell(0,7).printCell();

	puts("\nEnd of testing printGridAndCell\n Check console to see if print out is as expected.\n");


	printf("Result: %s", result ? "printGrid and printCell passed\n" : "printGrid and printCell failed.\n");

	return result;
}


/**
 * Function checks if the ant object were able to be instantiate correctly and if the occupancy
 * status was set correctly.
 *
 * @return result A boolean value that is true if the ant object was instantiated correctly and if
 * its occupancy status was set to ant, and false if this was not done.
 */
bool Tests2::makeAntsTest()
{
	bool result = true;
	bool ok1 = true;
	bool ok2 = true;
	std::cout << "Running the make ants test------------------" << std::endl;

	Grid* myGrid_p = new Grid(9);
	if(myGrid_p->getCellOccupant(1, 2)!=empty)
	{
		std::cout << "Cell 1,2 not initially empty" << std::endl;
	}
	myGrid_p->setCellOccupant(1, 2, ant);
	if(myGrid_p->getCellOccupant(1, 2)!=ant)
	{
		std::cout << "Cell not set to ant" << std::endl;
		ok1 = false;
	}
	Ant* a1 = new Ant(3,4);
	if(myGrid_p->getCellOccupant(3, 4)!=empty)
	{
		std::cout << "Cell 3,4 not initially empty" << std::endl;
	}
	myGrid_p->setCellOccupant(3, 4, doodlebug);
	if(myGrid_p->getCellOccupant(3, 4)!=doodlebug)
	{
		std::cout << "Cell not set to doodlebug" << std::endl;
		ok2 = false;
	}
	myGrid_p->setCellOccupant(3, 4, empty);
	myGrid_p->printGrid();
	delete a1;
	delete myGrid_p;
	result = ok1 && ok2;
	printf("Result: %s", result ? "makeAntstest passed\n" : "makeAntsTest failed.\n");
	return result;
}

/**
 * Function calls the antsMovetest and returns true if tests pass.
 *
 * @return result true if the tests were able to pass and false if they were not able to pass.
 */
bool Tests2::antsMoveTest()
{

	bool result = true;
	std::cout << "Running the move ants test-------------------" << std::endl;

	Grid* myGrid_p = new Grid(9);
	myGrid_p->setCellOccupant(1, 2, ant);
	Ant* a1 = new Ant(1,2);
	myGrid_p->setCellOrganism(1,2, a1);//supposed to move when called

	myGrid_p->setCellOccupant(2, 2, ant);
	Ant* a2 = new Ant(2,2);                   //supposed to move when called
	myGrid_p->setCellOrganism(2,2, a2);

	myGrid_p->setCellOccupant(3, 1, ant);
	Ant* a3 = new Ant(3,1);                   //supposed to move when called
	myGrid_p->setCellOrganism(3,1, a3);

	myGrid_p->setCellOccupant(3, 2, ant);
	Ant* a4 = new Ant(3,2);                   //not supposed to move when called
	myGrid_p->setCellOrganism(3,2, a4);

	myGrid_p->setCellOccupant(3, 3, ant);
	Ant* a5 = new Ant(3,3);                   //supposed to move when called
	myGrid_p->setCellOrganism(3,3, a5);

	myGrid_p->setCellOccupant(4, 2, ant);
	Ant* a6 = new Ant(4,2);                   //supposed to move when called
	myGrid_p->setCellOrganism(4,2, a6);

	myGrid_p->setCellOccupant(0, 8, ant);
	Ant* antNOTMOVING = new Ant(0,8); //ant shouldn't move
	myGrid_p->setCellOrganism(0,8,antNOTMOVING);

	myGrid_p->setCellOccupant(0, 7, ant);
	Ant* cornerBlock1 = new Ant(0,7);
	myGrid_p->setCellOrganism(0,7,cornerBlock1);

	myGrid_p->setCellOccupant(1,8 , ant);
	Ant* cornerBlock2 = new Ant(1,8);
	myGrid_p->setCellOrganism(1,8,cornerBlock2);


	//print grid
	puts("Printing antsMoveTest grid -- before.");
	myGrid_p->printGrid();

	a4->move(myGrid_p);
	antNOTMOVING->move(myGrid_p);
	//check the cell occupant and if it is unoccupied the ant has move.
	//check getCelloccupied to see if the spot is occupied, if it is unoccupied the test is correct.
	if(myGrid_p->getCellOccupant(3, 2) == ant){
		result = true;
		puts("Ant(a4) did not move. Pass.\n");
	} else{
		result = false;
		puts("Ant(a4) moved. Fail.\n");
	}

	if(myGrid_p->getCellOccupant(0, 8) == ant){
		result = true;
		puts("Ant(corner case) did not move. Pass.\n");
	} else{
		result = false;
		puts("Ant(corner case) moved. Fail.\n");
	}


	a1->move(myGrid_p);
	//check the cell occupant and if it is unoccupied the ant has move.
	//check getCelloccupied to see if the spot is occupied, if it is unoccupied the test is correct.
	if(myGrid_p->getCellOccupant(1, 2) == empty){
		result = true;
		puts("Ant(a1) moved. Pass.\n");
	} else{
		result = false;
		puts("Ant(a1) did not move. Fail\n");
	}

	a2->move(myGrid_p);
	//check the cell occupant and if it is unoccupied the ant has move.
	//check getCelloccupied to see if the spot is occupied, if it is unoccupied the test is correct.
	if(myGrid_p->getCellOccupant(2, 2) == empty){
		result = true;
		puts("Ant(a2) moved. Pass.\n");
	} else{
		result = false;
		puts("Ant(a2) did not moved. Fail.\n");
	}


	puts("Printing antsMovetest grid -- after.");
	myGrid_p->printGrid();

	delete a1;
	delete myGrid_p;

	printf("Result: %s", result ? "moveAntsTest passed\n" : "moveAntsTest failed.\n");
	return result;
}

/**
 * Function calls the antsBreedTest and returns true if tests pass.
 *
 * @return result true if the tests were puts("Printing grid after.");
	myGrid_p->printGrid();able to pass and false if they were not able to pass.
 */
bool Tests2::antsBreedTest()
{

	bool result = true;
	std::cout << "Running the ant breed test-----------------------" << std::endl;

	Grid* myGrid_p = new Grid(9);
	myGrid_p->setCellOccupant(1, 2, ant);
	Ant* a1 = new Ant(1,2);
	myGrid_p->setCellOrganism(1,2, a1);//supposed to move when called

	myGrid_p->setCellOccupant(2, 2, ant);
	Ant* a2 = new Ant(2,2);                   //supposed to move when called
	myGrid_p->setCellOrganism(2,2, a2);

	myGrid_p->setCellOccupant(3, 1, ant);
	Ant* a3 = new Ant(3,1);                   //supposed to move when called
	myGrid_p->setCellOrganism(3,1, a3);

	myGrid_p->setCellOccupant(3, 2, ant);
	Ant* a4 = new Ant(3,2);                   //not supposed to move when called
	myGrid_p->setCellOrganism(3,2, a4);

	myGrid_p->setCellOccupant(3, 3, ant);
	Ant* a5 = new Ant(3,3);                   //supposed to move when called
	myGrid_p->setCellOrganism(3,3, a5);

	myGrid_p->setCellOccupant(4, 2, ant);
	Ant* a6 = new Ant(4,2);                   //supposed to move when called
	myGrid_p->setCellOrganism(4,2, a6);

	myGrid_p->setCellOccupant(0, 8, ant);
	Ant* antBreeding = new Ant(0,8); //ant shouldn't move
	myGrid_p->setCellOrganism(0,8,antBreeding);

	myGrid_p->setCellOccupant(0, 7, ant);
	Ant* cornerBlock1 = new Ant(0,7);
	myGrid_p->setCellOrganism(0,7,cornerBlock1);


	antBreeding->setStepCount(3);
	//print grid
	puts("Printing antsBreedtest grid -- before.");
	myGrid_p->printGrid();
	antBreeding->breed(myGrid_p);
	puts("Printing antsBreedtest grid -- after.");
	myGrid_p->printGrid();
	if(myGrid_p->getCellOccupant(1, 8) == empty){
		result = false;
		puts("Ant did not breed. Fail.\n");
	}
	else if(myGrid_p->getCellOccupant(1, 8) == ant){
		result = true;
		puts("Ant did breed. Pass.\n");
	}

	printf("Result: %s", result ? "antsBreedtest passed\n" : "antsBreedTest failed.\n");
	return result;
}

/**
 * Function calls the antsDieTest and returns true if tests pass.
 *
 * @return result true if the tests were able to pass and false if they were not able to pass.
 */
bool Tests2::antsDieTest()
{
	bool result = true;
	std::cout << "Running the eat ant test---------------------------" << std::endl;

	Grid* myGrid_p = new Grid(3);
	myGrid_p->setCellOccupant(1, 2, ant);
	Ant* a1 = new Ant(1,2);
	myGrid_p->setCellOrganism(1,2, a1);

	myGrid_p->setCellOccupant(1, 1, doodlebug);
	Doodlebug* d1 = new Doodlebug(1,1);
	myGrid_p->setCellOrganism(1,1, d1);


	puts("Printing antsDieTest grid -- before.");
	myGrid_p->printGrid();
	d1->eat(myGrid_p);

	puts("Printing antsDieTestgrid -- after.");
	myGrid_p->printGrid();
	if(myGrid_p->getCellOccupant(1, 2) == ant){
		result = false;
		puts("Ant has survived. Fail.\n");
	} else{
		result = true;
		puts("Ant has died. Pass.\n");
	}

	printf("Result: %s", result ? "antsDieTest passed\n" : "antsDieTest failed.\n");
	return result;
}

/**
 * Function calls the makeDoodlesTest and returns true if tests pass.
 *
 * @return result true if the tests were able to pass and false if they were not able to pass.
 */
bool Tests2::makeDoodlesTest()
{
	bool result = true;
	std::cout << "Running the make doodlebugs test------------------------------" << std::endl;


	printf("Result: %s", result ? "makeDoodlesTest passed\n" : "makeDoodlesTest failed.\n");
	return result;
}

/**
 *Function calls the doodleMoveTest and returns true if tests pass.
 *
 * @return result true if the tests were able to pass and false if they were not able to pass.
 */
bool Tests2::doodleMoveTest()
{
	bool result = true;
	std::cout << "Running the move doodlebugs test----------------------------" << std::endl;


	Grid* myGrid_p = new Grid(9);
	myGrid_p->setCellOccupant(1, 2, doodlebug);
	Doodlebug* d1 = new Doodlebug(1,2);
	myGrid_p->setCellOrganism(1,2, d1);

	d1->move(myGrid_p);
	//check the cell occupant and if it is unoccupied the doodlebug has move.
	//check getCelloccupied to see if the spot is occupied, if it is unoccupied the test is correct.
	if(myGrid_p->getCellOccupant(1, 2) == false){
		result = true;
	} else{
		result = false;
	}

	printf("Result: %s", result ? "doodleMoveTest passed\n" : "doodleMoveTest failed.\n");
	return result;
}

/**
 * Function calls the doodleBreedTest and returns true if tests pass.
 *
 * @return result true if the tests were able to pass and false if they were not able to pass.
 */
bool Tests2::doodleBreedTest(){
	bool result = true;
	std::cout << "Running the doodlebug breed test--------------------------" << std::endl;

	Grid* myGrid_p = new Grid(9);


	myGrid_p->setCellOccupant(0, 8, doodlebug);
	Doodlebug* doodleBreed = new Doodlebug(0,8);
	myGrid_p->setCellOrganism(0,8,doodleBreed);

	myGrid_p->setCellOccupant(0, 7, doodlebug);
	Doodlebug* cornerBlock1 = new Doodlebug(0,7);
	myGrid_p->setCellOrganism(0,7,cornerBlock1);


	doodleBreed->setStepCount(9);
	//print grid
	puts("Printing doodleBreedTest grid -- before.");
	myGrid_p->printGrid();
	doodleBreed->breed(myGrid_p);
	puts("Printing doodleBreedTest grid -- after.");
	myGrid_p->printGrid();
	if(myGrid_p->getCellOccupant(1, 8) == empty){
		result = false;
		puts("Doodle did not breed. Fail.\n");
	}
	else if(myGrid_p->getCellOccupant(1, 8) == doodlebug){
		result = true;
		puts("Doodle did breed. Pass.\n");
	}
	printf("Result: %s", result ? "doodleBreedTest passed\n" : "doodleBreedTest failed.\n");
	return result;
}

/**
 *Function calls the doodleEatTest and returns true if tests pass.
 *
 * @return result true if the tests were able to pass and false if they were not able to pass.
 */
bool Tests2::doodleEatTest()
{
	bool result = true;
	std::cout << "Running the eat ant test-----------------------------" << std::endl;

	Grid* myGrid_p = new Grid(3);
	myGrid_p->setCellOccupant(1, 2, ant);
	Ant* a1 = new Ant(1,2);
	myGrid_p->setCellOrganism(1,2, a1);

	myGrid_p->setCellOccupant(1, 1, doodlebug);
	Doodlebug* d1 = new Doodlebug(1,1);
	myGrid_p->setCellOrganism(1,1, d1);


	puts("Printing doodleEatTest grid -- before.");
	myGrid_p->printGrid();
	d1->eat(myGrid_p);

	puts("Printing doodleEatTest grid -- after.");
	myGrid_p->printGrid();
	if(myGrid_p->getCellOccupant(1, 2) == ant){
		result = false;
		puts("Doodlebug did not eat ant. Fail.\n");
	} else{
		result = true;
		puts("Ant has been eaten. Pass.\n");
	}

	printf("Result: %s", result ? "doodleEatTest passed\n" : "doodleEatTest failed.\n");
	return result;
}

/**
 * Function calls the doodleDietest and returns true if tests pass.
 *
 * @return result true if the tests were able to pass and false if they were not able to pass.
 */
bool Tests2::doodleDietest()
{
	bool result = true;
	std::cout << "Running the doodlebug dies test---------------------------" << std::endl;

	printf("Result: %s", result ? "doodleDietest passed\n" : "doodleDietest failed.\n");
	return result;
}

/**
 * Function is a destructor that takes the Test object and deletes it once the program is done using the
 * object.
 */
Tests2::~Tests2() {
	// TODO Auto-generated destructor stub
}

