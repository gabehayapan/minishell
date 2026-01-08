/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 13:47:04 by hanakamu          #+#    #+#             */
/*   Updated: 2025/11/05 13:48:02 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

void	ft_putchar(char c, int *counter, t_flag *flag_lst)
{
	if (write(1, &c, 1) == -1)
		flag_lst->write_error = -1;
	else
		*counter += 1;
}
