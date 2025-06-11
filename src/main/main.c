/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 19:27:30 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/11 17:37:35 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void collect_finished_jobs(t_shell *shell)
{
	t_job *curr = shell->job_list;
	t_job *prev = NULL;
	int status;
	pid_t result;

	while (curr)
	{
		result = waitpid(curr->pid, &status, WNOHANG);
		if (result > 0)
		{
			printf("[%d] Done\t{command}\n", curr->id);
			if (prev)
				prev->next = curr->next;
			else
				shell->job_list = curr->next;
			//free(curr->cmd_str);
			t_job *to_free = curr;
			free(to_free);
		}
		else
			prev = curr;
		curr = curr->next;
	}
}


// ===========================================================





/*
 * Function that listens user's commads
 */
static void	listen(t_shell *shell)
{
	char		*input;
	t_command	*cmd;

	while (1)
	{
		collect_finished_jobs(shell);
		set_interactive_signals();
		input = readline("\001\033[0;32m\002minishell > \001\033[0m\002");
		set_execution_signals();
		if (!input) // Ctrl-D
		{
			free(input);
			safe_shell_exit(NULL, shell);
		}
		if (input[0] != '\0')
		{
			add_history(input);
			cmd = parse_command(input);
			free(input);
			if (cmd == NULL) // give parsing error to user
				continue ;
			exec_cmd(cmd, shell);
		}
	}
}

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	init_env_list(&shell, env);
	setup_signals();
	listen(&shell);
	return ((void)argc, (void)argv, 0);
}
