/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 17:23:19 by bammar            #+#    #+#             */
/*   Updated: 2023/03/19 20:05:12 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_msg(t_process_arg *targ, const char *state)
{
	sem_wait(targ->print_sem);
	printf(
		"%s%ld %s%lu %s\n%s",
		"", get_time() - targ->args->start_time,
		"", targ->philo->num,
		state,
		""
		);
	if (strncmp("died", state, 5) == 0)
	{
		sem_post(targ->exit_sem);
		return ;
		// usleep(100);
	}
	sem_post(targ->print_sem);
}
