--
-- options.lua for Gomoku in /home/wilmot_g/Epitech/IA/Gomoku/scripts
--
-- Made by wilmot_g
-- Login   <wilmot_g@epitech.net>
--
-- Started on  Sun Oct 16 18:14:01 2016 wilmot_g
-- Last update Mon Nov 14 17:39:31 2016 Adrien Milcent
--

function options()

  if (_ACTION == nil) then return end

	if _ACTION == "gmake" then

    location(GOMOKU_BUILD_DIR .. "projects/" .. "linux")

    configuration { "x64" }
        --flags { "Symbols" }
    		targetdir (GOMOKU_DIR)
    		objdir (GOMOKU_BUILD_DIR .. "linux64" .. "/obj")
    		libdirs (GOMOKU_BUILD_DIR .. "../",
        GOMOKU_BUILD_DIR .. "../lib/Linux")
        buildoptions {
        			"-Wextra",
        			"-Werror",
				      "-pthread",
				      "-std=c++11",
              "-DNANOVG_GLEW",
              "-O3"
        		}
  end
end
