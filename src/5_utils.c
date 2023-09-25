/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:32:02 by jmarinho          #+#    #+#             */
/*   Updated: 2023/09/22 15:59:34 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_atoi(const char *str)
{
	int		i;
	int		sig;
	long	res;

	i = 0;
	res = 0;
	sig = 1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (sig * res);
}

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
	exit (EXIT_FAILURE);
}

void	free_mtxs(t_project *project)
{
	int	i;

	i = -1;
	if (project->philo)
		free(project->philo);
	if (project->mtx_fork)
	{
		while (++i < project->nbr_philo)
			pthread_mutex_destroy(&project->mtx_fork[i]);
		free(project->mtx_fork);
	}
}

long long	get_current_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}
