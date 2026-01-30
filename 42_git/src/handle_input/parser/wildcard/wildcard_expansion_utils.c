/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expansion_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:20:30 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/30 14:10:44 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	set_type_word(t_token *current)
{
	while (current != NULL && current->tk_type != SPACES)
	{
		if (current->tk_type == WILDCARD)
			current->tk_type = WORD;
		current = current->next;
	}
}

int	verify_file_name(t_token *head, t_d_info *d_info)
{
	d_info->d_name = ft_strnstr(d_info->d_name, head->word, d_info->len_d_name);
	if (d_info->d_name == NULL)
		return (NOT_FOUND);
	d_info->len_str = ft_strlen(head->word);
	return (SUCCESS);
}

int	check_file_name(t_token *head, struct dirent *ent, t_dir *dnames)
{
	t_token		*last;
	t_d_info	d_info;
	int			ret;
	int			is_wildcard;

	(void)dnames;
	d_info.d_name = ent->d_name;
	d_info.len_d_name = ft_strlen(ent->d_name);
	d_info.len_str = 0;
	is_wildcard = 0;
	last = head;
	while (head != NULL && head->tk_type != SPACES && *(head->word) != '/')
	{
		if (head->tk_type != WILDCARD)
		{
			if (is_wildcard == 0 && *(d_info.d_name) != *(head->word))
				return (NOT_FOUND);
			ret = verify_file_name(head, &d_info);
			if (ret == FAILURE || ret == NOT_FOUND)
				return (ret);
			is_wildcard = 0;
		}
		else
			is_wildcard = 1;
		last = head;
		head = head->next;
	}
	if (is_wildcard == 0 && *(d_info.d_name + d_info.len_str) != '\0')
	{
		while (d_info.d_name != NULL && last != NULL)
		{
			d_info.d_name = ft_strnstr(d_info.d_name + 1, last->word,
				d_info.len_d_name);
			if (d_info.d_name != NULL && *(d_info.d_name + d_info.len_str) == '\0')
				return (SUCCESS);
			else if (d_info.d_name == NULL)
				return (NOT_FOUND);
			d_info.len_d_name = ft_strlen(d_info.d_name);
		}
		return (NOT_FOUND);
	}
	return (SUCCESS);
}
