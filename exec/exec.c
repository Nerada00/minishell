/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyaid <cyaid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 04:39:05 by cyaid             #+#    #+#             */
/*   Updated: 2024/06/29 04:39:35 by cyaid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*is_valid_cmd(t_minishell *sh, t_command *command, char *cmd,
		char **first_args)
{
	char	*valid_path;
	char	**path;
	size_t	i;

	i = -1;
	path = sh->path;
	while (path[++i])
	{
		valid_path = ft_strjoin(path[i], cmd);
		if (valid_path == NULL)
		{
			free(cmd);
			free_and_exit_failure_message(sh, command,
				"syscall: malloc failed");
		}
		if (access(valid_path, X_OK) == 0)
			return (free(cmd), ft_free_elem((void **)first_args), valid_path);
		free(valid_path);
	}
	free(cmd);
	return (NULL);
}

void	execute(t_minishell *sh, t_command *command, bool slashed_path)
{
	t_dynamic_arr	*arr;
	char			**cmd;
	char			*first_arg;
	char			*preprended_cmd;

	arr = command->commands;
	cmd = arr->tab;
	if ((slashed_path == false && sh->path == NULL))
		return ;
	first_arg = cmd[0];
	if (slashed_path == true)
		execve(first_arg, cmd, sh->env.tab);
	else
	{
		preprended_cmd = ft_strjoin("/", cmd[0]);
		if (preprended_cmd == NULL)
			free_and_exit_failure(sh, command);
		first_arg = is_valid_cmd(sh, command, preprended_cmd, &cmd[0]);
		if (first_arg == NULL)
			return ;
		cmd[0] = first_arg;
		execve(first_arg, cmd, sh->env.tab);
		ft_free_elem((void **)&cmd[0]);
	}
}

void	wait_all_child_process(t_command *node)
{
	bool	nl;
	int		save_signal;

	nl = true;
	save_signal = g_signum;
	close_doc(node, true, false);
	while (node)
	{
		if (node->pid > 0)
		{
			waitpid(node->pid, &g_signum, 0);
			if (nl == true && g_signum != BROKEN_PIPE && WIFSIGNALED(g_signum))
			{
				if (g_signum == SIGINT)
					g_signum += 128;
				write_nl(&nl);
			}
			if (node->next == NULL && WIFEXITED(g_signum))
				g_signum = WEXITSTATUS(g_signum);
		}
		else if (node->next == NULL && node->builtin_id != NONE)
			g_signum = save_signal;
		node = node->next;
	}
	signal(SIGINT, sigint_handler);
}

void	execute_command(t_minishell *sh, t_command *command)
{
	handle_signals_in_fork();
	if (try_open_close_redirection(command->redirections) == KO)
		free_and_exit_failure(sh, command);
	if (redirect_stdout_stdin(sh, command) == KO)
		free_and_exit_failure(sh, command);
	if (command->builtin_id == NONE && command->commands != NULL)
	{
		execute(sh, command, ft_strchr(command->commands->tab[0], '/'));
		free_and_exit_failure_message(sh, command,
			"minishell: command not found\n");
	}
	else if (command->builtin_id != NONE)
		sh->builtins[command->builtin_id](sh, command, true);
	free_and_exit(sh, command, g_signum, false);
}

void	exec_command(t_minishell *sh, t_command *command)
{
	signal(SIGINT, SIG_IGN);
	while (command)
	{
		if (command->next && pipe(sh->fd) == -1)
			return ;
		if (check_if_command_must_be_forked(sh, command, false) == true)
		{
			command->pid = fork();
			if (command->pid == -1)
				return ;
			if (command->pid == 0)
				execute_command(sh, command);
		}
		close_fd(&sh->fd[1]);
		if (sh->prev_pipes != -1)
			close(sh->prev_pipes);
		sh->prev_pipes = sh->fd[0];
		command = command->next;
	}
	wait_all_child_process(sh->command);
}
