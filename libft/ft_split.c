/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdmessa <abdmessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 21:52:54 by abdmessa          #+#    #+#             */
/*   Updated: 2024/06/28 21:52:55 by abdmessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ft_getsize(char const *s, char c, size_t index)
{
	size_t	size;

	size = 0;
	while (s[index] && s[index] != c)
	{
		index++;
		size += sizeof(char);
	}
	return (size);
}

static size_t	ft_counter(char const *s, char c)
{
	size_t	counter;
	size_t	i;

	counter = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			counter++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (counter);
}

static void	ft_free(char **str)
{
	while (*str)
	{
		free(*str);
		str = NULL;
		str++;
	}
	free(str);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	char	**str;

	i = 0;
	j = -1;
	if (s == NULL)
		return (NULL);
	str = malloc((ft_counter(s, c) + 1) * sizeof(char *));
	if (str == NULL)
		return (NULL);
	while (++j < ft_counter(s, c))
	{
		while (s[i] == c)
			i++;
		str[j] = ft_substr(s, i, ft_getsize(s, c, i));
		if (str[j] == NULL)
			return (ft_free(str), NULL);
		i += ft_getsize(s, c, i);
	}
	str[j] = NULL;
	return (str);
}
