#pragma once

namespace Void {
	class Texture
	{
	public:
		enum class TextureType {
			DIFFUSE = 0,
			SPECULAR = 1,
			NORMAL = 2,
			HEIGHT = 3
		};

		virtual ~Texture() = default;

		static Texture* Create(const std::string& path, const char* fileName, TextureType textureType);

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual TextureType GetTextureType() const = 0;
	};
}
