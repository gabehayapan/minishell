/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:41:00 by keitotak          #+#    #+#             */
/*   Updated: 2026/02/03 11:17:52 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"
#include <limits.h>

int	check_long_overflow(char *str, int sign)
{
	long	num;

	num = *str - '0';
	while (*(str + 1) >= '0' && *(str + 1) <= '9')
	{
		if ((num >= LONG_MAX / 10 && sign == 1)
			|| (num <= LONG_MIN / 10 && sign == -1))
			return (0);
		num = (num * 10) + (*(str + 1) - '0');
		str++;
	}
	return (1);
}

int	is_numeric(char *str)
{
	int		sign;
	char	*cp_str;

	sign = 1;
	if ((*str == '+' || *str == '-') && ft_isdigit(*(str + 1)) == 1)
	{
		if (*str == '-')
			sign = -1;
		str = str + 1;
	}
	cp_str = str;
	while (*str)
	{
		if (ft_isdigit(*str++) == 0)
			return (0);
	}
	return (check_long_overflow(cp_str, sign));
}

char	exit_code(char **cmdset)
{
	if (is_numeric(cmdset[1]))
	{
		if (cmdset[2] == NULL)
			return ((char)ft_atoi(cmdset[1]));
		else
		{
			ft_dprintf(2, "-minishell: exit: too many arguments\n");
			return (1);
		}
	}
	else
	{
		ft_dprintf(2, "-minishell: exit: %s: ", cmdset[1]);
		ft_dprintf(2, "numeric argument required\n");
		return (2);
	}
}

int	ft_exit(char **cmdset, t_env *env_lst, t_to_free *to_free)
{
	char	code;

	ft_dprintf(2, "exit\n");
	if (cmdset[1] == NULL)
		code = 0;
	else
		code = exit_code(cmdset);
	free_env_lst(env_lst);
	free_node_exec(to_free->top);
	free_his(to_free->his);
	exit((int)code);
}
