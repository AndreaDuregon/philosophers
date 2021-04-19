/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgiovo <sgiovo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 20:20:26 by aduregon          #+#    #+#             */
/*   Updated: 2021/04/19 14:37:51 by sgiovo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	main(int argc, char **argv)
{
	t_table		table;
	t_philo		*philo;
	pthread_t	*p;

	if (argc < 5 || argc > 6)
		input_error();
	if (!parse_input(argv, argc))
		input_error();
	p = ft_calloc(ft_atoi(argv[1]), sizeof(pthread_t));
	table = init_table(argv, argc);
	philo = init_philo(table);
	start_life(philo, p, table);
	free(philo);
	free(p);
}
