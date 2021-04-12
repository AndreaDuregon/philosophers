/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduregon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 20:20:26 by aduregon          #+#    #+#             */
/*   Updated: 2021/04/12 18:31:24 by aduregon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	pthread_mutex_t	status;
	pthread_mutex_t	print;
	pthread_mutex_t	dead;

	table.round = 0;
	table.cont = 0;
	table.turn = 0;
	table.num_philo = ft_atoi(argv[1]);
	table.time_to_die = ft_atoi(argv[2]);
	table.time_to_eat = ft_atoi(argv[3]);
	table.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table.num_meal = ft_atoi(argv[5]);
	else
		table.num_meal = -1;
	table.start = get_time_stamp();
	pthread_mutex_init(&status, NULL);
	pthread_mutex_init(&print, NULL);
	pthread_mutex_init(&dead, NULL);
	table.status = status;
	table.print = print;
	table.dead = dead;
	return(table);
}

void	philo_dead(t_philo *philo)
{
	printf("%llu %d is dead\n", get_time_stamp() - philo->table->start, philo->id);
	exit(0);
}

void	*is_dead(void *input)
{
	t_philo			*philo;
	philo = (t_philo *)input;

	while (1)
	{
		pthread_mutex_lock(&(philo->table->dead));
		if (get_time_stamp() - philo->eat_time >
										philo->table->time_to_die)
			philo_dead(philo);
		pthread_mutex_unlock(&(philo->table->dead));
	}
	return (NULL);
}

void	ft_sleep(t_philo *philo)
{
	pthread_mutex_lock(&(philo->table->print));
	printf("%llu %d is sleeping\n", get_time_stamp() - philo->table->start, philo->id);
	pthread_mutex_unlock(&(philo->table->print));
	usleep(philo->table->time_to_sleep * 1000);
	pthread_mutex_lock(&(philo->table->print));
	printf("%llu %d is thinking\n", get_time_stamp() - philo->table->start, philo->id);
	pthread_mutex_unlock(&(philo->table->print));
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
		if (philo->table->round == philo->id % 2 && philo->remain_meal == philo->table->turn)
		{
			philo->status = 1;
			pthread_mutex_lock(&(philo->table->status));
			printf("%llu %d has tahen a fork\n", get_time_stamp() - philo->table->start, philo->id);
			printf("%llu %d has tahen a fork\n", get_time_stamp() - philo->table->start, philo->id);
			philo->table->cont++;
			philo->remain_meal++;
			if (philo->table->cont == philo->table->num_philo / 2)
			{
				if (philo->table->round == 1)
				{
					philo->table->turn++;
					philo->table->round = 0;
				}
				else
					philo->table->round = 1;
				philo->table->cont = 0;
			}
			printf("%llu %d is eating\n", get_time_stamp() - philo->table->start, philo->id);
			pthread_mutex_unlock(&(philo->table->status));
			usleep(philo->table->time_to_eat);
			philo->eat_time = get_time_stamp();
			ft_sleep(philo);
		}
		if (philo->remain_meal == philo->table->num_meal)
			break ;
		//printf("ID: %d MEAL: %d TURN: %d\n", philo->id, philo->remain_meal, philo->table->turn);
		//pthread_mutex_lock(&(philo->table->print));
		//pthread_mutex_unlock(&(philo->table->print));
		
	}
	return (NULL);
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
		printf("PHILO %d IS BORN\n", philo[i].id);
		pthread_create(&p[i], NULL, &philosopher, &philo[i]);
		i++;
	}
	k = 0;
	while (k < i)
	{
		pthread_join(p[k], NULL);
		printf("PHILO %d IS FINISH\n", philo[k].id);
		k++;
	}
}
