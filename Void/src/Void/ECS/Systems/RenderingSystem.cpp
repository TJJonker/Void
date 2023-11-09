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

			glm::mat4 model = glm::mat4(1.0f);

			model = glm::translate(model, transform.Position);
			//model = glm::rotate(model, glm::radians(45.f), glm::vec3(0.f, 1.f, 0.f));
			model = glm::scale(model, transform.Scale);

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

				Rendering::RenderingCommands::Draw(vertexArray, shader, model);
			}
		}
	}
}