#pragma once
#include "glm/glm.hpp"
#include <Void/Physics/Colliders/Collider.h>
#include "Void/Utils/Parser/ISerializable.h"
#include "Void/Physics/Colliders/PlaneCollider.h"
#include "Void/Physics/Colliders/SphereCollider.h"
#include "Void/Physics/Colliders/MeshCollider.h"
#include "Void/Physics/Collision.h"

namespace Void {
	struct PhysicsComponent : public ISerializable {

		float Mass = 1;
		bool IsStatic = false;
		glm::vec3 Force = glm::vec3(0);
		Collider* Collider = nullptr;

		nlohmann::ordered_json ToJSON() const override {
			nlohmann::ordered_json json;

			json["Mass"] = Mass;
			json["IsStatic"] = IsStatic;

			if (PlaneCollider* collider = dynamic_cast<PlaneCollider*>(Collider)) {
				json["Type"] = "Plane";
				json["Data"] = collider->ToJSON();
			}

			if (SphereCollider* collider = dynamic_cast<SphereCollider*>(Collider)) {
				json["Type"] = "Sphere";
				json["Data"] = collider->ToJSON();
			}

			if (MeshCollider* collider = dynamic_cast<MeshCollider*>(Collider)) {
				json["Type"] = "Mesh";
				json["Data"] = collider->ToJSON();
			}

			return json;
		}

		void FromJSON(const nlohmann::json& json) override {
			Mass = json["Mass"];
			IsStatic = json["IsStatic"];

			std::string type = json["Type"];
			if (type == "Plane") {
				Collider = new PlaneCollider();
				Collider->FromJSON(json["Data"]);
			}

			if (type == "Sphere") {
				Collider = new SphereCollider();
				Collider->FromJSON(json["Data"]);
			}

			if (type == "Mesh") {
				Collider = new MeshCollider();
				Collider->FromJSON(json["Data"]);
			}
		}
	};
}