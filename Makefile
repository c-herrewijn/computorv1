NAME = computor
CXX = c++

# dev
# CXXFLAGS = -Wall -Wextra -Werror -Wconversion -std=c++11 -Wno-unused -Wno-unused-parameter
CXXFLAGS = -Wall -Wextra -Werror -Wconversion -std=c++11

SRC_DIR = src
OBJ_DIR = obj
INCL_DIR = src/include

SRCS = main.cpp polynomial.cpp term.cpp token.cpp utils.cpp
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.cpp=.o))


all: $(NAME)

# compiling
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) -c $(CXXFLAGS) $< -I$(INCL_DIR) -o $@

# linking
$(NAME): $(OBJS)
	$(CXX) $(OBJS) -o $(NAME)

debug: fclean
	$(MAKE) CXXFLAGS="$(CXXFLAGS) -g" $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

format:
	astyle --options=formatter.txt ./*.cpp,*.hpp

.PHONY: all debug clean fclean re format
