/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldaniel <ldaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 16:06:32 by ldaniel           #+#    #+#             */
/*   Updated: 2023/08/12 15:47:09 by ldaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_struct(t_data *data, int ac, char **av)
{
	(void)ac;
	data->t_die = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->eat_amount = ft_atoi(av[5]);
}

int	is_philo_dead(t_philo *philo)
{
	long long	current_time;
	long long	good_time;

	current_time = time_stamp(philo->time);
	good_time = (current_time - philo->last_eat);
	if (good_time >= philo->data->t_die)
	{
		return (1);
	}
	return (0);
}

void	clean_exit(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
	pthread_mutex_unlock(&(data->print_mutex));
	pthread_mutex_destroy(&(data->print_mutex));
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_unlock(&(data->forks[i]));
		pthread_mutex_destroy(&(data->forks[i]));
		i++;
	}
	free(data->forks);
	free(data->philo);
	free(data);
	exit(0);
}

void	initialize_philosophers(t_data *data, long long time, int i)
{
	int		status;

	if (pthread_mutex_init(&(data->forks[i]), NULL) != 0)
		clean_exit(data);
	data->philo[i].nb = i + 1;
	data->philo[i].l_fork = data->philo[i].nb - 1;
	data->philo[i].r_fork = (data->philo[i].nb) % data->nb_philo;
	data->philo[i].data = data;
	data->philo[i].time = time;
	data->philo[i].last_eat = time_stamp(time);
	status = pthread_create(&(data->philo[i].thread),
			NULL, philo_life, &data->philo[i]);
	if (status != 0)
		clean_exit(data);
}

void	init_thread(t_data *data)
{
	int				i;
	long long		time;

	time = time_stamp(0);
	i = 0;
	data->philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (data->philo == NULL)
		return ;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (data->forks == NULL)
		return ;
	data->is_dead = 0;
	data->max_eat = 0;
	if (pthread_mutex_init(&(data->print_mutex), NULL) != 0)
		clean_exit(data);
	while (i < data->nb_philo)
	{
		initialize_philosophers(data, time, i);
		i++;
	}
	check_death(data);
}
