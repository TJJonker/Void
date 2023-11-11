#pragma once

// Core
#include "Void/Core/Application.h"
#include "Void/Layers/Core/Layer.h"
#include "Void/ECS/Core/Scene/SceneManager.h"

// Debug
#include "Void/Debug/Log.h"

// Rendering Components
#include "Void/Rendering/Components/FrameBuffer/FrameBuffer.h"
#include "Void/Rendering/Components/FrameBuffer/FrameBufferConfig.h"
#include "Void/Rendering/Components/Texture/Texture.h"

// External
#include "Void/Utils/ExternalFiles/MeshLoader/MeshLoader.h"
#include "Void/Utils/ExternalFiles/File/File.h"
#include "Void/Utils/ExternalFiles/TextureLoader.h"

// Parsing
#include "Void/Utils/Parser/JSONParser.h"

// Rendering Pipeline
#include "Void/Rendering/Components/Renderer/RenderingCommands.h"

// Libraries
#include "Void/Rendering/Libraries/Mesh/MeshLibrary.h"
#include "Void/Rendering/Libraries/Shader/ShaderLibrary.h"
#include "Void/Rendering/Libraries/Texture/TextureLibrary.h"

// Built in Systems
#include "Void/ECS/Systems/RenderingSystem.h"
#include <Void/ECS/Systems/PhysicsSystem.h>

// Built in Components
#include "Void/ECS/Components/RenderingComponent.h"
#include "Void/ECS/Components/TranformComponent.h"
#include <Void/ECS/Components/LightComponent.h>
#include <Void/ECS/Components/SpotLightComponent.h>

#include "Void/Physics/CollisionPoints.h"

// Vendor
#include "assimp/scene.h"