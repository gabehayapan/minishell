/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa_d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 14:34:54 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/13 12:37:46 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

void	_ft_puthexa_lower(unsigned int u_num, int fd)
{
	char	*conv_list;

	conv_list = "0123456789abcdef";
	if (u_num / 16 > 0)
		_ft_puthexa_lower(u_num / 16, fd);
	write(fd, &conv_list[u_num % 16], 1);
}

void	_ft_puthexa_upper(unsigned int u_num, int fd)
{
	char	*conv_list;

	conv_list = "0123456789ABCDEF";
	if (u_num / 16 > 0)
		_ft_puthexa_upper(u_num / 16, fd);
	write(fd, &conv_list[u_num % 16], 1);
}
