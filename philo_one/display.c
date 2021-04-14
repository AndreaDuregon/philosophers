/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simonegiovo <simonegiovo@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 16:15:02 by aduregon          #+#    #+#             */
/*   Updated: 2021/04/14 21:21:23 by simonegiovo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void stringer(char *timestamp, char *id, char *phrase, char final[1000])
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(timestamp[i])
		final[j++]=timestamp[i++];
	i = 0;
	final[j++]= ' ';
	while(id[i])
		final[j++]=id[i++];
	final[j++]= ' ';
	while(phrase[i])
		final[j++] = phrase[i++];
	final[j] = 0;
}


void	print_dead(t_philo *philo, unsigned long long t, int i)
{
	char	*timestamp;
	char	*id;
	char 	text[1000];
	timestamp = ft_itoa(t);
	id = ft_itoa(i);
	stringer(timestamp, id, " is dead\n", &text);
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
	stringer(timestamp, id, " is sleeping\n", &text);
	pthread_mutex_lock(&(philo->table->print));
	write(1, text, ft_strlen(text));
	pthread_mutex_unlock(&(philo->table->print));
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
	stringer(timestamp, id," is thinking\n", &text);
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

	timestamp = ft_itoa(t);
	id = ft_itoa(i);
	stringer(timestamp, id, " has taken a fork\n", text);
	pthread_mutex_lock(&(philo->table->print));
	write(1, text, ft_strlen(text));
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
	stringer(timestamp, id, " is eating\n", &text);
	pthread_mutex_lock(&(philo->table->print));
	write(1, text, ft_strlen(text));
	pthread_mutex_unlock(&(philo->table->print));
	free(timestamp);
	free(id);
}
