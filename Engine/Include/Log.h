#pragma once
#include <string>
namespace Engine {
	//Print/Log Error msg
	extern void fatal_error(std::string error);
	//Print/Log Error msg
	extern void fatal_error(std::string error, std::string ctx);
	//Print/Log info
	extern void Message(std::string msg);
}