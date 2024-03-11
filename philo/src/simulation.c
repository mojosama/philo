/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlopez <hlopez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 18:43:10 by hlopez            #+#    #+#             */
/*   Updated: 2024/03/09 16:03:08 by hlopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_eat(t_philo *philo)
{
	if (philo->number % 2)
	{
		pthread_mutex_lock(&philo->left_fork->mutex);
		ft_write_status(philo, FORK);
		pthread_mutex_lock(&philo->right_fork->mutex);
		ft_write_status(philo, FORK);
	}
	else
	{
		pthread_mutex_lock(&philo->right_fork->mutex);
		ft_write_status(philo, FORK);
		pthread_mutex_lock(&philo->left_fork->mutex);
		ft_write_status(philo, FORK);
	}
	ft_write_status(philo, EAT);
	philo->last_meal = ft_get_utime();
	philo->meals++;
	if (philo->table->number_of_times_philos_must_eat > 0
		&& philo->meals >= philo->table->number_of_times_philos_must_eat)
		ft_set_bool(&philo->mutex, &philo->full, true);
	ft_usleep(philo->table->time_to_eat, philo->table);
	pthread_mutex_unlock(&philo->right_fork->mutex);
	pthread_mutex_unlock(&philo->left_fork->mutex);
}

void	ft_sleep(t_philo *philo)
{
	ft_write_status(philo, SLEEP);
	ft_usleep(philo->table->time_to_sleep, philo->table);
}

void	ft_think(t_philo *philo)
{
	ft_write_status(philo, THINK);
}

void	ft_death(t_philo *philo)
{
	ft_write_status(philo, DEATH);
	ft_set_bool(&philo->table->mutex, &philo->table->end, true);
}
