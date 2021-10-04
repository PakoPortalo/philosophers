/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 10:39:14 by fportalo          #+#    #+#             */
/*   Updated: 2021/10/01 15:42:01 by fportalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	bad_param(void)
{
	printf("ERROR: Param is not a number");
	exit(0);
}

int	handle_param_1(char *argv, int i)
{
	while (argv[i] != '\0')
	{
		if (!ft_isdigit(argv[i]))
		{
			printf("ERROR: You have wrong params\n");
			return (-1);
		}
		i++;
	}
	if (check_max_int(argv) == -1)
	{
		printf("BROOO: te has pasado muchísssimo chaval andaa tira \n");
		return (-1);
	}
	return (0);
}

int	handle_param(char *argv)
{
	int	param;
	int	i;

	i = 0;
	if (handle_param_1(argv, i) == -1)
		return (-1);
	if (atoi(argv))
		param = atoi(argv);
	else
	{
		printf("ERROR: You have wrong params\n");
		return (-1);
	}
	if (atoi(argv) < 0)
	{
		printf("ERROR: you introduced negative numbers\n");
		return (-1);
	}
	return (param);
}

int	arg_count(int argc)
{
	if (argc != 5 && argc != 6)
	{
		printf("ERROR:Wrong number of args");
		return (-1);
	}
	return (1);
}
