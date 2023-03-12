/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 09:35:40 by bammar            #+#    #+#             */
/*   Updated: 2023/02/04 19:31:15 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	haschr(char c, char *s)
{
	int	i;

	i = 0;
	while (s[i] != 0)
		if (s[i++] == c)
			return (1);
	return (0);
}

int	get_sum_of_trimmed(const char *s1, const char *set)
{
	char	*s;
	int		s1_len;
	int		i;
	int		sum_of_trimmed;

	s = (char *)s1;
	s1_len = ft_strlen(s);
	sum_of_trimmed = 0;
	i = 0;
	while (s[i] != 0 && (haschr(s[i], (char *)set)))
		if (haschr(s[i++], (char *)set))
			sum_of_trimmed++;
	i = s1_len - 1;
	while (i >= 0 && (haschr(s[i], (char *)set)))
		if (haschr(s[i--], (char *)set))
			sum_of_trimmed++;
	return (sum_of_trimmed);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		y;
	int		end;
	char	*s;

	if (!s1 || !set)
		return (NULL);
	i = ft_strlen((char *)s1) - 1;
	end = i;
	while (i >= 0 && (haschr(s1[i--], (char *)set)))
		end--;
	if (get_sum_of_trimmed(s1, (char *)set) >= (int)ft_strlen((char *)s1))
		return (ft_strdup(""));
	s = (char *)malloc(ft_strlen((char *)s1) - get_sum_of_trimmed(s1,
				(char *)set) + 1);
	if (!s)
		return (NULL);
	i = 0;
	while (s1[i] != 0 && (haschr(s1[i], (char *)set)))
		i++;
	y = 0;
	while (i <= end)
		s[y++] = s1[i++];
	s[y] = 0;
	return (s);
}
