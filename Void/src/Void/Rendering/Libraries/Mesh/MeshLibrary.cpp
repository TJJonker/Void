#include "pch.h"
#include "MeshLibrary.h"
#include "Void/Utils/ExternalFiles/MeshLoader/MeshLoader.h"

namespace Void {
	std::unique_ptr<MeshLibrary> MeshLibrary::m_Instance = std::make_unique<MeshLibrary>();

	void MeshLibrary::Load(const char* filePath)
	{
		VOID_ASSERT(!m_Library.count(filePath), "Filepath: '{0}' already exists.", filePath);
		m_Library[filePath] = MeshLoader::Load(filePath);
	}

	Rendering::Mesh* MeshLibrary::Get(const char* filePath)
	{
		VOID_ASSERT(m_Library.count(filePath), "Title: '{0}' does not exist.", filePath);
		return m_Library[filePath];
	}

	bool MeshLibrary::IsLoaded(const char* filePath)
	{
		return m_Library.count(filePath);
	}

}