/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 14:34:47 by hanakamu          #+#    #+#             */
/*   Updated: 2025/10/22 20:27:38 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	check_limits(long num, int sign, const char *next)
{
	if (num > LONG_MAX / 10)
	{
		if (sign == 1 && (*next - '0' > LONG_MAX % 10))
			return (LONG_MAX);
		else if (sign == -1 && (*next - '0' > LONG_MIN % 10))
			return (LONG_MIN);
	}
	return (0);
}

static long	convert_to_num(const char *str, int sign)
{
	long	num;

	num = 0;
	while (*str >= '0' && *str <= '9')
	{
		if (check_limits(num, sign, str + 1))
			return (check_limits(num, sign, str + 1));
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
	num = 0;
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
