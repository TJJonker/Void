project "ImGuizmo"
	kind "StaticLib"
	staticruntime "On"
	language "C++"
	cppdialect "C++17"

	targetdir ("lib")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	includedirs {
		solutionDir .. "%{includeDirs.IMGUI}"
	}

	files
	{
		"*.h",
		"*.cpp"
	}

	filter "system:windows"
		systemversion "latest"


	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
