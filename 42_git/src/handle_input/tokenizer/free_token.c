/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 11:37:30 by hanakamu          #+#    #+#             */
/*   Updated: 2026/02/03 11:39:19 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	*free_token(t_token *token)
{
	t_token	*tmp;

	while (token != NULL)
	{
		tmp = token->next;
		free(token->word);
		free(token);
		token = tmp;
	}
	return (NULL);
}

void	clear_token(t_token **tokens, t_token *target, void (*del)(void *))
{
	t_token	*tmp;

	if (tokens == NULL || *tokens == NULL || target == NULL)
		return ;
	if (*tokens == target)
	{
		*tokens = target->next;
		if (*tokens != NULL)
			(*tokens)->prev = NULL;
	}
	else
	{
		tmp = *tokens;
		while (tmp != NULL && tmp->next != target && tmp != target)
			tmp = tmp->next;
		tmp->next = target->next;
		if (target->next != NULL)
			(target->next)->prev = tmp;
	}
	if (del != NULL)
		(*del)(target->word);
	free(target);
}
