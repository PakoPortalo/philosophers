/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 16:07:49 by fportalo          #+#    #+#             */
/*   Updated: 2021/10/06 15:35:20 by fportalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_sticks(t_params *params)
{
	int	i;

	i = 0;
	pthread_mutex_init(&params->printer, NULL);
	pthread_mutex_unlock(&params->printer);
	while (i < params->num)
	{
		pthread_mutex_init(&params->stick[i], NULL);
		pthread_mutex_unlock(&params->stick[i]);
		i++;
	}
}

void	set_sticks(t_params *params, t_philosopher *philo, int i)
{
	if (i != (params->num - 1))
	{
		philo->stick_l = &params->stick[i];
		philo->stick_r = &params->stick[i + 1];
	}
	else
	{
		philo->stick_l = &params->stick[i];
		philo->stick_r = &params->stick[0];
	}
}

void	philo_data(t_params *params, t_philosopher *philo, int i)
{
	philo->id = i + 1;
	philo->params.num = params->num;
	philo->params.die = params->die;
	philo->params.eat = params->eat;
	philo->params.sleep = params->sleep;
	philo->params.num_eats = params->num_eats;
	philo->ini_start = &params->ini_start;
	philo->printer = &params->printer;
	philo->is_dead = &params->is_dead;
	philo->last_eat = 0;
}

void	ini_threads(t_params *params, t_philosopher *philo)
{
	int	i;

	i = 0;
	init_sticks(params);
	params->ini_start = get_time();
	while (i < params->num)
	{
		set_sticks(params, &philo[i], i);
		philo_data(params, &philo[i], i);
		pthread_create(&params->threads[i], NULL, philo_routine, &philo[i]);
		i++;
	}
}
