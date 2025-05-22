NAME=minishell

SRCS=main.c signal.c env.c ft_split.c ft_strdup.c#commands.c

OBJS=$(SRCS:.c=.o)

CC=cc

CFLAGS=-Wall -Wextra -Werror 

LGFLAGS=-lreadline

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LGFLAGS)

clean:
	rm -f $(OBJS) 

fclean: clean
	rm -f $(NAME)

re: fclean all 

.PHONY: all clean fclean re 
