#include "pch.h"
#include "OpenGLShader.h"
#include "Void/Utils/FileReader.h"
#include <glad/glad.h>
#include "Void/Platform/OpenGL/Debugging/OpenGLDebugger.h"

namespace Void {
	OpenGLShader::OpenGLShader(const char* vertexShaderPath, const char* fragmentShaderPath)
	{
		unsigned int vertexShader = CompileShader(FileReader::ReadFile(vertexShaderPath).c_str(), GL_VERTEX_SHADER);
		unsigned int fragmentShader = CompileShader(FileReader::ReadFile(fragmentShaderPath).c_str(), GL_FRAGMENT_SHADER);

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
}