#include "pch.h"
#include "OpenGLFrameBuffer.h"
#include <glad/glad.h>

namespace Void::Rendering {

	OpenGLFrameBuffer::OpenGLFrameBuffer(const FrameBufferConfig& config)
		: m_Config(config)
	{
		Generate();
	}

	OpenGLFrameBuffer::~OpenGLFrameBuffer()
	{
		glDeleteFramebuffers(1, &m_ID);
		glDeleteTextures(1, &m_TextureID);
	}

	void OpenGLFrameBuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_ID);
	}

	void OpenGLFrameBuffer::UnBind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFrameBuffer::Generate()
	{
		// Generate FrameBuffer
		glGenFramebuffers(1, &m_ID); 
		glBindFramebuffer(GL_FRAMEBUFFER, m_ID);

		// Geenrate Texture
		glGenTextures(1, &m_TextureID);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);

		// Set texture parameters
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Config.width, m_Config.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

		// Attach the texture to the framebuffer
		glBindFramebuffer(GL_FRAMEBUFFER, m_ID); 
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_TextureID, 0); 

		// Check framebuffer completeness
		VOID_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer not generated correctly.");

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFrameBuffer::Resize(uint16_t width, uint16_t height)
	{
		m_Config.width = width;
		m_Config.height = height;

		glBindTexture(GL_TEXTURE_2D, m_TextureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	}


}