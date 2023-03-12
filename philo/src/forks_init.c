/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 15:36:32 by bammar            #+#    #+#             */
/*   Updated: 2023/03/12 21:20:13 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_fork	**get_forks(t_philo_args *args)
{
	size_t	i;
	t_fork	**forks;

	forks = malloc((args->count + 1) * sizeof(t_fork *));
	if (!forks)
		return (print_error("Error\nNo mem\n"), NULL);
	i = 0;
	while (i < args->count)
	{
		forks[i] = malloc(sizeof(t_fork));
		if (!(forks[i]))
			return (print_error("Error\nNo mem\n"), NULL);
		memset(forks[i], 0, sizeof(t_fork));
		forks[i]->mutex = malloc(sizeof(pthread_mutex_t));
		forks[i]->is_used_mutex = malloc(sizeof(pthread_mutex_t));
		if (!forks[i]->mutex || !forks[i]->is_used_mutex)
			return (print_error("Error\nNo mem\n"), NULL);
		pthread_mutex_init(forks[i]->mutex, NULL);
		pthread_mutex_init(forks[i]->is_used_mutex, NULL);
		i++;
	}
	forks[i] = NULL;
	return (forks);
}
