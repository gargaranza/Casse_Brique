# Compiler
CC = g++

# Compiler flags
CFLAGS = -std=c++20 -Wall -Wextra

# SDL flags
SDLFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lX11

# Source files
SRCS = main.cpp paddle.cpp squareBloc.cpp grid.cpp ballManager.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
EXEC = casse_brique

# Target
all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC) $(SDLFLAGS)

main.o: main.cpp global.h bloc.hpp blocType.hpp ballType.hpp paddle.hpp rectanglePaddle.hpp blocContainer.hpp squareBloc.hpp grid.hpp ball.hpp ballManager.hpp
	$(CC) $(CFLAGS) -c $(SRCS)

# Clean
clean:
	rm -f $(OBJS) $(EXEC)
