/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_destroy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 17:15:11 by bammar            #+#    #+#             */
/*   Updated: 2023/03/14 03:29:45 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_destroy(t_fork **forks, t_philo **philos)
{
	int	i;

	i = -1;
	while (forks[++i])
	{
		pthread_mutex_destroy(forks[i]->mutex);
		free(forks[i]->mutex);
		free(forks[i]->is_used_mutex);
		free(forks[i]);
	}
	i = -1;
	while (philos[++i])
	{
		free(philos[i]->thread);
		free(philos[i]);
	}
	free(forks);
	free(philos);
}
