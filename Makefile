NAME = minishell

MAIN = \
	main.c signal.c
EXEC = \
	exec.c builtin.c bin.c \
	heredoc.c utils.c job_manager.c \
	helpers.c heredoc_utils.c
ENV = \
	env_init.c env_utils.c env_helpers.c \
	shlvl.c
EXPANDER = \
	expander.c expand_utils.c \
	wildcard.c args.c norm.c
VALIDATOR = \
	ns_validator.c ops.c \
	redirects.c brackets.c \
	not_req_chars.c cmd_subst.c \
	quotes.c paren_check.c \
	paren_check_utils.c
BUILTINS = \
	echo.c cd.c pwd.c \
	export.c unset.c env.c \
	exit.c
PARSER = \
	parser.c parser_utils.c \
	shell_split.c \
	tools.c counter.c helpers.c \
	parser_utils1.c 
UTILS = \
	ft_memcpy.c ft_split.c ft_strcmp.c \
	ft_strdup.c ft_strjoin.c utils.c \
	ft_strcpy.c ft_isalnum.c ft_atoi.c \
	ft_itoa.c fd_utils.c str_utils.c \
	ft_strchr.c ft_substr.c ft_strlen.c \
	ft_putstr_fd.c printerr.c free_cmd.c \
	ft_memset.c fd_utils_helper.c ft_isspace.c
SUBSHELL = \
	subshell.c ss_utils.c utils.c

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
	$(addprefix $(SRCS_DIR)parser/, $(PARSER)) \
	$(addprefix $(SRCS_DIR)subshell/, $(SUBSHELL)) \
	$(addprefix $(SRCS_DIR)validator/, $(VALIDATOR))

OBJS = $(patsubst $(SRCS_DIR)%.c, $(OBJS_DIR)%.o, $(SRCS))

CC = cc
CFLAGS = -Wall -Wextra -Werror # -g3 -fsanitize=address

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

