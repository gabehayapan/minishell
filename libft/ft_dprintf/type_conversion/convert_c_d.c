/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_c_d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 12:39:48 by hanakamu          #+#    #+#             */
/*   Updated: 2025/12/19 14:42:53 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

void	_convert_c(va_list args, int *counter, t_flag flag_lst)
{
	char	c;

	c = va_arg(args, int);
	if (!flag_lst.is_minus && flag_lst.width != 0)
	{
		ft_putspaces(flag_lst.width - 1, counter, flag_lst.fd);
		*counter += write(flag_lst.fd, &c, 1);
	}
	else if (flag_lst.is_minus && flag_lst.width != 0)
	{
		*counter += write(flag_lst.fd, &c, 1);
		ft_putspaces(flag_lst.width - 1, counter, flag_lst.fd);
	}
	else
		*counter += write(flag_lst.fd, &c, 1);
}
