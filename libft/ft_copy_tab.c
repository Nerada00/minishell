/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdmessa <abdmessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 21:51:27 by abdmessa          #+#    #+#             */
/*   Updated: 2024/06/28 21:51:28 by abdmessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_copy_tab(char **src, char **dest)
{
	int	i;

	if (!src || !dest)
		return (NULL);
	i = -1;
	while (src[++i])
	{
		dest[i] = ft_strdup(src[i]);
		if (!dest[i])
			return (ft_free_tab(dest), NULL);
	}
	dest[i] = NULL;
	return (dest);
}
