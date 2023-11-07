#pragma once
#include "Parser.h"
#include "Serializable.h"

namespace Void {
	class JSONParser 
	{
	public:
		static std::string Serialize(const Serializable& data);
		static std::string Serialize(const std::vector<Serializable>& data);
		static bool Deserialize(const char* data);
	};
}
