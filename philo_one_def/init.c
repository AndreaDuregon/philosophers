/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduregon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 16:11:23 by aduregon          #+#    #+#             */
/*   Updated: 2021/04/18 18:43:31 by aduregon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	parse_input(char **argv, int argc)
{
	if (ft_atoi(argv[1]) < 1)
		return (0);
	if (ft_atoi(argv[2]) < 0)
		return (0);
	if (ft_atoi(argv[3]) < 0)
		return (0);
	if (ft_atoi(argv[4]) < 0)
		return (0);
	if (argc == 6 && ft_atoi(argv[5]) <= 0)
		return (0);
	return (1);
}

t_table	init_table2(t_table table, char **argv, int argc)
{
	table.round = 0;
	table.cont = 0;
	table.turn = 0;
	table.is_dead = 0;
	table.num_philo = ft_atoi(argv[1]);
	table.time_to_die = ft_atoi(argv[2]);
	table.time_to_eat = ft_atoi(argv[3]) * 1000;
	table.time_to_sleep = ft_atoi(argv[4]) * 1000;
	if (argc == 6)
		table.num_meal = ft_atoi(argv[5]);
	else
		table.num_meal = -1;
	return (table);
}

t_table	init_table(char **argv, int argc)
{
	t_table			table;
	pthread_mutex_t	status;
	pthread_mutex_t	print;
	pthread_mutex_t	dead;
	pthread_mutex_t	*fork;
	int				i;

	table = init_table2(table, argv, argc);
	table.start = get_time_stamp();
	table.fork = ft_calloc(table.num_philo, sizeof(pthread_mutex_t));
	i = 0;
	while (i < table.num_philo)
	{
		pthread_mutex_init(&table.fork[i], NULL);
		//table.fork[i] = fork[i];
		i++;
	}
	pthread_mutex_init(&status, NULL);
	pthread_mutex_init(&print, NULL);
	pthread_mutex_init(&dead, NULL);
	table.status = status;
	table.print = print;
	table.dead = dead;
	if (table.time_to_eat == 0 && table.time_to_sleep == 0)
		table.time_to_eat = 1001;
	return (table);
}

t_philo	*init_philo(t_table table)
{
	t_philo	*philo;
	int		i;

	philo = ft_calloc(table.num_philo, sizeof(t_philo));
	i = 0;
	while (i < table.num_philo)
	{
		philo[i].id = i;
		philo[i].status = 0;
		philo[i].is_eating = 0;
		philo[i].remain_meal = 0;
		philo[i].table = &table;
		i++;
	}
	return (philo);
}
