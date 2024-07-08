/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyaid <cyaid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 21:53:05 by abdmessa          #+#    #+#             */
/*   Updated: 2024/06/29 04:42:32 by cyaid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(const char *s)
{
	int		i;
	int		j;
	char	*s2;

	i = 0;
	j = 0;
	s2 = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!s2)
		return (NULL);
	if (s)
	{
		while (s[i])
		{
			s2[j] = s[i];
			++i;
			++j;
		}
	}
	s2[j] = '\0';
	return (s2);
}
