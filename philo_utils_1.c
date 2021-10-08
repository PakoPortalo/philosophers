/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 12:32:03 by fportalo          #+#    #+#             */
/*   Updated: 2021/10/08 12:38:06 by fportalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	check_max_int_1(char *argv)
{
	if (argv[0] > 2)
		return (-1);
	if (argv[0] > 1)
		return (-1);
	if (argv[0] > 4)
		return (-1);
	if (argv[0] > 7)
		return (-1);
	if (argv[0] > 4)
		return (-1);
	if (argv[0] > 8)
		return (-1);
	if (argv[0] > 3)
		return (-1);
	if (argv[0] > 6)
		return (-1);
	if (argv[0] > 4)
		return (-1);
	if (argv[0] > 7)
		return (-1);
	return (0);
}

int	check_max_int(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	if (i > 10)
		return (-1);
	else if (i == 10)
	{
		if (check_max_int_1(argv) == -1)
			return (-1);
	}
	return (0);
}

int	check_full(t_params *params, t_philosopher *philo)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < params->num)
	{
		if (philo[i].full == 1)
		{
			j++;
		}
		i++;
	}
	return (0);
}

void	alloc_memory(t_params *params)
{
	params->stick = malloc(sizeof(pthread_mutex_t) * params->num);
	params->threads = malloc(sizeof(pthread_t) * params->num);
}
