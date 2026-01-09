/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 10:46:39 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/09 16:56:32 by hanakamu         ###   ########.fr       */
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

t_env	*init_env_list(char **envp);
size_t	get_array_size(char **strs);
int		new_env_var(t_env *current, char *env);
void	free_env_lst(t_env *env_lst);
size_t	count_size_env_lst(t_env *env_lst);
char	*ft_getenv(t_env *env_lst, const char *target);
int		ft_strcmp(const char *s1, const char *s2);

int		export(t_env *env_lst, char *new_env);
void	unset(t_env **env_lst, char *rm_env_key);

#endif
