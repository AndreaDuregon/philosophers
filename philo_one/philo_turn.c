/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_turn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simonegiovo <simonegiovo@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 16:55:51 by aduregon          #+#    #+#             */
/*   Updated: 2021/04/14 21:47:40 by simonegiovo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	philo_eat_odd(t_philo *philo)
{
	int sleeped;

	sleeped = 0;
	pthread_mutex_lock(&(philo->table->status));
	print_fork(philo, get_time_stamp() - philo->table->start, philo->id);
	print_fork(philo, get_time_stamp() - philo->table->start, philo->id);
	philo->table->cont++;
	philo->remain_meal++;
	print_eat(philo, get_time_stamp() - philo->table->start, philo->id);
	if (philo->table->cont == philo->table->num_philo / 2)
	{
		usleep(philo->table->time_to_eat);
		sleeped = 1;
		if (philo->table->round == 1)
		{
			philo->table->turn++;
			philo->table->round = 2;
		}
		else
			philo->table->round = 1;
		philo->table->cont = 0;
	}
	pthread_mutex_unlock(&(philo->table->status));
	if (!sleeped)
		usleep(philo->table->time_to_eat);
	philo->eat_time = get_time_stamp();
}

void	philo_eat_even(t_philo *philo)
{
	/* int sleeped;
	
	sleeped = 0; */
	pthread_mutex_lock(&(philo->table->status));
	print_fork(philo, get_time_stamp() - philo->table->start, philo->id);
	print_fork(philo, get_time_stamp() - philo->table->start, philo->id);
	philo->table->cont++;
	philo->remain_meal++;
	print_eat(philo, get_time_stamp() - philo->table->start, philo->id);
	if (philo->table->cont == philo->table->num_philo / 2)
	{
		/* sleeped = 1;
		usleep(philo->table->time_to_eat); */
		if (philo->table->round == 1)
		{
			philo->table->turn++;
			philo->table->round = 0;
		}
		else
			philo->table->round = 1;
		philo->table->cont = 0;
	}
	pthread_mutex_unlock(&(philo->table->status));
	philo->eat_time = get_time_stamp();
	/* if(!sleeped) */
	usleep(philo->table->time_to_eat);
}

void	philo_eat_last(t_philo *philo)
{
	pthread_mutex_lock(&(philo->table->status));
	print_fork(philo, get_time_stamp() - philo->table->start, philo->id);
	print_fork(philo, get_time_stamp() - philo->table->start, philo->id);
	philo->table->round = 0;
	philo->remain_meal++;
	print_eat(philo, get_time_stamp() - philo->table->start, philo->id);
	usleep(philo->table->time_to_eat);
	pthread_mutex_unlock(&(philo->table->status));
	philo->eat_time = get_time_stamp();
}

int	philo_even(t_philo *philo, pthread_t monitor)
{
	if (philo->remain_meal == philo->table->turn)
	{
		philo_eat_even(philo);
		ft_sleep(philo);
	}
	if (philo->remain_meal == philo->table->num_meal)
	{
		philo->status = 1;
		pthread_detach(monitor);
		return (0);
	}
	return (1);
}

int	philo_odd(t_philo *philo, pthread_t monitor)
{
	if (philo->table->round == philo->id % 2 && \
		philo->remain_meal == philo->table->turn
		&& philo->id != philo->table->num_philo - 1)
	{
		philo_eat_odd(philo);
		ft_sleep(philo);
	}
	else
	{
		philo_eat_last(philo);
		ft_sleep(philo);
	}
	if (philo->remain_meal == philo->table->num_meal)
	{
		philo->status = 1;
		pthread_detach(monitor);
		return (0);
	}
	return (1);
}