/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccosta-c <ccosta-c@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:03:17 by ccosta-c          #+#    #+#             */
/*   Updated: 2023/06/29 19:30:16 by ccosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"

int	ft_whitespace(const char *str, int *ptr_i)
{
	int	i;
	int	minus;

	i = 0;
	minus = 1;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] == '-')
	{
		minus *= -1;
		i++;
	}
	if (str[i] == '+')
		i++;
	*ptr_i = i;
	return (minus);
}

long	ft_atoi(const char *nptr)
{
	int		i;
	long	sign;
	long	result;

	result = 0;
	sign = ft_whitespace(nptr, &i);
	while (nptr[i] != '\0' && nptr[i] >= '0' && nptr[i] <= '9')
	{
		result *= 10;
		result += nptr[i] - 48;
		i++;
	}
	if (nptr[i] == '.' || nptr[i] == ',')
		return (0);
	result *= sign;
	return (result);
}

long long	get_time(void)
{
	struct timeval	time;
	long long		time_total;

	gettimeofday(&time, NULL);
	time_total = ((time.tv_sec * 1000) + (time.tv_usec / 1000));
	return (time_total);
}

void	ft_print(t_philos *philo, char *str)
{
	long long	time;

	pthread_mutex_lock(&philo->data->verify);
	if (philo->data->died
		|| philo->data->all_ate == philo->data->nbr_philos)
	{
		pthread_mutex_unlock(&philo->data->verify);
		return ;
	}
	pthread_mutex_unlock(&philo->data->verify);
	time = get_time() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->print);
	printf("%lld %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->data->print);
}
