#include "common.h"

void banana::common::Utils::PPP(void* ptr) {
	if ((unsigned char*)ptr != nullptr)
	{
		std::cout << (const char*)ptr << std::endl;
	}
	delete ptr;
}