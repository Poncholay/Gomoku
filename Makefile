##
## Makefile for Gomoku in /home/wilmot_g/Epitech/IA/Gomoku
##
## Made by wilmot_g
## Login   <wilmot_g@epitech.net>
##
## Started on  Sun Oct 16 15:28:11 2016 wilmot_g
## Last update Sun Oct 16 15:32:23 2016 wilmot_g
##

GENIE=	./lib/genie

all:
	@make --no-print-directory linux

linux:
	$(GENIE) --file=scripts/genie.lua gmake
	make -R -C build/projects/linux config=release64 verbose=y

.PHONY: clean fclean re

clean:
	@echo Cleaning...
	-@rm -rf obj

fclean: clean
	-@rm -rf build
	-@rm -f gomoku
	-@rm -f lib/libbgfx.a

re: fclean all
