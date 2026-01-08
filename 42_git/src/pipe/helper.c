/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 17:56:59 by keitotak          #+#    #+#             */
/*   Updated: 2025/12/06 16:46:49 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

bool	include_quote(char *str)
{
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
			return (true);
		str++;
	}
	return (false);
}

int	handle_noexist_cmd(char **cmdset)
{
	ft_putstr_fd(cmdset[0], 2);
	ft_putendl_fd(": command not found", 2);
	free_arrs_ret_s(cmdset, NULL);
	return (127);
}
