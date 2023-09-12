/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overseer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ride-sou <ride-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 11:51:32 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/07/03 12:33:32 by ride-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"

int	num_philos_dead(t_data *rules)
{
	int	i;

	i = 0;
	while (i < rules->nbr_philos)
	{
		pthread_mutex_lock(&rules->philos[i].alive);
		if ((get_time() - rules->philos[i].last_meal) >= rules->time_die)
		{
			ft_print(&rules->philos[i], "died.");
			pthread_mutex_lock(&rules->verify);
			rules->died = 1;
			pthread_mutex_unlock(&rules->verify);
			pthread_mutex_unlock(&rules->philos[i].alive);
			return (1);
		}
		pthread_mutex_unlock(&rules->philos[i].alive);
		i++;
	}
	return (0);
}

int	num_philos_eaten(t_data *rules)
{
	if (rules->times_to_eat == -1)
		return (0);
	pthread_mutex_lock(&rules->verify);
	if (rules->all_ate == rules->nbr_philos)
	{
		pthread_mutex_lock(&rules->print);
		printf("All philosophers ate!");
		pthread_mutex_unlock(&rules->print);
		pthread_mutex_unlock(&rules->verify);
		return (1);
	}
	pthread_mutex_unlock(&rules->verify);
	return (0);
}

void	*monitoring(void *index)
{
	t_data	*rules;

	rules = (t_data *)index;
	while (1)
	{
		if (num_philos_dead(rules))
			return (NULL);
		if (num_philos_eaten(rules))
			return (NULL);
	}
}
