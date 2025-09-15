#include "minishell.h"
#include "minishell.h"
#include "parser.h"
#include "tokenizer.h"
#include "exec.h"
#include "enviroment.h"
#include "expander.h"
#include "get_next_line.h"

void	init_session(t_shell *shell)
{
	int		fd;
	char	*line;
	t_token	*tokens;
	t_ast	*ast;

	fd = open(".minishellrc", O_RDONLY);
	if (fd == -1)
		return ;
	line = get_next_line(fd);
	while (line)
	{
		tokens = tokenize(line);
    	tokens = expand_aliases(tokens, shell->aliases);
		if (!check_token_array(tokens))
		{
			free(tokens);
			continue ;
		}
		ast = build_ast(tokens);
		free(line);
		if (ast)
			shell->exec_result = execute_node(ast, shell);
		free(ast);
	}
}
