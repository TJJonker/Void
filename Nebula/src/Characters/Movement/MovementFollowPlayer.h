#pragma once
#include "Void.h"
#include "Characters/Core/IMovement.h"
#include <Void/ECS/Components/TranformComponent.h>

class MovementFollowPlayer : public IMovement
{
private:
	unsigned int m_MovementSpeed = 0;
	glm::vec3 m_TargetLocation = glm::vec3(0);
	float m_TimeBetweenLocationRequests = 10;

public:
	MovementFollowPlayer();

	virtual void SetMovementSpeed(float movementSpeed) { m_MovementSpeed = movementSpeed; }

	virtual void Move() override;
	virtual void OnHit() override;
};

