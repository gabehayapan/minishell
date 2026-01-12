/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_specials.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 16:00:14 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/12 17:59:14 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	expand_dollar(t_token **tokens, t_token *current, t_env *env_lst)
{
	t_token	*next;
	char	*env_var;

	next = current->next;
	env_var = env_value(env_lst, next->word);
	free(current->word);
	clear_token(tokens, next, free);
	if (env_var == NULL)
		current->word = ft_strdup("");
	else
		current->word = ft_strdup(env_var);
	if (current->word == NULL)
		return (FAILURE);
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

int	expand_specials(t_token **tokens, t_env *env_lst)
{
	t_token	*current;
	int		is_success;

	current = *tokens;
	is_success = SUCCESS;
	while (current != NULL)
	{
		if (current->tk_type == DOLLAR)
			is_success = expand_dollar(tokens, current, env_lst);
		else if (current->tk_type == TILDE)
			is_success = expand_tilde(current, env_lst);
		if (is_success == FAILURE)
			return (FAILURE);
		current = current->next;
	}
	return (SUCCESS);
}
