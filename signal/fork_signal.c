/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdmessa <abdmessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 21:54:38 by abdmessa          #+#    #+#             */
/*   Updated: 2024/06/28 21:54:39 by abdmessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sigquit_handler(int sig)
{
	(void)sig;
	write(1, "Quit (core dumped)\n", 19);
	exit(131);
}

void	handle_signals_in_fork(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, sigquit_handler);
}
