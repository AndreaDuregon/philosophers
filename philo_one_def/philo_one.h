/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduregon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 20:40:46 by aduregon          #+#    #+#             */
/*   Updated: 2021/04/19 13:19:40 by aduregon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_table
{
	int				num_philo;
	u_int64_t		time_to_die;
	u_int64_t		time_to_eat;
	u_int64_t		time_to_sleep;
	int				num_meal;
	int				is_dead;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
	pthread_mutex_t	dead;
	u_int64_t		start;
}				t_table;

typedef struct s_philo
{
	int				id;
	int				status;
	u_int64_t		eat_time;
	u_int64_t		sleep_time;
	int				remain_meal;
	t_table			*table;
}					t_philo;

void			*ft_memset(void *s, int c, size_t n);
void			*ft_calloc(size_t nelem, size_t elsize);
int				ft_isspace(int c);
int				ft_isdigit(int c);
int				ft_atoi(const char *nptr);
void			input_error(void);
u_int64_t		get_time_stamp(void);
void			ft_usleep(int t);
static	size_t	ft_nsize(int n);
char			*ft_itoa(int n);
size_t			ft_strlen(const char *s);
int				parse_input(char **argv, int argc);
t_table			init_table2(t_table table, char **argv, int argc);
t_table			init_table(char **argv, int argc);
t_philo			*init_philo(t_table table);
void			stringer(char *timestamp, char *id, char *phrase,
					char final[1000]);
void			print_dead(t_philo *philo, unsigned long long t, int i);
void			print_sleep(t_philo *philo, unsigned long long t, int i);
void			print_think(t_philo *philo, unsigned long long t, int i);
void			print_fork(t_philo *philo, unsigned long long t, int i);
void			print_eat(t_philo *philo, unsigned long long t, int i);
void			start_life(char **argv, t_philo *philo, pthread_t *p,
					t_table table);
void			ft_sleep(t_philo *philo);
void			philo_eat(t_philo *philo);
void			philo_sleep(t_philo *philo);
void			philo_think(t_philo *philo);
void			wait_turn(t_philo *philo);		
void			ft_exit(void);

#endif