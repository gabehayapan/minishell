/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 11:57:05 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/19 13:00:39 by hanakamu         ###   ########.fr       */
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
