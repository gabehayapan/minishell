/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putspaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 11:03:59 by hanakamu          #+#    #+#             */
/*   Updated: 2025/11/05 14:10:57 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

void	ft_putspaces(int num, int *counter, t_flag *flag_lst)
{
	unsigned int	u_num;

	if (num < 0)
		u_num = num * -1;
	else
		u_num = num;
	while (u_num--)
		ft_putchar(' ', counter, flag_lst);
}
