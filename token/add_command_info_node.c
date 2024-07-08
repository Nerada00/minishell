/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_command_info_node.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdmessa <abdmessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 21:54:57 by abdmessa          #+#    #+#             */
/*   Updated: 2024/06/28 21:54:58 by abdmessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_command_info_node(t_minishell *sh, t_command *node)
{
	if (sh->command == NULL)
	{
		sh->command = node;
		sh->last_command = node;
	}
	else
	{
		sh->last_command->next = node;
		sh->last_command = node;
	}
}

int	add_new_command_info_node(t_minishell *sh)
{
	t_command	*node;

	node = ft_calloc(sizeof(t_command), 1);
	if (node == NULL)
		return (KO);
	node->infile_fd = -1;
	node->outfile_fd = -1;
	node->builtin_id = NONE;
	add_command_info_node(sh, node);
	++sh->nb_commands;
	return (OK);
}

bool	init_dynamic_arr_for_command(t_command *command, size_t capacity)
{
	t_dynamic_arr	*arr;

	arr = dynamic_arr_init_dynamic_arr(capacity);
	if (arr == NULL)
		return (false);
	command->commands = arr;
	return (true);
}
