/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_lock.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 23:53:56 by bammar            #+#    #+#             */
/*   Updated: 2023/03/17 23:54:14 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock2(pthread_mutex_t *m1, pthread_mutex_t *m2)
{
	if (m1)
		pthread_mutex_lock(m1);
	if (m2)
		pthread_mutex_lock(m2);
}

void	unlock2(pthread_mutex_t *m1, pthread_mutex_t *m2)
{
	if (m1)
		pthread_mutex_unlock(m1);
	if (m2)
		pthread_mutex_unlock(m2);
}
