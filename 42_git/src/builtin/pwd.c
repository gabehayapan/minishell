/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 19:32:04 by keitotak          #+#    #+#             */
/*   Updated: 2026/01/23 20:08:11 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "env_var.h"
#include "ft_dprintf.h"

#define PATHNAME_SIZE 512

int	pwd(void)
{
	char pathname[PATHNAME_SIZE];

	ft_memset(pathname, '\0', PATHNAME_SIZE); 
	getcwd(pathname, PATHNAME_SIZE);
	ft_dprintf(STDOUT_FILENO, "%s\n", pathname);

	return (EXIT_SUCCESS);
}
