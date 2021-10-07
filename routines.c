/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 16:28:19 by fportalo          #+#    #+#             */
/*   Updated: 2021/10/07 13:16:04 by fportalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		printer(t_philosopher *philo, int choose)
{
	pthread_mutex_lock(philo->printer);
	if (*philo->is_dead == 0 && philo->params.num_eats != 0)
	{
		if (choose == TAKEN)
			printf("[%llu]Philosopher %d has taken a fork\n", get_time_sub(*philo->ini_start) , philo->id);
		else if (choose == EAT)
			printf("[\033[0;32m%llu\033[0;37m]Philosopher %d is \033[0;32meating\033[0;37m\n", get_time_sub(*philo->ini_start), philo->id);
		else if (choose == SLEEP)
			printf("[%llu]Philosopher %d is sleeping\n", get_time_sub(*philo->ini_start), philo->id);
		else if (choose == THINK)
			printf("[%llu]Philosopher %d is thinking\n", get_time_sub(*philo->ini_start), philo->id);
		else if (choose == DIE)
		{
			printf("[%llu]Philosopher %d died\n", get_time_sub(*philo->ini_start), philo->id);
			return (-1);
		}
	}
	pthread_mutex_unlock(philo->printer);
	return(0);
}

int		eating(t_philosopher *philo)
{
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(philo->stick_l);
		printer(philo, TAKEN);
		pthread_mutex_lock(philo->stick_r);
		printer(philo, TAKEN);
		//usleep(10);
	}
	else
	{
		pthread_mutex_lock(philo->stick_r);
		printer(philo, TAKEN);
		pthread_mutex_lock(philo->stick_l);
		printer(philo, TAKEN);
	}
	if (philo->params.eat > philo->params.die)
	{
		ft_usleep((philo->params.die), philo);
		// printer(philo, DIE);
		*philo->is_dead = 1;
		return(-1);
	}
	philo->last_eat = get_time();
	printer(philo, EAT);
	ft_usleep(philo->params.eat, philo);
	pthread_mutex_unlock(philo->stick_l);
	pthread_mutex_unlock(philo->stick_r);
	return (0);
}

int		sleeping(t_philosopher *philo)
{
		printer(philo, SLEEP);
		if (philo->params.die < philo->params.eat + philo->params.sleep)
		{
			ft_usleep((philo->params.die - philo->params.eat), philo);
			*philo->is_dead = 1;
			return(-1);
		}
		ft_usleep(philo->params.sleep, philo);
		return(0);
}

void		thinking(t_philosopher *philo)
{
	printer(philo, THINK);
}

void	*philo_routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	if (philo->id % 2 == 1)
		ft_usleep(10, philo);
	while(*philo->is_dead == 0)
	{
		//if(get_time() - philo.last_eat > philo.params.die)
		//{
		//	*philo.is_dead = 1;
		//	break;
		//}
		if (eating(philo) == -1)
			return(NULL);
		if (sleeping(philo) == -1)
			return(NULL);
		thinking(philo);
	}
	return (NULL);
}
