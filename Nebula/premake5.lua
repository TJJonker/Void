project "Nebula"
	kind "ConsoleApp"
	language "C++"
	dependson { "Void" }

	targetdir (solutionDir .. "/bin/" .. outputdir .. "/%{prj.name}")
	objdir (solutionDir .. "/bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"src/**.cpp",
		"src/**.h"
	}

	includedirs {
		"src",
		solutionDir .. "%{includeDirs.VOID}",
		solutionDir .. "%{includeDirs.SPDLOG}",
		solutionDir .. "%{includeDirs.GLM}",
		solutionDir .. "%{includeDirs.GLAD}",
		solutionDir .. "%{includeDirs.IMGUI}",
		solutionDir .. "%{includeDirs.ASSIMP}",
		solutionDir .. "%{includeDirs.NLOHMANN}",
		solutionDir .. "%{includeDirs.IMGUIZMO}"	
	}

	libdirs {
		solutionDir .. "/bin/" .. outputdir .. "/%{prj.name}",
		solutionDir .. "%{libraryDirs.IMGUIZMO}"
	}

	links {
		"Void",
		"ImGui",
		"ImGuizmo.lib"
	}

	defines { }

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			"VOID_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "VOID_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "VOID_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "VOID_DIST"
		optimize "On"
	
