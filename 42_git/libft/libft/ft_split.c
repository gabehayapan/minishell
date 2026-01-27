/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 15:03:27 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/24 10:41:45 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_strs_size(char const *s, char c)
{
	size_t		counter;

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
	if (*s != c && counter == 0)
		counter = counter + 1;
	return (counter);
}

static size_t	get_len_str(char const **s, char c)
{
	size_t	counter;

	counter = 0;
	while (**s != c && **s)
	{
		counter++;
		(*s)++;
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
		count_len = get_len_str(&s, c);
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
	if (*s != c && *i == 0)
	{
		strs[*i] = ft_strdup("");
		(*i)++;
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
