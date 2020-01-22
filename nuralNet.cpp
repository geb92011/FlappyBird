#include "nuralNet.h"


bool nuralNet::getNetAnswer(poleData poles[10], pos bird)
{
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


	return followPath(getHight(bird.y), getHight(poles[nextPole].y), 
		getDist(poles[nextPole].xStart), poles[nextPole].yDif, bird.ySpeed);
}

bool nuralNet::followPath(int hight, int poleHight, int poleDist, int poleDiff, int speed)
{
	int iReturn;




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
