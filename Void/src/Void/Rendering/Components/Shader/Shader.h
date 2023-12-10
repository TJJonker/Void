#pragma once

namespace Void::Rendering {
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		static Shader* Create(const char* vertexShaderPath, const char* fragmentShaderPath);

		virtual void SetMatrix4(const std::string& name, const glm::mat4& v0) = 0;
		virtual void SetVec3(const std::string& name, glm::vec3& v0) = 0;
		virtual void SetVec4(const std::string& name, const glm::vec4& v0) = 0;
		virtual void SetInt(const std::string& name, int v0) = 0;
		virtual void SetFloat(const std::string& name, float v0) = 0;
	};
}