/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlopez <hlopez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:01:47 by hlopez            #+#    #+#             */
/*   Updated: 2024/03/07 14:33:33 by hlopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (-1);
	return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
}

long	ft_get_utime(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (-1);
	return (tv.tv_sec * 1e6 + tv.tv_usec);
}

void	ft_usleep(long usec, t_dinner *d)
{
	long	start;
	long	elapsed;
	long	remaining;

	start = ft_get_utime();
	while (ft_get_utime() - start < usec)
	{
		if (ft_dinner_end(d))
			break ;
		elapsed = ft_get_utime() - start;
		remaining = usec - elapsed;
		if (remaining > 1e4)
			usleep(remaining / 2);
		else
			while (ft_get_utime() - start < usec)
				;
	}
}
