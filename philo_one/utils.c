/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduregon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 10:52:42 by aduregon          #+#    #+#             */
/*   Updated: 2021/04/07 11:32:33 by aduregon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	index;
	void	*mem;

	mem = malloc(count * size);
	if (!mem)
		return (NULL);
	index = 0;
	ft_bzero(mem, count * size);
	return (mem);
}

int	ft_atoi(const char *str)
{
	size_t				index;
	int					neg;
	unsigned long int	res;

	index = 0;
	neg = 1;
	res = 0;
	while (ft_isspace(str[index]))
		index++;
	if (str[index] == '+' || str[index] == '-')
	{
		if (str[index] == '-')
			neg = -1;
		index++;
	}
	while (ft_isdigit(str[index]))
	{
		res *= 10;
		res += str[index] - 48;
		index++;
	}
	return (res * neg);
}
