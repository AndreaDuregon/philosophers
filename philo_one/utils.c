/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduregon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 10:52:42 by aduregon          #+#    #+#             */
/*   Updated: 2021/04/13 10:21:50 by aduregon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

size_t		ft_strlen(const char *s)
{
	size_t size;

	size = 0;
	while (s[size] != 0)
		size++;
	return (size);
}

static	size_t		ft_nsize(int n)
{
	size_t size;

	size = (n < 0 ? 1 : 0);
	while (1)
	{
		n /= 10;
		size++;
		if (n == 0)
			break ;
	}
	return (size);
}

char				*ft_itoa(int n)
{
	size_t	size;
	char	*itoa;
	long	number;

	number = n;
	size = ft_nsize(n);
	if (!(itoa = ft_calloc(size + 1, sizeof(char))))
		return (NULL);
	if (number < 0)
	{
		itoa[0] = '-';
		number *= -1;
	}
	itoa[size] = '\0';
	while (1)
	{
		itoa[size - 1] = (number % 10) + 48;
		number /= 10;
		size--;
		if (number == 0)
			break ;
	}
	return (itoa);
}

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;

	p = (unsigned char *)s;
	while (n--)
		*p++ = (unsigned char)c;
	return (s);
}

void    *ft_calloc(size_t nelem, size_t elsize)
{
	char	*p;

    p = (char *)malloc(nelem * elsize);
	if (!p)
		return (NULL);
	p = ft_memset(p, 0, nelem * elsize);
	return ((void *)p);
}

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\f' || c == '\n' ||
	c == '\r' || c == '\t' || c == '\v')
		return (1);
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	long int		sum;
	int				negative;
	int				count;

	sum = 0;
	negative = 1;
	count = 0;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
		if (*nptr++ == '-')
			negative = -1;
	while (ft_isdigit(*nptr))
	{
		sum *= 10;
		sum += *nptr++ - '0';
		if (negative == -1 && sum < 0)
			return (0);
		if (negative == 1 && sum < 0)
			return (-1);
		count++;
	}
	if (count == 0)
		return (-1);
	return (sum * negative);
}
