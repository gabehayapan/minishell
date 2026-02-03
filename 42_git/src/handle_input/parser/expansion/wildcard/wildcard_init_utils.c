/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_init_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 16:02:17 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/31 10:49:06 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token	*get_head_dir_token(t_token *token)
{
	while (token != NULL && token->prev != NULL
		&& (token->prev)->tk_type != SPACES)
		token = token->prev;
	return (token);
}

char	*is_slash(t_token *token_dir)
{
	char	*ret;

	if (token_dir == NULL)
		return (NULL);
	ret = ft_strrchr(token_dir->word, '/');
	return (ret);
}

void	clear_head_dir_token(t_token **head_dir)
{
	t_token	*next;

	next = (*head_dir)->next;
	clear_token(&(*head_dir)->prev, *head_dir, free);
	*head_dir = next;
}
