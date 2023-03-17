/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 23:52:51 by bammar            #+#    #+#             */
/*   Updated: 2023/03/18 00:42:07 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	set_forks(t_thread_arg *targ, bool val, size_t lastuser)
{
	if (targ->philo->num % 2 == 0)
		lock2(targ->philo->rfork->is_used_mutex,
			targ->philo->lfork->is_used_mutex);
	else
		lock2(targ->philo->lfork->is_used_mutex,
			targ->philo->rfork->is_used_mutex);
	targ->philo->rfork->is_used = val;
	targ->philo->lfork->is_used = val;
	targ->philo->rfork->last_user = lastuser;
	targ->philo->lfork->last_user = lastuser;
	unlock2(targ->philo->rfork->is_used_mutex,
			targ->philo->lfork->is_used_mutex);
	return (true);
}

static bool	forks_available(t_thread_arg *targ)
{
	if (targ->args->count == 1)
		return (false);
	if (targ->philo->num % 2 == 0)
		lock2(targ->philo->rfork->is_used_mutex,
			targ->philo->lfork->is_used_mutex);
	else
		lock2(targ->philo->lfork->is_used_mutex,
			targ->philo->rfork->is_used_mutex);
	if (targ->philo->lfork->is_used || targ->philo->rfork->is_used
		|| targ->philo->lfork->last_user == targ->philo->num
		|| targ->philo->rfork->last_user == targ->philo->num)
	{
		unlock2(targ->philo->rfork->is_used_mutex,
			targ->philo->lfork->is_used_mutex);
		return (false);
	}
	unlock2(targ->philo->rfork->is_used_mutex,
			targ->philo->lfork->is_used_mutex);
	return (true);
}

static void	lock_by_order(t_thread_arg *targ)
{
	if (targ->philo->num % 2 == 0)
		lock2(targ->philo->rfork->mutex,
			targ->philo->lfork->mutex);
	else
		lock2(targ->philo->lfork->mutex,
			targ->philo->rfork->mutex);
}

static bool	over_limit(t_thread_arg *targ)
{
	return (targ->args->is_limited 
		&& targ->args->eat_limit == targ->philo->eat_count);
}

bool	eat(t_thread_arg *targ)
{
	if (dead(targ) || !forks_available(targ))
		return (false);
	lock_by_order(targ);
	set_forks(targ, true, targ->philo->num);
	if (dead(targ))
		return (unlock2(targ->philo->rfork->mutex,
			targ->philo->lfork->mutex),
			set_forks(targ, false, targ->philo->num));
	targ->philo->state = EATING;
	if (over_limit(targ))
		return (unlock2(targ->philo->rfork->mutex,
			targ->philo->lfork->mutex),
			set_forks(targ, false, targ->philo->num));	
	print_msg(targ, "has taken a fork");
	print_msg(targ, "has taken a fork");
	print_msg(targ, "is eating");
	targ->philo->last_mealtime = get_time();
	psleep(targ->args->eat_time);
	targ->philo->eat_count++;
	return (unlock2(targ->philo->rfork->mutex,
			targ->philo->lfork->mutex),
			set_forks(targ, false, targ->philo->num));
}
