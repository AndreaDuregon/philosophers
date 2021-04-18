/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduregon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 16:17:37 by aduregon          #+#    #+#             */
/*   Updated: 2021/04/18 15:39:41 by aduregon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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
		{
			print_dead(philo, get_time_stamp() - \
						philo->table->start, philo->id);
			kill(philo->pid, SIGINT);
		}
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
	exit(0);
	return(NULL);
}

void	*philosopher_odd(void *input)
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
		if (!philo_odd(philo, monitor))
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
	int		j;

	i = 0;
	k = 0;
	if (ft_atoi(argv[1]) == 1)
	{
		pthread_create(&p[i], NULL, &alone_philosopher, &philo[i]);
		pthread_join(p[i], NULL);
		free(philo);
		free(p);
		exit(0);
	}
	philo->table->father = getpid();
	if (table.num_philo % 2 == 0)
	{
		while (k < 2)
		{
			while (i < table.num_philo)
			{
				philo->pid = fork();
				if (philo->pid == 0)
				{
					philosopher((void *)&philo[i]);
					exit(0);
				}
				else
					i += 2;
			}
			usleep(philo->table->time_to_eat);
			k++;
			i = 1;
		}
	}
	else
	{
		while (k < 2)
		{
			while (i < (table.num_philo - 1))
			{
				pthread_create(&p[i], NULL, &philosopher_odd, &philo[i]);
				i += 2;
			}
			usleep(philo->table->time_to_eat);
			k++;
			i = 1;
		}
		pthread_create(&p[table.num_philo - 1], NULL, &philosopher_odd, &philo[table.num_philo - 1]);
	}
	k = 0;
	while (k < table.num_philo)
	{
		waitpid(philo[k].pid, NULL, 0);
		k++;
	}
	exit(0);
}