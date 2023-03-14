/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 21:56:30 by bammar            #+#    #+#             */
/*   Updated: 2023/03/14 21:50:25 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
# include <string.h>

#define GRN	"\033[0;32m"
#define WHT	"\x1B[37m"
#define RST	"\033[0m"

typedef enum e_state
{
	THINKING,
	EATING,
	SLEEPING
}	t_state;

// Shared (common args).
typedef struct s_philo_args
{
	size_t	count;
	size_t	die_time;
	size_t	eat_time;
	size_t	sleep_time;
	size_t	eat_limit;
	bool	is_limited;
	time_t	start_time;
}	t_philo_args;

// Can be common between 2 philos.
typedef struct s_fork
{
	bool			is_used;
	pthread_mutex_t	*is_used_mutex;
	size_t			last_user;
	pthread_mutex_t	*mutex;
}	t_fork;

// Private to each philo (not shared).
typedef struct s_philo
{
	size_t			num;
	size_t			eat_count;
	t_fork			*lfork;
	t_fork			*rfork;
	pthread_t		*thread;
	time_t			last_mealtime;
	t_state			state;
}	t_philo;

// Thread argument.
typedef struct s_thread_arg
{
	t_philo			*philo;
	t_philo_args	*args;
	bool			*is_exit;
	pthread_mutex_t	*exit_mutex;
	pthread_mutex_t	*print_mutex;
}	t_thread_arg;

void	print_error(const char *msg);
long	ft_atol(const char *str);
int 	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
int		ft_index(const char *str, int c);
char	*ft_strtrim(char const *s1, char const *set);

// Parses the given args and fills them inside the struct.
bool	fill_philo_args(int argc, char **argv, t_philo_args *args);
t_fork	**get_forks(t_philo_args *args);
t_philo	**get_philos(t_fork **forks, t_philo_args *args);
void	philo_destroy(t_fork **forks, t_philo **philos);

// Get the current time since the start of the program in milliseconds.
time_t	get_time(void);

// sleep for the given milliseconds
void	psleep(time_t milliseconds);

/*
	prints the state of the philo in this state:
	{timestamp_in_ms} {philo_number} {philo_state}
*/
void	print_msg(t_thread_arg *targ, const char *state);

// The function where threads start.
void	simulate_philos(t_philo_args *args, t_philo **philos);

// Routine
void	*philo_life(void *t_arg);

#endif