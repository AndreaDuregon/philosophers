/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduregon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 16:15:02 by aduregon          #+#    #+#             */
/*   Updated: 2021/04/13 16:59:37 by aduregon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

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
