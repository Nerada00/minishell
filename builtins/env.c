/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdmessa <abdmessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 21:50:09 by abdmessa          #+#    #+#             */
/*   Updated: 2024/06/29 01:03:23 by abdmessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// affichage de lenv pour le builtins
void	display_env(t_dynamic_arr *env)
{
	size_t	i;
	size_t	len;
	char	**tab;

	tab = env->tab;
	if (!tab)
		return ;
	len = env->len;
	i = -1;
	while (++i < len)
		printf("%s\n", tab[i]);
}

int	builtin_ft_env(t_minishell *sh, t_command *command, bool in_fork)
{
	t_dynamic_arr	*env;
	size_t			len;

	(void)in_fork;
	env = &sh->env;
	len = command->commands->len;
	if (len > 1)
		print_error_and_set_exit_status("env: too many args\n", 127);
	else
		display_env(env);
	return (0);
}
