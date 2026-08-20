# The binary this exercise builds
NAME := game

# Automatically detect OS
ifeq ($(OS),Windows_NT)
    EXT := .exe
    DEL := cmd /c del /q /f
    LDFLAGS := -lraylib -lgdi32 -lwinmm
else
    EXT :=
    DEL := rm -f
    LDFLAGS := -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
endif

# Compiler and the gauntlet's mandatory flags
CXX      := g++
CXXFLAGS := -Wall -Wextra -Werror -std=c++17

# List EVERY .cpp file here! I added Player.cpp
SRCS := main.cpp Player.cpp FallingItem.cpp
OBJS := $(SRCS:.cpp=.o)

# make / make all: build the binary
all: $(NAME)$(EXT)

$(NAME)$(EXT): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)$(EXT) $(LDFLAGS)

# Compile each .cpp into a .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# make clean: remove object files
clean:
	$(DEL) $(OBJS)

# make fclean: remove objects AND the binary
fclean: clean
	$(DEL) $(NAME)$(EXT)

# make re: rebuild everything from scratch
re: fclean all

.PHONY: all clean fclean re
