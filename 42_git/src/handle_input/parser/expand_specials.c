/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_specials.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 16:00:14 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/19 13:02:31 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdbool.h>

int	expand_dollar(t_token **tokens, t_token *prev, t_token *current,
			t_env *env_lst, long exit_status)
{
	t_token	*next;
	char	*env_var;

	next = current->next;
	env_var = env_value(env_lst, next->word);
	free(current->word);
	if (env_var != NULL)
		current->word = rm_extra_space(env_var);
	else if (next->word != NULL && ft_strcmp(next->word, "?") == 0)
		current->word = convert_int_to_str(exit_status);
	else
		current->word = ft_strdup("");
	clear_token(tokens, next, free);
	if (current->word == NULL)
		return (FAILURE);
	if (prev != NULL && prev->tk_type != SPACES)
		current->is_join = true;
	return (SUCCESS);
}

int	expand_tilde(t_token *current, t_env *env_lst)
{
	char	*path_home;

	path_home = env_value(env_lst, "HOME");
	free(current->word);
	if (path_home == NULL)
		current->word = ft_strdup("");
	else
		current->word = ft_strdup(path_home);
	if (current->word == NULL)
		return (FAILURE);
	return (SUCCESS);
}

int	expand_quoted_dollar(t_token **tokens, t_token *current, t_env *env_lst,
			long exit_status)
{
	t_token	*next;
	char	*env_var;

	next = current->next;
	env_var = env_value(env_lst, next->word);
	free(current->word);
	if (env_var != NULL)
		current->word = ft_strdup(env_var);
	else if (next->word != NULL && ft_strcmp(next->word, "?") == 0)
		current->word = convert_int_to_str(exit_status);
	else
		current->word = ft_strdup("");
	clear_token(tokens, next, free);
	if (current->word == NULL)
		return (FAILURE);
	return (SUCCESS);
}

int	expand_quote(t_token **tokens, t_token *prev, t_token **current,
			t_env *env_lst, long exit_status)
{
	t_tk_type	tk_qte;
	t_token		*next;

	tk_qte = (*current)->tk_type;
	next = (*current)->next;
	clear_token(tokens, *current, free);
	if (prev != NULL && prev->tk_type != SPACES && next != NULL)
		next->is_join = true;
	while (next != NULL && next->tk_type != tk_qte)
	{
		if (handle_dbl_quoted_dollar(tokens, next, env_lst, tk_qte, exit_status)
			== FAILURE)
			return (FAILURE);
		if (next->next != NULL)
			(next->next)->is_join = true;
		next = next->next;
	}
	if (next != NULL)
	{
		*current = next->next;
		check_next_quote(*current);
	}
	else
		*current = NULL;
	clear_token(tokens, next, free);
	return (SUCCESS);
}

int	expand_specials(t_token **tokens, t_env *env_lst, long exit_status)
{
	t_token	*prev;
	t_token	*current;
	int		is_success;

	prev = NULL;
	current = *tokens;
	is_success = SUCCESS;
	while (current != NULL)
	{
		if (current->tk_type == SGL_QTE || current->tk_type == DBL_QTE)
		{
			is_success = expand_quote(tokens, prev, &current, env_lst,
				exit_status);
			if (is_success == FAILURE)
				return (FAILURE);
			continue ;
		}
		if (current->tk_type == DOLLAR)
			is_success = expand_dollar(tokens, prev, current, env_lst, exit_status);
		else if (current->tk_type == TILDE)
			is_success = expand_tilde(current, env_lst);
		if (is_success == FAILURE)
			return (FAILURE);
		prev = current;
		current = current->next;
	}
	return (SUCCESS);
}
