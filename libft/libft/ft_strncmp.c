/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 15:10:13 by hanakamu          #+#    #+#             */
/*   Updated: 2025/10/21 15:10:18 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while ((unsigned char)*s1 == (unsigned char)*s2 && i < n - 1 && *s1)
	{
		s1++;
		s2++;
		i++;
	}
	return ((int)((unsigned char)*s1 - (unsigned char)*s2));
}
