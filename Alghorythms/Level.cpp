#include "Level.h"
#include <random>
#include <math.h>
#include <time.h>
#include <iostream>
Level::Level()
{

}


Level::~Level()
{
}

void Level::init(std::string _name, float _width, float _height)
{
	width = (int)_width;
	height = (int)_height;
	name = _name;

	rawMapData.resize(height);
	for (int i = 0; i < height; i++)
	{
		rawMapData[i].resize(width);
	}

	genRawMapData();

}

void Level::debugPrintRaw()
{
	for (int i = height-1; i > 0; i--)
	{
		for (int j = 0; j < width; j++)
		{
			if (rawMapData[i][j] == 1)
			{
				std::cout << "1";
			}
			else
			{
				std::cout << "0";
			}
		}
		std::cout<<std::endl;
	}
}

void Level::genMapData(b2World* world)
{
	
}

void Level::genRawMapDataOld()
{
	srand(time(NULL));
	for (int i = 0; i < width; i++)
	{
		if (i >= (width / 2) - 1 && i <= (width / 2) + 1)
		{
			rawMapData[0][i] = 1;
		}
		else
		{
			rawMapData[0][i] = 0;
		}
	}

	for (int i = 1; i < height; i++)
	{
		int count = 0;
		for (int j = 0; j < width; j++)
		{
			if ((j > 1 && j<width - 2)&& count < 3)
			{
				if (rawMapData[i - 1][j - 2] == 1 && (rawMapData[i][j - 2] == 0&& rawMapData[i][j - 1] == 0))
				{
					rawMapData[i][j - 1] = 1;
					count++;
				}
				if (count != 0)
				{
					rawMapData[i][j] = 1;
					count++;
				}
				else
				{
					if ((rawMapData[i - 1][j] == 1 || rawMapData[i - 1][j - 1] == 1 || rawMapData[i - 1][j + 1] == 1) && !(j<2 || j>width - 3))
					{
						int rnum = rand() % 10 + 1;
						if (rnum <= 5)
						{
							rawMapData[i][j] = 0;
						}
						else
						{
							rawMapData[i][j] = 1;
							count++;
						}
					}
					else if ((rawMapData[i - 1][j] == 1 || rawMapData[i - 1][j + 1] == 1) && j < 2)
					{
						int rnum = rand() % 10 + 1;
						if (rnum <= 5)
						{
							rawMapData[i][j] = 0;
						}
						else
						{
							rawMapData[i][j] = 1;
							count++;
						}
					}
					else if ((rawMapData[i - 1][j] == 1 || rawMapData[i - 1][j + 1] == 1) && j>width-3)
					{
						int rnum = rand() % 10 + 1;
						if (rnum <= 5)
						{
							rawMapData[i][j] = 0;
						}
						else
						{
							rawMapData[i][j] = 1;
							count++;
						}
					}
					else
					{
						rawMapData[i][j] = 0;
					}
				}
			}
			else
			{
				rawMapData[i][j] = 0;
			}
		}
	}

}

void Level::genRawMapData()
{
	//https://gamedev.stackexchange.com/questions/37887/how-do-i-generate-a-smooth-random-horizontal-2d-tunnel
	//https://www.codeproject.com/Articles/25237/Bezier-Curves-Made-Simple
	srand(time(NULL));
	int size = (height / 5)*2;
	float* points = new float[size];
	points[0] = width / 2;
	for (int i = 1; i < size; i+2)
	{
		int r = rand() % width + 2;
		if (r > width - 2) r -= 2;
		points[i] = r;
	}
	float lastPos = NULL;
	for (int i = 0; i < size; i + 2)
	{
		if (lastPos != NULL)
		{
			points[i - 1] = (lastPos + points[i]) / 2;
		}
		float lastPos = points[i];
	}
}
