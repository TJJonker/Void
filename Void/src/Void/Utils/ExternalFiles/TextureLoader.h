#pragma once
#include <Void/Rendering/Components/Texture/Texture.h>

namespace Void {
	class TextureLoader
	{
	public:
		static Rendering::Texture* Load(const std::string& filePath);
	};
}
