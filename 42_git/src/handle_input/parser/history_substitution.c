/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_substitution.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 18:10:49 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/31 18:43:13 by hanakamu         ###   ########.fr       */
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

int	substitute_sgl_his(t_token **tokens, t_token **current, t_his *his)
{
	t_token	*next;
	char	*str;

	if (*current != NULL && ((*current)->next == NULL
		|| ((*current)->next != NULL && ((*current)->next)->tk_type == SPACES)))
	{
		if ((*current)->next != NULL)
			next = ((*current)->next)->next;
		else
			next = NULL;
		clear_token(tokens, (*current)->next, free);
		clear_token(tokens, *current, free);
		*current = next;
		return (SUCCESS);
	}
	else if (*current != NULL && (*current)->next != NULL
		&& ft_isalpha(*((*current)->next)->word) == 0)
	{
		ft_dprintf(2, "-minishell: %s%s: event not found\n",
				(*current)->word, ((*current)->next)->word);
		return (NO_EVENT);
	}
	else
	{
		str = trace_history((*current)->next, his);
		if (str == NULL)
		{
			ft_dprintf(2, "-minishell: %s%s: event not found\n",
				(*current)->word, ((*current)->next)->word);
			return (NO_EVENT);
		}
		clear_token(tokens, (*current)->next, free);
		free((*current)->word);
		(*current)->word = ft_strdup(str);
		if ((*current)->word == NULL)
			return (FAILURE);
		*current = (*current)->next;
		return (SUCCESS);
	}
}

int	substitute_dbl_his(t_token **tokens, t_token **current, t_his *his)
{
	t_token	*next;

	next = (*current)->next;
	if (his == NULL)
		clear_token(tokens, *current, free);
	else
	{
		free((*current)->word);
		(*current)->word = ft_strdup(his->line);
		if ((*current)->word == NULL)
			return (FAILURE);
	}
	*current = next;
	return (SUCCESS);
}

int	check_history(t_token **tokens, t_his *his)
{
	t_token	*current;
	int		is_success;

	current = *tokens;
	while (1)
	{
		while (current != NULL && current->tk_type == SPACES)
			clear_token(tokens, current, free);
		if (current != NULL && current->tk_type == SGL_HIS)
			is_success = substitute_sgl_his(tokens, &current, his);
		else if (current != NULL && current->tk_type == DBL_HIS)
			is_success = substitute_dbl_his(tokens, &current, his);
		else
			break ;
		if (is_success == FAILURE || is_success == NO_EVENT)
			return (is_success);
	}
	return (SUCCESS);
}
