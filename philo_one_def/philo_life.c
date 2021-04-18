/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduregon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 16:17:37 by aduregon          #+#    #+#             */
/*   Updated: 2021/04/18 19:39:58 by aduregon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*is_dead(void *input)
{
	t_philo		*philo;

	philo = (t_philo *)input;
	while (1)
	{
		if (philo->status == 1)
			return (NULL);
		pthread_mutex_lock(&(philo->table->dead));
		if (get_time_stamp() - philo->eat_time > philo->table->time_to_die && \
			philo->table->time_to_eat != 0 && philo->table->time_to_sleep != 0 \
			&& philo->is_eating == 0)
			{
				print_dead(philo, get_time_stamp() - \
							philo->table->start, philo->id);
				philo->table->is_dead = 1;
				return (NULL);
			}
		pthread_mutex_unlock(&(philo->table->dead));
	}
	return (NULL);
}

void	*philosopher(void *input)
{
	t_philo		*philo;
	pthread_t	monitor;

	philo = (t_philo *)input;
	philo->remain_meal = 0;
	philo->eat_time = get_time_stamp();
	pthread_create(&monitor, NULL, &is_dead, &(*input));
	while (1)
	{
		if (!philo->table->is_dead &&
		(philo->remain_meal < philo->table->num_meal || philo->table->num_meal == -1))
		{
			pthread_mutex_lock(&philo->table->fork[philo->id]);
			print_fork(philo, get_time_stamp() - philo->table->start, philo->id);
			if (philo->id == philo->table->num_philo - 1)
			{
				pthread_mutex_lock(&philo->table->fork[0]);

				print_fork(philo, get_time_stamp() - philo->table->start, philo->id);
				pthread_mutex_lock(&(philo->table->dead));
				print_eat(philo, get_time_stamp() - philo->table->start, philo->id);
				philo->remain_meal++;
				//philo->eat_time = get_time_stamp();
				pthread_mutex_unlock(&(philo->table->dead));
				pthread_mutex_unlock(&philo->table->fork[0]);
			}
			else
			{
				pthread_mutex_lock(&philo->table->fork[philo->id + 1]);
				print_fork(philo, get_time_stamp() - philo->table->start, philo->id);
				pthread_mutex_lock(&(philo->table->dead));
				print_eat(philo, get_time_stamp() - philo->table->start, philo->id);
				philo->remain_meal++;
				//philo->eat_time = get_time_stamp();
				pthread_mutex_unlock(&(philo->table->dead));
				pthread_mutex_unlock(&philo->table->fork[philo->id + 1]);
			}
			pthread_mutex_unlock(&philo->table->fork[philo->id]);
			usleep(philo->table->time_to_eat);
			philo->eat_time = get_time_stamp();
			philo->is_eating = 0;
			print_sleep(philo, get_time_stamp() - philo->table->start, philo->id);
			usleep(philo->table->time_to_sleep);
			print_think(philo, get_time_stamp() - philo->table->start, philo->id);
		}
		else
		{
			pthread_detach(monitor);
			return (NULL);
		}
	}
	return (0);
}

void	start_life(char **argv, t_philo *philo, pthread_t *p, t_table table)
{
	int	i;
	int	k;

	i = 0;
	while (i < table.num_philo)
	{
		if (table.num_philo % 2 == 1 && i == table.num_philo - 1)
			break ;
		pthread_create(&p[i], NULL, &philosopher, (void *)&philo[i]);
		i += 2;
	}
	usleep(table.time_to_eat);
	i = 1;
	while (i < table.num_philo)
	{
		pthread_create(&p[i], NULL, &philosopher, (void *)&philo[i]);
		i += 2;
	}
	usleep(table.time_to_eat);
	if (table.num_philo % 2 == 1)
		pthread_create(&p[table.num_philo - 1], NULL, &philosopher, (void *)&philo[table.num_philo - 1]);
	k = 0;
	while (k < table.num_philo)
	{
		pthread_join(p[k], NULL);
		pthread_detach(p[k++]);
		k++;
	}
}