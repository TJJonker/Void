project "Quantum"
	kind "StaticLib"
	language "C++"

	targetdir ("lib")
	objdir (solutionDir .. "/bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "QuantumPch.h"
	pchsource "src/QuantumPch.cpp" 

	files {
		"include/**.h",
		"src/**.cpp"
	}

	includedirs {
		"src",
		solutionDir .. "%{includeDirs.SPDLOG}",
		solutionDir .. "%{includeDirs.GLM}"
	}

	libdirs {
	}

	links {
	}


	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"
		staticruntime "on"

		defines {
		}

	filter "configurations:Debug"
		defines "QUANTUM_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "QUANTUM_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "QUANTUM_DIST"
		optimize "On"
	
