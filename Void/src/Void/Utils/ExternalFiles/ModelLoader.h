#pragma once
#include <Void/Rendering/Components/Model/Model.h>
#include <assimp/scene.h>

namespace Void {
	class ModelLoader
	{
	private:
		struct Vertex {
			glm::vec3 Position;
			glm::vec3 Normals;
			glm::vec2 TextureCoords;
		};

	private:
		std::string m_Directory;

		static void ProcessNode(aiNode* node, const aiScene* scene, Model* model);
		static std::shared_ptr<VertexArray> ProcessMesh(aiMesh* mesh, const aiScene* scene);
		static std::vector<Vertex> GetVertexInformation(aiMesh* mesh);
		static std::vector<unsigned int> GetIndices(aiMesh* mesh);
	public:
		static Model* LoadModel(const std::string& filePath);
	};
}
