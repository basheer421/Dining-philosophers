/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 19:02:59 by bammar            #+#    #+#             */
/*   Updated: 2023/03/18 22:50:45 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	start_fork(t_philo_args *args, t_philo *philo, t_sim_args *sargs, int *pid)
{
	t_process_arg	parg;

	parg.exit_sem = sargs->exit_sem;
	parg.forks_sem = sargs->forks_sem;
	parg.limit_sem = sargs->limit_sem;
	parg.print_sem = sargs->print_sem;
	parg.is_exit = &(sargs->is_exit);
	parg.args = args;
	parg.philo = philo;
	*pid = fork();
	if (*pid) // Parent
		return ;
	philo_life(&parg); // Child
}

static void	create_sems(t_sim_args *sim_args, unsigned int p_count)
{
	sem_unlink(".exit");
	sem_unlink(".forks");
	sem_unlink(".limit");
	sem_unlink(".print");
	sim_args->exit_sem = sem_open(".exit", O_CREAT, 0644, 1);
	sim_args->forks_sem = sem_open(".forks", O_CREAT, 0644, p_count);
	sim_args->limit_sem = sem_open(".limit", O_CREAT, 0644, 1);
	sim_args->print_sem = sem_open(".print", O_CREAT, 0644, 1);
}

void	simulate_philos(t_philo_args *args, t_philo **philos)
{
	size_t			i;
	int				*pids;
	t_sim_args		sim_args;

	sim_args.is_exit = false;
	memset(&(sim_args.process_arg), 0, sizeof(t_sim_args));
	sim_args.limits_reached = 0;
	create_sems(&sim_args, args->count);
	pids = malloc(sizeof(int) * (args->count + 1));
	i = 0;
	while (i < args->count)
		start_fork(args, philos[i], &sim_args, &(pids[i++]));
	i = 0;
	while (i < args->count)
		waitpid(pids[i++], NULL, 0);
	sem_close(sim_args.exit_sem);
	sem_close(sim_args.forks_sem);
	sem_close(sim_args.limit_sem);
	sem_close(sim_args.print_sem);
}
