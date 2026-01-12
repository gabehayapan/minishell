/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 12:49:58 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/12 12:49:48 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void			*new_ptr;
	unsigned char	*cp_ptr;
	unsigned char	*cp_str;

	new_ptr = malloc(sizeof(unsigned char) * size);
	if (new_ptr == NULL)
	{
		free(ptr);
		return (NULL);
	}
	cp_ptr = (unsigned char *)new_ptr;
	cp_str = (unsigned char *)ptr;
	while (*cp_str != '\0')
	{
		*cp_ptr = *cp_str;
		cp_ptr++;
		cp_str++;
	}
	*cp_ptr = '\0';
	free(ptr);
	return (new_ptr);
}

char	get_missing_char(t_tk_type tk_type)
{
	if (tk_type == SGL_QTE)
		return ('\'');
	else if (tk_type == DBL_QTE)
		return ('"');
	else if (tk_type == C_PAREN)
		return (')');
	else
		return ('\0');
}

void	*error_unexpected_eof(void)
{
	ft_putstr_fd("Unexpected EOF\n", 2);
	return (NULL);
}

char	*get_new_input(char *input, char **new_input)
{
	*new_input = readline("> ");
	if (*new_input == NULL)
		return (error_unexpected_eof());
	if (input == NULL)
		input = (char *)ft_calloc(ft_strlen(*new_input) + 1, sizeof(char));
	else
		input = ft_realloc(input, ft_strlen(input) + ft_strlen(*new_input) + 1);
	if (input == NULL)
	{
		free(*new_input);
		return (NULL);
	}
	ft_strlcat(input, *new_input, ft_strlen(input) + ft_strlen(*new_input) + 1);
	return (input);
}

char	*syntax_error(char *start, t_tk_type tk_type)
{
	t_syntax_err	syn_err;

	syn_err.c = get_missing_char(tk_type);
	ft_putchar_fd(syn_err.c, 2);
	ft_putstr_fd(" is missing\n", 2);
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
	syn_err.new_str = ft_strjoin(start, syn_err.input);
	free(syn_err.input);
	free(syn_err.new_input);
	if (syn_err.new_str == NULL)
		return (NULL);
	return (syn_err.new_str);
}
