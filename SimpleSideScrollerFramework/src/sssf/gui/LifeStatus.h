#pragma once
#include "sssf_VS\stdafx.h"
#include <vector>

class Game;
class TextureManager;

class LifeStatus
{
	//private:
	public:
		vector<unsigned int> statusID;
		int x;
		int y;
		int z;
		int alpha;
		int width;
		int height;
		unsigned int type;

	public:

		LifeStatus::LifeStatus();
		LifeStatus::~LifeStatus();

		void initLifeStatus(vector<unsigned int> initID, 
							 int initX,
							 int initY,
							 int initZ,
							 int initAlpha,
							 int initWidth,
							 int initHeight, unsigned int initType);
};