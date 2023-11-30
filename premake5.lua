workspace "Void Engine"
	architecture "x64"
	startproject "Nebula" 

	configurations {
		"Debug",
		"Release",
		"Dist"
	}

solutionDir = "%{wks.location}/"
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

includeDirs = {}
includeDirs["GLAD"] = "Void/vendor/GLAD/include"
includeDirs["GLFW"] = "Void/vendor/GLFW/include"
includeDirs["GLM"] = "Void/vendor/GLM"
includeDirs["SPDLOG"] = "Void/vendor/SPDLOG/include"
includeDirs["VOID"] = "Void/src"
includeDirs["ASSIMP"] = "Void/vendor/ASSIMP/include"
includeDirs["IMGUI"] = "Void/vendor/IMGUI"
includeDirs["NLOHMANN"] = "Void/vendor/NLOHMANN/single_include"
includeDirs["FMOD"] = "Void/vendor/FMOD/include"

libraryDirs = {}
libraryDirs["ASSIMP"] = "Void/vendor/ASSIMP/libs"
libraryDirs["FMOD"] = "Void/vendor/FMOD/lib"

include "Void/vendor/GLFW"
include "Void/vendor/GLAD"
include "Void/vendor/IMGUI"
include "Void"
include "Nebula"
