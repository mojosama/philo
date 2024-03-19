/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlopez <hlopez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:47:50 by hlopez            #+#    #+#             */
/*   Updated: 2024/03/19 15:24:20 by hlopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_all_threads(t_dinner *d)
{
	while (!ft_get_bool(&d->mutex, &d->threads_ready))
		ft_usleep(50, d);
}

static void	*ft_dining_solo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	ft_set_long(&philo->mutex, &philo->last_meal, ft_get_utime());
	ft_write_status(philo, FORK);
	while (!ft_dinner_end(philo->table))
		;
	return (NULL);
}

static void	*ft_dining(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	ft_set_long(&philo->mutex, &philo->last_meal, ft_get_utime());
	if (philo->number % 2 == 0)
	{
		ft_think(philo);
		ft_usleep(500, philo->table);
	}
	while (!ft_dinner_end(philo->table) && !philo->full)
	{
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (NULL);
}

int	ft_start_dinner(t_dinner *d)
{
	int	i;

	i = -1;
	if (d->number_of_philos == 1)
		ft_safe_pthread_create(&d->ph[0]->thread, ft_dining_solo, d->ph[0]);
	else
		while (++i < d->number_of_philos)
			ft_safe_pthread_create(&d->ph[i]->thread, ft_dining, d->ph[i]);
	ft_safe_pthread_create(&d->monitor, ft_monitoring, d);
	ft_set_long(&d->mutex, &d->start_time, ft_get_utime());
	ft_set_bool(&d->mutex, &d->threads_ready, true);
	i = -1;
	while (++i < d->number_of_philos)
		ft_safe_pthread_join(d->ph[i]->thread);
	ft_safe_pthread_join(d->monitor);
	return (1);
}
