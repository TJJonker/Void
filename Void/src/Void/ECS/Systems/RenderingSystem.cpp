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

namespace Void::Rendering {
	void RenderingSystem::Update(entt::registry& registry)
	{
		for (entt::entity ent : registry.view<TransformComponent, RenderingComponent>()) {
			RenderingComponent& rendering = registry.get<RenderingComponent>(ent);
			TransformComponent& transform = registry.get<TransformComponent>(ent);

			// TODO: expand so multiple submeshes can be rendered
			// TODO: Pass the strings so the Rendering Pipeline can load everything
			if (rendering.Submeshes.size()) {
				const std::string& textureName = rendering.Submeshes[0].Textures[0];
				Texture* texture = Void::TextureLibrary::GetInstance()->Get(textureName.c_str());

				const std::string& meshName = rendering.Submeshes[0].Model;
				Mesh* mesh = Void::MeshLibrary::GetInstance()->Get(meshName.c_str());
				VertexArray* vertexArray = mesh->Submeshes[0];

				const std::string& shaderName = rendering.Submeshes[0].Shader;
				Shader* shader = Void::ShaderLibrary::GetInstance()->Get(shaderName.c_str());

				shader->Bind();
				shader->SetInt("texture1", 0);
				glActiveTexture(GL_TEXTURE0);
				texture->Bind();


				// Remove as well
				if(rendering.DrawWireframe)
					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				else 
					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 

				Rendering::RenderingCommands::Draw(vertexArray, shader, transform.GetTransformMatrix());
			}
		}
	}
}