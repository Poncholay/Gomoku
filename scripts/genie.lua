--
-- genie.lua for Gomoku in /home/wilmot_g/Epitech/IA/Gomoku/scripts
--
-- Made by wilmot_g
-- Login   <wilmot_g@epitech.net>
--
-- Started on  Sun Oct 16 17:34:45 2016 wilmot_g
-- Last update Sun Oct 16 17:34:45 2016 wilmot_g
--

GOMOKU_DIR = (path.getabsolute("..") .. "/")
local GOMOKU_LIB_DIR  = (GOMOKU_DIR .. "lib/")
local GOMOKU_BUILD_DIR  = (GOMOKU_DIR .. "build/")
local GOMOKU_GAME_DIR = (GOMOKU_DIR .. "game/")
BGFX_DIR = (GOMOKU_LIB_DIR .. "bgfx/")
BX_DIR = (GOMOKU_LIB_DIR .. "bx/")

function copyLib()
end

solution "Gomoku"
configurations {
  "debug",
  "release"
}

platforms {
  "x64"
}

language "C++"

configuration {}

dofile (BGFX_DIR .. "scripts/bgfx.lua")
dofile ("gomoku.lua")
dofile ("options.lua")

options(GOMOKU_BUILD_DIR);

group "libs"
bgfxProject("", "StaticLib", os.is("windows") and { "BGFX_CONFIG_RENDERER_DIRECT3D9=1" } or {})

group "game"
gomoku_project("ConsoleApp")

postbuildcommands {
  "mv " .. path.getabsolute(".") .. "/gomoku " .. GOMOKU_DIR,
  "mv " .. path.getabsolute(".") .. "/libbgfx.a " .. GOMOKU_LIB_DIR
}
