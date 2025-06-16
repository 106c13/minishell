/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 18:20:38 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/15 17:08:02 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	write_heredoc(int write_fd, char *delimiter, t_shell *shell)
{
	char	*line;
	char	*tmp;
	char	expand;

	expand = !has_quotes(delimiter);
	delimiter = clear_quotes(delimiter);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		if (expand && str_contains(line, '$'))
		{
			tmp = line;
			line = replace_env_vars(shell, line, 0);
			free(tmp);
		}
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
	close(write_fd);
	exit(0);
}

int	process_heredoc(char *delimiter, t_shell *shell)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		close(pipefd[0]);
		close(pipefd[1]);
		return (-1);
	}
	if (pid == 0)
	{
		set_default_signals();
		close(pipefd[0]);
		write_heredoc(pipefd[1], delimiter, shell);
	}
	else
	{
		close(pipefd[1]);
		waitpid(pid, &status, 0);
		set_exec_result(shell, status);
		if (shell->exec_result == 130)
			return (close(pipefd[0]), -1);
		if (shell->exec_result == SUCCESS)
			return (pipefd[0]);
		close(pipefd[0]);
	}
	return (-1);
}
