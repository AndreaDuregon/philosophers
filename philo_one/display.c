/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalori <dmalori@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 16:15:02 by aduregon          #+#    #+#             */
/*   Updated: 2021/04/15 10:41:08 by dmalori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void stringer(char *timestamp, char *id, char *phrase, char final[1000])
{
	int j;

	j = 0;
	while(*timestamp)
		final[j++]=*timestamp++;
	final[j++]= ' ';
	while(*id)
		final[j++]=*id++;
	final[j++]= ' ';
	while(*phrase)
		final[j++] = *phrase++;
	final[j] = 0;
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
	write(1, text, ft_strlen(text));
	pthread_mutex_unlock(&(philo->table->print));
	free(timestamp);
	free(id);
	exit(0);
}

void	print_sleep(t_philo *philo, unsigned long long t, int i)
{
	char	*timestamp;
	char	*id;
	char 	*text[1000];

	timestamp = ft_itoa(t);
	id = ft_itoa(i);
	stringer(timestamp, id, "is sleeping\n", &text);
	pthread_mutex_lock(&(philo->table->print));
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
	char 	*text[1000];

	timestamp = ft_itoa(t);
	id = ft_itoa(i);
	stringer(timestamp, id,"is thinking\n", &text);
	pthread_mutex_lock(&(philo->table->print));
	write(1, text, ft_strlen(text));
	pthread_mutex_unlock(&(philo->table->print));
	free(timestamp);
	free(id);
}


void	print_fork(t_philo *philo, unsigned long long t, int i)
{
	char	*timestamp;
	char	*id;
	char 	*text[1000];
	char 	*text2[1000];

	timestamp = ft_itoa(t);
	id = ft_itoa(i);
	stringer(timestamp, id, "has taken a fork\n", text);
	stringer(timestamp, id, "is eating\n", text2);
	pthread_mutex_lock(&(philo->table->print));
	write(1, text, ft_strlen(text));
	write(1, text, ft_strlen(text));
	write(1, text2, ft_strlen(text2));
	pthread_mutex_unlock(&(philo->table->print));
	free(timestamp);
	free(id);
}

void	print_eat(t_philo *philo, unsigned long long t, int i)
{
	char	*timestamp;
	char	*id;
	char 	*text[1000];

	timestamp = ft_itoa(t);
	id = ft_itoa(i);
	stringer(timestamp, id, "is eating\n", &text);
	pthread_mutex_lock(&(philo->table->print));
	write(1, text, ft_strlen(text));
	pthread_mutex_unlock(&(philo->table->print));
	free(timestamp);
	free(id);
}
