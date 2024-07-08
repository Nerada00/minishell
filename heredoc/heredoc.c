/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyaid <cyaid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 04:41:10 by cyaid             #+#    #+#             */
/*   Updated: 2024/06/29 04:41:11 by cyaid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_doc(t_command *command)
{
	while (command)
	{
		if (command->infile && command->infile->type == TOKEN_DINF)
		{
			if (pipe(command->fd) == -1)
				return (KO);
			command->delimiter = command->infile->str;
		}
		command = command->next;
	}
	return (OK);
}

void	close_doc(t_command *command, bool close_read, bool close_write)
{
	while (command != NULL)
	{
		if (command->delimiter)
		{
			if (close_read == true && command->fd[0] != -1)
				close_fd(&command->fd[0]);
			if (close_write == true && command->fd[1] != -1)
				close_fd(&command->fd[1]);
		}
		command = command->next;
	}
}

int	write_into_pipe(int fd, char *delim)
{
	char	*input;
	int		ret;

	ret = OK;
	while (1)
	{
		input = readline(">heredoc ");
		if (input == NULL || ft_strcmp(delim, input) == 0)
		{
			free(input);
			break ;
		}
		if (fd != -1 && (write(fd, input, ft_strlen(input)) == -1 || write(fd,
					"\n", 1) == -1))
		{
			ret = KO;
			break ;
		}
		free(input);
	}
	return (ret);
}

int	handle_heredoc(t_minishell *sh)
{
	int	pid;
	int	ret;

	ret = open_doc(sh->command);
	if (ret == KO)
		return (ret);
	pid = fork();
	if (pid == -1)
		return (KO);
	if (pid == 0)
		child_proccess(sh, sh->command);
	return (parent_process(sh, pid));
}
