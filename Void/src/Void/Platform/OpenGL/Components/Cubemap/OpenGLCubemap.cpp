#include "pch.h"
#include "OpenGLCubemap.h"
#include <Void/Vendor/stb_lib/stb_lib.h>

namespace Void::Rendering {
	GLenum OpenGLCubemap::GetDataFormat(int amountOfChannels) const
	{
		if (amountOfChannels == 1)
			return GL_RED;
		if (amountOfChannels == 3)
			return GL_RGB;
		return GL_RGBA;
	}

	OpenGLCubemap::OpenGLCubemap(const std::vector<std::string>& textures_faces)
	{
		glGenTextures(1, &m_ID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_ID);

		int width, height, nrChannels;
		unsigned char* data;
		for (unsigned int i = 0; i < textures_faces.size(); i++)
		{
			data = stbi_load(textures_faces[i].c_str(), &width, &height, &nrChannels, 0);
			VOID_ASSERT(data, "Failed to load texture: {0}", textures_faces[i]);
			GLenum dataFormat = GetDataFormat(nrChannels);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	}

	void OpenGLCubemap::Bind() const
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_ID);
	}

	void OpenGLCubemap::Unbind() const
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}
}