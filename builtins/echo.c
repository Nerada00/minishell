/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdmessa <abdmessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 21:50:00 by abdmessa          #+#    #+#             */
/*   Updated: 2024/06/29 01:02:24 by abdmessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// fonction qui check le flag -n
bool	check_n_option(char *arg)
{
	size_t	i;

	i = 0;
	if (arg == NULL || arg[i] != '-')
		return (false);
	++i;
	if (!arg[i])
		return (false);
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

// fonction check options
void	check_options(char **argv, size_t *_i)
{
	size_t	i;

	i = *_i + 1;
	while (argv[i])
	{
		if (check_n_option(argv[i]) == false)
			break ;
		++i;
	}
	*_i = i;
}

void	print_args(t_command *command, size_t i, bool is_new_line_opt)
{
	char	**args;
	size_t	len;

	args = command -> commands -> tab;
	len = command -> commands -> len;
	while (i < len)
	{
		if ((write(STDOUT_FILENO, args[i], ft_strlen(args[i])) == -1)
			|| (i + 1 != len && write(STDOUT_FILENO, " ", 1) == -1))
		{
			is_new_line_opt = true;
			print_error_and_set_exit_status(NULL, EXIT_FAILURE);
			break ;
		}
		++i;
	}
	if (is_new_line_opt == false && write(STDOUT_FILENO, "\n", 1) == -1)
		print_error_and_set_exit_status(NULL, EXIT_FAILURE);
}

// fonction principal echo
int	builtin_ft_echo(t_minishell *sh, t_command *command, bool in_fork)
{
	t_dynamic_arr	*cmd;
	size_t			i;
	bool			is_new_line_opt;

	(void)in_fork;
	(void)sh;
	cmd = command -> commands;
	i = 1;
	is_new_line_opt = check_n_option(cmd->tab[i]);
	if (is_new_line_opt == true)
		check_options(cmd->tab, &i);
	print_args(command, i, is_new_line_opt);
	return (0);
}
