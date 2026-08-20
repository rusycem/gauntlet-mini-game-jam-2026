# The binary this exercise builds
NAME := hello

# Compiler and the gauntlet's mandatory flags
CXX := g++
CXXFLAGS := -Wall -Wextra -Werror -std=c++17

# List every .cpp file in the exercise here
SRCS := main.cpp
OBJS := $(SRCS:.cpp=.o)

# `make` / `make all`: build the binary
all: $(NAME).exe

$(NAME).exe: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME).exe

# Compile each .cpp into a .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# `make clean`: remove object files
clean:
	cmd /c del /q /f $(OBJS)

# `make fclean`: remove objects AND the binary
fclean: clean
	cmd /c del /q /f $(NAME).exe

# `make re`: rebuild everything from scratch
re: fclean all

.PHONY: all clean fclean re
