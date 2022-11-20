NAME	=	Containers
CC		=	c++
CFLAGS	=	-Wall -Wextra -Werror -std=c++98
RM		=	rm -f
 
SRCS	=	main_ft.cpp
SRCS_STD	=	main_std.cpp
 
INC		=	iterators.hpp \
			set_tree.hpp \
			utility.hpp \
			vector.hpp \
			set_tree.hpp \
			set.hpp \
			map.hpp \
			map_tree.hpp \
			stack.hpp
 
OBJ		=	$(SRCS:.cpp=.o)
OBJ_STD		=	$(SRCS_STD:.cpp=.o)
%.o		:	%.cpp
			$(CC) $(CFLAGS) -c $< -o $@
$(NAME)	:	$(OBJ) $(INC) $(OBJ_STD)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJ) ; $(CC) $(CFLAGS) -o $(NAME)_std $(OBJ_STD)
all		:	$(NAME)
clean	:
			$(RM) $(OBJ) $(OBJ_STD)
fclean	:	clean
			$(RM) $(NAME) $(NAME)_std
re		:	fclean all
.PHONY	:	all clean fclean re bonus