workspace "BadKey"

    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Distribution"
    }

outputPath = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Game"

    location "Game"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputPath .. "/%{prj.name}")
    objdir ("bin-int/" .. outputPath .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "BadKey/src"
    }

    links
    {
        "BadKey"
    }

    filter "system:windows"
    
        defines
        {
            "BK_PLATFORM_WINDOWS"
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

project "BadKey"

    location "BadKey"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputPath .. "/%{prj.name}")
    objdir ("bin-int/" .. outputPath .. "/%{prj.name}")

    pchheader "bkpch.h"
    pchsource "BadKey/src/bkpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "BadKey/src"
    }

    defines
    {
        "BK_BUILD_DLL"
    }

    filter "system:windows"

        defines
        {
            "BK_PLATFORM_WINDOWS"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputPath .. "/Game")
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