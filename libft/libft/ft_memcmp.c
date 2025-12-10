/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 14:49:27 by hanakamu          #+#    #+#             */
/*   Updated: 2025/10/22 09:15:49 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (*(unsigned char *)s1 == *(unsigned char *)s2 && i < n - 1)
	{
		s1++;
		s2++;
		i++;
	}
	return ((int)(*(unsigned char *)s1 - *(unsigned char *)s2));
}
