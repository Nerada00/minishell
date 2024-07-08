/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdmessa <abdmessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 08:08:16 by abdmessa          #+#    #+#             */
/*   Updated: 2024/04/16 22:58:06 by abdmessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_elem(void **addr)
{
	void	*to_free;

	to_free = *addr;
	if (to_free == NULL)
		return ;
	free(to_free);
	*addr = NULL;
}
