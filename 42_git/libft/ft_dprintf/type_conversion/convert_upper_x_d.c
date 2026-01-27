/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_upper_x_d.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 13:52:33 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/13 12:42:21 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

void	_check_width_upper_x(unsigned int u_num, int num_digits,
			int *counter, t_dflag flag_lst)
{
	if (flag_lst.width <= num_digits)
	{
		if (flag_lst.is_sharp && u_num != 0)
			write(flag_lst.fd, "0X", 2);
		_ft_puthexa_upper(u_num, flag_lst.fd);
	}
	else if (!flag_lst.is_minus)
		_check_width_upper_x_leftindent(u_num, num_digits, counter, flag_lst);
	else
		_check_width_upper_x_rightindent(u_num, num_digits, counter, flag_lst);
}

void	_upper_x_space_zero(unsigned int u_num, int num_digits,
			int *counter, t_dflag flag_lst)
{
	if (!flag_lst.is_minus)
		_upper_x_space_zero_leftindent(u_num, num_digits, counter, flag_lst);
	else
		_upper_x_space_zero_rightindent(u_num, num_digits, counter, flag_lst);
}

void	_check_prec_upper_x(unsigned int u_num, int num_digits,
			int *counter, t_dflag flag_lst) {
	if (flag_lst.prec >= flag_lst.width)
	{
		if (flag_lst.is_sharp && u_num != 0)
			write(flag_lst.fd, "0X", 2);
		_ft_putzeros(flag_lst.prec - num_digits, counter, flag_lst.fd);
		_ft_puthexa_upper(u_num, flag_lst.fd);
	}
	else
		_upper_x_space_zero(u_num, num_digits, counter, flag_lst);
}

void	_convert_upper_x(va_list args, int *counter, t_dflag flag_lst)
{
	int				num_digits;
	unsigned int	u_num;

	u_num = va_arg(args, unsigned int);
	if (flag_lst.is_dot && flag_lst.prec <= 0 && u_num == 0)
	{
		_exception_zero_upper_x(counter, flag_lst);
		return ;
	}
	num_digits = _count_hexa_digits(u_num);
	if (flag_lst.prec <= num_digits)
		_check_width_upper_x(u_num, num_digits, counter, flag_lst);
	else
		_check_prec_upper_x(u_num, num_digits, counter, flag_lst);
	if (flag_lst.is_sharp && u_num != 0)
		*counter += 2;
	*counter += num_digits;
}
