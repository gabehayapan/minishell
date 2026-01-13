/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_p_d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 13:39:56 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/13 12:41:04 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

void	_ft_putnil(int *counter, t_dflag flag_lst)
{
	if (flag_lst.width <= 5)
		*counter += write(flag_lst.fd, "(nil)", 5);
	else if (!flag_lst.is_minus)
	{
		_ft_putspaces(flag_lst.width - 5, counter, flag_lst.fd);
		*counter += write(flag_lst.fd, "(nil)", 5);
	}
	else
	{
		*counter += write(flag_lst.fd, "(nil)", 5);
		_ft_putspaces(flag_lst.width - 5, counter, flag_lst.fd);
	}
}

void	_ft_putaddress(unsigned long long ull_num, int fd)
{
	char	*conv_list;

	conv_list = "0123456789abcdef";
	if (ull_num / 16 > 0)
		_ft_putaddress(ull_num / 16, fd);
	write(fd, &conv_list[ull_num % 16], 1);
}

void	_check_width_p(unsigned long long ull_num, int len,
					int *counter, t_dflag flag_lst)
{
	if (flag_lst.width <= len)
	{
		write(flag_lst.fd, "0x", 2);
		_ft_putaddress(ull_num, flag_lst.fd);
		*counter += len;
	}
	else if (!flag_lst.is_minus)
	{
		_ft_putspaces(flag_lst.width - len, counter, flag_lst.fd);
		write(flag_lst.fd, "0x", 2);
		_ft_putaddress(ull_num, flag_lst.fd);
		*counter += len;
	}
	else
	{
		write(flag_lst.fd, "0x", 2);
		_ft_putaddress(ull_num, flag_lst.fd);
		*counter += len;
		_ft_putspaces(flag_lst.width - len, counter, flag_lst.fd);
	}
}

void	_convert_p(va_list args, int *counter, t_dflag flag_lst)
{
	int					len;
	unsigned long long	ull_num;

	ull_num = va_arg(args, unsigned long long);
	len = _count_hexa_digits(ull_num) + 2;
	if (!ull_num)
		_ft_putnil(counter, flag_lst);
	else
		_check_width_p(ull_num, len, counter, flag_lst);
}
