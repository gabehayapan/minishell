/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 13:00:24 by hanakamu          #+#    #+#             */
/*   Updated: 2025/11/05 13:50:04 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

void	init_flag_lst(t_flag *flag_lst)
{
	flag_lst->is_sharp = 0;
	flag_lst->is_space = 0;
	flag_lst->is_plus = 0;
	flag_lst->is_zero = 0;
	flag_lst->is_minus = 0;
	flag_lst->width = 0;
	flag_lst->is_dot = 0;
	flag_lst->prec = -1;
	flag_lst->write_error = 0;
}

void	check_flag(const char **format, t_flag *flag_lst)
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

void	check_width_prec_flag(const char **format, t_flag *flag_lst)
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

void	convert_type_sign(const char **format, va_list args,
					int *counter, t_flag *flag_lst)
{
	if (**format == 'c')
		convert_c(args, counter, flag_lst);
	else if (**format == 's')
		convert_s(args, counter, flag_lst);
	else if (**format == 'p')
		convert_p(args, counter, flag_lst);
	else if (**format == 'd' || **format == 'i')
		convert_d_i(args, counter, flag_lst);
	else if (**format == 'u')
		convert_u(args, counter, flag_lst);
	else if (**format == 'x')
		convert_lower_x(args, counter, flag_lst);
	else if (**format == 'X')
		convert_upper_x(args, counter, flag_lst);
	else if (**format == '%')
		convert_percent(counter, flag_lst);
	(*format)++;
}

int	check_type_sign(const char **format, va_list args, int *counter)
{
	t_flag	flag_lst;

	init_flag_lst(&flag_lst);
	check_flag(format, &flag_lst);
	check_width_prec_flag(format, &flag_lst);
	convert_type_sign(format, args, counter, &flag_lst);
	if (flag_lst.write_error == -1)
		return (-1);
	else
		return (0);
}
