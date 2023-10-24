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
		LookCamera();
	}

	void CameraController::MoveCamera()
	{
		int moveX = Input::KeyDown('D') - Input::KeyDown('A');
		int moveY = Input::KeyDown('W') - Input::KeyDown('S');
		m_Camera->MoveCamera({ moveX, moveY });
	}

	void CameraController::ScrollCamera()
	{
		// TODO: Rework so it works with callbacks instead of polling.
	}

	void CameraController::LookCamera()
	{
		glm::vec2 mousePosition = Input::MousePosition(); 
		m_Camera->LookCamera(mousePosition);
	}
}