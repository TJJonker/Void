#pragma once

namespace Void {
	class RenderingContext
	{
	public:
		virtual ~RenderingContext() = default;

		virtual void Init() = 0;

		static RenderingContext* Create();
	};
}
