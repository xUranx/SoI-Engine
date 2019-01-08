#include "Equations.h"
#include <iostream>
#include <glew.h>
#include "MainGame.h"

using namespace std;



int main(int argc, char* args[])
{
	MainGame Game;
	Game.run();
	system("pause");
	return 0;
	//printf("SoI = %f\n", SoI(2000.0,400.0, 5000.0));
}