/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 14:59:00 by hanakamu          #+#    #+#             */
/*   Updated: 2025/10/22 09:21:52 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	void	*res;

	res = s;
	i = 0;
	while (i < n)
	{
		*(unsigned char *)s = (unsigned char)c;
		s++;
		i++;
	}
	return (res);
}
