/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 14:53:39 by hanakamu          #+#    #+#             */
/*   Updated: 2025/10/22 23:31:05 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	init_input(int n, unsigned int *u_number,
						int *is_minus, int *num_digits)
{
	unsigned int		cp_number;

	if (n < 0)
	{
		*u_number = n * -1;
		*is_minus = 1;
	}
	else
		*u_number = n;
	*num_digits = 1;
	cp_number = *u_number;
	while (cp_number / 10 > 0)
	{
		(*num_digits)++;
		cp_number /= 10;
	}
}

char	*ft_itoa(int n)
{
	unsigned int	u_number;
	int				i;
	int				is_minus;
	int				num_digits;
	char			*conv;

	is_minus = 0;
	u_number = 0;
	num_digits = 0;
	init_input(n, &u_number, &is_minus, &num_digits);
	conv = (char *)ft_calloc(num_digits + is_minus + 1, sizeof(char));
	if (!conv)
		return (NULL);
	i = num_digits + is_minus - 1;
	while (i >= is_minus)
	{
		conv[i] = (u_number % 10) + '0';
		u_number /= 10;
		i--;
	}
	if (is_minus)
		conv[0] = '-';
	return (conv);
}
