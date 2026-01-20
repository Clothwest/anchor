project "Tloc"
	kind "ConsoleApp"
	language "C"
	cdialect "C11"

	files
	{
		"src/**.h",
		"src/**.c"
	}

	includedirs
	{
		IncludeDirs["Anchor"]
	}

	links
	{
		"Anchor"
	}
