/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdmessa <abdmessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 21:52:19 by abdmessa          #+#    #+#             */
/*   Updated: 2024/06/28 21:52:20 by abdmessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_nblen(long long n)
{
	int	len;

	if (n == 0)
		return (1);
	len = (n < 0);
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int				i;
	int				j;
	static char		str[12] = {0};

	i = (n < 0);
	j = ft_nblen(n);
	if (n < 0)
		str[0] = '-';
	str[j] = 0;
	while (--j >= i)
	{
		str[j] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}
