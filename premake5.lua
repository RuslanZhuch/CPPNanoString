-- premake5.lua
workspace "CPPNanoString"
    architecture "x64"
    configurations { "Debug", "Release" }

project "Tests"
    location "tests"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++latest"
    targetdir "bin/%{cfg.buildcfg}"

    files { "tests/includes/**.h", "tests/sources/**.cpp", "includes/**.h" }

    includedirs {
        "tests/includes",
        "includes",
    }

    libdirs {
        "tests/libs/gtests/Debug"
    }

    links {
        "gtest_main",
        "gtest",
    }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"
        runtime "Debug"
        staticruntime "On"

        flags { "MultiProcessorCompile" }

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
        runtime "Release"
        staticruntime "On"

        flags { "MultiProcessorCompile" }

    filter { "action:vs2022" }
        buildoptions { "/MP" }

