/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 20:34:18 by keitotak          #+#    #+#             */
/*   Updated: 2026/01/27 10:55:40 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

int	status_code(int status)
{
	int	code;
	int	signum;

	code = status;
	if (WIFEXITED(status))
		code = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		signum = WTERMSIG(status);
		code = signum + 128;
		write(1, "\n", 1);
	}
	return (code);
}

int	wait_for_children(int *procid, int proc_count)
{
	int	wstatus;
	int	i;

	(void)procid;
	i = 0;
	while (i < proc_count)
	{
		while (1)
		{
			if (wait(&wstatus) == error)
			{
				perror("wait");
				return (failure);
			}
			else
				break ;
		}
		i++;
	}
	return (status_code(wstatus));
}
