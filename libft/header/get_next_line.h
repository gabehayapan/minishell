/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 16:19:20 by hanakamu          #+#    #+#             */
/*   Updated: 2025/11/28 17:09:58 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_rd_state
{
	void	*stash;
	int		len;
}	t_rd_state;

char	*get_next_line(int fd);
void	free_stash(t_rd_state *rd_state);
void	*_ft_memchr(t_rd_state rd_state, int c, size_t n);
void	*_ft_memcpy(void *dest, const void *src, size_t n);
void	concat_buffer(t_rd_state *rd_state, char *buffer, int n);

#endif
