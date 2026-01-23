/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:14:01 by keitotak          #+#    #+#             */
/*   Updated: 2026/01/23 15:49:21 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

int	*init_procid(int count)
{
	int	*procid;
	int	i;

	procid = (int *)malloc(count * sizeof(int));
	if (procid == NULL)
		return (NULL);
	i = 0;
	while (i < count)
		procid[i++] = -1;
	return (procid);
}

int	*init_pipefd(int count)
{
	int	*pipefd;
	int	i;

	pipefd = (int *)malloc(count * 2 * sizeof(int));
	if (pipefd == NULL)
		return (NULL);
	i = 0;
	while (i < count)
	{
		if (pipe(&pipefd[i * 2]) < 0)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (pipefd);
}

int	init_pipe(t_pipe *p, int count)
{
	p->procid = init_procid(count);
	if (p->procid == NULL)
		return (FAILURE);
	p->pipefd = init_pipefd(count - 1);
	if (p->pipefd == NULL)
		return (free(p->procid), FAILURE);
	return (SUCCESS);
}

void	close_pipes(int	*pipefd, int count)
{
	int	i;

	i = 0;
	while (i < 2 * count)
		close(pipefd[i++]);
}

void	free_pipe(t_pipe *p)
{
	free(p->procid);
	free(p->pipefd);
}

int	pipeline(t_command *command, t_env *env_lst, int proc_count, t_exec *top)
{
	t_pipe	p;
	int		i;
	int		exit_code;

	if (init_pipe(&p, proc_count) == FAILURE)
		return (FAILURE);
	i = 0;
	while (i < proc_count)
	{
		p.procid[i] = fork_process(&p, command, env_lst, i, top);
		if (p.procid[i] == EXIT_FAILURE)
		{
			close_pipes(p.pipefd, proc_count - 1);
			free_pipe(&p);
			return (EXIT_FAILURE);
		}
		command = command->next;
		i++;
	}
	close_pipes(p.pipefd, proc_count - 1);
	exit_code = wait_for_children(&p, proc_count);
	free_pipe(&p);
	return (exit_code);
}
