/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 15:02:28 by hanakamu          #+#    #+#             */
/*   Updated: 2025/10/22 23:50:24 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	number;

	if (n < 0)
	{
		number = n * -1;
		write(fd, "-", 1);
	}
	else
		number = n;
	if (number / 10 > 0)
		ft_putnbr_fd(number / 10, fd);
	ft_putchar_fd(number % 10 + '0', fd);
}
