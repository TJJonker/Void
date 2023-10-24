#include "pch.h"
#include "Input.h"
#include "Void/Rendering/Components/Renderer/Renderer.h"
#include "Void/Platform/OpenGL/Input/OpenGLInput.h"

namespace Void {
	Input* Input::m_Input = nullptr;

	void Input::Create(void* window)
	{
		switch (Renderer::GetAPI()) {
			case Renderer::API::None:		VOID_CORE_ASSERT(false, "API 'NONE' is not supported.");
			case Renderer::API::OpenGL:	    Input::m_Input = new OpenGLInput(window);
		}
	}
}