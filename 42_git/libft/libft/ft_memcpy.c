/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 11:09:02 by hanakamu          #+#    #+#             */
/*   Updated: 2025/10/22 23:53:41 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*res;

	if (!dest && !src)
		return (NULL);
	res = (unsigned char *)dest;
	i = 0;
	while (i < n)
	{
		*(unsigned char *)dest = *(unsigned char *)src;
		dest++;
		src++;
		i++;
	}
	return (res);
}
