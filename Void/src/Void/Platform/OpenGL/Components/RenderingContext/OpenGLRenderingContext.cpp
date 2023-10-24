#include "pch.h"
#include "OpenGLRenderingContext.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Void/Platform/OpenGL/Debugging/OpenGLDebugger.h>

namespace Void {
	OpenGLRenderingContext::OpenGLRenderingContext() { }

	void OpenGLRenderingContext::Init()
	{
		int result = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);	// Check if the GLAD/GLFW initialisation worked
		VOID_CORE_ASSERT(result, "Failed to initialize GLAD");

		// TODO: Change feels hacky and is hardcoded...
		GLCall(glViewport(0, 0, 1280, 720));
	}
}