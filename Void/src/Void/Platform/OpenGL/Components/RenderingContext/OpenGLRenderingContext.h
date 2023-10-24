#pragma once
#include "Void/Rendering/Components/RenderingContext/RenderingContext.h"

namespace Void {
	class OpenGLRenderingContext : public RenderingContext
	{
	public:
		OpenGLRenderingContext();

		void Init() override;
	};
}
