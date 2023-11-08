#pragma once

namespace Void {

	class File
	{
	public:
		static std::string Read(const char* filePath);
		static bool Write(const char* filePath, const char* data);
	};

}

