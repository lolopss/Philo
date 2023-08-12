/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldaniel <ldaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 09:27:49 by ldaniel           #+#    #+#             */
/*   Updated: 2023/08/12 15:47:35 by ldaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_death(t_data *data)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < data->nb_philo)
		{
			if (is_philo_dead(&data->philo[i]) == 1)
			{
				data->is_dead = 1;
				printf("[ %lldms ]  |  Philo  %d  is dead\n",
					time_stamp(data->philo->time), i + 1);
				clean_exit(data);
			}
			i++;
		}
		usleep(1000);
	}
}

int	eat(t_philo *philo, int l_fork, int r_fork, int *i)
{
	pthread_mutex_lock(&(philo->data->forks[l_fork]));
	pthread_mutex_lock(&(philo->data->print_mutex));
	if (!philo->data->is_dead && philo->data->max_eat != 1)
		printf("[ %lldms ]  |  Philo  %d  has taken a fork\n",
			time_stamp(philo->time), philo->nb);
	pthread_mutex_unlock(&(philo->data->print_mutex));
	pthread_mutex_lock(&(philo->data->forks[r_fork]));
	pthread_mutex_lock(&(philo->data->print_mutex));
	if (!philo->data->is_dead && philo->data->max_eat != 1)
	{
		printf("[ %lldms ]  |  Philo  %d  has taken a fork\n",
			time_stamp(philo->time), philo->nb);
		printf("[ %lldms ]  |  Philo  %d  is eating\n",
			time_stamp(philo->time), philo->nb);
	}
	pthread_mutex_unlock(&(philo->data->print_mutex));
	(*i)++;
	if ((*i) == philo->data->eat_amount)
	{
		pthread_mutex_unlock(&(philo->data->forks[philo->l_fork]));
		pthread_mutex_unlock(&(philo->data->forks[philo->r_fork]));
		printf("philo  :   %d\n", philo->nb);
		philo->data->max_eat = 1;
		clean_exit(philo->data);
	}
	usleep(philo->data->t_eat * 1000);
	philo->last_eat = time_stamp(philo->time);
	pthread_mutex_unlock(&(philo->data->forks[r_fork]));
	pthread_mutex_unlock(&(philo->data->forks[l_fork]));
	return (0);
}

void	routine(t_philo *philo, int l_fork, int r_fork)
{
	int	i;

	i = 0;
	while (philo->data->is_dead != 1 && philo->data->max_eat != 1)
	{
		if (eat(philo, l_fork, r_fork, &i) == -1)
			break ;
		pthread_mutex_lock(&(philo->data->print_mutex));
		if (!philo->data->is_dead && philo->data->max_eat != 1)
			printf("[ %lldms ]  |  Philo  %d  is sleeping\n",
				time_stamp(philo->time), philo->nb);
		pthread_mutex_unlock(&(philo->data->print_mutex));
		usleep(philo->data->t_sleep * 1000);
		pthread_mutex_lock(&(philo->data->print_mutex));
		if (!philo->data->is_dead && philo->data->max_eat != 1)
			printf("[ %lldms ]  |  Philo  %d  is thinking\n",
				time_stamp(philo->time), philo->nb);
		pthread_mutex_unlock(&(philo->data->print_mutex));
	}
	return ;
}

void	*philo_life(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	if (philo->nb % 2 == 0)
		usleep(philo->data->t_eat * 1000);
	if (philo->nb % 2 == 0)
		routine(philo, philo->r_fork, philo->l_fork);
	else
		routine(philo, philo->l_fork, philo->r_fork);
	return (NULL);
}
