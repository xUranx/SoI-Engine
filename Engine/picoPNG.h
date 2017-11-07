#pragma once
#ifndef  WIN32
#include <stddef.h>
#endif
#include <vector>
namespace Engine {
	int decodePNG(std::vector<unsigned char>& out_image, unsigned long& image_width, unsigned long& image_height, const unsigned char* in_png, size_t in_size, bool convert_to_rgba32 = true);
}