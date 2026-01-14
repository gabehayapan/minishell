/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 23:11:26 by keitotak          #+#    #+#             */
/*   Updated: 2026/01/14 19:41:54 by hanakamu         ###   ########.fr       */
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

int	exec_command(char **cmd, char **ev)
{
	char	**cmdset;

	cmdset = cmd;
	if (**cmdset == '\0')
		return (handle_noexist_cmd(cmdset));
	if (execve(cmdset[0], cmdset, ev) == -1)
	{
		if (errno == ENOENT)
			return (handle_noexist_cmd(cmdset));
		perror(cmdset[0]);
		free_arrs_ret_s(cmdset, NULL);
		return (EXIT_FAILURE);
	}
	return (EXIT_FAILURE);
}
