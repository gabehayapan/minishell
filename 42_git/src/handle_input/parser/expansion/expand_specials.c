/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_specials.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 16:00:14 by hanakamu          #+#    #+#             */
/*   Updated: 2026/02/04 13:12:51 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	expand_dollar(t_token **tokens, t_token **current, t_env *env_lst,
			t_sub *sub)
{
	t_token	*next;
	char	*env_var;

	next = (*current)->next;
	if (next->tk_type == O_PAREN)
		return (replace_with_cmd_output(tokens, current, env_lst, sub));
	env_var = env_value(env_lst, next->word);
	free((*current)->word);
	if (env_var != NULL)
		(*current)->word = rm_extra_space(env_var);
	else if (next->word != NULL && *(next->word) == '?')
		(*current)->word = ft_itoa(sub->exit_status);
	else
		(*current)->word = ft_strdup("");
	clear_token(tokens, next, free);
	if ((*current)->word == NULL)
		return (FAILURE);
	return (SUCCESS);
}

int	expand_tilde(t_token *current, t_env *env_lst)
{
	char	*path_home;

	if (current->prev == NULL || (current->prev)->tk_type == SPACES)
	{
		path_home = env_value(env_lst, "HOME");
		free(current->word);
		if (path_home == NULL)
			current->word = ft_strdup("");
		else
			current->word = ft_strdup(path_home);
		if (current->word == NULL)
			return (FAILURE);
	}
	return (SUCCESS);
}

int	expand_quote(t_token **tokens, t_token **current, t_env *env_lst,
			t_sub *sub)
{
	t_tk_type	tk_qte;
	t_token		*next;

	tk_qte = (*current)->tk_type;
	next = (*current)->next;
	clear_token(tokens, *current, free);
	while (next != NULL && next->tk_type != tk_qte)
	{
		if (handle_dbl_quoted_dollar(tokens, &next, env_lst, sub)
			== FAILURE)
			return (FAILURE);
		next = next->next;
	}
	if (next != NULL)
		*current = next->next;
	else
		*current = NULL;
	clear_token(tokens, next, free);
	return (SUCCESS);
}

int	keyword_replacement(t_token **tokens, t_env *env_lst, t_sub *sub)
{
	t_token	*current;
	int		ret;

	current = *tokens;
	ret = SUCCESS;
	while (current != NULL)
	{
		if (current->tk_type == SGL_QTE || current->tk_type == DBL_QTE)
		{
			ret = expand_quote(tokens, &current, env_lst, sub);
			if (ret == FAILURE || ret < 0)
				return (ret);
			continue ;
		}
		if (current->tk_type == DOLLAR)
			ret = expand_dollar(tokens, &current, env_lst, sub);
		else if (current->tk_type == TILDE)
			ret = expand_tilde(current, env_lst);
		if (ret == FAILURE || ret < 0)
			return (ret);
		if (current == NULL)
			break ;
		current = current->next;
	}
	return (SUCCESS);
}

int	expand_specials(t_token **tokens, t_env *env_lst, t_sub *sub)
{
	int		ret;

	ret = keyword_replacement(tokens, env_lst, sub);
	if (ret == FAILURE || ret < 0)
		return (ret);
	ret = wildcard_expansion(tokens);
	if (ret == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
