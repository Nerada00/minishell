/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdmessa <abdmessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 21:50:56 by abdmessa          #+#    #+#             */
/*   Updated: 2024/06/28 21:50:57 by abdmessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	dynamic_arr_grow_arr(t_dynamic_arr *arr, size_t capacity)
{
	char	**new_arr;
	char	**current_arr;
	size_t	i;
	size_t	len;

	if (capacity == arr->capacity)
		return (true);
	i = -1;
	len = arr->len;
	current_arr = arr->tab;
	new_arr = malloc(sizeof(char *) * (len + capacity + 1));
	if (new_arr == NULL)
		return (false);
	if (current_arr != NULL)
	{
		while (++i < len)
		{
			new_arr[i] = ft_strdup(current_arr[i]);
			if (new_arr[i] == NULL)
				return (ft_free_tab(new_arr), false);
		}
		ft_free_tab_with_len(current_arr, len);
		arr->len = i;
	}
	return (arr->capacity = capacity, arr->tab = new_arr, true);
}

int	dynamic_arr_push_back(t_dynamic_arr *arr, char *value)
{
	if (arr->capacity == 0 && dynamic_arr_grow_arr(arr, arr->len * 2) == false)
		return (-1);
	arr->tab[arr->len++] = value;
	arr->tab[arr->len] = 0;
	--arr->capacity;
	return (arr->len - 1);
}

bool	dynamic_arr_remove_element_by_index(t_dynamic_arr *arr, size_t index)
{
	char	*tmp;

	if (index >= arr->len)
		return (false);
	tmp = arr->tab[index];
	arr->tab[index] = arr->tab[--arr->len];
	arr->tab[arr->len] = 0;
	++arr->capacity;
	free(tmp);
	return (true);
}

bool	dynamic_arr_update_element_by_index(
		t_dynamic_arr *arr, size_t index, char *value)
{
	if (index >= arr->len)
		return (false);
	free(arr->tab[index]);
	arr->tab[index] = value;
	return (true);
}
