/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 14:34:54 by hanakamu          #+#    #+#             */
/*   Updated: 2025/11/05 15:00:09 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

void	ft_puthexa_lower(unsigned int u_num, int *counter, t_flag *flag_lst)
{
	char	*conv_list;

	conv_list = "0123456789abcdef";
	if (u_num / 16 > 0)
		ft_puthexa_lower(u_num / 16, counter, flag_lst);
	ft_putchar(conv_list[u_num % 16], counter, flag_lst);
}

void	ft_puthexa_upper(unsigned int u_num, int *counter, t_flag *flag_lst)
{
	char	*conv_list;

	conv_list = "0123456789ABCDEF";
	if (u_num / 16 > 0)
		ft_puthexa_upper(u_num / 16, counter, flag_lst);
	ft_putchar(conv_list[u_num % 16], counter, flag_lst);
}
