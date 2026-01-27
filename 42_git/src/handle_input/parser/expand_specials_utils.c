/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_specials_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 11:57:32 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/27 12:11:02 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdbool.h>

char	*rm_extra_space(char *str)
{
	char	**strs;
	char	**cp_strs;
	char	*ret;
	size_t	len_ret;

	strs = ft_split(str, ' ');
	if (strs == NULL)
		return (NULL);
	ret = ft_strdup(*strs);
	if (ret == NULL)
		return (NULL);
	len_ret = ft_strlen(ret);
	cp_strs = strs + 1;
	while (*cp_strs != NULL)
	{
		ret = join_word_with_space(ret, *cp_strs, &len_ret);
		if (ret == NULL)
		{
			free_null_term_strs(strs);
			return (NULL);
		}
		cp_strs++;
	}
	return (ret);
}

int	expand_quoted_dollar(t_token **tokens, t_token **current, t_env *env_lst,
			long exit_status)
{
	t_token	*next;
	char	*env_var;

	next = (*current)->next;
	if (next->tk_type == O_PAREN)
		return (replace_with_cmd_output(tokens, current, env_lst));
	env_var = env_value(env_lst, next->word);
	free((*current)->word);
	if (env_var != NULL)
		(*current)->word = ft_strdup(env_var);
	else if (next->word != NULL && ft_strncmp(next->word, "?", 1) == 0)
		(*current)->word = handle_exit_status(&next, exit_status);
	else
		(*current)->word = ft_strdup("");
	clear_token(tokens, next, free);
	if ((*current)->word == NULL)
		return (FAILURE);
	return (SUCCESS);
}

int	handle_dbl_quoted_dollar(t_token **tokens, t_token **current,
			t_env *env_lst, long exit_status)
{
	int	ret;

	if ((*current)->tk_type == DOLLAR)
	{
		ret = expand_quoted_dollar(tokens, current, env_lst, exit_status);
		if (ret == FAILURE || ret == SIGNALED)
			return (ret);
	}
	return (SUCCESS);
}

bool	check_end_of_tokens(t_token *current)
{
	while (current != NULL && current->tk_type != SPACES)
		current = current->next;
	if (current == NULL)
		return (true);
	else
		return (false);
}

int	handle_others(t_token **tokens, t_token **current, t_env *env_lst,
			long exit_status)
{
	int		is_success;
	bool	set_null;

	is_success = SUCCESS;
	if ((*current)->tk_type == DOLLAR)
		is_success = expand_dollar(tokens, current, env_lst, exit_status);
	else if ((*current)->tk_type == TILDE)
		is_success = expand_tilde(*current, env_lst);
	else if ((*current)->tk_type == WILDCARD)
	{
		set_null = check_end_of_tokens(*current);
		is_success = expand_wildcard(tokens, *current);
		if (set_null == true)
			*current = NULL;
	}
	return (is_success);
}
