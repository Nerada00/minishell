/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyaid <cyaid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 21:55:15 by abdmessa          #+#    #+#             */
/*   Updated: 2024/06/29 04:43:24 by cyaid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	find_word(t_dynamic_arr *arr, char *input, int *_i)
{
	int	j;
	int	i;

	j = *_i;
	while (1)
	{
		i = j;
		if (is_valid_quote(input, j) == true)
		{
			++j;
			if ((input[j] != input[i]) && handle_quoted_word(arr, input, i,
					&j) == false)
				return (false);
		}
		else if (ft_is_in(PIPE_INF_OUT_SPACE, input[i]) == true)
			break ;
		else if (handle_unquoted_word(arr, input, i, &j) == false)
			return (false);
		++j;
		if (input[j] == 0)
			break ;
	}
	*_i = j;
	return (true);
}

char	*get_word(char *input, int *_i)
{
	t_dynamic_arr	arr;
	char			*word;

	if (dynamic_arr_init_stack_dynamic_arr(&arr,
			DEFAULT_COMMAND_CAPACITY) == false)
		return (NULL);
	if (find_word(&arr, input, _i) == false)
		return (NULL);
	word = ft_strjoin_tab_with_len(arr.tab, arr.len);
	ft_free_tab_with_len(arr.tab, arr.len);
	return (word);
}

bool	handle_dollars(t_dynamic_arr *arr, char **env, char *input, int *_j)
{
	int		i;
	int		j;
	char	token;
	char	*var_env;

	j = *_j;
	i = j + 1;
	while (input[++j] && !ft_is_in(STOP_TOKEN_WORD, input[j]))
		;
	token = input[j];
	input[j] = 0;
	var_env = get_env_var_value(env, &input[i]);
	if (var_env != NULL)
	{
		var_env = ft_strdup(var_env);
		if (var_env == NULL)
			return (false);
	}
	if (dynamic_arr_push_back(arr, var_env) == -1)
		return (false);
	input[j] = token;
	*_j = j;
	return (true);
}

bool	add_word(t_dynamic_arr *arr, char *input, int i, int j)
{
	char	token;
	char	*dup;

	token = input[j];
	input[j] = 0;
	dup = ft_strdup(&input[i]);
	if (dup == NULL || dynamic_arr_push_back(arr, dup) == -1)
		return (false);
	input[j] = token;
	return (true);
}
