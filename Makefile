NAME = minishell

FILES = main.c signal.c env.c ft_split.c \
		ft_strdup.c ft_strcmp.c cmd_arseniy.c \
		utils.c ft_memcpy.c ft_strjoin.c exit.c

SRCS_DIR=./src/

SRCS=$(addprefix $(SRCS_DIR), $(FILES))

OBJS_DIR=./obj/

OBJS=$(addprefix $(OBJS_DIR), $(FILES:.c=.o))

INCLUDES_DIR=./includes/

CC = cc

CFLAGS = -Wall -Wextra -Werror

LGFLAGS = -lreadline

# RULES
all: ./obj $(NAME)

./obj:
	mkdir -p $(OBJS_DIR)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	$(CC) $(CFLAGS) -I $(INCLUDES_DIR) -o $@ -c $<

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LGFLAGS)

clean:
	rm -f $(OBJS)
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
