#pragma once
#include "Void/Rendering/Components/Shader/Shader.h"
#include <map>

namespace Void {
	class OpenGLShader : public Shader
	{
	private:
		unsigned int m_ID;
		std::map<std::string, int> m_UniformMap;

	private:
		unsigned int CompileShader(const char* code, unsigned int type);
		unsigned int GetUniformLocation(const std::string& name);

	public:
		OpenGLShader(const char* vertexShaderPath, const char* fragmentShaderPath);
		~OpenGLShader();

		void Bind() override;
		void Unbind() override;

		void SetMatrix4(const std::string& name, glm::mat4& v0) override;
		void SetVec3(const std::string& name, glm::vec3& v0) override;
	};
}
