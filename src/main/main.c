/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 19:27:30 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/25 18:05:23 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdbool.h>

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
	if (!ns_validate(input))
	{
		shell->exec_result = 2;
		free(input);
		return ;
	}
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
	close_pipes(&shell->mfd);
	shell->cmd_ptr = NULL;
}

char	*get_prompt(void)
{
	char	*cwd;
	char	*prefix;
	char	*tmp;
	char	*prompt;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (NULL);
	prefix = ft_strjoin("minishell@\001\033[0;34m\002", cwd);
	free(cwd);
	tmp = ft_strjoin(prefix, " > ");
	free(prefix);
	prompt = ft_strjoin("\001\033[0;32m\002", tmp);
	free(tmp);
	tmp = prompt;
	prompt = ft_strjoin(tmp, "\001\033[0m\002");
	free(tmp);
	return (prompt);
}



static void	listen(t_shell *shell)
{
	int			last_code;
	char		*input;
	char		*prompt;

	while (1)
	{
		set_interactive_signals();
		prompt = get_prompt();
		input = readline(prompt);
		free(prompt);
		set_execution_signals();
		if (g_last_status == 130)
		{
			shell->exec_result = g_last_status;
			g_last_status = 0;
		}
		if (input == NULL)
		{
			last_code = shell->exec_result;
			cleanup(shell);
			exit(last_code);
		}
		if (input[0] != '\0')
			process_cmd(input, shell);
		else
			free(input);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	shell.exec_result = 0;
	shell.cmd_ptr = NULL;
	init_env_list(&shell, env);
	update_shlvl(shell.env_list);
	setup_signals();
	listen(&shell);
	safe_shell_exit(NULL, &shell);
	return ((void)argc, (void)argv, 0);
}
