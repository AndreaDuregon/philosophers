/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduregon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 20:20:26 by aduregon          #+#    #+#             */
/*   Updated: 2021/04/11 17:15:19 by aduregon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "philo_one.h"

int	parse_input(char **argv, int argc)
{
	if (ft_atoi(argv[1]) < 2)
		return (0);
	if (ft_atoi(argv[2]) < 0)
		return (0);
	if (ft_atoi(argv[3]) < 0)
		return (0);
	if (ft_atoi(argv[4]) < 0)
		return (0);
	if (argc == 6 && ft_atoi(argv[5]) < 0)
		return (0);
	return (1);
}

t_table	init_table(char **argv, int argc)
{
	t_table 		table;
	struct timeval	tv;
	pthread_mutex_t	status;

	table.num_philo = ft_atoi(argv[1]);
	table.time_to_die = ft_atoi(argv[2]);
	table.time_to_eat = ft_atoi(argv[3]);
	table.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table.num_meal = ft_atoi(argv[5]);
	else
		table.num_meal = -1;
	table.now = tv;
	pthread_mutex_init(&status, NULL);
	table.status = status;
	return(table);
}

void	philo_dead(int id)
{
	printf("PHILO %d IS DEAD\n", id);
	exit(0);
}

void	*is_dead(void *input)
{
	t_philo			*philo;
	philo = (t_philo *)input;

	while (1)
	{
		pthread_mutex_lock(&(philo->table->status));
		gettimeofday(&(philo->table->now), NULL);
		if ((philo->table->now.tv_usec % 1000) - philo->eat_time >
										philo->table->time_to_die)
			philo_dead(philo->id);
		pthread_mutex_unlock(&(philo->table->status));
	}
	return (NULL);
}

void	*philosopher(void *input)
{
	struct timeval	tv;
	t_philo			*philo;
	pthread_t		monitor;

	philo = (t_philo *)input;
	printf("PHILO %d IS BORN\n", philo->id);
	gettimeofday(&tv, NULL);
	philo->eat_time = tv.tv_usec % 1000;
	pthread_create(&monitor, NULL, &is_dead, &(*input));
	while (philo->remain_meal > 0 || philo->remain_meal == -1)
	{
		pthread_mutex_lock(&(philo->table->status));
		printf("PHILO %d IS EATING %d meal\n", philo->id, philo->remain_meal);
		pthread_mutex_unlock(&(philo->table->status));
		if (philo->remain_meal != -1)
			philo->remain_meal--;
	}
	return (NULL);
}

t_philo	*init_philo(t_table table)
{
	t_philo	*philo;
	int		i;
	struct timeval	tv;

	philo = ft_calloc(table.num_philo, sizeof(t_philo));
	i = 0;
	while (i < table.num_philo)
	{
		philo[i].id = i;
		philo[i].remain_meal = table.num_meal;
		philo[i].table = &table;
		i++;
	}
	return (philo);
}

int	main(int argc, char **argv)
{
	t_table		table;
	t_philo		*philo;
	pthread_t	*p;
	int		i;
	int		k;
	
	if (argc < 5 || argc > 6)
		input_error();
	if(!parse_input(argv, argc))
		input_error();
	p = ft_calloc(ft_atoi(argv[1]), sizeof(pthread_t));
	table = init_table(argv, argc);
	philo = init_philo(table);
	i = 0;
	while(i < table.num_philo)
	{
		pthread_create(&p[i], NULL, &philosopher, &philo[i]);
		i++;
	}
	k = 0;
	while (k < i)
	{
		pthread_join(p[k], NULL);
		k++;
	}
}
