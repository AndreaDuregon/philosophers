/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgiovo <sgiovo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 16:15:02 by aduregon          #+#    #+#             */
/*   Updated: 2021/04/19 14:54:59 by sgiovo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	print_dead(t_philo *philo, unsigned long long t, int i)
{
	sem_wait(philo->table->print);
	printf("%llu %d is dead\n", t, i);
	return ;
	sem_post(philo->table->print);
}

void	print_sleep(t_philo *philo, unsigned long long t, int i)
{
	sem_wait(philo->table->print);
	printf("%llu %d is sleeping\n", t, i);
	sem_post(philo->table->print);
	ft_usleep(philo->table->time_to_sleep);
}

void	print_think(t_philo *philo, unsigned long long t, int i)
{
	sem_wait(philo->table->print);
	printf("%llu %d is thinking\n", t, i);
	sem_post(philo->table->print);
}

void	print_fork(t_philo *philo, unsigned long long t, int i)
{
	sem_wait(philo->table->print);
	printf("%llu %d is taken a fork\n", t, i);
	printf("%llu %d is taken a fork\n", t, i);
	printf("%llu %d is eating\n", t, i);
	sem_post(philo->table->print);
}

void	print_eat(t_philo *philo, unsigned long long t, int i)
{
	sem_wait(philo->table->print);
	sem_post(philo->table->print);
}
