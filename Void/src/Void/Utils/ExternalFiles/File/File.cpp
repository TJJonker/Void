#include "pch.h"
#include "File.h"

namespace Void {
    std::string Void::File::Read(const char* filePath)
    {
		try {
			std::ifstream fileStream(filePath);
			fileStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);

			if (!fileStream.is_open()) { 
				VOID_CORE_ERROR("Failed to open file: {0}", filePath); 
				return {}; 
			}

			std::stringstream resultStream; 
			resultStream << fileStream.rdbuf(); 

			return resultStream.str();
		}
		catch (std::ifstream::failure e) {
			VOID_CORE_ERROR("File not read succesfully. File path: {0} - {1}:{2}", filePath, e.code().value(), e.what());
			return {};
		}
    }

	bool Void::File::Write(const char* filePath, const char* data)
	{
		try {
			std::ofstream fileStream(filePath, std::ios::out | std::ios::trunc);
			fileStream.exceptions(std::ofstream::failbit | std::ofstream::badbit);

			if (!fileStream.is_open()) {
				VOID_CORE_ERROR("Failed to open file: {0}", filePath);
				return false;
			}

			fileStream << data;
			fileStream.close(); 

			return true; 
		}
		catch (const std::ofstream::failure& e) {
			VOID_CORE_ERROR("File not written succesfully. File path: {0} - {1}:{2}", filePath, e.code().value(), e.what());
			return false;
		}
	}

}