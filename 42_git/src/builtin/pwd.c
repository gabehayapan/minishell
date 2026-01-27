/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 19:32:04 by keitotak          #+#    #+#             */
/*   Updated: 2026/01/27 17:15:49 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_var.h"
#include "ft_dprintf.h"

int	pwd(t_env **env_lst)
{
	t_env	*pwd;

	pwd = env_find(*env_lst, "PWD");
	ft_dprintf(STDOUT_FILENO, "%s\n", pwd->value);
	return (EXIT_SUCCESS);
}
