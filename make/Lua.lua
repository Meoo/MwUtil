-- Variables:
--      LUA_DIR
--      LUA_INCLUDE_DIR
--      LUA_LIBS_DIR
-- Functions:
--      links_Lua()

-- LUA options
newoption {
  trigger     = "lua_directory",
  value       = "path",
  description = "Lua base directory (must contain include directory)"
}

newoption {
  trigger     = "lua_bin_directory",
  value       = "path",
  description = "[Optional] Lua build directory (must contains lib directory)"
}

if not _OPTIONS["lua_bin_directory"] then
  _OPTIONS["lua_bin_directory"] = _OPTIONS["lua_directory"] or ""
end

-- ///////////////////////////////////////////////////// --

-- LUA paths
LUA_DIR         = _OPTIONS["lua_directory"] or ""
LUA_INCLUDE_DIR = LUA_DIR .."/include"
LUA_LIBS_DIR    = _OPTIONS["lua_bin_directory"] .."/lib"

-- ///////////////////////////////////////////////////// --

-- LUA version/////////// --

if _OPTIONS["sfml_directory"] ~= "" then
  local m = os.matchfiles(LUA_INCLUDE_DIR .."/luaconf.h")
  if #m == 0 then
    print("Not a valid Lua include directory : ".. LUA_INCLUDE_DIR)
  end

  local m = os.matchfiles(LUA_LIBS_DIR .."/liblua.a")
  if #m == 0 then
    print("Lua library not found in directory : ".. LUA_LIBS_DIR)
  end
end

-- ///////////////////////////////////////////////////// --

-- LUA libraries
function links_Lua()
    links ("lua")
end
