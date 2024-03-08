/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlopez <hlopez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:47:50 by hlopez            #+#    #+#             */
/*   Updated: 2024/03/08 13:20:47 by hlopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_all_threads(t_dinner *d)
{
	while (!ft_get_bool(&d->mutex, &d->threads_ready))
		ft_usleep(50, d);
}

void	*ft_dining_solo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	return (NULL);
}

void	*ft_dining(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	ft_set_long(&philo->mutex, &philo->last_meal, ft_get_utime());
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
	if (d->number_of_times_philos_must_eat == 0)
		return (1);
	else if (d->number_of_philos == 1)
	{
		if (pthread_create(&d->ph[0]->thread, NULL, ft_dining_solo, d->ph[0]))
			return (0);
	}
	else
		while (++i < d->number_of_philos)
			if (pthread_create(&d->ph[i]->thread, NULL, ft_dining, d->ph[i]))
				return (0);
	if (pthread_create(&d->monitor, NULL, ft_monitoring, d) != 0)
		return (0);
	d->start_time = ft_get_utime();
	ft_set_bool(&d->mutex, &d->threads_ready, true);
	i = -1;
	while (++i < d->number_of_philos)
		if (pthread_join(d->ph[i]->thread, NULL) != 0)
			return (0);
	ft_set_bool(&d->mutex, &d->end, true);
	if (pthread_join(d->monitor, NULL) != 0)
		return (0);
	return (1);
}
