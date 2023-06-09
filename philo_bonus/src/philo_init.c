/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 15:27:25 by bammar            #+#    #+#             */
/*   Updated: 2023/03/20 20:32:07 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	**get_philos(t_philo_args *args)
{
	size_t	i;
	t_philo	**philos;

	philos = malloc((args->count + 1) * sizeof(t_philo *));
	if (!philos)
		return (print_error("Error\nNo mem\n"), NULL);
	i = 0;
	while (i < args->count)
	{
		philos[i] = malloc(sizeof(t_philo));
		if (!(philos[i]))
			return (print_error("Error\nNo mem\n"), NULL);
		memset(philos[i], 0, sizeof(t_philo));
		philos[i]->state = 0;
		philos[i]->num = i + 1;
		philos[i]->last_mealtime = get_time();
		i++;
	}
	philos[i] = NULL;
	return (philos);
}
