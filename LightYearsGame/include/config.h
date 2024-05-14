#pragma once
#include <string>

std::string GetResourceDir() {
#ifdef NDEBUG //release build
	return "assets/";
#else
	return "D:/DEV/lightyears/LightYearsGame/assets/";
#endif
}
