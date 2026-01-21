project "CppTest"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs
	{
		IncludeDirs["Anchor"]
	}

	links
	{
		"Anchor"
	}
