/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 20:34:18 by keitotak          #+#    #+#             */
/*   Updated: 2026/01/26 15:21:21 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

int	handle_signal(void);
int	detect_signal(pid_t pid, int signum);

int	status_code(int status)
{
	int	code;

	code = status;
	if (WIFEXITED(status))
		code = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
		code = WTERMSIG(status) + 128;
	return (code);
}

int	wait_for_children(int *procid, int proc_count)
{
	int	wstatus;
	int	i;

	i = 0;
	g_sig = 0;
	while (i < proc_count)
	{
		//if (waitpid(procid[i], &wstatus, 0) == error)
		if (wait(&wstatus) == error)
		{
			if (g_sig == SIGINT || g_sig == SIGQUIT)
				return (detect_signal(procid[i], g_sig));
			//perror("waitpid");
			perror("wait");
			return (failure);
		}
		i++;
	}
	return (status_code(wstatus));
}
