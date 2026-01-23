/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 10:37:14 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/23 17:16:53 by keitotak         ###   ########.fr       */
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
int			cd(char **strs);
int			echo(char **strs, int fd);
int			env(t_env *env_lst);
int			ft_exit(char **cmdset, t_env *env_lst, t_exec *top);
int			export(t_env *env_lst, char *new_env);
int			unset(t_env **env_lst, char **strs);

#endif
