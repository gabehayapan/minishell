/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 20:34:18 by keitotak          #+#    #+#             */
/*   Updated: 2026/01/19 19:39:54 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

int	status_code(int status)
{
	int	code;

	if (WIFEXITED(status))
		code = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
		code = WTERMSIG(status) + 128;
	return (code);
}

/*int	wait_for_children(t_pipex *p)
{
	int	wstatus;

	if (waitpid(p->pid1, NULL, 0) == error)
	{
		perror("waitpid");
		return (failure);
	}
	if (waitpid(p->pid2, &wstatus, 0) == error)
	{
		perror("waitpid");
		return (failure);
	}
	return (status_code(wstatus));
}*/

int	wait_for_children(t_pipe *p, int proc_count)
{
	int	wstatus;
	int	i;

	i = 0;
	while (i < proc_count)
	{
		if (i + 1 < proc_count)
		{
			if (waitpid(p->procid[i], NULL, 0) == error)
			{
				perror("waitpid");
				return (failure);
			}
		}
		else
		{
			if (waitpid(p->procid[i], &wstatus, 0) == error)
			{
				perror("waitpid");
				return (failure);
			}
		}
		i++;
	}
	return (status_code(wstatus));
}
