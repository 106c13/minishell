NAME = minishell

SRCS = src/main.c src/signal.c src/env.c src/ft_split.c src/ft_strdup.c src/ft_strcmp.c \
	src/utils.c src/ft_memcpy.c src/ft_strjoin.c

OBJDIR = objs

OBJS = $(SRCS:src/%.c=$(OBJDIR)/%.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror

LGFLAGS = -lreadline

all: $(NAME)

$(OBJDIR)/%.o: src/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LGFLAGS)

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -f $(OBJS)
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

