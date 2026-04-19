/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_single.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 19:01:20 by hanakamu          #+#    #+#             */
/*   Updated: 2026/02/01 07:54:12 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*trace_history(t_token *target, t_his *his)
{
	size_t	len;

	len = ft_strlen(target->word);
	while (his != NULL)
	{
		if (ft_strncmp(his->line, target->word, len) == 0)
			return (his->line);
		his = his->next;
	}
	return (NULL);
}

int	skip_his(t_token **tokens, t_token **current)
{
	t_token	*next;

	if ((*current)->next != NULL)
		next = ((*current)->next)->next;
	else
		next = NULL;
	clear_token(tokens, (*current)->next, free);
	clear_token(tokens, *current, free);
	*current = next;
	return (SUCCESS);
}

int	his_no_event(t_token *current)
{
	if (current ->next != NULL)
		ft_dprintf(2, "-minishell: %s%s: event not found\n",
			current->word, (current->next)->word);
	return (NO_EVENT);
}

int	replace_his_token(t_token **tokens, t_token **current, t_his *his)
{
	char	*str;
	t_token	*next;
	t_token	*token_set;

	str = trace_history((*current)->next, his);
	if (str == NULL)
		return (his_no_event(*current));
	clear_token(tokens, (*current)->next, free);
	next = (*current)->next;
	token_set = tokenizer(&str);
	if (token_set == NULL)
		return (FAILURE);
	insert_token(*current, token_set);
	clear_token(tokens, *current, free);
	*current = next;
	return (SUCCESS);
}
