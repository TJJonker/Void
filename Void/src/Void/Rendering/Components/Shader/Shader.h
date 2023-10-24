#pragma once

namespace Void {
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		static Shader* Create(const char* vertexShaderPath, const char* fragmentShaderPath);
	};
}