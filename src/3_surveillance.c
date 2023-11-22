/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_surveillance.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:31:51 by jmarinho          #+#    #+#             */
/*   Updated: 2023/11/22 11:57:48 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	dead_or_full(t_philo *philo)
{
	pthread_mutex_lock(&philo->project->mtx_eating);
	pthread_mutex_lock(&philo->project->mtx_surveillance);
	if ((get_current_time() - philo->last_meal) >= philo->project->time_to_die)
	{
		pthread_mutex_unlock(&philo->project->mtx_surveillance);
		print_status(philo, RED"died"RESET);
		philo->project->should_end = TRUE;
		pthread_mutex_unlock(&philo->project->mtx_eating);
		return (TRUE);
	}
	if ((philo->project->times_must_eat > 0)
		&& (philo->times_eaten >= philo->project->times_must_eat))
	{
		if (philo->project->nbr_philo_full == philo->project->nbr_philo)
		{
			pthread_mutex_unlock(&philo->project->mtx_surveillance);
			print_status(philo, NULL);
			philo->project->should_end = TRUE;
			pthread_mutex_unlock(&philo->project->mtx_eating);
			return (TRUE);
		}
	}
	pthread_mutex_unlock(&philo->project->mtx_surveillance);
	pthread_mutex_unlock(&philo->project->mtx_eating);
	return (FALSE);
}

void	surveillance(t_project *project)
{
	int	i;
	int	should_end;

	should_end = FALSE;
	while (should_end == FALSE)
	{
		i = -1;
		while (++i < project->nbr_philo)
		{
			if (should_end == FALSE && dead_or_full(&project->philo[i]) == TRUE)
				should_end = TRUE;
		}
		usleep(80);
	}
}
