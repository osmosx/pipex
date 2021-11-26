NAME = pipex
#
FLAGS = -Wall -Werror -Wextra
#
HEADER = pipex.h
#
SRCS 	= 	minilib.c\
			ft_split.c\
			check_path.c\
			pipex.c
#
OBJS = $(SRCS:.c=.o)
#
.PHONY: all re clean fclean
#
%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -c $<
#
all: $(NAME)
	@echo "\033[32m\033[40m\033[1m[Pipex Compiled]"
#
$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $@
#
clean:
	${RM} $(OBJS)
#
fclean: clean
	${RM} $(NAME)
#
re: fclean all

