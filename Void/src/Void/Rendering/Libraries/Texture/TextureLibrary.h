#pragma once
#include "Void/Rendering/Components/Texture/Texture.h"

namespace Void {
	class TextureLibrary
	{
	private:
		static std::unique_ptr<TextureLibrary> m_Instance;

		std::unordered_map < std::string, Rendering::Texture*> m_Library;

	public:
		static TextureLibrary* GetInstance() { return m_Instance.get(); }

		void				Load(const char* filePath);
		Rendering::Texture*	Get(const char* title);
	};
}
