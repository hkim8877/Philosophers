/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjkim <hyunjkim@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 13:37:13 by hyunjkim          #+#    #+#             */
/*   Updated: 2025/08/13 13:37:14 by hyunjkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].eat_count = 0;
		data->philos[i].last_eat_time = data->start_time;
		data->philos[i].data = data;
		pthread_mutex_init(&data->philos[i].meal_lock, NULL);
		if (data->philos[i].id % 2 == 0)
		{
			data->philos[i].left_fork = (i + 1) % data->num_philos;
			data->philos[i].right_fork = i;
		}
		else
		{
			data->philos[i].left_fork = i;
			data->philos[i].right_fork = (i + 1) % data->num_philos;
		}
		i++;
	}
}

static void	ft_free(t_data *data)
{
	if (data->philos)
		free(data->philos);
	if (data->forks)
		free(data->forks);
}

void	init_data(t_data *data, int argc, char **argv)
{
	int	i;

	data->num_philos = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	data->end_flag = false;
	if (argc == 6)
		data->must_eat = ft_atol(argv[5]);
	else
		data->must_eat = -1;
	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->philos || !data->forks)
	{
		ft_free(data);
		ft_error("Error: memory allocation failed\n", 1);
	}
	pthread_mutex_init(&data->mtx, NULL);
	pthread_mutex_init(&data->print, NULL);
	i = 0;
	while (i < data->num_philos)
		pthread_mutex_init(&data->forks[i++], NULL);
	data->start_time = get_time();
	init_philos(data);
}
