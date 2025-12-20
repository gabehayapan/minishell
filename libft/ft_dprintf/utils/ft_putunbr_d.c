/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 14:24:01 by hanakamu          #+#    #+#             */
/*   Updated: 2025/12/18 12:34:58 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

void	ft_putunbr(unsigned int u_num, int fd)
{
	char	digit;

	if (u_num / 10 > 0)
		ft_putunbr(u_num / 10, fd);
	digit = (u_num % 10) + '0';
	write(fd, &digit, 1);
}
