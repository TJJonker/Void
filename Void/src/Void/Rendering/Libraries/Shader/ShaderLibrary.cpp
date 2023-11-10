#include "pch.h"
#include "ShaderLibrary.h"

namespace Void {
	std::unique_ptr<ShaderLibrary> ShaderLibrary::m_Instance = std::make_unique<ShaderLibrary>();

	void ShaderLibrary::Load(const char* vertexPath, const char* fragmentPath, const char* title)
	{
		VOID_ASSERT(!m_Library.count(title), "Filepath/Alias: '{0}' already exists.", title);

		m_Library[title] = Rendering::Shader::Create(vertexPath, fragmentPath);
	}

	Rendering::Shader* ShaderLibrary::Get(const char* title)
	{
		VOID_ASSERT(m_Library.count(title), "Title: '{0}' does not exist.", title);
		return m_Library[title];
	}
}