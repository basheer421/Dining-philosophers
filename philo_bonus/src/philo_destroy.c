/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_destroy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 17:15:11 by bammar            #+#    #+#             */
/*   Updated: 2023/03/18 22:14:06 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_destroy(t_philo **philos)
{
	int	i;

	i = -1;
	while (philos[++i])
		free(philos[i]);
	free(philos);
	sem_unlink(".exit");
	sem_unlink(".forks");
	sem_unlink(".limit");
	sem_unlink(".print");
}
