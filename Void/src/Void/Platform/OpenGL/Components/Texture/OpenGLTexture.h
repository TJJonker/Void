#pragma once
#include "Void/Rendering/Components/Texture/Texture.h"
#include <glad/glad.h>

namespace Void::Rendering {
	class OpenGLTexture : public Texture
	{
	private:
		unsigned int m_ID;

	private:
		GLenum GetDataFormat(int amountOfChannels) const;

	public:
		OpenGLTexture(const std::string& filePath);
		virtual ~OpenGLTexture();

		virtual void Bind() const override;
		virtual void Unbind() const override;
	};
}
