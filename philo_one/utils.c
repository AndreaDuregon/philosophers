/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduregon <aduregon@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 10:52:42 by aduregon          #+#    #+#             */
/*   Updated: 2021/04/06 11:08:35 by aduregon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	index;
	void	*mem;

	if (!(mem = malloc(count * size)))
		return (NULL);
	index = 0;
	ft_bzero(mem, count * size);
	return (mem);
}

void	*ft_malloc(size_t size, size_t mol)
{
	void	*res;
	int		i;

	res = ft_calloc((mol + 1), size);
	if (res == NULL)
		exit(1);
	return (res);
}