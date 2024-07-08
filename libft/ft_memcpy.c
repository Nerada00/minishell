/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdmessa <abdmessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 21:52:26 by abdmessa          #+#    #+#             */
/*   Updated: 2024/06/28 21:52:27 by abdmessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_memcpy(void *destination, const void *source, size_t size)
{
	unsigned char		*dest;
	unsigned const char	*src;
	size_t				i;

	if (source == NULL || destination == NULL)
		return ;
	i = -1;
	dest = destination;
	src = source;
	while (src[++i] && i < size)
		dest[i] = src[i];
}
