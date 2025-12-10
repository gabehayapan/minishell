/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 13:51:07 by hanakamu          #+#    #+#             */
/*   Updated: 2025/11/05 16:01:51 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

void	ft_putstr(const char *s, int *counter, t_flag *flag_lst)
{
	while (*s)
	{
		ft_putchar(*s, counter, flag_lst);
		s++;
	}
}

void	ft_putnstr(const char *s, int *counter, t_flag *flag_lst, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		ft_putchar(*s, counter, flag_lst);
		s++;
		i++;
	}
}
