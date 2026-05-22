/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 11:09:02 by hanakamu          #+#    #+#             */
/*   Updated: 2026/05/22 19:15:17 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*cp_dest;
	const unsigned char	*cp_src;

	if (!dest && !src)
		return (NULL);
	cp_dest = (unsigned char *)dest;
	cp_src = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		cp_dest[i] = cp_src[i];
		i++;
	}
	return (dest);
}
