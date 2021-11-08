local project_name = string.match(_MAIN_SCRIPT_DIR, ".*/([^/]+)") -- E:/repo/foobar -> foobar

print("Building Solution " .. project_name)

workspace (project_name)
  characterset ("MBCS")
  configurations { "Debug", "DebugConsole", "DebugFast", "Release" }
  startproject "app.parser"
  location ".build/projects"
  targetdir ".build/bin/%{cfg.buildcfg}"
  kind "StaticLib"
  language "C++"
  staticruntime "off"
  warnings "Off"
  architecture "x64"
  cppdialect "C++17"

  filter "action:vs*"
    disablewarnings {
      4018, -- '<': signed/unsigned mismatch
      4201, -- nonstandard extension used: nameless struct/union
      4244, -- conversion from 'int' to 'float', possible loss of data
      4245, -- conversion from 'int' to 'rose::hash_value', signed/unsigned mismatch
      4267, -- conversion from 'size_t' to 'int', possible loss of data
      4456, -- declaration of 'X' hides previous local declaration
      4458, -- declaration of 'X' hides class member
      4505, -- unreferenced local function has been removed
      4584, -- base-class 'XXX' is already a base-class of 'YYY'
      4996, -- 'fopen': This function or variable may be unsafe. Consider using fopen_s instead.
      26451, -- Arithmetic overflow: Using operator '*' on a 4 byte value and then casting the result to a 8 byte value.
      26812, -- The enum type 'XXX' is unscoped. Prefer 'enum class' over 'enum'

    }
    linkoptions {
      "/ignore:4006", -- F already defined in X.lib; second definition ignored
    }
    
  filter "configurations:Debug"
    defines { "DEBUG", "EA_DEBUG" }
    symbols "Full"
    optimize "Off"
    targetsuffix "-d"

  filter "configurations:DebugConsole"
    defines { "DEBUG", "EA_DEBUG" }
    symbols "Full"
    optimize "Off"
    targetsuffix "-d"

  filter "configurations:DebugFast"
    defines { "DEBUG", "EA_DEBUG" }
    symbols "Full"
    optimize "Size"
    targetsuffix "-df"

  filter "configurations:Release*"
    defines { "RELEASE", "NDEBUG" }
    symbols "Off"
    optimize "Size"

project "_root"
  configuration { "windows" }
  kind "None"
  files { "**" }
  removefiles { ".git/**" }
  removefiles { ".build/**" }
  removefiles { "externals/**" }
  removefiles { "**.cpp", "**.h", "**.c" }

project "app.parser"
  kind "ConsoleApp"
  warnings "Extra"
  debugdir "source/"
  debugargs { "--include", "parser.h" }
  targetname (project_name)
  files { "source/**" }

