/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdmessa <abdmessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 21:51:18 by abdmessa          #+#    #+#             */
/*   Updated: 2024/06/28 21:51:19 by abdmessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_bzero(void *s, size_t n)
{
	char	*s2;
	int		i;

	s2 = (char *)s;
	i = 0;
	while (n > 0)
	{
		s2[i] = '\0';
		i++;
		n--;
	}
}