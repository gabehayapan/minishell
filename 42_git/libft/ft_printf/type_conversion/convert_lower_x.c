/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_lower_x.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 15:41:17 by hanakamu          #+#    #+#             */
/*   Updated: 2025/11/05 15:02:56 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

void	check_width_lower_x(unsigned int u_num, int num_digits,
			int *counter, t_flag *flag_lst)
{
	if (flag_lst->width <= num_digits)
	{
		if (flag_lst->is_sharp && u_num != 0)
			ft_putstr("0x", counter, flag_lst);
		ft_puthexa_lower(u_num, counter, flag_lst);
	}
	else if (!flag_lst->is_minus)
		check_width_lower_x_leftindent(u_num, num_digits, counter, flag_lst);
	else
		check_width_lower_x_rightindent(u_num, num_digits, counter, flag_lst);
}

void	lower_x_space_zero(unsigned int u_num, int num_digits,
			int *counter, t_flag *flag_lst)
{
	if (!flag_lst->is_minus)
		lower_x_space_zero_leftindent(u_num, num_digits, counter, flag_lst);
	else
		lower_x_space_zero_rightindent(u_num, num_digits, counter, flag_lst);
}

void	check_prec_lower_x(unsigned int u_num, int num_digits,
			int *counter, t_flag *flag_lst)
{
	if (flag_lst->prec >= flag_lst->width)
	{
		if (flag_lst->is_sharp && u_num != 0)
			ft_putstr("0x", counter, flag_lst);
		ft_putzeros(flag_lst->prec - num_digits, counter, flag_lst);
		ft_puthexa_lower(u_num, counter, flag_lst);
	}
	else
		lower_x_space_zero(u_num, num_digits, counter, flag_lst);
}

void	convert_lower_x(va_list args, int *counter, t_flag *flag_lst)
{
	int				num_digits;
	unsigned int	u_num;

	u_num = va_arg(args, unsigned int);
	if (flag_lst->is_dot && flag_lst->prec <= 0 && u_num == 0)
	{
		exception_zero_lower_x(counter, flag_lst);
		return ;
	}
	num_digits = count_hexa_digits(u_num);
	if (flag_lst->prec <= num_digits)
		check_width_lower_x(u_num, num_digits, counter, flag_lst);
	else
		check_prec_lower_x(u_num, num_digits, counter, flag_lst);
}
