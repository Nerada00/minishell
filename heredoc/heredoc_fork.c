/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_fork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyaid <cyaid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 04:40:48 by cyaid             #+#    #+#             */
/*   Updated: 2024/06/29 04:40:48 by cyaid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parent_process(t_minishell *sh, int children_pid)
{
	int		status;

	signal(SIGINT, SIG_IGN);
	close_doc(sh->command, false, true);
	if (waitpid(children_pid, &status, 0) == -1)
	{
		close_doc(sh->command, true, false);
		return (KO);
	}
	if (WIFEXITED(status))
	{
		g_signum = WEXITSTATUS(status);
		if (g_signum == 130)
		{
			rl_on_new_line();
			return (KO);
		}
	}
	return (OK);
}

void	child_proccess(t_minishell *sh, t_command *command)
{
	int			fd;
	t_token		*redirection;

	close_doc(command, true, false);
	set_heredoc_signal();
	while (command != NULL)
	{
		redirection = command->redirections;
		while (redirection)
		{
			if (redirection->type == TOKEN_DINF)
			{
				fd = -1;
				if (command->delimiter == redirection->str)
					fd = command->fd[1];
				if (write_into_pipe(fd, redirection->str) == KO)
					break ;
			}
			redirection = redirection->next;
		}
		command = command->next;
	}
	close_doc(sh->command, false, true);
	free_and_exit_success(sh, NULL);
}
