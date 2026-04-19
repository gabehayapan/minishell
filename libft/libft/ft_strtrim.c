/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 15:11:33 by hanakamu          #+#    #+#             */
/*   Updated: 2025/10/22 23:30:20 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;

	start = 0;
	end = ft_strlen(s1);
	while (start < end && ft_strchr(set, (unsigned char)s1[start]))
		start++;
	while (end >= start && ft_strchr(set, (unsigned char)s1[end]))
		end--;
	return (ft_substr(s1, start, end - start + 1));
}
