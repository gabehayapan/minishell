/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 19:32:04 by keitotak          #+#    #+#             */
/*   Updated: 2026/01/31 09:54:40 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_var.h"
#include "ft_dprintf.h"

int	pwd(t_env **env_lst)
{
	t_env	*pwd;
	char	*cwd;

	pwd = env_find(*env_lst, "PWD");
	if (pwd != NULL)
		ft_dprintf(STDOUT_FILENO, "%s\n", pwd->value);
	else
	{
		cwd = getcwd(NULL, 0);
		if (cwd == NULL)
			return (EXIT_FAILURE);
		ft_dprintf(STDOUT_FILENO, "%s\n", cwd);
		free(cwd);
	}
	return (EXIT_SUCCESS);
}
