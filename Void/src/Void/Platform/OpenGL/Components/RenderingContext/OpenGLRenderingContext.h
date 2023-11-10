#pragma once
#include "Void/Rendering/Components/RenderingContext/RenderingContext.h"

namespace Void::Rendering {
	class OpenGLRenderingContext : public RenderingContext
	{
	public:
		OpenGLRenderingContext();

		void Init() override;
	};
}
