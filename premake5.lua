workspace "Imagelyn"

    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Distribution"
    }

outputPath = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Imagelyn"

    location "Imagelyn"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputPath .. "/%{prj.name}")
    objdir ("bin-int/" .. outputPath .. "/%{prj.name}")

    cppdialect "C++17"

    pchheader "imagelynpch.h"
    pchsource "Imagelyn/src/imagelynpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/data/*.txt"
    }

    includedirs
    {
        "Imagelyn/src"
    }

    filter "configurations:Debug"
        defines { "BK_DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "BK_RELEASE" }
        optimize "On"

    filter "configurations:Distribution"
        defines { "BK_DISTRIBUTION" }
        optimize "On"

    filter { "system:windows" }
        defines { "PLATFORM_WINDOWS" }

    filter { "system:macosx" }
        defines { "PLATFORM_MACOSX" }