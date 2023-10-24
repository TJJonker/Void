#pragma once
#include "Void/Core/Input.h"
#include <GLFW/glfw3.h>

namespace Void {
	class OpenGLInput : public Input
	{
	private:
		GLFWwindow* m_Window;

	public:
		OpenGLInput(void* window);
		 
	protected:
		// Keyboard
		bool VKeyPressed(int keycode) override;
		bool VKeyDown(int keycode) override;

		// Mouse
		bool VMousePressed(int button) override;
		glm::vec2 VMousePosition() override;
	};
}
