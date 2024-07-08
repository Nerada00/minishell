/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyaid <cyaid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 04:38:45 by cyaid             #+#    #+#             */
/*   Updated: 2024/06/29 04:38:45 by cyaid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fd(int *fd)
{
	if (fd == NULL || *fd <= 0)
		return ;
	close(*fd);
	*fd = -1;
}

void	close_infile_outfile(t_command *command)
{
	if (command == NULL)
		return ;
	close_fd(&command->infile_fd);
	close_fd(&command->outfile_fd);
}
