#pragma once

// Core
#include "Void/Core/Application.h"
#include "Void/Layers/Core/Layer.h"

// Debug
#include "Void/Debug/Log.h"

// Rendering Components
#include "Void/Rendering/Components/FrameBuffer/FrameBuffer.h"
#include "Void/Rendering/Components/FrameBuffer/FrameBufferConfig.h"
#include "Void/Rendering/Components/Texture/Texture.h"

// External
#include "Void/Utils/ExternalFiles/ModelLoader.h"
#include "Void/Utils/ExternalFiles/File.h"
#include "Void/Utils/ExternalFiles/TextureLoader.h"

// Parsing
#include "Void/Utils/Parser/JSONParser.h"

// Rendering Pipeline
#include "Void/Rendering/Components/Renderer/RenderingCommands.h"

// Built in Systems
#include "Void/ECS/Systems/RenderingSystem.h"

// Built in Components
#include "Void/ECS/Components/RenderingComponent.h"
#include "Void/ECS/Components/TranformComponent.h"

// Vendor
#include "assimp/scene.h"