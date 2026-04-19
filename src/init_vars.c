/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 09:27:07 by hanakamu          #+#    #+#             */
/*   Updated: 2026/02/05 14:41:33 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_input_and_sub(char **input, t_sub *sub)
{
	*input = NULL;
	sub->his = NULL;
	sub->exit_status = 0;
}

void	init_to_free(t_to_free *to_free, t_exec *top, t_his *his)
{
	to_free->top = top;
	to_free->his = his;
}

int	free_input_his(char *input, t_sub *sub)
{
	free(input);
	free_his(sub->his);
	return (FAILURE);
}
