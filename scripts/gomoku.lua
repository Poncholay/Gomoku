--
-- gomoku.lua for Gomoku in /home/wilmot_g/Epitech/IA/Gomoku/scripts
--
-- Made by wilmot_g
-- Login   <wilmot_g@epitech.net>
--
-- Started on  Sun Oct 16 17:48:12 2016 wilmot_g
-- Last update Mon Nov 14 17:40:16 2016 Adrien Milcent
--

function gomoku_project(_kind)

	project ("gomoku")
		kind (_kind)

		includedirs {
			GOMOKU_DIR .. "inc",
			GOMOKU_DIR .. "inc/Irrlicht",
			GOMOKU_DIR .. "inc/Menu",
			GOMOKU_DIR .. "inc/SDL"
		}

		linkoptions {
			"-O3 -Wl,-rpath,../../../lib/Linux"
		}
 		-- -pg

		links {
			GOMOKU_LIB_DIR .. "Linux/Irrlicht",
			"nanovg",
			"GL",
			"GLU",
			"m",
			"GLEW",
			"glfw",
			"X11",
			"Xxf86vm",
			"pthread",
			"SDL2",
			"SDL2_mixer-2.0"
		}

		files {
			GOMOKU_DIR .. "inc/**.hh",
			GOMOKU_DIR .. "inc/**.hpp",
			GOMOKU_DIR .. "src/**.cpp"
		}
end
