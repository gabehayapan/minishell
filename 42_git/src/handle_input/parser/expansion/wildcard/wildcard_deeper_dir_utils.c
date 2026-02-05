/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_deeper_dir_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 10:42:06 by hanakamu          #+#    #+#             */
/*   Updated: 2026/02/05 12:59:08 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	set_head_dir(t_token **head_dir, t_token *curr_dir, t_dir *dnames,
			int ret)
{
	if (dnames->is_found == 0)
		*head_dir = curr_dir->next;
	else if (ret == NEW_MATCH)
		*head_dir = (*head_dir)->next;
}

int	handle_not_found(t_token **tokens, t_token *head_filter, char *disname)
{
	int	is_success;

	is_success = reset_wildcard_tokens(tokens, head_filter, NULL,
			disname);
	if (is_success == FAILURE)
		return (FAILURE);
	free(disname);
	return (NOT_FOUND);
}
