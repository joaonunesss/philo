/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_surveillance.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:31:51 by jmarinho          #+#    #+#             */
/*   Updated: 2023/09/19 15:40:22 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/*
	here is where we check when it's time to end the simulation
	1) surveillance: used to check if the simulation should end or not
		- we can pass a value to the function to set the simulation to end
		- or we can check it by seeing if any philo has died or all have eaten
	2) dead_or_full: used to check if any philo has died or all have eaten
		- if any philo has died, we set the simulation to end
		- if all philos have eaten, we print a message and set the simulation to end
*/

int	dead_or_full(t_project *d, t_philo *p)
{
	pthread_mutex_lock(&d->mtx_eat);
	if ((get_current_time() - p->last_eaten) >= d->time_to_die)
	{
		print_status(p, "died");
		should_simulation_end(p, TRUE);
		pthread_mutex_unlock(&d->mtx_eat);
		return (TRUE);
	}
	if ((d->times_must_eat > 0) && (p->times_eaten >= d->times_must_eat))
	{
		d->n_philo_full++;
		if (d->n_philo_full == d->n_philo)
		{
			should_simulation_end(p, TRUE);
			print_status(p, NULL);
			pthread_mutex_unlock(&d->mtx_eat);
			return (TRUE);
		}
	}
	pthread_mutex_unlock(&d->mtx_eat);
	return (FALSE);
}

void	surveillance(t_project *d)
{
	int	i;
	int	should_end;

	should_end = FALSE;
	while (should_end == FALSE)
	{
		i = -1;
		while (++i < d->n_philo)
		{
			if (should_end == FALSE && dead_or_full(d, &d->philo[i]) == TRUE)
				should_end = TRUE;
		}
		usleep(10);
	}
}
