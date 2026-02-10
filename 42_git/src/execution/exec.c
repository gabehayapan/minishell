/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 23:11:26 by keitotak          #+#    #+#             */
/*   Updated: 2026/02/10 10:45:41 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"
#include "builtin.h"

void	free_arrs(char **arrs)
{
	char	**tmp;

	tmp = arrs;
	while (*arrs)
		free(*arrs++);
	free(tmp);
}

int	handle_noexist_cmd(char **cmdset)
{
	ft_dprintf(2, "-minishell: ");
	ft_putstr_fd(cmdset[0], 2);
	ft_putendl_fd(": command not found", 2);
	free_arrs(cmdset);
	return (127);
}

int	pass_to_builtin(t_command *command, t_env **env_lst, t_to_free *to_free)
{
	char	**cmdset;
	int		res;

	cmdset = command->command;
	if (is_builtin(cmdset[0]) == EXIT)
		res = ft_exit(cmdset, *env_lst, to_free);
	if (is_builtin(cmdset[0]) == CD)
		res = cd(cmdset, env_lst, to_free);
	if (is_builtin(cmdset[0]) == ENV)
		res = env(*env_lst);
	if (is_builtin(cmdset[0]) == EXPORT)
		res = export(cmdset, env_lst, to_free);
	if (is_builtin(cmdset[0]) == UNSET)
		res = unset(env_lst, cmdset);
	if (is_builtin(cmdset[0]) == PWD)
		res = pwd(env_lst);
	if (is_builtin(cmdset[0]) == ECHO)
		res = echo(cmdset, 1);
	if (is_builtin(cmdset[0]) == HISTORY)
		res = history(to_free->his);
	if (is_builtin(cmdset[0]) == TERMINAL0142)
		res = terminal0142(*env_lst, to_free);
	if (is_builtin(cmdset[0]) == GOOGLE)
		res = google(cmdset, *env_lst, to_free);
	return (res);
}

void	exit_errcase(char **cmdset)
{
	if (errno == ENOENT)
		exit(handle_noexist_cmd(cmdset));
	if (errno == ENOEXEC)
		exit(EXIT_SUCCESS);
	ft_dprintf(2, "-minishell: ");
	perror(cmdset[0]);
	exit(EXIT_FAILURE);
}

int	exec_command(t_command *command, t_env **env_lst, t_to_free *to_free)
{
	char	**cmdset;
	char	**envp;
	char	*pathname;

	cmdset = command->command;
	if (*cmdset == NULL)
		exit(EXIT_SUCCESS);
	if (**cmdset == '\0')
		return (handle_noexist_cmd(cmdset));
	if (is_builtin(cmdset[0]) != ELSE)
		exit(pass_to_builtin(command, env_lst, to_free));
	pathname = add_path_to_command(cmdset, *env_lst);
	if (pathname == NULL)
		exit(EXIT_FAILURE);
	envp = convert_to_envp(*env_lst);
	if (envp == NULL)
	{
		free(pathname);
		free_vars(env_lst, to_free);
		exit(EXIT_FAILURE);
	}
	execve(pathname, cmdset, envp);
	free(pathname);
	free_arrs(envp);
	free_vars(env_lst, to_free);
	exit_errcase(cmdset);
	return (EXIT_FAILURE);
}
