#pragma once

#ifdef GAMEMANAGER_EXPORTS
#define GAMEMANAGER_API __declspec(dllexport)
#else
#define GAMEMANAGER_API __declspec(dllimport)
#endif

namespace GameManagerMain
{
	class GAMEMANAGER_API GameManager
	{
	public:
		GameManager();
		void TestGameEngineImplementation();
	};
}
