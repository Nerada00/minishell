/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_user_input.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdmessa <abdmessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 21:55:12 by abdmessa          #+#    #+#             */
/*   Updated: 2024/06/28 21:55:13 by abdmessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_valid_inf_out(const char *input, int *_i, char token)
{
	int	count;
	int	i;

	count = 1;
	i = *_i;
	while (input[++i] && (input[i] == token))
		++count;
	if (count > 2)
		return (false);
	while (input[i] && ft_isspace(input[i]) == 1)
		++i;
	if (input[i] == 0 || ft_is_in(PIPE_INF_OUT, input[i]) == true)
		return (false);
	return (true);
}

bool	is_valid_token(const char *input, int *_i, char token)
{
	int	i;
	int	j;

	i = *_i;
	if (token == TOKEN_INF && is_valid_inf_out(input, _i, input[i]) == false)
		return (false);
	else if (token == TOKEN_SUP
		&& is_valid_inf_out(input, _i, input[i]) == false)
		return (false);
	else
	{
		j = i;
		while (input[++i] && ft_isspace(input[i]) == 1)
			;
		if (input[i] == '|' || input[i] == 0)
			return (false);
		while (--j >= 0 && ft_isspace(input[j]) == 1)
			;
		if (i == -1)
			return (false);
	}
	*_i = i - 1;
	return (true);
}

static bool	print_err(const char *err)
{
	print_msg_stderr(err);
	return (true);
}

bool	is_valid_user_input(char *input, int i)
{
	bool	err;
	char	quote;

	err = false;
	while (input[++i])
	{
		if (is_valid_quote(input, i))
		{
			quote = input[i];
			while (input[++i] && is_end_quote(input[i], quote) == false)
				;
			if (input[i] == '\0')
			{
				err = print_err(MISSING_QUOTES);
				break ;
			}
		}
		if (ft_is_in(PIPE_INF_OUT, input[i]) == true
			&& is_valid_token(input, &i, input[i]) == false)
			err = print_err(SYNTAX_ERROR);
	}
	if (err == true)
		return (free(input), false);
	return (true);
}
