#include "pch.h"
#include "SceneManager.h"
#include <Void/ECS/Components/TranformComponent.h>
#include <Void/ECS/Components/RenderingComponent.h>

namespace Void {
	void SceneManager::LoadScene(const char* filePath)
	{
		Scene* scene = new Scene();

		// Get Scene Data
		std::string data = File::Read(filePath);
		// Go through entities 
		nlohmann::ordered_json sceneJson = nlohmann::json::parse(data);
		
		const nlohmann::json& entitiesArray = sceneJson["Entities"];

		for (const auto& entity : entitiesArray) {

			entt::entity ent = scene->CreateEntity();

			const nlohmann::json& components = entity["Components"];
			
			for (const auto& component : components) {
					
				const std::string& type = component["Type"];
				if (type == "TransformComponent") {
					TransformComponent& tc = scene->AddComponent<TransformComponent>(ent);
					tc.FromJSON(component["Data"]);
					continue;
				}
				
				if (type == "RenderingComponent") {
					RenderingComponent& rc = scene->AddComponent<RenderingComponent>(ent);
					rc.FromJSON(component["Data"]);
					continue;
				}

			}
		}

		m_CurrentScene = scene;
			// Get Entity name 

			// Get Components
				// Go through components 
					// Add them to the new entity
						// Set the data inside the component
	}

	void SceneManager::SaveScene(const char* filePath)
	{
		nlohmann::ordered_json sceneJson;
		std::vector<entt::entity> entities = m_CurrentScene->GetAllEntities();
		entt::registry& reg = m_CurrentScene->Registry();

		// TODO: Remove this when entities have a name
		unsigned int index = 0;

		std::vector<entt::entity>::const_reverse_iterator it;  
		for (it = entities.rbegin(); it != entities.rend(); it++) {
			const entt::entity entity = *it;

			nlohmann::ordered_json entityJson; // Describes the Entity

			std::string name = "Entity_" + std::to_string(index);
			entityJson["Name"] = name; 


			if (m_CurrentScene->HasComponent<TransformComponent>(entity)) {
				nlohmann::ordered_json componentJson; 
				
				TransformComponent& transform = m_CurrentScene->GetComponent<TransformComponent>(entity);
				componentJson["Type"] = "TransformComponent";
				componentJson["Data"] = transform.ToJSON();

				entityJson["Components"].push_back(componentJson);
			}

			if (m_CurrentScene->HasComponent<RenderingComponent>(entity)) {
				nlohmann::ordered_json componentJson;

				RenderingComponent& rendering = m_CurrentScene->GetComponent<RenderingComponent>(entity);
				componentJson["Type"] = "RenderingComponent";
				componentJson["Data"] = rendering.ToJSON();

				entityJson["Components"].push_back(componentJson);
			}

			
			sceneJson["Entities"].push_back(entityJson);
			index++;

		}

		File::Write(filePath, sceneJson.dump(4).c_str());
	}
}