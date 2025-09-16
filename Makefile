NAME = computor
CXX = c++

# dev
# CPP_FLAGS = -Wall -Wextra -Werror -std=c++11 -Wno-unused -Wno-unused-parameter

CPP_FLAGS = -Wall -Wextra -Werror -std=c++11

SRC_DIR = src
OBJ_DIR = obj
INCL_DIR = src/include

SRCS = main.cpp polynomial.cpp token.cpp utils.cpp
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.cpp=.o))


all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CPP_FLAGS) $(OBJS) -I$(INCL_DIR) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) -c $(CPP_FLAGS) $< -I$(INCL_DIR) -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

format:
	astyle --options=formatter.txt ./*.cpp,*.hpp

.PHONY: all clean fclean re format
