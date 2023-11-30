#pragma once

namespace Void {
	struct CameraControllerComponent {
		unsigned int KeyForward = 'W';
		unsigned int KeyBackward = 'S';
		unsigned int KeyLeft = 'A';
		unsigned int KeyRight = 'D';

		float MovementSpeed = 4.0f;
		float Sensitivity = 30.f;
	};
}