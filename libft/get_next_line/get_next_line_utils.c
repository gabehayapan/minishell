/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 16:18:55 by hanakamu          #+#    #+#             */
/*   Updated: 2025/11/28 17:11:52 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	free_stash(t_rd_state *rd_state)
{
	free(rd_state->stash);
	rd_state->stash = NULL;
	rd_state->len = 0;
}

void	*_ft_memchr(t_rd_state rd_state, int c, size_t n)
{
	size_t	i;
	void	*s;

	s = rd_state.stash;
	if (s == NULL)
		return (NULL);
	i = 0;
	s = s + rd_state.len - n;
	while (i < n)
	{
		if (*(unsigned char *)s == (unsigned char)c)
			return ((void *)s);
		s++;
		i++;
	}
	return (NULL);
}

void	*_ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	void	*res;

	res = dest;
	i = 0;
	while (i < n)
	{
		*(unsigned char *)dest = *(unsigned char *)src;
		dest++;
		src++;
		i++;
	}
	return (res);
}

void	concat_buffer(t_rd_state *rd_state, char *buffer, int n)
{
	void	*tmp;

	if (n == 0)
		return ;
	tmp = malloc(rd_state->len - n);
	if (tmp == NULL)
	{
		free_stash(rd_state);
		return ;
	}
	_ft_memcpy(tmp, rd_state->stash, rd_state->len - n);
	free(rd_state->stash);
	rd_state->stash = malloc(rd_state->len);
	if (rd_state->stash == NULL)
	{
		rd_state->len = 0;
		free(tmp);
		return ;
	}
	_ft_memcpy(rd_state->stash, tmp, rd_state->len - n);
	free(tmp);
	_ft_memcpy(rd_state->stash + rd_state->len - n, buffer, n);
}
