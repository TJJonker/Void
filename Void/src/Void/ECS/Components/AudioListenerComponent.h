#pragma once
#include "Void/Utils/Parser/ISerializable.h"

namespace Void {
	struct AudioListenerComponent : public ISerializable {
		virtual nlohmann::ordered_json ToJSON() const { return {}; }
		virtual void FromJSON(const nlohmann::json& json) {}
	};
}