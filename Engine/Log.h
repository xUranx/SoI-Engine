#pragma once
#include <string>
namespace Engine {
	//Print/Log Error msg
	void fatal_error(std::string error);
	//Print/Log Error msg
	void fatal_error(std::string error, std::string ctx);
	//Print/Log info
	void Message(std::string msg);
}