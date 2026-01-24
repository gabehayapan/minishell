/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 10:37:14 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/24 11:55:17 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

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
}	t_builtin;

t_builtin	is_builtin(char *cmd);

int			cd(char **strs, t_env *env_lst, t_exec *top);
int			validate_args(char **strs);
int			set_oldpwd(t_env *pwd, t_env *env_lst);
int			set_pwd(t_env *env_lst);
int			update_to_new_pwd(t_env *oldpwd, t_env *env_lst);
int			update_to_new_oldpwd(t_env *pwd, t_env *oldpwd, t_env *env_lst);

int			echo(char **strs, int fd);
int			env(t_env *env_lst);
int			ft_exit(char **cmdset, t_env *env_lst, t_exec *top);
int			export(char **strs, t_env *env_lst);
int			pwd(void);
int			unset(t_env **env_lst, char **strs);

#endif
