# Compiler
CC = g++

# Compiler flags
CFLAGS =  -std=c++20 -Wall -Wextra -I /usr/include/SDL2

# SDL flags
SDLFLAGS = -lSDL2

# Source files
SRCS = main.cpp squareBloc.cpp grid.cpp ball.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
EXEC = casse_brique

# Target
all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC) $(SDLFLAGS)

main.o: main.cpp bloc.hpp blocType.hpp ballType.hpp blocContainer.hpp squareBloc.hpp grid.hpp ball.hpp
	$(CC) $(CFLAGS) -c $(SRCS)

# Clean
clean:
	rm -f $(OBJS) $(EXEC)
