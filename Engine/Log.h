#pragma once
#include <string>
namespace Engine {
	void fatal_error(std::string error);
	void fatal_error(std::string error, std::string ctx);

	void Message(std::string msg);
}