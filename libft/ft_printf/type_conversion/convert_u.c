/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_u.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 12:41:02 by hanakamu          #+#    #+#             */
/*   Updated: 2025/11/05 14:10:22 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

void	check_width_u(unsigned int u_num, int num_digits,
			int *counter, t_flag *flag_lst)
{
	if (flag_lst->width >= num_digits * -1 && flag_lst->width <= num_digits)
	{
		ft_putunbr(u_num, counter, flag_lst);
	}
	else if (!flag_lst->is_minus)
	{
		if (flag_lst->is_zero && flag_lst->prec == -1)
			ft_putzeros(flag_lst->width - num_digits, counter, flag_lst);
		else
			ft_putspaces(flag_lst->width - num_digits, counter, flag_lst);
		ft_putunbr(u_num, counter, flag_lst);
	}
	else
	{
		ft_putunbr(u_num, counter, flag_lst);
		ft_putspaces(flag_lst->width - num_digits, counter, flag_lst);
	}
}

void	ft_putu_zero_space(unsigned int u_num, int num_digits,
			int *counter, t_flag *flag_lst)
{
	if (!flag_lst->is_minus)
	{
		ft_putspaces(flag_lst->width - flag_lst->prec, counter, flag_lst);
		ft_putzeros(flag_lst->prec - num_digits, counter, flag_lst);
		ft_putunbr(u_num, counter, flag_lst);
	}
	else
	{
		ft_putzeros(flag_lst->prec - num_digits, counter, flag_lst);
		ft_putunbr(u_num, counter, flag_lst);
		ft_putspaces(flag_lst->width - flag_lst->prec, counter, flag_lst);
	}
}

void	ft_putu_zero(unsigned int u_num, int num_digits,
			int *counter, t_flag *flag_lst)
{
	ft_putzeros(flag_lst->prec - num_digits, counter, flag_lst);
	ft_putunbr(u_num, counter, flag_lst);
}

void	exception_zero_u(int *counter, t_flag *flag_lst)
{
	ft_putspaces(flag_lst->width, counter, flag_lst);
}

void	convert_u(va_list args, int *counter, t_flag *flag_lst)
{
	int				num_digits;
	unsigned int	u_num;

	u_num = va_arg(args, unsigned int);
	num_digits = count_decimal_digits(u_num);
	if (flag_lst->is_dot && flag_lst->prec <= 0 && u_num == 0)
	{
		exception_zero_u(counter, flag_lst);
		return ;
	}
	if (flag_lst->prec <= num_digits)
		check_width_u(u_num, num_digits, counter, flag_lst);
	else
	{
		if (flag_lst->prec >= flag_lst->width)
			ft_putu_zero(u_num, num_digits, counter, flag_lst);
		else
			ft_putu_zero_space(u_num, num_digits, counter, flag_lst);
	}
}
