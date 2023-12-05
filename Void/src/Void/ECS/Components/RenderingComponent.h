#pragma once
#include "Void/Utils/Parser/ISerializable.h"

namespace Void {
	struct RenderingComponent : public ISerializable {

		//////////////////
		// Submesh
		struct Submesh : public ISerializable {
			std::string Model;
			std::vector<std::string> Textures;
			std::string Shader;

			nlohmann::ordered_json ToJSON() const override {
				nlohmann::ordered_json json;

				json["Model"] = Model;

				for (const std::string& texture : Textures)
					json["Texture"].push_back(texture);

				json["Shader"] = Shader;

				return json;
			}

			void FromJSON(const nlohmann::json& json) override {
				Model = json["Model"];
				for (const std::string& texture : json["Texture"])
					Textures.push_back(texture);
				Shader = json["Shader"];
			}
		};


		//////////////////
		// RenderingComponent

		std::vector<Submesh> Submeshes;
		bool DrawWireframe = false;
		bool Blending = false;

		nlohmann::ordered_json ToJSON() const override {
			nlohmann::ordered_json json;
			json["DrawWireframe"] = DrawWireframe;
			json["Blending"] = Blending;
			for (Submesh submesh : Submeshes)
				json["Submeshes"].push_back(submesh.ToJSON());
			return json;
		}

		void FromJSON(const nlohmann::json& json) override {
			DrawWireframe = json["DrawWireframe"];
			Blending = json["Blending"];
			for (const auto& sm : json["Submeshes"]) {
				Submesh submesh;
				submesh.FromJSON(sm);
				Submeshes.push_back(submesh);
			}
		}
	};
}