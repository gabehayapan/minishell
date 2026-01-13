/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_lower_x_utils_d.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 20:23:36 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/13 12:17:59 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

void	_check_width_lower_x_leftindent(unsigned int u_num, int num_digits,
			int *counter, t_dflag flag_lst)
{
	if (flag_lst.width <= num_digits + 2 && flag_lst.is_sharp && u_num != 0)
	{
		write(flag_lst.fd, "0x", 2);
		_ft_puthexa_lower(u_num, flag_lst.fd);
	}
	else if (flag_lst.is_sharp && u_num != 0)
	{
		write(flag_lst.fd, "0x", 2);
		if (flag_lst.is_zero && flag_lst.prec == -1)
			_ft_putzeros(flag_lst.width - num_digits - 2, counter, flag_lst.fd);
		else
			_ft_putspaces(flag_lst.width - num_digits - 2, counter, flag_lst.fd);
		_ft_puthexa_lower(u_num, flag_lst.fd);
	}
	else
	{
		if (flag_lst.is_zero && flag_lst.prec == -1)
			_ft_putzeros(flag_lst.width - num_digits, counter, flag_lst.fd);
		else
			_ft_putspaces(flag_lst.width - num_digits, counter, flag_lst.fd);
		_ft_puthexa_lower(u_num, flag_lst.fd);
	}
}

void	_check_width_lower_x_rightindent(unsigned int u_num, int num_digits,
			int *counter, t_dflag flag_lst)
{
	if (flag_lst.is_sharp && u_num != 0)
		write(flag_lst.fd, "0x", 2);
	_ft_puthexa_lower(u_num, flag_lst.fd);
	if (flag_lst.is_sharp && u_num != 0 && flag_lst.width > num_digits - 2)
		_ft_putspaces(flag_lst.width - num_digits - 2, counter, flag_lst.fd);
	else if (!flag_lst.is_sharp)
		_ft_putspaces(flag_lst.width - num_digits, counter, flag_lst.fd);
}

void	_lower_x_space_zero_leftindent(unsigned int u_num, int num_digits,
			int *counter, t_dflag flag_lst)
{
	if (flag_lst.is_sharp && u_num != 0)
	{
		if (flag_lst.width - flag_lst.prec - 2 >= 0)
			_ft_putspaces(flag_lst.width - flag_lst.prec - 2, counter,
				flag_lst.fd);
		write(flag_lst.fd, "0x", 2);
		_ft_putzeros(flag_lst.prec - num_digits, counter, flag_lst.fd);
		_ft_puthexa_lower(u_num, flag_lst.fd);
	}
	else
	{
		_ft_putspaces(flag_lst.width - flag_lst.prec, counter, flag_lst.fd);
		_ft_putzeros(flag_lst.prec - num_digits, counter, flag_lst.fd);
		_ft_puthexa_lower(u_num, flag_lst.fd);
	}
}

void	_lower_x_space_zero_rightindent(unsigned int u_num, int num_digits,
			int *counter, t_dflag flag_lst)
{
	if (flag_lst.is_sharp && u_num != 0)
	{
		write(flag_lst.fd, "0x", 2);
		_ft_putzeros(flag_lst.prec - num_digits, counter, flag_lst.fd);
		_ft_puthexa_lower(u_num, flag_lst.fd);
		if (flag_lst.width - flag_lst.prec - 2 >= 0)
			_ft_putspaces(flag_lst.width - flag_lst.prec - 2, counter,
				flag_lst.fd);
	}
	else
	{
		_ft_putzeros(flag_lst.prec - num_digits, counter, flag_lst.fd);
		_ft_puthexa_lower(u_num, flag_lst.fd);
		_ft_putspaces(flag_lst.width - flag_lst.prec, counter, flag_lst.fd);
	}
}

void	_exception_zero_lower_x(int *counter, t_dflag flag_lst)
{
	_ft_putspaces(flag_lst.width, counter, flag_lst.fd);
}
