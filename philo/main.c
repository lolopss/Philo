/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldaniel <ldaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 13:13:36 by ldaniel           #+#    #+#             */
/*   Updated: 2023/08/12 14:42:52 by ldaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	*data;

	if (check_args(ac, av) == -1)
		return (-1);
	data = malloc(sizeof(t_data));
	data->nb_philo = ft_atoi(av[1]);
	init_struct(data, ac, av);
	//if (data->nb_philo == 1)
	//	init_one(data);
	//else
	init_thread(data);
	free(data);
	return (0);
}
