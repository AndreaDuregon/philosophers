/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalori <dmalori@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 13:10:28 by aduregon          #+#    #+#             */
/*   Updated: 2021/04/19 15:57:58 by dmalori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	print_fork(t_philo *philo, unsigned long long t, int i)
{
	char	*timestamp;
	char	*id;
	char	text[1000];

	timestamp = ft_itoa(t);
	id = ft_itoa(i);
	stringer(timestamp, id, "has taken a fork\n", text);
	sem_wait((philo->table->print));
	if (philo->table->is_dead)
	{
		sem_post((philo->table->print));
		return ;
	}
	write(1, text, ft_strlen(text));
	sem_post((philo->table->print));
	free(timestamp);
	free(id);
}

void	print_eat(t_philo *philo, unsigned long long t, int i)
{
	char	*timestamp;
	char	*id;
	char	text[1000];

	timestamp = ft_itoa(t);
	id = ft_itoa(i);
	stringer(timestamp, id, "is eating\n", text);
	sem_wait((philo->table->print));
	if (philo->table->is_dead)
	{
		sem_post((philo->table->print));
		return ;
	}
	write(1, text, ft_strlen(text));
	sem_post((philo->table->print));
	free(timestamp);
	free(id);
}
