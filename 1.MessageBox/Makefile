NAME_APP = main
PATH_EXE = ./bin/
G++ = g++
SRC = $(wildcard src/*.cpp)
FLAG = -Wall -std=c++23 -o
MAKEDIR = mkdir
REMOVE = rm -rf


all:
	@$(REMOVE) $(PATH_EXE)
	@$(MAKEDIR) $(PATH_EXE)
	@$(G++) $(SRC) $(FLAG) $(PATH_EXE)$(NAME_APP)
	@$(PATH_EXE)$(NAME_APP)

debug:
	$(REMOVE) $(PATH_EXE)
	$(MAKEDIR) $(PATH_EXE)
	$(G++) $(SRC) $(FLAG) $(PATH_EXE)$(NAME_APP)

clean:
	@$(REMOVE) $(PATH_EXE)