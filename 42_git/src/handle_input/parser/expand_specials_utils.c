/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_specials_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 11:57:32 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/17 12:29:28 by hanakamu         ###   ########.fr       */
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
	cp_strs = strs;
	while (*strs != NULL)
	{
		ret = join_word_with_space(ret, *strs, &len_ret);
		if (ret == NULL)
		{
			free_null_term_strs(cp_strs);
			return (NULL);
		}
		strs++;
	}
	return (ret);
}

void	check_next_quote(t_token *token)
{
	if (token == NULL)
		return ;
	if (token->tk_type == SGL_QTE || token->tk_type == DBL_QTE)
	{
		if (token->next != NULL)
			(token->next)->is_join = true;
	}
	else if (token->tk_type != SPACES)
		token->is_join = true;
}
