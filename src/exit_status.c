/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 13:15:58 by hanakamu          #+#    #+#             */
/*   Updated: 2026/02/04 13:17:05 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned char	set_exit_status(int ret)
{
	if (ret == -SIGINT)
		return (130);
	else if (ret == NO_COMMAND)
		return (127);
	else if (ret == IS_DIR)
		return (126);
	else if (ret == FORMAT_ERROR)
		return (2);
	else
		return (0);
}
