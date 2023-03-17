/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 20:23:36 by bammar            #+#    #+#             */
/*   Updated: 2023/03/17 15:38:26 by bammar           ###   ########.fr       */
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

static void	set_forks(t_thread_arg *targ, bool val, size_t lastuser)
{
	if (targ->philo->num % 2 == 0)
	{
		pthread_mutex_lock(targ->philo->rfork->is_used_mutex);
		pthread_mutex_lock(targ->philo->lfork->is_used_mutex);
	}
	else
	{
		pthread_mutex_lock(targ->philo->lfork->is_used_mutex);
		pthread_mutex_lock(targ->philo->rfork->is_used_mutex);
	}
	targ->philo->rfork->is_used = val;
	targ->philo->lfork->is_used = val;
	targ->philo->rfork->last_user = lastuser;
	targ->philo->lfork->last_user = lastuser;
	pthread_mutex_unlock(targ->philo->rfork->is_used_mutex);
	pthread_mutex_unlock(targ->philo->lfork->is_used_mutex);
}

static bool	forks_available(t_thread_arg *targ)
{
	if (targ->philo->num % 2 == 0)
	{
		pthread_mutex_lock(targ->philo->rfork->is_used_mutex);
		pthread_mutex_lock(targ->philo->lfork->is_used_mutex);
	}
	else
	{
		pthread_mutex_lock(targ->philo->lfork->is_used_mutex);
		pthread_mutex_lock(targ->philo->rfork->is_used_mutex);
	}
	
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



static bool	eat(t_thread_arg *targ)
{
	if (dead(targ) || !forks_available(targ))
		return (false);
	if (targ->philo->num % 2 == 0)
	{
		pthread_mutex_lock(targ->philo->rfork->mutex);
		pthread_mutex_lock(targ->philo->lfork->mutex);
	}
	else
	{
		pthread_mutex_lock(targ->philo->lfork->mutex);
		pthread_mutex_lock(targ->philo->rfork->mutex);
	}
	set_forks(targ, true, targ->philo->num);
	if (dead(targ))
		return ((void)pthread_mutex_unlock(targ->philo->rfork->mutex),
			(void)pthread_mutex_unlock(targ->philo->lfork->mutex),
			false);
	targ->philo->state = EATING;
	print_msg(targ, "has taken a fork");
	print_msg(targ, "has taken a fork");
	print_msg(targ, "is eating");
	targ->philo->last_mealtime = get_time();
	psleep(targ->args->eat_time);
	
	pthread_mutex_unlock(targ->philo->rfork->mutex);
	pthread_mutex_unlock(targ->philo->lfork->mutex);
	set_forks(targ, false, targ->philo->num);
	return (true);
}

static void	go_sleep(t_thread_arg *targ)
{
	if (dead(targ) || targ->philo->state == SLEEPING)
		return ;
	print_msg(targ, "is sleeping");
	psleep(targ->args->sleep_time);
	targ->philo->state = SLEEPING;
}

static void	think(t_thread_arg *targ)
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
