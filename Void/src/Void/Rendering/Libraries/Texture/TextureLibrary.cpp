#include "pch.h"
#include "TextureLibrary.h"

namespace Void {
	TextureLibrary& TextureLibrary::GetInstance()
	{
		static TextureLibrary instance;
		return instance;
	}

	void TextureLibrary::LoadTexture(const char* filePath)
	{
		VOID_ASSERT(!m_TextureLibrary.count(filePath), "Filepath: '{0}' already exists.", filePath);

		m_TextureLibrary[filePath] = Rendering::Texture::Create(filePath);
	}

	Rendering::Texture* TextureLibrary::GetTexture(const char* title)
	{
		VOID_ASSERT(m_TextureLibrary.count(title), "Title: '{0}' does not exist.", title);
		return m_TextureLibrary[title];
	}

	void TextureLibrary::LoadCubemap(const char* name, const std::vector<std::string>& textures)
	{
		VOID_ASSERT(!m_CubemapLibrary.count(name), "Cubemap with the title: '{0}' already exists.", name);

		m_CubemapLibrary[name] = Rendering::Cubemap::Create(textures);
	}

	Rendering::Cubemap* TextureLibrary::GetCubemap(const char* title)
	{
		VOID_ASSERT(m_CubemapLibrary.count(title), "Title: '{0}' does not exist.", title);
		return m_CubemapLibrary[title];
	}
}