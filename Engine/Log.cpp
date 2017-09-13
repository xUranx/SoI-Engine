#include "Log.h"
#include <iostream>
#include <cstdlib>
#include <SDL.h>

#ifdef _DEBUG
extern void fatal_error(std::string error)
{
	std::cout << "Error: " << error << std::endl;
}

extern void fatal_error(std::string error, std::string ctx)
{
	std::cout << "Error: " << error << ctx << std::endl;
}

extern void Message(std::string msg)
{
	std::cout << "Info: " << msg << std::endl;
}

#else
extern void fatal_error(std::string error)
{

}
extern void fatal_error(std::string error, std::string ctx)
{

}
extern void Message(std::string msg)
{

}
#endif

