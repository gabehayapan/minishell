/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 17:56:59 by keitotak          #+#    #+#             */
/*   Updated: 2026/01/24 00:41:19 by keitotak         ###   ########.fr       */
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

int	handle_noexist_cmd(char **cmdset)
{
	ft_putstr_fd(cmdset[0], 2);
	ft_putendl_fd(": command not found", 2);
	free_arrs_ret_s(cmdset, NULL);
	return (127);
}
