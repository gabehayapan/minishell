/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_num_sign.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 21:12:33 by hanakamu          #+#    #+#             */
/*   Updated: 2025/12/18 12:19:18 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

void	handle_num_sign(int num, int *counter, t_flag flag_lst)
{
	if (flag_lst.is_space && num >= 0)
		*counter += write(flag_lst.fd, " ", 1);
	else if (flag_lst.is_plus && num >= 0)
		*counter += write(flag_lst.fd, "+", 1);
	else if (num < 0)
		*counter += write(flag_lst.fd, "-", 1);
}
