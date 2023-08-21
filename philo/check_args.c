/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldaniel <ldaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 15:04:19 by ldaniel           #+#    #+#             */
/*   Updated: 2023/08/21 11:32:22 by ldaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(const char *src)
{
	int	i;

	i = 0;
	while (src && src[i])
		i++;
	return (i);
}

long int	ft_atol_modif(const char *str)
{
	int			i;
	long int	sign;
	long int	result;

	result = 0;
	sign = 1;
	i = -1;
	if (str[++i] == '-')
		return (-1);
	if (str[i] == '+')
		i++;
	while (str[i] && str[i] == '0')
		i++;
	if (ft_strlen(str + i) > 10)
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	result = 0;
	sign = 1;
	i = -1;
	if (str[++i] == '-')
		return (-1);
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

int	is_str_nb(char *av)
{
	int			i;
	long int	nb;

	i = 0;
	while (av[i] != '\0')
	{
		if (!(av[i] >= '0' && av[i] <= '9'))
			return (-1);
		i++;
	}
	nb = ft_atol_modif(av);
	if (nb <= 0 || nb > 2147483647)
		return (-1);
	return (0);
}

int	check_args(int ac, char **av)
{
	int			i;
	long int	nb;

	i = 1;
	if (ac < 5 || ac > 6)
		return (-1);
	while (i < ac)
	{
		if (is_str_nb(av[i]) == -1)
			return (-1);
		i++;
	}
	nb = ft_atol_modif(av[1]);
	if (nb <= 0 || nb > 2147483647)
		return (-1);
	return (0);
}
