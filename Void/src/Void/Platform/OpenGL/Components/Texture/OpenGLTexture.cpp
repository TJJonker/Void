#include "pch.h"
#include "OpenGLTexture.h"
#include <Void/Platform/OpenGL/Debugging/OpenGLDebugger.h>
#include <Void/Vendor/stb_lib/stb_lib.h>

namespace Void::Rendering {
    GLenum OpenGLTexture::GetDataFormat(int amountOfChannels) const
    {
        if (amountOfChannels == 1) 
            return GL_RED; 
        if (amountOfChannels == 3)
            return GL_RGB; 
        return GL_RGBA; 
    }
    
    // TODO: Extract to own class

    OpenGLTexture::OpenGLTexture(const std::string& filePath)
    {
        GLCall(glGenTextures(1, &m_ID));
        GLCall(glBindTexture(GL_TEXTURE_2D, m_ID));

        int width, height, nrChannels;
        unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);
        GLenum dataFormat = GetDataFormat(nrChannels);
        if (data) {
            GLCall(glTexImage2D(GL_TEXTURE_2D, 0, dataFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, data));
            GLCall(glGenerateMipmap(GL_TEXTURE_2D));
        }
        else {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);


        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    }

    OpenGLTexture::~OpenGLTexture()
    {
        GLCall(glDeleteTextures(1, &m_ID));
    }

    void OpenGLTexture::Bind() const
    {
        GLCall(glBindTexture(GL_TEXTURE_2D, m_ID));
    }

    void OpenGLTexture::Unbind() const
    {
        GLCall(glBindTexture(GL_TEXTURE_2D, 0));
    }

}