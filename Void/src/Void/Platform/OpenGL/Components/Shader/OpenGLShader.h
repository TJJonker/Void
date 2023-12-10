#pragma once
#include "Void/Rendering/Components/Shader/Shader.h"
#include <map>

namespace Void::Rendering {
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

		void SetMatrix4(const std::string& name, const glm::mat4& v0) override;
		void SetVec3(const std::string& name, glm::vec3& v0) override;
		void SetInt(const std::string& name, int v0) override;
		void SetFloat(const std::string& name, float v0) override;

		// Inherited via Shader
		void SetVec4(const std::string& name, const glm::vec4& v0) override;
	};
}
