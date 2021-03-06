/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 16:28:19 by fportalo          #+#    #+#             */
/*   Updated: 2021/10/08 12:41:02 by fportalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating_sub1(t_philosopher *philo)
{
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(philo->stick_l);
		printer(philo, TAKEN);
		pthread_mutex_lock(philo->stick_r);
		printer(philo, TAKEN);
	}
	else
	{
		pthread_mutex_lock(philo->stick_r);
		printer(philo, TAKEN);
		pthread_mutex_lock(philo->stick_l);
		printer(philo, TAKEN);
	}
}

void	eating_sub2(t_philosopher *philo)
{
	philo->last_eat = get_time();
	printer(philo, EAT);
	philo->params.num_eats--;
	if (philo->params.num_eats == 0)
		philo->full = 1;
	ft_usleep(philo->params.eat, philo);
	pthread_mutex_unlock(philo->stick_l);
	pthread_mutex_unlock(philo->stick_r);
}

int	eating(t_philosopher *philo)
{
	if (philo->full == 0)
	{
		if (philo->params.num == 1)
		{
			printer(philo, TAKEN);
			ft_usleep(philo->params.die, philo);
			*philo->is_dead = 1;
			return (-1);
		}
		eating_sub1(philo);
		if (philo->params.eat > philo->params.die)
		{
			ft_usleep((philo->params.die), philo);
			*philo->is_dead = 1;
			return (-1);
		}
		eating_sub2(philo);
	}
	return (0);
}

int	sleeping(t_philosopher *philo)
{
	printer(philo, SLEEP);
	if (philo->params.die < philo->params.eat + philo->params.sleep)
	{
		ft_usleep((philo->params.die - philo->params.eat), philo);
		*philo->is_dead = 1;
		return (-1);
	}
	ft_usleep(philo->params.sleep, philo);
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	if (philo->id % 2 == 1)
		usleep(20);
	while (*philo->is_dead == 0 && philo->full == 0)
	{
		if (eating(philo) == -1)
			return (NULL);
		if (sleeping(philo) == -1)
			return (NULL);
		printer(philo, THINK);
		if (philo->full == 1)
			return (NULL);
	}
	return (NULL);
}
