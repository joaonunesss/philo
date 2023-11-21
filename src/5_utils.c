/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:32:02 by jmarinho          #+#    #+#             */
/*   Updated: 2023/11/21 15:53:23 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_atoi(char *str)
{
	int		i;
	int		signal;
	long	atoi;

	i = 0;
	atoi = 0;
	signal = 1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		atoi = atoi * 10 + str[i] - 48;
		i++;
	}
	return (signal * atoi);
}

void	exit_error(char *str, t_project *project, int flag)
{
	printf("%s", str);
	free(project->philo);
	if (flag == 1)
	{
		free_mtxs(project);
		free(project);
	}
	exit (EXIT_FAILURE);
}

void	free_mtxs(t_project *project)
{
	int	i;

	i = -1;
	while (++i < project->nbr_philo)
	{
		if (&project->mtx_fork[i])
			pthread_mutex_destroy(&project->mtx_fork[i]);
	}
	free(project->mtx_fork);
}

long long	get_current_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

void	init_project_aux(t_project *project, int ac, char **av)
{
	project->nbr_philo_full = 0;
	project->should_end = 0;
	project->start_time = get_current_time();
	project->philo = malloc(sizeof(t_philo) * project->nbr_philo);
	if (!project->philo)
		exit_error(RED"Error: Creation of the PHILO MALLOC failed\n"RESET,
			project, 0);
}
