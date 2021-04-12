/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduregon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 20:40:46 by aduregon          #+#    #+#             */
/*   Updated: 2021/04/12 18:12:01 by aduregon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct	s_table
{
	int				cont;
	int				turn;
	int				num_philo;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	int				num_meal;
	int				round;
	uint64_t	 	now;
	pthread_mutex_t	status;
	pthread_mutex_t	print;
	pthread_mutex_t	dead;
	uint64_t		start;
}				t_table;

typedef struct s_philo
{
	int				id;
	int				status;
	uint64_t		eat_time;
	uint64_t		sleep_time;
	int				remain_meal;
	t_table			*table;
}					t_philo;


void			*ft_memset(void *s, int c, size_t n);
void    		*ft_calloc(size_t nelem, size_t elsize);
int				ft_isspace(int c);
int				ft_isdigit(int c);
int				ft_atoi(const char *nptr);
void			input_error(void);
uint64_t		get_time_stamp(void);

#endif