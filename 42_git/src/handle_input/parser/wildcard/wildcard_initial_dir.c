/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_initial_dir.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 17:17:39 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/30 18:08:43 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	check_initial_dir(t_token **tokens, t_token *filter, t_token **head_dir,
			t_dir *dnames)
{
	int	ret;

	ret = check_dirent(tokens, filter, head_dir, dnames);
	free(dnames->dirname);
	if (ret != SUCCESS && ret != NOT_FOUND)
		free(dnames->disname);
	return (ret);
}
