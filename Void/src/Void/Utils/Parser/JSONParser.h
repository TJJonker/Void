#pragma once
#include "Parser.h"
#include "ISerializable.h"

// Temp
#include "Void/ECS/Components/TranformComponent.h"

namespace Void {
	class JSONParser 
	{
	public:
		static std::string Serialize(const ISerializable& data);
		

		template<typename T>
		static T Deserialize(const char* filePath)
		{
			//std::string data = File::Read(filePath);
			//nlohmann::json json = nlohmann::json::parse(data);
			//T object;
			//object.ToJSON()
			//json.push_back(T.ToJSON());
		}
	};
}
