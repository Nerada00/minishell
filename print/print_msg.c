/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdmessa <abdmessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 21:54:11 by abdmessa          #+#    #+#             */
/*   Updated: 2024/06/28 21:54:12 by abdmessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_msg(const char *msg, int fd)
{
	write(fd, msg, ft_strlen(msg));
}

void	print_msg_stderr(const char *msg)
{
	print_msg(msg, STDERR_FILENO);
}

void	print_msg_stdout(const char *msg)
{
	print_msg(msg, STDOUT_FILENO);
}
