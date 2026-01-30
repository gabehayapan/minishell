/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_file_name_validation.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:20:30 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/30 18:13:41 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	init_d_info(t_d_info *d_info, struct dirent *ent)
{
	d_info->d_name = ent->d_name;
	d_info->len_d_name = ft_strlen(ent->d_name);
	d_info->len_str = 0;
}

int	validate_file_name(t_token *head, t_d_info *d_info, int *is_wildcard)
{
	if (head->tk_type != WILDCARD)
	{
		if (*is_wildcard == 0 && *(d_info->d_name) != *(head->word))
			return (NOT_FOUND);
		d_info->d_name = ft_strnstr(d_info->d_name, head->word,
				d_info->len_d_name);
		if (d_info->d_name == NULL)
			return (NOT_FOUND);
		d_info->len_str = ft_strlen(head->word);
		*is_wildcard = 0;
	}
	else
		*is_wildcard = 1;
	return (SUCCESS);
}

int	push_back_filter(t_token *last, t_d_info *d_info)
{
	while (d_info->d_name != NULL && last != NULL)
	{
		d_info->d_name = ft_strnstr(d_info->d_name + 1, last->word,
				d_info->len_d_name);
		if (d_info->d_name != NULL
			&& *(d_info->d_name + d_info->len_str) == '\0')
			return (SUCCESS);
		else if (d_info->d_name == NULL)
			return (NOT_FOUND);
		d_info->len_d_name = ft_strlen(d_info->d_name);
	}
	return (NOT_FOUND);
}

int	check_file_name(t_token *head, struct dirent *ent)
{
	t_token		*last;
	t_d_info	d_info;
	int			ret;
	int			is_wildcard;

	init_d_info(&d_info, ent);
	is_wildcard = 0;
	last = head;
	while (head != NULL && head->tk_type != SPACES && *(head->word) != '/')
	{
		ret = validate_file_name(head, &d_info, &is_wildcard);
		if (ret == NOT_FOUND)
			return (NOT_FOUND);
		last = head;
		head = head->next;
	}
	if (is_wildcard == 0 && *(d_info.d_name + d_info.len_str) != '\0')
		return (push_back_filter(last, &d_info));
	return (SUCCESS);
}
