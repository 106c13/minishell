#include <unistd.h>
#include "defines.h"

void	syntax_error(int type)
{
	char	*body;

	body = "minishell: syntax error near unexpected token ";
	write(STDERR_FILENO, body, 46);
	if (type == AND)
		write(STDERR_FILENO, "&&", 2);
	if (type == OR)
		write(STDERR_FILENO, "||", 2);
	if (type == RPAREN)
		write(STDERR_FILENO, ")", 1);
	if (type == LPAREN)
		write(STDERR_FILENO, "(", 1);
	if (type == SEMI)
		write(STDERR_FILENO, ";", 1);
	if (type == PIPE)
		write(STDERR_FILENO, "|", 1);
	write(STDERR_FILENO, "\n", 1);
}
