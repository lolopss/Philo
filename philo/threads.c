/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldaniel <ldaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 09:27:49 by ldaniel           #+#    #+#             */
/*   Updated: 2023/08/21 11:35:11 by ldaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_solitude(void *phi)
{
	t_philo	*philo;

	philo = (t_philo *)phi;
	pthread_mutex_lock(&philo->data->print_mutex);
	pthread_mutex_lock(&philo->data->forks[philo->l_fork]);
	printf("[ %lldms ]  |  Philo  %d  has taken a fork\n",
		time_stamp(philo->time), philo->nb);
	pthread_mutex_unlock(&philo->data->print_mutex);
	pthread_mutex_unlock(&philo->data->forks[philo->l_fork]);
	usleep(philo->t_die * 1000);
	printf("[ %lldms ]  |  Philo  %d  is dead\n",
		time_stamp(philo->data->philo->time), 1);
	return (NULL);
}

void	*philo_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->nb % 2 == 0)
		usleep((philo->data->t_eat + 10) * 1000);
	if (philo->nb % 2 == 0)
		routine(philo, philo->r_fork, philo->l_fork);
	else
		routine(philo, philo->l_fork, philo->r_fork);
	return (NULL);
}
