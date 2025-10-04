/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjkim <hyunjkim@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 13:37:29 by hyunjkim          #+#    #+#             */
/*   Updated: 2025/08/13 13:37:32 by hyunjkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	check_death(t_data *data, int i, long time)
{
	if (time - data->philos[i].last_eat_time > data->time_to_die)
	{
		pthread_mutex_unlock(&data->philos[i].meal_lock);
		pthread_mutex_lock(&data->mtx);
		if (!data->end_flag)
		{
			data->end_flag = true;
			pthread_mutex_lock(&data->print);
			printf("%ld %d died\n", time - data->start_time,
				data->philos[i].id);
			pthread_mutex_unlock(&data->print);
		}
		pthread_mutex_unlock(&data->mtx);
		return (true);
	}
	return (false);
}

static bool	check_philo_status(t_data *data, int *finished_eating)
{
	int		i;
	long	time;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->philos[i].meal_lock);
		time = get_time();
		if (check_death(data, i, time))
			return (false);
		if (data->must_eat != -1 && data->philos[i].eat_count >= data->must_eat)
			(*finished_eating)++;
		pthread_mutex_unlock(&data->philos[i].meal_lock);
		i++;
	}
	return (true);
}

void	*monitoring(void *arg)
{
	t_data	*data;
	int		finished_eating;

	data = (t_data *)arg;
	while (1)
	{
		finished_eating = 0;
		if (!check_philo_status(data, &finished_eating))
			return (NULL);
		pthread_mutex_lock(&data->mtx);
		if (data->must_eat != -1 && finished_eating == data->num_philos)
		{
			data->end_flag = true;
			pthread_mutex_unlock(&data->mtx);
			return (NULL);
		}
		pthread_mutex_unlock(&data->mtx);
		usleep(500);
	}
	return (NULL);
}
