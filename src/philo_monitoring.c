/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitoring.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 17:12:03 by jmarinho          #+#    #+#             */
/*   Updated: 2023/09/06 17:19:34 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	philo_monitoring(t_project *project)
{
	int	i;
	int	continue_flag;

	continue_flag = 1;
	while (continue_flag)
	{
		i = 0;
		project->is_full = 0;
		while (++i <= project->nbr_philos)
		{
			if (continue_flag && is_someone_dead_or_full(&project->philo[i]))
				continue_flag = 0;
		}
		usleep(10);
	}
	finish_dinner(project);
}

int	is_someone_dead_or_full(t_philosophers *philosophers)
{
	pthread_mutex_lock(&philosophers->project->eat_mutex);
	if (now() - philosophers->last_time_eat >= philosophers->project->time_to_die)
	{
		print_action(philosophers, "died");
		is_time_to_finish(philosophers, 1);
		pthread_mutex_unlock(&philosophers->project->eat_mutex);
		return (EXIT_FAILURE);
	}
	else if (philosophers->project->times_must_eat > 0
		&& philosophers->eat_count >= philosophers->project->times_must_eat)
	{
		philosophers->project->is_full++;
		if (philosophers->project->is_full >= philosophers->project->nbr_philos)
		{
			is_time_to_finish(philosophers, 1);
			print_action(philosophers, "f");
			pthread_mutex_unlock(&philosophers->project->eat_mutex);
			return (EXIT_FAILURE);
		}
	}
	pthread_mutex_unlock(&philosophers->project->eat_mutex);
	return (EXIT_SUCCESS);
}

void	finish_dinner(t_project *project)
{
	int	i;

	i = 1;
	while (i < project->nbr_philos)
		pthread_join(project->philo[i++].thread, NULL);
	destroy_padlocks(project);
}

void	destroy_padlocks(t_project *project)
{
	int	i;

	i = 1;
	while (++i < project->nbr_philos)
		pthread_mutex_destroy(&project->fork_mutex[i++]);
	free(project->philo);
	free(project->fork_mutex);
	pthread_mutex_destroy(&project->print_mutex);
	pthread_mutex_destroy(&project->eat_mutex);
	pthread_mutex_destroy(&project->finish_mutex);
}

/*
	here is where we check when it's time to end the simulation
	1) philo_monitoring: used to check if the simulation should end or not
		- we can pass a value to the function to set the simulation to end
		- or we can check it by seeing if any philo has died or all have eaten
	2) is_someone_full_or_dead: used to check if any philo has died or all have eaten
		- if any philo has died, we set the simulation to end
		- if all philos have eaten, we print a message and set the simulation to end
*/