NAME = minishell

MAIN = \
	main.c signal.c
LEXER = \
	tokenizer.c tokenizer_utils.c \
	token_utils.c
PARSER = \
	ast.c ast_utils.c
EXECUTOR = \
	exec.c exec_utils.c redirection_utils.c
EXECUTOR_BUILTINS = \
	cd.c echo.c exit.c pwd.c export.c env.c \
	alias.c
ENVIROMENT = \
	env.c
EXPANDER = \
	expand.c expand_utils.c expand_aliases.c
UTILS = \
	string_utils.c ft_strcmp.c \
	skip_utils.c ft_memcpy.c \
	ft_calloc.c ft_bzero.c \
	error_utils.c ft_strdup.c \
	ft_strchr.c ft_strjoin.c \
	ft_strlen.c ft_isalnum.c \
	ft_itoa.c free_utils.c \
	ft_isalpha.c utils.c \
	dict_utils.c ft_strcpy.c \
	multiline_utils.c array_utils.c
UTILS_SPLIT = \
	split.c split_utils.c
GET_NEXT_LINE = \
	get_next_line.c get_next_line_utils.c

SRCS_DIR = src/
OBJS_DIR = objs/
INCLUDES_DIR = includes/

SRCS = \
	$(addprefix $(SRCS_DIR)main/, $(MAIN)) \
	$(addprefix $(SRCS_DIR)lexer/, $(LEXER)) \
	$(addprefix $(SRCS_DIR)parser/, $(PARSER)) \
	$(addprefix $(SRCS_DIR)executor/, $(EXECUTOR)) \
	$(addprefix $(SRCS_DIR)executor/builtins/, $(EXECUTOR_BUILTINS)) \
	$(addprefix $(SRCS_DIR)enviroment/, $(ENVIROMENT)) \
	$(addprefix $(SRCS_DIR)expander/, $(EXPANDER)) \
	$(addprefix $(SRCS_DIR)utils/, $(UTILS)) \
	$(addprefix $(SRCS_DIR)utils/split/, $(UTILS_SPLIT)) \
	$(addprefix $(SRCS_DIR)get_next_line/, $(GET_NEXT_LINE))

OBJS = $(patsubst $(SRCS_DIR)%.c, $(OBJS_DIR)%.o, $(SRCS))

CC = cc
CFLAGS = -Wall -Wextra -Werror
#CFLAGS = -g3 -fsanitize=address

# Detect OS
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Darwin)
	# macOS specific paths (Homebrew readline)
	LGFLAGS = -L/opt/homebrew/opt/readline/lib -lreadline
	CFLAGS += -I/opt/homebrew/opt/readline/include
else
	# Linux default
	LGFLAGS = -lreadline
endif

# ✨ Colors
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
RED = \033[1;31m
PURPLE = \033[1;35m
CYAN = \033[1;36m
RESET = \033[0m

# 🧱 Build Rules
all: $(NAME)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(dir $@)
	@echo "$(CYAN)[Compiling]$(RESET) $<"
	@$(CC) $(CFLAGS) -I $(INCLUDES_DIR) -c $< -o $@

$(NAME): $(OBJS)
	@echo "$(YELLOW)🔧 Linking objects...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LGFLAGS)
	@echo "$(GREEN)✅ Build complete: ./$(NAME)$(RESET)"
	@echo "$(GREEN) ███▄ ▄███▓ ██▓ ███▄    █  ██▓  ██████  ██░ ██ ▓█████  ██▓     ██▓    $(RESET)"
	@sleep 0.07
	@echo "$(GREEN)▓██▒▀█▀ ██▒▓██▒ ██ ▀█   █ ▓██▒▒██    ▒ ▓██░ ██▒▓█   ▀ ▓██▒    ▓██▒    $(RESET)"
	@sleep 0.07
	@echo "$(GREEN)▓██    ▓██░▒██▒▓██  ▀█ ██▒▒██▒░ ▓██▄   ▒██▀▀██░▒███   ▒██░    ▒██░    $(RESET)"
	@sleep 0.07
	@echo "$(GREEN)▒██    ▒██ ░██░▓██▒  ▐▌██▒░██░  ▒   ██▒░▓█ ░██ ▒▓█  ▄ ▒██░    ▒██░    $(RESET)"
	@sleep 0.07
	@echo "$(GREEN)▒██▒   ░██▒░██░▒██░   ▓██░░██░▒██████▒▒░▓█▒░██▓░▒████▒░██████▒░██████▒$(RESET)"
	@sleep 0.07
	@echo "$(GREEN)░ ▒░   ░  ░░▓  ░ ▒░   ▒ ▒ ░▓  ▒ ▒▓▒ ▒ ░ ▒ ░░▒░▒░░ ▒░ ░░ ▒░▓  ░░ ▒░▓  ░$(RESET)"
	@sleep 0.07
	@echo "$(GREEN)░  ░      ░ ▒ ░░ ░░   ░ ▒░ ▒ ░░ ░▒  ░ ░ ▒ ░▒░ ░ ░ ░  ░░ ░ ▒  ░░ ░ ▒  ░$(RESET)"
	@sleep 0.07
	@echo "$(GREEN)░      ░    ▒ ░   ░   ░ ░  ▒ ░░  ░  ░   ░  ░░ ░   ░     ░ ░     ░ ░   $(RESET)"
	@sleep 0.07
	@echo "$(GREEN)       ░    ░           ░  ░        ░   ░  ░  ░   ░  ░    ░  ░    ░  ░$(RESET)"
	@sleep 0.07
	@echo "$(PURPLE)                   🔥 MADE BY: Arseniy & Hakob 🔥$(RESET)"

clean:
	@rm -rf $(OBJS_DIR)
	@echo "$(RED)🧹 Objects cleaned!$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)🔥 $(NAME) removed!$(RESET)"

re: fclean all

.PHONY: all clean fclean re

