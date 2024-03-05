/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlopez <hlopez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:47:50 by hlopez            #+#    #+#             */
/*   Updated: 2024/03/05 13:49:43 by hlopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	wait_all_threads(t_dinner *d)
{
	
}

void	*ft_dining(void *data)
{
	t_dinner	*d;

	d = (t_dinner *)data;
	wait_all_threads(d);
	return (NULL);
}
