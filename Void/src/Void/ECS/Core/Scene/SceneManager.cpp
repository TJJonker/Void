#include "pch.h"
#include "SceneManager.h"
#include <Void/ECS/Components/TranformComponent.h>
#include <Void/ECS/Components/RenderingComponent.h>
#include <Void/ECS/Components/SpotLightComponent.h>
#include <Void/ECS/Components/PhysicsComponent.h>
#include <Void/ECS/Components/TagComponent.h>

namespace Void {

	SceneManager& SceneManager::GetInstance() {
		static SceneManager instance;
		return instance;
	}

	void SceneManager::LoadScene(const char* filePath)
	{
		Scene* scene = new Scene();

		// Get Scene Data
		std::string data = File::Read(filePath);
		// Go through entities 
		nlohmann::ordered_json sceneJson = nlohmann::json::parse(data);
		
		const nlohmann::json& entitiesArray = sceneJson["Entities"];

		for (const auto& entity : entitiesArray) {

			Entity* ent = scene->CreateEntity();

			const nlohmann::json& components = entity["Components"];
			
			for (const auto& component : components) {
					
				const std::string& type = component["Type"];

				ISerializable* c = DeserializeComponent(type, ent);
				c->FromJSON(component["Data"]);
			}
		}
		m_CurrentScene = scene;
	}

	void SceneManager::SaveScene(const char* filePath)
	{
		nlohmann::ordered_json sceneJson;
		std::vector<Entity*> entities = m_CurrentScene->GetAllEntities();

		// TODO: Remove this when entities have a name
		unsigned int index = 0;

		std::vector<Entity*>::const_reverse_iterator it;  
		for (it = entities.rbegin(); it != entities.rend(); it++) {
			const Entity* entity = *it;

			nlohmann::ordered_json entityJson; // Describes the Entity

			std::string name = "Entity_" + std::to_string(index);
			entityJson["Name"] = name; 

			if (entity->HasComponent<TransformComponent>()) {
				nlohmann::ordered_json componentJson; 
				TransformComponent& transform = entity->GetComponent<TransformComponent>();
				componentJson["Type"] = "TransformComponent";
				componentJson["Data"] = transform.ToJSON();

				entityJson["Components"].push_back(componentJson);
			}

			if (entity->HasComponent<RenderingComponent>()) {
				nlohmann::ordered_json componentJson;

				RenderingComponent& rendering = entity->GetComponent<RenderingComponent>();
				componentJson["Type"] = "RenderingComponent";
				componentJson["Data"] = rendering.ToJSON();

				entityJson["Components"].push_back(componentJson);
			}

			if (entity->HasComponent<SpotLightComponent>()) {
				nlohmann::ordered_json componentJson;

				SpotLightComponent& rendering = entity->GetComponent<SpotLightComponent>();
				componentJson["Type"] = "SpotLightComponent";
				componentJson["Data"] = rendering.ToJSON();

				entityJson["Components"].push_back(componentJson);
			}

			if (entity->HasComponent<PhysicsComponent>()) {
				nlohmann::ordered_json componentJson;

				PhysicsComponent& rendering = entity->GetComponent<PhysicsComponent>();
				componentJson["Type"] = "PhysicsComponent";
				componentJson["Data"] = rendering.ToJSON();

				entityJson["Components"].push_back(componentJson);
			}

			if (entity->HasComponent<TagComponent>()) {
				nlohmann::ordered_json componentJson;

				TagComponent& rendering = entity->GetComponent<TagComponent>();
				componentJson["Type"] = "TagComponent";
				componentJson["Data"] = rendering.ToJSON();

				entityJson["Components"].push_back(componentJson);
			}

			
			sceneJson["Entities"].push_back(entityJson);
			index++;

		}

		File::Write(filePath, sceneJson.dump(4).c_str());
	}

	ISerializable* SceneManager::DeserializeComponent(std::string componentName, Entity* entity)
	{
		if(componentName == "TransformComponent")
			return &entity->AddComponent<TransformComponent>();
		if (componentName == "RenderingComponent")
			return &entity->AddComponent<RenderingComponent>();
		if (componentName == "SpotLightComponent")
			return &entity->AddComponent<SpotLightComponent>();
		if (componentName == "PhysicsComponent")
			return &entity->AddComponent<PhysicsComponent>();
		if (componentName == "TagComponent")
			return &entity->AddComponent<TagComponent>();

		VOID_ASSERT(false, "Component does not exist");
		return nullptr;
	}
}