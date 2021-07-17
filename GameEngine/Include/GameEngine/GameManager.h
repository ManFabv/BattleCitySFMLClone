#pragma once

#ifdef GAMEENGINE_EXPORTS
#define GAMEENGINE_API __declspec(dllexport)
#else
#define GAMEENGINE_API __declspec(dllimport)
#endif

namespace GameManagerMain
{
	class GAMEENGINE_API GameManager
	{
	public:
		GameManager();
		void TestGameEngineImplementation();
	};
}
