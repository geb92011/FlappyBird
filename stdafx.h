#pragma once

#include "libraries.h"
#include "classes.h"
#include "GlobalIDS.h"




struct pos
{
	int x;
	int y;
	int xSpeed;
	int ySpeed;
};


struct poleData
{
	// True = top
	// False = bottom
	int yDif;

	int xStart;
	int xEnd;
	int y;
};




// Nural net
struct element
{
	int value;
	int link;
};

struct net
{
	int distScore;
	element input[INPUTS];
	element weight1[INPUTS];
	element bias1[INPUTS];
};
