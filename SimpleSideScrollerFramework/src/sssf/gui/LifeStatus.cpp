#include "sssf\gui\LifeStatus.h"

LifeStatus::LifeStatus() 
{
	x = 0;
	y = 0;
	z = 0;
	width = 0;
	height = 0;
	type = 0;
}

LifeStatus::~LifeStatus() {}

void LifeStatus::initLifeStatus(vector<unsigned int> initID, 
							 int initX,
							 int initY,
							 int initZ,
							 int initAlpha,
							 int initWidth,
							 int initHeight, unsigned int initType)
{
	statusID = initID;
	x = initX;
	y = initY;
	z = initZ;
	alpha = initAlpha;
	width = initWidth;
	height = initHeight;
	type = initType;
}