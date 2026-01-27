/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putzeros_d.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 12:50:25 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/13 12:37:56 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

void	_ft_putzeros(int num, int *counter, int fd)
{
	unsigned int	u_num;

	if (num < 0)
		u_num = num * -1;
	else
		u_num = num;
	while (u_num--)
		*counter += write(fd, "0", 1);
}
