/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 20:08:55 by bammar            #+#    #+#             */
/*   Updated: 2023/03/18 01:26:28 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	simulate_philos(t_philo_args *args, t_philo **philos)
{
	size_t			i;
	size_t			limits_reached;
	t_thread_arg	*thrd_arg;
	bool			is_exit;
	pthread_mutex_t	exit_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	limit_mutex;
	
	thrd_arg = malloc((sizeof(t_thread_arg)) * (args->count + 1));
	if (!thrd_arg)
		return ;
	pthread_mutex_init(&(exit_mutex), NULL);
	pthread_mutex_init(&(print_mutex), NULL);
	pthread_mutex_init(&(limit_mutex), NULL);
	is_exit = false;
	memset(thrd_arg, 0, sizeof(t_thread_arg));
	limits_reached = 0;
	i = 0;
	while (i < args->count)
	{
		thrd_arg[i].limits_reached = &limits_reached;
		thrd_arg[i].args = args;
		thrd_arg[i].philo = philos[i];
		thrd_arg[i].is_exit = &is_exit;
		thrd_arg[i].exit_mutex = &exit_mutex;
		thrd_arg[i].print_mutex = &print_mutex;
		thrd_arg[i].limit_mutex = &limit_mutex;
		philos[i]->last_mealtime = get_time();
		if (pthread_create(philos[i]->thread, NULL,
			philo_life, &(thrd_arg[i])) != 0)
				return ;	
		i++;
	}
	i = 0;
	while (i < args->count)
		pthread_join(*(philos[i++]->thread), NULL);
	// pthread_mutex_destroy(&(exit_mutex));
	// pthread_mutex_destroy(&(print_mutex));
	// pthread_mutex_destroy(&(limit_mutex));
	return (free(thrd_arg));
}
