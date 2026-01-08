/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 15:04:54 by hanakamu          #+#    #+#             */
/*   Updated: 2025/11/05 13:12:08 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	total_len;
	char	*new_str;
	char	*res;

	total_len = ft_strlen(s1) + ft_strlen(s2);
	new_str = (char *)ft_calloc(total_len + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	res = new_str;
	while (*s1 != '\0')
	{
		*new_str = *s1;
		s1++;
		new_str++;
	}
	while (*s2 != '\0')
	{
		*new_str = *s2;
		s2++;
		new_str++;
	}
	return (res);
}
