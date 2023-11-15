#pragma once

struct IMovement {
	virtual void SetMovementSpeed(float movementSpeed) = 0;
	virtual void Move() = 0;
	virtual void OnHit() = 0;
};