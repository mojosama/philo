/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlopez <hlopez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 11:36:13 by hlopez            #+#    #+#             */
/*   Updated: 2024/02/28 15:28:24 by hlopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_philo	*ft_create_philo(int number)
{
	t_philo	*ph;

	ph = malloc(sizeof(t_philo));
	if (!ph)
		return (NULL);
	ph->number = number;
	ph->alive = true;
	return (ph);
}

static int	ft_init_philos(t_diner *d)
{
	int	i;

	d->ph = (t_philo **)malloc(sizeof(t_philo *) * d->number_of_philos);
	if (!d->ph)
		return ;
	i = -1;
	while (++i < d->number_of_philos)
	{
		d->ph[i] = ft_create_philo(i + 1);
		if (!d->ph[i])
			return (0);
	}
	return (1);
}

int	ft_init(t_diner *d, int ac, char **av)
{
	d->number_of_philos = ft_atoi(av[1]);
	d->time_to_die = ft_atoi(av[2]);
	d->time_to_eat = ft_atoi(av[3]);
	d->time_to_sleep = ft_atoi(av[4]);
	if (d->number_of_philos == -1 || d->time_to_die == -1 || d->time_to_eat == -1 || d->time_to_sleep == -1)
		return (0);
	if (ac == 6)
	{
		d->number_of_times_philos_must_eat = ft_atoi(av[5]);
		if (d->number_of_times_philos_must_eat == -1)
			return (0);
		// peut-etre dans une autre boucle pour faire une fonction avec et une sans limite
	}
	ft_init_philos(d);
	return (1);
}
