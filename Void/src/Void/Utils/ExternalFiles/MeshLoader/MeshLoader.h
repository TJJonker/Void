#pragma once
#include <assimp/scene.h>
#include "Void/Rendering/Components/Mesh/Mesh.h"

namespace Void {
	class MeshLoader
	{
	private:
		struct Vertex {
			glm::vec3 Position;
			glm::vec3 Normals;
			glm::vec2 TextureCoords;
		};

	private:
		std::string m_Directory;

		static void							ProcessNode(aiNode* node, const aiScene* scene, Rendering::Mesh* model);
		static Rendering::VertexArray*		ProcessMesh(aiMesh* mesh, const aiScene* scene);
		static std::vector<Vertex>			GetVertexInformation(aiMesh* mesh);
		static std::vector<unsigned int>	GetIndices(aiMesh* mesh);
	public:
		static Rendering::Mesh*				Load(const std::string& filePath);
	};
}
