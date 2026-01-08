/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_d_i.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 09:30:15 by hanakamu          #+#    #+#             */
/*   Updated: 2025/11/05 15:01:18 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

void	check_width_d_i(int num, int num_digits, int *counter, t_flag *flag_lst)
{
	if (flag_lst->width <= num_digits)
	{
		handle_num_sign(num, counter, flag_lst);
		if (num >= 0)
			ft_putunbr((unsigned int)num, counter, flag_lst);
		else
			ft_putunbr((unsigned int)(num * -1), counter, flag_lst);
	}
	else if (!flag_lst->is_minus)
		check_width_d_i_leftindent(num, num_digits, counter, flag_lst);
	else
		check_width_d_i_rightindent(num, num_digits, counter, flag_lst);
}

void	d_i_space_zero(int num, int num_digits, int *counter, t_flag *flag_lst)
{
	if (!flag_lst->is_minus)
		d_i_space_zero_leftindent(num, num_digits, counter, flag_lst);
	else
		d_i_space_zero_rightindent(num, num_digits, counter, flag_lst);
}

void	check_prec_d_i(int num, int num_digits, int *counter, t_flag *flag_lst)
{
	if (flag_lst->prec >= flag_lst->width)
	{
		handle_num_sign(num, counter, flag_lst);
		ft_putzeros(flag_lst->prec - num_digits, counter, flag_lst);
		if (num >= 0)
			ft_putunbr((unsigned int)num, counter, flag_lst);
		else
			ft_putunbr((unsigned int)(num * -1), counter, flag_lst);
	}
	else
		d_i_space_zero(num, num_digits, counter, flag_lst);
}

void	convert_d_i(va_list args, int *counter, t_flag *flag_lst)
{
	int				num;
	int				num_digits;
	unsigned int	u_num;

	num = va_arg(args, int);
	if (flag_lst->is_dot && flag_lst->prec <= 0 && num == 0)
	{
		exception_zero_d_i(counter, flag_lst);
		return ;
	}
	if (num < 0)
		u_num = num * -1;
	else
		u_num = num;
	num_digits = count_decimal_digits(u_num);
	if (flag_lst->prec <= num_digits)
		check_width_d_i(num, num_digits, counter, flag_lst);
	else
		check_prec_d_i(num, num_digits, counter, flag_lst);
}
