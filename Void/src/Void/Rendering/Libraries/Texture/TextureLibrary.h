#pragma once
#include "Void/Rendering/Components/Texture/Texture.h"
#include "Void/Rendering/Components/Cubemap/Cubemap.h"

namespace Void {
	class TextureLibrary
	{
	private:
		std::unordered_map < std::string, Rendering::Texture*> m_TextureLibrary;
		std::unordered_map < std::string, Rendering::Cubemap*> m_CubemapLibrary;

	public:
		static TextureLibrary& GetInstance();

		void LoadTexture(const char* filePath);
		void LoadCubemap(const char* name, const std::vector<std::string>& textures);

		Rendering::Texture*	GetTexture(const char* title);
		Rendering::Cubemap*	GetCubemap(const char* title);
	};
}
