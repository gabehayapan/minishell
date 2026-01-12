/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 10:46:39 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/12 20:45:09 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_VAR_H
# define ENV_VAR_H

# include <stdlib.h>
# include "../libft/header/libft.h"

# define SUCCESS 0
# define FAILURE 1

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_envp_len
{
	size_t	size_len;
	size_t	len_key;
	size_t	len_value;
}	t_envp_len;

typedef struct s_init_env
{
	t_env	head;
	t_env	*current;
	t_env	*last;
}	t_init_env;

// env_var/env_var.c
int		new_env_var(t_env *current, char *env);
char	*get_env_value(char *env);

// env_var/env_var_utils.c
size_t	count_size_env_lst(t_env *env_lst);
void	free_env_lst(t_env *env_lst);

// env_var/init_env_list.c
t_env	*init_env_list(char **envp);

// env_var/env_module/env_lookup.c
t_env	*env_find(t_env *env_lst, const char *target);
char	*env_key(t_env *env_lst, const char *target);
char	*env_value(t_env *env_lst, const char *target);
int		ft_strcmp(const char *s1, const char *s2);

// env_var/get_envp.c
char	**get_envp(t_env *env_lst);

// env_var/export/export.c
int		export(t_env *env_lst, char *new_env);

// env_var/unset/unset.c
void	unset(t_env **env_lst, char *rm_env_key);

#endif
