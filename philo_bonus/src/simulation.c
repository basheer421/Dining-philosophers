/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 19:02:59 by bammar            #+#    #+#             */
/*   Updated: 2023/03/20 20:41:34 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	start_fork(t_philo_args *args, t_philo *philo, t_sim_args *sargs,
		int *pid)
{
	t_process_arg	parg;

	parg.exit_sem = sargs->exit_sem;
	parg.forks_sem = sargs->forks_sem;
	parg.forks_available = sargs->forks_available;
	parg.print_sem = sargs->print_sem;
	parg.args = args;
	parg.philo = philo;
	*pid = fork();
	if (*pid)
		return ;
	philo_life(&parg);
	exit(0);
}

static void	create_sems(t_sim_args *sim_args, unsigned int p_count)
{
	sem_unlink(".exit");
	sem_unlink(".forks");
	sem_unlink(".available");
	sem_unlink(".print");
	sim_args->exit_sem = sem_open(".exit", O_CREAT, 0644, 1);
	sim_args->forks_sem = sem_open(".forks", O_CREAT, 0644, p_count / 2);
	sim_args->limit_sem = sem_open(".available", O_CREAT, 0644, 1);
	sim_args->print_sem = sem_open(".print", O_CREAT, 0644, 1);
}

void	simulate_philos(t_philo_args *args, t_philo **philos)
{
	int			i;
	int			*pids;
	t_sim_args	sim_args;

	memset(&(sim_args), 0, sizeof(t_sim_args));
	create_sems(&sim_args, args->count);
	pids = malloc(sizeof(int) * (args->count + 1));
	if (!pids)
		exit(EXIT_FAILURE);
	sem_wait((sim_args.exit_sem));
	i = -1;
	while (++i < (int)args->count)
		start_fork(args, philos[i], &sim_args, &(pids[i]));
	sem_wait((sim_args.exit_sem));
	i = -1;
	while (++i < (int)args->count)
		kill(pids[i], SIGQUIT);
	free(pids);
	sem_post((sim_args.exit_sem));
	sem_close(sim_args.exit_sem);
	sem_close(sim_args.forks_sem);
	sem_close(sim_args.limit_sem);
	sem_close(sim_args.print_sem);
}
