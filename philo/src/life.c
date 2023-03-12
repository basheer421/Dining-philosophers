/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 20:23:36 by bammar            #+#    #+#             */
/*   Updated: 2023/03/12 22:02:17 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	dead(t_thread_arg *targ)
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

static bool	forks_available(t_thread_arg *targ)
{
	pthread_mutex_lock(targ->philo->lfork->is_used_mutex);
	pthread_mutex_lock(targ->philo->rfork->is_used_mutex);
	if (targ->philo->lfork->is_used || targ->philo->rfork->is_used
		|| targ->philo->lfork->last_user == targ->philo->num
		|| targ->philo->rfork->last_user == targ->philo->num)
	{
		pthread_mutex_unlock(targ->philo->rfork->is_used_mutex);
		pthread_mutex_unlock(targ->philo->lfork->is_used_mutex);
		return (false);
	}
	pthread_mutex_unlock(targ->philo->rfork->is_used_mutex);
	pthread_mutex_unlock(targ->philo->lfork->is_used_mutex);
	return (true);
}

static void	set_forks(t_thread_arg *targ, bool val)
{
	pthread_mutex_lock(targ->philo->lfork->is_used_mutex);
	pthread_mutex_lock(targ->philo->rfork->is_used_mutex);
	targ->philo->rfork->is_used = val;
	targ->philo->lfork->is_used = val;
	pthread_mutex_unlock(targ->philo->rfork->is_used_mutex);
	pthread_mutex_unlock(targ->philo->lfork->is_used_mutex);
}

static bool	eat(t_thread_arg *targ)
{
	if (!forks_available(targ))
		return (false);
	pthread_mutex_lock(targ->philo->lfork->mutex);
	pthread_mutex_lock(targ->philo->rfork->mutex);
	set_forks(targ, true);
	targ->philo->rfork->last_user = targ->philo->num;
	targ->philo->lfork->last_user = targ->philo->num;
	if (dead(targ))
		return ((void)pthread_mutex_unlock(targ->philo->rfork->mutex),
			(void)pthread_mutex_unlock(targ->philo->rfork->mutex),
			false);
	print_msg(targ, "has taken a fork");
	print_msg(targ, "has taken a fork");
	print_msg(targ, "is eating");
	psleep(targ->args->eat_time);
	pthread_mutex_unlock(targ->philo->rfork->mutex);
	pthread_mutex_unlock(targ->philo->lfork->mutex);
	set_forks(targ, false);
	return (true);
}

static void	go_sleep(t_thread_arg *targ)
{
	print_msg(targ, "is sleeping");
	psleep(targ->args->sleep_time);
}

static void	think(t_thread_arg *targ)
{
	if (dead(targ))
		return ;
	print_msg(targ, "is thinking");
	while (true)
	{
		if (forks_available(targ))
			return ;
	}
}



void	*philo_life(void *t_arg)
{
	t_thread_arg	*targ;

	targ = (t_thread_arg *) (t_arg);
	if (dead(targ))
		return (NULL);
	if (eat(targ))
		go_sleep(targ);
	else
		think(targ);
	return (NULL);
}
