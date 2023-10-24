#pragma once
#include "Void/Rendering/Components/Shader/Shader.h"

namespace Void {
	class OpenGLShader : public Shader
	{
	private:
		unsigned int m_ID;

	private:
		unsigned int CompileShader(const char* code, unsigned int type);

	public:
		OpenGLShader(const char* vertexShaderPath, const char* fragmentShaderPath);
		~OpenGLShader();

		void Bind() override;
		void Unbind() override;
	};
}
