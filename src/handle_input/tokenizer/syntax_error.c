/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 12:49:58 by hanakamu          #+#    #+#             */
/*   Updated: 2026/02/03 10:25:08 by hanakamu         ###   ########.fr       */
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

static int	join_new_input(char **user_input, char *start,
			char *input, char **new_str)
{
	*user_input = join_word_no_space(*user_input, input);
	if (*user_input == NULL)
		return (FAILURE);
	*new_str = ft_strjoin(start, input);
	if (*new_str == NULL)
		return (FAILURE);
	return (SUCCESS);
}

char	*syntax_error(char **user_input, char *start, t_tk_type tk_type)
{
	char	c;
	char	*input;
	char	*new_input;
	char	*new_str;
	int		is_success;

	c = get_missing_char(tk_type);
	init_syntax_error(&input, &new_input);
	input = get_new_input(input, &new_input);
	if (input == NULL)
		return (NULL);
	while (ft_strchr(new_input, c) == NULL)
	{
		free(new_input);
		input = get_new_input(input, &new_input);
		if (input == NULL)
			return (NULL);
	}
	remove_last_new_line(input);
	is_success = join_new_input(user_input, start, input, &new_str);
	free(input);
	free(new_input);
	if (is_success == FAILURE)
		return (NULL);
	return (new_str);
}
