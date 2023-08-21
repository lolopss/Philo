/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldaniel <ldaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 11:33:45 by ldaniel           #+#    #+#             */
/*   Updated: 2023/08/21 11:34:07 by ldaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat2(t_philo *philo, int l_fork, int r_fork, int *i)
{
	(*i)++;
	pthread_mutex_lock(&(philo->data->max_eat_mutex));
	if ((*i) == philo->data->eat_amount)
		philo->data->max_eat += 1;
	pthread_mutex_unlock(&(philo->data->max_eat_mutex));
	usleep(philo->t_eat * 1000);
	pthread_mutex_lock(&(philo->data->time_m));
	philo->last_eat = time_stamp(philo->time);
	pthread_mutex_unlock(&(philo->data->time_m));
	pthread_mutex_unlock(&(philo->data->forks[r_fork]));
	pthread_mutex_unlock(&(philo->data->forks[l_fork]));
}

int	eat(t_philo *philo, int l_fork, int r_fork, int *i)
{
	pthread_mutex_lock(&(philo->data->forks[l_fork]));
	pthread_mutex_lock(&(philo->data->print_mutex));
	if (death_philo(philo) != 1 && check_max_eat(philo->data) != 1)
	{
		pthread_mutex_lock(&(philo->data->time_m));
		printf("[ %lldms ]  |  Philo  %d  has taken a fork\n",
			time_stamp(philo->time), philo->nb);
		pthread_mutex_unlock(&(philo->data->time_m));
	}
	pthread_mutex_unlock(&(philo->data->print_mutex));
	pthread_mutex_lock(&(philo->data->forks[r_fork]));
	pthread_mutex_lock(&(philo->data->print_mutex));
	if (death_philo(philo) != 1 && check_max_eat(philo->data) != 1)
	{
		pthread_mutex_lock(&(philo->data->time_m));
		printf("[ %lldms ]  |  Philo  %d  has taken a fork\n",
			time_stamp(philo->time), philo->nb);
		printf("[ %lldms ]  |  Philo  %d  is eating\n", time_stamp(philo->time),
			philo->nb);
		pthread_mutex_unlock(&(philo->data->time_m));
	}
	pthread_mutex_unlock(&(philo->data->print_mutex));
	eat2(philo, l_fork, r_fork, i);
	return (0);
}

void	thinking(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->print_mutex));
	if ((death_philo(philo) != 1) && (check_max_eat(philo->data) != 1))
	{
		pthread_mutex_lock(&(philo->data->time_m));
		printf("[ %lldms ]  |  Philo  %d  is thinking\n",
			time_stamp(philo->time), philo->nb);
		pthread_mutex_unlock(&(philo->data->time_m));
	}
	pthread_mutex_unlock(&(philo->data->print_mutex));
}

void	*routine(t_philo *philo, int l_fork, int r_fork)
{
	int	i;

	i = 0;
	while (death_philo(philo) != 1)
	{
		if (eat(philo, l_fork, r_fork, &i) == -1)
			break ;
		pthread_mutex_lock(&(philo->data->print_mutex));
		if (death_philo(philo) != 1 && check_max_eat(philo->data) != 1)
		{
			pthread_mutex_lock(&(philo->data->time_m));
			printf("[ %lldms ]  |  Philo  %d  is sleeping\n",
				time_stamp(philo->time), philo->nb);
			pthread_mutex_unlock(&(philo->data->time_m));
		}
		pthread_mutex_unlock(&(philo->data->print_mutex));
		usleep(philo->t_sleep * 1000);
		thinking(philo);
	}
	return (NULL);
}
