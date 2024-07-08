/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyaid <cyaid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 04:38:02 by cyaid             #+#    #+#             */
/*   Updated: 2024/06/29 04:39:38 by cyaid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_if_command_must_be_forked(t_minishell *sh, t_command *command,
		bool in_fork)
{
	get_builtin_id(command);
	if (command->builtin_id == NONE)
		return (true);
	return (call_builtin(sh, command, in_fork));
}

void	write_nl(bool *nl)
{
	ft_putchar_fd('\n', 0);
	rl_on_new_line();
	*nl = false;
}
