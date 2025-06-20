/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 19:27:30 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/20 14:40:56 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_mfd(t_mfd *mfd)
{
	mfd->in_fd = -1;
	mfd->out_fd = -1;
	mfd->s_in_fd = -1;
	mfd->s_out_fd = -1;
	mfd->pipefd[0] = -1;
	mfd->pipefd[1] = -1;
	mfd->hd_fd = -1;
	mfd->is_redirected = -1;
}

static void	sueta(t_command *cmd, t_shell *shell)
{
	while (cmd)
	{
		cmd->heredoc_fd = exec_heredocs(cmd, shell);
		cmd = cmd->next;
	}
}

static void	process_cmd(char *input, t_shell *shell)
{
	t_command	*cmd;

	add_history(input);
	cmd = parse_command(input);
	free(input);
	if (cmd == NULL)
		return ;
	shell->cmd_ptr = cmd;
	init_mfd(&shell->mfd);
	sueta(cmd, shell);
	shell->depth = 0;
	start_exec(cmd, shell);
	free_cmd_list(cmd);
	shell->cmd_ptr = NULL;
}

static void	listen(t_shell *shell)
{
	char	*input;

	while (1)
	{
		set_interactive_signals();
		input = readline("\001\033[0;32m\002minishell > \001\033[0m\002");
		set_execution_signals();
		if (g_last_status == 130)
		{
			shell->exec_result = g_last_status;
			g_last_status = 0;
		}
		if (input == NULL)
			safe_shell_exit(NULL, shell);
		if (input[0] != '\0')
			process_cmd(input, shell);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;
	shell.exec_result = 0;
	init_env_list(&shell, env);
	update_shlvl(shell.env_list);
	setup_signals();
	listen(&shell);
	safe_shell_exit(NULL, &shell);
	return ((void)argc, (void)argv, 0);
}
