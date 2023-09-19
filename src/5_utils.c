/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:32:02 by jmarinho          #+#    #+#             */
/*   Updated: 2023/09/19 15:39:10 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// this is a function that will convert a string to an integer
int	ft_atoi(const char *str)
{
	int		i;
	int		sig;
	long	res;

	i = 0;
	res = 0;
	sig = 1;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sig = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (sig * res);
}

// this is a function the will print the error, free allocated memory and exit
// the program
void	exit_error(char *str, t_project *project, int flag)
{
	printf("%s", str);
	if (flag == 1)
		free(project->philo);
	if (flag == 2)
	{
		free(project->philo);
		free(project->mtx_fork);
	}
	if (flag == 3)
		free_mtxs(project);
	exit (1);
}

// this is a function that will free the mutexes and the join the threads
void	free_mtxs(t_project *project)
{
	int	i;

	i = -1;
	if (project->philo)
		free(project->philo);
	if (project->mtx_fork)
	{
		while (++i < project->n_philo)
			pthread_mutex_destroy(&project->mtx_fork[i]);
		free(project->mtx_fork);
	}
	pthread_mutex_destroy(&project->mtx_print);
	pthread_mutex_destroy(&project->mtx_eat);
	pthread_mutex_destroy(&project->mtx_end);
}

// this is a function that will return the current time in milliseconds
// we return the number of seconds x1000 to get number of miliseconds
// plus the number of microseconds /1000 to get the remaining miliseconds
long long	get_current_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}
