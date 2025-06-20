/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 18:20:38 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/20 18:54:06 by azolotar         ###   ########.fr       */
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
		{
			printerr_three("minishell: warning: here-document \
			delimited by end-of-file (wanted `", delimiter, "`)");
			break ;
		}
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
	free(delimiter);
	cleanup(shell);
	exit(0);
}

int	pipe_error(int *pipefd)
{
	perror("fork");
	close(pipefd[0]);
	close(pipefd[1]);
	return (-1);
}

/* no if for pid > 0 cause of norminette */
int	process_heredoc(char *delimiter, t_shell *shell)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;

	if (pipe(pipefd) == -1)
		return (perror("pipe"), -1);
	pid = fork();
	if (pid == -1)
		return (pipe_error(pipefd));
	if (pid == 0)
	{
		set_default_signals();
		close(pipefd[0]);
		write_heredoc(pipefd[1], ft_strdup(delimiter), shell);
		return (-1);
	}
	close(pipefd[1]);
	waitpid(pid, &status, 0);
	set_exec_result(shell, status);
	if (shell->exec_result == 130)
		return (close(pipefd[0]), -1);
	if (shell->exec_result == SUCCESS)
		return (pipefd[0]);
	close(pipefd[0]);
	return (-1);
}

int	exec_heredocs(t_command *cmd, t_shell *shell)
{
	int	i;
	int	curr_pipe;

	i = 0;
	while (i < cmd->delimiter_count)
	{
		curr_pipe = process_heredoc(cmd->delimiters[i], shell);
		i++;
		if (curr_pipe == -1)
			return (-1);
		if (i == cmd->delimiter_count)
			return (curr_pipe);
		else
			close(curr_pipe);
	}
	return (curr_pipe);
}
