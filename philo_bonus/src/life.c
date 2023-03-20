/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 22:14:59 by bammar            #+#    #+#             */
/*   Updated: 2023/03/20 20:44:22 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static time_t	get_lastmeal_time(t_process_arg *targ)
{
	time_t			lmt;

	pthread_mutex_lock(targ->philo->mealtime_mutex);
	lmt = targ->philo->last_mealtime;
	pthread_mutex_unlock(targ->philo->mealtime_mutex);
	return (lmt);
}

static void	*dead(void *t_arg)
{
	bool			is_dead;
	t_process_arg	*targ;

	targ = t_arg;
	is_dead = false;
	while (!is_dead)
	{
		if (get_time() - get_lastmeal_time(targ)
			>= (time_t)targ->args->die_time)
		{
			if (!is_dead)
				print_msg(targ, "died");
			is_dead = true;
		}
		else if (targ->args->is_limited
			&& targ->args->eat_limit == targ->philo->eat_count)
			is_dead = true;
		if (is_dead)
		{
			sem_post(targ->exit_sem);
			exit(0);
		}
	}
	return (NULL);
}

void	think(t_process_arg *targ)
{
	if (targ->philo->state == THINKING)
		return ;
	print_msg(targ, "is thinking");
	targ->philo->state = THINKING;
}

void	go_sleep(t_process_arg *targ)
{
	if (targ->philo->state == SLEEPING)
		return ;
	print_msg(targ, "is sleeping");
	psleep(targ->args->sleep_time);
	targ->philo->state = SLEEPING;
}

void	philo_life(t_process_arg *targ)
{
	pthread_t		thread;
	pthread_mutex_t	meal_mutex;

	pthread_mutex_init(&meal_mutex, NULL);
	targ->philo->mealtime_mutex = &meal_mutex;
	pthread_create(&thread, NULL, dead, targ);
	while (true)
	{
		psleep(1);
		if (eat(targ))
			go_sleep(targ);
		else
			think(targ);
	}
	return ;
}
