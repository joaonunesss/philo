/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:14:39 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/06/29 18:01:52 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"

void	ft_destroy(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->verify);
	while (i < data->nbr_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].alive);
		i++;
	}
	free(data->philos);
	free(data->forks);
}
