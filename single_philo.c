/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjkim <hyunjkim@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 13:38:00 by hyunjkim          #+#    #+#             */
/*   Updated: 2025/08/13 13:38:02 by hyunjkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	single_philo(t_data *data)
{
	data->start_time = get_time();
	printf("%ld 1 has taken a fork\n", get_time() - data->start_time);
	ft_usleep(data, data->time_to_die);
	printf("%ld 1 died\n", get_time() - data->start_time);
	free_all(data);
	exit (0);
}
