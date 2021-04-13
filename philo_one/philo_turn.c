/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_turn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduregon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 16:55:51 by aduregon          #+#    #+#             */
/*   Updated: 2021/04/13 17:39:07 by aduregon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	philo_eat_odd(t_philo *philo)
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
}

void	philo_eat_even(t_philo *philo)
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
}

void	philo_eat_last(t_philo *philo)
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
}

int	philo_even(t_philo *philo, pthread_t monitor)
{
	if (philo->table->round == philo->id % 2 && \
		philo->remain_meal == philo->table->turn)
	{
		philo_eat_even(philo);
		ft_sleep(philo);
	}
	if (philo->remain_meal == philo->table->num_meal)
	{
		philo->status = 1;
		pthread_detach(monitor);
		return (0);
	}
	return (1);
}

int	philo_odd(t_philo *philo, pthread_t monitor)
{
	if (philo->table->round == philo->id % 2 && \
		philo->remain_meal == philo->table->turn
		&& philo->id != philo->table->num_philo - 1)
	{
		philo_eat_odd(philo);
		ft_sleep(philo);
	}
	else
	{
		philo_eat_last(philo);
		ft_sleep(philo);
	}
	if (philo->remain_meal == philo->table->num_meal)
	{
		philo->status = 1;
		pthread_detach(monitor);
		return (0);
	}
	return (1);
}