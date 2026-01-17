workspace "Anchor"
	architecture "x64"
	staticruntime "On"
	systemversion "latest"
	
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release"
	}

	buildoptions { "/utf-8" }

outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/"

IncludeDirs = {}

project "Anchor"
	location "Anchor"
	kind "StaticLib"
	language "C"
	cdialect "C11"

	targetdir(".bin/" .. outputDir .. "%{prj.name}/")
	objdir(".bin-int/" .. outputDir .. "%{prj.name}/")

	files
	{
		"%{prj.name}/include/**.h",

		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.c"
	}

	includedirs
	{
		"%{prj.name}/include"
	}

	defines
	{
	}

	filter "configurations:Debug"
		defines "ANCHOR_DEBUG"
		symbols "On"
		runtime "Debug"

	filter "configurations:Release"
		defines "ANCHOR_RELEASE"
		optimize "Speed"
		runtime "Release"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C"
	cdialect "C11"

	targetdir(".bin/" .. outputDir .. "%{prj.name}/")
	objdir(".bin-int/" .. outputDir .. "%{prj.name}/")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.c"
	}

	includedirs
	{
		"%{prj.name}/src",
		"Anchor/include"
	}

	links
	{
		"Anchor"
	}

	filter "configurations:Debug"
		defines "ANCHOR_DEBUG"
		symbols "On"
		runtime "Debug"

	filter "configurations:Release"
		defines "ANCHOR_RELEASE"
		optimize "Speed"
		runtime "Release"
