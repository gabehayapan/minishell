/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 23:11:26 by keitotak          #+#    #+#             */
/*   Updated: 2026/01/22 21:05:34 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*free_arrs_ret_s(char **arrs, char *s)
{
	char	**tmp;

	tmp = arrs;
	while (*arrs)
		free(*arrs++);
	free(tmp);
	return (s);
}

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

int	pass_to_builtin(char **command, char **envp)
{
	t_env	*env_lst;
	int		res;

	env_lst = env_arr_to_lst(envp);
	if (ft_strncmp(command[0], "exit", ft_strlen("exit") + 1) == 0)
		res = ft_exit(command);
	if (ft_strncmp(command[0], "cd", ft_strlen("cd") + 1) == 0)
		res = cd(command);
	if (ft_strncmp(command[0], "env", ft_strlen("env") + 1) == 0)
		res = env(env_lst);
	if (ft_strncmp(command[0], "export", ft_strlen("export") + 1) == 0)
		res = export(env_lst, command[1]);
	if (ft_strncmp(command[0], "unset", ft_strlen("unset") + 1) == 0)
		res = unset(&env_lst, command);
	if (ft_strncmp(command[0], "echo", ft_strlen("echo") + 1) == 0)
		res = echo(command, STDOUT_FILENO);
	return (false);
}

int	exec_command(char **command, char **envp)
{
	if (**command == '\0')
		return (handle_noexist_cmd(command));
	if (is_builtin(command))
		return (pass_to_builtin(command[0]));
	else if (execve(command[0], command, envp) == -1)
	{
		if (errno == ENOENT)
			exit(handle_noexist_cmd(command));
		perror(command[0]);
		free_arrs_ret_s(command, NULL);
		exit(EXIT_FAILURE);
	}
	return (EXIT_FAILURE);
}
