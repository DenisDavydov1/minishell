/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbie <abarbie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 22:42:44 by odhazzar          #+#    #+#             */
/*   Updated: 2020/10/22 01:31:06 by abarbie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		msh_set_fd(t_ms *ms)
{
	int fd;

	fd = 1;
	if (ms->cmd->write == -1)
		fd = 2;
	else if (ms->cmd->write == 0)
		fd = 1;
	else if (ms->cmd->write == 1)
	{
		if ((fd = open(ms->cmd->file, O_CREAT | O_WRONLY | O_TRUNC, 0644)) < 0)
			ft_error(NULL, ms->cmd->file, strerror(errno), ms);
	}
	else if (ms->cmd->write == 2)
	{
		if ((fd = open(ms->cmd->file, O_CREAT | O_WRONLY | O_APPEND, 0644)) < 0)
			ft_error(NULL, ms->cmd->file, strerror(errno), ms);
	}
	return (fd);
}

void	msh_set_pfd(t_ms *ms)
{
	if (ms->cmd->pipe)
	{
		if (pipe(ms->cmd->pfd) == -1)
			throw_error(PIPEERR, NULL);
		if (ms->cmd->fd < 3)
			ms->cmd->fd = ms->cmd->pfd[1];
	}
}

void	close_pfd(t_ms *ms)
{
	if (ms->cmd->pipe)
		close(ms->cmd->pfd[1]);
	if (ms->cmd->prev && ms->cmd->prev->pipe)
		close(ms->cmd->prev->pfd[0]);
	if (ms->cmd->fd > 2)
		close(ms->cmd->fd);
}

char	*get_next_line(char *command)
{
	char		buf[2];
	char		*cpy;

	buf[0] = '\0';
	buf[1] = '\0';
	if (!(read(0, buf, 1)))
		if (write(1, "exit\n", 5))
			exit(EXIT_SUCCESS);
	if (!command)
		command = ft_strdup("");
	while (buf[0] != '\n')
	{
		if (!(cpy = ft_strdup(command)))
			return (NULL);
		free(command);
		if (!(command = ft_strjoin(cpy, buf)))
			return (NULL);
		free(cpy);
		while (!(read(0, buf, 1)))
			write(1, "  \b\b", 4);
	}
	return (command);
}
