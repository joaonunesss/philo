/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_simulation_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:31:56 by jmarinho          #+#    #+#             */
/*   Updated: 2023/11/22 12:05:31 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	philo_grab_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->project->mtx_surveillance);
	if (philo->project->should_end == TRUE
		|| philo->project->nbr_philo_full == philo->project->nbr_philo)
	{
		pthread_mutex_unlock(&philo->project->mtx_surveillance);
		return (-1);
	}
	pthread_mutex_unlock(&philo->project->mtx_surveillance);
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
	return (EXIT_SUCCESS);
}

int	philo_is_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->project->mtx_surveillance);
	if (philo->project->should_end == TRUE
		|| (philo->project->nbr_philo_full == philo->project->nbr_philo))
	{
		pthread_mutex_unlock(&philo->project->mtx_surveillance);
		pthread_mutex_unlock(philo->fork_right);
		pthread_mutex_unlock(philo->fork_left);
		return (-1);
	}
	pthread_mutex_unlock(&philo->project->mtx_surveillance);
	pthread_mutex_lock(&philo->project->mtx_eating);
	philo->last_meal = get_current_time();
	print_status(philo, BLUE"is eating"RESET);
	philo->times_eaten++;
	if (philo->project->times_must_eat != -1)
		if (philo->times_eaten == philo->project->times_must_eat)
			philo->project->nbr_philo_full++;
	pthread_mutex_unlock(&philo->project->mtx_eating);
	usleep(philo->project->time_to_eat * 1000);
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
	return (EXIT_SUCCESS);
}

int	philo_is_sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->project->mtx_surveillance);
	if (philo->project->should_end == TRUE
		|| philo->project->nbr_philo_full == philo->project->nbr_philo)
	{
		pthread_mutex_unlock(&philo->project->mtx_surveillance);
		return (-1);
	}
	pthread_mutex_unlock(&philo->project->mtx_surveillance);
	print_status(philo, PURPLE"is sleeping"RESET);
	usleep(philo->project->time_to_sleep * 1000);
	return (EXIT_SUCCESS);
}

void	print_status(t_philo *philo, char *str)
{
	long long	timestamp;

	pthread_mutex_lock(&philo->project->mtx_surveillance);
	if (philo->project->should_end == FALSE && str != NULL)
	{
		timestamp = get_current_time() - philo->project->start_time;
		printf("%lld %d %s\n", timestamp, philo->id, str);
	}
	pthread_mutex_unlock(&philo->project->mtx_surveillance);
	if (str == NULL)
		printf(GREEN"All philosophers ate %d times\n"RESET,
			philo->project->times_must_eat);
}
