#pragma once
#include "Void/Utils/Parser/ISerializable.h"
#include <Quantum/Quantum.h>

namespace Void {
	struct MeshCollider3DComponent : public ISerializable {
		Quantum::BoxCollider3D Collider;

		// Inherited via ISerializable
		virtual nlohmann::ordered_json ToJSON() const override {
			nlohmann::ordered_json json;

			json["IsTrigger"] = Collider.IsTrigger();
			json["Offset"]["X"] = Collider.GetOffset().x;
			json["Offset"]["Y"] = Collider.GetOffset().y;
			json["Offset"]["Z"] = Collider.GetOffset().z;
			json["HalfExtents"]["X"] = Collider.HalfExtents.x;
			json["HalfExtents"]["Y"] = Collider.HalfExtents.y;
			json["HalfExtents"]["Z"] = Collider.HalfExtents.z;

			return json;
		}

		virtual void FromJSON(const nlohmann::json& json) override {

			Collider.SetTrigger(json["IsTrigger"]);

			float x, y, z;
			x = json["Offset"]["X"];
			y = json["Offset"]["Y"];
			z = json["Offset"]["Z"];
			Collider.SetOffset({ x, y, z });

			x = json["HalfExtents"]["X"];
			y = json["HalfExtents"]["Y"];
			z = json["HalfExtents"]["Z"];
			Collider.HalfExtents = { x, y, z };
		}

	};
}