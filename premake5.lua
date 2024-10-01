workspace "BadKey"

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

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    defines
    {
        "BK_BUILD_DLL"
    }

    postbuildcommands
    {
        ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputPath .. "/Imagelyn")
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