/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduregon <aduregon@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 20:40:46 by aduregon          #+#    #+#             */
/*   Updated: 2021/04/06 11:09:01 by aduregon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>

typedef struct  s_philo
{
	int			philo_num;
	int			die;
	int			eat;
	int			sleep;
	int			meal;
}				t_philo;

void			*ft_malloc(size_t size, size_t mol);

#endif