#pragma once
#include <assimp/scene.h>
#include "Void/Rendering/Components/Mesh/Mesh.h"
#include <Void/Rendering/Components/VertexLayout.h>

namespace Void {
	class MeshLoader
	{
	private:
		std::string m_Directory;

		static void							ProcessNode(aiNode* node, const aiScene* scene, Rendering::Mesh* model);
		static Rendering::VertexArray*		ProcessMesh(aiMesh* mesh, const aiScene* scene);
		static std::vector<VertexLayout>	GetVertexInformation(aiMesh* mesh);
		static std::vector<unsigned int>	GetIndices(aiMesh* mesh);
	public:
		static Rendering::Mesh*				Load(const std::string& filePath);
	};
}
