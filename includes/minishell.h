/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 21:46:32 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/20 13:47:31 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>

# include "parser.h"
# include "defines.h"

extern int			g_last_status;

typedef t_command	t_cmd;

typedef struct s_env
{
	char			*key;
	char			*val;
	struct s_env	*next;
}	t_env;

typedef struct s_job
{
	int				id;
	pid_t			pid;
	char			*command;
	struct s_job	*next;
}	t_job;

typedef struct s_mfd
{
	int	in_fd;
	int	out_fd;
	int	pipefd[2];
	int	hd_fd;
	int	is_redirected;
	int	s_in_fd;
	int	s_out_fd;
}	t_mfd;

typedef struct s_shell
{
	int			exec_result;
	int			depth;
	t_command	*cmd_ptr;
	t_env		*env_list;
	t_job		*job_list;
	t_mfd		mfd;
}	t_shell;

/* exec */
int		start_exec(t_command *cmd, t_shell *shell);

int		exec_bin(t_command *cmd, t_shell *shell);

int		exec_builtin(t_command *cmd, t_shell *shell);

int		is_builtin(t_command *cmd);

void	set_exec_result(t_shell *shell, int status);

/* builtins */
int		safe_shell_exit(t_command *cmd, t_shell *shell);

int		echo(t_command *cmd, t_shell *shell);

int		print_env_list(t_command *cmd, t_shell *shell);

int		change_dir(t_command *cmd, t_shell *shell);

int		print_working_dir(t_command *cmd, t_shell *shell);

int		unset_env(t_command *cmd, t_shell *shell);

int		export_env(t_command *cmd, t_shell *shell);

/* env.c */
void	init_env_list(t_shell *shell, char **env);

void	free_env_list(t_shell *shell);

char	*get_env_val(t_env *env_list, char *key);

void	set_env_val(t_env *env_list, char *key, char *new_val);

void	del_env_pair(t_env **env_list, char *key);

void	print_export_env(t_env *env);

int		envlen(t_env *env);

char	**env_list_to_str_arr(t_env *env);

void	update_shlvl(t_env *env);
/* signal.c */
void	setup_signals(void);

void	set_interactive_signals(void);

void	set_execution_signals(void);

void	set_default_signals(void);

/* utils */
int		get_args_count(char **args);

int		ft_strlen(char *str);

int		ft_strcmp(const char *s1, const char *s2);

int		ft_strncmp(const char *s1, const char *s2, int n);

char	*get_shell_prompt(t_shell *shell);

char	*ft_strcpy(char *str);

char	**ft_split(const char *str, char c);

char	*ft_strdup(const char *str);

char	*ft_strjoin(char *s1, char *s2);

void	free_split(char **split);

void	*ft_memcpy(void *dest, const void *src, size_t n);

void	*ft_memset(void *ptr, int value, size_t num);

int		str_contains(char *str, char c);

char	*ft_strchr(const char *s, int c);

char	*ft_substr(char *s, unsigned int start, size_t len);

int		ft_isalnum(int c);

int		ft_isalpha(int c);

int		ft_atoi(const char *str);

int		ft_isdigit(int c);

int		digits_only(char *str);

char	*ft_itoa(int n);

void	ft_putstr_fd(char *s, int fd);

char	**str_arr_append(char **arr, char *str);

int		strlen_till(char *str, char c);

void	restore_fd(t_mfd *mfd);

/* fd_utils.c */
int		redirect_to_file(t_command *cmd, int depth);

int		redirect_from_file(t_command *cmd, int depth);

int		setup_redirection(t_command *cmd, t_shell *shell);

char	*str_append_char_safe(char *str, char c);

int		has_quotes(char *str);

void	printerr_one(char *msg);

void	printerr_two(char *cmd, char *msg);

void	printerr_three(char *cmd, char *msg1, char *msg2);

void	free_cmd_list(t_command *cmd);

void	cleanup(t_shell *shell);

/* interpret args*/
void	expand_args(t_command *cmd, t_shell *shell);

char	*replace_env_vars(t_shell *shell, char *input_cmd, int quoted);

/* wildcards */
t_arg	*replace_wildcards(t_arg *pattern_arg, t_arg *arr, int *len);

int		match_pattern(char *pattern, char *filename);

int		process_heredoc(char *delimiter, t_shell *shell);

int		exec_heredocs(t_command *cmd, t_shell *shell);

/* job_manager.c */
void	collect_finished_jobs(t_shell *shell);

void	add_job(t_shell *shell, pid_t pid);

/* args helpers */
t_arg	*append_arg(t_arg new, t_arg *old_arr, int *len);

void	print_cmd(t_command *cmd);

char	**args_to_argv(t_arg *args, int args_count);

void	free_args(t_arg *arr, int len);

t_arg	new_arg_copy(char *str, t_arg *ref);

/* subshell */
t_cmd	*skip_command(t_command *cmd, int depth);

int		get_ss_next_operator(t_command *cmd, t_shell *shell, int change);

int		run_ss_in_pipe(t_command **cmd, t_shell *shell);

int		run_ss_ordinary(t_command **cmd, t_shell *shell);

int		run_subshell(t_command **cmd, t_shell *shell);

int		ss_redirect(t_command *cmd, t_shell *shell);

t_cmd	*get_ss_cmd(t_command *cmd, t_shell *shell, int change);

#endif
