#include "pch.h"
#include "TextureLibrary.h"

namespace Void {
	std::unique_ptr<TextureLibrary> TextureLibrary::m_Instance = std::make_unique<TextureLibrary>();

	void TextureLibrary::Load(const char* filePath)
	{
		VOID_ASSERT(!m_Library.count(filePath), "Filepath: '{0}' already exists.", filePath);

		m_Library[filePath] = Rendering::Texture::Create(filePath);
	}

	Rendering::Texture* TextureLibrary::Get(const char* title)
	{
		VOID_ASSERT(m_Library.count(title), "Title: '{0}' does not exist.", title);
		return m_Library[title];
	}
}