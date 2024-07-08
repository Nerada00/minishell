/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyaid <cyaid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 21:50:24 by abdmessa          #+#    #+#             */
/*   Updated: 2024/06/29 04:42:03 by cyaid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_not_valid_syntax(const char *env_var)
{
	if (ft_strchr(env_var, '=') == NULL)
		return (1);
	if (ft_isdigit(env_var[0]))
		return (print_error_and_set_exit_status("not a valid identifier",
				EXIT_FAILURE), 1);
	return (0);
}

int	export_var(t_minishell *sh, t_dynamic_arr *env, char **envp, char *env_var)
{
	int		index;
	char	*duplicate_str;

	if (is_not_valid_syntax(env_var) == 1)
		return (0);
	index = get_env_var_index(envp, env_var);
	duplicate_str = ft_strdup(env_var);
	if (duplicate_str == NULL)
		return (KO);
	if (index > -1)
		dynamic_arr_update_element_by_index(env, index, duplicate_str);
	else
	{
		index = dynamic_arr_push_back(env, duplicate_str);
		if (index == -1)
			return (KO);
	}
	if (check_env_key(env_var, "PATH") == 0)
	{
		sh->path = ft_split(env->tab[index] + 5, ':');
		if (sh->path == NULL)
			return (KO);
	}
	return (OK);
}

void	display_env2(t_dynamic_arr *env)
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
		printf("\e[38;5;414mexport %s\n", tab[i]);
}

int	builtin_ft_export(t_minishell *sh, t_command *command, bool in_fork)
{
	t_dynamic_arr	*env;
	char			**cmd;
	size_t			i;
	size_t			len;

	(void)in_fork;
	i = 0;
	env = &sh->env;
	len = command->commands->len;
	cmd = command->commands->tab;
	if (len == 1)
		display_env2(env);
	else if (sh->nb_commands == 1)
	{
		while (++i < len)
			if (export_var(sh, env, env->tab, cmd[i]) == KO)
				free_and_exit_failure(sh, command);
	}
	return (0);
}
