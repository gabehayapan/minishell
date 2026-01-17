/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 11:53:10 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/17 11:53:53 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*join_word_with_space(char *str, char *word, size_t *len_str)
{
	size_t	len_word;
	char	*ret;

	len_word = ft_strlen(word);
	ret = (char *)ft_calloc(*len_str + len_word + 2, sizeof(char));
	if (ret == NULL)
	{
		free(str);
		return (NULL);
	}
	ft_strlcat(ret, str, *len_str + 1);
	ft_strlcat(ret + *len_str, " ", 2);
	ft_strlcat(ret + *len_str + 1, word, len_word + 1);
	free(str);
	*len_str = *len_str + len_word + 1;
	return (ret);
}

char	*join_word_no_space(char *str, char *word)
{
	char	*ret;

	ret = ft_strjoin(str, word);
	if (ret == NULL)
		return (NULL);
	free(str);
	return (ret);
}
