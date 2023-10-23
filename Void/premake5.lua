project "Void"
	kind "SharedLib"
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
		solutionDir .. "%{includeDirs.GLM}"
	}

	libdirs {
		solutionDir .. "%{libraryDirs.GLFW}",
	}

	links {
		"GLFW",
		"opengl32",
		"GLAD"
	}


	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"
		staticruntime "off"
		runtime "Debug"

		defines {
			"VOID_PLATFORM_WINDOWS",
			"VOID_BUILD_DLL",
			"VOID_ASSERT_ENABLED"
		}

		postbuildcommands {
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
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
	
