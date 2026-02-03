/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 11:29:34 by hanakamu          #+#    #+#             */
/*   Updated: 2026/02/03 11:30:12 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

t_builtin	is_builtin(char *cmd)
{
	if (cmd == NULL)
		return (ELSE);
	if (ft_strcmp("echo", cmd) == 0)
		return (ECHO);
	if (ft_strcmp("cd", cmd) == 0)
		return (CD);
	if (ft_strcmp("pwd", cmd) == 0)
		return (PWD);
	if (ft_strcmp("export", cmd) == 0)
		return (EXPORT);
	if (ft_strcmp("unset", cmd) == 0)
		return (UNSET);
	if (ft_strcmp("env", cmd) == 0)
		return (ENV);
	if (ft_strcmp("exit", cmd) == 0)
		return (EXIT);
	if (ft_strcmp("history", cmd) == 0)
		return (HISTORY);
	if (ft_strcmp("terminal0142", cmd) == 0)
		return (TERMINAL0142);
	if (ft_strcmp("google", cmd) == 0)
		return (GOOGLE);
	else
		return (ELSE);
}
