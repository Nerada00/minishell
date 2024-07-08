/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdmessa <abdmessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 21:50:04 by abdmessa          #+#    #+#             */
/*   Updated: 2024/06/28 22:48:21 by abdmessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_env_key(char *env_var, char *to_check)
{
	int		i;
	int		res;
	bool	equal;

	i = -1;
	equal = false;
	if (to_check[0] == 0)
		return (1);
	while (env_var[++i] && env_var[i] != '=')
		;
	if (env_var[i] == '=')
	{
		equal = true;
		env_var[i] = 0;
	}
	res = ft_strcmp(env_var, to_check);
	if (equal == true)
		env_var[i] = '=';
	return (res);
}

int	get_env_var_index(char **tab, char *to_find)
{
	int		i;
	int		j;
	char	stop;

	j = -1;
	i = -1;
	while (to_find[++j] && to_find[j] != '=')
		;
	stop = to_find[j];
	to_find[j] = 0;
	while (tab[++i])
		if (!check_env_key(tab[i], to_find))
			break ;
	to_find[j] = stop;
	if (tab[i] == 0)
		return (-1);
	return (i);
}

char	*get_env_var_value(char **tab, char *to_find)
{
	size_t	i;

	i = -1;
	if (tab == NULL)
		return (NULL);
	if (ft_strcmp(to_find, "?") == 0)
		return (ft_itoa(g_signum));
	while (tab[++i])
	{
		if (tab[i][0] == to_find[0] && !check_env_key(tab[i], to_find))
			return (tab[i] + ft_strlen(to_find) + 1);
	}
	return (NULL);
}

int	init_env(t_minishell *sh, t_dynamic_arr *env, char **envp)
{
	char	*path;
	char	*cmd;
	size_t	i;

	if (dynamic_arr_init_stack_dynamic_arr(env, CAPACITY) == false)
		return (KO);
	i = -1;
	while (envp[++i])
	{
		cmd = ft_strdup(envp[i]);
		if (cmd == NULL || dynamic_arr_push_back(env, cmd) == -1)
			return (KO);
	}
	path = get_env_var_value(envp, "PATH");
	if (path != NULL)
	{
		sh->path = ft_split(path, ':');
		if (sh->path == NULL)
			return (KO);
	}
	return (OK);
}
