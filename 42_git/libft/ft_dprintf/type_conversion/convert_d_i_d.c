/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_d_i_d.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 09:30:15 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/14 17:48:03 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

void	_check_width_d_i(int num, int num_digits, int *counter,
			t_dflag flag_lst)
{
	if (flag_lst.width <= num_digits)
	{
		_handle_num_sign(num, counter, flag_lst);
		if (num >= 0)
			_ft_putunbr((unsigned int)num, flag_lst.fd);
		else
			_ft_putunbr((unsigned int)(num * -1), flag_lst.fd);
	}
	else if (!flag_lst.is_minus)
		_check_width_d_i_leftindent(num, num_digits, counter, flag_lst);
	else
		_check_width_d_i_rightindent(num, num_digits, counter, flag_lst);
}

void	_d_i_space_zero(int num, int num_digits, int *counter, t_dflag flag_lst)
{
	if (!flag_lst.is_minus)
		_d_i_space_zero_leftindent(num, num_digits, counter, flag_lst);
	else
		_d_i_space_zero_rightindent(num, num_digits, counter, flag_lst);
}

void	_check_prec_d_i(int num, int num_digits, int *counter, t_dflag flag_lst)
{
	if (flag_lst.prec >= flag_lst.width)
	{
		_handle_num_sign(num, counter, flag_lst);
		_ft_putzeros(flag_lst.prec - num_digits, counter, flag_lst.fd);
		if (num >= 0)
			_ft_putunbr((unsigned int)num, flag_lst.fd);
		else
			_ft_putunbr((unsigned int)(num * -1), flag_lst.fd);
	}
	else
		_d_i_space_zero(num, num_digits, counter, flag_lst);
}

void	_convert_d_i(va_list args, int *counter, t_dflag flag_lst)
{
	int				num;
	int				num_digits;
	unsigned int	u_num;

	num = va_arg(args, int);
	if (flag_lst.is_dot && flag_lst.prec <= 0 && num == 0)
	{
		_exception_zero_d_i(counter, flag_lst);
		return ;
	}
	if (num < 0)
		u_num = num * -1;
	else
		u_num = num;
	num_digits = _count_decimal_digits(u_num);
	if (flag_lst.prec <= num_digits)
		_check_width_d_i(num, num_digits, counter, flag_lst);
	else
		_check_prec_d_i(num, num_digits, counter, flag_lst);
	*counter += num_digits;
}
