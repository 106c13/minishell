/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 18:20:38 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/11 19:35:16 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static volatile sig_atomic_t	g_interrupted = 0;

static void	heredoc_sigint(int sig)
{
	(void)sig;
	g_interrupted = 1;
	write(1, "\n", 1);
}

static int	is_quoted(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == '\'' || *str == '"')
			return (1);
		str++;
	}
	return (0);
}

static void	child_heredoc(char *delimiter, t_command *cmd, int heredoc[2], t_shell *shell)
{
	char	*line;
	char	*tmp;
	char	expand;

	signal(SIGINT, heredoc_sigint);
	signal(SIGQUIT, SIG_IGN);
	close(heredoc[0]);
	expand = !is_quoted(delimiter);
	g_interrupted = 0;
	while (!interrupted)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		if (expand)
		{
			tmp = line;
			line = replace_env_vars(shell, line, 0, shell->env_list);
			free(tmp);
		}
		write(heredoc[1], line, ft_strlen(line));
		write(heredoc[1], "\n", 1);
		free(line);
	}
	close(heredoc[1]);
	if (g_interrupted)
		exit(130);
	else
		exit(0);
}

static int	parent_heredoc(t_command *cmd, int heredoc[2])
{
	int	status;

	close(heredoc[1]);
	waitpid(-1, &status, 0);

}

int	heredoc(char *delimeter, t_command *cmd, t_shell *shell)
{
	int	pid;
	int	heredoc[2];

	if (pipe(heredoc) == -1)
		exit(1);
	pid = fork();
	if (pid == -1)
		exit(1);
	else if (pid == 0)
	{
		child_heredoc(cmd, heredoc, shell);
	}
	else if (pid > 0)
	{
		return (parent_heredoc(cmd, heredoc));
	}
	else if (pid == -1)
	{
		// handle error
	}
	return (0);
}
