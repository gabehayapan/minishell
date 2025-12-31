/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 10:46:39 by hanakamu          #+#    #+#             */
/*   Updated: 2025/12/31 11:25:51 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_VAR_H
# define ENV_VAR_H

# include <stdlib.h>
# include "../libft/header/libft.h"
# include "../libft/header/ftprintf.h"

# define SUCCESS 0
# define FAILURE 1

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

void	env(t_env *env_lst);
t_env	*init_env_list(char **envp);
int		new_env_var(t_env *tmp, char *env);
void	free_env_lst(t_env *env_lst);
char	*ft_getenv(t_env *env_lst, char *target);

#endif
