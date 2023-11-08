#include "pch.h"
#include "RenderingSystem.h"
#include <Void/ECS/Components/TranformComponent.h>
#include <Void/ECS/Components/RenderingComponent.h>
#include <glm/gtc/matrix_transform.hpp>
#include <Void/Rendering/Components/Renderer/RenderingCommands.h>

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

			/*if (rendering.Submeshes.size()) {
				std::shared_ptr<Shader> shader = rendering.Submeshes[0]->Shader;
				std::shared_ptr<Texture> texture = rendering.Submeshes[0]->Textures[0];
				std::shared_ptr<Rendering::VertexArray> vertexArray = rendering.Submeshes[0]->VertexArray;

				shader->Bind();
				shader->SetInt("texture1", 0);
				glActiveTexture(GL_TEXTURE0);
				texture->Bind();

				Rendering::RenderingCommands::Draw(vertexArray, shader, model);
			}*/
		}
	}
}