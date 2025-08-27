#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include "minishell.h"
#include "exec.h"
#include "utils.h"
#include "defines.h"
#include "enviroment.h"

void	execute_pipe_node(t_ast *node, t_shell *shell, int *pipefd)
{	
	close(pipefd[0]);
	close(pipefd[1]);
	exit(execute_node(node, shell));
}

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	return (
		ft_strcmp(cmd, "exit") == 0
		|| ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "alias") == 0
	);
}

int	execute_subshell(t_ast *node, t_shell *shell)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("Subshell");
		return (FAILURE);
	}
	if (pid == 0)
		exit(execute_node(node->right, shell));
	waitpid(pid, &status, 0);
	shell->exec_result = status;
	return (WIFEXITED(status) ? WEXITSTATUS(status) : FAILURE);
}

static char	*build_path(char *path_env, char *cmd)
{
	char	*path;
	int		i;
	int		size;

	size = 0;
	while (!is_end(path_env[size], ":"))
		size++;
	size += ft_strlen(cmd) + 1;
	path = malloc((size + 1) * sizeof(char));
	if (!path)
		return (NULL);
	i = 0;
	while (!is_end(*path_env, ":"))
		path[i++] = *(path_env++);
	path[i++] = '/';
	while (*cmd)
		path[i++] = *(cmd++);
	path[i] = '\0';
	return (path);
}

char	*find_executable(char *cmd, t_list *env)
{
	char	*path_env;
	char	*path;
	char	*start;
		
	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path_env = get_env_val(env, "PATH");
	if (!path_env)
		return (NULL);
	start = path_env;
	while (start && *start)
	{
		path = build_path(start, cmd);
		if (!path)
			return (NULL);
		if (access(path, X_OK) == 0)
			return (path);
		start = ft_strchr(start, ':');
		if (start)
			start++;
	}
	return (NULL);
}
