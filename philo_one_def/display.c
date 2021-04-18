/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduregon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 16:15:02 by aduregon          #+#    #+#             */
/*   Updated: 2021/04/18 19:46:51 by aduregon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void stringer(char *timestamp, char *id, char *phrase, char final[1000])
{
	while(*timestamp)
		*final++ = *timestamp++;
	*final++ = ' ';
	while(*id)
		*final++ = *id++;
	*final++ = ' ';
	while(*phrase)
		*final++ = *phrase++;
	*final = 0;
}

void	print_dead(t_philo *philo, unsigned long long t, int i)
{
	char	*timestamp;
	char	*id;
	char 	text[1000];

	timestamp = ft_itoa(t);
	id = ft_itoa(i);
	stringer(timestamp, id, "is dead\n", &text);
	pthread_mutex_lock(&(philo->table->print));
	if (philo->table->is_dead)
	{
		pthread_mutex_unlock(&(philo->table->print));
		return ;
	}
	write(1, text, ft_strlen(text));
	free(timestamp);
	free(id);
	pthread_mutex_unlock(&(philo->table->print));
}

void	print_sleep(t_philo *philo, unsigned long long t, int i)
{
	char	*timestamp;
	char	*id;
	char 	text[1000];

		
	timestamp = ft_itoa(t);
	id = ft_itoa(i);
	stringer(timestamp, id, "is sleeping\n", &text);
	pthread_mutex_lock(&(philo->table->print));
	if (philo->table->is_dead)
	{
		pthread_mutex_unlock(&(philo->table->print));
		return ;
	}
	write(1, text, ft_strlen(text));
	pthread_mutex_unlock(&(philo->table->print));
	usleep(philo->table->time_to_sleep);
	free(timestamp);
	free(id);
}

void	print_think(t_philo *philo, unsigned long long t, int i)
{
	char	*timestamp;
	char	*id;
	char 	text[1000];

	
	timestamp = ft_itoa(t);
	id = ft_itoa(i);
	stringer(timestamp, id,"is thinking\n", &text);
	pthread_mutex_lock(&(philo->table->print));
	if (philo->table->is_dead)
	{
		pthread_mutex_unlock(&(philo->table->print));
		return ;
	}
	write(1, text, ft_strlen(text));
	pthread_mutex_unlock(&(philo->table->print));
	free(timestamp);
	free(id);
}


void	print_fork(t_philo *philo, unsigned long long t, int i)
{
	char	*timestamp;
	char	*id;
	char 	text[1000];
	
	timestamp = ft_itoa(t);
	id = ft_itoa(i);
	stringer(timestamp, id, "has taken a fork\n", text);
	pthread_mutex_lock(&(philo->table->print));
	if (philo->table->is_dead)
	{
		pthread_mutex_unlock(&(philo->table->print));
		return ;
	}
	write(1, text, ft_strlen(text));
	pthread_mutex_unlock(&(philo->table->print));
	free(timestamp);
	free(id);
}

void	print_eat(t_philo *philo, unsigned long long t, int i)
{
	char	*timestamp;
	char	*id;
	char 	text[1000];

	
	timestamp = ft_itoa(t);
	id = ft_itoa(i);
	philo->is_eating = 1;
	stringer(timestamp, id, "is eating\n", &text);
	pthread_mutex_lock(&(philo->table->print));
	if (philo->table->is_dead)
	{
		pthread_mutex_unlock(&(philo->table->print));
		return ;
	}
	write(1, text, ft_strlen(text));
	pthread_mutex_unlock(&(philo->table->print));
	free(timestamp);
	free(id);
}
