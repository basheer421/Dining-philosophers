/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 22:14:59 by bammar            #+#    #+#             */
/*   Updated: 2023/03/18 22:49:38 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

philo_life(t_process_arg *targ)
{
	while (true)
	{
		increase_limits_reached(targ);
		if (dead(targ))
			return ;
		if (eat(targ))
			go_sleep(targ);
		else
			think(targ);
	}
	return ;
}
