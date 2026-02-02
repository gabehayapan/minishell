/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_specials_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 11:57:32 by hanakamu          #+#    #+#             */
/*   Updated: 2026/02/02 10:15:23 by hanakamu         ###   ########.fr       */
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
		(*current)->word = ft_strdup(env_var);
	else if (next->word != NULL && *(next->word) == '?')
		(*current)->word = ft_itoa(sub->exit_status);
	else
		(*current)->word = ft_strdup("");
	clear_token(tokens, next, free);
	if ((*current)->word == NULL)
		return (FAILURE);
	return (SUCCESS);
}

int	handle_dbl_quoted_dollar(t_token **tokens, t_token **current,
			t_env *env_lst, t_sub *sub)
{
	int	ret;

	if ((*current)->tk_type == DOLLAR)
	{
		ret = expand_quoted_dollar(tokens, current, env_lst, sub);
		if (ret == FAILURE || ret == SIGNALED)
			return (ret);
	}
	return (SUCCESS);
}

int	tokenize_expanded_word(t_token **tokens)
{
	char	*word;
	t_token	*current;
	t_token	*new_token_set;

	word = ft_strdup("");
	if (word == NULL)
		return (FAILURE);
	current = *tokens;
	while (current != NULL)
	{
		word = join_word_no_space(word, current->word);
		if (word == NULL)
			return (FAILURE);
		current = current->next;
	}
	new_token_set = tokenizer(&word);
	free(word);
	if (new_token_set == NULL)
		return (FAILURE);
	free_token(*tokens);
	*tokens = new_token_set;
	return (SUCCESS);
}
