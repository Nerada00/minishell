/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyaid <cyaid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 21:50:28 by abdmessa          #+#    #+#             */
/*   Updated: 2024/06/29 04:42:09 by cyaid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_ft_pwd(t_minishell *sh, t_command *command, bool in_fork)
{
	char	path[PATH_MAX + 1];

	(void)sh;
	(void)command;
	(void)in_fork;
	if (getcwd(path, PATH_MAX) != NULL)
		printf("\e[38;5;221m%s\n \033[0m", path);
	else
	{
		g_signum = 1;
		perror("getcwd() error");
	}
	return (0);
}

// fonction pour laffichage avant le prompt (estethique seulement)
void	ft_affpwd(void)
{
	char	path[PATH_MAX + 1];
	char	*last_slash;

	if (getcwd(path, PATH_MAX) != NULL)
	{
		last_slash = strrchr(path, '/');
		if (last_slash)
			printf("\e[38;5;410m > \e[38;5;412m[%s] ➡️ ", last_slash + 1);
		else
			printf("%s", path);
	}
}
