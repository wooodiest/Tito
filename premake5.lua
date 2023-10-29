workspace "Tito"
architecture "x64"
	startproject "Tito"
	configurations
	{
		"Debug",
		"Release"
	}

	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Tito"
	location "Tito"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++14"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"Dependencies/SDL2/include"
	}

	libdirs 
	{
		"Dependencies/SDL2/lib/x64"
	}

	links
	{
		"SDL2.lib",
		"SDL2main.lib",
		"SDL2_image.lib",
		"SDL2_ttf.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"PROJECT_PLATFORM_WINDOWS",
			"WIN32"
		}

	filter "configurations:Debug"
		defines "PROJECT_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "PROJECT_RELEASE"
		runtime "Release"
		optimize "on"