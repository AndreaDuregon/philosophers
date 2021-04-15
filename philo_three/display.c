/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalori <dmalori@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 16:15:02 by aduregon          #+#    #+#             */
/*   Updated: 2021/04/15 12:28:25 by dmalori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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
	sem_wait((philo->table->print));
	write(1, text, ft_strlen(text));
	sem_post((philo->table->print));
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
	sem_wait((philo->table->print));
	write(1, text, ft_strlen(text));
	sem_post((philo->table->print));
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
	sem_wait((philo->table->print));
	write(1, text, ft_strlen(text));
	sem_post((philo->table->print));
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
	sem_wait((philo->table->print));
	write(1, text, ft_strlen(text));
	write(1, text, ft_strlen(text));
	write(1, text2, ft_strlen(text2));
	sem_post((philo->table->print));
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
	sem_wait((philo->table->print));
	write(1, text, ft_strlen(text));
	sem_post((philo->table->print));
	free(timestamp);
	free(id);
}
