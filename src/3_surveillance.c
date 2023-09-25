/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_surveillance.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:31:51 by jmarinho          #+#    #+#             */
/*   Updated: 2023/09/25 11:52:24 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	dead_or_full(t_philo *philo)
{
	if ((get_current_time() - philo->last_meal) >= philo->project->time_to_die)
	{
		print_status(philo, RED"died"RESET);
		philo->project->should_end = 1;
		return (TRUE);
	}
	if ((philo->project->times_must_eat > 0)
		&& (philo->times_eaten >= philo->project->times_must_eat))
	{
		philo->project->nbr_philo_full++;
		if (philo->project->nbr_philo_full == philo->project->nbr_philo)
		{
			philo->project->should_end = 1;
			print_status(philo, NULL);
			return (TRUE);
		}
	}
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
		usleep(10);
	}
}
