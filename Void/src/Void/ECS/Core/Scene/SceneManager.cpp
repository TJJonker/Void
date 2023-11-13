#include "pch.h"
#include "SceneManager.h"
#include <Void/ECS/Components/TranformComponent.h>
#include <Void/ECS/Components/RenderingComponent.h>
#include <Void/ECS/Components/LightComponent.h>
#include <Void/ECS/Components/SpotLightComponent.h>
#include <Void/ECS/Components/PhysicsComponent.h>
#include <Void/ECS/Components/TagComponent.h>

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

				ISerializable* c = DeserializeComponent(type, scene, ent);
				c->FromJSON(component["Data"]);
			}
		}
		m_CurrentScene = scene;
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

			if (m_CurrentScene->HasComponent<LightComponent>(entity)) {
				nlohmann::ordered_json componentJson;

				LightComponent& rendering = m_CurrentScene->GetComponent<LightComponent>(entity);
				componentJson["Type"] = "LightComponent";
				componentJson["Data"] = rendering.ToJSON();

				entityJson["Components"].push_back(componentJson);
			}

			if (m_CurrentScene->HasComponent<SpotLightComponent>(entity)) {
				nlohmann::ordered_json componentJson;

				SpotLightComponent& rendering = m_CurrentScene->GetComponent<SpotLightComponent>(entity);
				componentJson["Type"] = "SpotLightComponent";
				componentJson["Data"] = rendering.ToJSON();

				entityJson["Components"].push_back(componentJson);
			}

			if (m_CurrentScene->HasComponent<PhysicsComponent>(entity)) {
				nlohmann::ordered_json componentJson;

				PhysicsComponent& rendering = m_CurrentScene->GetComponent<PhysicsComponent>(entity);
				componentJson["Type"] = "PhysicsComponent";
				componentJson["Data"] = rendering.ToJSON();

				entityJson["Components"].push_back(componentJson);
			}

			if (m_CurrentScene->HasComponent<TagComponent>(entity)) {
				nlohmann::ordered_json componentJson;

				TagComponent& rendering = m_CurrentScene->GetComponent<TagComponent>(entity);
				componentJson["Type"] = "TagComponent";
				componentJson["Data"] = rendering.ToJSON();

				entityJson["Components"].push_back(componentJson);
			}

			
			sceneJson["Entities"].push_back(entityJson);
			index++;

		}

		File::Write(filePath, sceneJson.dump(4).c_str());
	}

	ISerializable* SceneManager::DeserializeComponent(std::string componentName, Scene* scene, entt::entity entity)
	{
		if(componentName == "TransformComponent")
			return &scene->AddComponent<TransformComponent>(entity);
		if (componentName == "RenderingComponent")
			return &scene->AddComponent<RenderingComponent>(entity);
		if (componentName == "LightComponent")
			return &scene->AddComponent<LightComponent>(entity);
		if (componentName == "SpotLightComponent")
			return &scene->AddComponent<SpotLightComponent>(entity);
		if (componentName == "PhysicsComponent")
			return &scene->AddComponent<PhysicsComponent>(entity);
		if (componentName == "TagComponent")
			return &scene->AddComponent<TagComponent>(entity);

		VOID_ASSERT(false, "Component does not exist");
		return nullptr;
	}
}