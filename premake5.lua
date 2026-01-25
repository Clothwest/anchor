workspace "Anchor"
	architecture "x64"
	staticruntime "On"
	systemversion "latest"
	
	startproject "CSandbox"

	configurations
	{
		"Debug",
		"Release"
	}

	buildoptions { "/utf-8" }

OutputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/"
targetdir(".bin/" .. OutputDir .. "%{prj.name}/")
objdir(".bin-int/" .. OutputDir .. "%{prj.name}/")

filter "configurations:Debug"
	defines "ANCHOR_DEBUG"
	symbols "On"
	runtime "Debug"

filter "configurations:Release"
	defines "ANCHOR_RELEASE"
	optimize "Speed"
	runtime "Release"

filter {}

IncludeDirs = {}
IncludeDirs["Anchor"] = "%{wks.location}/Anchor/include"

include "Anchor"

group "Examples"
	include "Examples/Tloc"
	include "Examples/CppTest"
	include "Examples/CSandbox"
group ""
