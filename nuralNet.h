#pragma once

#include "stdafx.h"

class nuralNet
{
public:
	// Net inputes
		// Hight
		// Downwared speed
		// Horizontal speed
		// Distance to pole
		// Pole hight
		// Pole difference
	//

	// Execution
	bool getNetAnswer(poleData[10], pos);

	bool followPath(int, int, int, int, int);

	int followLink(int);

	// Returns
	int getHight(int);
	int getDist(int);


	nuralNet();

	// Net evaluation
	bool updateNet(int);
	
	void changeValues();

private:
	net CurrentNet;
	net BestNet;

	int iteration;
};

