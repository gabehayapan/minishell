/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_d_i_utils_d.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 20:38:33 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/13 12:14:21 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

void	_check_width_d_i_leftindent(int num, int num_digits,
			int *counter, t_dflag flag_lst)
{
	if (flag_lst.is_zero && flag_lst.prec == -1)
	{
		_handle_num_sign(num, counter, flag_lst);
		if (((flag_lst.is_space || flag_lst.is_plus) && num >= 0) || num < 0)
			_ft_putzeros(flag_lst.width - num_digits - 1, counter, flag_lst.fd);
		else
			_ft_putzeros(flag_lst.width - num_digits, counter, flag_lst.fd);
	}
	else
	{
		if (((flag_lst.is_space || flag_lst.is_plus) && num >= 0) || num < 0)
			_ft_putspaces(flag_lst.width - num_digits - 1, counter, flag_lst.fd);
		else
			_ft_putspaces(flag_lst.width - num_digits, counter, flag_lst.fd);
		_handle_num_sign(num, counter, flag_lst);
	}
	if (num >= 0)
		_ft_putunbr((unsigned int)num, flag_lst.fd);
	else
		_ft_putunbr((unsigned int)(num * -1), flag_lst.fd);
}

void	_check_width_d_i_rightindent(int num, int num_digits,
			int *counter, t_dflag flag_lst)
{
	_handle_num_sign(num, counter, flag_lst);
	if (num >= 0)
		_ft_putunbr((unsigned int)num, flag_lst.fd);
	else
		_ft_putunbr((unsigned int)(num * -1), flag_lst.fd);
	if (((flag_lst.is_space || flag_lst.is_plus) && num >= 0)
		|| num < 0)
		_ft_putspaces(flag_lst.width - num_digits - 1, counter, flag_lst.fd);
	else
		_ft_putspaces(flag_lst.width - num_digits, counter, flag_lst.fd);
}

void	_d_i_space_zero_leftindent(int num, int num_digits,
			int *counter, t_dflag flag_lst)
{
	if (((flag_lst.is_space || flag_lst.is_plus) && num >= 0) || num < 0)
		_ft_putspaces(flag_lst.width - flag_lst.prec - 1, counter, flag_lst.fd);
	else
		_ft_putspaces(flag_lst.width - flag_lst.prec, counter, flag_lst.fd);
	_handle_num_sign(num, counter, flag_lst);
	_ft_putzeros(flag_lst.prec - num_digits, counter, flag_lst.fd);
	if (num >= 0)
		_ft_putunbr((unsigned int)num, flag_lst.fd);
	else
		_ft_putunbr((unsigned int)(num * -1), flag_lst.fd);
}

void	_d_i_space_zero_rightindent(int num, int num_digits,
			int *counter, t_dflag flag_lst)
{
	_handle_num_sign(num, counter, flag_lst);
	_ft_putzeros(flag_lst.prec - num_digits, counter, flag_lst.fd);
	if (num >= 0)
		_ft_putunbr((unsigned int)num, flag_lst.fd);
	else
		_ft_putunbr((unsigned int)(num * -1), flag_lst.fd);
	if (((flag_lst.is_space || flag_lst.is_plus) && num >= 0) || num < 0)
		_ft_putspaces(flag_lst.width - flag_lst.prec - 1, counter, flag_lst.fd);
	else
		_ft_putspaces(flag_lst.width - flag_lst.prec, counter, flag_lst.fd);
}

void	_exception_zero_d_i(int *counter, t_dflag flag_lst)
{
	if (!flag_lst.is_minus && flag_lst.width != 0)
	{
		if (flag_lst.is_plus)
		{
			_ft_putspaces(flag_lst.width - 1, counter, flag_lst.fd);
			*counter += write(flag_lst.fd, "+", 1);
		}
		else
			_ft_putspaces(flag_lst.width, counter, flag_lst.fd);
	}
	else if (flag_lst.is_minus)
	{
		if (flag_lst.is_plus)
		{
			*counter += write(flag_lst.fd, "+", 1);
			_ft_putspaces(flag_lst.width - 1, counter, flag_lst.fd);
		}
		else
			_ft_putspaces(flag_lst.width, counter, flag_lst.fd);
	}
	else
	{
		if (flag_lst.is_plus)
			*counter += write(flag_lst.fd, "+", 1);
	}
}
