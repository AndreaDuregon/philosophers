/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: forsili <forsili@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 14:24:23 by forsili           #+#    #+#             */
/*   Updated: 2021/04/19 14:25:26 by forsili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	print_think(t_philo *philo, unsigned long long t, int i)
{
	char	*timestamp;
	char	*id;
	char	*text[1000];

	timestamp = ft_itoa(t);
	id = ft_itoa(i);
	sem_wait(philo->table->print);
	printf("%llu %d is thinking\n", t, i);
	sem_post(philo->table->print);
	free(timestamp);
	free(id);
}

void	print_fork(t_philo *philo, unsigned long long t, int i)
{
	char	*timestamp;
	char	*id;
	char	*text[1000];
	char	*text2[1000];

	timestamp = ft_itoa(t);
	id = ft_itoa(i);
	sem_wait(philo->table->print);
	printf("%llu %d is taken a fork\n", t, i);
	printf("%llu %d is taken a fork\n", t, i);
	printf("%llu %d is eating\n", t, i);
	sem_post(philo->table->print);
	free(timestamp);
	free(id);
}

void	print_eat(t_philo *philo, unsigned long long t, int i)
{
	char	*timestamp;
	char	*id;
	char	*text[1000];

	timestamp = ft_itoa(t);
	id = ft_itoa(i);
	sem_wait(philo->table->print);
	sem_post(philo->table->print);
	free(timestamp);
	free(id);
}
