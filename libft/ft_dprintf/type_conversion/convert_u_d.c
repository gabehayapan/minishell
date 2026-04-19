/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_u_d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 12:41:02 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/13 12:41:52 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

void	_check_width_u(unsigned int u_num, int num_digits,
			int *counter, t_dflag flag_lst)
{
	if (flag_lst.width >= num_digits * -1 && flag_lst.width <= num_digits)
	{
		_ft_putunbr(u_num, flag_lst.fd);
	}
	else if (!flag_lst.is_minus)
	{
		if (flag_lst.is_zero && flag_lst.prec == -1)
			_ft_putzeros(flag_lst.width - num_digits, counter, flag_lst.fd);
		else
			_ft_putspaces(flag_lst.width - num_digits, counter, flag_lst.fd);
		_ft_putunbr(u_num, flag_lst.fd);
	}
	else
	{
		_ft_putunbr(u_num, flag_lst.fd);
		_ft_putspaces(flag_lst.width - num_digits, counter, flag_lst.fd);
	}
}

void	_ft_putu_zero_space(unsigned int u_num, int num_digits,
			int *counter, t_dflag flag_lst)
{
	if (!flag_lst.is_minus)
	{
		_ft_putspaces(flag_lst.width - flag_lst.prec, counter, flag_lst.fd);
		_ft_putzeros(flag_lst.prec - num_digits, counter, flag_lst.fd);
		_ft_putunbr(u_num, flag_lst.fd);
	}
	else
	{
		_ft_putzeros(flag_lst.prec - num_digits, counter, flag_lst.fd);
		_ft_putunbr(u_num, flag_lst.fd);
		_ft_putspaces(flag_lst.width - flag_lst.prec, counter, flag_lst.fd);
	}
}

void	_ft_putu_zero(unsigned int u_num, int num_digits,
			int *counter, t_dflag flag_lst)
{
	_ft_putzeros(flag_lst.prec - num_digits, counter, flag_lst.fd);
	_ft_putunbr(u_num, flag_lst.fd);
}

void	_exception_zero_u(int *counter, t_dflag flag_lst)
{
	_ft_putspaces(flag_lst.width, counter, flag_lst.fd);
}

void	_convert_u(va_list args, int *counter, t_dflag flag_lst)
{
	int				num_digits;
	unsigned int	u_num;

	u_num = va_arg(args, unsigned int);
	num_digits = _count_decimal_digits(u_num);
	if (flag_lst.is_dot && flag_lst.prec <= 0 && u_num == 0)
	{
		_exception_zero_u(counter, flag_lst);
		return ;
	}
	if (flag_lst.prec <= num_digits)
		_check_width_u(u_num, num_digits, counter, flag_lst);
	else
	{
		if (flag_lst.prec >= flag_lst.width)
			_ft_putu_zero(u_num, num_digits, counter, flag_lst);
		else
			_ft_putu_zero_space(u_num, num_digits, counter, flag_lst);
	}
	*counter += num_digits;
}
