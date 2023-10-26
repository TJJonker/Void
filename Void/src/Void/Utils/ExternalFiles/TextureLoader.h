#pragma once
#include <Void/Rendering/Components/Texture/Texture.h>

namespace Void {
	class TextureLoader
	{
	private:

	public:
		static Texture* LoadTexture(const std::string& filePath);
	};
}
