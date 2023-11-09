#pragma once
#include "Void/Rendering/Components/Shader/Shader.h"

namespace Void {
	class ShaderLibrary
	{
	private:
		static std::unique_ptr<ShaderLibrary> m_Instance;

		std::unordered_map<std::string, Rendering::Shader*> m_Library;

	public:
		static ShaderLibrary* GetInstance() { return m_Instance.get(); }

		void				Load(const char* vertexPath, const char* fragmentPath, const char* title = "");
		Rendering::Shader*	Get(const char* title);
	};

	// TODO: Add destructor. Same for other libs
}
