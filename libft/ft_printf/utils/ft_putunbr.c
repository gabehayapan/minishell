/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 14:24:01 by hanakamu          #+#    #+#             */
/*   Updated: 2025/11/05 15:00:30 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

void	ft_putunbr(unsigned int u_num, int *counter, t_flag *flag_lst)
{
	char	digit;

	if (u_num / 10 > 0)
		ft_putunbr(u_num / 10, counter, flag_lst);
	digit = (u_num % 10) + '0';
	ft_putchar(digit, counter, flag_lst);
}
