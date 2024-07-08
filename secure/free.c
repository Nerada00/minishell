/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdmessa <abdmessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 21:54:33 by abdmessa          #+#    #+#             */
/*   Updated: 2024/06/28 21:54:34 by abdmessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_list(t_token *node)
{
	t_token	*next;

	while (node)
	{
		next = node->next;
		free(node->str);
		free(node);
		node = next;
	}
}

void	free_commands(t_command **_command, t_command **last_command)
{
	t_command	*command;
	t_command	*tmp;

	command = *_command;
	while (command)
	{
		if (command->delimiter != NULL)
			close_fd(&command->fd[0]);
		free_list(command->redirections);
		dynamic_arr_clear(command->commands);
		tmp = command->next;
		free(command);
		command = tmp;
	}
	*_command = NULL;
	*last_command = NULL;
}

void	reset_struct(t_minishell *sh, t_command *command)
{
	if (command != NULL)
	{
		if (command->next != NULL)
		{
			close_fd(&command->infile_fd);
			close_fd(&command->outfile_fd);
			close_fd(&sh->fd[0]);
			close_fd(&sh->fd[1]);
		}
		close_fd(&sh->prev_pipes);
	}
	ft_free_elem((void **)&sh->user_input);
	free_commands(&sh->command, &sh->last_command);
	sh->prev_pipes = -1;
	sh->nb_commands = 0;
}

void	free_and_exit(t_minishell *sh, t_command *command, int code, bool err)
{
	if (err)
		perror("minishell: ");
	ft_free_tab(sh->env.tab);
	ft_free_tab(sh->path);
	reset_struct(sh, command);
	exit(code);
}
