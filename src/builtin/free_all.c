/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 18:48:56 by hanakamu          #+#    #+#             */
/*   Updated: 2026/02/04 10:44:17 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	free_all(t_env *env_lst, t_to_free *to_free)
{
	free_env_lst(env_lst);
	free_node_exec(to_free->top);
	free_his(to_free->his);
}
