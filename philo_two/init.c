/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduregon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 16:11:23 by aduregon          #+#    #+#             */
/*   Updated: 2021/04/16 13:01:20 by aduregon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

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
	sem_t			status;
	sem_t			print;
	sem_t			dead;

	table = init_table2(table, argv, argc);
	table.start = get_time_stamp();
	sem_unlink("/status_sem");
	sem_unlink("/print_sem");
	sem_unlink("/dead_sem");
	table.status = sem_open("/status_sem", O_CREAT, 01411, table.num_philo/2);
	table.print = sem_open("/print_sem", O_CREAT, 01411, 1);
	table.dead = sem_open("/dead_sem", O_CREAT, 01411, 1);
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
		philo[i].remain_meal = 0;
		philo[i].table = &table;
		i++;
	}
	return (philo);
}
