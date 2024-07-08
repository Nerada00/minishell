/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_dynamic_arr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdmessa <abdmessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 21:50:50 by abdmessa          #+#    #+#             */
/*   Updated: 2024/06/28 21:50:51 by abdmessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dynamic_arr_clear(t_dynamic_arr *arr)
{
	char	**cmds;
	size_t	i;
	size_t	len;

	if (arr == NULL)
		return ;
	i = -1;
	cmds = arr->tab;
	len = arr->len;
	while (++i < len)
		free(cmds[i]);
	free(cmds);
	free(arr);
}
