#pragma once
#include "Void/Rendering/Camera/Camera/Camera.h"

namespace Void {
	class VOID_API CameraController
	{
	private:
		Camera* m_Camera;

	private:
		void MoveCamera();
		void ScrollCamera();
		void LookCamera();

	public:
		CameraController();
		~CameraController();

		void Update();
		Camera* GetCamera() { return m_Camera; }
	};
}
