/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlopez <hlopez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 11:36:13 by hlopez            #+#    #+#             */
/*   Updated: 2024/03/20 16:41:20 by hlopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_philo	*ft_create_philo(int number, t_dinner *d)
{
	t_philo	*ph;

	ph = malloc(sizeof(t_philo));
	if (!ph)
		return (NULL);
	ph->number = number;
	ph->full = false;
	ph->meals = 0;
	ph->table = d;
	ph->last_meal = ft_get_utime();
	ph->right_fork = d->forks[number - 1];
	if (number != d->number_of_philos)
		ph->left_fork = d->forks[number];
	else
		ph->left_fork = d->forks[0];
	if (!ft_safe_mutex_handle(&ph->mutex, INIT))
		return (NULL);
	return (ph);
}

static int	ft_init_philos(t_dinner *d)
{
	int	i;

	d->ph = (t_philo **)malloc(sizeof(t_philo *) * d->number_of_philos);
	if (!d->ph)
		return (0);
	i = -1;
	while (++i < d->number_of_philos)
	{
		d->ph[i] = ft_create_philo(i + 1, d);
		if (!d->ph[i])
			return (0);
	}
	return (1);
}

static int	ft_init_forks(t_dinner *d)
{
	int	i;

	d->forks = (t_fork **)malloc(sizeof(t_fork *) * d->number_of_philos);
	if (!d->forks)
		return (0);
	i = 0;
	while (i < d->number_of_philos)
	{
		d->forks[i] = malloc(sizeof(t_fork));
		if (!d->forks[i])
			return (0);
		if (!ft_safe_mutex_handle(&d->forks[i]->mutex, INIT))
			return (0);
		d->forks[i]->free = true;
		i++;
	}
	return (1);
}

int	ft_init(t_dinner *d, int ac, char **av)
{
	d->number_of_philos = (int)ft_atol(av[1]);
	d->time_to_die = ft_atol(av[2]) * 1e3;
	d->time_to_eat = ft_atol(av[3]) * 1e3;
	d->time_to_sleep = ft_atol(av[4]) * 1e3;
	if (d->number_of_philos == -1 || d->time_to_die == -1
		|| d->time_to_eat == -1 || d->time_to_sleep == -1)
		return (0);
	if (ac == 6)
	{
		d->max_meals = ft_atol(av[5]);
		if (d->max_meals == -1)
			return (0);
	}
	else
		d->max_meals = -42;
	d->threads_ready = false;
	d->end = false;
	d->start_time = 0;
	if (!ft_safe_mutex_handle(&d->mutex, INIT))
		return (0);
	if (!ft_safe_mutex_handle(&d->print_mutex, INIT))
		return (0);
	if (!ft_init_forks(d) || !ft_init_philos(d))
		return (0);
	return (1);
}
