/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 20:23:36 by bammar            #+#    #+#             */
/*   Updated: 2023/03/18 00:56:51 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	dead(t_thread_arg *targ)
{
	bool	is_dead;

	is_dead = false;
	pthread_mutex_lock(targ->exit_mutex);
	if (*targ->is_exit)
		is_dead = true;
	else if (get_time() - targ->philo->last_mealtime
		>= (time_t)targ->args->die_time)
	{
		if (!is_dead)
			print_msg(targ, "died");
		is_dead = true;
	}
	*targ->is_exit = is_dead;
	pthread_mutex_unlock(targ->exit_mutex);
	return (is_dead);
}

void	go_sleep(t_thread_arg *targ)
{
	if (dead(targ) || targ->philo->state == SLEEPING)
		return ;
	print_msg(targ, "is sleeping");
	psleep(targ->args->sleep_time);
	targ->philo->state = SLEEPING;
}

void	think(t_thread_arg *targ)
{
	if (dead(targ) || targ->philo->state == THINKING)
		return ;
	print_msg(targ, "is thinking");
	targ->philo->state = THINKING;
}

void	*philo_life(void *t_arg)
{
	t_thread_arg	*targ;

	targ = (t_thread_arg *) (t_arg);
	while (true)
	{
		if (dead(targ))
			return (NULL);
		if (eat(targ))
			go_sleep(targ);
		else
			think(targ);
	}
	return (NULL);
}
