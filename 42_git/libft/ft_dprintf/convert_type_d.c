/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_type_d.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 13:00:24 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/13 12:31:05 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

void	_init_flag_lst(t_dflag *flag_lst, int fd)
{
	flag_lst->is_sharp = 0;
	flag_lst->is_space = 0;
	flag_lst->is_plus = 0;
	flag_lst->is_zero = 0;
	flag_lst->is_minus = 0;
	flag_lst->width = 0;
	flag_lst->is_dot = 0;
	flag_lst->prec = -1;
	flag_lst->fd = fd;
}

void	_check_flag(const char **format, t_dflag *flag_lst)
{
	while (**format == '#' || **format == ' ' || **format == '+'
		|| **format == '-' || **format == '0')
	{
		if (**format == '#')
			flag_lst->is_sharp = 1;
		else if (**format == ' ')
			flag_lst->is_space = 1;
		else if (**format == '+')
			flag_lst->is_plus = 1;
		else if (**format == '-')
			flag_lst->is_minus = 1;
		else
			flag_lst->is_zero = 1;
		(*format)++;
	}
}

void	_check_width_prec_flag(const char **format, t_dflag *flag_lst)
{
	if (ft_isdigit(**format))
	{
		flag_lst->width = ft_atoi(*format);
		while (ft_isdigit(**format))
			(*format)++;
	}
	if (**format == '.')
	{
		flag_lst->is_dot = 1;
		(*format)++;
		flag_lst->prec = ft_atoi(*format);
		while (ft_isdigit(**format))
			(*format)++;
	}
}

void	_convert_type_sign(const char **format, va_list args,
					int *counter, t_dflag flag_lst)
{
	if (**format == 'c')
		_convert_c(args, counter, flag_lst);
	else if (**format == 's')
		_convert_s(args, counter, flag_lst);
	else if (**format == 'p')
		_convert_p(args, counter, flag_lst);
	else if (**format == 'd' || **format == 'i')
		_convert_d_i(args, counter, flag_lst);
	else if (**format == 'u')
		_convert_u(args, counter, flag_lst);
	else if (**format == 'x')
		_convert_lower_x(args, counter, flag_lst);
	else if (**format == 'X')
		_convert_upper_x(args, counter, flag_lst);
	else if (**format == '%')
		_convert_percent(counter, flag_lst.fd);
	(*format)++;
}

void	_check_type_sign(const char **format, va_list args,
			int *counter, int fd)
{
	t_dflag	flag_lst;

	_init_flag_lst(&flag_lst, fd);
	_check_flag(format, &flag_lst);
	_check_width_prec_flag(format, &flag_lst);
	_convert_type_sign(format, args, counter, flag_lst);
}
