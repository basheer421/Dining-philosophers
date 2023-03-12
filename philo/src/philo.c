/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 22:09:14 by bammar            #+#    #+#             */
/*   Updated: 2023/03/12 21:56:21 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_error(const char *msg)
{
	write(2, msg, ft_strlen(msg));
}

int	main(int argc, char **argv)
{
	t_philo_args	args;
	t_fork			**forks;
	t_philo			**philos;

	if (argc != 5 && argc != 6)
		return (print_error("Error\nIncorrect arguments\n"), EXIT_FAILURE);
	if (!fill_philo_args(argc, argv, &args))
		return (print_error("Error\nIncorrect arguments\n"), EXIT_FAILURE);
	forks = get_forks(&args);
	if (!forks)
		return (print_error("Error\nNo mem\n"), EXIT_FAILURE);
	philos = get_philos(forks, &args);
	if (!philos)
		return (print_error("Error\nNo mem\n"), EXIT_FAILURE);
	simulate_philos(&args, philos);
	return (philo_destroy(forks, philos), EXIT_SUCCESS);
}
