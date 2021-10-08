/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 13:27:01 by fportalo          #+#    #+#             */
/*   Updated: 2021/10/08 11:29:41 by fportalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_params(int argc, char **argv, t_params *params)
{
	int	i;

	i = 0;
	if (handle_param(argv[1]) == -1 || handle_param(argv[2]) == -1 || \
		handle_param(argv[3]) == -1 || handle_param(argv[4]) == -1 )
		return (-1);
	else
	{
		params->num = handle_param(argv[1]);
		params->die = handle_param(argv[2]);
		params->eat = handle_param(argv[3]);
		params->sleep = handle_param(argv[4]);
	}
	if (argc == 5)
		params->num_eats = -1;
	else
	{
		if (handle_param(argv[5]) == -1)
			return (-1);
		else
			params->num_eats = handle_param(argv[5]);
	}
	params->is_dead = 0;
	return (0);
}

void	alloc_memory(t_params *params, t_philosopher *philo)
{
	params->stick = malloc(sizeof(pthread_mutex_t) * params->num);
	philo->printer = malloc(sizeof(pthread_mutex_t) * params->num);
	params->threads = malloc(sizeof(pthread_t) * params->num);
}

void	free_memory(t_params *params, t_philosopher *philo)
{
	//free(params->stick);
	//free(philo->printer);
	free(params->threads);
	free(philo);
}

void	join_threads(t_params *params)
{
	int	i;

	i = 0;
	while (i < params->num)
	{
		pthread_join(params->threads[i], NULL);
		i++;
	}
}

//void	ciao_mutex(t_philosopher *philo)
//{
//	int i;

//	i = 0;
//	pthread_mutex_unlock(philo->printer);
//	while (i <= philo->params.num)
//	{
//		pthread_mutex_unlock(philo[i].stick_l);
//		i++;
//	}
//}

int	check_full(t_params *params, t_philosopher *philo)
{
	int i;
	int j;

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
	//if (j == params->num)
	//{
	//	ciao_mutex(philo);
	//	return (-1);
	//}
	return (0);
}

int	check_loop(t_params *params, t_philosopher *philo)
{
	int	i;

	i = 0;
	while (params->is_dead == 0)
	{
		if (philo[i].full == 0)
		{

			if (i >= philo->params.num)
				i = 0;
			if (philo->full == 1)
				break;
			if (philo[i].last_eat != 0 && \
				(get_time() - philo[i].last_eat) > params->die)
			{
				params->is_dead = 1;
				printf("[%llu]Philosopher %d died\n", \
					get_time_sub(*philo->ini_start), philo[i].id);
				return (-1);
			}
			if (params->is_dead == 1)
			{
				printf("[%llu]Philosopher %d died\n", \
					get_time_sub(*philo->ini_start), philo[i].id);
				return (-1);
			}
		}
		i++;
	}
	if (check_full(params, philo) == -1)
		return(-1);
	return (-1);
}

int	main(int argc, char *argv[])
{
	t_params		params;
	t_philosopher	*philo;
	int				i;

	i = 0;
	if (arg_count(argc) == -1)
		return (-1);
	if (get_params(argc, argv, &params) == -1)
		return (-1);
	philo = malloc(sizeof(t_philosopher) * params.num);
	alloc_memory(&params, philo);
	ini_threads(&params, philo);
	check_loop(&params, philo);
	join_threads(&params);
	free_memory(&params, philo);
	//system("leaks philo");
	return (0);
}
