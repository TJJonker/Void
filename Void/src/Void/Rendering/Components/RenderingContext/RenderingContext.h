#pragma once

namespace Void::Rendering {
	class RenderingContext
	{
	public:
		virtual ~RenderingContext() = default;

		virtual void Init() = 0;

		static RenderingContext* Create();
	};
}
