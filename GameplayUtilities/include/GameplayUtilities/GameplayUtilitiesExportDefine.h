#pragma once

#ifdef GAMEPLAYUTILITIES_EXPORTS
#define GAMEPLAYUTILITIES_API __declspec(dllexport)
#else
#define GAMEPLAYUTILITIES_API __declspec(dllimport)
#endif