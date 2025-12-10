/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 18:51:42 by hanakamu          #+#    #+#             */
/*   Updated: 2025/11/10 16:10:45 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

int	format_output(const char *format, va_list args)
{
	int	counter;

	counter = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (check_type_sign(&format, args, &counter) == -1)
				return (-1);
		}
		else
		{
			if (write(1, &*format, 1) == -1)
				return (-1);
			else
				counter += 1;
			format++;
		}
	}
	return (counter);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		size;

	if (!format)
		return (-1);
	va_start(args, format);
	size = format_output(format, args);
	va_end(args);
	if (size == -1)
		return (-1);
	return (size);
}
