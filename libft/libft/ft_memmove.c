/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 15:23:42 by hanakamu          #+#    #+#             */
/*   Updated: 2026/05/22 19:28:44 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*cp_dest;
	const unsigned char	*cp_src;

	if ((!dest || !src) && n > 0)
		return (NULL);
	cp_dest = (unsigned char *)dest;
	cp_src = (const unsigned char *)src;
	if (dest > src)
	{
		while (n--)
			cp_dest[n] = cp_src[n];
	}
	else
	{
		i = 0;
		while (i < n)
		{
			cp_dest[i] = cp_src[i];
			i++;
		}
	}
	return (dest);
}
