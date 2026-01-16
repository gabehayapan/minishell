/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 20:21:48 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/16 11:20:42 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "ft_dprintf.h"
#include <stdbool.h>

int	is_valid_option(char *str)
{
	while (*str != '\0')
	{
		if (*str != 'n')
			return (false);
		str++;
	}
	return (true);
}

int	check_option(char ***strs)
{
	int		is_option;
	int		is_valid;
	char	**argv;

	is_option = 0;
	argv = *strs + 1;
	while (*argv != NULL && **argv == '-')
	{
		is_valid = is_valid_option((*argv) + 1);
		if (is_valid == true)
			is_option = 1;
		else
			break ;
		argv++;
	}
	*strs = argv;
	return (is_option);
}

int	echo(char **strs, int fd)
{
	int	is_option;
	int	is_space;

	is_option = check_option(&strs);
	is_space = false;
	while (*strs != NULL && *(strs + 1) != NULL)
	{
		ft_dprintf(fd, "%s", *strs);
		if (is_space == false)
			is_space = true;
		strs++;
	}
	if (*strs != NULL)
	{
		if (is_space == true)
			ft_dprintf(fd, " ");
		ft_dprintf(fd, "%s", *strs);
	}
	if (is_option == false)
		ft_dprintf(fd, "\n");
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	(void)argc;
	echo(argv, 1);
	return (0);
}
