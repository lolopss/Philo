/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldaniel <ldaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 13:06:02 by ldaniel           #+#    #+#             */
/*   Updated: 2023/08/21 11:38:39 by ldaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_max_eat(t_data *data)
{
	pthread_mutex_lock(&(data->max_eat_mutex));
	if (data->max_eat == data->nb_philo)
	{
		pthread_mutex_unlock(&(data->max_eat_mutex));
		return (1);
	}
	pthread_mutex_unlock(&(data->max_eat_mutex));
	return (0);
}

void	check_death_philo_1(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (is_philo_dead(&data->philo[i]) == 1)
		{
			data->is_dead = 1;
			pthread_mutex_lock(&(data->time_m));
			pthread_mutex_lock(&(data->print_mutex));
			printf("[ %lldms ]  |  Philo  %d  is dead\n",
				time_stamp(data->philo->time), i + 1);
			pthread_mutex_unlock(&(data->time_m));
			pthread_mutex_unlock(&(data->print_mutex));
			clean_exit(data);
		}
		i++;
	}
	usleep(9000);
	data->is_dead = 1;
	clean_exit(data);
}

void	check_death(t_data *data)
{
	int	i;

	while (check_max_eat(data) != 1)
	{
		i = 0;
		while (i < data->nb_philo)
		{
			if (is_philo_dead(&data->philo[i]) == 1)
			{
				data->is_dead = 1;
				pthread_mutex_lock(&(data->time_m));
				printf("[ %lldms ]  |  Philo  %d  is dead\n",
					time_stamp(data->philo->time), i + 1);
				pthread_mutex_unlock(&(data->time_m));
				clean_exit(data);
			}
			i++;
		}
		usleep(9000);
	}
	data->is_dead = 1;
	clean_exit(data);
}

int	death_philo(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->death_mutex));
	if (philo->dead == 1)
	{
		pthread_mutex_unlock(&(philo->data->death_mutex));
		return (1);
	}
	pthread_mutex_unlock(&(philo->data->death_mutex));
	return (0);
}
