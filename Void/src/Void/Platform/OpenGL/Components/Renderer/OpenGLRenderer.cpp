#include "pch.h"
#include "OpenGLRenderer.h"
#include <Void/Platform/OpenGL/Debugging/OpenGLDebugger.h>

namespace Void {
	void OpenGLRenderer::Draw(const std::shared_ptr<VertexArray> vertexArray)
	{
		GLCall(glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr));
	}

	void OpenGLRenderer::Clear()
	{
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	}

	void OpenGLRenderer::SetClearColor()
	{
	}
}