workspace "Void Engine"
	architecture "x64"
	startproject "Chat_Client" 

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
includeDirs["GLM"] = "Void/vendor/GLM/include"
includeDirs["SPDLOG"] = "Void/vendor/SPDLOG/include"
includeDirs["VOID"] = "Void/src"

libraryDirs = {}

include "Void/vendor/GLFW"
include "Void/vendor/GLAD"
include "Void"
include "Sandbox"
