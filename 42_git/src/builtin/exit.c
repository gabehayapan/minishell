/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:41:00 by keitotak          #+#    #+#             */
/*   Updated: 2026/01/23 18:02:47 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

int	is_numeric(char *str)
{
	while (*str)
	{
		if (ft_isdigit(*str++) == 0)
			return (0);
	}
	return (1);
}

int	ft_exit(char **cmdset, t_env *env_lst, t_exec *top)
{
	char	code;

	ft_dprintf(2, "exit\n");
	if (cmdset[1] == NULL)
		code = 0;
	else
	{
		if (is_numeric(cmdset[1]))
		{
			if (cmdset[2] == NULL)
				code = (char)ft_atoi(cmdset[1]);
			else
			{
				ft_dprintf(2, "minishell: exit: too many arguments\n");
				code = 1;
			}
		}
		else
		{
			ft_dprintf(2, "minishell: exit: %s:"\
					" numeric argument required\n", cmdset[1]);
			code = 2;
		}
	}
	free_env_lst(env_lst);
	free_node_exec(top);
	exit((int)code);
}
