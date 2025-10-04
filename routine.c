/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjkim <hyunjkim@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 13:37:54 by hyunjkim          #+#    #+#             */
/*   Updated: 2025/08/13 13:37:55 by hyunjkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_eat_time = get_time();
	philo->eat_count++;
	print_status(philo, "is eating");
	pthread_mutex_unlock(&philo->meal_lock);
	ft_usleep(philo->data, philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
}

void	*routine(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	if (philo->id % 2 == 0)
	{
		print_status(philo, "is thinking");
		usleep(1000);
	}
	while (1)
	{
		pthread_mutex_lock(&philo->data->mtx);
		if (philo->data->end_flag)
		{
			pthread_mutex_unlock(&philo->data->mtx);
			break ;
		}
		pthread_mutex_unlock(&philo->data->mtx);
		philo_eat(philo);
		print_status(philo, "is sleeping");
		ft_usleep(philo->data, philo->data->time_to_sleep);
		print_status(philo, "is thinking");
		usleep(500);
	}
	return (NULL);
}
