/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduregon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 15:13:58 by aduregon          #+#    #+#             */
/*   Updated: 2021/04/16 15:27:21 by aduregon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int main(int argc, char **argv)
{
	int		pid = 1;
	int 	i;

	i = -1;
	while (++i < 3 && pid)
		pid = fork();
	if (!pid)
	{
		printf("sono il processo %d figlio, i:%d\n", pid, i);
	}
	else
	{
		while (i-- > 0)
			wait(0);
		printf("sono il processo %d padre\n", pid);
	}

}