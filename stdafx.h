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
