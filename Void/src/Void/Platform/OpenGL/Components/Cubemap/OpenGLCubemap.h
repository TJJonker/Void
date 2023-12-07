#pragma once
#include "Void/Rendering/Components/Cubemap/Cubemap.h"
#include <glad/glad.h>

namespace Void::Rendering {
	class OpenGLCubemap : public Cubemap
	{
	public:
		OpenGLCubemap(const std::vector<std::string>& textures);

		// Inherited via Cubemap
		virtual void Bind() const override;
		virtual void Unbind() const override;

	private:
		GLenum GetDataFormat(int amountOfChannels) const;

	private:
		unsigned int m_ID;
	};
}
