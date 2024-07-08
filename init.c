/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyaid <cyaid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 04:43:41 by cyaid             #+#    #+#             */
/*   Updated: 2024/06/29 04:55:05 by cyaid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_sh(t_minishell *sh, char **envp, int argc, char **argv)
{
	(void)argc;
	(void)argv;
	handle_signals();
	memset(sh, 0, sizeof(t_minishell));
	sh->builtins[ENV] = builtin_ft_env;
	sh->builtins[EXPORT] = builtin_ft_export;
	sh->builtins[CD] = builtin_ft_cd;
	sh->builtins[ECHO] = builtin_ft_echo;
	sh->builtins[UNSET] = builtin_ft_unset;
	sh->builtins[PWD] = builtin_ft_pwd;
	sh->builtins[EXIT] = builtin_ft_exit;
	sh->prev_pipes = -1;
	if (init_env(sh, &sh->env, envp) == KO)
		return (OK);
	sh->fd[1] = -1;
	return (OK);
}
