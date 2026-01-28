/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 01:08:17 by keitotak          #+#    #+#             */
/*   Updated: 2026/01/29 08:50:40 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"
#include "get_next_line.h"

int	heredoc(char *doc)
{
	char	*marker;
	int		fd[2];
	char	*line;

	marker = ft_strjoin(doc, "\n");
	if (pipe(fd) < -1)
		return (-1);
	while (1)
	{
		ft_dprintf(STDOUT_FILENO, "> ");
		line = get_next_line(STDIN_FILENO);
		if (line == NULL)
			return (-1);
		if (ft_strcmp(marker, line) == 0)
		{
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		free(line);
	}
	close(fd[1]);
	free(marker);
	return (fd[0]);
}

int	setfd_infile(t_command *command)
{
	while (command->inrdt != NULL)
	{
		if (command->inrdt->type == INFILE)
		{
			command->infd = open(command->inrdt->rdt, O_RDONLY);
			if (command->infd == -1)
			{
				ft_dprintf(2, "-minishell: ");
				perror(command->inrdt->rdt);
				return (FAILURE);
			}
		}
		if (command->inrdt->type == HEREDOC)
			command->infd = heredoc(command->inrdt->rdt);
		dup2(command->infd, command->inrdt->fd_rdt);
		command->inrdt = command->inrdt->next;
	}
	return (SUCCESS);
}

int	setfd_outfile(t_command *command)
{
	while (command->outrdt != NULL)
	{
		if (command->outrdt->type == OUTFILE)
			command->outfd = open(command->outrdt->rdt,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (command->outrdt->type == APPEND)
			command->outfd = open(command->outrdt->rdt,
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		dup2(command->outfd, command->outrdt->fd_rdt);
		command->outrdt = command->outrdt->next;
	}
	return (SUCCESS);
}

int	redirect_fd(t_command *command)
{
	int	is_success;

	if (command->inrdt)
	{
		is_success = setfd_infile(command);
		if (is_success == FAILURE)
			return (FAILURE);
		close(command->infd);
	}
	if (command->outrdt)
	{
		setfd_outfile(command);
		close(command->outfd);
	}
	return (SUCCESS);
}
