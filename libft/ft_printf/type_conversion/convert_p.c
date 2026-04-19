/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_p.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 13:39:56 by hanakamu          #+#    #+#             */
/*   Updated: 2025/11/05 14:59:35 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

void	ft_putnil(int *counter, t_flag *flag_lst)
{
	if (flag_lst->width <= 5)
		ft_putstr("(nil)", counter, flag_lst);
	else if (!flag_lst->is_minus)
	{
		ft_putspaces(flag_lst->width - 5, counter, flag_lst);
		ft_putstr("(nil)", counter, flag_lst);
	}
	else
	{
		ft_putstr("(nil)", counter, flag_lst);
		ft_putspaces(flag_lst->width - 5, counter, flag_lst);
	}
}

void	ft_putaddress(unsigned long long ull_num,
			int *counter, t_flag *flag_lst)
{
	char	*conv_list;

	conv_list = "0123456789abcdef";
	if (ull_num / 16 > 0)
		ft_putaddress(ull_num / 16, counter, flag_lst);
	ft_putchar(conv_list[ull_num % 16], counter, flag_lst);
}

void	check_width_p(unsigned long long ull_num, int len,
					int *counter, t_flag *flag_lst)
{
	if (flag_lst->width <= len)
	{
		ft_putstr("0x", counter, flag_lst);
		ft_putaddress(ull_num, counter, flag_lst);
	}
	else if (!flag_lst->is_minus)
	{
		ft_putspaces(flag_lst->width - len, counter, flag_lst);
		ft_putstr("0x", counter, flag_lst);
		ft_putaddress(ull_num, counter, flag_lst);
	}
	else
	{
		ft_putstr("0x", counter, flag_lst);
		ft_putaddress(ull_num, counter, flag_lst);
		ft_putspaces(flag_lst->width - len, counter, flag_lst);
	}
}

void	convert_p(va_list args, int *counter, t_flag *flag_lst)
{
	int					len;
	unsigned long long	ull_num;

	ull_num = va_arg(args, unsigned long long);
	len = count_hexa_digits(ull_num) + 2;
	if (!ull_num)
		ft_putnil(counter, flag_lst);
	else
		check_width_p(ull_num, len, counter, flag_lst);
}
