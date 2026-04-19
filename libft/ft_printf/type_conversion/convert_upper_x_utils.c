/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_upper_x_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 20:30:25 by hanakamu          #+#    #+#             */
/*   Updated: 2025/11/28 16:58:49 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

void	check_width_upper_x_leftindent(unsigned int u_num, int num_digits,
			int *counter, t_flag *flag_lst)
{
	if (flag_lst->width <= num_digits + 2 && flag_lst->is_sharp && u_num != 0)
	{
		ft_putstr("0X", counter, flag_lst);
		ft_puthexa_upper(u_num, counter, flag_lst);
	}
	else if (flag_lst->is_sharp && u_num != 0)
	{
		ft_putstr("0X", counter, flag_lst);
		if (flag_lst->is_zero && flag_lst->prec == -1)
			ft_putzeros(flag_lst->width - num_digits - 2, counter, flag_lst);
		else
			ft_putspaces(flag_lst->width - num_digits - 2, counter, flag_lst);
		ft_puthexa_upper(u_num, counter, flag_lst);
	}
	else
	{
		if (flag_lst->is_zero && flag_lst->prec == -1)
			ft_putzeros(flag_lst->width - num_digits, counter, flag_lst);
		else
			ft_putspaces(flag_lst->width - num_digits, counter, flag_lst);
		ft_puthexa_upper(u_num, counter, flag_lst);
	}
}

void	check_width_upper_x_rightindent(unsigned int u_num, int num_digits,
			int *counter, t_flag *flag_lst)
{
	if (flag_lst->is_sharp && u_num != 0)
		ft_putstr("0X", counter, flag_lst);
	ft_puthexa_upper(u_num, counter, flag_lst);
	if (flag_lst->is_sharp && u_num != 0 && flag_lst->width > num_digits + 2)
		ft_putspaces(flag_lst->width - num_digits - 2, counter, flag_lst);
	else if (!flag_lst->is_sharp)
		ft_putspaces(flag_lst->width - num_digits, counter, flag_lst);
}

void	upper_x_space_zero_leftindent(unsigned int u_num, int num_digits,
			int *counter, t_flag *flag_lst)
{
	if (flag_lst->is_sharp && u_num != 0)
	{
		if (flag_lst->width - flag_lst->prec - 2 >= 0)
			ft_putspaces(flag_lst->width - flag_lst->prec - 2, counter,
				flag_lst);
		ft_putstr("0X", counter, flag_lst);
		ft_putzeros(flag_lst->prec - num_digits, counter, flag_lst);
		ft_puthexa_upper(u_num, counter, flag_lst);
	}
	else
	{
		ft_putspaces(flag_lst->width - flag_lst->prec, counter, flag_lst);
		ft_putzeros(flag_lst->prec - num_digits, counter, flag_lst);
		ft_puthexa_upper(u_num, counter, flag_lst);
	}
}

void	upper_x_space_zero_rightindent(unsigned int u_num, int num_digits,
			int *counter, t_flag *flag_lst)
{
	if (flag_lst->is_sharp && u_num != 0)
	{
		ft_putstr("0X", counter, flag_lst);
		ft_putzeros(flag_lst->prec - num_digits, counter, flag_lst);
		ft_puthexa_upper(u_num, counter, flag_lst);
		if (flag_lst->width - flag_lst->prec - 2 >= 0)
			ft_putspaces(flag_lst->width - flag_lst->prec - 2, counter,
				flag_lst);
	}
	else
	{
		ft_putzeros(flag_lst->prec - num_digits, counter, flag_lst);
		ft_puthexa_upper(u_num, counter, flag_lst);
		ft_putspaces(flag_lst->width - flag_lst->prec, counter, flag_lst);
	}
}

void	exception_zero_upper_x(int *counter, t_flag *flag_lst)
{
	ft_putspaces(flag_lst->width, counter, flag_lst);
}
