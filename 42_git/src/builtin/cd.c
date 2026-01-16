/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 10:27:23 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/16 10:45:04 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "ft_dprintf.h"

int	cd(char **strs)
{
	int	ret;

	ret = chdir(*(strs + 1));
	if (ret == -1)
	{
		ft_dprintf(2, "minishell: cd: ");
		perror(*(strs + 1));
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
