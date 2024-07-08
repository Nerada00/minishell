/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdmessa <abdmessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 21:50:36 by abdmessa          #+#    #+#             */
/*   Updated: 2024/06/29 01:26:33 by abdmessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_var_env(
	t_minishell *sh, t_dynamic_arr *env, t_dynamic_arr *command)
{
	int		index;
	char	**cmd;
	size_t	i;
	size_t	len;

	if (env == NULL)
		return ;
	i = 0;
	cmd = command->tab;
	len = command->len;
	while (++i < len)
	{
		index = get_env_var_index(env-> tab, cmd[i]);
		if (index < 0)
			continue ;
		if (check_env_key(cmd[i], "PATH") == 0)
			sh->path = ft_free_tab(sh->path);
		dynamic_arr_remove_element_by_index(env, index);
	}
}

int	builtin_ft_unset(t_minishell *sh, t_command *command, bool in_fork)
{
	(void)in_fork;
	if (sh->nb_commands == 1)
		unset_var_env(sh, &sh->env, command->commands);
	return (0);
}
