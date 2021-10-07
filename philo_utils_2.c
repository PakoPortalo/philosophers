/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 16:38:50 by fportalo          #+#    #+#             */
/*   Updated: 2021/10/07 15:43:11 by fportalo         ###   ########.fr       */
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

int	printer(t_philosopher *philo, int choose)
{
	pthread_mutex_lock(philo->printer);
	if (*philo->is_dead == 0 && philo->params.num_eats != 0)
	{
		if (choose == TAKEN)
			printf("[%llu]Philosopher %d has taken a fork\n", \
				get_time_sub(*philo->ini_start), philo->id);
		else if (choose == EAT)
			printf("[%llu]Philosopher %d is eating\n", \
				get_time_sub(*philo->ini_start), philo->id);
		else if (choose == SLEEP)
			printf("[%llu]Philosopher %d is sleeping\n", \
				get_time_sub(*philo->ini_start), philo->id);
		else if (choose == THINK)
			printf("[%llu]Philosopher %d is thinking\n", \
				get_time_sub(*philo->ini_start), philo->id);
		else if (choose == DIE)
		{
			printf("[%llu]Philosopher %d died\n", \
				get_time_sub(*philo->ini_start), philo->id);
			return (-1);
		}
	}
	pthread_mutex_unlock(philo->printer);
	return (0);
}
