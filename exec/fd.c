/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyaid <cyaid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 04:40:24 by cyaid             #+#    #+#             */
/*   Updated: 2024/06/29 04:40:25 by cyaid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_open_flag(enum e_token type)
{
	if (type == TOKEN_INF)
		return (O_RDONLY);
	else if (type == TOKEN_SUP)
		return (O_CREAT | O_TRUNC | O_WRONLY);
	else if (type == TOKEN_DSUP)
		return (O_CREAT | O_APPEND | O_WRONLY);
	else
		return (-1);
}

int	try_open_close_redirection(t_token *redirection)
{
	int	fd;
	int	open_flags;

	while (redirection)
	{
		open_flags = get_open_flag(redirection->type);
		if (open_flags != -1)
		{
			fd = open(redirection->str, open_flags, 0644);
			if (fd == -1)
				return (KO);
			else if ((open_flags == O_RDONLY && dup2(fd, STDIN_FILENO) == -1)
				|| (open_flags != O_RDONLY && dup2(fd, STDOUT_FILENO) == -1))
				return (close(fd), KO);
			close(fd);
		}
		redirection = redirection->next;
	}
	return (OK);
}

int	open_pipe_builtin(t_minishell *sh, t_command *command, int *save_stdout)
{
	if (command->outfile == NULL)
	{
		if (command && command->commands && ft_strcmp(command->commands->tab[0],
				"exit") != 0)
			*save_stdout = dup(STDOUT_FILENO);
		return (dup_wrapper(&sh->fd[1], STDOUT_FILENO));
	}
	return (OK);
}

int	try_open_close_redirection_builtin(t_minishell *sh, t_command *command,
		t_token *redirection, int *save_stdout)
{
	int	fd;
	int	open_flags;

	while (redirection)
	{
		open_flags = get_open_flag(redirection->type);
		if (open_flags != -1)
		{
			fd = open(redirection->str, open_flags, 0644);
			if (fd == -1)
				return (KO);
			else if (open_flags != O_RDONLY)
			{
				if (*save_stdout == -1 && (command && command->commands
						&& ft_strcmp(command->commands->tab[0], "exit") != 0))
					*save_stdout = dup(STDOUT_FILENO);
				if (dup2(fd, STDOUT_FILENO) == -1)
					return (close(fd), KO);
			}
			close(fd);
		}
		redirection = redirection->next;
	}
	return (open_pipe_builtin(sh, command, save_stdout));
}

int	redirect_stdout_stdin(t_minishell *sh, t_command *command)
{
	int	*infile_fd;
	int	*outfile_fd;

	outfile_fd = NULL;
	if (command->next != NULL)
		close_fd(&sh->fd[0]);
	if (command->delimiter != NULL)
		infile_fd = &command->fd[0];
	else
		infile_fd = &sh->prev_pipes;
	if (command->outfile == NULL)
		outfile_fd = &sh->fd[1];
	if (dup_wrapper(infile_fd, STDIN_FILENO) == KO || (outfile_fd
			&& dup_wrapper(outfile_fd, STDOUT_FILENO) == KO))
		return (KO);
	return (OK);
}
