/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 17:23:19 by bammar            #+#    #+#             */
/*   Updated: 2023/03/18 22:48:27 by bammar           ###   ########.fr       */
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
	sem_post(targ->print_sem);
}
