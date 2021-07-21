#pragma once

#include "GameplayUtilitiesExportDefine.h"

#include <iostream>
#include <fstream>
#include <string>

namespace GameplayUtilities
{
	namespace IO
	{
		class GAMEPLAYUTILITIES_API File
		{
		public:
			File(const std::string& filepath = "", std::ios::openmode openMode = std::ios::in);
			~File();
			void Open(const std::string& filepath = "", std::ios::openmode openMode = std::ios::in);
			void OpenForRead(const std::string& filepath);
			void OpenForWrite(const std::string& filepath);
			void Write(const std::string& inputValue);
			const std::string Read();
			const char* ReadAsCString();
			const bool IsOpen();
			void Close();
		private:
			std::fstream file;
		};
	}
}
