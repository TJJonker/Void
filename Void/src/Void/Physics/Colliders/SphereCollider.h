#pragma once
#include "Collider.h"

namespace Void {
	struct SphereCollider : public Collider {
	
		glm::vec3 Offset;
		float Radius;

		CollisionPoints TestCollision(
			const Transform* transform, 
			const Collider* collider, 
			const Transform* colliderTransform) const override;

		CollisionPoints TestCollision(
			const Transform* transform, 
			const SphereCollider* collider, 
			const Transform* sphereTransform) const override;

		CollisionPoints TestCollision(
			const Transform* transform, 
			const PlaneCollider* plane, 
			const Transform* planeTransform) const override;

		virtual nlohmann::ordered_json ToJSON() const override {
			nlohmann::ordered_json json;
			json["Offset"]["X"] = Offset.x;
			json["Offset"]["Y"] = Offset.y;
			json["Offset"]["Z"] = Offset.z;

			json["Radius"] = Radius;
			return json;
		}

		virtual void FromJSON(const nlohmann::json& json) override {
			Offset.x = json["Offset"]["X"];
			Offset.y = json["Offset"]["Y"];
			Offset.z = json["Offset"]["Z"];

			Radius = json["Radius"];
		}
	};
}