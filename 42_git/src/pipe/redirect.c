/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 01:08:17 by keitotak          #+#    #+#             */
/*   Updated: 2026/01/24 01:10:24 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

int	setfd_infile(t_command *command)
{
	while (command->inrdt != NULL)
	{
		if (command->inrdt->type == INFILE)
			command->infd = open(command->inrdt->rdt, O_RDONLY);
		if (command->inrdt->type == HEREDOC)
			command->infd = STDIN_FILENO;
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
		command->outrdt = command->outrdt->next;
	}
	return (SUCCESS);
}

int	redirect_fd(t_command *command)
{
	if (command->inrdt)
	{
		setfd_infile(command);
		dup2(command->infd, STDIN_FILENO);
	}
	if (command->outrdt)
	{
		setfd_outfile(command);
		dup2(command->outfd, STDOUT_FILENO);
	}
	return (SUCCESS);
}
