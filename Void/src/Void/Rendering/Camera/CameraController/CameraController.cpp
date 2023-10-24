#include "pch.h"
#include "CameraController.h"
#include "Void/Core/Input.h"

namespace Void {

	CameraController::CameraController()
	{
		m_Camera = new Camera();
	}

	CameraController::~CameraController()
	{
		delete m_Camera;
	}

	void CameraController::Update()
	{
		MoveCamera();
	}

	void CameraController::MoveCamera()
	{
		int moveX = Input::KeyDown('d') - Input::KeyDown('a');
		int moveY = Input::KeyDown('w') - Input::KeyDown('s');
		m_Camera->MoveCamera({ moveX, moveY });
	}

	void CameraController::ScrollCamera()
	{
		// TODO: Rework so it works with callbacks instead of polling.
	}

	void CameraController::LookCamera()
	{
		glm::vec2 mousePosition;
		m_Camera->LookCamera(mousePosition);
	}
}