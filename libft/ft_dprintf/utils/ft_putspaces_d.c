/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putspaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 11:03:59 by hanakamu          #+#    #+#             */
/*   Updated: 2025/12/18 12:18:16 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

void	ft_putspaces(int num, int *counter, int fd)
{
	unsigned int	u_num;

	if (num < 0)
		u_num = num * -1;
	else
		u_num = num;
	while (u_num--)
		*counter += write(fd, " ", 1);
}
