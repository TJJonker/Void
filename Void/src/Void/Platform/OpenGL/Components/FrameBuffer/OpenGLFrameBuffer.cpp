#include "pch.h"
#include "OpenGLFrameBuffer.h"
#include <glad/glad.h>
#include "Void/Platform/OpenGL/Debugging/OpenGLDebugger.h"

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
		glDeleteTextures(1, &m_DepthTextureID);
	}

	void OpenGLFrameBuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_ID);
		glViewport(0, 0, m_Config.width, m_Config.height);
	}

	void OpenGLFrameBuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFrameBuffer::Generate()
	{
		GLCall(glGenFramebuffers(1, &m_ID));
		GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_ID));
		
		GLCall(glGenTextures(1, &m_TextureID));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureID));
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Config.width, m_Config.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));

		GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_TextureID, 0));

		GLCall(glGenRenderbuffers(1, &m_DepthTextureID));
		GLCall(glBindRenderbuffer(GL_RENDERBUFFER, m_DepthTextureID));
		GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_Config.width, m_Config.height));
		GLCall(glBindRenderbuffer(GL_RENDERBUFFER, 0));

		GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_DepthTextureID));

		VOID_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Something went wrong in the FrameBuffer.");

		GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0)); 
	}

	void OpenGLFrameBuffer::Resize(uint16_t width, uint16_t height)
	{
		m_Config.width = width;
		m_Config.height = height;

		GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureID));
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Config.width, m_Config.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL));
	}
}