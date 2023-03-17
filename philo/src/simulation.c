/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 20:08:55 by bammar            #+#    #+#             */
/*   Updated: 2023/03/18 01:53:01 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	start_thread(t_philo_args *args, t_philo *philo,
	t_thread_arg	*thrd_arg, t_sim_args *sim_args)
{
	thrd_arg->limits_reached = &(sim_args->limits_reached);
	thrd_arg->args = args;
	thrd_arg->philo = philo;
	thrd_arg->is_exit = &(sim_args->is_exit);
	thrd_arg->exit_mutex = &(sim_args->exit_mutex);
	thrd_arg->print_mutex = &(sim_args->print_mutex);
	thrd_arg->limit_mutex = &(sim_args->limit_mutex);
	philo->last_mealtime = get_time();
	if (pthread_create(philo->thread, NULL,
			philo_life, (thrd_arg)) != 0)
		return ;
}

void	simulate_philos(t_philo_args *args, t_philo **philos)
{
	size_t			i;
	t_sim_args		sim_args;

	sim_args.thrd_arg = malloc((sizeof(t_thread_arg)) * (args->count + 1));
	if (!sim_args.thrd_arg)
		return ;
	pthread_mutex_init(&(sim_args.exit_mutex), NULL);
	pthread_mutex_init(&(sim_args.print_mutex), NULL);
	pthread_mutex_init(&(sim_args.limit_mutex), NULL);
	sim_args.is_exit = false;
	memset(sim_args.thrd_arg, 0, sizeof(t_thread_arg));
	sim_args.limits_reached = 0;
	i = 0;
	while (i < args->count)
	{
		start_thread(args, philos[i], &(sim_args.thrd_arg[i]), &sim_args);
		i++;
	}
	i = 0;
	while (i < args->count)
		pthread_join(*(philos[i++]->thread), NULL);
	pthread_mutex_destroy(&(sim_args.exit_mutex));
	pthread_mutex_destroy(&(sim_args.print_mutex));
	pthread_mutex_destroy(&(sim_args.limit_mutex));
	return (free(sim_args.thrd_arg));
}
