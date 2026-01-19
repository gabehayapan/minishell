/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit_status.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 11:57:05 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/19 14:36:56 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

size_t	count_size(int num)
{
	size_t	counter;

	counter = 1;
	while (num >= 10)
	{
		counter = counter + 1;
		num = num / 10;
	}
	return (counter);
}

char	*convert_int_to_str(long exit_status)
{
	unsigned char	status;
	size_t			size;
	char			*str;
	size_t			i;

	status = (unsigned char)exit_status;
	size = count_size((int)status);
	str = (char *)ft_calloc(size + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	i = size - 1;
	while (i)
	{
		str[i] = status % 10 + '0';
		status = status / 10;
		i--;
	}
	str[i] = status % 10 + '0';
	return (str);
}

char	*handle_exit_status(t_token **next, long exit_status)
{
	char	*ret;
	char	*tmp;
	char	*ptr;
	t_token	*new_token;

	ret = convert_int_to_str(exit_status);
	if (ret == NULL)
		return (NULL);
	if (*((*next)->word) == '?' && *((*next)->word) == '\0')
		return (ret);
	tmp = (*next)->word;
	(*next)->word = ft_strdup((*next)->word + 1);
	if ((*next)->word == NULL)
		return (NULL);
	free(tmp);
	ptr = "?";
	new_token = create_new_token(&ptr, (*next)->prev, WORD);
	if (new_token == NULL)
		return (NULL);
	new_token->next = *next;
	(*next)->prev = new_token;
	*next = new_token;
	return (ret);
}
