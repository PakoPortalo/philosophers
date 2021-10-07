/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 13:27:01 by fportalo          #+#    #+#             */
/*   Updated: 2021/10/07 13:41:23 by fportalo         ###   ########.fr       */
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

void	all_dead(t_philosopher *philo)
{
	int i;

	i = 0;
	while (i < philo->params.num)
	{
		if (philo[i].is_dead == 0)
			*philo[i].is_dead = 1;
		i++;
	}
}

int	check_loop(t_params *params, t_philosopher *philo)
{
	int i;

	i = 0;
	while(params->is_dead == 0 || params->num_eats)
	{
		if (i >= philo->params.num)
			i = 0;
		//fprintf(stderr, "%llu -- %llu\n, ", philo[i].last_eat, get_time() - philo[i].last_eat);

		if (philo[i].last_eat != 0 && (get_time() - philo[i].last_eat) > params->die)
		{
			params->is_dead = 1;
			//printf("Get Time: %llu\n", (get_time()));
			//printf("Last Eat: %llu\n", (philo[i].last_eat));
			//printf("La maldita resta es: %llu\n", (get_time() - philo[i].last_eat));
			printf("[\033[0;31m%llu\033[0;37m]Philosopher %d \033[0;31mdied\033[0;37m\n", get_time_sub(*philo->ini_start), philo[i].id);
			return (-1);
		}
		if (params->is_dead == 1)
		{
			printf("[\033[0;31m%llu\033[0;37m]Philosopher %d \033[0;31mdied\033[0;37m\n", get_time_sub(*philo->ini_start), philo[i].id);
			return (-1);
		}
		i++;
	}
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
	if (check_loop(&params, philo) == -1)
		return (-1);
	join_threads(&params);
	return (0);
}
