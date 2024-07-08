/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdmessa <abdmessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 21:49:56 by abdmessa          #+#    #+#             */
/*   Updated: 2024/06/28 22:01:01 by abdmessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd(t_minishell *sh, t_command *command)
{
	char	old_pwd[1024];
	char	new_pwd[1024];
	char	*cur_path;
	char	**argv;

	argv = command->commands->tab;
	if (getcwd(old_pwd, sizeof(old_pwd)) == NULL && argv[1] != NULL)
		return (print_perror_and_set_exit_status("getcwd() error",
				EXIT_FAILURE));
	if (!argv[1])
	{
		cur_path = get_env_var_value(sh->env.tab, "HOME");
		if (cur_path == NULL)
			return (print_error_and_set_exit_status("cd: HOME not set\n",
					EXIT_FAILURE));
	}
	else
		cur_path = argv[1];
	if (chdir(cur_path) != 0)
		return (print_error_and_set_exit_status(NULL, EXIT_FAILURE));
	if (getcwd(new_pwd, sizeof(new_pwd)) == NULL)
		return (print_perror_and_set_exit_status("getcwd() error",
				EXIT_FAILURE));
	return (0);
}

int	builtin_ft_cd(t_minishell *sh, t_command *command, bool in_fork)
{
	(void)in_fork;
	if (sh->nb_commands == 1)
		return (cd(sh, command));
	return (0);
}
