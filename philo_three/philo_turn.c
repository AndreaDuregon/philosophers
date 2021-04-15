/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_turn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalori <dmalori@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 16:55:51 by aduregon          #+#    #+#             */
/*   Updated: 2021/04/15 13:29:37 by dmalori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	philo_eat_odd(t_philo *philo)
{
	print_fork(philo, get_time_stamp() - philo->table->start, philo->id);
	philo->remain_meal++;
	philo->eat_time = get_time_stamp();
	usleep(philo->table->time_to_eat);
}

void	philo_eat_even(t_philo *philo)
{
	print_fork(philo, get_time_stamp() - philo->table->start, philo->id);
	philo->remain_meal++;
	philo->eat_time = get_time_stamp();
	usleep(philo->table->time_to_eat);
}

void	philo_eat_last(t_philo *philo)
{
	sem_wait((philo->table->status));
	print_fork(philo, get_time_stamp() - philo->table->start, philo->id);
	print_fork(philo, get_time_stamp() - philo->table->start, philo->id);
	philo->table->round = 0;
	philo->remain_meal++;
	print_eat(philo, get_time_stamp() - philo->table->start, philo->id);
	sem_post((philo->table->status));
	usleep(philo->table->time_to_eat);
	philo->eat_time = get_time_stamp();
}

int	philo_even(t_philo *philo, pthread_t monitor)
{
	philo_eat_even(philo);
	ft_sleep(philo);
	if (philo->remain_meal == philo->table->num_meal)
	{
		philo->status = 1;
		pthread_detach(monitor);
		exit(0);
		return (0);
	}
	return (1);
}

int	philo_odd(t_philo *philo, pthread_t monitor)
{
	philo_eat_odd(philo);
	ft_sleep(philo);
	usleep(philo->table->time_to_eat);
	if (philo->remain_meal == philo->table->num_meal)
	{
		philo->status = 1;
		pthread_detach(monitor);
		exit(0);
		return (0);
	}
	return (1);
}