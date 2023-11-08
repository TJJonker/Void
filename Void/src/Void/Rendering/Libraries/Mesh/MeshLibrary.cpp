#include "pch.h"
#include "MeshLibrary.h"
#include "Void/Utils/ExternalFiles/MeshLoader/MeshLoader.h"

namespace Void {
	std::unique_ptr<MeshLibrary> MeshLibrary::m_Instance = std::make_unique<MeshLibrary>();

	void MeshLibrary::Load(const char* filePath, const char* alias)
	{
		const char* name = alias == "" ? filePath : alias;
		VOID_ASSERT(m_Library.count(name), "Filepath/Alias: '{0}' already exists.", name);

		Rendering::Mesh* mesh = MeshLoader::Load(filePath);
		m_Library[name] = std::make_unique<Rendering::Mesh>(mesh);
	}

	Rendering::Mesh* MeshLibrary::Get(const char* title)
	{
		VOID_ASSERT(m_Library.count(title), "Title: '{0}' does not exist.", title);
		return m_Library[title].get();
	}

}