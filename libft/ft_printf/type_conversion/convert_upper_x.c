/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_upper_x.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 13:52:33 by hanakamu          #+#    #+#             */
/*   Updated: 2025/11/05 15:39:10 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

void	check_width_upper_x(unsigned int u_num, int num_digits,
			int *counter, t_flag *flag_lst)
{
	if (flag_lst->width <= num_digits)
	{
		if (flag_lst->is_sharp && u_num != 0)
			ft_putstr("0X", counter, flag_lst);
		ft_puthexa_upper(u_num, counter, flag_lst);
	}
	else if (!flag_lst->is_minus)
		check_width_upper_x_leftindent(u_num, num_digits, counter, flag_lst);
	else
		check_width_upper_x_rightindent(u_num, num_digits, counter, flag_lst);
}

void	upper_x_space_zero(unsigned int u_num, int num_digits,
			int *counter, t_flag *flag_lst)
{
	if (!flag_lst->is_minus)
		upper_x_space_zero_leftindent(u_num, num_digits, counter, flag_lst);
	else
		upper_x_space_zero_rightindent(u_num, num_digits, counter, flag_lst);
}

void	check_prec_upper_x(unsigned int u_num, int num_digits,
			int *counter, t_flag *flag_lst) {
	if (flag_lst->prec >= flag_lst->width)
	{
		if (flag_lst->is_sharp && u_num != 0)
			ft_putstr("0X", counter, flag_lst);
		ft_putzeros(flag_lst->prec - num_digits, counter, flag_lst);
		ft_puthexa_upper(u_num, counter, flag_lst);
	}
	else
		upper_x_space_zero(u_num, num_digits, counter, flag_lst);
}

void	convert_upper_x(va_list args, int *counter, t_flag *flag_lst)
{
	int				num_digits;
	unsigned int	u_num;

	u_num = va_arg(args, unsigned int);
	if (flag_lst->is_dot && flag_lst->prec <= 0 && u_num == 0)
	{
		exception_zero_upper_x(counter, flag_lst);
		return ;
	}
	num_digits = count_hexa_digits(u_num);
	if (flag_lst->prec <= num_digits)
		check_width_upper_x(u_num, num_digits, counter, flag_lst);
	else
		check_prec_upper_x(u_num, num_digits, counter, flag_lst);
}
