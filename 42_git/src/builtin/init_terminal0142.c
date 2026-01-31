/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_terminal0142.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 11:17:41 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/31 11:22:05 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "parser.h"
#include "env_var.h"

char	**clone_term0142(void)
{
	char	**git;

	git = (char **)malloc(sizeof(char *) * 4);
	if (git == NULL)
		return (NULL);
	*git = "/bin/git";
	*(git + 1) = "clone";
	*(git + 2) = "https://github.com/gabehayapan/TERMINAL0142.git";
	*(git + 3) = NULL;
	return (git);
}

char	**launch_term0142(void)
{
	char	**term0142;

	term0142 = (char **)malloc(sizeof(char *) * 2);
	if (term0142 == NULL)
		return (NULL);
	*term0142 = "./launch.sh";
	*(term0142 + 1) = NULL;
	return (term0142);
}

char	**remove_term0142(void)
{
	char	**rm;

	rm = (char **)malloc(sizeof(char *) * 4);
	if (rm == NULL)
		return (NULL);
	*rm = "/bin/rm";
	*(rm + 1) = "-rf";
	*(rm + 2) = "TERMINAL0142";
	*(rm + 3) = NULL;
	return (rm);
}

int	init_term_var(t_env *env_lst, t_term *term, char ***envp)
{
	*envp = convert_to_envp(env_lst);
	if (*envp == NULL)
		return (FAILURE);
	term->git = clone_term0142();
	if (term->git == NULL)
	{
		free_null_term_strs(*envp);
		return (FAILURE);
	}
	term->term0142 = launch_term0142();
	if (term->term0142 == NULL)
	{
		free_null_term_strs(*envp);
		free(term->git);
		return (FAILURE);
	}
	term->rm = remove_term0142();
	if (term->rm == NULL)
	{
		free_null_term_strs(*envp);
		free(term->git);
		free(term->term0142);
		return (FAILURE);
	}
	return (SUCCESS);
}
