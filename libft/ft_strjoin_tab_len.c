/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_tab_len.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdmessa <abdmessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 21:53:11 by abdmessa          #+#    #+#             */
/*   Updated: 2024/06/28 21:53:12 by abdmessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_tab_with_len(char **tab, size_t len)
{
	char	*str;
	size_t	i;
	size_t	j;
	size_t	total_len;

	i = -1;
	total_len = 0;
	while (++i < len)
		total_len += ft_strlen(tab[i]);
	str = malloc(sizeof(char) * (total_len + 1));
	if (str == NULL)
		return (NULL);
	str[total_len] = 0;
	i = -1;
	j = 0;
	while (++i < len)
	{
		ft_memcpy(str + j, tab[i], ft_strlen(tab[i]));
		j += ft_strlen(tab[i]);
	}
	return (str);
}
