/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 23:11:26 by keitotak          #+#    #+#             */
/*   Updated: 2026/01/23 20:14:39 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"
#include "builtin.h"

char	*free_arrs_ret_s(char **arrs, char *s)
{
	char	**tmp;

	tmp = arrs;
	while (*arrs)
		free(*arrs++);
	free(tmp);
	return (s);
}

/*
bool	is_builtin(char **command)
{
	if (ft_strncmp(command[0], "exit", ft_strlen("exit") + 1) == 0)
		return (true);
	if (ft_strncmp(command[0], "cd", ft_strlen("cd") + 1) == 0)
		return (true);
	if (ft_strncmp(command[0], "env", ft_strlen("env") + 1) == 0)
		return (true);
	if (ft_strncmp(command[0], "export", ft_strlen("export") + 1) == 0)
		return (true);
	if (ft_strncmp(command[0], "unset", ft_strlen("unset") + 1) == 0)
		return (true);
	if (ft_strncmp(command[0], "echo", ft_strlen("echo") + 1) == 0)
		return (true);
	return (false);
}
*/

int	pass_to_builtin(t_command *command, t_env *env_lst, t_exec *top)
{
	char	**cmdset;
	int		res;

	cmdset = command->command;
	if (is_builtin(cmdset[0]) == EXIT)
		res = ft_exit(cmdset, env_lst, top);
	if (is_builtin(cmdset[0]) == CD)
		res = cd(cmdset, env_lst);
	if (is_builtin(cmdset[0]) == ENV)
		res = env(env_lst);
	if (is_builtin(cmdset[0]) == EXPORT)
		res = export(cmdset, env_lst);
	if (is_builtin(cmdset[0]) == UNSET)
		res = unset(&env_lst, cmdset);
	if (is_builtin(cmdset[0]) == PWD)
		res = pwd();
	if (is_builtin(cmdset[0]) == ECHO)
		res = echo(cmdset, 1);
	return (res);
}

int	exec_command(t_command *command, t_env *env_lst, t_exec *top)
{
	char	**cmdset;

	cmdset = command->command;
	if (**cmdset == '\0')
		return (handle_noexist_cmd(cmdset));
	if (is_builtin(cmdset[0]) != ELSE)
		exit(pass_to_builtin(command, env_lst, top));
	else if (execve(cmdset[0], cmdset, convert_to_envp(env_lst)) == -1)
	{
		if (errno == ENOENT)
			exit(handle_noexist_cmd(cmdset));
		perror(cmdset[0]);
		free_arrs_ret_s(cmdset, NULL);
		exit(EXIT_FAILURE);
	}
	return (EXIT_FAILURE);
}
