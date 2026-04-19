/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 18:47:16 by hanakamu          #+#    #+#             */
/*   Updated: 2026/02/03 09:44:35 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void			*new_ptr;
	unsigned char	*cp_ptr;
	unsigned char	*cp_str;

	new_ptr = malloc(sizeof(unsigned char) * size);
	if (new_ptr == NULL)
	{
		free(ptr);
		return (NULL);
	}
	cp_ptr = (unsigned char *)new_ptr;
	cp_str = (unsigned char *)ptr;
	while (*cp_str != '\0')
	{
		*cp_ptr = *cp_str;
		cp_ptr++;
		cp_str++;
	}
	*cp_ptr = '\0';
	free(ptr);
	return (new_ptr);
}
