/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduregon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 20:20:26 by aduregon          #+#    #+#             */
/*   Updated: 2021/04/07 12:00:20 by aduregon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "philo_one.h"

t_philo	init_philo(char **argv, int i)
{
	t_philo	p;

	p.philo_num = i;
	p.occupied = 0;
	p.die = ft_atoi(argv[2]);
	p.eat = ft_atoi(argv[3]);
	p.sleep = ft_atoi(argv[4]);
	if (argv[5])
		p.meal = ft_atoi(argv[5]);
	pthread_mutex_init(&p.fork, NULL);
	return (p);
}

int	philo_life(t_philo p)
{
	while (p.meal > 0)
	{
		if ()
	}
}

int	main(int argc, char **argv)
{
	pthread_t	*philo;
	t_philo		*p;
	int			i;

	if (argc < 5 || argc > 6)
		return (1);
	philo = ft_calloc(ft_atoi(argv[1]), sizeof(t_philo));
	p = ft_calloc(ft_atoi(argv[1]), sizeof(t_philo));
	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		p[i] = init_philo(argv, i);
		pthread_create(&philo[i], NULL, philo_life, &p[i]);
		pthread_join(philo[i], NULL);
	}
}
