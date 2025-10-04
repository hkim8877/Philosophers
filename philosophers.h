/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjkim <hyunjkim@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 13:37:41 by hyunjkim          #+#    #+#             */
/*   Updated: 2025/08/13 13:37:42 by hyunjkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdbool.h>
# include <limits.h>

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int				num_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			start_time;
	int				must_eat;
	bool			end_flag;
	pthread_mutex_t	*forks;
	pthread_mutex_t	mtx;
	pthread_mutex_t	print;
	t_philo			*philos;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	int				eat_count;
	long			last_eat_time;
	pthread_mutex_t	meal_lock;
	pthread_t		thread;
	t_data			*data;
}	t_philo;

//check_argc.c && init.c
long	ft_atol(const char *str);
int		check_args(int argc, char **argv);
void	init_philos(t_data *data);
void	init_data(t_data *data, int argc, char **argv);

// routine.c && monitoring.c
void	*routine(void *philo);
void	*monitoring(void *ptr);

// print.c && utils.c && single_philo.c
void	ft_error(char *msg, int code);
void	free_all(t_data *data);
long	get_time(void);
void	ft_usleep(t_data *data, long time_to_wait);
void	print_status(t_philo *philo, char *status);
void	single_philo(t_data *data);

#endif
