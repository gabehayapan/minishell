/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 12:49:58 by hanakamu          #+#    #+#             */
/*   Updated: 2026/02/02 10:27:50 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "parser.h"

static char	*get_new_input(char *input, char **new_input)
{
	size_t	total_len;

	*new_input = readline("> ");
	if (*new_input == NULL)
		return (error_unexpected_eof());
	if (input == NULL)
	{
		input = (char *)ft_calloc(ft_strlen(*new_input) + 3, sizeof(char));
		*input = '\n';
	}
	else
		input = ft_realloc(input, ft_strlen(input) + ft_strlen(*new_input) + 2);
	if (input == NULL)
	{
		free(*new_input);
		return (NULL);
	}
	total_len = ft_strlen(input) + ft_strlen(*new_input);
	ft_strlcat(input, *new_input, total_len + 1);
	ft_strlcat(input + total_len, "\n", 2);
	return (input);
}

static int	join_new_input(char **input, char *start, t_syntax_err *syn_err)
{
	*input = join_word_no_space(*input, (*syn_err).input);
	if (*input == NULL)
		return (FAILURE);
	(*syn_err).new_str = ft_strjoin(start, (*syn_err).input);
	if ((*syn_err).new_str == NULL)
		return (FAILURE);
	return (SUCCESS);
}

char	*syntax_error(char **input, char *start, t_tk_type tk_type)
{
	t_syntax_err	syn_err;
	int				is_success;

	syn_err.c = get_missing_char(tk_type);
	ft_dprintf(2, "-minishell: %c is missing\n", syn_err.c);
	syn_err.input = NULL;
	syn_err.new_input = NULL;
	syn_err.input = get_new_input(syn_err.input, &syn_err.new_input);
	if (syn_err.input == NULL)
		return (NULL);
	while (ft_strchr(syn_err.new_input, syn_err.c) == NULL)
	{
		free(syn_err.new_input);
		syn_err.input = get_new_input(syn_err.input, &syn_err.new_input);
		if (syn_err.input == NULL)
			return (NULL);
	}
	remove_last_new_line(syn_err.input);
	is_success = join_new_input(input, start, &syn_err);
	free(syn_err.input);
	free(syn_err.new_input);
	if (is_success == FAILURE)
		return (NULL);
	return (syn_err.new_str);
}
