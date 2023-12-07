#pragma once

namespace Void::Rendering {
	class Cubemap
	{
	public:
		virtual ~Cubemap() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static Cubemap* Create(const std::vector<std::string>& textures);
	};
}
