/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 17:56:59 by keitotak          #+#    #+#             */
/*   Updated: 2026/01/25 19:10:56 by keitotak         ###   ########.fr       */
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
