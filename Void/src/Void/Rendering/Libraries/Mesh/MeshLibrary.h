#pragma once
#include "Void/Rendering/Components/Mesh/Mesh.h"
#include <memory>
#include <unordered_map>
#include <string>

namespace Void {
	class MeshLibrary
	{
	private:
		static std::unique_ptr<MeshLibrary> m_Instance;

		std::unordered_map<std::string, Rendering::Mesh*> m_Library;

	public:
		static MeshLibrary* GetInstance() { return m_Instance.get(); }

		void				Load(const char* filePath);
		Rendering::Mesh*	Get(const char* filePath);
		bool				IsLoaded(const char* filePath);
	};
}
