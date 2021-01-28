workspace "CSGOExtension"
	architecture "x86"

	filter "system:windows"
		systemversion "latest"
		defines
		{
			"PLATFORM_WINDOWS"
		}

	filter {}

	runtime "Release"
	optimize "on"

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"WIN32",
		"NDEBUG",
		"_WINDOWS",
		"_USRDLL",
		"SDK_EXPORTS",
		"_CRT_SECURE_NO_DEPRECATE",
		"SOURCEMOD_BUILD",
		"COMPILER_MSVC",
		"COMPILER_MSVC32",
		"SOURCE_ENGINE=12"
	}

	configurations
	{
		"Release",
	}

	flags
	{
		"MultiProcessorCompile"
	}

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
	targetdir("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

include "Extension"
