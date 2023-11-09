#include "pch.h"
#include "OpenGLShader.h"
#include <glad/glad.h>
#include "Void/Platform/OpenGL/Debugging/OpenGLDebugger.h"
#include "Void/Utils/ExternalFiles/File/File.h"
#include <glm/gtc/type_ptr.hpp>

namespace Void::Rendering {
	//TODO: Seperate loading and managing
	OpenGLShader::OpenGLShader(const char* vertexShaderPath, const char* fragmentShaderPath)
	{
		unsigned int vertexShader = CompileShader(File::Read(vertexShaderPath).c_str(), GL_VERTEX_SHADER);
		unsigned int fragmentShader = CompileShader(File::Read(fragmentShaderPath).c_str(), GL_FRAGMENT_SHADER);

		m_ID = glCreateProgram();
		GLCall(glAttachShader(m_ID, vertexShader));
		GLCall(glAttachShader(m_ID, fragmentShader));
		GLCall(glLinkProgram(m_ID));

		// Check for prorgam errors.
		int success;
		char infoLog[512];
		GLCall(glGetProgramiv(m_ID, GL_LINK_STATUS, &success));

		if (!success) {
			GLCall(glGetProgramInfoLog(m_ID, 512, NULL, infoLog));
			std::cout << "[SHADER COMPILE ERROR]: " << infoLog << std::endl;
		}

		GLCall(glDeleteShader(vertexShader));
		GLCall(glDeleteShader(fragmentShader));
	}

	OpenGLShader::~OpenGLShader()
	{
		GLCall(glDeleteProgram(m_ID));
	}

	void OpenGLShader::Bind()
	{
		GLCall(glUseProgram(m_ID));
	}

	void OpenGLShader::Unbind()
	{
		GLCall(glUseProgram(0));
	}

	void OpenGLShader::SetMatrix4(const std::string& name, glm::mat4& v0)
	{
		GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(v0)));
	}

	void OpenGLShader::SetVec3(const std::string& name, glm::vec3& v0)
	{
		GLCall(glUniform3fv(GetUniformLocation(name), 1, glm::value_ptr(v0)));
	}

	void OpenGLShader::SetInt(const std::string& name, int v0)
	{
		GLCall(glUniform1i(GetUniformLocation(name), v0));
	}

	unsigned int OpenGLShader::CompileShader(const char* code, unsigned int type)
	{
		unsigned int shaderID = glCreateShader(type);
		glShaderSource(shaderID, 1, &code, NULL);
		glCompileShader(shaderID);

		// Check for errors in shader code.
		int success;
		char infoLog[512];
		GLCall(glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success));

		if (!success) {
			glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
			VOID_CORE_ERROR("[SHADER COMPILE ERROR]: {0}", infoLog);
		}

		return shaderID;
	}

	unsigned int OpenGLShader::GetUniformLocation(const std::string& name)
	{
		if (m_UniformMap.find(name) == m_UniformMap.end()) {
			m_UniformMap.insert({ name, glGetUniformLocation(m_ID, name.c_str()) });
		}
		//VOID_CORE_TRACE("{0} : {1}", m_UniformMap[name], name);
		return m_UniformMap[name];
	}
}