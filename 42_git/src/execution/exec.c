/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 23:11:26 by keitotak          #+#    #+#             */
/*   Updated: 2026/01/25 19:24:07 by keitotak         ###   ########.fr       */
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

int	handle_noexist_cmd(char **cmdset)
{
	ft_putstr_fd("-minishell: ", 2);
	ft_putstr_fd(cmdset[0], 2);
	ft_putendl_fd(": command not found", 2);
	free_arrs_ret_s(cmdset, NULL);
	return (127);
}

int	pass_to_builtin(t_command *command, t_env *env_lst, t_exec *top)
{
	char	**cmdset;
	int		res;

	cmdset = command->command;
	if (is_builtin(cmdset[0]) == EXIT)
		res = ft_exit(cmdset, env_lst, top);
	if (is_builtin(cmdset[0]) == CD)
		res = cd(cmdset, env_lst, top);
	if (is_builtin(cmdset[0]) == ENV)
		res = env(env_lst);
	if (is_builtin(cmdset[0]) == EXPORT)
		res = export(cmdset, env_lst, top);
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
