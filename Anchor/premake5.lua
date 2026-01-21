project "Anchor"
	kind "StaticLib"
	language "C"
	cdialect "C11"

	files
	{
		"include/**.h",

		"src/**.h",
		"src/**.c"
	}

	includedirs
	{
		"include"
	}
