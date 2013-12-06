
-- Output directories option
newoption {
  trigger     = "output_directory",
  value       = "path",
  description = "[Default=bin] Output directory for the executable"
}

if not _OPTIONS["output_directory"] then
  _OPTIONS["output_directory"] = "bin"
end

-- Static or shared library
newoption {
  trigger     = "mw_shared",
  value       = "bool",
  description = "[Default=false] Build MwUtils as a shared library",
  allowed = {
    { "true",   "Build as a shared library" },
    { "false",  "Build as a static library" },
  }
}

-- GNU GProf option
newoption {
  trigger     = "gprof",
  value       = "bool",
  description = "[Default=false] Enable GNU Profiler file generation",
  allowed = {
    { "true",   "GNU Profiler enabled" },
    { "false",  "GNU Profiler disabled" },
  }
}

-- Static stdlib linkage option
newoption {
  trigger     = "stdlib_static",
  value       = "bool",
  description = "[Default=false] Enable static linking of standard libraries",
  allowed = {
    { "true",   "Static linking of stdlib enabled" },
    { "false",  "Static linking of stdlib disabled" },
  }
}

-- ///////////////////////////////////////////////////// --

-- Lua directories and configuration
--dofile "make/Lua.lua"

-- Boost directories and configuration
dofile "make/Boost.lua"

-- ///////////////////////////////////////////////////// --

function bool_default(value, default)
  if not value then return default end
  if value:lower() == "true" then return true end
  if value:lower() == "false" then return false end
  error (value.." is not a valid boolean value")
end

-- Output directories
local BIN_DIR       = _OPTIONS["output_directory"]
local OBJ_DIR       = BIN_DIR.."/obj"
local MAKE_DIR      = BIN_DIR.."/make"

-- MwUtil
local MW_SHARED     = bool_default(_OPTIONS["mw_shared"], false)
local MW_KIND       = MW_SHARED and "SharedLib" or "StaticLib"
local MW_SUFFIX     = MW_SHARED and "" or "-s"

-- Enable profiling with gprof on GNU GCC
local GPROF         = bool_default(_OPTIONS["gprof"], false)

-- Enable static linking of stdlib
local STDLIB_STATIC = bool_default(_OPTIONS["stdlib_static"], false)

-- ///////////////////////////////////////////////////// --

solution "MwUtil"
  configurations { "Debug", "Release" }

  targetdir(BIN_DIR)
  objdir   (OBJ_DIR)

  flags { "ExtraWarnings", "FatalWarnings", "NoPCH" }
  
  if STDLIB_STATIC then
    flags { "StaticRuntime" }
  end
  
  if GPROF then
    configuration "GMake"
      buildoptions { "-pg" }
      linkoptions  { "-pg" }
  end

  configuration "Debug"
    flags { "Symbols" }

  configuration "Release"
    flags   { "Optimize" }
    defines { "NDEBUG" }

-- ///////////////////////////////////////////////////// --

project "Test"
  language "C++"
  location (MAKE_DIR)
  kind     "ConsoleApp"

  BOOST_LIBS = { "unit_test_framework" }

  files       { "test/Mw/**.cpp" }
  includedirs { "src" }

  use_Boost ( BOOST_LIBS )
