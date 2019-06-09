NAME = a.out
CC = clang++
# CFLAGS = -Werror -Wall -Wextra
CFLAGS = -g -std=c++98
INC = -Iinclude
LIB = -lncurses
BG_SND_PATH = $(realpath ./media/background.mov)
FIRE_SND_PATH = $(realpath ./media/shooty.mov)

OS := $(shell uname)

SRC := $(shell find ./src -type f -name "*.cpp")
OBJ := $(SRC:%.cpp=%.o)
DEP := $(OBJ:%.o=%.d)

all : $(NAME) author

author :
	@echo "wseegers" > author

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(INC) -o $@ $^ $(LFLAGS) $(LIB)

%.o : %.cpp
	$(CC) -DBGSOUND='"$(BG_SND_PATH)"' -DFSOUND='"$(FIRE_SND_PATH)"' $(CFLAGS) $(INC) -MMD -c $< -o $@

-include $(DEP)

clean :
	rm -rf $(OBJ) $(DEP)

fclean : clean
	rm -f $(NAME)

re : fclean all

run : all
	./$(NAME)

.PHONEY : all clean  fclean  re
