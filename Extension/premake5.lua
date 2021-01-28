project "CSGOExtension"
	kind "SharedLib"
	language "C++"
	cppdialect "C++14"
	staticruntime "on"

	targetname "jailbreak.ext"

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs
	{
		"src/",
		"../vendor/sourcemod/public/",
		"../vendor/sourcemod/public/Extension/",
		"../vendor/sourcemod/sourcepawn/include",
		"../vendor/hl2sdk-csgo/public",
		"../vendor/hl2sdk-csgo/public/engine",
		"../vendor/hl2sdk-csgo/public/game/server",
		"../vendor/hl2sdk-csgo/public/tier0",
		"../vendor/hl2sdk-csgo/public/tier1",
		"../vendor/sourcemod/public/amtl/amtl/",
		"../vendor/sourcemod/public/amtl/",
		"../vendor/metamod/core",
		"../vendor/metamod/core/sourcehook",
		"../vendor/sourcemod",
		"../vendor/sourcemod/core",
		"../vendor/hl2sdk-csgo/public/engine/protobuf",
		"../vendor/hl2sdk-csgo/common/protobuf-2.3.0/src"
	}

	links
	{
		"../vendor/hl2sdk-csgo/lib/public/interfaces.lib",
		"../vendor/hl2sdk-csgo/lib/public/tier0.lib",
		"../vendor/hl2sdk-csgo/lib/public/tier1.lib",
		"../vendor/hl2sdk-csgo/lib/public/vstdlib.lib"
	}
