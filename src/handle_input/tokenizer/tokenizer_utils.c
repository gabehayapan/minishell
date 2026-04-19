/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 12:57:43 by hanakamu          #+#    #+#             */
/*   Updated: 2026/02/03 11:38:25 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include <stdbool.h>

int	init_token_vars(t_token *head, t_token **current, char **input, char **str)
{
	head->next = NULL;
	*current = head;
	*str = ft_strdup(*input);
	if (*str == NULL)
		return (FAILURE);
	return (SUCCESS);
}

static t_tk_type	get_token_type_util(char *str)
{
	if (*str == '\'')
		return (SGL_QTE);
	if (*str == '"')
		return (DBL_QTE);
	if (*str == '$' && (ft_isalnum(*(str + 1)) == 1 || *(str + 1) == '?'
			|| *(str + 1) == '(' || *(str + 1) == '_'))
		return (DOLLAR);
	if (*str == '-' && (ft_isspace(*(str + 1)) == 1 || *(str + 1) == '\0'))
		return (HYPHEN);
	if (*str == '(')
		return (O_PAREN);
	if (*str == ')')
		return (C_PAREN);
	if (*str == '*')
		return (WILDCARD);
	if (*str == '~'
		&& (*(str + 1) == '/' || *(str + 1) == ' ' || *(str + 1) == '\0'))
		return (TILDE);
	if (*str == ';')
		return (SEMI);
	if (ft_isspace(*str))
		return (SPACES);
	return (WORD);
}

t_tk_type	get_token_type(char *str)
{
	if (*str == '\0')
		return (END);
	if (ft_strncmp(str, "<<", 2) == 0)
		return (DBL_INRDT);
	if (ft_strncmp(str, ">>", 2) == 0)
		return (DBL_OUTRDT);
	if (*str == '<')
		return (SGL_INRDT);
	if (*str == '>')
		return (SGL_OUTRDT);
	if (ft_strncmp(str, "!!", 2) == 0)
		return (DBL_HIS);
	if (*str == '!')
		return (SGL_HIS);
	if (*str == '\\')
		return (BACKSLASH);
	if (ft_strncmp(str, "&&", 2) == 0)
		return (AND);
	if (ft_strncmp(str, "||", 2) == 0)
		return (OR);
	if (*str == '|')
		return (PIPE);
	return (get_token_type_util(str));
}
