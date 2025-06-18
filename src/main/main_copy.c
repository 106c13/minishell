/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 19:27:30 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/18 17:29:28 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		i = 0;
char	*inputs[2];

void	init_mfd(t_mfd *mfd)
{
		mfd->in_fd = -1;
		mfd->out_fd = -1;
		mfd->pipefd[0] = -1;
		mfd->pipefd[1] = -1;
}

static void	listen(t_shell *shell)
{
	char		*input;
	t_command	*cmd;

	while (1)
	{
		set_interactive_signals();
//		input = readline("\001\033[0;32m\002minishell > \001\033[0m\002");
		input = inputs[i];
		i++;
		getchar();
		set_execution_signals();
		if (g_last_status == 130)
		{
			shell->exec_result = g_last_status;
			g_last_status = 0;
		}
		if (input == NULL)
			safe_shell_exit(NULL, shell);
		if (input[0] != '\0')
		{
//			add_history(input);
			cmd = parse_command(input);
			free(input);
			if (cmd == NULL)
				continue ;
			shell->cmd_ptr = cmd;
			init_mfd(&shell->mfd);
			shell->depth = 0;
			start_exec(cmd, shell);
			free_cmd_list(cmd);
			shell->cmd_ptr = NULL;
		}
	}
}

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	inputs[0] = ft_strdup("cat << end1 <<end2 <<end3");
	inputs[1] = NULL;
	init_env_list(&shell, env);
	setup_signals();
	listen(&shell);
	safe_shell_exit(NULL, &shell);
	return ((void)argc, (void)argv, 0);
}
