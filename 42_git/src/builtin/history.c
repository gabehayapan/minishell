/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 19:31:44 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/31 19:42:43 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "parser.h"

int	history(t_his *his)
{
	while (his != NULL && his->next != NULL)
		his = his->next;
	while (his != NULL)
	{
		ft_printf("% 5d  %s\n", his->id, his->line);
		his = his->prev;
	}
	return (SUCCESS);
}
