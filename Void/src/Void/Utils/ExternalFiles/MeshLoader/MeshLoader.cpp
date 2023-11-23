#include "pch.h"
#include "MeshLoader.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "Void/Utils/ExternalFiles/File/File.h"


namespace Void {

	Rendering::Mesh* MeshLoader::Load(const std::string& filePath)
	{
		// Loadinig file into memory
		std::string data = File::Read(filePath.c_str());

		// Read file
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFileFromMemory(data.c_str(), data.length(), 
			aiProcess_Triangulate | aiProcess_GenSmoothNormals | 
			aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

		// Check for errors
		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
		{
			VOID_CORE_ERROR("ERROR::ASSIMP:: {0}", importer.GetErrorString());
			return nullptr;
		}

		// Save path to directory
		std::string directory = filePath.substr(0, filePath.find_last_of('/'));

		Rendering::Mesh* mesh = new Rendering::Mesh();

		// Start processing file
		ProcessNode(scene->mRootNode, scene, mesh);

		return mesh;
	}


	void MeshLoader::ProcessNode(aiNode* node, const aiScene* scene, Rendering::Mesh* mesh)
	{
		// Iterate over current Node's meshes and process the meshes
		for (unsigned int i = 0; i < node->mNumMeshes; ++i) {
			mesh->Submeshes.push_back(ProcessMesh(scene->mMeshes[node->mMeshes[i]], scene));
		}

		// Check if the current Node has more child Nodes and recursively call this function.
		for (unsigned int i = 0; i < node->mNumChildren; ++i) {
			ProcessNode(node->mChildren[i], scene, mesh);
		}
	}

	Rendering::VertexArray* MeshLoader::ProcessMesh(aiMesh* mesh, const aiScene* scene)
	{
		Rendering::VertexArray* vertexArray = Rendering::VertexArray::Create();
		
		// VertexBuffer Related stuff
		std::vector<Vertex> vertices = GetVertexInformation(mesh);

		std::shared_ptr<Rendering::VertexBuffer> vertexBuffer; 
		vertexBuffer.reset(Rendering::VertexBuffer::Create(vertices.data(), vertices.size() * sizeof(float) * 8));

		VertexBufferLayout vertexBufferLayout;
		vertexBufferLayout.Push<float>(3); // Position
		vertexBufferLayout.Push<float>(3); // Normal
		vertexBufferLayout.Push<float>(2); // Texcoords
		vertexBuffer->SetVertexBufferLayout(vertexBufferLayout);
		vertexArray->AddVertexBuffer(vertexBuffer);

		std::vector<unsigned int> indices = GetIndices(mesh);

		std::shared_ptr<Rendering::IndexBuffer> indexBuffer;
		indexBuffer.reset(Rendering::IndexBuffer::Create(indices.data(), (uint32_t)indices.size()));

		vertexArray->SetIndexBuffer(indexBuffer);

		return vertexArray;
	}

	std::vector<MeshLoader::Vertex> MeshLoader::GetVertexInformation(aiMesh* mesh)
	{
		std::vector<Vertex> vertices; 

		// Process the mesh and collect the necessary data. 
		for (unsigned int i = 0; i < mesh->mNumVertices; ++i) { 
			// Place this data in a Vertex struct for easy overview.
			Vertex vertex; 

			// Process Vertex Position
			aiVector3D pos = mesh->mVertices[i]; 
			vertex.Position = { pos.x, pos.y, pos.z }; 

			// Process Vertex Normals
			aiVector3D norm = mesh->mNormals[i]; 
			vertex.Normals = { norm.x, norm.y, norm.z }; 

			if (mesh->mTextureCoords[0]) { 
				// Process Texture Coords
				aiVector3D texco = mesh->mTextureCoords[0][i]; 
				vertex.TextureCoords = { texco.x, texco.y }; 
			}
			else {
				vertex.TextureCoords = { 0.0, 0.0 }; 
			}

			// Place all the collected structs inside a vector.
			vertices.push_back(vertex); 
		}

		return vertices;
	}

	std::vector<unsigned int> MeshLoader::GetIndices(aiMesh* mesh)
	{
		std::vector<unsigned int> indices;

		for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
			aiFace face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; ++j) {
				indices.push_back(face.mIndices[j]);
			}
		}

		return indices;
	}
}