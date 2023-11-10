#include "pch.h"
#include "Input.h"
#include "Void/Rendering/Components/Renderer/Renderer.h"
#include "Void/Platform/OpenGL/Input/OpenGLInput.h"

namespace Void {
	Input* Input::m_Input = nullptr;

	void Input::Create(void* window)
	{
		switch (Rendering::Renderer::GetAPI()) {
			case Rendering::Renderer::API::None:		VOID_CORE_ASSERT(false, "API 'NONE' is not supported.");
			case Rendering::Renderer::API::OpenGL:	    Input::m_Input = new OpenGLInput(window);
		}
	}
}