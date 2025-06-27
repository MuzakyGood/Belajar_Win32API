G++ = g++
SRC = $(wildcard src/*.cpp)
FLAG = -Wall -std=c++23
EXEC = bin/main
RUNAPP = ./$(wildcard bin/*.exe)
REMOVEAPP = rm -rf bin/*.exe


all:
	@$(REMOVEAPP)
	@$(G++) $(SRC) $(FLAG) -o $(EXEC)
	@$(RUNAPP)

debug:
	$(REMOVEAPP)
	$(G++) $(SRC) $(FLAG) -o $(EXEC)

clean:
	@$(REMOVEAPP)