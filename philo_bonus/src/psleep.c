/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   psleep.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 20:57:52 by bammar            #+#    #+#             */
/*   Updated: 2023/03/18 00:19:57 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	psleep(time_t milliseconds)
{
	time_t	start;

	start = get_time();
	while (1)
	{
		if (get_time() - start >= milliseconds)
			break ;
		usleep(100);
	}
}
