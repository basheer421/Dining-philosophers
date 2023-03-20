/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 21:56:30 by bammar            #+#    #+#             */
/*   Updated: 2023/03/20 20:41:03 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define GRN "\033[0;32m"
# define WHT "\x1B[37m"
# define RST "\033[0m"

typedef enum e_state
{
	THINKING,
	EATING,
	SLEEPING,
	DEATH
}					t_state;

// Shared (common args).
typedef struct s_philo_args
{
	size_t			count;
	size_t			die_time;
	size_t			eat_time;
	size_t			sleep_time;
	size_t			eat_limit;
	bool			is_limited;
	time_t			start_time;
}					t_philo_args;

// Private to each philo (not shared).
typedef struct s_philo
{
	size_t			num;
	size_t			eat_count;
	time_t			last_mealtime;
	pthread_mutex_t	*mealtime_mutex;
	t_state			state;
}					t_philo;

// Thread argument.
typedef struct t_process_arg
{
	t_philo			*philo;
	t_philo_args	*args;
	bool			*is_exit;
	sem_t			*exit_sem;
	sem_t			*forks_sem;
	sem_t			*print_sem;
	sem_t			*forks_available;
	pthread_t		*exit_thread;
}					t_process_arg;

typedef struct s_sim_args
{
	t_process_arg	*process_arg;
	bool			is_exit;
	sem_t			*exit_sem;
	sem_t			*forks_sem;
	sem_t			*print_sem;
	sem_t			*limit_sem;
	sem_t			*forks_available;
}					t_sim_args;

void				print_error(const char *msg);
long				ft_atol(const char *str);
int					ft_strlen(const char *s);
char				*ft_strdup(const char *s);
int					ft_index(const char *str, int c);
char				*ft_strtrim(char const *s1, char const *set);

// Parses the given args and fills them inside the struct.
bool				fill_philo_args(int argc, char **argv, t_philo_args *args);
t_philo				**get_philos(t_philo_args *args);
void				philo_destroy(t_philo **philos);

// Get the current time since the start of the program in milliseconds.
time_t				get_time(void);

// sleep for the given milliseconds
void				psleep(time_t milliseconds);

/*
	prints the state of the philo in this state:
	{timestamp_in_ms} {philo_number} {philo_state}
*/
void				print_msg(t_process_arg *targ, const char *state);

// The function where threads start.
void				simulate_philos(t_philo_args *args, t_philo **philos);

// Routine
void				philo_life(t_process_arg *targ);

// -- Life functions --
bool				eat(t_process_arg *targ);
void				go_sleep(t_process_arg *targ);
void				think(t_process_arg *targ);

#endif