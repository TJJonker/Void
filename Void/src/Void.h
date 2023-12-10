#pragma once

// Core
#include "Void/Core/Application.h"
#include "Void/Layers/Core/Layer.h"
#include "Void/ECS/Core/Scene/SceneManager.h"
#include "Void/Core/Input.h"
#include "Void/Utils/TimeSteps/Time.h"

// Debug
#include "Void/Debug/Log.h"

// Rendering Components
#include "Void/Rendering/Components/FrameBuffer/FrameBuffer.h"
#include "Void/Rendering/Components/FrameBuffer/FrameBufferConfig.h"
#include "Void/Rendering/Components/Texture/Texture.h"

// External
#include "Void/Utils/ExternalFiles/MeshLoader/MeshLoader.h"
#include "Void/Utils/ExternalFiles/File/File.h"
#include "Void/Utils/ExternalFiles/TextureLoader/TextureLoader.h"

// Parsing
#include "Void/Utils/Parser/JSONParser.h"

// Rendering Pipeline
#include "Void/Rendering/Components/Renderer/RenderingCommands.h"

// Libraries
#include "Void/Rendering/Libraries/Mesh/MeshLibrary.h"
#include "Void/Rendering/Libraries/Shader/ShaderLibrary.h"
#include "Void/Rendering/Libraries/Texture/TextureLibrary.h"

// Built in Systems
#include "Void/ECS/Systems/Rendering/RenderingSystem.h"
#include "Void/ECS/Systems/Physics/PhysicsSystem.h"

// Built in Components
#include "Void/ECS/Components/RenderingComponent.h"
#include "Void/ECS/Components/TranformComponent.h"
#include <Void/ECS/Components/PointLightComponent.h>
#include <Void/ECS/Components/SpotLightComponent.h>
#include <Void/ECS/Components/TagComponent.h>
#include <Void/ECS/Components/Physics/BoxCollider3DComponent.h>
#include "Void/Physics/CollisionPoints.h"

// Vendor
#include "assimp/scene.h"

// Physics Solvers
#include "Void/Physics/Solvers/Position/PositionSolver.h"
#include "Void/Physics/Solvers/Impulse/ImpulseSolver.h"

#include "Void/Utils/Math/Math.h"

#include <Quantum/Quantum.h>