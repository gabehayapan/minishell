/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 13:54:46 by hanakamu          #+#    #+#             */
/*   Updated: 2025/12/30 13:56:29 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_var.h"

int	*ft_strcmp(const char *s1, const char *s2)
{
	while ((unsigned char)*s1 == (unsigned char)*s2 && *s1 != '\0')
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

char	*ft_getenv(t_env *env_lst, char *target)
{
	while (env_lst != NULL)
	{
		if (strcmp(env_lst->key, target) == 0)
			return (env_lst->value);
		env_lst = env_lst->next;
	}
	return (NULL);
}
