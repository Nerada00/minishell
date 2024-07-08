/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error_and_set_exit_status.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdmessa <abdmessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 21:54:07 by abdmessa          #+#    #+#             */
/*   Updated: 2024/06/28 21:54:08 by abdmessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_error_and_set_exit_status(const char *msg, int err_code)
{
	g_signum = err_code;
	if (msg != NULL)
		print_msg_stderr(msg);
	else
		perror("mininshell");
	return (0);
}

int	print_perror_and_set_exit_status(const char *msg, int err_code)
{
	g_signum = err_code;
	perror(msg);
	return (0);
}
