#include "pch.h"
#include "JSONParser.h"

namespace Void {
	std::string JSONParser::Serialize(const ISerializable& data)
	{
		nlohmann::json json;
		json["Entity"] = data.ToJSON();

		return json.dump(4);
	}
}