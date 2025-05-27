NAME = minishell

MAIN = main.c signal.c
BUILTINS = echo.c cd.c pwd.c export.c unset.c env.c exit.c
EXEC = exec.c builtin.c bin.c
ENV = env.c
UTILS = ft_memcpy.c ft_split.c ft_strcmp.c ft_strdup.c ft_strjoin.c utils.c

SRCS_DIR = src/
INCLUDES_DIR = includes/

SRCS = \
	$(addprefix $(SRCS_DIR), $(addprefix main/, $(MAIN))) \
	$(addprefix $(SRCS_DIR), $(addprefix builtins/, $(BUILTINS))) \
	$(addprefix $(SRCS_DIR), $(addprefix exec/, $(EXEC))) \
	$(addprefix $(SRCS_DIR), $(addprefix env/, $(ENV))) \
	$(addprefix $(SRCS_DIR), $(addprefix utils/, $(UTILS))) 

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror
LGFLAGS = -lreadline

# --- Rules ---
all: $(NAME)

$(OBJS): %.o : %.c 
	$(CC) $(CFLAGS) -I $(INCLUDES_DIR) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LGFLAGS)

clean:
	rm -f $(OBJS)
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
