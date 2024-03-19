/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlopez <hlopez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:23:45 by hlopez            #+#    #+#             */
/*   Updated: 2024/03/19 15:06:42 by hlopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	ft_philo_died(t_philo *philo)
{
	long	elapsed;
	long	start_time;
	long	last_meal;
	long	since_beginning; // delete later

	last_meal = ft_get_long(&philo->mutex, &philo->last_meal);
	start_time = ft_get_long(&philo->table->mutex, &philo->table->start_time);
	elapsed = ft_get_utime() - last_meal;
	since_beginning = ft_get_utime() - start_time; // delete later
	if (elapsed > philo->table->time_to_die
		&& start_time < last_meal)
	{
		printf("Elapsed since:\n"); // delete later
		printf("beginning: %ld\n", since_beginning); // delete later
		printf("last meal: %ld\n", elapsed); // delete later
		printf("meals: %ld\n", ft_get_long(&philo->mutex, &philo->meals)); // delete later
		return (true);
	}
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
			else if (ft_get_bool(&d->ph[i]->mutex, &d->ph[i]->full))
				full++;
			if (full == d->number_of_philos)
			{
				printf("All philosophers are full!\n");
				ft_set_bool(&d->mutex, &d->end, true);
			}
		}
	}
	return (NULL);
}

void	ft_write_status(t_philo *philo, t_status status)
{
	long	elapsed;
	long	start_time;

	start_time = ft_get_long(&philo->table->mutex, &philo->table->start_time);
	elapsed = (long)((ft_get_utime() - start_time) * 0.001);
	if (status == EAT && !ft_dinner_end(philo->table))
		printf("🍝 %ld %d is eating. 🍝\n", elapsed, philo->number);
	else if (status == SLEEP && !ft_dinner_end(philo->table))
		printf("💤 %ld %d is sleeping. 💤\n", elapsed, philo->number);
	else if (status == THINK && !ft_dinner_end(philo->table))
		printf("💭 %ld %d is thinking. 💭\n", elapsed, philo->number);
	else if (status == FORK && !ft_dinner_end(philo->table))
		printf("🍴 %ld %d has taken a fork. 🍴\n", elapsed, philo->number);
	else if (status == DEATH && !ft_dinner_end(philo->table))
	{
		ft_set_bool(&philo->table->mutex, &philo->table->end, true);
		printf("💀 %ld %d died. 💀\n", elapsed, philo->number);
	}
	else if (status == FULL && !ft_dinner_end(philo->table))
		printf("😋 %ld %d is full. 😋\n", elapsed, philo->number);
	else if (!ft_dinner_end(philo->table))
		error_exit("Wrong status passed as argument.\n");
}
