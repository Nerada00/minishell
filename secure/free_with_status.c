/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_with_status.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdmessa <abdmessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 21:54:28 by abdmessa          #+#    #+#             */
/*   Updated: 2024/06/28 21:54:29 by abdmessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_and_exit_success(t_minishell *sh, t_command *command)
{
	ft_free_tab(sh->path);
	ft_free_tab(sh->env.tab);
	reset_struct(sh, command);
	exit(SUCCESS);
}

void	free_and_exit_failure(t_minishell *sh, t_command *command)
{
	perror("minishell: ");
	ft_free_tab(sh->path);
	ft_free_tab(sh->env.tab);
	reset_struct(sh, command);
	exit(FAILURE);
}

void	free_and_exit_failure_message(
	t_minishell *sh, t_command *command, const char *err_msg)
{
	int	exit_status;

	exit_status = EXIT_FAILURE;
	if (command && command -> commands && errno == 2)
		exit_status = 127;
	write(STDERR_FILENO, err_msg, ft_strlen(err_msg));
	ft_free_tab(sh->path);
	ft_free_tab(sh->env.tab);
	reset_struct(sh, command);
	exit(exit_status);
}

void	free_and_exit_failure_message_and_status(
	t_minishell *sh, t_command *command, const char *err_msg, int err_status)
{
	write(STDERR_FILENO, err_msg, ft_strlen(err_msg));
	ft_free_tab(sh->path);
	ft_free_tab(sh->env.tab);
	reset_struct(sh, command);
	exit(err_status);
}
