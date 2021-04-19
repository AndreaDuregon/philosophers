/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_turn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalori <dmalori@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 16:55:51 by aduregon          #+#    #+#             */
/*   Updated: 2021/04/15 12:23:50 by dmalori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	philo_eat_even(t_philo *philo)
{
	print_fork(philo, get_time_stamp() - philo->table->start, philo->id);
	philo->remain_meal++;
	philo->eat_time = get_time_stamp();
	usleep(philo->table->time_to_eat);
}

int	philo_even(t_philo *philo, pthread_t monitor)
{
	sem_wait(philo->table->status);
	philo_eat_even(philo);
	sem_post(philo->table->status);
	ft_sleep(philo);
	if (philo->remain_meal == philo->table->num_meal)
	{
		philo->status = 1;
		pthread_detach(monitor);
		return (0);
	}
	return (1);
}
