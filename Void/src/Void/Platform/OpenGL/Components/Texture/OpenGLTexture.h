#pragma once
#include "Void/Rendering/Components/Texture/Texture.h"
#include <glad/glad.h>

namespace Void {
	class OpenGLTexture : public Texture
	{
	private:
		unsigned int m_ID;
		TextureType m_TextureType;

	private:
		GLenum GetDataFormat(int amountOfChannels) const;

	public:
		OpenGLTexture(const std::string& path, const char* fileName, TextureType textureType);
		virtual ~OpenGLTexture();

		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual TextureType GetTextureType() const override { return m_TextureType; }
	};
}
