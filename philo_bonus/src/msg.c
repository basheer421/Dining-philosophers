/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 17:23:19 by bammar            #+#    #+#             */
/*   Updated: 2023/03/20 19:30:07 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] != 0 && s2[i] != 0 && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	print_msg(t_process_arg *targ, const char *state)
{
	sem_wait(targ->print_sem);
	printf(
		"%s%ld %s%lu %s\n%s",
		"",
		get_time() - targ->args->start_time,
		"",
		targ->philo->num,
		state,
		"");
	if (ft_strncmp("died", state, 5) == 0)
		return ;
	sem_post(targ->print_sem);
}
