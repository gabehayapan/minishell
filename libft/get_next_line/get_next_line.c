/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 16:17:43 by hanakamu          #+#    #+#             */
/*   Updated: 2025/11/28 17:10:53 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*extract_line(t_rd_state *rd_state, void *addr_nl)
{
	int		size;
	char	*new_line;

	size = (addr_nl - rd_state->stash) / sizeof(char) + 1;
	new_line = (char *)malloc(sizeof(char) * (size + 1));
	if (new_line == NULL)
	{
		free_stash(rd_state);
		return (NULL);
	}
	_ft_memcpy(new_line, rd_state->stash, size);
	*(new_line + size) = '\0';
	rd_state->len -= size;
	if (rd_state->len == 0)
		free_stash(rd_state);
	else
		_ft_memcpy(rd_state->stash, rd_state->stash + size, rd_state->len);
	return (new_line);
}

char	*read_content(int fd, t_rd_state *rd_state)
{
	char	buffer[BUFFER_SIZE];
	int		n;
	void	*addr_nl;

	while (1)
	{
		n = read(fd, buffer, BUFFER_SIZE);
		if (n < 0)
		{
			free_stash(rd_state);
			return (NULL);
		}
		rd_state->len += n;
		concat_buffer(rd_state, buffer, n);
		addr_nl = _ft_memchr(*rd_state, '\n', n);
		if (addr_nl != NULL)
			return (extract_line(rd_state, addr_nl));
		else if (n == 0 || rd_state->stash == NULL)
			return (NULL);
	}
}

char	*check_remaining(t_rd_state *rd_state)
{
	char	*new_line;

	new_line = (char *)malloc(sizeof(char) * (rd_state->len + 1));
	if (new_line == NULL)
	{
		free_stash(rd_state);
		return (NULL);
	}
	_ft_memcpy(new_line, rd_state->stash, rd_state->len);
	*(new_line + rd_state->len) = '\0';
	free_stash(rd_state);
	return (new_line);
}

char	*get_next_line(int fd)
{
	static t_rd_state	rd_state;
	char				*new_line;
	void				*addr_nl;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > 8192000)
		return (NULL);
	addr_nl = _ft_memchr(rd_state, '\n', rd_state.len);
	if (addr_nl != NULL)
		return (extract_line(&rd_state, addr_nl));
	new_line = read_content(fd, &rd_state);
	if (new_line != NULL)
		return (new_line);
	if (rd_state.len > 0)
		return (check_remaining(&rd_state));
	return (NULL);
}
