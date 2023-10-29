#pragma once

namespace Void {
	class Texture
	{
	public:


		virtual ~Texture() = default;

		static Texture* Create(const std::string& filePath);

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
	};
}
