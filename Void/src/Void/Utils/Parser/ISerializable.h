#pragma once
#include <nlohmann/json.hpp>

namespace Void {
	class ISerializable
	{
	public:
		virtual nlohmann::ordered_json ToJSON() const = 0;
		virtual void FromJSON(const nlohmann::json& json) = 0;
	};
}
