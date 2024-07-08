/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_dynamic_arr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdmessa <abdmessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 21:51:00 by abdmessa          #+#    #+#             */
/*   Updated: 2024/06/28 21:51:01 by abdmessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dynamic_arr	*dynamic_arr_init_dynamic_arr(size_t capacity)
{
	t_dynamic_arr	*arr;

	arr = ft_calloc(sizeof(t_dynamic_arr), 1);
	if (arr == NULL)
		return (NULL);
	arr->capacity = capacity;
	arr->tab = malloc(sizeof(char *) * (capacity + 1));
	if (arr->tab == NULL)
		return (free(arr), NULL);
	return (arr);
}

bool	dynamic_arr_init_stack_dynamic_arr(t_dynamic_arr *arr, size_t capacity)
{
	memset(arr, 0, sizeof(t_dynamic_arr));
	arr->capacity = capacity;
	arr->tab = malloc(sizeof(char *) * (capacity + 1));
	if (arr->tab == NULL)
		return (false);
	return (true);
}
