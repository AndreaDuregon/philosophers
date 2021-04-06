/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduregon <aduregon@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 20:20:26 by aduregon          #+#    #+#             */
/*   Updated: 2021/04/06 11:09:16 by aduregon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "philo_one.h"

int		philo_life(void)
{
	
}

int		main(int argc, char **argv)
{
	pthread_t	*philo;
	int 		i;

	if (argc < 5 || argc > 6)
		return 1;
	philo = ft_malloc(sizeof(t_philo), argv[1]);
	i = 0;
	while (i < argv[1])
	{
		pthread_create(&philo[i], NULL, philo_life, NULL);
	}
	
}