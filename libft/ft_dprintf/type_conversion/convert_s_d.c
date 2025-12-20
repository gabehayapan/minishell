/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_s.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 11:17:57 by hanakamu          #+#    #+#             */
/*   Updated: 2025/12/18 12:29:29 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

void	ft_putnull(int *counter, t_flag flag_lst)
{
	if (flag_lst.prec == -1 || flag_lst.prec >= 6)
	{
		if (flag_lst.width <= 6)
			*counter += write(flag_lst.fd, "(null)", 6);
		else if (!flag_lst.is_minus)
		{
			ft_putspaces(flag_lst.width - 6, counter, flag_lst.fd);
			*counter += write(flag_lst.fd, "(null)", 6);
		}
		else
		{
			*counter += write(flag_lst.fd, "(null)", 6);
			ft_putspaces(flag_lst.width - 6, counter, flag_lst.fd);
		}
	}
	else
		ft_putspaces(flag_lst.width, counter, flag_lst.fd);
}

void	ft_puts_precision(char *s, int *counter, t_flag flag_lst)
{
	if (flag_lst.prec >= flag_lst.width)
		*counter += write(flag_lst.fd, s, flag_lst.prec);
	else
	{
		if (!flag_lst.is_minus)
		{
			ft_putspaces(flag_lst.width - flag_lst.prec, counter, flag_lst.fd);
			*counter += write(flag_lst.fd, s, flag_lst.prec);
		}
		else
		{
			*counter += write(flag_lst.fd, s, flag_lst.prec);
			ft_putspaces(flag_lst.width - flag_lst.prec, counter, flag_lst.fd);
		}
	}
}

void	ft_puts(char *s, int len, int *counter, t_flag flag_lst)
{
	if (flag_lst.prec == -1 || flag_lst.prec >= len)
	{
		if (flag_lst.width <= len)
			*counter += write(flag_lst.fd, s, len);
		else if (!flag_lst.is_minus)
		{
			ft_putspaces(flag_lst.width - len, counter, flag_lst.fd);
			*counter += write(flag_lst.fd, s, len);
		}
		else
		{
			*counter += write(flag_lst.fd, s, len);
			ft_putspaces(flag_lst.width - len, counter, flag_lst.fd);
		}
	}
	else
		ft_puts_precision(s, counter, flag_lst);
}

void	convert_s(va_list args, int *counter, t_flag flag_lst)
{
	char	*s;
	int		len;

	s = va_arg(args, char *);
	if (!s)
	{
		ft_putnull(counter, flag_lst);
		return ;
	}
	len = (int)ft_strlen(s);
	ft_puts(s, len, counter, flag_lst);
}
