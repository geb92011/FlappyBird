#include "nuralNet.h"


bool nuralNet::getNetAnswer(poleData poles[10], pos bird)
{
	// Get the next pole in line
	int nextPole;
	int iterator = 0;
	while (iterator < 10)
	{
		if (poles[iterator].xStart > bird.x)
		{
			nextPole = iterator;
			iterator = 10;
		}
		iterator++;
	}


	// Execute and return the net answer
	return followPath(getHight(bird.y), getHight(poles[nextPole].y), 
		getDist(poles[nextPole].xStart), poles[nextPole].yDif, bird.ySpeed);
}

bool nuralNet::followPath(int hight, int poleHight, int poleDist, int poleDiff, int speed)
{
	int iReturn;




}


// Net evaluation
bool nuralNet::updateNet(int newScore)
{
	CurrentNet.distScore = newScore;

	// Evaluate if it has improved or not
	if (CurrentNet.distScore >= BestNet.distScore)
	{
		BestNet = CurrentNet;
	}
	else
	{
		CurrentNet = BestNet;
		changeValues();
	}


	return true;
}

// Change path values in net
void nuralNet::changeValues()
{
	// Chooses the path to modify
	int choosePath = rand() % INPUTS;

	// Chooses the component to modify
		// weight	bias
		// change weight more often than bias
		// 
	int chooseComponent = rand() % 100;
	if (chooseComponent > 60)
	{
		chooseComponent = 2;
	}
	else
	{
		chooseComponent = 1;
	}


}



// Returns
int nuralNet::getHight(int initY)
{
	// 600 ground
	int yReturn;

	yReturn = initY - 600;
	yReturn = yReturn * -1;

	return yReturn;

}

// Distance to pole
int nuralNet::getDist(int polePos)
{
	int iReturn;

	iReturn = polePos - BIRDX;

	return iReturn;
}
