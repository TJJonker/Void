#include "pch.h"
#include "Shader.h"
#include "Void/Rendering/Components/Renderer/Renderer.h"
#include "Void/Platform/OpenGL/Components/Shader/OpenGLShader.h"

namespace Void::Rendering {
	Shader* Shader::Create(const char* vertexShaderPath, const char* fragmentShaderPath)
	{
        switch (Renderer::GetAPI()) {
            case Renderer::API::None:		VOID_CORE_ASSERT(false, "API 'NONE' is not supported."); return nullptr;
            case Renderer::API::OpenGL:	    return new OpenGLShader(vertexShaderPath, fragmentShaderPath);
            default: VOID_ASSERT(false, "Invalid option selected or not implemented yet."); return nullptr;
        }
	}
}