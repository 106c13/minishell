#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "minishell.h"
#include "defines.h"
#include "exec.h"
#include "expander.h"
#include "utils.h"
#include "enviroment.h"
#include "signals.h"

int	execute_builtin(t_ast *cmd, t_shell *shell)
{
	if (ft_strcmp(cmd->argv[0], "cd") == 0)
		return (change_dir(cmd, shell->env));
	else if (ft_strcmp(cmd->argv[0], "echo") == 0)
		return (echo(cmd));
	else if (ft_strcmp(cmd->argv[0], "exit") == 0)
		return (shell_exit(cmd, shell));
	else if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		return (print_working_dir(cmd));
	else if (ft_strcmp(cmd->argv[0], "export") == 0)
		return (export_env(cmd, shell->env));
	else if (ft_strcmp(cmd->argv[0], "env") == 0)
		return (print_env_list(cmd, shell->env));
	else if (ft_strcmp(cmd->argv[0], "alias") == 0)
		return (alias(cmd, &shell->aliases));
	return (NOTFOUND);
}

int	execute_bin(t_ast *leaf, t_dict *env)
{
	char	**envp;
	char	*path;

	path = find_executable(leaf->argv[0], env);
	if (!path)
	{
		printf("%s: command not found\n", leaf->argv[0]);
		exit(127);
	}
	envp = env_to_array(env);
	set_default_signals();
	execve(path, leaf->argv, envp);
	perror(leaf->argv[0]);
	exit(127);
}

int	execute_command(t_ast *leaf, t_shell *shell)
{
	int		status;
	int		fds[2];
	pid_t	pid;

	expand_command(leaf, shell);
	if (!setup_redirections(fds, leaf->redirs))
		return (1);
	if (leaf->argv && is_builtin(leaf->argv[0]))
		status = execute_builtin(leaf, shell);
	else if (getpid() != shell->pid)
		execute_bin(leaf, shell->env);
	else if (leaf->argv)
	{
		pid = fork();
		if (pid < 0)
			return (perror("fork"), FAILURE);
		if (pid == 0)
			execute_bin(leaf, shell->env);
		waitpid(pid, &status, 0);
		status = WIFEXITED(status) ? WEXITSTATUS(status) : FAILURE;
	}
	restore_fds(fds);
	return (status);
}

int execute_pipe(t_ast *node, t_shell *shell)
{
	int		pipefd[2];
    int 	status;
	pid_t	pid_left;
	pid_t	pid_right;

    if (pipe(pipefd) < 0)
        return (FAILURE);
    pid_left = fork();
    if (pid_left == 0)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		execute_pipe_node(node->left, shell, pipefd);
	}
    pid_right = fork();
    if (pid_right == 0)
	{
        dup2(pipefd[0], STDIN_FILENO);
		execute_pipe_node(node->right, shell, pipefd);
    }
    close(pipefd[0]);
    close(pipefd[1]);
	//waitpid(pid_left, NULL, 0);
    waitpid(pid_right, &status, 0);
    return (WIFEXITED(status) ? WEXITSTATUS(status) : FAILURE);
}

int	execute_background(t_ast *node, t_shell *shell)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == 0)
		exit(execute_node(node->left, shell));
	else
		status = execute_node(node->right, shell);
	return (status);
}

int	execute_node(t_ast *node, t_shell *shell)
{
	if (!node)
		return (FAILURE);
	if (node->type == COMMAND)
		return (execute_command(node, shell));
	if (node->type == SUBSHELL)
		return (execute_subshell(node, shell));
	if (node->type == PIPE)
		return (execute_pipe(node, shell));
	if (node->type == BG)
		return (execute_background(node, shell));
	shell->exec_result = execute_node(node->left, shell);
	if (node->type == SEMI)
		return (execute_node(node->right, shell));
	if (node->type == OR && shell->exec_result != SUCCESS)
		return (execute_node(node->right, shell));
	if (node->type == AND && shell->exec_result == SUCCESS)
		return (execute_node(node->right, shell));
	return (shell->exec_result);
}
