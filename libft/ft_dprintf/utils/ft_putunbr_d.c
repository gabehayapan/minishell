/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr_d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 14:24:01 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/13 12:37:29 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

void	_ft_putunbr(unsigned int u_num, int fd)
{
	char	digit;

	if (u_num / 10 > 0)
		_ft_putunbr(u_num / 10, fd);
	digit = (u_num % 10) + '0';
	write(fd, &digit, 1);
}
