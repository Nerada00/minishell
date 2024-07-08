/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyaid <cyaid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 21:55:25 by abdmessa          #+#    #+#             */
/*   Updated: 2024/06/29 04:44:46 by cyaid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_signum = 0;

char	*clear_and_retrieve_str(t_dynamic_arr *arr, char *expanded_input, int j)
{
	if (j != 0)
	{
		free(expanded_input);
		expanded_input = ft_strjoin_tab_with_len(arr->tab, arr->len);
	}
	ft_free_tab_with_len(arr->tab, arr->len);
	return (expanded_input);
}

void	last_clean(t_minishell *sh)
{
	ft_free_tab(sh->path);
	ft_free_tab(sh->env.tab);
	rl_clear_history();
}

bool	is_expandable_word(const char *input, int i, char quote)
{
	if ((input[i] == '$' && (input[i + 1] && ft_is_in("\t\n\v\f\r $'\"", input[i
						+ 1]) == false)) && (quote == '"' || quote == '\0'))
	{
		while (--i >= 0 && ft_is_in(PIPE_INF_OUT, input[i]) == false)
			;
		if (i > 0 && (input[i] == '<' && input[i - 1] == '<'))
			return (false);
		return (true);
	}
	return (false);
}

char	*expand_str(char **env, char *input, int i, int j)
{
	char			quote;
	t_dynamic_arr	arr;

	if (dynamic_arr_init_stack_dynamic_arr(&arr, 4) == false)
		return (NULL);
	quote = '\0';
	while (1)
	{
		if (quote == '\0' && is_valid_quote(input, i) == true)
			quote = input[i++];
		if (input[i] == 0 || is_expandable_word(input, i, quote))
		{
			if ((i - j > 0 && add_word(&arr, input, j, i) == false)
				|| (input[i] == '$' && handle_dollars(&arr, env, input,
						&i) == false))
				return (ft_free_tab_with_len(arr.tab, arr.len), NULL);
			j = i;
			i = i - (input[j] != '\0');
		}
		if (quote != '\0' && is_end_quote(input[i], quote) == true)
			quote = '\0';
		if (input[i++] == 0)
			break ;
	}
	return (clear_and_retrieve_str(&arr, input, j));
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	sh;
	bool		here_doc;

	init_sh(&sh, envp, argc, argv);
	while (1)
	{
		ft_affpwd();
		sh.user_input = readline(READLINE_PROMPT);
		if (!sh.user_input)
			break ;
		add_history(sh.user_input);
		if (is_valid_user_input(sh.user_input, -1) == false)
			continue ;
		sh.user_input = expand_str(sh.env.tab, sh.user_input, 0, 0);
		if (sh.user_input == NULL)
			break ;
		here_doc = tokenize(&sh, sh.user_input, OK);
		ft_free_elem((void **)&sh.user_input);
		if (sh.command == NULL || (here_doc && handle_heredoc(&sh)) == KO)
			continue ;
		exec_command(&sh, sh.command);
		reset_struct(&sh, NULL);
	}
	last_clean(&sh);
}
