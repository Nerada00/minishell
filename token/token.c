/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdmessa <abdmessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 21:55:08 by abdmessa          #+#    #+#             */
/*   Updated: 2024/06/28 22:02:22 by abdmessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_new_redirection_to_command_node(
		t_command *command, t_token *redirection, enum e_token type)
{
	if (type == TOKEN_INF || type == TOKEN_DINF)
		command->infile = redirection;
	else
		command->outfile = redirection;
	if (command->redirections == NULL)
	{
		command->redirections = redirection;
		command->last_redirection = redirection;
		return ;
	}
	command->last_redirection->next = redirection;
	command->last_redirection = redirection;
}

int	set_new_redirection_node(
		t_minishell *sh, enum e_token type, int *_i, char *input)
{
	int				i;
	t_command		*command;
	t_token			*redirection_node;
	char			*redirection_name;

	i = *_i;
	if (sh->last_command == NULL && add_new_command_info_node(sh) == KO)
		return (KO);
	command = sh->last_command;
	while (input[i] && ft_isspace(input[i]))
		++i;
	*_i = i;
	redirection_name = get_word(input, _i);
	redirection_node = ft_calloc(sizeof(t_token), 1);
	if (redirection_name == NULL || redirection_node == NULL)
		return (KO);
	redirection_node->type = type;
	redirection_node->str = redirection_name;
	add_new_redirection_to_command_node(command, redirection_node, type);
	return (OK);
}

// Fonction pour traiter les opérateurs de redirection
int	process_redirect_operators(t_minishell *sh, char *input, int *_i)
{
	int				i;	
	enum e_token	type;

	i = (*_i + 1);
	if (input[i - 1] == '|' && add_new_command_info_node(sh) == KO)
		return (KO);
	else if (input[i - 1] != '|')
	{
		type = TOKEN_DSUP;
		if (input[i - 1] == '>' && input[i] == '>')
			++i;
		else if (input[i - 1] == '<' && input[i] == '<')
		{
			type = TOKEN_DINF;
			++i;
		}
		else if (input[i - 1] == '<')
			type = TOKEN_INF;
		else
			type = TOKEN_SUP;
		if (set_new_redirection_node(sh, type, &i, input) == KO)
			return (KO);
	}
	*_i = i;
	return (OK);
}

// Fonction pour traiter le token WORD
int	process_words(t_minishell *sh, char *input, int *i)
{
	t_command	*command;
	char		*word;

	if (sh->last_command == NULL && add_new_command_info_node(sh) == KO)
		return (KO);
	command = sh->last_command;
	if (command->commands == NULL
		&& init_dynamic_arr_for_command(
			command, DEFAULT_COMMAND_CAPACITY) == false)
		return (KO);
	word = get_word(input, i);
	if (word == NULL || dynamic_arr_push_back(command->commands, word) == -1)
		return (free(word), KO);
	return (OK);
}

bool	tokenize(t_minishell *sh, char *input, int err)
{
	int		i;
	bool	is_heredoc;

	i = 0;
	is_heredoc = false;
	while (input[i])
	{
		if (is_valid_quote(input, i)
			|| ft_is_in(PIPE_INF_OUT_SPACE, input[i]) == false)
			err = process_words(sh, input, &i);
		else if (ft_is_in(PIPE_INF_OUT, input[i]) == true)
		{
			if (is_heredoc == false && input[i] == '<' && input[i + 1] == '<')
				is_heredoc = true;
			err = process_redirect_operators(sh, input, &i);
		}
		else
			++i;
		if (err == KO)
			free_and_exit_failure_message(sh, NULL, "syscall: malloc failed\n");
		while (input[i] && ft_isspace(input[i]))
			++i;
	}
	return (is_heredoc);
}
