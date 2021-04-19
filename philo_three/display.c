/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: forsili <forsili@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 16:15:02 by aduregon          #+#    #+#             */
/*   Updated: 2021/04/19 14:43:29 by forsili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	stringer(char *timestamp, char *id, char *phrase, char final[1000])
{
	while (*timestamp)
		*final++ = *timestamp++;
	*final++ = ' ';
	while (*id)
		*final++ = *id++;
	*final++ = ' ';
	while (*phrase)
		*final++ = *phrase++;
	*final = 0;
}

void	print_dead(t_philo *philo, unsigned long long t, int i)
{
	char	*timestamp;
	char	*id;

	timestamp = ft_itoa(t);
	id = ft_itoa(i);
	sem_wait(philo->table->print);
	printf("%llu %d is dead\n", t, i);
	free(timestamp);
	free(id);
	sem_post(philo->table->print);
}

void	print_sleep(t_philo *philo, unsigned long long t, int i)
{
	char	*timestamp;
	char	*id;

	timestamp = ft_itoa(t);
	id = ft_itoa(i);
	sem_wait(philo->table->print);
	printf("%llu %d is sleeping\n", t, i);
	sem_post(philo->table->print);
	usleep(philo->table->time_to_sleep);
	free(timestamp);
	free(id);
}
