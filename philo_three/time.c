/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: forsili <forsili@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 17:26:29 by aduregon          #+#    #+#             */
/*   Updated: 2021/04/19 14:34:41 by forsili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

u_int64_t	get_time_stamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec) * 1000 + (tv.tv_usec) / 1000);
}
