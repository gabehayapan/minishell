/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_digits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 13:47:35 by hanakamu          #+#    #+#             */
/*   Updated: 2025/10/31 14:27:23 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

int	count_decimal_digits(unsigned int num)
{
	int	counter;

	counter = 1;
	while (num / 10 > 0)
	{
		counter++;
		num /= 10;
	}
	return (counter);
}

int	count_hexa_digits(unsigned long long ull_num)
{
	int	counter;

	counter = 1;
	while (ull_num / 16 > 0)
	{
		counter++;
		ull_num /= 16;
	}
	return (counter);
}
