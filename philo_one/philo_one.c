/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduregon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 20:20:26 by aduregon          #+#    #+#             */
/*   Updated: 2021/04/13 12:52:09 by aduregon         ###   ########.fr       */
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
	table.time_to_eat = ft_atoi(argv[3]) * 1000;
	table.time_to_sleep = ft_atoi(argv[4]) * 1000;
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

void	print_dead(t_philo *philo, unsigned long long t, int i)
{
	char	*timestamp;
	char	*id;

	timestamp = ft_itoa(t);
	id = ft_itoa(i);
	pthread_mutex_lock(&(philo->table->print));
	write(1, timestamp, ft_strlen(timestamp));
	write(1, " ", 1);
	write(1, id, ft_strlen(id));
	write(1, " ", 1);
	write(1, "is dead\n", 8);
	free(timestamp);
	free(id);
	exit(0);
	pthread_mutex_unlock(&(philo->table->print));
}

void	*is_dead(void *input)
{
	t_philo			*philo;
	philo = (t_philo *)input;

	while (1)
	{
		pthread_mutex_lock(&(philo->table->dead));
		if (philo->status)
			return (NULL);
		//printf("%llu - %llu = %llu > %llu\n", get_time_stamp(), philo->eat_time, get_time_stamp() - philo->eat_time, philo->table->time_to_die);
		if (get_time_stamp() - philo->eat_time >
										philo->table->time_to_die)
			print_dead(philo, get_time_stamp() - philo->table->start, philo->id);
		pthread_mutex_unlock(&(philo->table->dead));
	}
	return (NULL);
}

void	print_sleep(t_philo *philo, unsigned long long t, int i)
{
	char	*timestamp;
	char	*id;

	timestamp = ft_itoa(t);
	id = ft_itoa(i);
	pthread_mutex_lock(&(philo->table->print));
	write(1, timestamp, ft_strlen(timestamp));
	write(1, " ", 1);
	write(1, id, ft_strlen(id));
	write(1, " ", 1);
	write(1, "is sleeping\n", 12);
	free(timestamp);
	free(id);
	pthread_mutex_unlock(&(philo->table->print));
}

void	print_think(t_philo *philo, unsigned long long t, int i)
{
	char	*timestamp;
	char	*id;

	timestamp = ft_itoa(t);
	id = ft_itoa(i);
	pthread_mutex_lock(&(philo->table->print));
	write(1, timestamp, ft_strlen(timestamp));
	write(1, " ", 1);
	write(1, id, ft_strlen(id));
	write(1, " ", 1);
	write(1, "is thinking\n", 12);
	free(timestamp);
	free(id);
	pthread_mutex_unlock(&(philo->table->print));
}

void	print_fork(t_philo *philo, unsigned long long t, int i)
{
	char	*timestamp;
	char	*id;

	timestamp = ft_itoa(t);
	id = ft_itoa(i);
	pthread_mutex_lock(&(philo->table->print));
	write(1, timestamp, ft_strlen(timestamp));
	write(1, " ", 1);
	write(1, id, ft_strlen(id));
	write(1, " ", 1);
	write(1, "has taken a fork\n", 17);
	free(timestamp);
	free(id);
	pthread_mutex_unlock(&(philo->table->print));
}

void	print_eat(t_philo *philo, unsigned long long t, int i)
{
	char	*timestamp;
	char	*id;

	timestamp = ft_itoa(t);
	id = ft_itoa(i);
	pthread_mutex_lock(&(philo->table->print));
	write(1, timestamp, ft_strlen(timestamp));
	write(1, " ", 1);
	write(1, id, ft_strlen(id));
	write(1, " ", 1);
	write(1, "is eating\n", 10);
	free(timestamp);
	free(id);
	pthread_mutex_unlock(&(philo->table->print));
}

void	ft_sleep(t_philo *philo)
{
	print_sleep(philo, get_time_stamp() - philo->table->start, philo->id);
	usleep(philo->table->time_to_sleep);
	print_think(philo, get_time_stamp() - philo->table->start, philo->id);
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
		if (philo->table->num_philo % 2 == 0)
		{
			if (philo->table->round == philo->id % 2 && philo->remain_meal == philo->table->turn)
			{
				pthread_mutex_lock(&(philo->table->status));
				print_fork(philo, get_time_stamp() - philo->table->start, philo->id);
				print_fork(philo, get_time_stamp() - philo->table->start, philo->id);
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
				print_eat(philo, get_time_stamp() - philo->table->start, philo->id);
				pthread_mutex_unlock(&(philo->table->status));
				usleep(philo->table->time_to_eat);
				philo->eat_time = get_time_stamp();
				ft_sleep(philo);
			}
			if (philo->remain_meal == philo->table->num_meal)
			{
				philo->status = 1;
				pthread_detach(monitor);
				break ;
			}
		}
		else
		{
			if (philo->table->round == philo->id % 2 && philo->remain_meal == philo->table->turn
				&& philo->id != philo->table->num_philo - 1)
			{
				pthread_mutex_lock(&(philo->table->status));
				print_fork(philo, get_time_stamp() - philo->table->start, philo->id);
				print_fork(philo, get_time_stamp() - philo->table->start, philo->id);
				philo->table->cont++;
				philo->remain_meal++;
				if (philo->table->cont == philo->table->num_philo / 2)
				{
					if (philo->table->round == 1)
					{
						philo->table->turn++;
						philo->table->round = 2;
					}
					else
						philo->table->round = 1;
					philo->table->cont = 0;
				}
				print_eat(philo, get_time_stamp() - philo->table->start, philo->id);
				pthread_mutex_unlock(&(philo->table->status));
				usleep(philo->table->time_to_eat);
				philo->eat_time = get_time_stamp();
				ft_sleep(philo);
			}
			else
			{
				pthread_mutex_lock(&(philo->table->status));
				print_fork(philo, get_time_stamp() - philo->table->start, philo->id);
				print_fork(philo, get_time_stamp() - philo->table->start, philo->id);
				philo->table->round = 0;
				philo->remain_meal++;
				print_eat(philo, get_time_stamp() - philo->table->start, philo->id);
				pthread_mutex_unlock(&(philo->table->status));
				usleep(philo->table->time_to_eat);
				philo->eat_time = get_time_stamp();
				ft_sleep(philo);
			}
			if (philo->remain_meal == philo->table->num_meal)
			{
				philo->status = 1;
				pthread_detach(monitor);
				break ;
			}
		}
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
		pthread_create(&p[i], NULL, &philosopher, &philo[i]);
		i++;
	}
	k = 0;
	while (k < i)
	{
		pthread_join(p[k], NULL);
		pthread_detach(p[k]);
		k++;
	}
	free(philo);
	free(p);
}
