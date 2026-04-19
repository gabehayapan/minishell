/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 19:16:24 by hanakamu          #+#    #+#             */
/*   Updated: 2026/02/03 10:15:23 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void	init_syntax_error(char **input, char **new_input)
{
	*input = NULL;
	*new_input = NULL;
}

void	*error_unexpected_eof(void)
{
	ft_dprintf(2, "Unexpected EOF\n");
	return (NULL);
}

char	get_missing_char(t_tk_type tk_type)
{
	char	missing_char;

	if (tk_type == SGL_QTE)
		missing_char = '\'';
	else if (tk_type == DBL_QTE)
		missing_char = '"';
	else if (tk_type == C_PAREN)
		missing_char = ')';
	else
		missing_char = '\0';
	ft_dprintf(2, "-minishell: %c is missing\n", missing_char);
	return (missing_char);
}

void	remove_last_new_line(char *input)
{
	if (input == NULL || *input == '\0')
		return ;
	while (*(input + 1) != '\0')
		input++;
	if (*input == '\n')
		*input = '\0';
}
