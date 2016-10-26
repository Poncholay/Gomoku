--
-- gomoku.lua for Gomoku in /home/wilmot_g/Epitech/IA/Gomoku/scripts
--
-- Made by wilmot_g
-- Login   <wilmot_g@epitech.net>
--
-- Started on  Sun Oct 16 17:48:12 2016 wilmot_g
-- Last update Sun Oct 16 17:48:12 2016 wilmot_g
--

function gomoku_project(_kind)

	project ("gomoku")
		kind (_kind)

		includedirs {
			GOMOKU_DIR .. "inc",
			GOMOKU_DIR .. "inc/irrlicht"
		}

		defines {
			_defines,
		}

		links {
			GOMOKU_LIB_DIR .. "Linux/Irrlicht",
			"GL",
			"X11",
			"Xxf86vm",
			"pthread"
		}

		configuration {}

		files {
			GOMOKU_DIR .. "inc/**.hh",
			GOMOKU_DIR .. "inc/**.hpp",
			GOMOKU_DIR .. "src/**.cpp"
		}

		configuration {} -- reset configuration
end
