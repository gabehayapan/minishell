/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 15:03:27 by hanakamu          #+#    #+#             */
/*   Updated: 2025/10/23 15:04:13 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_strs_size(char const *s, char c)
{
	size_t	counter;

	counter = 0;
	while (*s == c && *s)
		s++;
	while (*s)
	{
		while (*s != c && *s)
			s++;
		while (*s == c && *s)
			s++;
		counter++;
	}
	return (counter);
}

static void	assign_substrs(char **strs, char const *s, char c, size_t *i)
{
	size_t			count_len;
	unsigned int	start;
	char const		*cp_s = s;

	start = 0;
	while (*s)
	{
		count_len = 0;
		while (*s != c && *s)
		{
			count_len++;
			s++;
		}
		if ((*s == c || !*s) && count_len)
		{
			strs[*i] = ft_substr(cp_s, start, count_len);
			if (!strs[*i])
				return ;
			start += count_len;
			(*i)++;
		}
		if (*s)
			s++;
		start++;
	}
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	size;
	char	**strs;

	i = 0;
	size = get_strs_size(s, c);
	strs = (char **)malloc(sizeof(char *) * (size + 1));
	if (!strs)
		return (NULL);
	assign_substrs(strs, s, c, &i);
	if (i != size)
	{
		while (i--)
			free(strs[i]);
		free(strs);
		return (NULL);
	}
	strs[i] = NULL;
	return (strs);
}
