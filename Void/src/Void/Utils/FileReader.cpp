#include "pch.h"
#include "FileReader.h"

namespace Void {
    std::string Void::FileReader::ReadFile(const char* filePath)
    {
		std::string data;
		std::ifstream fileStream;
		fileStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try {
			// Open a the file 
			fileStream.open(filePath);

			// Create a datastream
			std::stringstream resultStream;
			resultStream << fileStream.rdbuf();
			fileStream.close();
			data = resultStream.str();
		}
		catch (std::ifstream::failure e) {
			VOID_CORE_ERROR("File not read succesfully. File path: {0}", filePath);
		}

		return data;
    }
}