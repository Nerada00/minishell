/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dynamic_arr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdmessa <abdmessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 21:51:06 by abdmessa          #+#    #+#             */
/*   Updated: 2024/06/28 21:51:07 by abdmessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dynamic_arr_print_dynamic_arr(t_dynamic_arr *arr)
{
	size_t	len;
	size_t	i;
	char	**tab;

	i = -1;
	if (arr == NULL)
	{
		printf("dynamic arr is null\n");
		return ;
	}
	len = arr->len;
	tab = arr->tab;
	if (tab == NULL)
	{
		printf("[Tab is empty]\n");
		return ;
	}
	while (++i < len)
		printf("[%s]", tab[i]);
	printf("\n");
}
