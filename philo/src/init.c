/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlopez <hlopez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 11:36:13 by hlopez            #+#    #+#             */
/*   Updated: 2024/02/27 12:04:48 by hlopez           ###   ########.fr       */
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
	ph->next = NULL;
	ph->prev = NULL;
}

static void	ft_add_philo(t_diner *d, t_philo *new)
{
	t_philo	*last;

	if (d->ph == NULL)
		d->ph = new;
	else
	{
		last = d->ph->prev;
		new->prev = last;
		new->next = d->ph;
		d->ph->prev = new;
		last->next = new;
	}
}

static void	ft_init_philos(t_diner *d)
{
	t_philo	*ph;
	int		i;

	i = 0;
	while (i++ < d->number_of_philosophers)
	{
		ft_add_philo(d, ft_create_philo(i));
	}
}

void	ft_init(t_diner *d, int ac, char **av)
{
	d->number_of_philosophers = ft_atoi(av[1]);
	d->time_to_die = ft_atoi(av[2]);
	d->time_to_eat = ft_atoi(av[3]);
	d->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
	{
		d->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
		// peut-etre dans une autre boucle pour faire une fonction avec et une sans limite
	}
}
