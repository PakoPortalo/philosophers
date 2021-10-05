/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 16:38:50 by fportalo          #+#    #+#             */
/*   Updated: 2021/10/05 12:54:17 by fportalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec) * 1000 + (time.tv_usec / 1000));
}

uint64_t	get_time_sub(uint64_t subtraction)
{
	return (get_time() - subtraction);
}

int	ft_usleep(uint64_t time, t_philosopher *philo)
{
	uint64_t	finish;
	uint64_t	getaux;

	finish = get_time() + time;
	getaux = get_time();
	while (getaux < finish)
	{
		usleep(philo->params.num);
		getaux = get_time();
	}
	return (-1);
}
