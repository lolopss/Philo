/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldaniel <ldaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 16:06:32 by ldaniel           #+#    #+#             */
/*   Updated: 2023/08/21 11:38:05 by ldaniel          ###   ########.fr       */
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
	else
		data->eat_amount = -1;
}

void	init_mutex(t_data *data)
{
	int	i;

	if (pthread_mutex_init(&(data->time_m), NULL) != 0)
		clean_exit(data);
	if (pthread_mutex_init(&(data->death_mutex), NULL) != 0)
		clean_exit(data);
	if (pthread_mutex_init(&(data->print_mutex), NULL) != 0)
		clean_exit(data);
	if (pthread_mutex_init(&(data->max_eat_mutex), NULL) != 0)
		clean_exit(data);
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL) != 0)
			clean_exit(data);
		i++;
	}
}

void	initialize_philosophers(t_data *data, long long time, int i)
{
	int	status;

	data->philo[i].t_sleep = data->t_sleep;
	data->philo[i].t_eat = data->t_eat;
	data->philo[i].t_die = data->t_die;
	data->philo[i].nb = i + 1;
	data->philo[i].l_fork = data->philo[i].nb - 1;
	data->philo[i].r_fork = (data->philo[i].nb) % data->nb_philo;
	data->philo[i].data = data;
	data->philo[i].dead = 0;
	pthread_mutex_lock(&(data->time_m));
	data->philo[i].time = time;
	data->philo[i].last_eat = time_stamp(time);
	pthread_mutex_unlock(&(data->time_m));
	if (data->nb_philo == 1)
		status = pthread_create(&(data->philo[i].thread), NULL, ft_solitude,
				&data->philo[i]);
	else
		status = pthread_create(&(data->philo[i].thread), NULL, philo_life,
				&data->philo[i]);
	if (status != 0)
		clean_exit(data);
}

void	init_2(t_data *data)
{
	data->philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (data->philo == NULL)
		return ;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (data->forks == NULL)
	{
		ft_free(data);
		return ;
	}
	data->is_dead = 0;
	data->max_eat = 0;
}

void	init_thread(t_data *data)
{
	int			i;
	long long	time;

	time = time_stamp(0);
	i = 0;
	init_2(data);
	init_mutex(data);
	while (i < data->nb_philo)
	{
		initialize_philosophers(data, time, i);
		i++;
	}
	if (data->nb_philo == 1)
		check_death_philo_1(data);
	else
		check_death(data);
}
