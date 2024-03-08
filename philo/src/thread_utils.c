/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlopez <hlopez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:10:34 by hlopez            #+#    #+#             */
/*   Updated: 2024/03/07 17:59:20 by hlopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_set_bool(pthread_mutex_t *mutex, bool *dest, bool value)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}

bool	ft_get_bool(pthread_mutex_t *mutex, bool *dest)
{
	bool	res;

	pthread_mutex_lock(mutex);
	res = *dest;
	pthread_mutex_unlock(mutex);
	return (res);
}

void	ft_set_long(pthread_mutex_t *mutex, long *dest, long value)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}

long	ft_get_long(pthread_mutex_t *mutex, long *dest)
{
	long	res;

	pthread_mutex_lock(mutex);
	res = *dest;
	pthread_mutex_unlock(mutex);
	return (res);
}

bool	ft_dinner_end(t_dinner *d)
{
	return (ft_get_bool(&d->mutex, &d->end));
}
