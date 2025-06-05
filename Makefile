NAME = minishell

MAIN = main.c signal.c
BUILTINS = echo.c cd.c pwd.c export.c unset.c env.c exit.c
EXEC = exec.c builtin.c bin.c
ENV = env.c env_utils.c
<<<<<<< HEAD
PARSER = parser.c parser_utils.c shell_split.c validator.c tools.c
UTILS = ft_memcpy.c ft_split.c ft_strcmp.c ft_strdup.c ft_strjoin.c utils.c ft_strcpy.c ft_isalnum.c interpret.c
=======
PARSER = parser.c parser_utils.c shell_split.c validator.c
UTILS = ft_memcpy.c ft_split.c ft_strcmp.c ft_strdup.c ft_strjoin.c utils.c ft_strcpy.c ft_isalnum.c
EXPANDER = interpret.c
>>>>>>> 49ae3e12af2addab6dec13e7017bd30d328cb2fa

SRCS_DIR = src/
OBJS_DIR = objs/
INCLUDES_DIR = includes/

SRCS = \
        $(addprefix $(SRCS_DIR)main/, $(MAIN)) \
        $(addprefix $(SRCS_DIR)builtins/, $(BUILTINS)) \
        $(addprefix $(SRCS_DIR)exec/, $(EXEC)) \
        $(addprefix $(SRCS_DIR)env/, $(ENV)) \
        $(addprefix $(SRCS_DIR)utils/, $(UTILS)) \
        $(addprefix $(SRCS_DIR)expander/, $(EXPANDER)) \
        $(addprefix $(SRCS_DIR)parser/, $(PARSER))

OBJS = $(patsubst $(SRCS_DIR)%.c, $(OBJS_DIR)%.o, $(SRCS))

CC = cc
CFLAGS = -Wall -Wextra -Werror
LGFLAGS = -lreadline

all: $(NAME)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I $(INCLUDES_DIR) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LGFLAGS)

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

