/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:41:00 by keitotak          #+#    #+#             */
/*   Updated: 2026/01/25 19:21:12 by keitotak         ###   ########.fr       */
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

char	exit_code(char **cmdset)
{
	if (is_numeric(cmdset[1]))
	{
		if (cmdset[2] == NULL)
			return ((char)ft_atoi(cmdset[1]));
		else
		{
			ft_dprintf(2, "minishell: exit: too many arguments\n");
			return (1);
		}
	}
	else
	{
		ft_dprintf(2, "minishell: exit: %s: ", cmdset[1]);
		ft_dprintf(2, "numeric argument required\n");
		return (2);
	}
}

int	ft_exit(char **cmdset, t_env *env_lst, t_exec *top)
{
	char	code;

	ft_dprintf(2, "exit\n");
	if (cmdset[1] == NULL)
		code = 0;
	else
		code = exit_code(cmdset);
	free_env_lst(env_lst);
	free_node_exec(top);
	exit((int)code);
}
