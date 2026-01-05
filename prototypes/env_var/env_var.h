/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 10:46:39 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/05 12:37:05 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_VAR_H
# define ENV_VAR_H

# include <stdlib.h>
# include "../../libft/header/ftprintf.h"

# define SUCCESS 0
# define FAILURE 1

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

t_env	*init_env_list(char **envp);
char	*ft_getenv(t_env *env_lst, const char *target);
int		ft_strcmp(const char *s1, const char *s2);

#endif
