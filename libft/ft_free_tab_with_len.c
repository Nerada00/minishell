/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab_with_len.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdmessa <abdmessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 21:51:40 by abdmessa          #+#    #+#             */
/*   Updated: 2024/06/28 21:51:43 by abdmessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_free_tab_with_len(char **tab, size_t len)
{
	size_t	i;

	if (!tab)
		return (NULL);
	i = -1;
	while (++i < len)
		free(tab[i]);
	free(tab);
	return (NULL);
}
