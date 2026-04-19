/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putzeros.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 12:50:25 by hanakamu          #+#    #+#             */
/*   Updated: 2025/11/05 14:11:29 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

void	ft_putzeros(int num, int *counter, t_flag *flag_lst)
{
	unsigned int	u_num;

	if (num < 0)
		u_num = num * -1;
	else
		u_num = num;
	while (u_num--)
		ft_putchar('0', counter, flag_lst);
}
