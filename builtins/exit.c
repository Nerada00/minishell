/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdmessa <abdmessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 21:50:13 by abdmessa          #+#    #+#             */
/*   Updated: 2024/06/28 21:50:14 by abdmessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_is_invalid_arg(char *arg)
{
	size_t	i;

	if (arg == NULL)
		return (false);
	i = 0;
	if ((!ft_isdigit(arg[i]) && (arg[i] != '-' && arg[i] != '+')))
		return (true);
	i++;
	if (!ft_isdigit(arg[i - 1]) && arg[i] == 0)
		return (true);
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (true);
		i++;
	}
	return (false);
}

static long long int	ft_atol(const char *str)
{
	long long int	res;
	long long int	sign;

	res = 0;
	sign = 1;
	if (str == NULL)
		return (0);
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	return (res * sign);
}

//	fonction exit
int	builtin_ft_exit(t_minishell *sh, t_command *command, bool in_fork)
{
	t_dynamic_arr	*cmd;
	char			**args;
	bool			is_invalid;

	cmd = command->commands;
	args = cmd->tab;
	is_invalid = ft_is_invalid_arg(args[1]);
	if (in_fork == false && sh -> nb_commands > 1)
		return (1);
	else if (args[1] == NULL || (is_invalid == false && cmd -> len == 2))
		free_and_exit(sh, command, ft_atol(args[1]), false);
	else
	{
		if (is_invalid == true)
			free_and_exit_failure_message_and_status(
				sh, command, EXIT_ERR_NUM_ARG, 2);
		if (in_fork == true)
			free_and_exit_failure_message_and_status(
				sh, command, EXIT_TOO_MANY_ARGS, 1);
	}
	return (print_error_and_set_exit_status(EXIT_TOO_MANY_ARGS, 1));
}
