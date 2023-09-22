/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_simulation_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:31:56 by jmarinho          #+#    #+#             */
/*   Updated: 2023/09/22 15:42:54 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	philo_grab_forks(t_philo *philo)
{
	if (philo->project->should_end == 1
		|| philo->project->nbr_philo_full == philo->project->nbr_philo)
		return (-1);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->fork_left);
		print_status(philo, YELLOW"has taken a fork"RESET);
		pthread_mutex_lock(philo->fork_right);
		print_status(philo, YELLOW"has taken a fork"RESET);
	}
	else
	{
		pthread_mutex_lock(philo->fork_right);
		print_status(philo, YELLOW"has taken a fork"RESET);
		pthread_mutex_lock(philo->fork_left);
		print_status(philo, YELLOW"has taken a fork"RESET);
	}
	return (0);
}

int	philo_is_eating(t_philo *philo)
{
	if (philo->project->should_end == 1
		|| (philo->project->nbr_philo_full == philo->project->nbr_philo))
	{
		pthread_mutex_unlock(philo->fork_right);
		pthread_mutex_unlock(philo->fork_left);
		return (-1);
	}
	print_status(philo, BLUE"is eating"RESET);
	philo->last_meal = get_current_time();
	philo->times_eaten++;
	if (philo->project->times_must_eat != -1)
		if (philo->times_eaten == philo->project->times_must_eat)
			philo->project->nbr_philo_full++;
	usleep(philo->project->time_to_eat * 1000);
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
	return (0);
}

int	philo_is_sleeping(t_philo *philo)
{
	if (philo->project->should_end == 1
		|| philo->project->nbr_philo_full == philo->project->nbr_philo)
		return (-1);
	print_status(philo, PURPLE"is sleeping"RESET);
	usleep(philo->project->time_to_sleep * 1000);
	return (0);
}

void	print_status(t_philo *philo, char *str)
{
	long long	timestamp;

	if (should_simulation_end(philo, FALSE) == FALSE)
	{
		timestamp = get_current_time() - philo->project->start_time;
		printf("%lld %d %s\n", timestamp, philo->id, str);
	}
	if (str == NULL)
		printf(GREEN"All philosophers ate %d times\n"RESET,
			philo->project->times_must_eat);
}

int	should_simulation_end(t_philo *philo, int should_end)
{
	if (should_end == TRUE || philo->project->should_end == 1)
	{
		if (should_end == TRUE)
			philo->project->should_end = 1;
		return (TRUE);
	}
	return (FALSE);
}
