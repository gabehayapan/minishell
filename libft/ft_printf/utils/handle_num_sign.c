/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_num_sign.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 21:12:33 by hanakamu          #+#    #+#             */
/*   Updated: 2025/11/05 14:12:21 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

void	handle_num_sign(int num, int *counter, t_flag *flag_lst)
{
	if (flag_lst->is_space && num >= 0)
		ft_putchar(' ', counter, flag_lst);
	else if (flag_lst->is_plus && num >= 0)
		ft_putchar('+', counter, flag_lst);
	else if (num < 0)
		ft_putchar('-', counter, flag_lst);
}
