workspace "Void"
	architecture "x64"

	configurations {
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Void"
	location "Void"
	kind "SharedLib"
	language "C++"
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs {
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			"VOID_PLATFORM_WINDOWS",
			"VOID_BUILD_DLL"
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

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"

	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs {
		"Void/vendor/spdlog/include",
		"Void/src"
	}

	links {
		"Void"
	}

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