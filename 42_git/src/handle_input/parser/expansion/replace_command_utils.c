/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_command_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 16:54:05 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/31 16:54:26 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_cmd_replace(t_token **tokens, t_token **current)
{
	t_token	*next;

	next = (*current)->next;
	clear_token(tokens, *current, free);
	*current = next;
	next = (*current)->next;
	clear_token(tokens, *current, free);
	*current = next;
	next = (*current)->next;
	clear_token(tokens, *current, free);
	*current = next;
}
