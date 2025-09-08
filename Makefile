NAME = computor
CXX = c++

CPP_FLAGS = -Wall -Wextra -Werror -std=c++11

SRC_DIR = src
OBJ_DIR = obj
INCL_DIR = src/include

SRCS = main.cpp polynomial.cpp
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
