/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 18:48:56 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/31 19:08:46 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_all(t_env *env_lst, t_exec *top)
{
	free_env_lst(env_lst);
	free_node_exec(top);
}

void	free_his(t_his *his)
{
	t_his	*next;

	while (his != NULL)
	{
		next = his->next;
		free(his->line);
		free(his);
		his = next;
	}
}
