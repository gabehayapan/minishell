/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 14:34:47 by hanakamu          #+#    #+#             */
/*   Updated: 2026/04/20 15:30:11 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	convert_to_num(const char *str, int sign)
{
	long	num;

	num = 0;
	while (*str >= '0' && *str <= '9')
	{
		if (*(str + 1) >= '0' && *(str + 1) <= '9')
		{
			if (num >= LONG_MAX / 10 && sign == 1)
				return (LONG_MAX);
			else if (num <= LONG_MIN / 10 && sign == -1)
				return (LONG_MIN);
		}
		num = (num * 10) + (*str - '0');
		str++;
	}
	return (num * sign);
}

int	ft_atoi(const char *nptr)
{
	int		sign;
	long	num;

	sign = 1;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == ' ')
		nptr++;
	if (*nptr == '-')
	{
		sign *= -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	num = convert_to_num(nptr, sign);
	return ((int)num);
}
