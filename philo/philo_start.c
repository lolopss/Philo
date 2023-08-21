/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldaniel <ldaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 11:38:10 by ldaniel           #+#    #+#             */
/*   Updated: 2023/08/21 11:30:19 by ldaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	time_stamp(long long time_start)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
	{
		printf("Error from timestamp, a philosopher will die.\n");
		return (9999);
	}
	return ((tv.tv_sec * 1000 + tv.tv_usec / 1000) - time_start);
}
