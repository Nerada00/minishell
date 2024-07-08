/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyaid <cyaid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 04:38:56 by cyaid             #+#    #+#             */
/*   Updated: 2024/06/29 04:38:57 by cyaid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dup_wrapper(int *_fd, int old_fd)
{
	int	fd;

	fd = *_fd;
	if (fd > 0 && dup2(fd, old_fd) == -1)
		return (close_fd(_fd), KO);
	close_fd(_fd);
	return (OK);
}

int	dup_and_save(int *fd, int old_fd)
{
	int	save_stdout;

	save_stdout = dup(old_fd);
	if (save_stdout == -1 || dup2(*fd, old_fd) == -1)
		return (-1);
	close_fd(fd);
	return (save_stdout);
}
