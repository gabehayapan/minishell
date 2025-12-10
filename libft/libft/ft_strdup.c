/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 15:04:10 by hanakamu          #+#    #+#             */
/*   Updated: 2025/10/21 15:04:25 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	int		len_s;
	char	*new_str;

	len_s = ft_strlen(s);
	new_str = malloc(sizeof(char) * (len_s + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < len_s)
	{
		new_str[i] = s[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
