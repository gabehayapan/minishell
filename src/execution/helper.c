/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 17:56:59 by keitotak          #+#    #+#             */
/*   Updated: 2026/02/03 11:37:30 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

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

void	cleanup_pipe(t_pipe *p)
{
	close_pipes(p->pipefd, p->proccnt - 1);
	free_pipe(p);
}

void	free_vars(t_env **env_lst, t_to_free *to_free)
{
	free_env_lst(*env_lst);
	free_node_exec(to_free->top);
	free_his(to_free->his);
}
