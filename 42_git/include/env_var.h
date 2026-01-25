/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 10:46:39 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/25 18:52:30 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_VAR_H
# define ENV_VAR_H

# include <stdlib.h>
# include <stdbool.h>
# include "../libft/header/libft.h"
# include "ftprintf.h"

# define SUCCESS 0
# define FAILURE 1

# define ENV_VAR 0
# define SHELL_VAR 1
# define EXPORT_VAR 2

typedef struct s_env
{
	char			*key;
	char			*value;
	int				is_env;
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
t_env	*get_last_env(t_env *env_lst);
void	free_env_lst(t_env *env_lst);

// env_var/init_env_list.c
t_env	*init_env_list(char **envp);

// env_var/env_module/env_lookup.c
t_env	*env_find(t_env *env_lst, const char *target);
char	*env_key(t_env *env_lst, const char *target);
char	*env_value(t_env *env_lst, const char *target);
int		ft_strcmp(const char *s1, const char *s2);

// env_var/convert_to_envp.c
char	**convert_to_envp(t_env *env_lst);

// env_var/unset/unset.c
int	unset(t_env **env_lst, char **strs);

#endif
