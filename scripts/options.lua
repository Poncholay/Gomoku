--
-- options.lua for Gomoku in /home/wilmot_g/Epitech/IA/Gomoku/scripts
--
-- Made by wilmot_g
-- Login   <wilmot_g@epitech.net>
--
-- Started on  Sun Oct 16 18:14:01 2016 wilmot_g
-- Last update Sun Oct 16 18:14:01 2016 wilmot_g
--

function options()

  if (_ACTION == nil) then return end

	if _ACTION == "gmake" then

    location(GOMOKU_BUILD_DIR .. "projects/" .. "linux")

    configuration { "x64", "linux-*" }
    		targetdir (GOMOKU_BUILD_DIR .. "linux64" .. "/bin")
    		objdir (GOMOKU_BUILD_DIR .. "linux64" .. "/obj")
    		libdirs (GOMOKU_BUILD_DIR .. "../.build/linux64/bin")
        buildoptions {
        			"-Wall",
        			"-Wextra",
        			"-Werror",
              "-pthread"
        		}
        		buildoptions_cpp {
        			"-std=c++11",
        		}
        		-- linkoptions {
        		-- 	"-Wl,-rpath=\\$$ORIGIN",
        		-- 	"-Wl,--no-as-needed",
        		-- }
  end
end
