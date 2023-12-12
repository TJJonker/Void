#include "pch.h"
#include "RenderingSystem.h"
#include <Void/ECS/Components/TranformComponent.h>
#include <Void/ECS/Components/RenderingComponent.h>
#include <glm/gtc/matrix_transform.hpp>
#include <Void/Rendering/Components/Renderer/RenderingCommands.h>
#include <Void/Rendering/Components/Texture/Texture.h>
#include <Void/Rendering/Libraries/Texture/TextureLibrary.h>
#include <Void/Rendering/Libraries/Mesh/MeshLibrary.h>
#include <Void/Rendering/Libraries/Shader/ShaderLibrary.h>
#include "Void/ECS/Core/Scene/Scene.h"

namespace Void::Rendering {
	void RenderingSystem::Update(Scene* scene)
	{
		for (Entity* ent : scene->GetAllEntitesWith<TransformComponent, RenderingComponent>()) {
			RenderingComponent& rendering = ent->GetComponent<RenderingComponent>();
			TransformComponent& transform = ent->GetComponent<TransformComponent>();

			// TODO: expand so multiple submeshes can be rendered
			// TODO: Pass the strings so the Rendering Pipeline can load everything
			if (rendering.Submeshes.size() <= 0)
				continue;

			// TODO: Klopt niks van... Hoezo zitten er submeshes in het model en klooien we hier ook met submeshes...?
			for (RenderingComponent::Submesh submesh : rendering.Submeshes) {
				Mesh* mesh = Void::MeshLibrary::GetInstance()->Get(submesh.Model.c_str());
				VertexArray* vertexArray = mesh->Submeshes[0];

				const std::string& shaderName = rendering.Submeshes[0].Shader;
				if(rendering.Blending)
					Rendering::RenderingCommands::SubmitBlended(vertexArray, transform.GetTransformMatrix(), submesh.Textures, submesh.Shader);
				else
					Rendering::RenderingCommands::Submit(vertexArray, transform.GetTransformMatrix(), submesh.Textures, submesh.Shader, !rendering.DrawWireframe);
			}
		}
	}
}