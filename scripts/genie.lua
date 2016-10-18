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
GOMOKU_LIB_DIR  = (GOMOKU_DIR .. "lib/")
GOMOKU_BUILD_DIR  = (GOMOKU_DIR .. "build/")

function copyLib()
end

solution "Gomoku"
configurations {
  "release"
}

platforms {
  "x64"
}

language "C++"

configuration {}

dofile ("gomoku.lua")
dofile ("options.lua")

options(GOMOKU_BUILD_DIR);

group "game"
gomoku_project("ConsoleApp")

postbuildcommands {
  "mv " .. path.getabsolute(".") .. "/gomoku " .. GOMOKU_DIR,
}
