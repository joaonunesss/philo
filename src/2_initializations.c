/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_initializations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:31:48 by jmarinho          #+#    #+#             */
/*   Updated: 2023/09/22 15:42:48 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*start_simulation(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (1)
	{
		if (philo->project->nbr_philo == 1)
		{
			print_status(philo, YELLOW"has taken a fork"RESET);
			break ;
		}
		if (philo->id % 2 == 0)
			usleep(4000);
		if (philo_grab_forks(philo) == -1)
			break ;
		if (philo_is_eating(philo) == -1)
			break ;
		if (philo_is_sleeping(philo) == -1)
			break ;
		print_status(philo, "is thinking");
	}
	return (NULL);
}

void	init_thread(t_project *project)
{
	int	i;

	i = -1;
	while (++i < project->nbr_philo)
	{
		if (pthread_create(&project->philo[i].thread, NULL,
				start_simulation, &project->philo[i]) != 0)
			exit_error(RED"Error: Creation of the thread failed\n"RESET,
				project, 3);
	}
	surveillance(project);
	i = -1;
	while (++i < project->nbr_philo)
	{
		if (pthread_join(project->philo[i].thread, NULL) != 0)
			exit_error(RED"Error: Joining of the thread failed\n"RESET,
				project, 3);
	}
}

void	init_philo(t_project *project)
{
	int	i;

	i = 0;
	while (i < project->nbr_philo)
	{
		project->philo[i].id = i + 1;
		project->philo[i].fork_right = &project->mtx_fork[i];
		if ((i + 1) != project->nbr_philo)
			project->philo[i].fork_left = &project->mtx_fork[i + 1];
		else
			project->philo[i].fork_left = &project->mtx_fork[0];
		project->philo[i].times_eaten = 0;
		project->philo[i].last_meal = project->start_time;
		project->philo[i].project = project;
		i++;
	}
}

void	init_mtxs(t_project *project)
{
	int	i;

	i = -1;
	project->mtx_fork = malloc(sizeof(pthread_mutex_t) * project->nbr_philo);
	if (!project->mtx_fork)
		exit_error(RED"Error: Creation of the FORK MALLOC failed\n"RESET,
			project, 2);
	while (++i < project->nbr_philo)
	{
		if (pthread_mutex_init(&project->mtx_fork[i], NULL) != 0)
			exit_error(RED"Error: Creation of the FORK MUTEX failed\n"RESET,
				project, 2);
	}
}

void	init_project(t_project *project, int ac, char **av)
{
	project->nbr_philo = ft_atoi(av[1]);
	project->time_to_die = ft_atoi(av[2]);
	project->time_to_eat = ft_atoi(av[3]);
	project->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		project->times_must_eat = ft_atoi(av[5]);
	else
		project->times_must_eat = 0;
	project->nbr_philo_full = 0;
	project->should_end = 0;
	project->start_time = get_current_time();
	project->philo = malloc(sizeof(t_philo) * project->nbr_philo);
	if (!project->philo)
		exit_error(RED"Error: Creation of the PHILO MALLOC failed\n"RESET,
			project, 1);
	if (project->nbr_philo < 1)
		exit_error(RED"Error: There must be at least one philosopher\n"RESET,
			project, 1);
	if (project->time_to_die < 1 || project->time_to_eat < 1
		|| project->time_to_sleep < 1)
		exit_error(RED"Error: Time arguments must be greater than 0\n"RESET,
			project, 1);
	if (ac == 6 && project->times_must_eat < 1)
		exit_error(RED"Error: If it exists, the last arg must be > 0\n"RESET,
			project, 1);
}
