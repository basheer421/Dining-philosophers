/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 22:14:59 by bammar            #+#    #+#             */
/*   Updated: 2023/03/19 19:58:09 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	dead(t_process_arg *targ)
{
	bool	is_dead;

	is_dead = false;
	if (get_time() - targ->philo->last_mealtime
		>= (time_t)targ->args->die_time)
	{
		if (!is_dead)
			print_msg(targ, "died");
		sem_post(targ->exit_sem);
		exit(0);
		is_dead = true;
	}
	sem_wait(targ->limit_sem);
	if (targ->args->is_limited
		&& (*targ->limits_reached) == targ->args->count)
		is_dead = true;
	sem_post(targ->limit_sem);
	return (is_dead);
}

void	think(t_process_arg *targ)
{
	if (dead(targ) || targ->philo->state == THINKING)
		return ;
	print_msg(targ, "is thinking");
	targ->philo->state = THINKING;
}

void	go_sleep(t_process_arg *targ)
{
	if (dead(targ) || targ->philo->state == SLEEPING)
		return ;
	print_msg(targ, "is sleeping");
	psleep(targ->args->sleep_time);
	targ->philo->state = SLEEPING;
}

// static void	increase_limits_reached(t_process_arg *targ)
// {
// 	sem_wait(targ->limit_sem);
// 	if (targ->philo->eat_count == targ->args->eat_limit)
// 		(*targ->limits_reached)++;
// 	sem_post(targ->limit_sem);
// }

void philo_life(t_process_arg *targ)
{
	while (true)
	{
		// increase_limits_reached(targ);
		if (dead(targ))
			return ;
		if (eat(targ))
			go_sleep(targ);
		else
			think(targ);
	}
	return ;
}
