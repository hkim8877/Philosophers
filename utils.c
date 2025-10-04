/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjkim <hyunjkim@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 13:38:07 by hyunjkim          #+#    #+#             */
/*   Updated: 2025/08/13 13:38:08 by hyunjkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_error(char *msg, int code)
{
	if (code == 1)
	{
		printf("%s\n", msg);
		exit(1);
	}
	printf("%s\n", msg);
}

void	free_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->mtx);
	pthread_mutex_destroy(&data->print);
	free(data->philos);
	free(data->forks);
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

static int	check_end_flag(t_data *data)
{
	int	flag;

	pthread_mutex_lock(&data->mtx);
	flag = data->end_flag;
	pthread_mutex_unlock(&data->mtx);
	return (flag);
}

void	ft_usleep(t_data *data, long time_to_wait)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < time_to_wait)
	{
		if (check_end_flag(data))
			break ;
		usleep(500);
	}
}
