project "Void"
	kind "StaticLib"
	language "C++"

	targetdir (solutionDir .. "/bin/" .. outputdir .. "/%{prj.name}")
	objdir (solutionDir .. "/bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "src/pch.cpp" 

	files {
		"src/**.h",
		"src/**.cpp"
	}

	includedirs {
		"src",
		solutionDir .. "%{includeDirs.SPDLOG}",
		solutionDir .. "%{includeDirs.GLFW}",
		solutionDir .. "%{includeDirs.GLAD}",
		solutionDir .. "%{includeDirs.GLM}",
		solutionDir .. "%{includeDirs.ASSIMP}",
		solutionDir .. "%{includeDirs.IMGUI}",
		solutionDir .. "%{includeDirs.NLOHMANN}",
		solutionDir .. "%{includeDirs.FMOD}",
		solutionDir .. "%{includeDirs.IMGUIZMO}",
		solutionDir .. "%{includeDirs.QUANTUM}"
	}

	libdirs {
		solutionDir .. "%{libraryDirs.ASSIMP}",
		solutionDir .. "%{libraryDirs.FMOD}",
		solutionDir .. "%{libraryDirs.IMGUIZMO}",
		solutionDir .. "%{libraryDirs.QUANTUM}"
	}

	links {
		"GLFW",
		"opengl32",
		"GLAD",
		"assimp-vc143-mtd.lib",
		"ImGui",
		"fmod_vc.lib",
		"fmodL_vc.lib",
		"ImGuizmo.lib",
		"Quantum.lib"
	}


	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"
		staticruntime "on"

		defines {
			"VOID_PLATFORM_WINDOWS",
			"VOID_BUILD_DLL",
			"VOID_ASSERT_ENABLED",
			"VOID_AUDIO_FMOD"
		}

		prebuildcommands {
			("{COPY} vendor/ASSIMP/libs/assimp-vc143-mtd.dll " .. solutionDir .. "bin/" .. outputdir .. "/%{prj.name}"),
			("{COPY} vendor/FMOD/lib/fmod.dll " .. solutionDir .. "bin/" .. outputdir .. "/%{prj.name}")
		}

		postbuildcommands {
			-- "call CreateDir.bat ../bin/" .. outputdir .. "/Sandbox",
			"call CreateDir.bat ../bin/" .. outputdir .. "/Nebula",
			
			-- ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox"),			
			-- ("{COPY} ../bin/" .. outputdir .. "/%{prj.name}/assimp-vc143-mtd.dll ../bin/" .. outputdir .. "/Sandbox"),	

			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Nebula"),			
			("{COPY} ../bin/" .. outputdir .. "/%{prj.name}/assimp-vc143-mtd.dll ../bin/" .. outputdir .. "/Nebula"),	
			("{COPY} ../bin/" .. outputdir .. "/%{prj.name}/fmod.dll ../bin/" .. outputdir .. "/Nebula")	
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
	
