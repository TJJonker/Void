#include "pch.h"
#include "SceneManager.h"
#include <Void/ECS/Components/TranformComponent.h>
#include <Void/ECS/Components/RenderingComponent.h>

namespace Void {
	void SceneManager::LoadScene(const char* filePath)
	{
		// Get Scene Data
		std::string data = File::Read(filePath);
		// Go through entities 
		
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

		// TODO: Remove this
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