/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyaid <cyaid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 21:49:49 by abdmessa          #+#    #+#             */
/*   Updated: 2024/06/29 04:41:57 by cyaid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_builtin_id(t_command *command)
{
	char	*cmd;

	if (command->commands == NULL)
		return ;
	cmd = command->commands->tab[0];
	if (ft_strcmp("env", cmd) == 0)
		command->builtin_id = ENV;
	else if (ft_strcmp("export", cmd) == 0)
		command->builtin_id = EXPORT;
	else if (ft_strcmp("pwd", cmd) == 0)
		command->builtin_id = PWD;
	else if (ft_strcmp("cd", cmd) == 0)
		command->builtin_id = CD;
	else if (ft_strcmp("echo", cmd) == 0)
		command->builtin_id = ECHO;
	else if (ft_strcmp("unset", cmd) == 0)
		command->builtin_id = UNSET;
	else if (ft_strcmp("exit", cmd) == 0)
		command->builtin_id = EXIT;
	else
		command->builtin_id = NONE;
}

//	fonction qui gere les builtins
int	call_builtin(t_minishell *sh, t_command *command, bool in_fork)
{
	enum e_builtin_id	builtin_id;
	int					ret;
	int					save_stdout;

	save_stdout = -1;
	builtin_id = command->builtin_id;
	if (builtin_id == NONE)
		return (0);
	g_signum = 0;
	if (try_open_close_redirection_builtin(sh, command, command->redirections,
			&save_stdout) == KO)
		return (print_error_and_set_exit_status(NULL, EXIT_FAILURE));
	ret = sh->builtins[builtin_id](sh, command, in_fork);
	if (save_stdout != -1)
		dup_wrapper(&save_stdout, STDOUT_FILENO);
	close_infile_outfile(command);
	return (ret);
}

int	builtin_dup_and_save_stdout(t_minishell *sh, t_command *command)
{
	int	*fd;
	int	save_fd;

	save_fd = -1;
	fd = &command->outfile_fd;
	if (*fd == -1)
		fd = &sh->fd[1];
	if (*fd != -1)
	{
		save_fd = dup_and_save(fd, STDOUT_FILENO);
		if (save_fd == -1)
			free_and_exit_failure(sh, command);
	}
	return (save_fd);
}

void	builtin_restore_stdout(t_minishell *sh, t_command *command, int save_fd)
{
	if (save_fd > 0)
	{
		if (dup2(save_fd, STDOUT_FILENO) == -1)
			free_and_exit_failure(sh, command);
		close(save_fd);
	}
}
