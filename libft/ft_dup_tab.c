/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdmessa <abdmessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 21:51:32 by abdmessa          #+#    #+#             */
/*   Updated: 2024/06/28 21:51:33 by abdmessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_dup_tab(char **to_copy)
{
	int		i;
	char	**tab;

	if (!to_copy)
		return (NULL);
	i = ft_tab_len(to_copy);
	tab = malloc(sizeof(char *) * (i + 1));
	if (!tab)
		return (NULL);
	tab[i] = 0;
	i = -1;
	while (to_copy[++i])
	{
		tab[i] = ft_strdup(to_copy[i]);
		if (!tab[i])
			return (ft_free_tab(tab));
	}
	return (tab);
}
