/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 23:01:13 by bammar            #+#    #+#             */
/*   Updated: 2023/03/19 20:01:34 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	eat(t_process_arg *targ)
{
	if (targ->args->count == 1)
		return (false);
	sem_wait(targ->forks_sem);
	targ->philo->state = EATING;
	if (targ->args->is_limited
		&& targ->args->eat_limit == targ->philo->eat_count)
		return (true);
	print_msg(targ, "has taken a fork");
	print_msg(targ, "has taken a fork");
	print_msg(targ, "is eating");
	targ->philo->last_mealtime = get_time();
	psleep(targ->args->eat_time);
	targ->philo->eat_count++;
	sem_post(targ->forks_sem);
	return (true);
}
