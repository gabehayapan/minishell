/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 12:39:48 by hanakamu          #+#    #+#             */
/*   Updated: 2025/11/05 14:58:58 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

void	convert_c(va_list args, int *counter, t_flag *flag_lst)
{
	char	c;

	c = va_arg(args, int);
	if (!flag_lst->is_minus && flag_lst->width != 0)
	{
		ft_putspaces(flag_lst->width - 1, counter, flag_lst);
		ft_putchar(c, counter, flag_lst);
	}
	else if (flag_lst->is_minus && flag_lst->width != 0)
	{
		ft_putchar(c, counter, flag_lst);
		ft_putspaces(flag_lst->width - 1, counter, flag_lst);
	}
	else
		ft_putchar(c, counter, flag_lst);
}
