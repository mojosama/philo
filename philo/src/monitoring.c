/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlopez <hlopez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:23:45 by hlopez            #+#    #+#             */
/*   Updated: 2024/03/29 13:43:42 by hlopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline int	ft_death(t_philo *philo)
{
	long	elapsed;
	long	start_time;

	if (!ft_set_bool(&philo->table->mutex, &philo->table->end, true))
		return (0);
	start_time = ft_get_long(&philo->table->mutex, &philo->table->start_time);
	elapsed = (long)((ft_get_utime() - start_time) * 0.001);
	if (!ft_safe_mutex_handle(&philo->table->print_mutex, LOCK))
		return (0);
	printf("💀 %ld %d died. 💀\n", elapsed, philo->number);
	if (!ft_safe_mutex_handle(&philo->table->print_mutex, UNLOCK))
		return (0);
	return (1);
}

static int	ft_philo_died(t_philo *philo)
{
	long	elapsed;
	long	start_time;
	long	last_meal;

	if (ft_get_bool(&philo->mutex, &philo->full) == 1)
		return (false);
	last_meal = ft_get_long(&philo->mutex, &philo->last_meal);
	if (last_meal < 0)
		return (-1);
	start_time = ft_get_long(&philo->table->mutex, &philo->table->start_time);
	if (start_time < 0)
		return (-1);
	elapsed = ft_get_utime() - last_meal;
	if (elapsed > philo->table->time_to_die && start_time < last_meal)
		return (true);
	else
		return (false);
}

void	*ft_monitoring(void *data)
{
	t_dinner	*d;
	int			i;
	int			full;

	d = (t_dinner *)data;
	wait_all_threads(d);
	while (!ft_dinner_end(d))
	{
		i = -1;
		full = 0;
		while (++i < d->number_of_philos && !ft_dinner_end(d))
		{
			if (ft_philo_died(d->ph[i]))
				return (ft_death(d->ph[i]), NULL);
			else if (ft_get_bool(&d->ph[i]->mutex, &d->ph[i]->full) == 1)
				full++;
			if (full == d->number_of_philos)
			{
				printf("All philosophers are full!\n");
				if (!ft_set_bool(&d->mutex, &d->end, true))
					return (NULL);
			}
		}
	}
	return (NULL);
}

int	ft_write_status(t_philo *philo, t_status status)
{
	long	elapsed;
	long	start_time;

	start_time = ft_get_long(&philo->table->mutex, &philo->table->start_time);
	if (start_time < 0)
		return (0);
	elapsed = (long)((ft_get_utime() - start_time) * 0.001);
	if (!ft_safe_mutex_handle(&philo->table->print_mutex, LOCK))
		return (0);
	if (!ft_dinner_end(philo->table))
	{
		if (status == EAT)
			printf("🍝 %ld %d is eating. 🍝\n", elapsed, philo->number);
		else if (status == SLEEP)
			printf("💤 %ld %d is sleeping. 💤\n", elapsed, philo->number);
		else if (status == THINK)
			printf("💭 %ld %d is thinking. 💭\n", elapsed, philo->number);
		else if (status == FORK)
			printf("🍴 %ld %d has taken a fork. 🍴\n", elapsed, philo->number);
		else if (status == FULL)
			printf("😋 %ld %d is full. 😋\n", elapsed, philo->number);
	}
	if (!ft_safe_mutex_handle(&philo->table->print_mutex, UNLOCK))
		return (0);
	return (1);
}
