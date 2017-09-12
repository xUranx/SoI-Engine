#include "Error.h"
#include <iostream>

#ifdef _DEBUG
extern void fatal_error(std::string error)
{
	std::cout << error << std::endl;
}
extern void fatal_error(std::string error, std::string ctx)
{
	std::cout << error << ctx << std::endl;
}
#else
extern void fatal_error(std::string error)
{

}
extern void fatal_error(std::string error, std::string ctx)
{

}
#endif