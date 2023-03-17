/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 00:30:20 by bammar            #+#    #+#             */
/*   Updated: 2023/03/18 01:39:41 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	contains_nonnum(const char *str)
{
	char	*temp;

	temp = (char *)(str);
	while (*(temp))
		if ((*temp < '0' || *temp > '9')
			&& *temp != '+')
			return (true);
	else
			temp++;
	return (false);
}

static void	destroy_words(char **words)
{
	int	i;

	i = -1;
	while (words[++i])
		free(words[i]);
}

static bool	set_words(int argc, char **argv, char **words)
{
	int		wordc;

	wordc = -1;
	while (++wordc < argc - 1)
	{
		words[wordc] = ft_strtrim(argv[wordc + 1], " ");
		if (!words[wordc])
			return (destroy_words(words), false);
		if (contains_nonnum(words[wordc]))
			return (destroy_words(words), false);
	}
	return (true);
}

static bool	is_valid_num(char *s, long n)
{
	if (!s)
		return (true);
	if (n == 0 && (*s >= '0' && *s <= '9')
		&& ft_strlen(s) == 1 && *s == '0')
		return (true);
	else if (n <= 0)
		return (false);
	return (true);
}

bool	fill_philo_args(int argc, char **argv, t_philo_args *args)
{
	char	*words[6];
	int		i;

	i = -1;
	while (++i < 6)
		words[i] = NULL;
	memset(args, 0, sizeof(t_philo_args));
	if (argc == 6)
		args->is_limited = true;
	if (!set_words(argc, argv, words))
		return (false);
	args->count = ft_atol(words[0]);
	args->die_time = ft_atol(words[1]);
	args->eat_time = ft_atol(words[2]);
	args->sleep_time = ft_atol(words[3]);
	if (args->is_limited)
		args->eat_limit = ft_atol(words[4]);
	args->start_time = get_time();
	if (!is_valid_num(words[0], args->count)
		|| !is_valid_num(words[1], args->die_time)
		|| !is_valid_num(words[2], args->eat_time)
		|| !is_valid_num(words[3], args->sleep_time)
		|| !is_valid_num(words[4], args->eat_limit))
		return (destroy_words(words), false);
	return (destroy_words(words), true);
}
