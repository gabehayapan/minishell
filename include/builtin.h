/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 10:37:14 by hanakamu          #+#    #+#             */
/*   Updated: 2026/05/22 18:42:38 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "parser.h"
# include "pipe.h"

typedef enum s_buitin
{
	ELSE = -1,
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
	HISTORY,
}	t_builtin;

typedef struct s_term
{
	char	**git;
	char	**term0142;
	char	**rm;
}	t_term;

t_builtin	is_builtin(char *cmd);

int			cd(char **strs, t_env **env_lst, t_to_free *to_free);
int			validate_args(char **strs);
int			set_oldpwd(t_env *pwd, t_env **env_lst);
int			set_pwd(t_env **env_lst);
int			update_to_new_pwd(t_env *oldpwd, t_env **env_lst);
int			update_to_new_oldpwd(t_env *pwd, t_env *oldpwd, t_env **env_lst);

int			echo(char **strs, int fd);
int			env(t_env *env_lst);
int			ft_exit(char **cmdset, t_env *env_lst, t_to_free *to_free);

int			export(char **strs, t_env **env_lst, t_to_free *to_free);
int			export_no_args(t_env *env_lst);
int			check_invalid_identifier(char *str);
int			set_env_key_and_value(t_env *env, char *key, char *value);

int			pwd(t_env **env_lst);
int			unset(t_env **env_lst, char **strs);

int			history(t_his *his);

void		free_all(t_env *env_lst, t_to_free *to_free);

#endif
