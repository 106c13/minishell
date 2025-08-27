#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include "minishell.h"
#include "defines.h"

static bool redirect_out(char *file)
{
	int fd;

	if (access(file, F_OK) == 0 && access(file, R_OK) != 0)
		return (printf("minishell: %s: Premission denied\n", file), false);
	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (false);
	if (dup2(fd, STDOUT_FILENO) < 0)
		return (close(fd), false);
	close(fd);
	return (true);
}

static bool redirect_in(char *file)
{
	int fd;

	if (access(file, F_OK) != 0)
		return (printf("minishell: %s: No such file or directory\n", file), false);
	if (access(file, R_OK) != 0)
		return (printf("minishell: %s: Premission denied\n", file), false);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (false);
	if (dup2(fd, STDIN_FILENO) < 0)
		return (close(fd), false);
	close(fd);
	return (true);
}

bool	restore_fds(int	*fds)
{
	if (fds[0] != -1)
	{
		close(STDIN_FILENO);
		dup2(fds[0], STDIN_FILENO);
		close(fds[0]);
	}
	if (fds[1] != -1)
	{
		close(STDOUT_FILENO);
		dup2(fds[1], STDOUT_FILENO);
		close(fds[1]);
	}
	return (true);
}

bool	setup_redirections(int *fds, t_redir *redirs)
{
	fds[0] = dup(STDIN_FILENO);
	fds[1] = dup(STDOUT_FILENO);
	if (!redirs)
		return (true);
	while (redirs->type)
	{
		if (redirs->type == OUTFILE && !redirect_out(redirs->file))
			return (false);
		if (redirs->type == INFILE && !redirect_in(redirs->file))
			return (false);
		redirs++;
	}
	return (true);
}
