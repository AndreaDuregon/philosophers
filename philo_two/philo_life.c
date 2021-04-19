/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduregon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 16:17:37 by aduregon          #+#    #+#             */
/*   Updated: 2021/04/16 17:28:30 by aduregon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	ft_sleep(t_philo *philo)
{
	print_sleep(philo, get_time_stamp() - philo->table->start, philo->id);
	print_think(philo, get_time_stamp() - philo->table->start, philo->id);
}

void	*is_dead(void *input)
{
	t_philo			*philo;

	philo = (t_philo *)input;
	while (1)
	{
		sem_wait((philo->table->dead));
		if (philo->status)
			return (NULL);
		if (get_time_stamp() - philo->eat_time > philo->table->time_to_die && \
			philo->table->time_to_eat != 0 && philo->table->time_to_sleep != 0)
			print_dead(philo, get_time_stamp() - \
						philo->table->start, philo->id);
		sem_post((philo->table->dead));
	}
	return (NULL);
}

void	*philosopher(void *input)
{
	t_philo			*philo;
	pthread_t		monitor;
	int				i;

	philo = (t_philo *)input;
	philo->remain_meal = 0;
	i = 0;
	philo->eat_time = get_time_stamp();
	pthread_create(&monitor, NULL, &is_dead, &(*input));
	while (1)
	{
		if (!philo_even(philo, monitor))
			break ;
	}
	return (NULL);
}

void	*alone_philosopher(void *input)
{
	t_philo			*philo;

	philo = (t_philo *)input;
	print_fork(philo, get_time_stamp() - philo->table->start, philo->id);
	usleep(philo->table->time_to_die * 1000);
	print_dead(philo, get_time_stamp() - philo->table->start, philo->id);
	exit(0);
}

void	start_life(char **argv, t_philo *philo, pthread_t *p, t_table table)
{
	int		i;
	int		k;

	i = 0;
	k = 0;
	if (ft_atoi(argv[1]) == 1)
	{
		pthread_create(&p[i], NULL, &alone_philosopher, &philo[i]);
		pthread_join(p[i], NULL);
		free(philo);
		free(p);
		return ;
	}
	while (i < table.num_philo)
	{
		pthread_create(&p[i], NULL, &philosopher, &philo[i]);
		i += 1;
	}
	k = 0;
	while (k < i)
	{
		pthread_join(p[k], NULL);
		pthread_detach(p[k++]);
		k++;
	}
}