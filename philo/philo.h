/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldaniel <ldaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 11:34:40 by ldaniel           #+#    #+#             */
/*   Updated: 2023/08/12 14:42:34 by ldaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

struct	s_data;

typedef struct s_philo
{
	long long		time;
	int				nb;
	int				dead;
	int				l_fork;
	int				r_fork;
	int				last_eat;
	pthread_t		thread;
	struct s_data	*data;
}			t_philo;

typedef struct s_data
{
	t_philo				*philo;
	int					t_die;
	int					t_eat;
	int					t_sleep;
	int					eat_amount;
	int					nb_philo;
	int					is_dead;
	int					max_eat;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		death_mutex;
}			t_data;

long long	time_stamp(long long time_start);
void		init_thread(t_data *data);
int			is_nb(const char *str);
int			check_args(int ac, char **av);
int			ft_atoi(const char *str);
void		init_struct(t_data *data, int ac, char **av);
void		*philo_life(void *arg);
void		clean_exit(t_data *data);
void		check_death(t_data *data);
void		*philo_life(void *arg);
int			is_philo_dead(t_philo *philo);
//void		init_one(t_data *data);
#endif
