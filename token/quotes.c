/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdmessa <abdmessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 21:55:02 by abdmessa          #+#    #+#             */
/*   Updated: 2024/06/28 21:55:03 by abdmessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_valid_quote(const char *input, int i)
{
	return (input[i] == '"' || input[i] == '\'');
}

bool	is_end_quote(char current_char, char quote)
{
	return (current_char == quote);
}

bool	handle_unquoted_word(t_dynamic_arr *arr, char *input, int i, int *_j)
{
	int	j;

	j = *_j;
	while (1)
	{
		if (input[j] == 0 || ft_is_in(STOP_TOKEN_REDIR, input[j]) == true)
		{
			if (add_word(arr, input, i, j) == false)
				return (false);
			break ;
		}
		++j;
	}
	*_j = j - 1;
	return (true);
}

bool	handle_quoted_word(t_dynamic_arr *arr, char *input, int i, int *_j)
{
	int	j;

	j = *_j;
	while (1)
	{
		if (is_end_quote(input[j], input[i]) == true)
		{
			if (add_word(arr, input, i + 1, j) == false)
				return (false);
			break ;
		}
		++j;
	}
	*_j = j;
	return (true);
}
