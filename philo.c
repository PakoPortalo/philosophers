/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 13:27:01 by fportalo          #+#    #+#             */
/*   Updated: 2021/10/04 13:02:47 by fportalo         ###   ########.fr       */
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
		params->number_eats = -1;
	else
	{
		if (handle_param(argv[5]) == -1)
			return (-1);
		else
			params->number_eats = handle_param(argv[5]);
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
	while(params->is_dead == 0)
	{
		all_dead(philo);
		//printf("hola");
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
