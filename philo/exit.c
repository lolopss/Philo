/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldaniel <ldaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 13:01:43 by ldaniel           #+#    #+#             */
/*   Updated: 2023/08/21 12:19:31 by ldaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_philo_dead(t_philo *philo)
{
	long long	current_time;
	long long	good_time;

	pthread_mutex_lock(&(philo->data->time_m));
	current_time = time_stamp(philo->time);
	pthread_mutex_unlock(&(philo->data->time_m));
	pthread_mutex_lock(&(philo->data->time_m));
	good_time = (current_time - philo->last_eat);
	pthread_mutex_unlock(&(philo->data->time_m));
	if (good_time > philo->data->t_die)
	{
		return (1);
	}
	return (0);
}

void	ft_free(t_data *data)
{
	if (data->forks)
		free(data->forks);
	if (data->forks)
		free(data->philo);
	if (data)
		free(data);
}

void	clean_exit(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_lock(&(data->death_mutex));
		data->philo[i].dead = 1;
		pthread_mutex_unlock(&(data->death_mutex));
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
	pthread_mutex_destroy(&(data->print_mutex));
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&(data->forks[i]));
		i++;
	}
	ft_free(data);
	exit(0);
}
